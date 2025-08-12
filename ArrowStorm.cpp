#include "ArrowStorm.h"
#include "DrawManager.h"
#include "Projectile.h"
#include "Player.h"
#include "Actor.h"
#include "Projectile.h"

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
	
}

bool ArrowStorm::LoadGame()
{
	return false;
}

void ArrowStorm::Initialize()
{

	// �� �׸���
	std::string Line;
	for (int y = 0; y < BOARD_SIZE::BOARD_HEIGTH; ++y)
	{
		DrawManager::gotoxy(0, y);
		for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH * 2; ++x)
		{
			//Line += DrawManager::GetObjectIcon(m_Board[y][x].m_Type);
			Line += " ";
		}
		std::cout << Line;
	}
	// ������ ���� �� ���Ա� �׸���

	// �÷��̾� ����
	m_Player = std::make_unique<Player>(
		Position(BOARD_SIZE::BOARD_WIDTH / 2, BOARD_SIZE::BOARD_HEIGTH / 2),
		BOARD_OBJECT::PLAYER_UP
	);

	DrawManager::DrawObjectAtPosition(m_Player->GetCurrentPosition(), m_Player->GetActorObject());

	// ����ü�� �׸���
	/*m_CreatureArr.resize(1);
	m_CreatureArr[0] = std::make_unique<Player>();
	for (int id = 0; id < m_CreatureArr.size(); ++id)
	{
		if (m_CreatureArr[id])
		{
			Position CreaturePos = m_CreatureArr[id]->GetCurrentPosition();
			BOARD_OBJECT CreatureObj = m_CreatureArr[id]->GetActorObject();
			DrawManager::DrawObjectAtPosition(CreaturePos, CreatureObj);
		}
	}*/
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
	// �÷��̾� ƽ
	m_Player->Tick();

	// ���� ƽ
	for (int i = 0; i < m_CreatureArr.size(); ++i)
	{
		if (m_CreatureArr[i] == nullptr) continue;

		m_CreatureArr[i]->Tick();
		// Attack?
	}

	// ����ü ƽ
	for (auto& Projectile : m_ProjectileList)
	{
		Projectile->Tick();
	}
}

void ArrowStorm::CollisionCheck()
{
	for (std::list<std::unique_ptr<Projectile>>::iterator it = m_ProjectileList.begin(); it != m_ProjectileList.end();)
	{
		if (!InRange((*it)->GetCurrentPosition()))
		{
			it = m_ProjectileList.erase(it);
		}
		else
		{
			it++;
		}
	}
}


void ArrowStorm::RegisterProjectile(std::unique_ptr<Projectile> _Projectile)
{
	m_ProjectileList.emplace_back(std::move(_Projectile));
}

///*
//	�̵� ���ϴ� ���
//	1. �� ���� ��
//	2. m_Board[y][x]�� EMPTY���� �������
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
		&& 0 <= _Position.m_y && _Position.m_y < BOARD_SIZE::BOARD_HEIGTH);
}

