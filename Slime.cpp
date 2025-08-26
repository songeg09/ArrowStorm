#include "Slime.h"
#include "Timer.h"

Slime::Slime(const Position _InitialPos)
	:Monster(_InitialPos, BOARD_OBJECT::SLIME)
{
	m_Hp = SLIME_HP;
	m_MoveTimer->SetTimer(TIME::SLIME_MOVE_SPEED, std::bind(&Slime::FollowTarget, this));
	m_AttackTimer->SetTimer(TIME::SLIME_ATTACK_COOL, std::bind(&Slime::MeleeAttack, this));
	m_MeleeDamage = DEFAULT_DAMAGE;
	m_Exp = MONSTER_EXP::SLIME_EXP;
}

Slime::~Slime()
{

}

void Slime::Tick()
{
	if (Position::Distance(m_Target->GetCurrentPosition(), m_CurrentPosition) > 1)
	{
		TryMove();
	}
	else
	{
		TryAttack();
	}
}

