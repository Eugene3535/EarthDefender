#pragma once
#include "System.h"
#include "oMissle.h"

class Turret_Defender : public B
{
private:

	float timer;
	float attack_coldown;
	const float ATTACK_COLDOWN;
	bool isRight;
	sf::Text text_time;

public:

	Shape shpTurret;
	Shape shpWheel;
	

	Turret_Defender(v2f pos, float attack_coldown, float timer) : 
		timer(timer), 
		attack_coldown(attack_coldown), 
		ATTACK_COLDOWN(attack_coldown),
		isRight(bool(rand()%2))
	{
		ConstructShape(shpWheel, pos, v2f(4,4), texture->Defender_Wheel, false);
		ConstructShape(shpTurret, pos, v2f(5,3), texture->Defender_Turret, false);
		shpTurret.setRotation(cam.getRotation());
		shpTurret.setOrigin(shpTurret.getSize().x/3.5f, shpTurret.getSize().y/2.f);
	}

	virtual bool Attack()
	{
		attack_coldown -= time;
		if(attack_coldown < 0)
		{
			attack_coldown = ATTACK_COLDOWN;
			return true;
		}
		return false;
	}

	virtual void Update(bool isEnemyEnable)
	{
		if(isEnemyEnable) timer -= time;
		
		if(isRight) shpTurret.rotate(0.1*time);
		else shpTurret.rotate(-0.1*time);
		std::string str;
		for(int i = 0; i < 4; i++) str.push_back(to_string(timer/1000)[i]);
		ConstructText(text_time, v2f(shpWheel.getPosition()), 2.5, str, font_freshman, CLR::Red);
		text_time.setRotation(cam.getRotation());
	}

	virtual bool IsEnd() const { return timer < 0; }

	virtual void Draw()
	{
		wnd->draw(shpWheel);
		wnd->draw(shpTurret);
		wnd->draw(text_time);
	}

	virtual ~Turret_Defender(){}

};