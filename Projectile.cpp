#include "Projectile.h"
#include "Timer.h"

Projectile::Projectile(const Position _InitialPosition, const BOARD_OBJECT _ActorObject, const DIRECTION _MovingDirection, const int _Damage):
	Actor(_InitialPosition, _ActorObject)
{
	m_MovingDirection = _MovingDirection;
	m_Damage = _Damage;
	m_MoveTimer->SetTimer(TIME::DEFAULT_PROJECTILE_SPEED, std::bind(&Projectile::MoveTowards, this, m_MovingDirection));
}

Projectile::Projectile(FireRequest _Request, int _Damage)
	:Actor(_Request.m_InitialPosition, _Request.m_Object)
{
	m_MovingDirection = _Request.m_MovingDirection;
	m_Damage = _Damage;
	m_MoveTimer->SetTimer(TIME::DEFAULT_PROJECTILE_SPEED, std::bind(&Projectile::MoveTowards, this, m_MovingDirection));
}

Projectile::~Projectile()
{

}

void Projectile::TryMove()
{
	m_MoveTimer->CheckTimer();
}

void Projectile::Tick()
{
	Actor::Tick();
}