#pragma once
#include "Actor.h"
class Creature abstract : public Actor
{
protected:
	// 멤버 변수
	int m_Hp; // 각 몬스터별로 고유 값 존재
	int m_RangedDamage;

	// 이동
	void MoveTowards(const DIRECTION& _Direction) override;

public:
	// 생성자 소멸자
	Creature(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Creature();

	// Getter & Setter
	int GetHp() { return m_Hp; }
	void SetHp(int _Hp) { m_Hp = _Hp; }
	virtual void TakeDamage(const int _Damage);
	int GetRangedDamage() { return m_RangedDamage; }
	
};

