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

	void RegisterProjectile(std::unique_ptr<class Projectile> _Projectile);

private:
	ArrowStorm();
	~ArrowStorm();

	std::unique_ptr<class Player> m_Player;
	std::vector<std::unique_ptr<class Creature>> m_CreatureArr; // ∏ÛΩ∫≈Õ
	std::list<std::unique_ptr<class Projectile>> m_ProjectileList;

	void Tick();
	void CollisionCheck();
	bool IsGameOver();

	//bool IsMovableTile(const Position& _Position);
	bool InRange(const Position& _Position);

};

