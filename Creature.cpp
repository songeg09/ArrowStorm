#include "Creature.h"

Creature::Creature(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
	: Actor(_InitialPosition, _ActorObject)
{
}

Creature::~Creature()
{
}

void Creature::MoveTowards(const DIRECTION& _Direction)
{
	Position NextPosition = m_CurrentPosition + _Direction;
	if (IsValidPos(NextPosition))
		ApplyNewPosAndRedraw(NextPosition);
}

bool Creature::IsValidPos(const Position& NewPosition)
{
	return true;
}