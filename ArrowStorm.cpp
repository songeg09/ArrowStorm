#include "ArrowStorm.h"
#include "DrawManager.h"
#include "Projectile.h"
#include "Player.h"
#include "Actor.h"
#include "MapManager.h"

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
}

bool ArrowStorm::LoadGame()
{
	return false;
}

void ArrowStorm::Initialize()
{
	// 벽 그리기
	std::string Line;
	for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
	{
		DrawManager::gotoxy(0, y);
		Line = "";
		for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH; ++x)
		{
			Line += DrawManager::GetObjectIcon(MapManager::GetBoard()[y][x]);
		}
		std::cout << Line;
	}
	// 아이템 상자 및 출입구 그리기

	
	// 플레이어 리셋
	m_CreatureArr.push_back(std::make_unique<Player>(
		Position(BOARD_SIZE::BOARD_WIDTH / 2, BOARD_SIZE::BOARD_HEIGHT / 2),
		BOARD_OBJECT::PLAYER_UP
	));


	// 임시 몬스터
	m_CreatureArr.push_back(std::make_unique<Creature>(
		Position(10,3),
		BOARD_OBJECT::WALL
	));

	for (int id = 0; id < m_CreatureArr.size(); ++id)
	{
		if (m_CreatureArr[id])
		{
			Position CreaturePos = m_CreatureArr[id]->GetCurrentPosition();
			BOARD_OBJECT CreatureObj = m_CreatureArr[id]->GetActorObject();
			DrawManager::DrawObjectAtPosition(CreaturePos, CreatureObj);
		}
	}
}

void ArrowStorm::Run()
{
	Initialize();
	
	while (1)
	{
		Tick();
		CollisionCheck();

		//if (IsGameOver())
		//	return;
	}
}

void ArrowStorm::Tick()
{
	// 플레이어 틱
	m_CreatureArr[0]->Tick();
	//m_Player->Tick();

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

void ArrowStorm::CollisionCheck()
{
	for (std::list<std::unique_ptr<Projectile>>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end();)
	{
		Position CurrentPos = (*it)->GetCurrentPosition();

		// 1. 범위 밖 or 벽에 충돌
		if (!InRange(CurrentPos) || MapManager::GetBoard()[CurrentPos.m_y][CurrentPos.m_x] == BOARD_OBJECT::WALL)
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
				m_CreatureArr[HitIndex]->TakeDamage((*it)->GetDamage());
				AfterHit(HitIndex);
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

// 체력을 확인하고 죽어야 한다면 맵에서 지우고
// 인스턴스 삭제해주기
void ArrowStorm::AfterHit(const int& _Index)
{
	Position CurrentPos = m_CreatureArr[_Index]->GetCurrentPosition();
	
	// 죽어야 하는 경우 지우기
	if (m_CreatureArr[_Index]->GetHp() == 0)
	{
		DrawManager::DrawObjectAtPosition(
			CurrentPos, 
			MapManager::GetBoard()[CurrentPos.m_y][CurrentPos.m_x]
		);
		m_CreatureArr[_Index] = nullptr;
	}

	// 살았을 경우 화살을 지우고 크리쳐 다시 그려주기
	else
	{
		DrawManager::DrawObjectAtPosition(
			CurrentPos,
			m_CreatureArr[_Index]->GetActorObject()
		);
	}
}

void ArrowStorm::RemoveProjectile(std::list<std::unique_ptr<Projectile>>::iterator& it)
{
	Position CurrentPos = (*it)->GetCurrentPosition();
	DrawManager::DrawObjectAtPosition(CurrentPos, MapManager::GetBoard()[CurrentPos.m_y][CurrentPos.m_x]);
	it = m_ProjectileList.erase(it);
}

///*
//	이동 못하는 경우
//	1. 맵 범위 밖
//	2. m_Board[y][x]가 EMPTY이지 않은경우
//*/
//bool ArrowStorm::IsMovableTile(const Position& _Position)
//{
//	if (!InRange(_Position))
//		return false;
//	if (m_Board[_Position.m_y][_Position.m_x].m_Type != BOARD_OBJECT::EMPTY)
//		return false;
//	return true;
//}
//
bool ArrowStorm::InRange(const Position& _Position)
{
	return (0 <= _Position.m_x && _Position.m_x < BOARD_SIZE::BOARD_WIDTH
		&& 0 <= _Position.m_y && _Position.m_y < BOARD_SIZE::BOARD_HEIGHT);
}

