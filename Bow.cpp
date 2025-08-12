#include "Bow.h"
#include "Timer.h"
#include "ArrowStorm.h"
#include "Projectile.h"
#include <memory>

Bow::Bow(TIME _AttackSpeed)
{
	m_AttackTimer = std::make_unique<Timer>();
	m_AttackTimer->SetTimer(_AttackSpeed, std::bind(&Bow::TempCheck,this));
}

Bow::~Bow()
{
	
}


void Bow::TrySpawnProjectile(Position _InitialPos, BOARD_OBJECT _Object, DIRECTION _MovingDir)
{
	if (m_AttackTimer->CheckTimer())
		SpawnProjectile(_InitialPos, _Object, _MovingDir);
}

void Bow::SpawnProjectile(Position _InitialPos, BOARD_OBJECT _Object, DIRECTION _MovingDir)
{
	std::unique_ptr<Projectile> _Projectile = std::make_unique<Projectile>(_InitialPos, _Object, _MovingDir);
	ArrowStorm::GetInstance().RegisterProjectile(std::move(_Projectile));
}

