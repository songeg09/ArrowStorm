#pragma once
#include "Monster.h"

class Slime : public Monster
{
protected:
	// �̵�
	void FollowTarget();
	Position GetNextPosition();

public:
	// ������ �Ҹ���
	Slime(const Position _InitialPos);
	virtual ~Slime();

	// Tick
	virtual void Tick() override;


};

