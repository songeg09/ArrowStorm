#include "ArrowStorm.h"
#include "DrawManager.h"
#include "MapManager.h"
#include "UIManager.h"

#include "Projectile.h"
#include "Player.h"
#include "Actor.h"
#include "Slime.h"
#include "Skeleton.h"
#include "Bow.h"
#include "TriBow.h"


ArrowStorm& ArrowStorm::GetInstance()
{
	static ArrowStorm ArrowStorm;
	return ArrowStorm;
}

ArrowStorm::ArrowStorm()
{
	
}

ArrowStorm::~ArrowStorm()
{

}

void ArrowStorm::NewGame()
{
	// 임시 초기화
	for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH; ++x)
		{
			if (y == 0 || x == 0 || y == BOARD_SIZE::BOARD_HEIGHT - 1 || x == BOARD_SIZE::BOARD_WIDTH - 1)
			{
				MapManager::GetBoard()[y][x] = BOARD_OBJECT::WALL;
			}
			else
			{
				MapManager::GetBoard()[y][x] = BOARD_OBJECT::EMPTY;
			}
		}
	}

	MapManager::GetBoard()[20][20] = BOARD_OBJECT::CHEST;
	MapManager::GetBoard()[20][23] = BOARD_OBJECT::CHEST;
	MapManager::GetBoard()[20][25] = BOARD_OBJECT::BOW;

}

bool ArrowStorm::LoadGame()
{
	return false;
}

void ArrowStorm::Initialize()
{
	m_CreatureArr.clear();
	
	m_CreatureArr.push_back(std::make_unique<Player>(
		Position(BOARD_SIZE::BOARD_WIDTH / 2, BOARD_SIZE::BOARD_HEIGHT / 2),
		BOARD_OBJECT::PLAYER_UP
	));

	m_CreatureArr.push_back(std::make_unique<Skeleton>(
		Position(10,3)
	));

	m_CreatureArr.push_back(std::make_unique<Slime>(
		Position(20, 3)
	));

	MapManager::DrawFullBoard();
	UIManager::DrawUI();
}

void ArrowStorm::Run()
{
	Initialize();
	
	while (1)
	{
		Tick();
		CollisionCheck();
		CommitTick();
		ItemCheck();

		if (IsGameOver())
		{
			DrawManager::DrawInfoPopup("Game Over!");
			return;
		}
	}
}

void ArrowStorm::Tick()
{
	// 플레이어 틱
	m_CreatureArr[0]->Tick();

	// 몬스터 틱
	for (int i = 1; i < m_CreatureArr.size(); ++i)
	{
		if (m_CreatureArr[i] == nullptr) continue;

		m_CreatureArr[i]->Tick();
	}

	// 투사체 틱
	for (std::list<std::unique_ptr<Projectile>>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end(); it++)
	{
		(*it)->Tick();
	}
}

//활 충돌 확인 및 데미지 적용
void ArrowStorm::CollisionCheck()
{
	for (std::list<std::unique_ptr<Projectile>>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end();)
	{
		Position CurrentPos = (*it)->GetCurrentPosition();

		// 1. 범위 밖 or 벽에 충돌
		if (!MapManager::InRange(CurrentPos) || MapManager::GetBoard()[CurrentPos.m_y][CurrentPos.m_x] == BOARD_OBJECT::WALL)
		{
			RemoveProjectile(it);
		}
		else
		{
			// 2. 크리쳐에 맞았을 경우
			int HitIndex = DidHit((*it));
			if (HitIndex != -1)
			{
				// 데미지 적용
				ApplyHit(HitIndex, (*it)->GetDamage());
				it = m_ProjectileList.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

// 화살이 크리쳐를 맞추었을 경우,
// 해당 크리쳐의 인덱스를 반환
int ArrowStorm::DidHit(const std::unique_ptr<Projectile>& _Projectile)
{
	for (int index = 0; index < m_CreatureArr.size(); ++index)
	{
		if (m_CreatureArr[index] == nullptr) continue;

		if (m_CreatureArr[index]->GetCurrentPosition() == _Projectile->GetCurrentPosition())
		{
			return index;
		}
	}
	return -1;
}

// 데미지 적용및 덧그려주기
void ArrowStorm::ApplyHit(const int& _Index, const int _Damage)
{
	m_CreatureArr[_Index]->TakeDamage(_Damage);
	Position CurrentPos = m_CreatureArr[_Index]->GetCurrentPosition();
	DrawManager::DrawObjectAtPosition(CurrentPos, m_CreatureArr[_Index]->GetActorObject());
}

// 리스트에서 투사체 삭제및 덧그리기
void ArrowStorm::RemoveProjectile(std::list<std::unique_ptr<Projectile>>::iterator& it)
{
	Position CurrentPos = (*it)->GetCurrentPosition();
	DrawManager::DrawObjectAtPosition(CurrentPos, MapManager::GetBoard()[CurrentPos.m_y][CurrentPos.m_x]);
	it = m_ProjectileList.erase(it);
}

void ArrowStorm::CommitTick()
{
	for (int index = 0; index < m_CreatureArr.size(); ++index)
	{
		if (m_CreatureArr[index] == nullptr) continue;

		if (m_CreatureArr[index]->GetHp() == 0)
		{
			Position CurrentPos = m_CreatureArr[index]->GetCurrentPosition();
			DrawManager::DrawObjectAtPosition(CurrentPos, MapManager::GetBoard()[CurrentPos.m_y][CurrentPos.m_x]);
			m_CreatureArr[index] = nullptr;
		}	
	}
}

bool ArrowStorm::IsGameOver()
{
	if (m_CreatureArr[0] == nullptr)
		return true;
	return false;
}

bool ArrowStorm::CreatureExistAtPos(const Position& _Pos)
{
	for (int index = 0; index < GetInstance().GetCreatureArr().size(); ++index)
	{
		if (GetInstance().GetCreatureArr()[index] == nullptr) continue;
		if (GetInstance().GetCreatureArr()[index]->GetCurrentPosition() == _Pos)
			return true;
	}
	return false;
}

void ArrowStorm::ItemCheck()
{
	if (m_CreatureArr[0] != nullptr)
	{
		if (Player* player = dynamic_cast<Player*>(m_CreatureArr[0].get()))
		{
			Position Pos = player->GetCurrentPosition();
			if (MapManager::GetBoard()[Pos.m_y][Pos.m_x] == BOARD_OBJECT::CHEST)
			{
				int Type = rand() % 2;
				player->EarnPotion((POTION_TYPE)Type);
				MapManager::GetBoard()[Pos.m_y][Pos.m_x] = BOARD_OBJECT::EMPTY;
			}
			else if (MapManager::GetBoard()[Pos.m_y][Pos.m_x] == BOARD_OBJECT::BOW)
			{
				
				BowChange(player);

				MapManager::GetBoard()[Pos.m_y][Pos.m_x] = BOARD_OBJECT::EMPTY;
			}
		}
	}
}

void ArrowStorm::BowChange(Player* player)
{
	// Random Bow 만들어야 겠지?
	std::unique_ptr<Bow> TempBow = std::make_unique<TriBow>(player);
	std::string Msg = player->GetBow()->GetName() + " -> " + TempBow->GetName();
	if (DrawManager::DrawConfirmPopup(Msg))
	{
		player->SetBow(std::move(TempBow));
	}
	// 화면 다시 그리기
	MapManager::DrawFullBoard();
}