#pragma once
#include "Creature.h"

class Player : public Creature
{

private:
	DIRECTION m_FacingDir;
	DIRECTION m_MovingDir;
	std::unique_ptr<class Bow> m_Bow;

	void HandleInput();
	void ClearInputBuffer();
	void SetFacingDir(DIRECTION _NewFacingDir);
	BOARD_OBJECT GetArrowObject();

	void TryMove() override;

public:
	Player(const Position _InitialPosition, const BOARD_OBJECT _ActorObject);
	~Player();

	DIRECTION GetFacingDir() {return m_FacingDir;}
	
	virtual void Tick() override;

};

