#pragma once
#include "System.h"

class oStar : public System
{
protected:

	float speed;
	float rot;

public:

	Shape shape[2];

	oStar(v2f pos, v2f siz, float speed, sf::Texture& img) : rot(0), speed(speed)
	{
		for(int i = 0; i < 2; i++) 
			ConstructShape(shape[i], pos, siz, img, false);
		shape[1].setScale(-1, 1);
	}

	virtual void Update()
	{
		shape[0].rotate(rot*time_enemy);
		shape[1].rotate(-rot*time_enemy);
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) wnd->draw(shape[i]);
	}

	virtual ~oStar()
	{

	}
};