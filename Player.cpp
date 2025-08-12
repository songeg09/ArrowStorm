#include "Player.h"
#include <conio.h>
#include "Timer.h"
#include "Bow.h"

Player::Player(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
	: Creature(_InitialPosition, _ActorObject)
{
	m_Hp = PLAYER_HEALTH;
	m_FacingDir = DIRECTION::UP;
	m_MoveTimer->SetTimer(TIME::PLAYER_MOVE_SPEED, std::bind(&Player::MoveTowards, this, std::ref(m_MovingDir)));
	m_Bow = std::make_unique<Bow>(this); // 임시
}

Player::~Player()
{

}

void Player::Tick()
{
	HandleInput();
}

void Player::SetFacingDir(DIRECTION _NewFacingDir)
{
	m_FacingDir = _NewFacingDir;
	switch (_NewFacingDir)
	{
	case DIRECTION::UP:
		m_ActorObject = BOARD_OBJECT::PLAYER_UP;
		Redraw(m_CurrentPosition);
		break;
	case DIRECTION::RIGHT:
		m_ActorObject = BOARD_OBJECT::PLAYER_RIGHT;
		Redraw(m_CurrentPosition);
		break;
	case DIRECTION::DOWN:
		m_ActorObject = BOARD_OBJECT::PLAYER_DOWN;
		Redraw(m_CurrentPosition);
		break;
	case DIRECTION::LEFT:
		m_ActorObject = BOARD_OBJECT::PLAYER_LEFT;
		Redraw(m_CurrentPosition);
		break;
	default:
		break;
	}
}

void Player::TryMove()
{
	m_MoveTimer->CheckTimer();
}

void Player::HandleInput()
{
	if (_kbhit())
	{
		char Input = _getch();

		switch ((KEY_BOARD)Input)
		{
		case KEY_BOARD::W:
			m_MovingDir = DIRECTION::UP;
			TryMove();
			break;
		case KEY_BOARD::D:
			m_MovingDir = DIRECTION::RIGHT;
			TryMove();
			break;
		case KEY_BOARD::S:
			m_MovingDir = DIRECTION::DOWN;
			TryMove();
			break;
		case KEY_BOARD::A:
			m_MovingDir = DIRECTION::LEFT;
			TryMove();
			break;
		case KEY_BOARD::I:
			SetFacingDir(DIRECTION::UP);
			break;
		case KEY_BOARD::L:
			SetFacingDir(DIRECTION::RIGHT);
			break;
		case KEY_BOARD::K:
			SetFacingDir(DIRECTION::DOWN);
			break;
		case KEY_BOARD::J:
			SetFacingDir(DIRECTION::LEFT);
			break;
		case KEY_BOARD::SPACE:
			m_Bow->TryFire(GetArrowObject(), m_FacingDir);
			break;
		default:
			break;
		}
		ClearInputBuffer();
	}
	
}

BOARD_OBJECT Player::GetArrowObject()
{
	switch (m_FacingDir)
	{
	case DIRECTION::UP:
		return BOARD_OBJECT::ARROW_UP;
	case DIRECTION::RIGHT:
		return BOARD_OBJECT::ARROW_RIGHT;
	case DIRECTION::DOWN:
		return BOARD_OBJECT::ARROW_DOWN;
	case DIRECTION::LEFT:
		return BOARD_OBJECT::ARROW_LEFT;
	}
}
void Player::ClearInputBuffer()
{
	while (_kbhit()) // 버퍼에 입력이 남아 있는 동안
	{
		_getch();    // 한 글자 꺼내서 버림
	}
}
