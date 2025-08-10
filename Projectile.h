#pragma once
#include "Actor.h"
#include "Timer.h"

enum DAMAGE
{
	DEFAULT_DAMAGE = 10,
};

class Projectile : public Actor
{
private:
	DIRECTION m_MovingDirection;
	DAMAGE m_Damage;

public:
	Projectile(const Position _InitialPosition, const BOARD_OBJECT _ActorObject, const DIRECTION _MovingDirection, DAMAGE _Damage = DEFAULT_DAMAGE);	
	Projectile(FireRequest _Request, DAMAGE _Damage = DEFAULT_DAMAGE);
	~Projectile();

	Position TryMove() override;

};

