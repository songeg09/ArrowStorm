#pragma once
#include "Mecro.h"
#include <vector>

extern Position Doors[4];

class Map
{
private:
	// ��� ����
	int m_TotalMapNum;
	int m_CurMapIndex;
	std::string m_Name;
	std::vector<std::vector<std::vector<int>>> m_Maps;

	// �ε� 
	void LoadSingleMap(int index, std::fstream& load);

	// ��ƿ��Ƽ �Լ�
	BOARD_OBJECT IntToBO(int _Input);

public:
	// ������ �Ҹ���
	Map();
	~Map();

	// ��ƿ �Լ�
	bool IsValidPos(const Position& Pos);
	bool InRange(const Position& _Position);
	void DrawBoard(); // ũ����&����ü ����

	// �ε� �� ���̺�
	void LoadMapsForNewGame();
	bool LoadMapsToContinue();
	void SaveMapInfo();

	// Getters & Setters
	BOARD_OBJECT GetBoardObject(int x, int y) { return IntToBO(m_Maps[m_CurMapIndex][y][x]); }
	std::vector<std::vector<int>>& GetBoard() { return m_Maps[m_CurMapIndex]; }
	std::string GetName() { return m_Name; }
	int GetCurMapIndex() { return m_CurMapIndex; }
	void SetCurMapIndex(int _CurMapIndex) { m_CurMapIndex = _CurMapIndex; }
};

