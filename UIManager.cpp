#include "UIManager.h"
#include "DrawManager.h"
#include "Player.h"
#include "Bow.h"
#include "Creature.h"
#include "ArrowStorm.h"
#include "Mecro.h"

#include <sstream>
#include <iomanip>

namespace UIManager {

	constexpr int UI_OFFSET_X = 1;
	constexpr int UI_OFFSET_Y = BOARD_SIZE::BOARD_HEIGHT;

	Position BOW_NAME(UI_OFFSET_X, UI_OFFSET_Y);
	Position HP_BAR(UI_OFFSET_X, UI_OFFSET_Y+1);
	Position MP_BAR(UI_OFFSET_X, UI_OFFSET_Y+2);
	Position HP_POTION_ICON(UI_OFFSET_X + 25, UI_OFFSET_Y+1);
	Position MP_POTION_ICON(UI_OFFSET_X + 25, UI_OFFSET_Y+2);
	Position HP_POTION_NUM(UI_OFFSET_X + 26, UI_OFFSET_Y + 1);
	Position MP_POTION_NUM(UI_OFFSET_X + 26, UI_OFFSET_Y + 2);

	std::string GetUIIcon(UI_ICON _Icon)
	{
		switch (_Icon)
		{
		case UI_ICON::HP:
			return "¢¾";
		case UI_ICON::MP:
			return "¡Ü";
		case UI_ICON::POTION:
			return "¢Í";
		default:
			return "  ";
		}
	}

	Player* GetPlayerPtr()
	{
		Player* player = nullptr;
		player = dynamic_cast<Player*>(ArrowStorm::GetCreatureArr()[0].get());
		return player;
	}

	void UpdateBowName()
	{
		if (Player* player = GetPlayerPtr())
		{
			std::string Msg = "ÀåÂøµÈ È° : " + player->GetBow()->GetName();
			DrawManager::DrawAtPos(BOW_NAME, Msg);
		}
	}

	void UpdateHpBar()
	{
		if (Player* player = GetPlayerPtr())
		{
			RED
			UpdateStatBar(UI_ICON::HP, HP_BAR, player->GetHp(), PLAYER_MAX_HP);
		}
	}

	void UpdateMpBar()
	{
		if (Player* player = GetPlayerPtr())
		{
			BLUE
			UpdateStatBar(UI_ICON::MP, MP_BAR, player->GetMp(), PLAYER_MAX_MP);
		}
	}

	void UpdateStatBar(const UI_ICON _Icon, const Position& _Pos, int _Num, int _Max)
	{
		DrawManager::DrawAtPos(_Pos, MakeBar(_Num, _Max, _Icon));
	}

	std::string MakeBar(int _Num, int _Max, UI_ICON _Icon)
	{
		std::string Msg = "";
		for (int i = 0; i < _Num; ++i)
			Msg += GetUIIcon(_Icon) + " ";

		for (int i = _Num; i < _Max; ++i)
			Msg += GetUIIcon(UI_ICON::BLANK) + " ";

		return Msg;
	}

	std::string Format02(int _Num) 
	{
		std::ostringstream oss;
		oss << std::setw(2) << std::setfill('0') << _Num;
		return oss.str();
	}

	void UpdateHpPotions()
	{
		ORIGINAL
		if (Player* player = GetPlayerPtr())
		{
			std::string Msg = " : " + Format02(player->GetHpPotion());
			DrawManager::DrawAtPos(HP_POTION_NUM, Msg);
		}
	}
	
	void UpdateMpPotions()
	{
		ORIGINAL
		if (Player* player = GetPlayerPtr())
		{
			std::string Msg = " : " + Format02(player->GetMpPotion());
			DrawManager::DrawAtPos(MP_POTION_NUM, Msg);
		}
	}

	void DrawUI()
	{
		UpdateBowName();
		UpdateHpBar();
		UpdateMpBar();
		DrawPotionIcons();
		UpdateHpPotions();
		UpdateMpPotions();
	}

	void DrawPotionIcons()
	{
		RED
		DrawManager::DrawAtPos(HP_POTION_ICON, GetUIIcon(UI_ICON::POTION));

		BLUE
		DrawManager::DrawAtPos(MP_POTION_ICON, GetUIIcon(UI_ICON::POTION));
	}
};