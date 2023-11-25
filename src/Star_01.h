#pragma once
#include "oStar.h"

class Star_01 : public oStar
{
public:

	Star_01(v2f pos, v2f siz, float speed, sf::Texture& img) : oStar(pos, siz, speed, img)
	{
		rot = 0.1;
		for(int i = 0; i < 2; i++) 
			shape[i].setFillColor(sf::Color(rand()%255, rand()%255, rand()%255, 100));
	}

	virtual void Update()
	{
		oStar::Update();
		const float slower = time_enemy/time;
		for(int i = 0; i < 2; i++) 
			MoveToAngle(shape[i], speed*slower, 90);
	}

	virtual void Draw()
	{
		oStar::Draw();
	}

	virtual ~Star_01(){}
};