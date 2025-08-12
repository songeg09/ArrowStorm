#pragma once

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
	void DrawLobby();
	void DrawChoices();

	void DrawErrorPopUp();
};

