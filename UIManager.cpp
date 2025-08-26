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

	Position BOW_NAME_Text(UI_OFFSET_X, UI_OFFSET_Y);
	Position BOW_NAME(UI_OFFSET_X + 3, UI_OFFSET_Y);

	Position HP_BAR(UI_OFFSET_X, UI_OFFSET_Y+1);
	Position MP_BAR(UI_OFFSET_X, UI_OFFSET_Y+2);

	Position HP_POTION_ICON(UI_OFFSET_X + 25, UI_OFFSET_Y+1);
	Position MP_POTION_ICON(UI_OFFSET_X + 25, UI_OFFSET_Y+2);
	Position HP_POTION_NUM(UI_OFFSET_X + 26, UI_OFFSET_Y + 1);
	Position MP_POTION_NUM(UI_OFFSET_X + 26, UI_OFFSET_Y + 2);

	Position Level_Text(UI_OFFSET_X + 25, UI_OFFSET_Y);
	Position Level_Num(UI_OFFSET_X + 28, UI_OFFSET_Y);
	Position Exp_Text(UI_OFFSET_X + 32, UI_OFFSET_Y);
	Position Exp_Num(UI_OFFSET_X + 35, UI_OFFSET_Y);

	Position Skill_CoolTime_Text(UI_OFFSET_X + 12, UI_OFFSET_Y);
	Position Skill_CollTime(UI_OFFSET_X + 20, UI_OFFSET_Y);

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
		player = dynamic_cast<Player*>(ArrowStorm::GetInstance().GetCreatureArr()[0].get());
		return player;
	}

	void UpdateBowName()
	{
		if (Player* player = GetPlayerPtr())
		{
			std::string Msg = player->GetBow()->GetName();
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
		RED
			DrawManager::DrawAtPos(HP_POTION_ICON, GetUIIcon(UI_ICON::POTION));
		BLUE
			DrawManager::DrawAtPos(MP_POTION_ICON, GetUIIcon(UI_ICON::POTION));
		ORIGINAL
			DrawManager::DrawAtPos(BOW_NAME_Text, "ÀåÂøµÈ È°: ");
			DrawManager::DrawAtPos(Level_Text, "Level: ");
			DrawManager::DrawAtPos(Exp_Text, "Exp: ");
			DrawManager::DrawAtPos(Skill_CoolTime_Text, "Skill Cool Time:");

		UpdateBowName();
		UpdateHpBar();
		UpdateMpBar();
		UpdateLevel();
		UpdateExp();
		UpdateHpPotions();
		UpdateMpPotions();
	}


	void UpdateLevel()
	{
		if (Player* player = GetPlayerPtr())
		{
			ORIGINAL
				DrawManager::DrawAtPos(Level_Num, Format02(player->GetLevel()));
		}
	}

	void UpdateSkillCoolTime()
	{
		if (Player* player = GetPlayerPtr())
		{
			int CoolTime = player->GetBow()->GetSkillCoolTime();
			if (CoolTime < 0) return;

			std::string Msg = std::to_string(CoolTime / 10) + "." + std::to_string(CoolTime % 10);
			ORIGINAL
				DrawManager::DrawAtPos(Skill_CollTime, Msg);
		}
	}

	void UpdateExp()
	{
		if (Player* player = GetPlayerPtr())
		{
			std::string Msg = std::to_string(player->GetExp()) + "/" + std::to_string(player->GetLevel() * 5);
			ORIGINAL
				DrawManager::DrawAtPos(Exp_Num, Msg);
		}
	}
};