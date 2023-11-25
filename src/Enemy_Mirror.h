#pragma once
#include "oEnemy.h"

class Enemy_Mirror : public oEnemy
{
protected:

	float timer_reset_position;
	const float TIMER_RESET_POSITION;
	float a;
	const bool dir_rot;

public:

	Enemy_Mirror(v2f pos, v2f siz, float speed, uint hp, uint lvl, sf::Texture& img, string name, float timer_reset_position) 
		: oEnemy(pos, siz, speed, hp, lvl, img, name), 
		TIMER_RESET_POSITION(timer_reset_position), timer_reset_position(timer_reset_position),
		dir_rot(rand()%2)
	{
		this->speed = speed;
		a = GetAngle(shape, v2f(0,0));
	}
	
	virtual void Update()
	{
		oEnemy::Update();
	
		if(timer_reset_position > 0)
		{
			timer_reset_position -= time_enemy;
		}
		else
		{
			if(dir_rot) a += 10;
			else a -= 10;
			shape.setPosition(GetNormalizedPosition(v2f(0,0), GetDistance(shape, v2f(0,0)), a));
			shape.setFillColor(sf::Color(255,255,255,255));
			angle = a + 180;
			shape.setRotation(angle);
			timer_reset_position = TIMER_RESET_POSITION;
		}
		indicator_hp_postiton = v2f(shape.getPosition().x - (shape.getSize().x / 2.f), shape.getPosition().y - (shape.getSize().y / 2.f));
		shpIndicatorHp.setPosition(indicator_hp_postiton);
	}
	
	virtual void Draw()
	{
		wnd->draw(shape);
		wnd->draw(shpIndicatorHp);
	}
	
	virtual bool IsAttack() { return false; }


	virtual ~Enemy_Mirror() {}

};