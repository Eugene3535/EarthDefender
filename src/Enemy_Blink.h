#pragma once
#include "oEnemy.h"

class Enemy_Blink : public oEnemy
{
protected:

	float timer_blink;
	const float TIMER_BLINK;

	float timer_blink_animation;
	const float TIMER_BLINK_ANIMATION;


	Shape shpBlinkEffect[2];
	Shape shpBlinkPortal;

public:

Enemy_Blink(v2f pos, v2f siz, float speed, uint hp, uint lvl, sf::Texture& img, string name, float timer_blink, float timer_blink_animation) 
	: oEnemy(pos, siz, speed, hp, lvl, img, name), 
	TIMER_BLINK(timer_blink), timer_blink(timer_blink),
	TIMER_BLINK_ANIMATION(timer_blink_animation), timer_blink_animation(timer_blink_animation)
{
	this->speed = speed;
	ConstructShape(shpBlinkPortal, shape.getPosition(), v2f(siz.x,siz.x)*1.50f, texture->EFF_Portal_Dark, false);
	ConstructShape(shpBlinkEffect[0], shape.getPosition(), v2f(siz.x,siz.x)*1.20f, texture->EFF_Portal_Tornado_Dark, false);
	ConstructShape(shpBlinkEffect[1], shape.getPosition(), v2f(siz.x,siz.x)*1.20f, texture->EFF_Portal_Tornado_Dark, false);
	shpBlinkEffect[1].setScale(-1,-1);
}

virtual void Update()
{
	oEnemy::Update();
	shpBlinkPortal.setPosition(shape.getPosition());
	for(int i = 0; i < 2; i++) shpBlinkEffect[i].setPosition(shape.getPosition());

	if(timer_blink_animation > 0)
	{
		timer_blink_animation -= time_enemy;  // time_enemy * speedUP если ускоряется
		shape.setFillColor(sf::Color(255,255,255,255 * (timer_blink_animation/TIMER_BLINK_ANIMATION)));
		shpBlinkEffect[0].rotate( 0.1*time);
		shpBlinkEffect[1].rotate(-0.1*time);
		
		if(timer_blink_animation < 0)
		{
			timer_blink_animation = 0;
			const int a = rand()%360;
			shape.setPosition(GetNormalizedPosition(v2f(0,0), GetDistance(shape, v2f(0,0)), a));
			shape.setFillColor(sf::Color(255,255,255,255));
			angle = a + 180;
			shape.setRotation(angle);
			speed *= 1.1f;
		}

		const sf::Color &c = shpBlinkPortal.getFillColor();
		shpBlinkPortal.setFillColor(sf::Color(c.r, c.g, c.b, 255 * (timer_blink_animation / TIMER_BLINK_ANIMATION)));

		for(int i = 0; i < 2; i++) shpBlinkEffect[i].setFillColor(shpBlinkPortal.getFillColor());
	}
	else
	{
		timer_blink -= time_enemy; // time_enemy * speedUP если ускоряется
		if(timer_blink < 0)
		{
			timer_blink_animation = TIMER_BLINK_ANIMATION;
			timer_blink = TIMER_BLINK;
		}
	}
	indicator_hp_postiton = v2f(shape.getPosition().x - (shape.getSize().x / 2.f), shape.getPosition().y - (shape.getSize().y / 2.f));
	shpIndicatorHp.setPosition(indicator_hp_postiton);
}

virtual void Draw()
{
	wnd->draw(shpBlinkPortal);
	wnd->draw(shape);
	for(int i = 0; i < 2; i++) 
		wnd->draw(shpBlinkEffect[i]);
	wnd->draw(shpIndicatorHp);
}

virtual bool IsAttack() { return false; }

virtual ~Enemy_Blink() {}

			 
};