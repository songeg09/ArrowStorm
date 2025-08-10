#pragma once
#include "Creature.h"

class Player : public Creature
{

private:
	DIRECTION m_FacingDir;

	Position HandleMoveInput();
	void ClearInputBuffer();


public:
	Player();
	~Player();

	DIRECTION GetFacingDir() {return m_FacingDir;}
	void SetFacingDir(DIRECTION _NewFacingDir);
	
	Position TryMove() override;
	DIRECTION TryTurn();
	FireRequest  TryFire();

	//TestTryShoot();
};

