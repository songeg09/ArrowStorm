#pragma once
#include "Creature.h"

class Player : public Creature
{

private:
	DIRECTION m_FacingDir;

	void HandleMoveInput();
	
	void ClearInputBuffer();


public:
	Player(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	~Player();

	DIRECTION GetFacingDir() {return m_FacingDir;}
	void SetFacingDir(DIRECTION _NewFacingDir);
	
	void TryMove() override;
	DIRECTION TryTurn();
	FireRequest  TryFire();

	//TestTryShoot();
};

