#pragma once
#include "Bow.h"

class TriBow : public Bow
{
protected:
	// 공격 함수
	virtual void UseSkill(const DIRECTION _AmingDir) override;

public:
	TriBow(class Creature* _Owner = nullptr);
	virtual ~TriBow();
	virtual std::string GetName() const override { return "Triple Bow"; }
	virtual BOW_TYPE GetType() const override{ return BOW_TYPE::TRIPLE; }
};

