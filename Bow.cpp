#include "Bow.h"
#include "Timer.h"
#include "ArrowStorm.h"
#include "Projectile.h"
#include "Creature.h"
#include "Player.h"
#include "UIManager.h"

#include <memory>

Bow::Bow(Creature* _Owner)
{
	m_Name = "�⺻ Ȱ";
	m_Owner = _Owner;
	m_AttackTimer = std::make_unique<Timer>();
	m_AttackTimer->SetTimer(TIME::DEFAULT_ATTACK_COOL, std::bind(&Bow::Fire,this,std::ref(m_AmingDir)));
	m_SkillTimer = std::make_unique<Timer>();
	m_SkillTimer->SetTimer(TIME::DEFAULT_SKILL_COOL, std::bind(&Bow::UseSkill, this, std::ref(m_AmingDir)));
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

void Bow::TrySkill(const DIRECTION _AmingDir)
{
	m_AmingDir = _AmingDir;
	if (m_SkillTimer->CheckTimer())
	{
		if (Player* player = dynamic_cast<Player*>(m_Owner))
			player->UseMp();
	}
}

void Bow::UseSkill(const DIRECTION _AmingDir)
{
	Fire(DIRECTION::UP);
	Fire(DIRECTION::RIGHT);
	Fire(DIRECTION::DOWN);
	Fire(DIRECTION::LEFT);	
}
