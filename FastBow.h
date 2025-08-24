#pragma once
#include "Bow.h"

class FastBow : public Bow
{
public:
	// ������ �Ҹ���
	FastBow(class Creature* _Owner = nullptr);
	virtual ~FastBow();
	
	// Getter & Setter
	virtual std::string GetName() const override { return "Fast Bow"; }
	virtual BOW_TYPE GetType() const override { return BOW_TYPE::FAST; }
}; 

