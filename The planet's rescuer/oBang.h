#pragma once
#include "System.h"

// Маленькие осколки
class VertexBang : public System
{
private:

	float speed;
	float angle;
	bool isRotDir;

public:

	Shape shape;

	VertexBang(v2f pos, v2f siz, float speed, float angle, IMG& img) : speed(speed), angle(angle), isRotDir(rand()%2)
	{
		ConstructShape(shape, pos, siz, img, false);
	}

	virtual void Draw()
	{
		wnd->draw(shape);
	}

	virtual void Update()
	{
		if(isRotDir) shape.rotate(0.3*time);
		else shape.rotate(-0.3*time);
		MoveToAngle(shape, speed, angle);
	}

	virtual ~VertexBang()
	{

	}
};

// Абстрактный класс для осколочных взрывов
class oBang : public System
{
protected:
	
	float timer;
	float siz;
	vector<shared_ptr<VertexBang>> vec_VertexBang;
	
public:

	oBang(float timer, float siz) : timer(timer), siz(siz)
	{

	}

	virtual void Update()
	{
		timer -= time;
	}

	virtual void Draw()
	{
		for(auto& vbang: vec_VertexBang) vbang->Draw();
	}

	virtual bool IsEnd()
	{
		if(timer <= 0) return true;
		return false;
	}

	virtual ~oBang() {}
};

// Наследник - Взрыв при нанесении урона планеты
class BangOnPlanet : public oBang
{
private:

	const float TIMER;
	Shape shape[2];

public:

	BangOnPlanet(v2f pos, float angle, float timer, float siz) : oBang(timer, siz), TIMER(timer)
	{
		for(int i = 0; i < 2; i++) ConstructShape(shape[i], pos, v2f(6,6), texture->EFF_Bang_01, false);
		shape[1].setScale(-1,1);

		for(int i = 0; i < 15; i++)
		{
			vec_VertexBang.push_back(make_shared<VertexBang>(VertexBang(pos, v2f(1,1)*float(rand()%4+1), 0.025f, angle - 90+(12*i), texture->EFF_Shard_Red)));
		}
	}

	virtual void Update()
	{
		oBang::Update();
		shape[0].rotate(0.5*time);
		shape[1].rotate(-0.5*time);
		for(auto vBang: vec_VertexBang) 
		{
			vBang->Update();
			if(timer > 0) 
			{
				vBang->shape.setFillColor(sf::Color(255,255,255,255*(timer/TIMER)));
				for(int i = 0; i < 2; i++) 
				{
					shape[i].setFillColor(sf::Color(255,255,255,255*(timer/TIMER)));
				}
				shape[0].setScale(2-(timer/TIMER),2-(timer/TIMER));
				shape[1].setScale(-2+(timer/TIMER),2-(timer/TIMER));
			}
			else
			{
				vec_VertexBang.clear(); 
				break;
			}
		}
	}

	virtual void Draw()
	{
		oBang::Draw();
		for(int i = 0; i < 2; i++) wnd->draw(shape[i]);
	}

	virtual bool IsEnd()
	{
		if(timer <= 0) return true;
		return false;
	}

	virtual ~BangOnPlanet() {}
};

// Взрыв снаряда при попадании пули во врага
class Bang_Damage : public oBang
{
private:

	const float TIMER;
	Shape shape[2];

public:

	Bang_Damage(v2f pos, float angle, float timer, float siz) : oBang(timer, siz), TIMER(timer)
	{
		for(int i = 0; i < 2; i++) ConstructShape(shape[i], pos, v2f(4,4), texture->EFF_Bang_03, false);
		shape[1].setScale(-1,1);

		for(int i = 0; i < 15; i++)
		{
			vec_VertexBang.push_back(make_shared<VertexBang>(VertexBang(pos, v2f(1,1)*float(rand()%4+1), 0.025, angle - 90+(12*i), texture->EFF_Shard_Green)));
		}
	}

	virtual void Update()
	{
		oBang::Update();
		shape[0].rotate(0.5*time);
		shape[1].rotate(-0.5*time);
		for(auto vBang: vec_VertexBang) 
		{
			vBang->Update();
			if(timer > 0) 
			{
				vBang->shape.setFillColor(CLR(255,255,255,255*(timer/TIMER)));
				for(int i = 0; i < 2; i++) 
				{
					shape[i].setFillColor(CLR(255,255,255,255*(timer/TIMER)));
				}
				shape[0].setScale(2-(timer/TIMER),2-(timer/TIMER));
				shape[1].setScale(-2+(timer/TIMER),2-(timer/TIMER));
			}
			else
			{
				vec_VertexBang.clear(); 
				break;
			}
		}
	}

	virtual void Draw()
	{
		oBang::Draw();
		for(int i = 0; i < 2; i++) 
			wnd->draw(shape[i]);
	}

	virtual bool IsEnd()
	{
		if(timer <= 0) return true;
		return false;
	}

	virtual ~Bang_Damage() {}
};

// Взрыв астероидов при смерти
class Bang_Asteroid : public oBang
{
private:

	const float TIMER;
	Shape shape[2];
	

public:

	Bang_Asteroid(v2f pos, float angle, float timer, float siz) : oBang(timer, siz), TIMER(timer)
	{
		for(int i = 0; i < 2; i++) ConstructShape(shape[i], pos, v2f(siz,siz), texture->EFF_Bang_01, false);
		shape[1].setScale(-1,1);
		for(int i = 0; i < 15; i++)
		{
			vec_VertexBang.push_back(make_shared<VertexBang>(VertexBang(pos, v2f(1,1)*float(rand()%4+1), 0.025, angle - 90+(12*i), texture->EFF_Shard_Red)));
		}
	}

	virtual void Update()
	{
		oBang::Update();
		shape[0].rotate(0.5*time);
		shape[1].rotate(-0.5*time);
		for(auto vBang: vec_VertexBang) 
		{
			vBang->Update();
			if(timer > 0) 
			{
				vBang->shape.setFillColor(CLR(255,255,255,255*(timer/TIMER)));
				for(int i = 0; i < 2; i++) 
				{
					shape[i].setFillColor(CLR(255,255,255,255*(timer/TIMER)));
				}
				shape[0].setScale(2-(timer/TIMER),2-(timer/TIMER));
				shape[1].setScale(-2+(timer/TIMER),2-(timer/TIMER));
			}
			else
			{
				vec_VertexBang.clear(); 
				break;
			}
		}
	}

	virtual void Draw()
	{
		oBang::Draw();
		for(int i = 0; i < 2; i++) wnd->draw(shape[i]);
	}

	virtual bool IsEnd()
	{
		if(timer <= 0) return true;
		return false;
	}

	virtual ~Bang_Asteroid() {}
};

// Языки пламени после взрыва

class Flare : public B
{
private:

	float T_LIFE, t_life;
	float speed;
	float angle;

public:

	Shape shape[2];

	Flare(v2f pos, float siz, float timer_life, float speed, IMG& img, float angle = rand()%360+1) 
		: T_LIFE(timer_life), t_life(timer_life), angle(angle), speed(speed)
	{
		for(int i = 0; i < 2; i++)
			ConstructShape(shape[i], pos, v2f(siz, siz), img, false);
		shape[1].setScale(-1,-1);
	}

	virtual void Update()
	{
		t_life -= time_enemy;
		if(t_life < 0) t_life = 0;
		const float scaler = t_life / T_LIFE;

		for(int i = 0; i < 2; i ++)
		{
			shape[i].setFillColor(CLR(255,255,255,255 * scaler));
			shape[i].setScale(scaler, scaler);
			MoveToAngle(shape[i], speed, angle, true);
		}

		shape[0].rotate(0.2*time_enemy);
		shape[1].rotate(-0.2*time_enemy);
	}

	virtual bool IsEnd() { return t_life == 0; }

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++) 
			wnd->draw(shape[i]);
	}

	virtual ~Flare() {}

};