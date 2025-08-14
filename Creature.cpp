#include "Creature.h"
#include "MapManager.h"
#include "ArrowStorm.h"

Creature::Creature(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
	: Actor(_InitialPosition, _ActorObject)
{
}

Creature::~Creature()
{
}


void Creature::MoveTowards(const DIRECTION& _Direction)
{
	Position NextPosition = m_CurrentPosition + Directions[_Direction];
	if (!MapManager::IsValidPos(NextPosition) || ArrowStorm::CreatureExistAtPos(NextPosition)) return;
	Redraw(NextPosition);
}


void Creature::Tick()
{
	Actor::Tick();
}