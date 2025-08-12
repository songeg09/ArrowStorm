#pragma once
#include "Mecro.h"

class Bow
{
protected:
	class Creature* m_Owner;
	int m_Damage;
	std::unique_ptr<class Timer> m_AttackTimer;
	std::unique_ptr<class Timer> m_SkillTimer;
	
	void SpawnProjectile(Position _InitialPos, BOARD_OBJECT _Object, DIRECTION _FacingDir);
	void TempCheck() {}
	
public:
	Bow(Creature* _Owner);
	~Bow();

	void TryFire(BOARD_OBJECT _Object, DIRECTION _FacingDir);
	void Fire();

	void TrySkill();
	void UseSkill();
	
};

