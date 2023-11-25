#pragma once
#include "System.h"

class Bang_Ricochet : public System
{
private:

	sf::Text text_Boom;
	float timer_life;
	float radius;

public:

	const v2f size;
	Shape shape[2];

	Bang_Ricochet(v2f pos, v2f siz, float radius) : timer_life(0), size(siz*scr_1), radius(radius*scr_1)
	{
		ConstructShape(shape[0], pos, siz, texture->EFF_Bang_03, false);
		ConstructText(text_Boom, shape[0].getPosition(), 3, "BANG!", font_freshman, sf::Color::Red);
		shape[1]=shape[0];
		shape[1].setScale(-1,1);
	}

	virtual void Update()
	{
		timer_life += time;
		shape[0].rotate( time*0.5);
		shape[1].rotate(-time*0.5);
		text_Boom.setRotation(cam.getRotation());
		if(timer_life > 1000.f) timer_life = 1000;
	}

	virtual float getRadius() const
	{
		return radius;
	}

	virtual bool IsEnd() const
	{
		return timer_life == 1000.f ? true : false;
	}

	virtual void Draw()
	{
		float a = timer_life/1000.f; 
		for(int i = 0; i < 2; i++)
		{
			text_Boom.setColor(sf::Color(255,70,70,255 - (255*a)));
			shape[i].setSize(size + (v2f(10,10) * scr_1 * a));
			shape[i].setFillColor(sf::Color(255,255,255,255 - (255*a)));
			shape[i].setOrigin(shape[i].getSize()/2.f);
			wnd->draw(shape[i]);
		}
		wnd->draw(text_Boom);
	}

	virtual ~Bang_Ricochet() {}

};