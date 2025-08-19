#include "Creature.h"
#include "Map.h"
#include "ArrowStorm.h"

Creature::Creature(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
	: Actor(_InitialPosition, _ActorObject)
{
}

Creature::~Creature()
{
}

// 생명체는 다른 생명체를 통과해서 이동 불가
void Creature::MoveTowards(const DIRECTION& _Direction)
{
	Position NextPosition = m_CurrentPosition + Directions[_Direction];
	if (!ArrowStorm::GetInstance().GetMap().IsValidPos(NextPosition) || ArrowStorm::GetInstance().CreatureExistAtPos(NextPosition)) return;
	Redraw(NextPosition);
}

void Creature::TakeDamage(const int _Damage)
{
	m_Hp -= _Damage;
	if (m_Hp < 0)
		m_Hp = 0;
}
