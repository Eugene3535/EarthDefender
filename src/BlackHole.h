#pragma once
#include "System.h"

class BlackHole : public System
{
private:

	float timer_per_dmg;
	const float TIMER_PER_DMG;
	bool isDMG;
	float damage;
	Shape shpBackHole;


public:

	Shape shape[2];
	
	BlackHole(int lvl = 0) : TIMER_PER_DMG(200), timer_per_dmg(0), isDMG(false), damage(1.7f + (lvl*.45f))
	{
		const float siz = 7.5f + ( (lvl-1) * 2.5);
		ConstructShape(shape[0], cur_p, v2f(siz,siz), texture->EFF_BlackHole[1], false);
		ConstructShape(shpBackHole, cur_p, v2f(siz,siz)*1.25f, texture->EFF_BlackHole[2], false);
		shpBackHole.setFillColor(CLR(255,255,255,80));
		shape[0].setFillColor(CLR(255,255,255,125));
		shape[1] = shape[0];
		shape[1].setTexture(&texture->EFF_BlackHole[0]);
		shape[1].setScale(-1, 1);
	}

	virtual float GetDamage()
	{
		if(!isDMG) return 0;
		else isDMG = false;
		return damage;
	}

	virtual void Reset(int lvl)
	{
		const float siz = 7.5f + ( (lvl-1) * 2.5);
		ConstructShape(shape[0], cur_p, v2f(siz,siz), texture->EFF_BlackHole[1], false);
		shpBackHole.setSize(shape[0].getSize()*1.25f);
		shape[0].setFillColor(CLR(255,255,255,125));
		shape[1] = shape[0];
		shape[1].setTexture(&texture->EFF_BlackHole[0]);
		shape[1].setScale(-1, 1);
		damage = (1.7f + (lvl*.45f));
	}

	virtual void Update()
	{
		timer_per_dmg += time;
		if(timer_per_dmg >= TIMER_PER_DMG)
		{
			isDMG = true;
			timer_per_dmg = 0;
		}
		for(int i = 0; i < 2; i++) shape[i].setPosition(cur_p);
		shape[0].rotate(0.066f*time);
		shape[1].rotate(-.066f*time);
		shpBackHole.rotate(0.1*time);
	}


	virtual void Draw()
	{
		wnd->draw(shpBackHole);
		for(int i = 0; i < 2; i++) wnd->draw(shape[i]);
	}

	virtual ~BlackHole() {}

};