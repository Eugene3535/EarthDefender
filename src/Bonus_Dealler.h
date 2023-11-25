#pragma once
#include "Bonus.h"

class Bonus_Dealler : public B
{
private:

	float radius;
	float speed;					// �������� ����� �������
	float timer_give, TIMER_GIVE;	// ������������� ������ �������
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

				if(!isOpen && timer_anim > 100) // ���������
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
				isGive = false;									// ����� ��������
				string type;									// ��� ��������
				int chance = rand()%100;						// ���� ��������

				if(chance < 5 )			type = "heal";			// �����
				else if(chance < 10 )	type = "energy";		// �������
				else if(chance < 40 )	type = "experience";	// ����
				else if(chance < 45 )	type = "power";			// ��
				else if(chance < 50 )	type = "overload";		// �������� ��� ������
				else if(chance < 55 )	type = "slow";			// ����������
				else if(chance < 60 )	type = "multiple";		// ���������������
				else if(chance < 65 )	type = "shards";		// ��������� �������
				else if(chance < 70 )	type = "shield";		// �������� ���� �������
				else if(chance < 75 )	type = "chrono";		// ������� �����
				else if(chance < 80 )	type = "explosive";		// ����� � ���������
				else if(chance < 85 )	type = "turret";		// �������� ���������
				else if(chance < 90 )	type = "plasm";			// ����� �������
				else if(chance < 95 )	type = "plasm";			// �������� ���������
				else if(chance < 100 )	type = "plasm";			// �������� ���������
	
				vec_Bonus.push_back(make_shared<Bonus>(Bonus(shape.getPosition(), speed, type)));
			}

			timer_anim += time;
			if(isOpen && timer_anim > 50) // � ���������
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