#include "Player.h"
#include <conio.h>
#include "Timer.h"
#include "Bow.h"
#include "UIManager.h"

Player::Player(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
	: Creature(_InitialPosition, _ActorObject)
{
	m_Hp = PLAYER_MAX_HP;
	m_Mp = PLAYER_MAX_MP;
	m_HpPotion = 0;
	m_MpPotion = 0;

	m_FacingDir = DIRECTION::UP;
	m_MoveTimer->SetTimer(TIME::PLAYER_MOVE_SPEED, std::bind(&Player::MoveTowards, this, std::ref(m_MovingDir)));
	m_Bow = std::make_unique<Bow>(this); // 임시

	//UIManager::DrawUI();
}

Player::~Player()
{

}

void Player::TakeDamage(const int _Damage)
{
	Creature::TakeDamage(_Damage);
	UIManager::UpdateHpBar();
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
		case KEY_BOARD::U:
			m_Bow->TryFire(m_FacingDir);
			break;
		case KEY_BOARD::O:
			if (m_Mp > 0)
			{
				m_Bow->TrySkill(m_FacingDir);
			}
			break;
		case KEY_BOARD::ONE:
			TryUsePotion(POTION_TYPE::HP);
			break;
		case KEY_BOARD::TWO:
			TryUsePotion(POTION_TYPE::MP);
			break;
		default:
			break;
		}
		ClearInputBuffer();
	}
	
}

void Player::ClearInputBuffer()
{
	while (_kbhit()) // 버퍼에 입력이 남아 있는 동안
	{
		_getch();    // 한 글자 꺼내서 버림
	}
}

void Player::EarnPotion(POTION_TYPE _PotionType)
{
	if (_PotionType == POTION_TYPE::HP)
		UpdatePotion(m_HpPotion, MAX_HP_POTION, &UIManager::UpdateHpPotions);
	else
		UpdatePotion(m_MpPotion, MAX_MP_POTION, &UIManager::UpdateMpPotions);
}

void Player::UpdatePotion(int& _Potion, int _MaxVal, std::function<void()> _UpdateUI)
{
	_Potion++;
	if (_Potion > _MaxVal)
		_Potion = _MaxVal;

	_UpdateUI();
}

void Player::TryUsePotion(POTION_TYPE _PotionType)
{
	if (_PotionType == POTION_TYPE::HP)
	{
		if (m_HpPotion > 0)
		{
			m_HpPotion--;
			m_Hp += 3;
			if (m_Hp > PLAYER_MAX_HP)
				m_Hp = PLAYER_MAX_HP;
			UIManager::UpdateHpBar();
			UIManager::UpdateHpPotions();
		}
	}
	else
	{
		if (m_MpPotion > 0)
		{
			m_MpPotion--;
			m_Mp += 3;
			if (m_Mp > PLAYER_MAX_MP)
				m_Mp = PLAYER_MAX_MP;
			UIManager::UpdateMpBar();
			UIManager::UpdateMpPotions();
		}
	}
}

void Player::SetBow(std::unique_ptr<Bow> _NewBow)
{ 
	m_Bow = std::move(_NewBow); 
	UIManager::UpdateBowName();
};

void Player::UseMp() 
{
	m_Mp--; 
	UIManager::UpdateMpBar();
}