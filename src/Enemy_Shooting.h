#pragma once
#include"oEnemy.h"

class Enemy_Shooting : public oEnemy
{
protected:

	float attack_coldown, ATTACK_COLDOWN;

public:

	Enemy_Shooting(v2f pos, v2f siz, float speed, float hp, float attack_coldown, const int level, sf::Texture& img, string name, const bool isBoss = false, const bool isHideHpBar = false) : 
		oEnemy(pos, siz, speed, hp, level, img, name, isBoss, isHideHpBar), attack_coldown(attack_coldown), ATTACK_COLDOWN(attack_coldown)
	{
	}

	virtual void Update()
	{
		oEnemy::Update();
	}

	virtual bool IsAttack()
	{
		attack_coldown-=time_enemy;
		if(attack_coldown < 0 )
		{
			attack_coldown = ATTACK_COLDOWN;
			return true;
		}
		else
		{
			return false;
		}
	}

	virtual void Draw()
	{
		oEnemy::Draw();
	}

	virtual ~Enemy_Shooting()
	{

	}
};