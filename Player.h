#pragma once
#include "Creature.h"

class Player : public Creature
{
private:
	// ��� ����
	DIRECTION m_FacingDir;
	DIRECTION m_MovingDir;
	std::unique_ptr<class Bow> m_Bow;
	int m_Mp;

	// �÷��̾� ���� �Լ�
	void HandleInput();
	void ClearInputBuffer();
	void SetFacingDir(DIRECTION _NewFacingDir);
	BOARD_OBJECT GetArrowObject();

public:
	// ������ �Ҹ���
	Player(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Player();

	// Getter Setters
	DIRECTION GetFacingDir() { return m_FacingDir; }
	virtual void TakeDamage(const int _Damage) override;
	class Bow* GetBow() { return m_Bow.get(); }
	void UseMp() { m_Mp--; }
	int GetMp() { return m_Mp; }

	// Tick
	virtual void Tick() override;
};

