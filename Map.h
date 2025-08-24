#pragma once
#include "Mecro.h"
#include <vector>

extern Position Doors[4];

class Map
{
private:
	// 멤버 변수
	int m_TotalMapNum;
	int m_CurMapIndex;
	std::string m_Name;
	std::vector<std::vector<std::vector<int>>> m_Maps;

	// 로드 
	void LoadSingleMap(int index, std::fstream& load);

	// 유틸리티 함수
	BOARD_OBJECT IntToBO(int _Input);

public:
	// 생성자 소멸자
	Map();
	~Map();

	// 유틸 함수
	bool IsValidPos(const Position& Pos);
	bool InRange(const Position& _Position);
	void DrawBoard(); // 크리쳐&투사체 포함

	// 로드 및 세이브
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

