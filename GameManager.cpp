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
		GetSafeInput(Choice);

		switch ((LOBBY_CHOICE)Choice)
		{
		case LOBBY_CHOICE::NEW_GAME:
			m_ArrowStorm.NewGame();
			m_ArrowStorm.Run();
			break;
		case LOBBY_CHOICE::CONTINUE:
			if (m_ArrowStorm.LoadGame())
			{
				m_ArrowStorm.Run();
			}
			else
			{
				DrawManager::DrawInfoPopup("No Save Data Found");
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
	DrawManager::DrawEdges(ASPECT_RATIO::SCREEN_WIDTH, ASPECT_RATIO::SCREEN_HEIGHT, "#");
	DrawChoices();
}

void GameManager::DrawChoices()
{
	DrawManager::DrawMidText("A r r o w  S t o r m", ASPECT_RATIO::SCREEN_WIDTH, ASPECT_RATIO::SCREEN_HEIGHT * 0.3f);
	DrawManager::DrawMidText("1.New Game ", ASPECT_RATIO::SCREEN_WIDTH, ASPECT_RATIO::SCREEN_HEIGHT * 0.4f);
	DrawManager::DrawMidText("2.Continue ", ASPECT_RATIO::SCREEN_WIDTH, ASPECT_RATIO::SCREEN_HEIGHT * 0.5f);
	DrawManager::DrawMidText("3.Quit     ", ASPECT_RATIO::SCREEN_WIDTH, ASPECT_RATIO::SCREEN_HEIGHT * 0.6f);
	DrawManager::DrawMidText("Select :   ", ASPECT_RATIO::SCREEN_WIDTH, ASPECT_RATIO::SCREEN_HEIGHT * 0.7f);
}



