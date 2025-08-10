#include "Actor.h"

Actor::Actor(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
{
	m_CurrentPosition = _InitialPosition;
	m_ActorObject = _ActorObject;
	m_MoveTimer = std::make_unique<Timer<Position>>();
}

Actor::~Actor() 
{

}

Position Actor::TryMoveTowards(const DIRECTION& _Direction)
{
	return m_CurrentPosition + Directions[_Direction];
}