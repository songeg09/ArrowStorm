#pragma once
#include "Bow.h"

class TriBow : public Bow
{
protected:
	// ���� �Լ�
	virtual void UseSkill(const DIRECTION _AmingDir) override;

public:
	// ������ �Ҹ���
	TriBow(class Creature* _Owner = nullptr);
	virtual ~TriBow();
	
	// Getter & Setter
	virtual std::string GetName() const override { return "Triple Bow"; }
};

