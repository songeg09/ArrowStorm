#pragma once
#include "Actor.h"
class Creature abstract : public Actor
{
protected:
	// ��� ����
	int m_Hp; // �� ���ͺ��� ���� �� ����

	// �̵�
	void MoveTowards(const DIRECTION& _Direction) override;

public:
	// ������ �Ҹ���
	Creature(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Creature();

	// Getter & Setter
	int GetHp() { return m_Hp; }
	virtual void TakeDamage(const int _Damage);
};

