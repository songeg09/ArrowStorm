#pragma once
#include "Creature.h"
#include <functional>

class Player : public Creature
{
private:
	// 멤버 변수
	DIRECTION m_FacingDir;
	DIRECTION m_MovingDir;
	std::unique_ptr<class Bow> m_Bow;
	int m_Mp;
	int m_HpPotion;
	int m_MpPotion;
	int m_Level;
	int m_Exp;

	// 플레이어 조작 함수
	virtual void TryMove() override;
	void HandleInput();
	void ClearInputBuffer();
	void SetFacingDir(DIRECTION _NewFacingDir);

	// 포션 관련 함수
	void UpdatePotion(int& _Potion, int _MaxVal, std::function<void()> _UpdateUI);
	void TryUsePotion(POTION_TYPE _PotionType);
	void UsePotion(int& _Potion, int& Stat, std::function<void()> _UpdateUI);

public:
	// 생성자 소멸자
	Player(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	virtual ~Player();

	// Getter Setters
	DIRECTION GetFacingDir() { return m_FacingDir; }
	virtual void TakeDamage(const int _Damage) override;
	Bow* GetBow() { return m_Bow.get(); }
	void SetBow(std::unique_ptr<Bow> _NewBow);
	void UseMp();
	int GetMp() { return m_Mp; }
	void SetMp(int _Mp) { m_Mp = _Mp; }
	int GetHpPotion() { return m_HpPotion; }
	void SetHpPotion(int _HpPotion) { m_HpPotion = _HpPotion; }
	int GetMpPotion() { return m_MpPotion; }
	void SetMpPotion(int _MpPotion) { m_MpPotion = _MpPotion; }
	void EarnPotion(POTION_TYPE _PotionType);
	int GetLevel(){ return m_Level; }
	void SetLevel(int _Level) { m_Level = _Level; }
	int GetExp() { return m_Exp; }
	void SetExp(int _Exp) { m_Exp = _Exp; }

	// 레벨 관련 함수들
	void EarnExp(int _Exp);

	// Tick
	virtual void Tick() override;
};

