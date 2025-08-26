#pragma once
#include "Bow.h"

class TriBow : public Bow
{
protected:
	// 공격 함수
	virtual void UseSkill(const DIRECTION _AmingDir) override;

public:
	// 생성자 소멸자
	TriBow(class Creature* _Owner = nullptr);
	virtual ~TriBow();
	
	// Getter & Setter
	virtual std::string GetName() const override { return "Triple Bow"; }
};

