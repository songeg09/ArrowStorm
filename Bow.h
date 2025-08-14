#pragma once
#include "Mecro.h"

class Bow
{
protected:
	class Creature* m_Owner;
	int m_Damage;
	DIRECTION m_AmingDir;
	std::unique_ptr<class Timer> m_AttackTimer;
	std::unique_ptr<class Timer> m_SkillTimer;
	
	BOARD_OBJECT GetArrowObject(const DIRECTION _AmingDir);
	void Fire(const DIRECTION _AmingDir);
	void UseSkill();

public:
	Bow(Creature* _Owner);
	virtual ~Bow();

	void TryFire(const DIRECTION _AmingDir);
	void TrySkill();
};

