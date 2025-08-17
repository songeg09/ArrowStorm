#pragma once
#include "Mecro.h"


using BoardArr = BOARD_OBJECT[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH];

class MapManager
{
private:
	MapManager() {}
	~MapManager() {}
	BoardArr m_Board{};

public:
	static MapManager& GetInstance();
	static BOARD_OBJECT(*GetBoard())[BOARD_SIZE::BOARD_WIDTH];
	static bool IsValidPos(const Position& Pos);
	static bool InRange(const Position& _Position);
	static BoardArr& MakeSnapshot();
	static void DrawFullBoard(); // 크리쳐&투사체 포함
};

