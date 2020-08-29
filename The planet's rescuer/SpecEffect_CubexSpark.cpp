#pragma once
#include "SpecEffect.h"

SpecEffect_CubexSpark::SpecEffect_CubexSpark(v2f pos, v2f siz, IMG& img, sf::Color color, float angle, float timer_life, float speed) 
	: SpecEffect(timer_life), angle(angle), speed(speed)
{
	ConstructShape(shape, pos, siz, img, false);
	shape.setFillColor(color);
	this->shape.setRotation(shape.getRotation());
}

SpecEffect_CubexSpark::SpecEffect_CubexSpark(v2f pos, v2f siz, sf::Color color, float angle, float timer_life, float speed) 
	: SpecEffect(timer_life), angle(angle), speed(speed)
{
	ConstructShape(shape, pos, siz, false);
	shape.setFillColor(color);
	this->shape.setRotation(shape.getRotation());
}

SpecEffect_CubexSpark::SpecEffect_CubexSpark(Shape& shape, float timer_life, float speed) 
	: SpecEffect(timer_life), shape(shape), angle(shape.getRotation()), speed(speed)
{
} 

void SpecEffect_CubexSpark::Update()
{
	SpecEffect::Update();
	shape.rotate(-.1 * time);
	const sf::Color& c = shape.getFillColor();
	const float factor = timer_life / TIMER_LIFE;
	shape.setFillColor(sf::Color(c.r, c.g, c.b, factor * 100));
	shape.setOutlineColor(sf::Color(c.r*.8, c.g*.8, c.b*.8, factor * 100));
	shape.setScale(v2f(factor,factor));
	MoveToAngle(shape, speed*factor, angle);
}

void SpecEffect_CubexSpark::Draw()
{
	wnd->draw(shape);
}

SpecEffect_CubexSpark::~SpecEffect_CubexSpark() { }