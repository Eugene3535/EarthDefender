#pragma once
#include "System.h"

class Bonus : public B
{
protected:

	float speed;
	bool isRotDir;
	string type;

public:

	Shape shpBonus, shpPlato, shpCircle[2];

	Bonus(v2f pos, float speed, string type) : 
		speed(speed), isRotDir(rand()%2), type(type)
	{
		ConstructShape(shpPlato, pos, v2f(5,5), texture->Bonus_Plato, false);
		ConstructShape(shpBonus, pos, v2f(4.5,4.5), false);
		ConstructShape(shpCircle[0], pos, v2f(6,6), texture->EFF_Bonus_Border, false);
		shpCircle[1] = shpCircle[0];
		shpCircle[1].setScale(-1,-1);

			 if(type == "heal") shpBonus.setTexture(&texture->Bonus_HP[0]);
		else if(type == "experience") shpBonus.setTexture(&texture->Bonus_Experience[0]);
		else if(type == "slow") shpBonus.setTexture(&texture->Bonus_Slow[2]);
		else if(type == "energy") shpBonus.setTexture(&texture->Bonus_Energy[0]);
		else if(type == "shards") shpBonus.setTexture(&texture->Bonus_Fragment_Explosion[2]);
		else if(type == "multiple") shpBonus.setTexture(&texture->Bonus_Multiple[2]);
		else if(type == "power") shpBonus.setTexture(&texture->Bonus_Power[2]);
		else if(type == "overload") shpBonus.setTexture(&texture->Bonus_Shock[2]);
		else if(type == "chrono") shpBonus.setTexture(&texture->Bonus_Mirror_Tank[2]);
		else if(type == "shield") shpBonus.setTexture(&texture->Bonus_Shield[2]);
		else if(type == "explosive") shpBonus.setTexture(&texture->Bonus_Splash_Ricochet[2]);
		else if(type == "turret") shpBonus.setTexture(&texture->Bonus_Turret_Defender[2]);
		else if(type == "plasm") shpBonus.setTexture(&texture->Bonus_Plasm_Attack[2]);
		else if(type == "signal_sos") shpBonus.setTexture(&texture->Bonus_Signal_SOS[2]);
		else if(type == "blackhole") shpBonus.setTexture(&texture->Bonus_Black_Hole[2]);
	}
	virtual string GetType() const { return type; }

	virtual void Update(float angle)
	{
		shpCircle[1].rotate(0.3f*time);
		shpCircle[0].rotate(-0.3f*time);
		if(isRotDir) shpPlato.rotate(0.05*time);
		else shpPlato.rotate(-0.05*time);
		shpBonus.setRotation(cam.getRotation());
		MoveToAngle(shpPlato, speed, angle);
		shpBonus.setPosition(shpPlato.getPosition());
		for(int i = 0; i < 2; i++) 
			shpCircle[i].setPosition(shpBonus.getPosition());
	}

	virtual void Draw()
	{
		wnd->draw(shpPlato);
		for(int i = 0; i < 2; i++) 
			wnd->draw(shpCircle[i]);
		wnd->draw(shpBonus);
	}

	virtual ~Bonus() {}
};