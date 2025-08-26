#pragma once
#include "Creature.h"

class Monster : public Creature
{
protected:
	// ��� ����
	Creature* m_Target;
	std::unique_ptr<class Timer> m_AttackTimer;
	int m_MeleeDamage;
	int m_Exp;

	// ����
	void TryAttack();
	void MeleeAttack();

	// �̵�
	void FollowTarget();
	Position GetNextPosition();

public:
	// ������ �Ҹ���
	Monster(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Monster();

	// Getter & Setter
	int GetExp() { return m_Exp; }
};

