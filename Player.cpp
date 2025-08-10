#include "Player.h"
#include <conio.h>
#include "Timer.h"

Player::Player() 
	: Creature(Position(BOARD_SIZE::BOARD_WIDHT / 2, BOARD_SIZE::BOARD_HEIGHT / 2) , BOARD_OBJECT::PLAYER_UP)
{
	m_FacingDir = DIRECTION::UP;
	m_MoveTimer->SetTimer(TIME::PLAYER_MOVE_SPEED, std::bind(&Player::HandleMoveInput, this));
}

Player::~Player()
{

}

void Player::SetFacingDir(DIRECTION _NewFacingDir)
{
	m_FacingDir = _NewFacingDir;
	switch (_NewFacingDir)
	{
	case DIRECTION::UP:
		m_ActorObject = BOARD_OBJECT::PLAYER_UP;
		return;
	case DIRECTION::RIGHT:
		m_ActorObject = BOARD_OBJECT::PLAYER_RIGHT;
		return;
	case DIRECTION::DOWN:
		m_ActorObject = BOARD_OBJECT::PLAYER_DOWN;
		return;
	case DIRECTION::LEFT:
		m_ActorObject = BOARD_OBJECT::PLAYER_LEFT;
		return;
	default:
		return;
	}
}


Position Player::TryMove()
{
	Position NewPosition{};
	if (_kbhit())
	{
		// 키가 눌렸더라도 시간이 지나지 않았으면 -1,-1 반환
		NewPosition = m_MoveTimer->CheckTimer();
		ClearInputBuffer();
	}
	return NewPosition;
}

Position Player::HandleMoveInput()
{
	char Input = _getch();

	Position Result;
	switch ((KEY_BOARD)Input)
	{
	case KEY_BOARD::W:
		Result = TryMoveTowards(DIRECTION::UP);
		break;
	case KEY_BOARD::D:
		Result = TryMoveTowards(DIRECTION::RIGHT);
		break;
	case KEY_BOARD::S: 
		Result = TryMoveTowards(DIRECTION::DOWN);
		break;
	case KEY_BOARD::A:
		Result = TryMoveTowards(DIRECTION::LEFT);
		break;
	default:
		break;
	}

	return Result;
}

DIRECTION Player::TryTurn()
{
	if (_kbhit())
	{
		char Input = _getch();

		DIRECTION Result;
		switch ((KEY_BOARD)Input)
		{
		case KEY_BOARD::I:
			Result = DIRECTION::UP;
			break;
		case KEY_BOARD::L:
			Result = DIRECTION::RIGHT;
			break;
		case KEY_BOARD::K:
			Result = DIRECTION::DOWN;
			break;
		case KEY_BOARD::J:
			Result = DIRECTION::LEFT;
			break;
		default:
			Result = DIRECTION::NEUTRAL;
		}
		ClearInputBuffer();
		return Result;
	}

	return DIRECTION::NEUTRAL;
}

void Player::ClearInputBuffer()
{
	while (_kbhit()) // 버퍼에 입력이 남아 있는 동안
	{
		_getch();    // 한 글자 꺼내서 버림
	}
}

FireRequest Player::TryFire()
{
	FireRequest Request;
	if (_kbhit())
	{
		char Input = _getch();

		if ((KEY_BOARD)Input == KEY_BOARD::SPACE)
		{
			Request.m_InitialPosition = m_CurrentPosition + m_FacingDir;
			Request.m_MovingDirection = m_FacingDir;
			Request.m_Object = BOARD_OBJECT::ARROW_LEFT;
		}

		ClearInputBuffer();
	}
	return Request;
}