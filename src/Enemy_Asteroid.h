#pragma once
#include"oEnemy.h"

class Enemy_Asteroid : public oEnemy
{
protected:

	bool isRotDir;
	float rotSpeed;

public:

	Enemy_Asteroid(v2f pos, v2f siz, float speed, float hp, const int level, sf::Texture& img, string name, const bool isBoss = false, const bool isHideHpBar = false) : 
		oEnemy(pos, siz, speed, hp, level, img, name, isBoss, isHideHpBar), isRotDir(rand()%6), rotSpeed(0.06)
	{
	}

	virtual void Update()
	{
		oEnemy::Update();
		if(isRotDir) shape.rotate(rotSpeed*time);
		else shape.rotate(-rotSpeed*time);
	}

	virtual bool IsAttack(){return false;}

	virtual void Draw()
	{
		oEnemy::Draw();
	}

	virtual ~Enemy_Asteroid()
	{

	}
};