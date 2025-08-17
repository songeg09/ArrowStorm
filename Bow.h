#pragma once
#include "Mecro.h"

class Bow
{
protected:
	// 멤버 변수
	std::string m_Name;
	class Creature* m_Owner;
	int m_Damage;
	DIRECTION m_AmingDir;
	std::unique_ptr<class Timer> m_AttackTimer;
	std::unique_ptr<class Timer> m_SkillTimer;

	void Fire(const DIRECTION _AmingDir);
	void UseSkill();

public:
	// 생성자 소멸자
	Bow(class Creature* _Owner);
	virtual ~Bow();
	
	// 발사 관련 함수
	void TryFire(const DIRECTION _AmingDir);
	void TrySkill();

	// Getters
	std::string GetName() { return m_Name; }
};

