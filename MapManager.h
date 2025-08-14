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

	static bool IsValidPos(const Position& Pos)
	{
		// 범위 밖
		if (!(0 <= Pos.m_x && Pos.m_x < BOARD_SIZE::BOARD_WIDTH && 0 <= Pos.m_y && Pos.m_y < BOARD_SIZE::BOARD_HEIGHT))
			return false;
		// 벽 충돌
		if (GetInstance().m_Board[Pos.m_y][Pos.m_x] == BOARD_OBJECT::WALL)
			return false;

		return true;
	}

	static bool InRange(const Position& _Position)
	{
		return (0 <= _Position.m_x && _Position.m_x < BOARD_SIZE::BOARD_WIDTH
			&& 0 <= _Position.m_y && _Position.m_y < BOARD_SIZE::BOARD_HEIGHT);
	}
};

