#include "Monster.h"
#include "ArrowStorm.h"
#include "Timer.h"

Monster::Monster(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
	:Creature(_InitialPosition, _ActorObject)
{
	m_Target = ArrowStorm::GetCreatureArr()[0].get();
	m_AttackTimer = std::make_unique<Timer>();
}

Monster::~Monster()
{

}

void Monster::TryAttack()
{
	m_AttackTimer->CheckTimer();
}

void Monster::MeleeAttack()
{
	if (m_Target)
	{
		m_Target->TakeDamage(m_MeleeDamage);
	}
}