#pragma once
#include "Mecro.h"
#include <iostream>

namespace UIManager
{

	std::string GetUIIcon(UI_ICON _Icon);

	void UpdateBowName();

	void UpdateHpBar();
	void UpdateMpBar();
	void UpdateStatBar(const UI_ICON _Icon, const Position& _Pos, int _Num, int _Max);
	std::string MakeBar(int _Num, int _Max, UI_ICON _Icon);
	
	std::string Format02(int _Num);
	void UpdateHpPotions();
	void UpdateMpPotions();
	void UpdateLevel();
	void UpdateExp();
	void UpdateAttackSpeed();
	void UpdateDamage();

	void DrawUI();

	void UpdateSkillCoolTime();
};
