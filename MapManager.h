#pragma once
#include "Mecro.h"
class MapManager
{
private:
	MapManager();
	~MapManager();
	BOARD_OBJECT m_Board[BOARD_SIZE::BOARD_HEIGTH][BOARD_SIZE::BOARD_WIDTH] = {};

public:
	static MapManager& GetInstance()
	{
		static MapManager Manager;
		return Manager;
	}

	BOARD_OBJECT (*GetBoard())[BOARD_SIZE::BOARD_WIDTH]
	{
		return &m_Board[0]; 
	}
};

