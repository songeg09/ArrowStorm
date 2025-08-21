#pragma once
#include "Mecro.h"

class Bow
{
protected:
	// ��� ����
	std::string m_Name;
	class Creature* m_Owner;
	int m_Damage;
	DIRECTION m_AmingDir;
	std::unique_ptr<class Timer> m_AttackTimer;
	std::unique_ptr<class Timer> m_SkillTimer;

	// ���� �Լ�
	void Fire(const DIRECTION _AmingDir);
	virtual void UseSkill(const DIRECTION _AmingDir);

public:
	// ������ �Ҹ���
	Bow();
	Bow(class Creature* _Owner);
	virtual ~Bow();
	
	// �߻� ���� �Լ�
	void TryFire(const DIRECTION _AmingDir);
	void TrySkill(const DIRECTION _AmingDir);

	// Getters & Setter
	std::string GetName() { return m_Name; }
	void SetOwner(Creature* _Owner) { m_Owner = _Owner; }
	virtual BOW_TYPE GetType() const { return BOW_TYPE::BASIC; }
};

