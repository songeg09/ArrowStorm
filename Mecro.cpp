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