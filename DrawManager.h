#pragma once
#include "Windows.h"

#include <string>
#include <iostream>

#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define RED SetConsoleTextAttribute( col,0x000c );

namespace DrawManager
{
	static void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	static void DrawMidText(std::string str, int x, int y)
	{
		if (x > str.size() / 2)
			x -= str.size() / 2;
		gotoxy(x, y);
		std::cout << str;
	}


}