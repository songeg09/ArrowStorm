#include "MapManager.h"
#include "ArrowStorm.h"
#include "Creature.h"
#include "Projectile.h"
#include "DrawManager.h"

MapManager& MapManager::GetInstance()
{
	static MapManager Manager;
	return Manager;
}

bool MapManager::IsValidPos(const Position& Pos)
{
	// 범위 밖
	if (!(0 <= Pos.m_x && Pos.m_x < BOARD_SIZE::BOARD_WIDTH && 0 <= Pos.m_y && Pos.m_y < BOARD_SIZE::BOARD_HEIGHT))
		return false;
	// 벽 충돌
	if (GetInstance().m_Board[Pos.m_y][Pos.m_x] == BOARD_OBJECT::WALL)
		return false;

	return true;
}

bool MapManager::InRange(const Position& _Position)
{
	return (0 <= _Position.m_x && _Position.m_x < BOARD_SIZE::BOARD_WIDTH
		&& 0 <= _Position.m_y && _Position.m_y < BOARD_SIZE::BOARD_HEIGHT);
}

BoardArr& MapManager::MakeSnapshot()
{
	static BoardArr Snapshot{};

	std::memcpy(Snapshot, MapManager::GetBoard(),
		sizeof(BOARD_OBJECT) * BOARD_SIZE::BOARD_HEIGHT * BOARD_SIZE::BOARD_WIDTH);

	for (int index = 0; index < ArrowStorm::GetCreatureArr().size(); ++index)
	{
		if (ArrowStorm::GetCreatureArr()[index] == nullptr) continue;

		Position CreatruePos = ArrowStorm::GetCreatureArr()[index]->GetCurrentPosition();
		Snapshot[CreatruePos.m_y][CreatruePos.m_x] = BOARD_OBJECT::WALL;
	}

	return Snapshot;
}

BOARD_OBJECT(*MapManager::GetBoard())[BOARD_SIZE::BOARD_WIDTH]
{
	return GetInstance().m_Board;
}

void MapManager::DrawFullBoard()
{
	// 벽 그리기
	std::string Line;
	for (int y = 0; y < BOARD_SIZE::BOARD_HEIGHT; ++y)
	{
		DrawManager::gotoxy(0, y);
		Line = "";
		for (int x = 0; x < BOARD_SIZE::BOARD_WIDTH; ++x)
		{
			Line += DrawManager::GetObjectIcon(MapManager::GetBoard()[y][x]);
		}
		std::cout << Line;
	}

	// 투사체 그리기
	for (std::list<std::unique_ptr<Projectile>>::iterator it = ArrowStorm::GetProjectileList().begin(); it != ArrowStorm::GetProjectileList().end(); ++it)
	{
		Position CreaturePos = (*it)->GetCurrentPosition();
		BOARD_OBJECT CreatureObj = (*it)->GetActorObject();
		DrawManager::DrawObjectAtPosition(CreaturePos, CreatureObj);
	}

	// 크리쳐들 그리기
	for (int id = 0; id < ArrowStorm::GetCreatureArr().size(); ++id)
	{
		if (Creature* Creature = ArrowStorm::GetCreatureArr()[id].get())
		{
			Position CreaturePos = Creature->GetCurrentPosition();
			BOARD_OBJECT CreatureObj = Creature->GetActorObject();
			DrawManager::DrawObjectAtPosition(CreaturePos, CreatureObj);
		}
	}
}