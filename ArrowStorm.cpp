#include "ArrowStorm.h"
#include "DrawManager.h"
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

void ArrowStorm::Init()
{
	// �ʱ�ȭ
	m_CreatureArr.clear();
	m_ProjectileList.clear();

	m_CreatureArr.push_back(std::make_unique<Player>(Position(BOARD_SIZE::BOARD_WIDTH / 2, BOARD_SIZE::BOARD_HEIGHT / 2), BOARD_OBJECT::PLAYER_UP));
}

void ArrowStorm::NewGame()
{
	Init();
	m_Map.LoadMap("Map_Start");
}

bool ArrowStorm::LoadGame()
{
	Init();

	std::fstream load("Save.txt");
	if (!load.is_open()) return false;

	LoadPlayer(load);
	return true;
}

void ArrowStorm::LoadPlayer(std::fstream& load)
{
	std::string tmpStr;
	int tmp1, tmp2;
	
	if (Player* player = dynamic_cast<Player*>(m_CreatureArr[0].get()))
	{
		// �� �ε�
		load >> tmpStr;
		m_Map.LoadMap(tmpStr);

		// �÷��̾� ��ġ ����
		load >> tmp1 >> tmp2;
		player->SetCurrentPosition(Position(tmp1, tmp2));

		// Ȱ �ε� *****
		load >> tmpStr;

		// Hp �� Mp �ε�
		load >> tmp1 >> tmp2;
		player->SetHp(tmp1);
		player->SetMp(tmp2);

		// ���� �� �ε�
		load >> tmp1 >> tmp2;
		player->SetHpPotion(tmp1);
		player->SetMpPotion(tmp2);
	}

	load.close();
}

void ArrowStorm::SaveGame()
{
	std::ofstream save("Save.txt", std::ios::trunc);

	if (Player* player = dynamic_cast<Player*>(m_CreatureArr[0].get()))
	{
		// �� �̸� ����
		save << m_Map.GetName() << std::endl;
		// ��ġ ����
		save << player->GetCurrentPosition().m_x << " " << player->GetCurrentPosition().m_y << std::endl;;
		// Ȱ �̸� ����
		save << player->GetBow()->GetName() << std::endl;
		// Hp �� Mp ����
		save << player->GetHp() << " " << player->GetMp() << std::endl;
		// ���� �� ����
		save << player->GetHpPotion() << " " << player->GetMpPotion() << std::endl;;
	}

	save.close();

	if (DrawManager::DrawConfirmPopup("������ �Ϸ��Ͽ����ϴ�. ������ �����Ͻðڽ��ϱ�?"))
		return;

	DrawFullBoard();
}

void ArrowStorm::Initialize()
{
	GenerateMonster();
	DrawFullBoard();
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
		MapChangeCheck();

		if (IsGameOver())
		{
			DrawManager::DrawInfoPopup("Game Over!");
			return;
		}
	}
}

void ArrowStorm::Tick()
{
	// �÷��̾� ƽ
	m_CreatureArr[0]->Tick();

	// ���� ƽ
	for (int i = 1; i < m_CreatureArr.size(); ++i)
	{
		if (m_CreatureArr[i] == nullptr) continue;

		m_CreatureArr[i]->Tick();
	}

	// ����ü ƽ
	for (std::list<std::unique_ptr<Projectile>>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end(); it++)
	{
		(*it)->Tick();
	}
}

//Ȱ �浹 Ȯ�� �� ������ ����
void ArrowStorm::CollisionCheck()
{
	for (std::list<std::unique_ptr<Projectile>>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end();)
	{
		Position CurrentPos = (*it)->GetCurrentPosition();

		// 1. ���� �� or ���� �浹
		if (!m_Map.InRange(CurrentPos) || m_Map.GetBoard()[CurrentPos.m_y][CurrentPos.m_x] == BOARD_OBJECT::WALL)
		{
			RemoveProjectile(it);
		}
		else
		{
			// 2. ũ���Ŀ� �¾��� ���
			int HitIndex = DidHit((*it));
			if (HitIndex != -1)
			{
				// ������ ����
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

// ȭ���� ũ���ĸ� ���߾��� ���,
// �ش� ũ������ �ε����� ��ȯ
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

// ������ ����� ���׷��ֱ�
void ArrowStorm::ApplyHit(const int& _Index, const int _Damage)
{
	m_CreatureArr[_Index]->TakeDamage(_Damage);
	Position CurrentPos = m_CreatureArr[_Index]->GetCurrentPosition();
	m_CreatureArr[_Index]->Render();
}

// ����Ʈ���� ����ü ������ ���׸���
void ArrowStorm::RemoveProjectile(std::list<std::unique_ptr<Projectile>>::iterator& it)
{
	Position CurrentPos = (*it)->GetCurrentPosition();
	DrawManager::DrawObjectAtPosition(CurrentPos, m_Map.GetBoard()[CurrentPos.m_y][CurrentPos.m_x]);
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
			DrawManager::DrawObjectAtPosition(CurrentPos, m_Map.GetBoard()[CurrentPos.m_y][CurrentPos.m_x]);
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
			if (m_Map.GetBoard()[Pos.m_y][Pos.m_x] == BOARD_OBJECT::CHEST)
			{
				int Type = rand() % 2;
				player->EarnPotion((POTION_TYPE)Type);
				m_Map.GetBoard()[Pos.m_y][Pos.m_x] = BOARD_OBJECT::EMPTY;
			}
			else if (m_Map.GetBoard()[Pos.m_y][Pos.m_x] == BOARD_OBJECT::BOW)
			{
				
				BowChange(player);

				m_Map.GetBoard()[Pos.m_y][Pos.m_x] = BOARD_OBJECT::EMPTY;
			}
		}
	}
}

void ArrowStorm::BowChange(Player* player)
{
	// Random Bow ������ ����?
	std::unique_ptr<Bow> TempBow = std::make_unique<TriBow>(player);
	std::string Msg = player->GetBow()->GetName() + " -> " + TempBow->GetName();
	if (DrawManager::DrawConfirmPopup(Msg))
	{
		player->SetBow(std::move(TempBow));
	}
	// ȭ�� �ٽ� �׸���
	DrawFullBoard();
}

void ArrowStorm::DrawFullBoard()
{
	m_Map.DrawBoard();
	
	// ����ü �׸���
	for (std::list<std::unique_ptr<Projectile>>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end(); ++it)
	{
		Position CreaturePos = (*it)->GetCurrentPosition();
		BOARD_OBJECT CreatureObj = (*it)->GetActorObject();
		DrawManager::DrawObjectAtPosition(CreaturePos, CreatureObj);
	}

	// ũ���ĵ� �׸���
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

	std::memcpy(Snapshot, m_Map.GetBoard(),
		sizeof(BOARD_OBJECT)* BOARD_SIZE::BOARD_HEIGHT* BOARD_SIZE::BOARD_WIDTH);

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
	int NumOfMonsters = (rand() % 5) + 5; //�ּ� �ټ�����

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

void ArrowStorm::MapChangeCheck()
{
	if (m_CreatureArr[0] == nullptr) return;
	
	Position Pos = m_CreatureArr[0]->GetCurrentPosition();
	if (m_Map.GetBoard()[Pos.m_y][Pos.m_x] != BOARD_OBJECT::DOOR)return;

	for (Door& Door : m_Map.GetDoors())
	{
		if (Door.m_Name == "X") continue;
		if (Door.m_Position != Pos) continue;

		LoadNextMap(Door);
		return;
	}
}

void ArrowStorm::LoadNextMap(Door _Door)
{
	m_Map.LoadMap(_Door.m_Name);
	m_ProjectileList.clear();
	m_CreatureArr.resize(1);
	RelocatePlayer(_Door.m_Position);
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