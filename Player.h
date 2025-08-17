#pragma once
#include "Creature.h"

class Player : public Creature
{
private:
	// 멤버 변수
	DIRECTION m_FacingDir;
	DIRECTION m_MovingDir;
	std::unique_ptr<class Bow> m_Bow;
	int m_Mp;

	// 플레이어 조작 함수
	void HandleInput();
	void ClearInputBuffer();
	void SetFacingDir(DIRECTION _NewFacingDir);
	BOARD_OBJECT GetArrowObject();

public:
	// 생성자 소멸자
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

