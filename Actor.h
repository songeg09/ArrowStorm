#pragma once
#include "Mecro.h"

class Actor
{
protected:
	// ��� ����
	Position m_CurrentPosition;
	BOARD_OBJECT m_ActorObject;
	std::unique_ptr<class Timer> m_MoveTimer;

	// �̵� �� �ٽ� �׸���
	virtual void TryMove();
	virtual void MoveTowards(const DIRECTION& _Direction);
	void Redraw(Position& _NewPosition);

public:
	// ������ �Ҹ���
	Actor(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Actor();

	// Getter & Setter
	Position GetCurrentPosition() { return m_CurrentPosition; }
	void SetCurrentPosition(const Position& _NextPosition) { m_CurrentPosition = _NextPosition; }
	BOARD_OBJECT GetActorObject() { return m_ActorObject; }

	// Tick
	virtual void Tick() = 0;

	// Render
	void Render();

};

