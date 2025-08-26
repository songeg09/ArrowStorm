#pragma once
#include "Actor.h"
#include "Timer.h"

class Projectile : public Actor
{
private:
	// 멤버 변수
	DIRECTION m_MovingDirection;
	int m_Damage;
	class Creature* m_Owner;

public:
	// 생성자 소멸자
	Projectile(Creature* m_Owner, const Position _InitialPosition, const BOARD_OBJECT _ActorObject, const DIRECTION _MovingDirection, int _Damage = DEFAULT_DAMAGE);
	virtual ~Projectile();

	// Getter & Setter
	int GetDamage() { return m_Damage; }
	Creature* GetOwner() { return m_Owner; }

	// Tick
	virtual void Tick() override;
};

