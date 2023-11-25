#pragma once
#include "oEnemy.h"
// Режим игры с нападением на землю играя за инопланетян и ведя тактики нападения на землю

class Enemy_Kamikadze : public oEnemy
{

public:

	Enemy_Kamikadze(v2f pos, v2f siz, float speed, float hp, const int level, sf::Texture& img, string name, const bool isBoss = false, const bool isHideHpBar = false) 
		: oEnemy(pos, siz, speed, hp, level, img, name, isBoss, isHideHpBar)
	{
		shape.setScale(0.01, 0.01);
	}

	virtual void Update()
	{
		oEnemy::Update();
		float scale = shape.getScale().x;
		if(scale < 1.0)
		{
			scale += (0.0005f*time_enemy);
			shape.setScale(scale, scale);
		}
		else speed += 0.000005*time_enemy;
	}

	virtual bool IsDead()
	{
		return hp <= 0;
	}

	virtual void Draw()
	{
		oEnemy::Draw();
	}

	virtual ~Enemy_Kamikadze() {}

};