#pragma once
#include "SpecEffect.h"

SpecEffect_Turbo::SpecEffect_Turbo(v2f pos, v2f siz, IMG& img, float angle, float timer_life) : SpecEffect(timer_life)
{
	for(int i = 0; i < 3; i++)
	{
		ConstructShape(shape[i], GetNormalizedPosition(pos, (-siz.y/1.5f)*scr_1, angle), siz, img, false);
		shape[i].setRotation(angle+90);
	}
	shape[0].setScale(0.6,0.6);
	shape[2].setScale(0.45,0.45);
}

void SpecEffect_Turbo::Update()
{
	timer_life -= time;
	if(timer_life < 0) timer_life = 0;
	const float scaler = timer_life/TIMER_LIFE;

	shape[0].setFillColor(CLR(255,180,180,scaler*255));
	shape[2].setFillColor(CLR(255,100,100,scaler*150));
	shape[1].setFillColor(CLR(255,255,255,scaler*200));

	shape[1].setScale(-scaler+2.00,-scaler+2.00);
	shape[0].setScale(-scaler+1.60,-scaler+1.60);
	shape[2].setScale(-scaler+1.45,-scaler+1.45);
}

void SpecEffect_Turbo::Draw()
{
	for(int i = 0; i < 3; i++) wnd->draw(shape[i]);
}

SpecEffect_Turbo::~SpecEffect_Turbo() {}
