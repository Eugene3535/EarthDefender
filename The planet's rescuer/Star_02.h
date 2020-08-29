#pragma once
#include "oStar.h"

class Star_02 : public oStar
{
private:

public:

	Star_02(v2f pos, v2f siz, float speed, IMG& img) : oStar(pos, siz, speed, img)
	{
		rot = 0.03;
		for(int i = 0; i < 2; i++)
		{
			shape[i].move(0,-scr_1w*30);
			shape[i].setFillColor(CLR(255,255,255,140));
		}
	}

	virtual void Update()
	{
		oStar::Update();
		const float slower = time_enemy/time;
		for(int i = 0; i < 2; i++) 
			MoveToAngle(shape[i], speed*slower, 90);
	}

	virtual void Draw()
	{
		oStar::Draw();
	}

	virtual ~Star_02(){}
};