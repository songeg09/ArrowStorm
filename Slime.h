#pragma once
#include "Monster.h"

class Slime : public Monster
{
protected:
	// 이동
	void FollowTarget();
	Position GetNextPosition();

public:
	// 생성자 소멸자
	Slime(const Position _InitialPos);
	virtual ~Slime();

	// Tick
	virtual void Tick() override;


};

