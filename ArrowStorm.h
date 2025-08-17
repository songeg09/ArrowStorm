#pragma once
#include "Mecro.h"
#include <memory>
#include <vector>
#include <list>

// 싱글톤
class ArrowStorm
{

public:
	static ArrowStorm& GetInstance();

	// 게임 시작, 로드 ,종료 관리 함수
	void NewGame();
	bool LoadGame();
	void Initialize();
	void Run();

	// Getter
	static std::list<std::unique_ptr<class Projectile>>& GetProjectileList()
	{
		return GetInstance().m_ProjectileList;
	}
	static std::vector<std::unique_ptr<class Creature>>& GetCreatureArr()
	{ 
		return GetInstance().m_CreatureArr;
	}

	// 유틸리티 정적 함수
	static bool CreatureExistAtPos(const Position& _Pos);

private:
	// 생성자 소멸자
	ArrowStorm();
	~ArrowStorm();

	// 멤버 변수
	std::vector<std::unique_ptr<class Creature>> m_CreatureArr; // 0번은 항상 플레이어
	std::list<std::unique_ptr<Projectile>> m_ProjectileList;

	// 게임 Tick 관리 함수들
	void Tick();
	void CommitTick();

	// 멤버 변수 관리 함수들
	void CollisionCheck();
	void RemoveProjectile(std::list<std::unique_ptr<Projectile>>::iterator& it);
	int DidHit(const std::unique_ptr<Projectile>& _Projectile);
	void ApplyHit(const int& _Index, const int _Damage);

	// 게임 시작, 로드 ,종료 관리 함수
	bool IsGameOver();

};

