#pragma once
#include "Mecro.h"
class MapManager
{
private:
	MapManager() {}
	~MapManager() {}
	BOARD_OBJECT m_Board[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH] = {};

public:
	static MapManager& GetInstance()
	{
		static MapManager Manager;
		return Manager;
	}

	static BOARD_OBJECT (*GetBoard())[BOARD_SIZE::BOARD_WIDTH]
	{
		return GetInstance().m_Board;
	}

	static bool IsValidPosition(const Position& Pos)
	{
		if (!(0 <= Pos.m_x && Pos.m_x < BOARD_SIZE::BOARD_WIDTH && 0 <= Pos.m_y && Pos.m_y < BOARD_SIZE::BOARD_HEIGHT))
			return false;
		if (GetInstance().m_Board[Pos.m_y][Pos.m_x] == BOARD_OBJECT::WALL)
			return false;

		return true;
	}
};

