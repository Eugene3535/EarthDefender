#include "SpecEffect.h"


SpecEffect::SpecEffect(float timer_life = 0.f) 
{ 
	if(timer_life <= 0) isNo_Timer = true;
	else
	{
		this->timer_life = timer_life;
		this->TIMER_LIFE = timer_life;
	}
}

void SpecEffect::Update()
{
	if(!isNo_Timer)
	{
		if(timer_life > 0) timer_life -= time;
		else timer_life = 0;
	}
}

bool SpecEffect::IsEnd() 
{ 
	if(timer_life <= 0) 
	{ 
		timer_life = 0; 
		return true; 
	} 
	else return false; 
}

void SpecEffect::Draw() { }
SpecEffect::~SpecEffect() {}