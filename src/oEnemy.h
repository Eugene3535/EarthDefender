#pragma once
#include "System.h"
#include "oMissle.h"

class oEnemy : public System
{
protected:

	float angle;
	float speed;
	float hp;
	const float maxHp;
	float slowPowerBuff;
	float timer_stun;
	float TIMER_STUN;
	const int level;
	v2f indicator_hp_postiton;
	float pX;
	Shape shpIndicatorHp;
	bool isHideHpBar;
	Shape shpTarget[2];
	
public:

	const bool isBoss;

	Shape shape;
	string name;

	oEnemy(v2f pos, v2f siz, float speed, float hp, const int level, IMG& img, string name, const bool isBoss = false, const bool isHideHpBar = false) :
		speed(speed),  
		hp(hp), 
		maxHp(hp),
		timer_stun(0),
		TIMER_STUN(0),
		name(name),
		level(level),
		isBoss(isBoss),
		isHideHpBar(isHideHpBar)
	{
		ConstructShape(shape,pos, siz, img, false);
		indicator_hp_postiton = v2f(shape.getPosition().x - (shape.getSize().x / 2.f), shape.getPosition().y - (shape.getSize().y / 2.f));
		ConstructShape(shpIndicatorHp, indicator_hp_postiton, v2f(siz.x, 3.f/scr_1), CLR::Green, false);

		for(int i = 0; i < 2; i++) 
		{
			float SIZE;
			if(siz.x > siz.y) SIZE = siz.x;
			else SIZE = siz.y;
			ConstructShape(shpTarget[i], pos, v2f(SIZE,SIZE) * 1.35f, texture->EFF_Warning_Red_Circle, false);
			shpTarget[i].setFillColor(CLR(255,255,255,120));
		}

		shpTarget[0].setScale(shape.getScale());
		shpTarget[1].setScale(-shape.getScale());

		shpIndicatorHp.setOrigin(0, 3.f/scr_1);
		angle = GetAngle(shape, planet_p);
		shape.setRotation(angle);
		
		pX = shape.getSize().x;
	}

	virtual float GetMaxHp() const
	{
		return maxHp;
	}

	virtual float GetHp()
	{
		if(hp < 0) hp = 0; 
		return hp;
	}

	virtual float GetSpeed() const { return speed; }
	
	virtual const int GetLevel()
	{
		return level;
	}

	virtual void Update()
	{
		if(timer_stun < 0)
		{
			shape.setFillColor(CLR(255,255,255));
			MoveToAngle(shape, speed, angle, true); 
		}
		else 
		{
			timer_stun -= time_enemy;
			shape.setFillColor(CLR(255 * ( timer_stun / TIMER_STUN ), 255, 255));
			MoveToAngle(shape, speed/3, angle, true); 
		}
		indicator_hp_postiton = v2f(shape.getPosition().x - (shape.getSize().x / 2.f), shape.getPosition().y - (shape.getSize().y / 2.f));
		shpIndicatorHp.setPosition(indicator_hp_postiton);

		for(int i = 0; i < 2; i++) 
			shpTarget[i].setPosition(shape.getPosition());

		shpTarget[0].setScale(shape.getScale());
		shpTarget[1].setScale(-shape.getScale());

		shpTarget[0].rotate(0.5*time);
		shpTarget[1].rotate(-.5*time);
	}

	virtual float GetSizeBang() { return shape.getSize().x / scr_1; }

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) 
			wnd->draw(shpTarget[i]);

		wnd->draw(shape);

		if(!isHideHpBar) wnd->draw(shpIndicatorHp);
	}

	virtual bool IsDead()
	{
		return hp <= 0;
	}

	virtual bool IsAttack() { return false; }

	virtual void Damage(float dmg, float timer_stun = 0, float _slowPowerBuff = 1.0)
	{
		TIMER_STUN = timer_stun;
		this->timer_stun = timer_stun;
		this->slowPowerBuff = _slowPowerBuff;
		hp -= dmg;
		if(hp < 0) hp = 0;
		shpIndicatorHp.setSize(v2f(pX * (float(hp) / float(maxHp)), 3.f));
	}

	virtual void Attack(v2f& attack_pos)
	{

	}

	virtual ~oEnemy()
	{

	}
};