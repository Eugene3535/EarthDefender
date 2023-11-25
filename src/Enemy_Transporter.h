#pragma once
#include "Enemy_Shooting.h"

class Enemy_Transporter : public oEnemy
{
protected:

	float attack_coldown, ATTACK_COLDOWN;

	float timer_give, TIMER_GIVE;
	float timer_anim;
	float frame;
	bool isGive;
	bool isOpen;

public:

	Enemy_Transporter(v2f pos, v2f siz, float speed, float hp, float attack_coldown, const int level, sf::Texture& img, string name, const bool isBoss = false, const bool isHideHpBar = false) : 
		oEnemy(pos, siz, speed, hp, level, img, name, isBoss, isHideHpBar),
		timer_give(attack_coldown),
		TIMER_GIVE(attack_coldown),
		frame(0),
		timer_anim(0),
		isGive(false),
		isOpen(false),
		attack_coldown(attack_coldown), 
		ATTACK_COLDOWN(attack_coldown)
	{
		shape.setTextureRect(sf::IntRect(0,0,232,240));
		shape.rotate(90);
	}

	virtual bool IsAttack()
	{
		attack_coldown -= time_enemy;

		if(attack_coldown < 0 && isOpen)
		{
			attack_coldown = ATTACK_COLDOWN;
			return true;
		}
		else
		{
			return false;
		}
	}

	virtual void Update()
	{

		oEnemy::Update();

		if(!isGive)
		{
			timer_give -= time_enemy;
			timer_anim += time_enemy;
			if(timer_give <= 0)
			{
				if(!isOpen && timer_anim > ATTACK_COLDOWN/15) // Открываем
				{
					timer_anim = 0;

					if(frame >= 0 && frame < 2) shape.setTextureRect(sf::IntRect(frame*232, 0, 232, 240));
					if(frame >= 3 && frame < 5) shape.setTextureRect(sf::IntRect((frame-3)*232, 240, 232, 240));
					if(frame >= 5 && frame < 7) shape.setTextureRect(sf::IntRect((frame-5)*232, 480, 232, 240));
					if(frame < 7) frame++;
					else
					{
						isOpen = true;
						isGive = true;
					}
				}
			}
		}

		if(timer_give <= 0)
		{
			if(isGive) isGive = false;
			if(isOpen && timer_anim > ATTACK_COLDOWN/16) // И закрываем
			{
				timer_anim = 0;
				if(frame < 7 && frame >= 5) shape.setTextureRect(sf::IntRect((frame-5)*232, 480, 232, 240));
				if(frame < 5 && frame >= 3) shape.setTextureRect(sf::IntRect((frame-3)*232, 240, 232, 240));
				if(frame < 2 && frame >= 0) shape.setTextureRect(sf::IntRect(frame*232, 0, 232, 240));
				if(frame > 0) frame--;
				else
				{
					isOpen = false;
					timer_give = TIMER_GIVE;
				}
			}
		}
	}

	virtual void Draw()
	{
		oEnemy::Draw();
	}

	virtual ~Enemy_Transporter() {}
};