#include "Monster.h"
#include "ArrowStorm.h"

Monster::Monster(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
	:Creature(_InitialPosition, _ActorObject)
{
	m_Target = ArrowStorm::GetCreatureArr()[0].get();
}

Monster::~Monster()
{

}