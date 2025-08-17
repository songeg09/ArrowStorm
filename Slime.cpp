#include "Slime.h"
#include "Timer.h"
#include <queue>
#include "ArrowStorm.h"
#include "MapManager.h"

Slime::Slime(const Position _InitialPos)
	:Monster(_InitialPos, BOARD_OBJECT::SLIME)
{
	m_Hp = SLIME_HP;
	m_MoveTimer->SetTimer(TIME::SLIME_MOVE_SPEED, std::bind(&Slime::FollowTarget, this));
	m_AttackTimer->SetTimer(TIME::SLIME_ATTACK_COOL, std::bind(&Slime::MeleeAttack, this));
	m_MeleeDamage = DEFAULT_DAMAGE;
}

Slime::~Slime()
{

}

void Slime::Tick()
{
	if (Position::Distance(m_Target->GetCurrentPosition(), m_CurrentPosition) > 1)
	{
		TryMove();
	}
	else
	{
		TryAttack();
	}
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
	BOARD_OBJECT(&BoardCopy)[BOARD_SIZE::BOARD_HEIGHT][BOARD_SIZE::BOARD_WIDTH] = MapManager::MakeSnapshot();

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

			if (!MapManager::InRange(NextPos)) continue;
			if (BoardCopy[NextPos.m_y][NextPos.m_x] == BOARD_OBJECT::WALL) continue;
			BoardCopy[NextPos.m_y][NextPos.m_x] = BOARD_OBJECT::WALL;
			queue.push(NextPos);
		}
	}

	return Result;
}