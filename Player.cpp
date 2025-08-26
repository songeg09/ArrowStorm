#include "Player.h"
#include <conio.h>
#include "Timer.h"
#include "Bow.h"
#include "UIManager.h"
#include "ArrowStorm.h"
#include "DrawManager.h"

Player::Player(const Position _InitialPosition, const BOARD_OBJECT _ActorObject)
	: Creature(_InitialPosition, _ActorObject)
{
	m_HpPotion = 0;
	m_MpPotion = 0;
	m_Level = 1;
	m_Exp = 0;
	m_CurrentMaxHp = 3;
	m_CurrentMaxMp = 3;
	m_Hp = m_CurrentMaxHp;
	m_Mp = m_CurrentMaxMp;

	m_RangedDamage = 0;
	m_AttackSpeed = DEFAULT_ATTACK_COOL;

	m_FacingDir = DIRECTION::UP;
	m_MoveTimer->SetTimer(TIME::PLAYER_MOVE_SPEED, std::bind(&Player::MoveTowards, this, std::ref(m_MovingDir)));
	m_Bow = std::make_unique<Bow>(); // 임시
	m_Bow->SetOwner(this);
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
	UIManager::UpdateSkillCoolTime();
}

void Player::TryMove()
{
	if (m_MoveTimer->CheckTimer())
	{
		ArrowStorm::GetInstance().ItemCheck(this);
		ArrowStorm::GetInstance().MapChangeCheck(m_CurrentPosition);
	}
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
		case KEY_BOARD::ESCAPE:
			ArrowStorm::GetInstance().EndGame();
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
			if (m_Hp > m_CurrentMaxHp)
				m_Hp = m_CurrentMaxHp;
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
			if (m_Mp > m_CurrentMaxMp)
				m_Mp = m_CurrentMaxMp;
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

void Player::EarnExp(int _Exp)
{
	m_Exp += _Exp;

	int ExpRequired = m_Level * 5;
	while (ExpRequired <= m_Exp)
	{
		LevelUp();
		m_Exp -= ExpRequired;
		ExpRequired = m_Level * 5;
	}

	UIManager::UpdateExp();
}

void Player::LevelUp()
{
	m_Level++;
	UIManager::UpdateLevel();

	// 데미지 증가
	SetRangedDamage(m_RangedDamage+1);
	UIManager::UpdateDamage();

	// Hp 또는 Mp 최대치 증가 선택
	IncreaseHpMp();

	// 체력및 마나 풀로 채워주기
	m_Hp = m_CurrentMaxHp;
	m_Mp = m_CurrentMaxMp;
	UIManager::UpdateHpBar();
	UIManager::UpdateMpBar();

	// 5레벨 마다 공속 감소
	if (m_Level % 3 == 0)
	{
		// 임의로 두배 빠르게 만들어주기
		SetAttackSpeed(m_AttackSpeed *= 0.9);
		UIManager::UpdateAttackSpeed();
	}
}

void Player::IncreaseHpMp()
{
	std::string Msg = "Level Up! Hp증가: 1, Mp증가: else";
	if (DrawManager::DrawConfirmPopup(Msg))
	{
		m_CurrentMaxHp++;
		if (m_CurrentMaxHp > PLAYER_MAX_HP)
			m_CurrentMaxHp = PLAYER_MAX_HP;
	}
	else
	{
		m_CurrentMaxMp++;
		if (m_CurrentMaxMp > PLAYER_MAX_MP)
			m_CurrentMaxMp = PLAYER_MAX_MP;
	}
	ArrowStorm::GetInstance().DrawFullBoard();
}

void Player::SetRangedDamage(int _RangedDamage)
{
	m_RangedDamage = _RangedDamage; 
	m_Bow->SetDamage(_RangedDamage);
}

void Player::SetAttackSpeed(int _AttackSpeed)
{ 
	m_AttackSpeed = _AttackSpeed;
	if (m_AttackSpeed < TIME::MINIMUM_ATTACK_COOL) m_AttackSpeed = TIME::MINIMUM_ATTACK_COOL;
	m_AttackSpeed = _AttackSpeed; 
	m_Bow->SetAttackTimerCool(m_AttackSpeed);
}