#pragma once
#include "Mecro.h"

class Bow
{
private:
	
	DAMAGE m_Damage;
	std::unique_ptr<class Timer> m_AttackTimer;
	
	void SpawnProjectile(Position _InitialPos, BOARD_OBJECT _Object, DIRECTION _FacingDir);
	void TempCheck() {}
	
public:
	Bow(TIME _AttackSpeed = TIME::DEFAULT_ATTACK_SPEED);
	~Bow();

	void TrySpawnProjectile(Position _InitialPos, BOARD_OBJECT _Object, DIRECTION _FacingDir);
	
};

