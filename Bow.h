#pragma once
#include "Mecro.h"

class Bow
{
protected:
	// 멤버 변수
	class Creature* m_Owner;
	int m_Damage;
	DIRECTION m_AmingDir;
	std::unique_ptr<class Timer> m_AttackTimer;
	std::unique_ptr<class Timer> m_SkillTimer;
	const BOW_TYPE m_BowType;

	// 공격 함수
	void Fire(const DIRECTION _AmingDir);
	virtual void UseSkill(const DIRECTION _AmingDir);

public:
	// 생성자 소멸자
	Bow(BOW_TYPE _BowType = BOW_TYPE::BASIC, Creature* _Owner = nullptr);
	virtual ~Bow();
	
	// 발사 관련 함수
	void TryFire(const DIRECTION _AmingDir);
	void TrySkill(const DIRECTION _AmingDir);

	// Getters & Setter
	void SetDamage(int _RangedDamage) { m_Damage = _RangedDamage + DEFAULT_DAMAGE; }
	virtual std::string GetName() const { return "Basic Bow"; }
	virtual BOW_TYPE GetType() const { return m_BowType; }
	void SetOwner(Creature* _Owner);
	int GetSkillCoolTime();
	void SetAttackTimerCool(int _AttackSpeed);
};

