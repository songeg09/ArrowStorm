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
}; 

