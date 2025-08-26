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
	bool m_EndGame;
	Map m_Map;
	std::vector<std::unique_ptr<class Creature>> m_CreatureArr; // 0번은 항상 플레이어
	std::list<std::unique_ptr<class Projectile>> m_ProjectileList;

	// 게임 Tick 관리 함수들
	void Tick();
	void CommitTick();

	// 멤버 변수 관리 함수들
	void CollisionCheck();
	bool DidHitWall(std::list<std::unique_ptr<Projectile>>::iterator& it);
	int DidHitCreature(const std::unique_ptr<Projectile>& _Projectile);
	void ApplyHit(const int& _Index, const int _Damage);

	// 아이템 관련 함수들
	void BowChange(class Player* player);
	void LoadBow(BOW_TYPE _BowType);

	// 맵 관련 함수들
	void LoadNextMap(int _MapIndex);
	void RelocatePlayer(Position _Pos);

	// 게임 시작, 로드 ,종료 관리 함수
	void InitGame();
	void InitBoard();
	bool IsGameOver();
	bool LoadPlayerInfo();
	void SavePlayerInfo();

	// 유틸리티 함수
	void GenerateMonster();
	Position GetRandomePos();

	

public:
	static ArrowStorm& GetInstance();

	// 게임 시작, 로드 ,종료 관리 함수
	void NewGame();
	bool LoadGame();
	void Run();
	void EndGame();

	// 플레이어 이동시 확인이 필요한것들
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

	// 유틸리티 함수
	void DrawFullBoard();
	bool CreatureExistAtPos(const Position& _Pos);
	BOARD_OBJECT(&MakeSnapshot())[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH];

};

