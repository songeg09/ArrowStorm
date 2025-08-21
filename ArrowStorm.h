#pragma once
#include "Mecro.h"
#include "Map.h"

#include <memory>
#include <vector>
#include <list>
#include <fstream>

// 싱글톤
class ArrowStorm
{
private:
	// 생성자 소멸자
	ArrowStorm();
	~ArrowStorm();

	// 멤버 변수
	Map m_Map;
	std::vector<std::unique_ptr<class Creature>> m_CreatureArr; // 0번은 항상 플레이어
	std::list<std::unique_ptr<class Projectile>> m_ProjectileList;

	// 게임 Tick 관리 함수들
	void Tick();
	void CommitTick();

	// 멤버 변수 관리 함수들
	void CollisionCheck();
	void RemoveProjectile(std::list<std::unique_ptr<Projectile>>::iterator& it);
	int DidHit(const std::unique_ptr<Projectile>& _Projectile);
	void ApplyHit(const int& _Index, const int _Damage);

	// 아이템 관련 함수들
	void ItemCheck();
	void BowChange(class Player* player);

	// 맵 관련 함수들
	void LoadNextMap(Door _Door);
	void MapChangeCheck();
	void RelocatePlayer(Position _Pos);

	// 게임 시작, 로드 ,종료 관리 함수
	bool IsGameOver();

	// 유틸리티 함수
	void DrawFullBoard();
	void GenerateMonster();
	Position GetRandomePos();
	void LoadPlayer(std::fstream& load);
	void Init();

public:
	static ArrowStorm& GetInstance();

	// 게임 시작, 로드 ,종료 관리 함수
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

	// 유틸리티 함수
	bool CreatureExistAtPos(const Position& _Pos);
	BOARD_OBJECT(&MakeSnapshot())[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH];


};

