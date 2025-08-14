#pragma once
#define NOMINMAX
#include <limits>
#include <iostream>
#include <string>

constexpr int PLAYER_HP = 10;
constexpr int PLAYER_MP = 10;
constexpr int SLIME_HP = 3;

constexpr int DEFAULT_DAMAGE = 1;

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
	CHEST,
	PLAYER_UP,
	PLAYER_RIGHT,
	PLAYER_DOWN,
	PLAYER_LEFT,
	ARROW_UP,
	ARROW_RIGHT,
	ARROW_DOWN,
	ARROW_LEFT,
	SKELETON,
	SLIME,

};

enum class UI_ICON
{
	HP,
	MP,
	BLANK,
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
	
	bool operator!=(const Position& other) const
	{
		return (m_x != other.m_x || m_y != other.m_y);
	}

	Position operator+(const Position& other)
	{
		return Position(m_x + other.m_x, m_y + other.m_y);
	}

	static int Distance(const Position& p1, Position& p2)
	{
		return abs(p1.m_x - p2.m_x) + abs(p1.m_y - p2.m_y);
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
	U = 117,
	O = 111,
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
	
	SLIME_MOVE_SPEED = 1000,
	SLIME_ATTACK_COOL = 2000,

	PLAYER_MOVE_SPEED = 300,
	DEFAULT_ATTACK_COOL = 1000,
	DEFAULT_SKILL_COOL = 5000,
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