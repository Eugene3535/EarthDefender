#pragma once
#include"oEnemy.h"

class Enemy_Dodge : public oEnemy
{
private:

	float attack_coldown;
	float alpha;
	bool isRotDir;
	float rotSpeed;
	float timer_anim;
	int frame_count;
	const float radius;
	v2f pos;

public:

	Enemy_Dodge(v2f pos, v2f siz, float speed, float hp, const int level, float radius_rot, sf::Texture& img, string name, const bool isBoss = false, const bool isHideHpBar = false) : 
		oEnemy(pos, siz, speed, hp, level, img, name, isBoss, isHideHpBar),
		isRotDir(rand()%2), 
		rotSpeed(0.05),
		alpha(0),
		attack_coldown(3500),
		timer_anim(0),
		frame_count(0),
		radius(radius_rot*scr_1),
		pos(pos)
	{
		shape.setTextureRect(sf::IntRect(0,0,64,64));
	}

	virtual void Update()
	{
		timer_anim += time;
		
		if(timer_anim > 50)
		{
			timer_anim = 0;

			if(frame_count < 5) shape.setTextureRect(sf::IntRect(frame_count*64,0,64,64));
			if(frame_count < 10 && frame_count >= 5) shape.setTextureRect(sf::IntRect((frame_count-5)*64,64,64,64));
			if(frame_count < 15 && frame_count >= 10) shape.setTextureRect(sf::IntRect((frame_count-10)*64,128,64,64));
			frame_count++;
			if(frame_count >= 15) 
				frame_count = 0;
		}

		attack_coldown -= time_enemy;
		
		if(timer_stun < 0) // Движение
		{
			alpha += time_enemy/500;
			shape.setFillColor(sf::Color(255,255,255));
			MoveToAngle(pos, speed, angle, true);
			shape.setPosition(pos + v2f(cos(alpha), sin(alpha))*radius);
		}
		else 
		{
			alpha += time_enemy/3000;
			timer_stun -= time_enemy;
			shape.setFillColor(sf::Color(255*(timer_stun/TIMER_STUN),255,255));
			MoveToAngle(pos, speed/3.f, angle, true); 
			shape.setPosition(pos + v2f(cos(alpha), sin(alpha))*radius);
		}

		if(isRotDir) shape.rotate(rotSpeed*time);
		else shape.rotate(-rotSpeed*time);
		for(int i = 0; i < 2; i++) shpTarget[i].setPosition(shape.getPosition());
		indicator_hp_postiton = v2f(shape.getPosition().x - (shape.getSize().x / 2.f), shape.getPosition().y - (shape.getSize().y / 2.f));
		shpIndicatorHp.setPosition(indicator_hp_postiton);
		shpTarget[0].rotate(0.5*time);
		shpTarget[1].rotate(-.5*time);
	}

	virtual bool IsAttack()
	{
		if(attack_coldown < 0) 
		{
			attack_coldown = 2000; 
			return true;
		}
		return false;
	}

	virtual void Attack(v2f& attack_pos)
	{
	}

	virtual void Draw()
	{

		oEnemy::Draw();
	}

	virtual ~Enemy_Dodge()
	{

	}
};