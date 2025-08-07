#include "GameManager.h"
#include "DrawManager.h"
#include "Mecro.h"

#include <iostream>

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::RunGame()
{
	int Choice;
	while (1)
	{
		system("cls");
		DrawLobby();
		std::cin >> Choice;

		switch ((LOBBY_CHOICE)Choice)
		{
		case LOBBY_CHOICE::NEW_GAME:
			m_ArrowStorm.Initialize();
			m_ArrowStorm.Run();
			break;
		case LOBBY_CHOICE::CONTINUE:
			if (m_ArrowStorm.Load())
			{
				m_ArrowStorm.Run();
			}
			else
			{

			}
			break;
		case LOBBY_CHOICE::QUIT:
			return;
		default:
			break;
		}

	}
}

void GameManager::DrawLobby()
{
	DrawManager::DrawMidText("A r r o w  S t o r m", ASPECT_RATIO::WIDTH, ASPECT_RATIO::HEIGHT * 0.3f);
	DrawManager::DrawMidText("1.New Game ", ASPECT_RATIO::WIDTH, ASPECT_RATIO::HEIGHT * 0.4f);
	DrawManager::DrawMidText("2.Continue ", ASPECT_RATIO::WIDTH, ASPECT_RATIO::HEIGHT * 0.5f);
	DrawManager::DrawMidText("3.Quit     ", ASPECT_RATIO::WIDTH, ASPECT_RATIO::HEIGHT * 0.6f);
	DrawManager::DrawMidText("Select :   ", ASPECT_RATIO::WIDTH, ASPECT_RATIO::HEIGHT * 0.7f);
}