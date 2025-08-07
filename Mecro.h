#pragma once
#define NOMINMAX
#include <limits>
#include <iostream>


enum ASPECT_RATIO
{
	SCREEN_WIDTH = 100,
	SCREEN_HEIGHT = 30
};

enum BOARD_SIZE
{
	BOARD_WIDHT = 100,
	BOARD_HEIGHT = 25
};

enum BOARD_OBJECT
{
	WALL,
	DOOR,
	EMPTY
};

enum POPUP_SIZE
{
	POPUP_WIDTH = 40,
	POPUP_HEIGHT = 10,
};

enum POPUP_CHOICE
{
	YES = 1
};

/*
	integer Ÿ���� ��ǲ�� �ùٸ��� �޾Ƽ�
	cin ���ۿ� ������ ������ �ʵ��� �ϴ� �Լ�
*/
int GetSafeInput(int& Input)
{
	std::cin >> Input;

	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return -1;
	}
	else
	{
		return Input;
	}
}