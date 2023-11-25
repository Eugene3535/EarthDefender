#pragma once
#include "oBang.h"

class Mover_Ship : public System
{
private:

	vector<shared_ptr<Flare>> vec_Flare;
	float timer_create;
	const float TIMER_CREATE;

public:


	Mover_Ship(float timer_create) : timer_create(0), TIMER_CREATE(timer_create)
	{

	}

	virtual void Update(Shape& shape)
	{
		for(auto& it = vec_Flare.begin(); it != vec_Flare.end();)
		{
			Flare& f = *(*it);
			timer_create += time_enemy;

			if(timer_create >= TIMER_CREATE)
			{
				timer_create = 0;
				const v2f &p = shape.getPosition();
				const float &s = shape.getSize().y/5.f;
				for(int i = 0; i < 5; i++)
					vec_Flare.push_back(make_shared<Flare>(Flare(p,s, 400.f, 0.05f, texture->Flare)));
			}

			if(!f.IsEnd())
			{
				f.Update();
				it++;
			}
			else
			{
				it = vec_Flare.erase(it);
			}
		}
	}

	virtual void Draw()
	{
		for(auto& b : vec_Flare) b->Draw();
	}

	virtual ~Mover_Ship() {}
};