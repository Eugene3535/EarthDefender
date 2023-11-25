#pragma once
#include "oEnemy.h"
#include "SpecEffect.h"
class Enemy_Boss_03 : public oEnemy
{
private:

	Shape shpEffect_Teleportation[2];
	Shape shpEffect_Portal;

	float timer_blink_animation; // Время анимации при телепортации
	const float TIMER_BLINK_ANIMATION;				

	float timer_blink; // Время между телепортациями
	const float TIMER_BLINK;

	float timer_create_turbo; // Время появления эффекта турбо
	const float START_DISTANCE;

	vector<shared_ptr<SpecEffect>> vec_Turbo;

public:

	//Shape shpEffect;

	Enemy_Boss_03(v2f pos, v2f siz, float speed, float hp, uint level, sf::Texture& img, string name, float timer_blink_animation, float timer_blink, const bool isBoss = false, const bool isHideHpBar = false) : 
		oEnemy(pos, siz, speed, hp, level, img, name, isBoss, isHideHpBar), 
		timer_blink_animation(timer_blink_animation),
		TIMER_BLINK_ANIMATION(timer_blink_animation),
		timer_blink(timer_blink),
		TIMER_BLINK(timer_blink),
		timer_create_turbo(0),
		START_DISTANCE(GetDistance(pos*scr_1, v2f(0,0)))
	{
		this->speed = (speed / 1000.f);
		ConstructShape(shpEffect_Portal, shape.getPosition(), siz*1.50f, texture->EFF_Portal_Dark, false);
		ConstructShape(shpEffect_Teleportation[0], shape.getPosition(), siz*1.20f, texture->EFF_Portal_Tornado_Dark, false);
		ConstructShape(shpEffect_Teleportation[1], shape.getPosition(), siz*1.20f, texture->EFF_Portal_Tornado_Dark, false);
		shpEffect_Teleportation[1].setScale(-1,-1);
	}

	virtual void Update()
	{
		// Множитель скорости при приблежении
		float speedUp = 2.f - (GetDistance(shape.getPosition(), v2f(0,0)) / START_DISTANCE);

		MoveToAngle(shape, speed, angle, true);
		timer_create_turbo += time_enemy;

		if(timer_create_turbo >= 180)
		{
			timer_create_turbo = 0;
			vec_Turbo.push_back(make_shared<SpecEffect_Turbo>(SpecEffect_Turbo(shape.getPosition(), v2f(6,12.5), texture->EFF_Turbo_Boss, angle, 750)));
		}

		for(auto it = vec_Turbo.begin(); it != vec_Turbo.end();)
		{
			SpecEffect& turbo = *(*it);
			if(turbo.IsEnd()) it = vec_Turbo.erase(it);
			else 
			{
				turbo.Update();
				it++;
			}
		}

		shpEffect_Portal.setPosition(shape.getPosition());
		for(int i = 0; i < 2; i++) shpEffect_Teleportation[i].setPosition(shape.getPosition());

		if(timer_blink_animation > 0)
		{
			timer_blink_animation -= (time_enemy*speedUp);
			shape.setFillColor(sf::Color(255,255,255,255 * (timer_blink_animation/TIMER_BLINK_ANIMATION)));
			shpEffect_Teleportation[0].rotate( 0.1*time);
			shpEffect_Teleportation[1].rotate(-0.1*time);
			
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

			const sf::Color &c = shpEffect_Portal.getFillColor();
			shpEffect_Portal.setFillColor(sf::Color(c.r, c.g, c.b, 255 * (timer_blink_animation / TIMER_BLINK_ANIMATION)));

			for(int i = 0; i < 2; i++) shpEffect_Teleportation[i].setFillColor(shpEffect_Portal.getFillColor());
		}
		else
		{
			timer_blink -= time_enemy * speedUp;
			if(timer_blink < 0)
			{
				timer_blink_animation = TIMER_BLINK_ANIMATION;
				timer_blink = TIMER_BLINK;
			}
		}
		indicator_hp_postiton = v2f(shape.getPosition().x - (shape.getSize().x / 2.f), shape.getPosition().y - (shape.getSize().y / 2.f));
		shpIndicatorHp.setPosition(indicator_hp_postiton);
	}

	virtual bool IsDead()
	{
		return hp <= 0;
	}

	virtual void Draw()
	{
		wnd->draw(shpEffect_Portal);
		for(auto& turbo : vec_Turbo) turbo->Draw();
		wnd->draw(shape);
		for(int i = 0; i < 2; i++) 
			wnd->draw(shpEffect_Teleportation[i]);
		wnd->draw(shpIndicatorHp);
	}

	virtual ~Enemy_Boss_03() {}
};