#pragma once
#include "Mecro.h"
#include "Timer.h"

class Actor
{
public:
	Actor(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Actor();

protected:
	Position m_CurrentPosition;
	BOARD_OBJECT m_ActorObject;
	std::unique_ptr<Timer<Position>> m_MoveTimer;

public:
	Position GetCurrentPosition() { return m_CurrentPosition; }
	void SetCurrentPosition(const Position& _NextPosition) { m_CurrentPosition = _NextPosition; }
	BOARD_OBJECT GetActorObject() { return m_ActorObject; }
	
	virtual Position TryMove() = 0;
	Position TryMoveTowards(const DIRECTION& _Direction);
};

