#pragma once
#include "System.h"

class oUI_BAR : public System
{
private:

	int level;
	float current, MAX;
	Shape shpLine;
	Shape shpBonus;
	Shape shpIco;
	Shape shpPlato;
	Shape shpBar;
	sf::Text text;
	const float sizex_line;

public:

	oUI_BAR(uint level, uint current) : 
		level(level), 
		current(current), 
		MAX(200+(level*100)),
		sizex_line(25*scr_1)
	{
		ConstructShape(shpIco, v2f(-15,-43.25), v2f(3.5,3.5), texture->UI_Ico);
		ConstructShape(shpBar, v2f(1.75,-43.25), v2f(30,3.5), texture->UI_Bar);
		ConstructShape(shpBonus, v2f(-15,-43.25), v2f(2.5,2.5), texture->Bonus_Experience);
		ConstructShape(shpPlato, v2f(-15,-43.25), v2f(3.2,3.2), texture->Bonus_Plato);
		ConstructShape(shpLine, v2f(-13.25,-43.25), v2f(0,3.5), texture->UI_EXP_Line);
		shpLine.setOrigin(0,shpLine.getOrigin().y);
		ConstructText(text, shpBar.getPosition(), 1.65, "Level " + to_string(level) + ": " + to_string(int(this->current)) + "/" + to_string(int(MAX)) + " exp.", font_freshman, sf::Color::White);
	}

	virtual void Update()
	{
		shpPlato.rotate(0.03*time);
	}

	virtual int getLevel() const { return level; }
	virtual void levelUp() { level++; }

	virtual void Draw()
	{
		wnd->draw(shpIco);
		wnd->draw(shpLine);
		wnd->draw(shpBar);
		wnd->draw(shpPlato);
		wnd->draw(shpBonus);
		wnd->draw(text);
	}

	virtual void Action()
	{

	}

	virtual bool addExp(int experience)
	{
		const int l = level;
		this->current += experience;
		if(this->current >= MAX)
		{
			this->current -= MAX;
			level++;
			MAX = 200+(level*100);
		}
		shpLine.setSize(v2f(sizex_line*(this->current/MAX), shpLine.getSize().y));
		shpLine.setTextureRect(sf::IntRect(0,0,256*(this->current/MAX),72));
		text.setString("Level " + to_string(level) + ": " + to_string(int(this->current)) + " / " + to_string(int(MAX)) + " exp.");
		if(l < level) return true;
		return false;
	}

	virtual ~oUI_BAR() {}
};