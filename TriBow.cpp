#include "ArrowStorm.h"

#include "TriBow.h"
#include "Creature.h"
#include "Projectile.h"

TriBow::TriBow()
	: Bow()
{
	m_Name = "Triple_Bow";
}

TriBow::TriBow(class Creature* _Owner)
	:Bow(_Owner)
{
	m_Name = "Triple_Bow";
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
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(InitialPos, Object, _AmingDir));
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(InitialPos + Position(1, 0), Object, _AmingDir));
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(InitialPos + Position(-1, 0), Object, _AmingDir));
	}
	else
	{
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(InitialPos, Object, _AmingDir));
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(InitialPos + Position(0, 1), Object, _AmingDir));
		ArrowStorm::GetInstance().GetProjectileList().emplace_back(std::make_unique<Projectile>(InitialPos + Position(0, -1), Object, _AmingDir));
	}
}