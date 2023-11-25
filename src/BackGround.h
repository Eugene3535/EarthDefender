#pragma once
#include "Star_01.h"
#include "Star_02.h"

class BackGround : public System
{
private:

	float timer_star_create;			// Таймер создания звезд
	float timer_galaxy_create;			// Таймер создания галактик
	float alpha;						// 
	Shape shpUniverse1, shpUniverse2;

public:

	vector<shared_ptr<oStar>> vec_Star;

	BackGround() : timer_star_create(0), timer_galaxy_create(0), alpha(0)
	{
		ConstructShape(shpUniverse1, v2f(0,0), v2f(scr_W, scr_W)/scr_1*2.f, texture->Universe1, false);
		ConstructShape(shpUniverse2, v2f(0,0), v2f(scr_W, scr_W)/scr_1*2.f, texture->Universe2, false);
		for(int i = 0; i < 180; i++) 
		{
			const v2f size = v2f(1,1)*float(rand()%5+1);
			vec_Star.push_back(make_shared<Star_01>(Star_01(v2f(rand()%scr_W-(scr_W/2),rand()%scr_W-(scr_W/2)), size, float((rand()%6+8)*(size.x*0.0003f)), texture->BG_Star[rand()%10])));
		}
	}

	virtual void Update()
	{
		const float C = cos(alpha);
		const float S = sin(alpha);
		const sf::Color color(255 * (1.f+-S)/2.f, 255 * (1.f+-C)/2.f, 255 * (1.f+-cos(alpha/2))/2.f, 50);
		shpUniverse1.setRotation((-C*10) + 45);
		shpUniverse1.setScale(v2f(1+(-C/5),1+(-S/5)));
		shpUniverse1.setPosition(v2f(-C,-S)*(15*scr_1));

		shpUniverse2.setRotation((C*10) + 45);
		shpUniverse2.setScale(v2f(1+(C/5),1+(S/5)));
		shpUniverse2.setFillColor(sf::Color(color.b,color.r,color.g,175));
		shpUniverse2.setPosition(v2f(C,S)*(15*scr_1));

		alpha += 0.00015*time;

		if(timer_star_create >= 60)
		{
			timer_star_create = 0;
			const v2f size = v2f(1,1)*float(rand()%4+2);
			vec_Star.push_back(make_shared<Star_01>(Star_01(v2f(rand()%scr_W-(scr_W/2),-scr_W/2), size, float((rand()%6+8)*(size.x*0.0003f)), texture->BG_Star[rand()%10])));
		}
		else  timer_star_create += time_enemy;

		if(timer_galaxy_create <= 0)
		{
			timer_galaxy_create = rand()%6000+8000;
			const v2f size = v2f(1,1)*float(rand()%20+20);
			int rnd = rand()%20;
			vec_Star.push_back(make_shared<Star_02>(Star_02(v2f(rand()%scr_W-(scr_W/2),-scr_W/2), size, float((rand()%4+8))*0.001f, texture->BG_Galaxy[rnd])));
		}
		else timer_galaxy_create -= time_enemy;

		for(auto& it = vec_Star.begin(); it != vec_Star.end();)
		{
			auto& star = *(*it);
			if(GetDistance(star.shape[0], cam_p) < scr_W*1.5)
			{
				star.Update();
				it++;
			}
			else it = vec_Star.erase(it);
		}
	}

	virtual void Draw()
	{
		wnd->draw(shpUniverse1);
		wnd->draw(shpUniverse2);
		for(auto& star: vec_Star) star->Draw();
	}

	virtual ~BackGround() { }
};