#pragma once
#include "Mecro.h"

class Actor
{
public:
	Actor(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Actor();

protected:
	Position m_CurrentPosition;
	BOARD_OBJECT m_ActorObject;
	std::unique_ptr<class Timer> m_MoveTimer;

	// 이동 및 다시 그리기
	virtual void TryMove() = 0;
	virtual void MoveTowards(const DIRECTION& _Direction);
	void Redraw(Position& _NewPosition);

public:
	Position GetCurrentPosition() { return m_CurrentPosition; }
	void SetCurrentPosition(const Position& _NextPosition) { m_CurrentPosition = _NextPosition; }
	BOARD_OBJECT GetActorObject() { return m_ActorObject; }
	
	virtual void Tick() = 0;
	
};

