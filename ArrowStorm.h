#pragma once
#include "Mecro.h"
#include <memory>
#include <vector>
#include <list>

class ArrowStorm
{

public:
	static ArrowStorm& GetInstance();

	void NewGame();
	bool LoadGame();

	void Initialize();
	void Run();

	std::list<std::unique_ptr<class Projectile>>& GetProjectileList(){return m_ProjectileList;}

private:
	ArrowStorm();
	~ArrowStorm();

	//std::unique_ptr<class Player> m_Player;
	std::vector<std::unique_ptr<class Creature>> m_CreatureArr; // 0번은 항상 플레이어
	std::list<std::unique_ptr<class Projectile>> m_ProjectileList;

	void Tick();
	void CollisionCheck();
	bool IsGameOver();

	void RemoveProjectile(std::list<std::unique_ptr<Projectile>>::iterator& it);
	int DidHit(const std::unique_ptr<Projectile>& _Projectile);
	void AfterHit(const int& _Index);

	
	//bool IsMovableTile(const Position& _Position);
	bool InRange(const Position& _Position);

};

