#pragma once
#include "Bow.h"

class TriBow : public Bow
{
protected:
	// ���� �Լ�
	virtual void UseSkill(const DIRECTION _AmingDir) override;

public:
	TriBow(class Creature* _Owner);
	virtual ~TriBow();

};

