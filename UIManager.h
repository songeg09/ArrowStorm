#pragma once
#include "Mecro.h"
#include <iostream>

namespace UIManager
{

	std::string GetUIIcon(UI_ICON _Icon);

	void UpdateBowName(const std::string& _BowName);

	void UpdateHp(const int _Hp);

	void UpdateMp(const int _Mp);

	void DrawUI(const std::string& _BowName, const int& _Hp, const int& _Mp);
};
