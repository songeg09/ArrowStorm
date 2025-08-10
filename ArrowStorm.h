#pragma once
#include "Mecro.h"
#include <memory>
#include <vector>
#include <list>

struct Cell
{
	BOARD_OBJECT m_Type;
	int m_Id;

	Cell()
	{
		m_Type = BOARD_OBJECT::EMPTY;
		m_Id = -1;
	}

	Cell(BOARD_OBJECT _type)
	{
		m_Type = _type;
		m_Id = -1;
	}

	Cell(BOARD_OBJECT _type, int _Id)
	{
		m_Type = _type;
		m_Id = _Id;
	}
};

class ArrowStorm
{

public:
	ArrowStorm();
	~ArrowStorm();

	void NewGame();
	bool LoadGame();
	void Initialize();
	void Run();

private:
	Cell m_Board[BOARD_SIZE::BOARD_WIDHT][BOARD_SIZE::BOARD_HEIGHT] = {};
	
	std::vector<std::unique_ptr<class Creature>> m_CreatureArr; // 0 번 인덱스는 항상 플레이어
	std::list<std::unique_ptr<class Projectile>> m_ProjectileList;


	void HandleAllCreatureMoveRequests();
	void HandleCretureMoveRequest(std::unique_ptr<class Creature>& _Actor, const int _Id);
	void ApplyCreatureMoveAndRedraw(std::unique_ptr<class Creature>& _Creature, const Position& _NewPosition, const int _Id);
	void HandlePlayerTurnRequest();
	void HandlePlayerFireRequest();

	void HandleAllProjectileMoveRequests();
	void ApplyProjectileMoveAndRedraw(std::unique_ptr<class Projectile>& _Projectile);
	void ApplyProjectileMoveAndRedraw(std::unique_ptr<class Projectile>& _Projectile, const Position& _NewPosition);

	bool IsMovableTile(const Position& _Position);
	bool InRange(const Position& _Position);

};

