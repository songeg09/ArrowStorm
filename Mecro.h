#pragma once
#define NOMINMAX
#include <limits>
#include <iostream>
#include <string>

constexpr int MAX_HP_POTION = 99;
constexpr int MAX_MP_POTION = 99;

constexpr int PLAYER_MAX_HP = 10;
constexpr int PLAYER_MAX_MP = 10;
constexpr int SLIME_HP = 3;

constexpr int SKELETON_HP = 5;
constexpr int SKELETON_MELEE_DAMAGE = 3;

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
	CHEST,
	BOW,
	DOOR,
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
	POTION,
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

enum DIRECTION
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	NEUTRAL,
};

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

	static int Distance(const Position& p1, const  Position& p2)
	{
		return abs(p1.m_x - p2.m_x) + abs(p1.m_y - p2.m_y);
	}
	
	Position operator+(const int _Num)
	{
		return Position(m_x + _Num, m_y + _Num);
	}

	// Direction from p1 to p2
	static DIRECTION GetDirection(const Position& p1, const Position& p2)
	{
		int dx = (p1.m_x - p2.m_x);
		int dy = (p1.m_y - p2.m_y);

		if (abs(dx) < abs(dy))
		{
			return (dy > 0) ? DIRECTION::UP : DIRECTION::DOWN;
		}
		else
		{
			return (dx > 0) ? DIRECTION::LEFT : DIRECTION::RIGHT;
		}
	}

};

extern Position Directions[4];

BOARD_OBJECT GetArrowObject(const DIRECTION _AmingDir);

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
	L = 108,
	ESCAPE = 27,
};

enum TIME
{
	DEFAULT_PROJECTILE_SPEED = 100,
	
	SLIME_MOVE_SPEED = 1500,
	SLIME_ATTACK_COOL = 2000,

	SKELETON_MOVE_SPEED = 1000,
	SKELETON_ATTACK_COOL = 2000,

	PLAYER_MOVE_SPEED = 150,
	
	DEFAULT_ATTACK_COOL = 1000,
	DEFAULT_SKILL_COOL = 5000,
	MINIMUM_ATTACK_COOL = 300,
	
	FAST_ATTACK_COOL = 500,
	FAST_SKILL_COOL = 2500,
};

enum POTION_TYPE
{
	HP = 0,
	MP = 1,
};

enum BOW_TYPE
{
	BASIC = 0,
	TRIPLE,
	FAST,
	BOW_TYPE_COUNT,
};

enum MONSTER_TYPE
{
	SLIME_TYPE = 0,
	SKELETON_TYPE = 1,
	COUNT
};

enum MONSTER_EXP
{
	SLIME_EXP = 1,
	SKELETON_EXP = 3
};