#include "Actor.h"
#include "DrawManager.h"
#include "ArrowStorm.h"
#include "Map.h"
#include "Timer.h"

Actor::Actor(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
{
	m_CurrentPosition = _InitialPosition;
	m_ActorObject = _ActorObject;
	m_MoveTimer = std::make_unique<Timer>();
}

Actor::~Actor() 
{

}

void Actor::MoveTowards(const DIRECTION& _Direction)
{
	Position NewPosition = m_CurrentPosition + Directions[_Direction];
	Redraw(NewPosition);
}

void Actor::Redraw(Position& _NewPosition)
{
	DrawManager::DrawObjectAtPosition(
		m_CurrentPosition,
		ArrowStorm::GetInstance().GetMap().GetBoardObject(m_CurrentPosition.m_x, m_CurrentPosition.m_y)
	);
	m_CurrentPosition = _NewPosition;
	Render();
}

void Actor::TryMove()
{
	m_MoveTimer->CheckTimer();
}

// 자기 자신의 정보를 렌더
void Actor::Render()
{
	DrawManager::DrawObjectAtPosition(m_CurrentPosition, m_ActorObject);
}

