#pragma once
#define NOMINMAX
#include <limits>
#include <iostream>
#include <string>

constexpr int PLAYER_HEALTH = 100;
constexpr int DEFAULT_DAMAGE = 10;

enum ASPECT_RATIO
{
	SCREEN_WIDTH = 100,
	SCREEN_HEIGHT = 30
};

enum BOARD_SIZE
{
	BOARD_WIDTH = 50,
	BOARD_HEIGHT = 25
};

enum BOARD_OBJECT
{
	EMPTY,
	WALL,
	DOOR,
	PLAYER_UP,
	PLAYER_RIGHT,
	PLAYER_DOWN,
	PLAYER_LEFT,
	ARROW_UP,
	ARROW_RIGHT,
	ARROW_DOWN,
	ARROW_LEFT,
};

enum POPUP_SIZE
{
	POPUP_WIDTH = 40,
	POPUP_HEIGHT = 10,
};

enum POPUP_CHOICE
{
	YES = 1
};

/*
	integer 타입을 인풋을 올바르게 받아서
	cin 버퍼에 문제가 생기지 않도록 하는 함수
*/
int GetSafeInput(int& input);

struct Position
{
	int m_x;
	int m_y;

	Position()
	{
		m_x = -1; 
		m_y = -1;
	}

	Position(int _x, int _y)
	{
		m_x = _x;
		m_y = _y;
	}

	bool operator==(const Position& other) const
	{
		return m_x == other.m_x && m_y == other.m_y;
	}

	Position operator+(const Position& other)
	{
		return Position(m_x + other.m_x, m_y + other.m_y);
	}
	
	Position operator+(const int _Num)
	{
		return Position(m_x + _Num, m_y + _Num);
	}

};

extern Position Directions[4];

enum DIRECTION
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	NEUTRAL,
};

enum KEY_BOARD
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	SPACE = 32,
	SHIFT = 15,
	ONE = 49,
	TWO = 50,
	I = 105,
	J = 106, 
	K = 107,
	L = 108
};

enum TIME
{
	DEFAULT_PROJECTILE_SPEED = 100,
	DEFAULT_ATTACK_SPEED = 1000,
	PLAYER_MOVE_SPEED = 500,
};

enum HP
{
	DAMAGE_DEFAULT = 10,
	HEALTH_PLAYER = 100,
	HEALTH_MONSTER = 10,
};


struct FireRequest
{
	Position m_InitialPosition;
	DIRECTION m_MovingDirection;
	BOARD_OBJECT m_Object;

	FireRequest()
	{
		m_InitialPosition = Position();
		m_MovingDirection = DIRECTION::NEUTRAL;
		m_Object = BOARD_OBJECT::EMPTY;
	}

	FireRequest(const Position _InitialPosition, const DIRECTION _MovingDirection, const BOARD_OBJECT _Object)
	{
		m_InitialPosition = _InitialPosition;
		m_MovingDirection = _MovingDirection;
		m_Object = _Object;
	}
};