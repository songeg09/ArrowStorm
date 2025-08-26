#include "Projectile.h"
#include "Timer.h"
#include "Creature.h"

Projectile::Projectile(Creature* _Owner, const Position _InitialPosition, const BOARD_OBJECT _ActorObject, const DIRECTION _MovingDirection, const int _Damage):
	Actor(_InitialPosition, _ActorObject)
{
	m_Owner = _Owner;
	m_MovingDirection = _MovingDirection;
	m_Damage = _Damage;
	m_MoveTimer->SetTimer(TIME::DEFAULT_PROJECTILE_SPEED, std::bind(&Projectile::MoveTowards, this, m_MovingDirection));
}

Projectile::~Projectile()
{

}

void Projectile::Tick()
{
	TryMove();
}