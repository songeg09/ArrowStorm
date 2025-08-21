#pragma once
#include "Bow.h"

class TriBow : public Bow
{
protected:
	// ���� �Լ�
	virtual void UseSkill(const DIRECTION _AmingDir) override;

public:
	TriBow();
	TriBow(class Creature* _Owner);
	virtual ~TriBow();
	virtual BOW_TYPE GetType() const override{ return BOW_TYPE::TRIPLE; }
};

