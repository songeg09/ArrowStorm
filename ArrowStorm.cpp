#include "ArrowStorm.h"
#include "DrawManager.h"
#include "UIManager.h"

#include "Projectile.h"
#include "Player.h"
#include "Actor.h"
#include "Monster.h"
#include "Slime.h"
#include "Skeleton.h"

#include "Bow.h"
#include "TriBow.h"
#include "FastBow.h"

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

void ArrowStorm::InitGame()
{
	// 초기화
	m_EndGame = false;
	m_CreatureArr.clear();
	m_ProjectileList.clear();
	m_CreatureArr.push_back(std::make_unique<Player>(Position(BOARD_SIZE::BOARD_WIDTH / 2, BOARD_SIZE::BOARD_HEIGHT / 2), BOARD_OBJECT::PLAYER_UP));
}

void ArrowStorm::NewGame()
{
	InitGame();
	m_Map.SetCurMapIndex(0);
	m_Map.LoadMapsForNewGame();
}

bool ArrowStorm::LoadGame()
{
	InitGame();
	if(!m_Map.LoadMapsToContinue() || !LoadPlayerInfo())
		return false;
	return true;
}

bool ArrowStorm::LoadPlayerInfo()
{
	std::fstream load("Saves/Player_Save.txt");
	if (!load.is_open()) return false;

	int tmp1, tmp2;
	
	if (Player* player = dynamic_cast<Player*>(m_CreatureArr[0].get()))
	{
		// 플레이어 위치 설정
		load >> tmp1 >> tmp2;
		player->SetCurrentPosition(Position(tmp1, tmp2));

		// 활 로드
		load >> tmp1;
		LoadBow((BOW_TYPE)tmp1);

		// Hp 및 Mp 로드
		load >> tmp1 >> tmp2;
		player->SetHp(tmp1);
		player->SetMp(tmp2);

		// 포션 수 로드
		load >> tmp1 >> tmp2;
		player->SetHpPotion(tmp1);
		player->SetMpPotion(tmp2);

		// 레벨 로드
		load >> tmp1;
		player->SetLevel(tmp1);

		// 경험치 로드
		load >> tmp1;
		player->SetExp(tmp1);

		// 최대 체력및 마나 로드
		load >> tmp1 >> tmp2;
		player->SetCurrentMaxHp(tmp1);
		player->SetCurrentMaxMp(tmp2);

		// 공격력 및 공격속도 로드
		load >> tmp1 >> tmp2;
		player->SetRangedDamage(tmp1);
		player->SetAttackSpeed(tmp2);
	}

	load.close();

	return true;
}

void ArrowStorm::EndGame()
{
	std::string Msg = "저장 하시겠습니까?";
	if (DrawManager::DrawConfirmPopup(Msg))
	{
		SavePlayerInfo();
		m_Map.SaveMapInfo();
	}

	Msg = "저장 성공! 게임을 종료하시겠습니까?";
	if (DrawManager::DrawConfirmPopup(Msg))
	{
		m_EndGame = true;
		return;
	}

	DrawFullBoard();
}

void ArrowStorm::SavePlayerInfo()
{
	std::ofstream save("Saves/Player_Save.txt", std::ios::trunc);

	if (Player* player = dynamic_cast<Player*>(m_CreatureArr[0].get()))
	{
		// 위치 저장
		save << player->GetCurrentPosition().m_x << " " << player->GetCurrentPosition().m_y << std::endl;;
		// 활 타입 저장
		save << player->GetBow()->GetType() << std::endl;
		// Hp 및 Mp 저장
		save << player->GetHp() << " " << player->GetMp() << std::endl;
		// 포션 수 저장
		save << player->GetHpPotion() << " " << player->GetMpPotion() << std::endl;;
		// 레벨 저장
		save << player->GetLevel() << std::endl;
		// 경험치 저장
		save << player->GetExp() << std::endl;
		// 최대 체력 및 마나 저장
		save << player->GetCurrentMaxHp() << " " << player->GetCurrentMaxMp() << std::endl;
		// 공격력 및 공격속도 저장
		save << player->GetRangedDamage() << " " << player->GetAttackSpeed() << std::endl;
	}
	save.close();
}

void ArrowStorm::InitBoard()
{
	GenerateMonster();
	DrawFullBoard();
	UIManager::DrawUI();
}

void ArrowStorm::Run()
{
	InitBoard();
	
	while (1)
	{
		Tick();
		CollisionCheck();
		CommitTick();

		if (IsGameOver())
		{
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
		// 1. 범위 밖 or 벽에 충돌
		if (!DidHitWall(it))
		{
			// 2. 크리쳐에 맞았을 경우
			int HitIndex = DidHitCreature((*it));
			if (HitIndex != -1)
			{
				// 데미지 적용
				ApplyHit(HitIndex, (*it)->GetDamage());
				
				// 경험치 적용
				if (HitIndex != 0 && m_CreatureArr[HitIndex]->GetHp() <= 0)
				{
					if (Player* player = dynamic_cast<Player*>((*it)->GetOwner()))
					{
						if (Monster* monster = dynamic_cast<Monster*>(m_CreatureArr[HitIndex].get()))
						{
							player->EarnExp(monster->GetExp());
						}
					}
				}

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
int ArrowStorm::DidHitCreature(const std::unique_ptr<Projectile>& _Projectile)
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
	m_CreatureArr[_Index]->Render();
}

// 리스트에서 투사체 삭제및 덧그리기
bool ArrowStorm::DidHitWall(std::list<std::unique_ptr<Projectile>>::iterator& it)
{
	Position CurrentPos = (*it)->GetCurrentPosition();

	if (!m_Map.InRange(CurrentPos))
	{
		it = m_ProjectileList.erase(it);
		return true;
	}
	else if (m_Map.GetBoardObject(CurrentPos.m_x, CurrentPos.m_y) == BOARD_OBJECT::WALL 
		|| m_Map.GetBoardObject(CurrentPos.m_x, CurrentPos.m_y) == BOARD_OBJECT::DOOR)
	{
		DrawManager::DrawObjectAtPosition(CurrentPos, m_Map.GetBoardObject(CurrentPos.m_x, CurrentPos.m_y));
		it = m_ProjectileList.erase(it);
		return true;
	}

	return false;
}

void ArrowStorm::CommitTick()
{
	for (int index = 0; index < m_CreatureArr.size(); ++index)
	{
		if (m_CreatureArr[index] == nullptr) continue;

		if (m_CreatureArr[index]->GetHp() == 0)
		{
			Position CurrentPos = m_CreatureArr[index]->GetCurrentPosition();
			DrawManager::DrawObjectAtPosition(CurrentPos, m_Map.GetBoardObject(CurrentPos.m_x, CurrentPos.m_y));
			m_CreatureArr[index] = nullptr;
		}	
	}
}

bool ArrowStorm::IsGameOver()
{
	if (m_CreatureArr[0] == nullptr)
	{
		m_EndGame = true;
		DrawManager::DrawInfoPopup("Game Over!");
	}
		
	return m_EndGame;
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

void ArrowStorm::ItemCheck(Player* player)
{
	if (player == nullptr) return;
	
	Position Pos = player->GetCurrentPosition();
	if (m_Map.GetBoardObject(Pos.m_x, Pos.m_y) == BOARD_OBJECT::CHEST)
	{
		int Type = rand() % 2;
		player->EarnPotion((POTION_TYPE)Type);
		m_Map.GetBoard()[Pos.m_y][Pos.m_x] = BOARD_OBJECT::EMPTY;
	}
	else if (m_Map.GetBoardObject(Pos.m_x, Pos.m_y) == BOARD_OBJECT::BOW)
	{
				
		BowChange(player);
		m_Map.GetBoard()[Pos.m_y][Pos.m_x] = BOARD_OBJECT::EMPTY;
	}
}

std::unique_ptr<Bow> CreateBow(BOW_TYPE _BowType)
{
	std::unique_ptr<Bow> bow;
	switch (_BowType)
	{
	case BOW_TYPE::BASIC:
		bow = std::make_unique<Bow>();
		break;
	case BOW_TYPE::TRIPLE:
		bow = std::make_unique<TriBow>();
		break;
	case BOW_TYPE::FAST:
		bow = std::make_unique<FastBow>();
		break;
	default:
		bow = std::make_unique<Bow>();
		break;
	}

	return std::move(bow);
}

void ArrowStorm::BowChange(Player* player)
{
	// Random Bow 생성
	int RandomBowType = rand() % BOW_TYPE::BOW_TYPE_COUNT;
	std::unique_ptr<Bow> TempBow = CreateBow((BOW_TYPE)RandomBowType);

	std::string Msg = player->GetBow()->GetName() + " -> " + TempBow->GetName();
	if (DrawManager::DrawConfirmPopup(Msg))
	{
		player->SetBow(std::move(TempBow));
		player->GetBow()->SetOwner(player);
		player->GetBow()->SetAttackTimerCool(player->GetAttackSpeed());
	}
	// 화면 다시 그리기
	DrawFullBoard();
}

void ArrowStorm::LoadBow(BOW_TYPE _BowType) 
{
	if (Player* player = dynamic_cast<Player*>(m_CreatureArr[0].get()))
	{
		std::unique_ptr<Bow> LoadedBow = CreateBow(_BowType);
		player->SetBow(std::move(LoadedBow));
		player->GetBow()->SetOwner(player);
	}
}

void ArrowStorm::DrawFullBoard()
{
	m_Map.DrawBoard();
	
	// 투사체 그리기
	for (std::list<std::unique_ptr<Projectile>>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end(); ++it)
	{
		Position CreaturePos = (*it)->GetCurrentPosition();
		BOARD_OBJECT CreatureObj = (*it)->GetActorObject();
		DrawManager::DrawObjectAtPosition(CreaturePos, CreatureObj);
	}

	// 크리쳐들 그리기
	for (int id = 0; id < m_CreatureArr.size(); ++id)
	{
		if (Creature* Creature = m_CreatureArr[id].get())
		{
			Position CreaturePos = Creature->GetCurrentPosition();
			BOARD_OBJECT CreatureObj = Creature->GetActorObject();
			DrawManager::DrawObjectAtPosition(CreaturePos, CreatureObj);
		}
	}
}

BOARD_OBJECT(&ArrowStorm::MakeSnapshot())[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH]
{
	static BOARD_OBJECT Snapshot[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH]{};

	for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH; ++x)
		{
			Snapshot[y][x] = m_Map.GetBoardObject(x, y);
		}
	}

	for (int index = 0; index < ArrowStorm::GetInstance().GetCreatureArr().size(); ++index)
	{
		if (ArrowStorm::GetInstance().GetCreatureArr()[index] == nullptr) continue;

		Position CreatruePos = ArrowStorm::GetInstance().GetCreatureArr()[index]->GetCurrentPosition();
		Snapshot[CreatruePos.m_y][CreatruePos.m_x] = BOARD_OBJECT::WALL;
	}

	return Snapshot;
}

void ArrowStorm::GenerateMonster()
{
	int NumOfMonsters = (rand() % 5) + 5; //최소 다섯마리
	for (int i = 0; i < NumOfMonsters; ++i)
	{
		int MonsterType = rand() % MONSTER_TYPE::COUNT;
		Position InitialPos = GetRandomePos();
		switch ((MONSTER_TYPE)MonsterType)
		{
		case MONSTER_TYPE::SLIME_TYPE:
			m_CreatureArr.push_back(std::make_unique<Slime>(InitialPos));
			break;
		case MONSTER_TYPE::SKELETON_TYPE:
			m_CreatureArr.push_back(std::make_unique<Skeleton>(InitialPos));
			break;
		default:
			break;
		}
	}
}

Position ArrowStorm::GetRandomePos()
{
	int temp_x;
	int temp_y;
	while (1)
	{
		temp_x = rand() % BOARD_SIZE::BOARD_WIDTH;
		temp_y = rand() % BOARD_SIZE::BOARD_HEIGHT;

		if (!m_Map.IsValidPos(Position(temp_x, temp_y))) continue;
		if (CreatureExistAtPos(Position(temp_x, temp_y))) continue;
		if (Position::Distance(Position(temp_x, temp_y), m_CreatureArr[0]->GetCurrentPosition()) < 5) continue;

		return Position(temp_x, temp_y);
	}

}

void ArrowStorm::MapChangeCheck(Position _Pos)
{
	if (m_CreatureArr[0] == nullptr) return;
	if (m_Map.GetBoardObject(_Pos.m_x, _Pos.m_y) != BOARD_OBJECT::DOOR)return;

	LoadNextMap(m_Map.GetBoard()[_Pos.m_y][_Pos.m_x] - 100);
}

void ArrowStorm::LoadNextMap(int _MapIndex)
{
	m_Map.SetCurMapIndex(_MapIndex);
	m_ProjectileList.clear();
	m_CreatureArr.resize(1);
	RelocatePlayer(m_CreatureArr[0]->GetCurrentPosition());
	GenerateMonster();
	DrawFullBoard();
}

void ArrowStorm::RelocatePlayer(Position _Pos)
{
	if (_Pos.m_x == 0)
	{
		_Pos.m_x = BOARD_SIZE::BOARD_WIDTH - 2;
	}
	else if (_Pos.m_x == BOARD_SIZE::BOARD_WIDTH - 1)
	{
		_Pos.m_x = 1;
	}
	else if (_Pos.m_y == 0)
	{
		_Pos.m_y = BOARD_SIZE::BOARD_HEIGHT - 2;
	}
	else if (_Pos.m_y == BOARD_SIZE::BOARD_HEIGHT - 1)
	{
		_Pos.m_y = 1;
	}

	m_CreatureArr[0]->SetCurrentPosition(_Pos);
}