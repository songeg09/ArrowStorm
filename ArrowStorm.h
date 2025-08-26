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
	bool m_EndGame;
	Map m_Map;
	std::vector<std::unique_ptr<class Creature>> m_CreatureArr; // 0���� �׻� �÷��̾�
	std::list<std::unique_ptr<class Projectile>> m_ProjectileList;

	// ���� Tick ���� �Լ���
	void Tick();
	void CommitTick();

	// ��� ���� ���� �Լ���
	void CollisionCheck();
	bool DidHitWall(std::list<std::unique_ptr<Projectile>>::iterator& it);
	int DidHitCreature(const std::unique_ptr<Projectile>& _Projectile);
	void ApplyHit(const int& _Index, const int _Damage);

	// ������ ���� �Լ���
	void BowChange(class Player* player);
	void LoadBow(BOW_TYPE _BowType);

	// �� ���� �Լ���
	void LoadNextMap(int _MapIndex);
	void RelocatePlayer(Position _Pos);

	// ���� ����, �ε� ,���� ���� �Լ�
	void InitGame();
	void InitBoard();
	bool IsGameOver();
	bool LoadPlayerInfo();
	void SavePlayerInfo();

	// ��ƿ��Ƽ �Լ�
	void GenerateMonster();
	Position GetRandomePos();

	

public:
	static ArrowStorm& GetInstance();

	// ���� ����, �ε� ,���� ���� �Լ�
	void NewGame();
	bool LoadGame();
	void Run();
	void EndGame();

	// �÷��̾� �̵��� Ȯ���� �ʿ��Ѱ͵�
	void ItemCheck(Player* player);
	void MapChangeCheck(Position _Pos);

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
	void DrawFullBoard();
	bool CreatureExistAtPos(const Position& _Pos);
	BOARD_OBJECT(&MakeSnapshot())[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH];

};

