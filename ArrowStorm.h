#pragma once
#include "Mecro.h"
#include "Map.h"

#include <memory>
#include <vector>
#include <list>
#include <fstream>

// �̱���
class ArrowStorm
{
private:
	// ������ �Ҹ���
	ArrowStorm();
	~ArrowStorm();

	// ��� ����
	Map m_Map;
	std::vector<std::unique_ptr<class Creature>> m_CreatureArr; // 0���� �׻� �÷��̾�
	std::list<std::unique_ptr<class Projectile>> m_ProjectileList;

	// ���� Tick ���� �Լ���
	void Tick();
	void CommitTick();

	// ��� ���� ���� �Լ���
	void CollisionCheck();
	void RemoveProjectile(std::list<std::unique_ptr<Projectile>>::iterator& it);
	int DidHit(const std::unique_ptr<Projectile>& _Projectile);
	void ApplyHit(const int& _Index, const int _Damage);

	// ������ ���� �Լ���
	void ItemCheck();
	void BowChange(class Player* player);

	// �� ���� �Լ���
	void LoadNextMap(Door _Door);
	void MapChangeCheck();
	void RelocatePlayer(Position _Pos);

	// ���� ����, �ε� ,���� ���� �Լ�
	bool IsGameOver();

	// ��ƿ��Ƽ �Լ�
	void DrawFullBoard();
	void GenerateMonster();
	Position GetRandomePos();
	void LoadPlayer(std::fstream& load);
	void Init();

public:
	static ArrowStorm& GetInstance();

	// ���� ����, �ε� ,���� ���� �Լ�
	void NewGame();
	bool LoadGame();
	void Initialize();
	void Run();
	void SaveGame();

	// Getter
	std::list<std::unique_ptr<Projectile>>& GetProjectileList()
	{
		return m_ProjectileList;
	}

	std::vector<std::unique_ptr<Creature>>& GetCreatureArr()
	{ 
		 return m_CreatureArr;
	}

	Map& GetMap() { return m_Map; }

	// ��ƿ��Ƽ �Լ�
	bool CreatureExistAtPos(const Position& _Pos);
	BOARD_OBJECT(&MakeSnapshot())[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH];


};

