#pragma once
#include "Monster.h"

class Slime : public Monster
{

public:
	// 持失切 社瑚切
	Slime(const Position _InitialPos);
	virtual ~Slime();

	// Tick
	virtual void Tick() override;


};

