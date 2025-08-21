#include "Map.h"
#include "DrawManager.h"

#include <fstream>

Position Doors[4] = {
	Position(BOARD_SIZE::BOARD_WIDTH / 2, 0), // ªÛ
	Position(BOARD_SIZE::BOARD_WIDTH - 1, BOARD_SIZE::BOARD_HEIGHT / 2), // øÏ
	Position(BOARD_SIZE::BOARD_WIDTH / 2, BOARD_SIZE::BOARD_HEIGHT - 1), // «œ
	Position(0, BOARD_SIZE::BOARD_HEIGHT / 2), // ¡¬
};

Map::Map()
{
	
}

void Map::LoadMapsForNewGame()
{
	std::fstream load("Maps/MapList.txt");
	if (load.is_open())
	{
		int tmp;
		// ≈‰≈ª ∏  ∞πºˆ ±∏«œ±‚
		load >> tmp;
		m_TotalMapNum = tmp;

		m_Maps.resize(m_TotalMapNum, std::vector<std::vector<int>>(BOARD_SIZE::BOARD_HEIGHT, std::vector<int>(BOARD_SIZE::BOARD_WIDTH)));
		std::string filename;
		for (int i = 0; i < m_TotalMapNum; ++i)
		{
			load >> tmp;
			filename = "Maps/" + std::to_string(tmp) + ".txt";
			LoadMap(i, filename);
		}
		load.close();
	}	
}

bool Map::LoadMapsToContinue()
{
	std::fstream load("Saves/Map_Save.txt");

	if (load.is_open())
	{
		int tmp;
		// ∏  ¿Œµ¶Ω∫ ∫“∑Øø¿±‚
		load >> tmp;
		m_CurMapIndex = tmp;

		// √— ∏  ∞πºˆ ∫“∑Øø¿±‚
		load >> tmp;
		m_TotalMapNum = tmp;


		std::string tmpChar;
		m_Maps.resize(m_TotalMapNum, std::vector<std::vector<int>>(BOARD_SIZE::BOARD_HEIGHT, std::vector<int>(BOARD_SIZE::BOARD_WIDTH)));
		for (int index = 0; index < m_TotalMapNum; ++index)
		{
			for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
			{
				load >> tmpChar;
				for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH; ++x)
				{
					m_Maps[index][y][x] = tmpChar[x] - '0';
				}
			}

			int NextMapIndex;
			for (int DoorIndex = 0; DoorIndex < 4; ++DoorIndex)
			{
				load >> NextMapIndex;
				if (NextMapIndex == -1) continue;
				m_Maps[index][Doors[DoorIndex].m_y][Doors[DoorIndex].m_x] = NextMapIndex;
			}
		}

		return true;
	}

	return false;
}

void Map::LoadMap(int index, std::string filename)
{
	std::fstream load(filename);
	if (load.is_open())
	{
		std::string tmp;
		for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
		{
			load >> tmp;
			for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH; ++x)
			{
				m_Maps[index][y][x] = tmp[x] - '0';
			}
		}
		
		int NextMapIndex;
		for (int i = 0; i < 4; ++i)
		{
			load >> NextMapIndex;
			if (NextMapIndex == -1) continue;
			m_Maps[index][Doors[i].m_y][Doors[i].m_x] = NextMapIndex;
		}

		load.close();
	}
}

void Map::SaveMapInfo()
{
	std::ofstream save("Saves/Map_Save.txt", std::ios::trunc);

	// «ˆ¿Á ∏  ¿Œµ¶Ω∫ ¿˙¿Â
	save << m_CurMapIndex << std::endl;
	// ≈‰≈ª ∏  ∞πºˆ ¿˙¿Â
	save << m_TotalMapNum << std::endl;

	for (int i = 0; i < m_TotalMapNum; ++i)
	{
		for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
		{
			for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH; ++x)
			{
				if(m_Maps[i][y][x] >= 100)
					save << 1;
				else
					save << m_Maps[i][y][x];
			}
			save << std::endl;
		}

		for (int DoorIndex = 0; DoorIndex < 4; ++DoorIndex)
		{
			if (m_Maps[i][Doors[DoorIndex].m_y][Doors[DoorIndex].m_x] < 100)
				save << -1 << std::endl;
			else
				save << m_Maps[i][Doors[DoorIndex].m_y][Doors[DoorIndex].m_x] << std::endl;
		}
	}
}

Map::~Map()
{

}

bool Map::IsValidPos(const Position& Pos)
{
	// π¸¿ß π€
	if (!InRange(Pos))
		return false;
	// ∫Æ √Êµπ
	if (m_Maps[m_CurMapIndex][Pos.m_y][Pos.m_x] == BOARD_OBJECT::WALL)
		return false;

	return true;
}

bool Map::InRange(const Position& _Position)
{
	return (0 <= _Position.m_x && _Position.m_x < BOARD_SIZE::BOARD_WIDTH
		&& 0 <= _Position.m_y && _Position.m_y < BOARD_SIZE::BOARD_HEIGHT);
}


void Map::DrawBoard()
{
	std::string Line;
	for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
	{
		DrawManager::gotoxy(0, y);
		Line = "";
		for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH; ++x)
		{
			Line += DrawManager::GetObjectIcon(IntToBO(m_Maps[m_CurMapIndex][y][x]));
		}
		std::cout << Line;
	}
}


BOARD_OBJECT Map::IntToBO(int _Input)
{
	if (_Input >= 100)
		return BOARD_OBJECT::DOOR;
	else
		return (BOARD_OBJECT)_Input;
}