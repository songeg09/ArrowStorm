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
	m_AttackTimer->SetTimer(TIME::DEFAULT_ATTACK_COOL, std::bind(&Bow::Fire,this,std::ref(m_AmingDir)));
	m_SkillTimer = std::make_unique<Timer>();
	m_SkillTimer->SetTimer(TIME::DEFAULT_SKILL_COOL, std::bind(&Bow::UseSkill, this));
}

Bow::~Bow()
{
	
}


void Bow::TryFire(const DIRECTION _AmingDir)
{
	m_AmingDir = _AmingDir;
	m_AttackTimer->CheckTimer();
}

void Bow::Fire(const DIRECTION _AmingDir)
{
	Position InitialPos = m_Owner->GetCurrentPosition() + Directions[_AmingDir];
	BOARD_OBJECT Object = GetArrowObject(_AmingDir);
	ArrowStorm::GetProjectileList().emplace_back(std::make_unique<Projectile>(InitialPos, Object, _AmingDir));
}

void Bow::TrySkill()
{
	m_SkillTimer->CheckTimer();
}

void Bow::UseSkill()
{
	Fire(DIRECTION::UP);
	Fire(DIRECTION::RIGHT);
	Fire(DIRECTION::DOWN);
	Fire(DIRECTION::LEFT);
}

BOARD_OBJECT Bow::GetArrowObject(const DIRECTION _AmingDir)
{
	switch (_AmingDir)
	{
	case DIRECTION::UP:
		return BOARD_OBJECT::ARROW_UP;
	case DIRECTION::RIGHT:
		return BOARD_OBJECT::ARROW_RIGHT;
	case DIRECTION::DOWN:
		return BOARD_OBJECT::ARROW_DOWN;
	case DIRECTION::LEFT:
		return BOARD_OBJECT::ARROW_LEFT;
	default:
		return BOARD_OBJECT::ARROW_UP;
	}
}
