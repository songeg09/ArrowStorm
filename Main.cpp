#include "GameManager.h"
#include <iostream>

int main()
{
	std::srand(time(nullptr));
	GameManager GameManager;
	GameManager.RunGame();
	return 0;
}