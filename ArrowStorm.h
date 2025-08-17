#pragma once
#include "Mecro.h"
#include <memory>
#include <vector>
#include <list>

// �̱���
class ArrowStorm
{

public:
	static ArrowStorm& GetInstance();

	// ���� ����, �ε� ,���� ���� �Լ�
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

	// ��ƿ��Ƽ ���� �Լ�
	static bool CreatureExistAtPos(const Position& _Pos);

private:
	// ������ �Ҹ���
	ArrowStorm();
	~ArrowStorm();

	// ��� ����
	std::vector<std::unique_ptr<class Creature>> m_CreatureArr; // 0���� �׻� �÷��̾�
	std::list<std::unique_ptr<Projectile>> m_ProjectileList;

	// ���� Tick ���� �Լ���
	void Tick();
	void CommitTick();

	// ��� ���� ���� �Լ���
	void CollisionCheck();
	void RemoveProjectile(std::list<std::unique_ptr<Projectile>>::iterator& it);
	int DidHit(const std::unique_ptr<Projectile>& _Projectile);
	void ApplyHit(const int& _Index, const int _Damage);

	// ���� ����, �ε� ,���� ���� �Լ�
	bool IsGameOver();

};

