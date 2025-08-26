#include "FastBow.h"
#include "Timer.h"

FastBow::FastBow(Creature* _Owner)
	: Bow(BOW_TYPE::FAST, _Owner)
{
	m_AttackTimer->ChangeSecond(FAST_ATTACK_COOL);
	m_SkillTimer->ChangeSecond(FAST_SKILL_COOL);
}

FastBow::~FastBow()
{

}