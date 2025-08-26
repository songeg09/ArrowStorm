#include "Skeleton.h"
#include "Timer.h"
#include "Bow.h"

Skeleton::Skeleton(const Position _InitialPos)
	:Monster(_InitialPos, BOARD_OBJECT::SKELETON)
{
	m_Hp = SKELETON_HP;
	m_MoveTimer->SetTimer(TIME::SKELETON_MOVE_SPEED, std::bind(&Skeleton::Wander, this));
	m_AttackTimer->SetTimer(TIME::SKELETON_ATTACK_COOL, std::bind(&Skeleton::MeleeAttack, this));
	m_MeleeDamage = SKELETON_MELEE_DAMAGE;
	m_Bow = std::make_unique<Bow>();
	m_Bow->SetOwner(this);
	m_Exp = MONSTER_EXP::SKELETON_EXP;
}

Skeleton::~Skeleton()
{

}

void Skeleton::Tick()
{
	int Distance = Position::Distance(m_Target->GetCurrentPosition(), m_CurrentPosition);
	if (Distance <= 1)
	{
		// 근접 공격 시도
		TryAttack();
	}
	else if (IsAligned())
	{
		// 거리가 멀 경우 화살 발사
		m_Bow->TryFire(Position::GetDirection(m_CurrentPosition, m_Target->GetCurrentPosition()));
	}
	else
	{
		// 플레이어를 탐지 하지 못했을경우 패트롤
		TryMove();
	}
}


void Skeleton::Wander()
{
	int RandomDir = rand() % 4;
	MoveTowards((DIRECTION)RandomDir);
}

bool Skeleton::IsAligned()
{
	Position TargetPos = m_Target->GetCurrentPosition();
	return TargetPos.m_x == m_CurrentPosition.m_x || TargetPos.m_y == m_CurrentPosition.m_y;
}


