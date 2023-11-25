#pragma once
#include "System.h"

class SpecEffect : public System
{
protected:

	float timer_life;
	float TIMER_LIFE;
	bool isNo_Timer;

public:

	SpecEffect(float timer_life);
	virtual void Update();
	virtual void Draw() = 0;
	virtual bool IsEnd();
	virtual ~SpecEffect();
};

class SpecEffect_CubexSpark : public SpecEffect
{
private:

	float speed;
	float angle;
	
public:

	Shape shape;

	SpecEffect_CubexSpark(v2f pos, v2f siz, sf::Texture& img, sf::Color color, float angle, float timer_life, float speed);
	SpecEffect_CubexSpark(v2f pos, v2f siz, sf::Color color, float angle, float timer_life, float speed);
	SpecEffect_CubexSpark(Shape& shape, float timer_life, float speed);
	virtual void Update();
	virtual void Draw();
	virtual ~SpecEffect_CubexSpark();
};

class SpecEffect_BG_FloatQuad : public SpecEffect
{
private:

	float alpha;
	float angle;
	Shape shape;

public:
	
	SpecEffect_BG_FloatQuad(v2f pos, v2f siz, sf::Texture& img, sf::Color color, float angle, float timer_life);
	SpecEffect_BG_FloatQuad(v2f pos, v2f siz, sf::Color color, float angle, float timer_life);
	SpecEffect_BG_FloatQuad(Shape& shape, float timer_life);
	virtual void Update();
	virtual void Draw();
	virtual ~SpecEffect_BG_FloatQuad();
};

class SpecEffect_Turbo : public SpecEffect
{
private:

	Shape shape[3];

public:

	SpecEffect_Turbo(v2f pos, v2f siz, sf::Texture& img, float angle, float timer_life);
	virtual void Update();
	virtual void Draw();
	virtual ~SpecEffect_Turbo();
};

