#pragma once
#include "Monster.h"

class Skeleton : public Monster
{
protected:
	// 멤버 변수
	std::unique_ptr<class Bow> m_Bow;

	// 공격
	bool IsAligned();

	// 이동
	void Wander();
	


public:
	// 생성자 소멸자
	Skeleton(const Position _InitialPos);
	virtual ~Skeleton();

	// Tick
	virtual void Tick() override;
};

