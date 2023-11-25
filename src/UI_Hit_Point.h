#pragma once
#include "System.h"

class UI_Point : public System
{
protected:

	Shape shpBonus;
	Shape shpIco;
	Shape shpPlato;
	Shape shpLine;
	Shape shpBar;
	sf::Text text;

	float timer_regen;
	float current;
	float regen, REGEN;
	float max;
	float size_line;

public:

	UI_Point(float max, float regen) : max(max), REGEN(regen), regen(regen), current(max), timer_regen(0)
	{
		size_line = 20*scr_1;
	}

	virtual float getMax() const { return max; }
	virtual float getCurrent() const { return current; }

	virtual void Regen(int add = 0)
	{
		if(add > 0) current += add;
		else current += regen/4;
		if(current > max) current = max;
		shpLine.setSize(v2f(size_line*(current/max), shpLine.getSize().y));
		shpLine.setTextureRect(sf::IntRect(0,0,float(256*(current/max)),36));
	}

	virtual float getRegenStart() const { return REGEN; }

	virtual void setRegen(float reg)
	{
		regen = REGEN + reg;
	}

	virtual void Update()
	{
		timer_regen += time;
		if(timer_regen >= 250)
		{
			timer_regen = 0;
			Regen();
		}
		shpPlato.rotate(0.03*time);
	}

	virtual void setMax(float max)
	{
		this->max = max;
	}

	virtual void Draw()
	{
		wnd->draw(shpIco);
		wnd->draw(shpLine);
		wnd->draw(shpBar);
		wnd->draw(shpPlato);
		wnd->draw(shpBonus);
		if(shpBar.getGlobalBounds().contains(cur_p)) ConstructText(text, shpBar.getPosition(), 1.25, to_string(int(current)) + "/" + to_string(int(max)), font_freshman, sf::Color::White);
		else ConstructText(text, shpBar.getPosition(), 2, to_string(int((current / max) * 100)) + "%", font_freshman, sf::Color::White);
		wnd->draw(text);
	}
};

class UI_Hit_Point : public UI_Point
{
public:

	UI_Hit_Point(float max, float regen) : UI_Point(max, regen)
	{
		ConstructShape(shpIco, v2f(-62.5, 46.5), v2f(5,5), texture->UI_Ico);
		ConstructShape(shpBonus, v2f(-62.5, 46.5), v2f(4,4), texture->Bonus_HP[0]);
		ConstructShape(shpPlato, v2f(-62.5, 46.5), v2f(4.5,4.5), texture->Bonus_Plato);
		ConstructShape(shpBar, v2f(-62.5, 34), v2f(20,5), texture->UI_Bar);
		ConstructShape(shpLine, v2f(-62.5, 34), v2f(20,5), texture->UI_HP_Line);
		shpBar.setRotation(270);
		shpLine.setRotation(270);
	}

	virtual void Damage(int dmg)
	{
		current -= dmg;
		if(current <= 0) current = 0;
		shpLine.setSize(v2f(size_line*(current/max), shpLine.getSize().y));
		shpLine.setTextureRect(sf::IntRect(0,0,float(256*(current/max)),36));
		ConstructText(text, shpBar.getPosition(), 1.5, to_string(int(current / max * 100))+"%", font_freshman, sf::Color::White);
	}

	virtual ~UI_Hit_Point() {}
};

class UI_Energy_Point : public UI_Point
{
private:

	sf::Text text_Fail_Energy;
	float timer_ShowTextFailEnergy;

public:

	UI_Energy_Point(float max, float regen)  : UI_Point(max, regen), timer_ShowTextFailEnergy(0)
	{
		ConstructShape(shpIco, v2f(62.5,46.5), v2f(5,5), texture->UI_Ico);
		ConstructShape(shpBonus, v2f(62.5,46.5), v2f(4,4), texture->Bonus_Energy[0]);
		ConstructShape(shpPlato, v2f(62.5,46.5), v2f(4.5,4.5), texture->Bonus_Plato);
		ConstructShape(shpBar, v2f(62.5,34), v2f(20,5), texture->UI_Bar);
		ConstructShape(shpLine, v2f(62.5, 34), v2f(20,5), texture->UI_Energy_Line);
		shpBar.setRotation(270);
		shpLine.setRotation(270);
		ConstructText(text_Fail_Energy, v2f(0, -scr_1*25), 2, "Fail energy...", font_freshman, sf::Color(255,70,100));
	}

	virtual bool Cast(float cast)
	{
		if(current < cast) 
		{ 
			timer_ShowTextFailEnergy = 2000;
			ConstructText(text_Fail_Energy, v2f(0, -scr_1*25), 2, "Fail energy...", font_freshman, sf::Color(255,70,100));
			return false;
		}
		else
		{
			if(current/max < 10) ConstructText(text_Fail_Energy, v2f(0, -scr_1*25), 3, "Low energy...", font_freshman, sf::Color(255,70,100));
			current -= cast;
		}
		shpLine.setSize(v2f(size_line*(current/max), shpLine.getSize().y));
		shpLine.setTextureRect(sf::IntRect(0,0,float(256*(current/max)),36));
		ConstructText(text, shpBar.getPosition(), 2, to_string(int((current / max) * 100))+"%", font_freshman, sf::Color::White);
		return true;
	}

	virtual void Draw()
	{
		UI_Point::Draw();
		if(timer_ShowTextFailEnergy > 0)
		{
			timer_ShowTextFailEnergy-=time;
			text_Fail_Energy.setColor(sf::Color(255,70,100,255*(timer_ShowTextFailEnergy/2000)));
			wnd->draw(text_Fail_Energy);
		}
	}

	virtual ~UI_Energy_Point() {}
};