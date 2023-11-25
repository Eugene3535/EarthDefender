#pragma once
#include "oEnemy.h"

class Enemy_Circle_Fly : public oEnemy
{
private:

	const float DIST_START_TO_PLANET;
	const float ANGLE_UP;
	const bool direction;
	float ANGLE;

public:

	Enemy_Circle_Fly(v2f pos, v2f siz, float speed, float hp, const int level, sf::Texture& img, string name) 
		: 
		oEnemy(pos, siz, speed, hp, level, img, name),
		DIST_START_TO_PLANET(GetDistance(pos*scr_1, v2f())),
		ANGLE_UP(0.01f),
		direction(rand()%2)
	{
		ANGLE = angle;
	}

	virtual void Update()
	{
		// const float DIST_TO_PLANET = GetDistance(shape, v2f(0,0));
		// const float FACTOR = DIST_TO_PLANET / DIST_START_TO_PLANET;
		// 
		// if(direction) ANGLE += ANGLE_UP * (2.f - FACTOR );
		// else ANGLE -= ANGLE_UP * (2.f - FACTOR );
		// 
		// shape.setPosition(GetNormalizedPosition(v2f(0,0), DIST_TO_PLANET, ANGLE));
		// angle = ANGLE;
		// shape.setRotation(angle);
		oEnemy::Update();
	}

	virtual void Draw()
	{
		oEnemy::Draw();
	}
	
	virtual ~Enemy_Circle_Fly() {}

};