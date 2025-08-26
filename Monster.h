#pragma once
#include "Creature.h"

class Monster : public Creature
{
protected:
	// 멤버 변수
	Creature* m_Target;
	std::unique_ptr<class Timer> m_AttackTimer;
	int m_MeleeDamage;
	int m_Exp;

	// 공격
	void TryAttack();
	void MeleeAttack();

	// 이동
	void FollowTarget();
	Position GetNextPosition();

public:
	// 생성자 소멸자
	Monster(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Monster();

	// Getter & Setter
	int GetExp() { return m_Exp; }
};

