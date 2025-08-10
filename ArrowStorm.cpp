#include "ArrowStorm.h"
#include "DrawManager.h"
#include "Projectile.h"
#include "Player.h"
#include "Actor.h"

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
	// 벽 그리기
	std::string Line;
	for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
	{
		DrawManager::gotoxy(0, y);
		for (int x = 0; x < BOARD_SIZE::BOARD_WIDHT * 2; ++x)
		{
			Line += DrawManager::GetObjectIcon(m_Board[y][x].m_Type);
		}
		std::cout << Line;
	}
	// 아이템 상자 및 출입구 그리기

	// 생명체들 그리기
	m_CreatureArr.resize(1);
	m_CreatureArr[0] = std::make_unique<Player>();
	for (int id = 0; id < m_CreatureArr.size(); ++id)
	{
		if (m_CreatureArr[id])
		{
			Position CreaturePos = m_CreatureArr[id]->GetCurrentPosition();
			BOARD_OBJECT CreatureObj = m_CreatureArr[id]->GetActorObject();
			m_Board[CreaturePos.m_y][CreaturePos.m_x] = Cell(CreatureObj, id);
			DrawManager::DrawObjectAtLocation(CreaturePos, CreatureObj);
		}
	}
}

void ArrowStorm::Run()
{
	Initialize();
	
	while (1)
	{
		HandleAllCreatureMoveRequests();

		HandleAllProjectileMoveRequests();
	}
}


void ArrowStorm::HandleAllCreatureMoveRequests()
{
	for (int id = 0; id < m_CreatureArr.size(); ++id)
	{
		HandleCretureMoveRequest(m_CreatureArr[id], id);
	}
}

void ArrowStorm::HandleCretureMoveRequest(std::unique_ptr<class Creature>& _Creature, const int _Id)
{
	if (_Id == 0)
		HandlePlayerTurnRequest();
		HandlePlayerFireRequest();

	Position NewPosition = _Creature->TryMove();
		if (IsMovableTile(NewPosition))
			ApplyCreatureMoveAndRedraw(_Creature, NewPosition, _Id);
}


void ArrowStorm::HandlePlayerTurnRequest()
{
	if (Player* _PlayerPtr = (Player*)(m_CreatureArr[0].get()))
	{
		DIRECTION NewFacingDirection = _PlayerPtr->TryTurn();
		if (NewFacingDirection == DIRECTION::NEUTRAL) return;
		
		_PlayerPtr->SetFacingDir(NewFacingDirection);
		Position CurrentPosition = _PlayerPtr->GetCurrentPosition();
		m_Board[CurrentPosition.m_y][CurrentPosition.m_x] = _PlayerPtr->GetActorObject();
		DrawManager::DrawObjectAtLocation(CurrentPosition, _PlayerPtr->GetActorObject());
	}
}

void ArrowStorm::HandlePlayerFireRequest()
{
	if (Player* _PlayerPtr = (Player*)(m_CreatureArr[0].get()))
	{
		FireRequest FireRequest = _PlayerPtr->TryFire();
		if (FireRequest.m_MovingDirection == DIRECTION::NEUTRAL) return;

		m_ProjectileList.push_back(std::make_unique<Projectile>(FireRequest));
	}
}

void ArrowStorm::ApplyCreatureMoveAndRedraw(std::unique_ptr<class Creature>& _Creature, const Position& _NewPosition, const int _Id)
{
	// 기존 위치 지우기
	Position OriginalPosition = _Creature->GetCurrentPosition();
	m_Board[OriginalPosition.m_y][OriginalPosition.m_x] = Cell();
	DrawManager::DrawObjectAtLocation(OriginalPosition, BOARD_OBJECT::EMPTY);

	// 새로운 위치에 그리기
	_Creature->SetCurrentPosition(_NewPosition);
	m_Board[_NewPosition.m_y][_NewPosition.m_x] = Cell(_Creature->GetActorObject(), _Id);
	DrawManager::DrawObjectAtLocation(_NewPosition, _Creature->GetActorObject());
}


void ArrowStorm::HandleAllProjectileMoveRequests()
{
	for (auto& Projectile : m_ProjectileList)
	{
		ApplyProjectileMoveAndRedraw(Projectile);
	}
}

void ArrowStorm::ApplyProjectileMoveAndRedraw(std::unique_ptr<class Projectile>& _Projectile)
{
	Position NewPosition = _Projectile->TryMove();
	if (IsMovableTile(NewPosition))
		ApplyProjectileMoveAndRedraw(_Projectile, NewPosition);
}

void ArrowStorm::ApplyProjectileMoveAndRedraw(std::unique_ptr<class Projectile>& _Projectile, const Position& _NewPosition)
{
	// 기존 위치 지우기
	Position OriginalPosition = _Projectile->GetCurrentPosition();
	DrawManager::DrawObjectAtLocation(OriginalPosition, BOARD_OBJECT::EMPTY);

	// 새로운 위치에 그리기
	_Projectile->SetCurrentPosition(_NewPosition);
	DrawManager::DrawObjectAtLocation(_NewPosition, _Projectile->GetActorObject());
}







///*
//	이동 못하는 경우
//	1. 맵 범위 밖
//	2. m_Board[y][x]가 EMPTY이지 않은경우
//*/
bool ArrowStorm::IsMovableTile(const Position& _Position)
{
	if (!InRange(_Position))
		return false;
	if (m_Board[_Position.m_y][_Position.m_x].m_Type != BOARD_OBJECT::EMPTY)
		return false;
	return true;
}

bool ArrowStorm::InRange(const Position& _Position)
{
	return (0 <= _Position.m_x && _Position.m_x < BOARD_SIZE::BOARD_WIDHT
		&& 0 <= _Position.m_y && _Position.m_y < BOARD_SIZE::BOARD_HEIGHT);
}

