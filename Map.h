#pragma once
#include "Mecro.h"


using BoardArr = BOARD_OBJECT[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH];

class Map
{
private:
	BOARD_OBJECT m_Board[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH];

public:
	Map();
	~Map();

	BOARD_OBJECT(*GetBoard())[BOARD_SIZE::BOARD_WIDTH];
	bool IsValidPos(const Position& Pos);
	bool InRange(const Position& _Position);
	void DrawBoard(); // 크리쳐&투사체 포함
};

