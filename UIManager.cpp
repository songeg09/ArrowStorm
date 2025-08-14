#include "UIManager.h"
#include "DrawManager.h"

namespace UIManager {

	constexpr int UI_OFFSET_X = 1;
	constexpr int UI_OFFSET_Y = BOARD_SIZE::BOARD_HEIGHT;

	std::string GetUIIcon(UI_ICON _Icon)
	{
		switch (_Icon)
		{
		case UI_ICON::HP:
			return "¢¾";
		case UI_ICON::MP:
			return "¡Ü";
		default:
			return " ";
		}
	}

	void UpdateBowName(const std::string& _BowName)
	{
		std::string Msg = "ÀåÂøµÈ È° : " + _BowName;
		Position Pos = Position(UI_OFFSET_X, UI_OFFSET_Y);
		DrawManager::DrawAtPos(Pos, Msg);
	}

	void UpdateHp(const int _Hp)
	{
		RED
		std::string Msg = "";
		for (int i = 0; i < _Hp; ++i)
			Msg += GetUIIcon(UI_ICON::HP) + " ";

		for (int i = _Hp; i < PLAYER_HP; ++i)
			Msg += GetUIIcon(UI_ICON::BLANK) + " ";

		Position Pos = Position(1, UI_OFFSET_Y + 1);
		DrawManager::DrawAtPos(Pos, Msg);
	}

	void UpdateMp(const int _Mp)
	{
		BLUE
		std::string Msg = "";
		for (int i = 0; i < _Mp; ++i)
			Msg += GetUIIcon(UI_ICON::MP) + " ";

		for (int i = _Mp; i < PLAYER_MP; ++i)
			Msg += GetUIIcon(UI_ICON::BLANK) + " ";

		Position Pos = Position(1, UI_OFFSET_Y + 2);
		DrawManager::DrawAtPos(Pos, Msg);
	}

	void DrawUI(const std::string& _BowName, const int& _Hp, const int& _Mp)
	{
		UpdateBowName(_BowName);
		UpdateHp(_Hp);
		UpdateMp(_Mp);
	}
};