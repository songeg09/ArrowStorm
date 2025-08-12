#pragma once
#include "Actor.h"
class Creature : public Actor
{
public:
	Creature(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Creature();

	virtual void Tick() override;

protected:
	void MoveTowards(const DIRECTION& _Direction) override;
	bool IsValidPos(const Position& NewPosition);
};

