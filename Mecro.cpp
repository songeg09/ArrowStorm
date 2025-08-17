#include "Mecro.h"

Position Directions[4] = {Position(0,-1),Position(1,0),Position(0,1),Position(-1,0)};

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

BOARD_OBJECT GetArrowObject(const DIRECTION _AmingDir)
{
	switch (_AmingDir)
	{
	case DIRECTION::UP:
		return BOARD_OBJECT::ARROW_UP;
	case DIRECTION::RIGHT:
		return BOARD_OBJECT::ARROW_RIGHT;
	case DIRECTION::DOWN:
		return BOARD_OBJECT::ARROW_DOWN;
	case DIRECTION::LEFT:
		return BOARD_OBJECT::ARROW_LEFT;
	default:
		return BOARD_OBJECT::ARROW_UP;
	}
}