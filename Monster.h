#pragma once
#include "Creature.h"

class Monster : public Creature
{
public:
	Monster(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Monster();

protected:
	Creature* m_Target;
	std::unique_ptr<class Timer> m_AttackTimer;
	int m_MeleeDamage;

	void TryAttack();
	void MeleeAttack();
};

