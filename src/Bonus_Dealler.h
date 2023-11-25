#pragma once
#include "Bonus.h"

class Bonus_Dealler : public B
{
private:

	float radius;
	float speed;					// Скорость полёта бонусов
	float timer_give, TIMER_GIVE;	// Переодичность выдачи бонусов
	float timer_anim;
	float frame;
	bool isGive;
	bool isOpen;
	float alpha;

public:

	vector<shared_ptr<Bonus>> vec_Bonus;
	Shape shape;

	Bonus_Dealler(v2f siz, float speed, float radius, float timer_give) : 
		radius(radius*scr_1),
		speed(speed),
		timer_give(timer_give),
		TIMER_GIVE(timer_give),
		frame(0),
		timer_anim(0),
		isGive(false),
		isOpen(false),
		alpha(0)
	{
		ConstructShape(shape, v2f(0,0), siz, texture->Bonus_Dealler, false);
		shape.setTextureRect(sf::IntRect(0,0,232,240));
	}

	virtual void Update()
	{
		alpha += time/3000;
		shape.setPosition(v2f(cos(alpha), sin(alpha))*radius);
		shape.setRotation(GetAngle(cam_p, shape.getPosition())-90);
		if(!isGive)
		{
			timer_give -= time;

			if(timer_give < 0)
			{
				timer_anim += time;

				if(!isOpen && timer_anim > 100) // Открываем
				{
					timer_anim = 0;

					if(frame >= 0 && frame < 2) shape.setTextureRect(sf::IntRect(frame*232, 0, 232, 240));
					if(frame >= 3 && frame < 5) shape.setTextureRect(sf::IntRect((frame-3)*232, 240, 232, 240));
					if(frame >= 5 && frame < 7) shape.setTextureRect(sf::IntRect((frame-5)*232, 480, 232, 240));
					if(frame < 7) frame++;
					else
					{
						isOpen = true;
						isGive = true;
					}
				}
			}
		}

		if(timer_give < 0)
		{
			if(isGive) 
			{
				isGive = false;									// Выдаём печеньку
				string type;									// Тип печеньки
				int chance = rand()%100;						// Шанс печеньки

				if(chance < 5 )			type = "heal";			// Хилка
				else if(chance < 10 )	type = "energy";		// Енергия
				else if(chance < 40 )	type = "experience";	// Опыт
				else if(chance < 45 )	type = "power";			// ДД
				else if(chance < 50 )	type = "overload";		// Стрельба без затрат
				else if(chance < 55 )	type = "slow";			// Замедление
				else if(chance < 60 )	type = "multiple";		// Многоструйность
				else if(chance < 65 )	type = "shards";		// Разрывные снаряды
				else if(chance < 70 )	type = "shield";		// Защитное поле планеты
				else if(chance < 75 )	type = "chrono";		// иллюзия танка
				else if(chance < 80 )	type = "explosive";		// Взрыв с рикошетом
				else if(chance < 85 )	type = "turret";		// Защитная установка
				else if(chance < 90 )	type = "plasm";			// Атака плазмой
				else if(chance < 95 )	type = "plasm";			// Защитная установка
				else if(chance < 100 )	type = "plasm";			// Защитная установка
	
				vec_Bonus.push_back(make_shared<Bonus>(Bonus(shape.getPosition(), speed, type)));
			}

			timer_anim += time;
			if(isOpen && timer_anim > 50) // И закрываем
			{
				timer_anim = 0;
				if(frame < 7 && frame >= 5) shape.setTextureRect(sf::IntRect((frame-5)*232, 480, 232, 240));
				if(frame < 5 && frame >= 3) shape.setTextureRect(sf::IntRect((frame-3)*232, 240, 232, 240));
				if(frame < 2 && frame >= 0) shape.setTextureRect(sf::IntRect(frame*232, 0, 232, 240));
				if(frame > 0) frame--;
				else
				{
					isOpen = false;
					timer_give = TIMER_GIVE;
				}
			}
		}
	}

	virtual void Draw()
	{
		wnd->draw(shape);
		for(auto& bonus: vec_Bonus) bonus->Draw();
	}

	virtual ~Bonus_Dealler() {}

};