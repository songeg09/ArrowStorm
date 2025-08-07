#pragma once
#include "Mecro.h"
#include "Windows.h"

#include <string>
#include <iostream>

#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define RED SetConsoleTextAttribute( col,0x000c );

constexpr int POPUP_TEXT_OFFSET = ASPECT_RATIO::SCREEN_HEIGHT / 2 - POPUP_SIZE::POPUP_HEIGHT / 2;;

namespace DrawManager
{
	static void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	static std::string GetObjectIcon(BOARD_OBJECT _eObject)
	{
		ORIGINAL
			switch (_eObject)
			{
			case BOARD_OBJECT::WALL:
				return "▦";
			default:
				return " ";
			}
	}

	/*
		해당 해당 좌표가 중앙이 되도록 메시지를 출력
	*/
	static void DrawMidText(std::string str, int x, int y)
	{
		if (x / 2 - str.size() / 2 > 0)
			x = x / 2 - str.size() / 2;
		gotoxy(x, y);
		std::cout << str;
	}

	/*
		화면 중앙에 매개변수로 받은 크기의 속이 꽉찬 상자를 그린다.
		_Width : 엣지의 넓이
		_Height : 엣지의 높이
	*/
	static void DrawEdges(int _Width, int _Height, std::string _Object)
	{
		int TopLeftX = ASPECT_RATIO::SCREEN_WIDTH / 2 - _Width / 2;
		int TopLeftY = ASPECT_RATIO::SCREEN_HEIGHT / 2 - _Height / 2;
		int BottomRightX = TopLeftX + _Width;
		int BottomRightY = TopLeftY + _Height;;
		
		std::string Line;
		for (int y = TopLeftY; y < BottomRightY; ++y)
		{
			Line = "";
			DrawManager::gotoxy(TopLeftX, y);
			for (int x = TopLeftX; x < BottomRightX; ++x)
			{
				if (x == TopLeftX || x == BottomRightX - 1 || y == TopLeftY || y == BottomRightY - 1)
					Line += _Object;
				else
					Line += " ";
			}
			std::cout << Line;
		}
	}

	void DrawPopupContent(const std::string& _Msg)
	{
		DrawEdges(POPUP_SIZE::POPUP_WIDTH, POPUP_SIZE::POPUP_HEIGHT, "+");
		DrawMidText(_Msg, ASPECT_RATIO::SCREEN_WIDTH, POPUP_TEXT_OFFSET + POPUP_SIZE::POPUP_HEIGHT * 0.2f);
	}

	static void DrawInfoPopup(const std::string& _Msg)
	{
		DrawPopupContent(_Msg);
		DrawMidText("Press Any Key to Continue...", ASPECT_RATIO::SCREEN_WIDTH, POPUP_TEXT_OFFSET + POPUP_SIZE::POPUP_HEIGHT * 0.7f);
		system("pause >nul");
	}

	static bool DrawConfirmPopup(const std::string& _Msg)
	{
		DrawPopupContent(_Msg);
		DrawMidText("Yes = 1, No = Anyother Numbers", ASPECT_RATIO::SCREEN_WIDTH, POPUP_TEXT_OFFSET + POPUP_SIZE::POPUP_HEIGHT * 0.6f);
		DrawMidText("Select : ", ASPECT_RATIO::SCREEN_WIDTH, POPUP_TEXT_OFFSET + POPUP_SIZE::POPUP_HEIGHT * 0.7f);
		int Choice;
		GetSafeInput(Choice);

		switch ((POPUP_CHOICE)Choice)
		{
		case POPUP_CHOICE::YES:
			return true;
		default:
			return false;
		}
	}
}