#pragma once
#include "Monster.h"

class Skeleton : public Monster
{
protected:
	// ��� ����
	std::unique_ptr<class Bow> m_Bow;

	// ����
	bool IsAligned();

	// �̵�
	void Wander();
	


public:
	// ������ �Ҹ���
	Skeleton(const Position _InitialPos);
	virtual ~Skeleton();

	// Tick
	virtual void Tick() override;
};

