#pragma once
#include "Mecro.h"

class Bow
{
protected:
	// ��� ����
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
	Bow(class Creature* _Owner = nullptr);
	virtual ~Bow();
	
	// �߻� ���� �Լ�
	void TryFire(const DIRECTION _AmingDir);
	void TrySkill(const DIRECTION _AmingDir);

	// Getters & Setter
	virtual std::string GetName() const { return "Basic Bow"; }
	virtual BOW_TYPE GetType() const { return BOW_TYPE::BASIC; }
	void SetOwner(Creature* _Owner) { m_Owner = _Owner; }
};

