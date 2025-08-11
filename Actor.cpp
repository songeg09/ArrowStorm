#include "Actor.h"
#include "DrawManager.h"
#include "MapManager.h"

Actor::Actor(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
{
	m_CurrentPosition = _InitialPosition;
	m_ActorObject = _ActorObject;
	m_MoveTimer = std::make_unique<Timer<void>>();
}

Actor::~Actor() 
{

}

void Actor::MoveTowards(const DIRECTION& _Direction)
{
	Position NewPosition = m_CurrentPosition + Directions[_Direction];
	ApplyNewPosAndRedraw(NewPosition);
}

void Actor::ApplyNewPosAndRedraw(Position& _NewPosition)
{
	DrawManager::DrawObjectAtPosition(
		m_CurrentPosition, 
		MapManager::GetInstance().GetBoard()[m_CurrentPosition.m_y][m_CurrentPosition.m_x]
	);
	m_CurrentPosition = _NewPosition;
	DrawManager::DrawObjectAtPosition(m_CurrentPosition, m_ActorObject);
}
