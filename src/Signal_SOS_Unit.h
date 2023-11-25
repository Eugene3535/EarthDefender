#pragma once
#include "System.h"
#include "oMissle.h"
class Signal_SOS_Unit_01 : public System
{
private:

	float attack_Coldown;
	const float ATTACK_COLDOWN;
	float speed;
	const int level;

public:

	Shape shape;
	Shape shpBonusBorder[2];
	vector<shared_ptr<Missle>> vec_Missle;
	
	Signal_SOS_Unit_01(v2f pos, v2f siz, const float speed, IMG &img, const float att_cldwn, const int level) 
		: ATTACK_COLDOWN(att_cldwn), attack_Coldown(0), speed(speed), level(level)
	{
		
		vec_Missle.push_back(make_shared<Missle>(
			Missle(GetNormalizedPosition(shape, shape.getSize().x/2.f, shape.getRotation()), v2f(2.25,2.25), speed*2.75, shape.getRotation() + float(rand()%200-100), texture->MissleT[12], level, false))
			);

		ConstructShape(shape, pos, siz, img, false);
		shape.setRotation(GetAngle(shape, v2f(0,0)) + 10);
		ConstructShape(shpBonusBorder[0],shape.getPosition(), siz*0.8f, texture->EFF_Bonus_Border, false);
		shpBonusBorder[0].setScale(-1.5,-1.5);
		shpBonusBorder[0].setFillColor(CLR(80,255,80,100));
		shpBonusBorder[1] = shpBonusBorder[0];
		shpBonusBorder[1].setScale(1.5,1.5);
	}

	virtual void Update()
	{
		MoveToAngle(shape, speed, shape.getRotation());
		shpBonusBorder[0].setPosition(shape.getPosition());
		shpBonusBorder[1].setPosition(shape.getPosition());
		shpBonusBorder[0].rotate(0.8*time);
		shpBonusBorder[1].rotate(-0.8*time);
		attack_Coldown += time;
		if(attack_Coldown >= ATTACK_COLDOWN)
		{
			attack_Coldown = 0;
			vec_Missle.push_back(make_shared<Missle>(
				Missle(GetNormalizedPosition(shape, shape.getSize().x/2, shape.getRotation()), v2f(2.25,2.25), speed*2.75f, shape.getRotation(), texture->MissleT[12], level, false)));
		}
		
		
		for(auto& missle = vec_Missle.begin(); missle != vec_Missle.end();)
		{
			Missle& m = *(*missle);
			if(shape.getGlobalBounds().intersects(getVisible()))
			{
				m.Update();
				missle++;
			}
			else missle = vec_Missle.erase(missle);
		}
	}

	virtual void Draw()
	{
		wnd->draw(shpBonusBorder[0]);
		wnd->draw(shpBonusBorder[1]);
		wnd->draw(shape);
		for(auto& missle : vec_Missle) 
			missle->Draw();
	}
	virtual ~Signal_SOS_Unit_01()  {}
};