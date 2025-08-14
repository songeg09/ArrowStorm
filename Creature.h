#pragma once
#include "Actor.h"
class Creature : public Actor
{
public:
	Creature(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Creature();

	virtual void Tick() override;

	int GetHp() { return m_Hp; }
	void TakeDamage(const int _Damage)
	{
		m_Hp -= _Damage;
		if (m_Hp < 0)
			m_Hp = 0;
	}

protected:
	void MoveTowards(const DIRECTION& _Direction) override;
	bool IsValidPos(const Position& NewPosition);

	int m_Hp = 30;// юс╫ц
	
};

