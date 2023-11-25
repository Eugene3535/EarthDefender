#pragma once
#include "System.h"

class UI_EXP_BAR : public System
{
private:

	int level;
	float experience, EXPERIENCE;

	Shape shpLine;
	Shape shpBonus;
	Shape shpIco;
	Shape shpPlato;
	Shape shpBar;
	sf::Text text;
	const float sizex_line;

public:

	UI_EXP_BAR(uint level, uint experience) : 
		level(level), 
		experience(experience), 
		EXPERIENCE(100+(level*100)),
		sizex_line(25*scr_1)
	{
		ConstructShape(shpIco, v2f(-15,-43.25), v2f(3.5,3.5), texture->UI_Ico);
		ConstructShape(shpBar, v2f(1.75,-43.25), v2f(30,3.5), texture->UI_Bar);
		ConstructShape(shpBonus, v2f(-15,-43.25), v2f(2.5,2.5), texture->Bonus_Experience[0]);
		ConstructShape(shpPlato, v2f(-15,-43.25), v2f(3.2,3.2), texture->Bonus_Plato);
		ConstructShape(shpLine, v2f(-13.25,-43.25), v2f(0,3.5), texture->UI_EXP_Line);
		shpLine.setOrigin(0,shpLine.getOrigin().y);
		ConstructText(text, shpBar.getPosition(), 1.65, "Level " + to_string(level) + " : " + to_string(int(this->experience)) + " / " + to_string(int(EXPERIENCE)) + " exp.", font_freshman, CLR::White);
	}

	virtual void Update()
	{
		shpPlato.rotate(0.03*time);
	}

	virtual int getLevel() const { return level; }

	virtual void Draw()
	{
		wnd->draw(shpIco);
		wnd->draw(shpLine);
		wnd->draw(shpBar);
		wnd->draw(shpPlato);
		wnd->draw(shpBonus);
		wnd->draw(text);
	}

	virtual bool addExp(int experience)
	{
		const int l = level;
		this->experience += experience;
		if(this->experience >= EXPERIENCE)
		{
			this->experience -= EXPERIENCE;
			level++;
			EXPERIENCE = 100 + ( level * 100 );
		}
		shpLine.setSize(v2f(sizex_line*(this->experience/EXPERIENCE), shpLine.getSize().y));
		shpLine.setTextureRect(sf::IntRect(0,0,600*(this->experience/EXPERIENCE),40));
		ConstructText(text, shpBar.getPosition(), 2.f, "Level " + to_string(level) + " : " + to_string(int(this->experience)) + " of " + to_string(int(EXPERIENCE)) + " exp.", font_freshman, CLR::White);
		if(l < level) return true;
		return false;
	}

	virtual ~UI_EXP_BAR() {}
};