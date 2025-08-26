#include "ArrowStorm.h"

#include "TriBow.h"
#include "Creature.h"
#include "Projectile.h"

TriBow::TriBow(Creature* _Owner)
	: Bow(BOW_TYPE::TRIPLE, _Owner)
{

}

TriBow::~TriBow()
{

}

void TriBow::UseSkill(const DIRECTION _AmingDir)
{
	Position InitialPos = m_Owner->GetCurrentPosition() + Directions[_AmingDir];
	BOARD_OBJECT Object = GetArrowObject(_AmingDir);
	if (_AmingDir == DIRECTION::DOWN || _AmingDir == DIRECTION::UP)
	{
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(m_Owner,InitialPos, Object, _AmingDir));
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(m_Owner, InitialPos + Position(1, 0), Object, _AmingDir));
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(m_Owner, InitialPos + Position(-1, 0), Object, _AmingDir));
	}
	else
	{
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(m_Owner, InitialPos, Object, _AmingDir));
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(m_Owner, InitialPos + Position(0, 1), Object, _AmingDir));
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(m_Owner, InitialPos + Position(0, -1), Object, _AmingDir));
	}
}