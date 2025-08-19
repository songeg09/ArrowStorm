#pragma once
#include "Mecro.h"

struct Door
{
	std::string m_Name;
	Position m_Position;

	Door()
	{
		m_Name = "X";
		m_Position = Position(-1, -1);
	}

	Door(std::string _Name, Position _Position)
	{
		m_Name = _Name;
		m_Position = _Position;
	}
};

class Map
{
private:
	BOARD_OBJECT m_Board[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH];
	Door m_Doors[4]; // �������

public:
	Map();
	~Map();

	BOARD_OBJECT(*GetBoard())[BOARD_SIZE::BOARD_WIDTH];
	bool IsValidPos(const Position& Pos);
	bool InRange(const Position& _Position);
	void DrawBoard(); // ũ����&����ü ����

	// �ε�
	void LoadMap(std::string _MapName);

	// Getters
	Door (& GetDoors())[4] { return m_Doors; }

	BOARD_OBJECT GetBoardObject(char _MapCell);
};

