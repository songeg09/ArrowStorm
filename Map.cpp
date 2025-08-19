#include "Map.h"
#include "DrawManager.h"

Map::Map()
{

}

Map::~Map()
{

}

bool Map::IsValidPos(const Position& Pos)
{
	// 범위 밖
	if (!InRange(Pos))
		return false;
	// 벽 충돌
	if (m_Board[Pos.m_y][Pos.m_x] == BOARD_OBJECT::WALL)
		return false;

	return true;
}

bool Map::InRange(const Position& _Position)
{
	return (0 <= _Position.m_x && _Position.m_x < BOARD_SIZE::BOARD_WIDTH
		&& 0 <= _Position.m_y && _Position.m_y < BOARD_SIZE::BOARD_HEIGHT);
}

BOARD_OBJECT(*Map::GetBoard())[BOARD_SIZE::BOARD_WIDTH]
{
	return m_Board;
}

void Map::DrawBoard()
{
	// 벽 그리기
	std::string Line;
	for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
	{
		DrawManager::gotoxy(0, y);
		Line = "";
		for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH; ++x)
		{
			Line += DrawManager::GetObjectIcon(Map::GetBoard()[y][x]);
		}
		std::cout << Line;
	}
}