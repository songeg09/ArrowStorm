#include "Map.h"
#include "DrawManager.h"

#include <fstream>

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

void Map::LoadMap(std::string _MapName)
{
	_MapName = "Maps/" + _MapName + ".txt";
	std::ifstream load(_MapName);

	if (load.is_open())
	{
		// 맵 로드
		std::string temp;
		for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
		{
			load >> temp;
			for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH; ++x)
			{	
				m_Board[y][x] = GetBoardObject(temp[x]);
				if (m_Board[y][x] == BOARD_OBJECT::DOOR)
				{
					m_Doors[Position::GetDirection(Position(BOARD_SIZE::BOARD_WIDTH / 2, BOARD_SIZE::BOARD_HEIGHT / 2), Position(x, y))].m_Position = Position(x, y);
				}
			}
		}

		// 문 로드
		for (int i = 0; i < 4; ++i)
		{
			load >> temp;
			m_Doors[i].m_Name = temp;
		}

		load.close();
	}
}

BOARD_OBJECT Map::GetBoardObject(char _MapCell)
{
	switch (_MapCell)
	{
	case '1':
		return BOARD_OBJECT::EMPTY;
	case '0':
		return BOARD_OBJECT::WALL;
	case '2':
		return BOARD_OBJECT::CHEST;
	case '3':
		return BOARD_OBJECT::BOW;
	case '4':
		return BOARD_OBJECT::DOOR;
	default:
		return BOARD_OBJECT::EMPTY;
	}
}
