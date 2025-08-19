#include "Monster.h"
#include "ArrowStorm.h"
#include "Timer.h"
#include <queue>

Monster::Monster(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
	:Creature(_InitialPosition, _ActorObject)
{
	m_Target = ArrowStorm::GetInstance().GetCreatureArr()[0].get();
	m_AttackTimer = std::make_unique<Timer>();
}

Monster::~Monster()
{

}

void Monster::TryAttack()
{
	m_AttackTimer->CheckTimer();
}

void Monster::MeleeAttack()
{
	if (m_Target)
	{
		m_Target->TakeDamage(m_MeleeDamage);
	}
}

void Monster::FollowTarget()
{
	if (m_Target)
	{
		Position NextPos = GetNextPosition();
		if (m_CurrentPosition == NextPos) return;
		Redraw(NextPos);
	}
}

Position Monster::GetNextPosition()
{
	BOARD_OBJECT(&BoardCopy)[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH] = ArrowStorm::GetInstance().MakeSnapshot();

	Position TargetPos = m_Target->GetCurrentPosition();
	Position SlimePos = m_CurrentPosition;

	std::queue<Position> queue;
	queue.push(TargetPos);

	Position Result = SlimePos;
	while (!queue.empty())
	{
		Position CurrentPos = queue.front(); queue.pop();

		if (Position::Distance(SlimePos, CurrentPos) == 1 && CurrentPos != TargetPos)
		{
			Result = CurrentPos;
			break;
		}

		for (Position Dir : Directions)
		{
			Position NextPos = CurrentPos + Dir;

			if (!ArrowStorm::GetInstance().GetMap().InRange(NextPos)) continue;
			if (BoardCopy[NextPos.m_y][NextPos.m_x] == BOARD_OBJECT::WALL) continue;
			BoardCopy[NextPos.m_y][NextPos.m_x] = BOARD_OBJECT::WALL;
			queue.push(NextPos);
		}
	}

	return Result;
}