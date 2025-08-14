#include "Slime.h"
#include "Timer.h"
#include <queue>
#include "ArrowStorm.h"
#include "MapManager.h"

Slime::Slime(const Position _InitialPos)
	:Monster(_InitialPos, BOARD_OBJECT::SLIME)
{
	m_MoveTimer = std::make_unique<Timer>();
	m_MoveTimer->SetTimer(TIME::SLIME_MOVE_SPEED, std::bind(&Slime::FollowTarget, this));
}

Slime::~Slime()
{

}

void Slime::Tick()
{
	TryMove();
}

void Slime::FollowTarget()
{
	if (m_Target)
	{
		Position NextPos = GetNextPosition();
		if (m_CurrentPosition == NextPos) return;
		Redraw(NextPos);
	}
}

Position Slime::GetNextPosition()
{
	MarkingsForBFS(true);

	Position TargetPos = m_Target->GetCurrentPosition();
	Position SlimePos = m_CurrentPosition;

	bool visited[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH]{};
	std::queue<Position> queue;
	queue.push(TargetPos);
	visited[TargetPos.m_y][TargetPos.m_x] = true;

	Position Result = SlimePos;
	while (!queue.empty())
	{
		Position CurrentPos = queue.front(); queue.pop();

		if (SlimePos - CurrentPos == 1)
		{
			Result = CurrentPos;
			break;
		}

		for (Position Dir : Directions)
		{
			Position NextPos = CurrentPos + Dir;

			if (!MapManager::IsValidPosition(NextPos)) continue;
			if (visited[NextPos.m_y][NextPos.m_x]) continue;
			visited[NextPos.m_y][NextPos.m_x] = true;
			queue.push(NextPos);
		}
	}

	MarkingsForBFS(false);
	return Result;
}

void Slime::MarkingsForBFS(bool option)
{
	for (int index = 1; index < ArrowStorm::GetCreatureArr().size(); ++index)
	{
		if (ArrowStorm::GetCreatureArr()[index] == nullptr) continue;

		Position CreatruePos = ArrowStorm::GetCreatureArr()[index]->GetCurrentPosition();
		if (option)
			MapManager::GetBoard()[CreatruePos.m_y][CreatruePos.m_x] = BOARD_OBJECT::WALL;
		else
			MapManager::GetBoard()[CreatruePos.m_y][CreatruePos.m_x] = BOARD_OBJECT::EMPTY;
		
	}
}