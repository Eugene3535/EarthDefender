#pragma once
#include "System.h"

class UI_Chance_Drop : public System
{
private:

	int chance, dchance;
	sf::Text text;
	Shape shpIco;
	Shape shpCost;

public:

	Shape shpBar;

	UI_Chance_Drop(int chance) : chance(chance), dchance(rand()%100+1)
	{
		ConstructShape(shpBar, v2f(-34,-45), v2f(25,7), texture->UI_Bar);
		ConstructShape(shpIco, v2f(-50,-45), v2f(7,7), texture->UI_Ico);
		ConstructText(text, v2f(-34,-45)*scr_1, 2, "PowerUp Drop: " + to_string(chance) + " of " + to_string(dchance), font_freshman, sf::Color::White);
		ConstructShape(shpCost, v2f(-50,-45), v2f(7,7), texture->UI_Chance_Drop);
	}

	virtual void Update()
	{
		// 
	}

	virtual void Draw()
	{
		wnd->draw(shpBar);
		wnd->draw(shpIco);
		wnd->draw(shpCost);
		wnd->draw(text);
	}

	virtual bool IsDrop(int add)
	{
		chance += add;
		ConstructText(text, v2f(-34,-45)*scr_1, 2, "PowerUp Drop: " + to_string(chance) + " of " + to_string(dchance), font_freshman, sf::Color::White);
		
		if(chance >= dchance)
		{
			chance = 0;
			dchance = rand()%100+1;
			ConstructText(text, v2f(-34,-45)*scr_1, 2, "PowerUp Drop: " + to_string(chance) + " of " + to_string(dchance), font_freshman, sf::Color::White);
			return true;
		}
		return false;
	}

	virtual ~UI_Chance_Drop() {}
};