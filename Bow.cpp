#include "Bow.h"
#include "Timer.h"
#include "ArrowStorm.h"
#include "Projectile.h"
#include "Creature.h"
#include <memory>

Bow::Bow(Creature* _Owner)
{
	m_Owner = _Owner;
	m_AttackTimer = std::make_unique<Timer>();
	m_AttackTimer->SetTimer(TIME::DEFAULT_ATTACK_COOL, std::bind(&Bow::TempCheck,this));
	m_SkillTimer = std::make_unique<Timer>();
	m_SkillTimer->SetTimer(TIME::DEFAULT_SKILL_COOL, std::bind(&Bow::UseSkill, this));
}

Bow::~Bow()
{
	
}


void Bow::TryFire(BOARD_OBJECT _Object, DIRECTION _MovingDir)
{
	if (m_AttackTimer->CheckTimer())
		SpawnProjectile(m_Owner->GetCurrentPosition() + Directions[_MovingDir], _Object, _MovingDir);
}

void Bow::Fire()
{

}


void Bow::SpawnProjectile(Position _InitialPos, BOARD_OBJECT _Object, DIRECTION _MovingDir)
{
	ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(_InitialPos, _Object, _MovingDir));	
}

void Bow::TrySkill()
{
	m_SkillTimer->CheckTimer();
}

void Bow::UseSkill()
{

}

