#pragma once
#include "Monster.h"

class Slime : public Monster
{

public:
	Slime(const Position _InitialPos);
	virtual ~Slime();

	virtual void Tick() override;

protected:
	void FollowTarget();
	Position GetNextPosition();
	void MarkingsForBFS(bool option);
	
};

