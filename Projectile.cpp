#include "Projectile.h"

Projectile::Projectile(const Position _InitialPosition, const BOARD_OBJECT _ActorObject, const DIRECTION _MovingDirection, const DAMAGE _Damage):
	Actor(_InitialPosition, _ActorObject)
{
	m_MovingDirection = _MovingDirection;
	m_Damage = _Damage;
	m_MoveTimer->SetTimer(TIME::DEFAULT_PROJECTILE_SPEED, std::bind(&Projectile::TryMoveTowards, this, m_MovingDirection));
}

Projectile::Projectile(FireRequest _Request, DAMAGE _Damage)
	:Actor(_Request.m_InitialPosition, _Request.m_Object)
{
	m_MovingDirection = _Request.m_MovingDirection;
	m_Damage = _Damage;
	m_MoveTimer->SetTimer(TIME::DEFAULT_PROJECTILE_SPEED, std::bind(&Projectile::TryMoveTowards, this, m_MovingDirection));
}

Projectile::~Projectile()
{

}

Position Projectile::TryMove()
{
	return m_MoveTimer->CheckTimer();
}