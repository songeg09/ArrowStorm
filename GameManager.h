#pragma once
#include "ArrowStorm.h"

enum LOBBY_CHOICE 
{
	NEW_GAME = 1,
	CONTINUE,
	QUIT
};


class GameManager
{
public:
	GameManager();
	~GameManager();

	void RunGame();

private:
	ArrowStorm m_ArrowStorm;

	void DrawLobby();
	void DrawChoices();

	void DrawErrorPopUp();
};

