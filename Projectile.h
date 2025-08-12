#pragma once
#include "Actor.h"
#include "Timer.h"



class Projectile : public Actor
{
private:
	DIRECTION m_MovingDirection;
	int m_Damage;

	void TryMove() override;

public:
	Projectile(const Position _InitialPosition, const BOARD_OBJECT _ActorObject, const DIRECTION _MovingDirection, int _Damage = DEFAULT_DAMAGE);	
	Projectile(FireRequest _Request, int _Damage = DEFAULT_DAMAGE);
	~Projectile();

	int GetDamage() { return m_Damage; }

	virtual void Tick() override;
};

