#pragma once
#include "Tank.h"
#include "BackGround.h"
#include "Enemy_Asteroid.h"
#include "Enemy_Dodge.h"
#include "Enemy_Transporter.h"
#include "Enemy_Kamikadze.h"
#include "Enemy_Circle_Fly.h"
#include "Enemy_Boss_03.h"
#include "Enemy_Blink.h"
#include "Enemy_Mirror.h"
#include "Bonus.h"
#include "Bang_Ricochet.h"
#include "oBang.h"
#include "oMirror_Effect.h"
#include "Signal_SOS_Unit.h"
#include "BlackHole.h"

// Добавить способность призывающую добрых нло


class LevelName : public System
{
private:
	

	float timer_create;
	vector<shared_ptr<oMissle>> vec_Missle_E;
	Shape shpLevel, shpNum[2];
	float timer_preview;

public:

	LevelName(USHORT n1, USHORT n2) : timer_preview(7500), timer_create(0)
	{
		ConstructShape(shpLevel, v2f(0,0), v2f(65,13), texture->UI_Text_Level);
		ConstructShape(shpNum[0], v2f(40,0), v2f(16,16), texture->UI_Num[n1]);
		ConstructShape(shpNum[1], v2f(49,0), v2f(16,16), texture->UI_Num[n2]);
	}

	LevelName(USHORT n1) : timer_preview(7500), timer_create(0)
	{
		ConstructShape(shpLevel, v2f(0,0), v2f(65,13), texture->UI_Text_Level);
		ConstructShape(shpNum[0], v2f(40,0), v2f(16,16), texture->UI_Num[n1]);
	}

	virtual void Update()
	{
		const float A = 90 + cam.getRotation();
		if(timer_preview > 0) timer_create += time;
		if(timer_create > 50) 
		{
			shpLevel.setFillColor(sf::Color(75+rand()%100,75+rand()%100,75+rand()%100, 255*(timer_preview/7500)));
			shpNum[0].setFillColor(sf::Color(75+rand()%100,75+rand()%100,75+rand()%100, 255*(timer_preview/7500)));
			shpNum[1].setFillColor(sf::Color(75+rand()%100,75+rand()%100,75+rand()%100, 255*(timer_preview/7500)));
			for(int i = 0; i < scr_W; i += ( scr_1 * 5 ) )
			{
				vec_Missle_E.push_back(make_shared<Missle_Lighting_Ball>(
					Missle_Lighting_Ball(GetNormalizedPosition(v2f(cam_p.x - (scr_W / 2) + i, -scr_H), -scr_H / 2.f,  A), v2f(6,6), 0.125f, A, texture->MissleT[rand()%13], 10, false)));
			}
			timer_create = 0;
		}

		for(auto& it = vec_Missle_E.begin(); it != vec_Missle_E.end();)
		{
			oMissle& missle = *(*it);
			if(GetDistance(missle.shape, cam_p) < scr_W*1.5) 
			{
				missle.setAngle(A);
				missle.Update();
				it++;
			}
			else
			{
				it = vec_Missle_E.erase(it);
			}
		}

		timer_preview -= time;
		if(timer_preview < 0) 
		{
			timer_preview = 0;
		}
		else
		{
			for(int i = 0; i < 2; i++) shpNum[i].setFillColor(sf::Color(255,255,255,255*(timer_preview/7500)));
		}
	}

	virtual bool IsEndPreview() 
	{
		timer_preview = 0; // Стереть к релизу
		return timer_preview == 0 ? true : false; 
	}

	virtual void Draw()
	{
		for(auto& it : vec_Missle_E) wnd->draw((*it).shape);
		if(!IsEndPreview())
		{
			wnd->draw(shpLevel);
			for(int i = 0; i < 2; i++) wnd->draw(shpNum[i]);
		}
	}

	LevelName(){}
	virtual ~LevelName() {}
};

class FloatText : public System
{
private:

	sf::Text text;
	float timer_life;
	const float TIMER_LIFE;
	const v2f POSITION;
	float alpha;
	sf::Color m_color;

public:

	FloatText(v2f pos, float siz, string str, float timer_life, sf::Color color = sf::Color::Yellow) : timer_life(timer_life), POSITION(pos), alpha(0), TIMER_LIFE(timer_life), m_color(color)
	{
		ConstructText(text, pos, siz, str, font_freshman, color);
	}

	virtual void Update()
	{
		if(timer_life < 0) timer_life = 0;
		else
		{
			const float scaler = timer_life / TIMER_LIFE;
			timer_life -= time;
			alpha += time * 0.003;
			text.setRotation(cam.getRotation());
			text.setPosition(POSITION + v2f(cos(alpha), sin(alpha)) * scr_1);
			text.setColor(sf::Color(m_color.r, m_color.g, m_color.b, m_color.a * scaler ));
			text.setScale(2 - scaler, 2 - scaler);
		}
	}

	virtual bool IsEnd() { return timer_life == 0; }

	virtual void Draw()
	{
		wnd->draw(text);
	}

	virtual ~FloatText() {}

};

class oLevel : public System
{
protected:

	sf::Text text_wave_name;	// Названия волны
	LevelName level_Name;		// Приветствие уровня

	Tank tank;
	BackGround background;
	vector<shared_ptr<oEnemy>> vec_Enemy;
	vector<shared_ptr<oMissle>> vec_Enemy_Missle;
	vector<shared_ptr<oBang>> vec_Bang;
	vector<shared_ptr<Bonus>> vec_Bonus;
	vector<shared_ptr<Effect_Tank_Damage>> vec_Effect_Tank_Damage;
	vector<shared_ptr<Bang_Ricochet>> vec_Splash_Ricochet;
	vector<shared_ptr<oMirror_Effect>> vec_Mirror_Spec_Effect;
	vector<shared_ptr<Flare>> vec_Flare;
	vector<shared_ptr<FloatText>> vec_FloatText;
	vector<shared_ptr<Signal_SOS_Unit_01>> vec_SOS_Unit;
	BlackHole black_Hole;
	float timer_cleate_mirror_spec_effect;
	v2f pEnemySpawn;

	bool isWin;
	bool isDefeat;

public:

	virtual bool IsWin () 
	{
		return isWin;
	}

	virtual bool IsDefeat()
	{
		return isDefeat;
	}

	oLevel() : tank(6,1), timer_cleate_mirror_spec_effect(0), pEnemySpawn(0,0), black_Hole(tank.ui.black_hole.getLevel()), isWin(false), isDefeat(false)
	{
		planet_p = tank.shpPlanet.getPosition();
	}

	virtual inline v2f& SP()
	{
		pEnemySpawn = GetNormalizedPosition(tank.shpPlanet, scr_W, rand()%360);
		return pEnemySpawn;
	}

	virtual void AddDropChanceBonus(oEnemy& enemy)
	{
		string type; // Тип бонуса
		int chance_type = rand()%tank.max_chance_type_bonus;		// Определение типа бонуса
		// Повышаем шанс на выпад бонуса
		int drop_add = (enemy.GetLevel() * 16) - (tank.level / 6);
		// минимальный ограничитель
		if(drop_add < 10) drop_add = 10;

		if(tank.ui.chance_drop.IsDrop(drop_add)) 
		{
			if(chance_type < 10 ) type = "heal";				// Хилка
			else if(chance_type < 20 ) type = "energy";			// Энергия
			else if(chance_type < 30 ) type = "experience";		// Опыт
			else if(chance_type < 40 ) type = "multiple";		// ДД
			else if(chance_type < 50 ) type = "overload";		// Стрельба без затрат энергии
			else if(chance_type < 60 ) type = "shield";			// Замедление
			else if(chance_type < 70 ) type = "power";			// Многоструйность
			else if(chance_type < 80 ) type = "slow";			// Разрывные снаряды
			else if(chance_type < 90 ) type = "shards";			// Защитное поле планеты
			else if(chance_type < 100 ) type = "explosive";		// иллюзия танка
			else if(chance_type < 110 ) type = "signal_sos";	// Взрыв с рикошетом
			else if(chance_type < 120 ) type = "plasm";			// Сигнал SOS
			else if(chance_type < 130 ) type = "chrono";		// Защитная установка
			else if(chance_type < 140 ) type = "turret";		// Атака плазмой
			else if(chance_type <= 150 ) type = "blackhole";	// Черная дыра

			vec_Bonus.push_back(make_shared<Bonus>(Bonus(enemy.shape.getPosition(), 0.025f, type)));
		}

		// Добавляем плавающий текст получения бонуса "Опыт и его кол-во"
		vec_FloatText.push_back(make_shared<FloatText>(FloatText(enemy.shape.getPosition(),1.5f, "EXP +" + to_string(enemy.GetLevel()*36), 2000, sf::Color(180, 0, 165))));
		if(tank.ui.experience.addExp(enemy.GetLevel() * 36)) // Если апнули уровень
		{
			tank.LevelUp();
			// Добавляем плавающий текст получения нового уровня
			vec_FloatText.push_back(make_shared<FloatText>(FloatText(tank.shpWheel.getPosition(),3.5f, "LVL UP" + to_string(tank.getLevel()) + "!", 4000, sf::Color::Green)));
		}
	}

	virtual void SPEN(uint num, string name, float factor = 1.0f, v2f pos = v2f(0,0))
	{
		const float &f = factor;
		const string n = name;
		const int NNN = 99999;
		v2f p(0,0); 

		vector<shared_ptr<oEnemy>>& vE = vec_Enemy;

		typedef Enemy_Asteroid		EA01;
		typedef Enemy_Shooting		ES01;
		typedef Enemy_Boss_03		EBS1;
		typedef Enemy_Transporter	ET01;
		typedef Enemy_Dodge			ED01;
		typedef Enemy_Blink			EB01;
		typedef Enemy_Mirror		EM01;
		
		
		for(int i = 0; i < num; i++)
		{
			if(pos == v2f(0,0)) p = SP();
			else p = pos; 

			const int r = rand()%2; 
			const int& rn = r;

			//				ID											 pos			size	 speed		 hp          lvl
				 if (n == "as01")	{ vE.push_back(make_shared<EA01>(EA01(p,	v2f(3.50,3.50),	 0.012,		4 *f,		 1 *f,			texture->Asteroid[rn], n)));	}
			else if (n == "as02")	{ vE.push_back(make_shared<EA01>(EA01(p,	v2f(4.25,4.25),	 0.012,		8 *f,		 2 *f,			texture->Asteroid[rn], n)));	}
			else if (n == "as03")	{ vE.push_back(make_shared<EA01>(EA01(p,	v2f(5.00,5.00),	 0.011,		12*f,		 3 *f,			texture->Asteroid[ 2], n)));	}
			else if (n == "as04")	{ vE.push_back(make_shared<EA01>(EA01(p,	v2f(6.00,6.00),	 0.011,		18*f,		 4 *f,			texture->Asteroid[ 2], n)));	}
			else if (n == "as05")	{ vE.push_back(make_shared<EA01>(EA01(p,	v2f(8.00,8.00),	 0.010,		24*f,		 5 *f,			texture->Asteroid[ 3], n)));	}
			else if (n == "as06")	{ vE.push_back(make_shared<EA01>(EA01(p,	v2f(10.0,10.0),	 0.010,		30*f,		 6 *f,			texture->Asteroid[ 3], n)));	}
			else if (n == "as07")	{ vE.push_back(make_shared<EA01>(EA01(p,	v2f(12.0,12.0),	 0.010,		40*f,		 7 *f,			texture->Asteroid[ 4], n)));	}
			else if (n == "asB1")	{ vE.push_back(make_shared<EA01>(EA01(p,	v2f(16.0,16.0),	 0.010,		50*f,		 8 *f,			texture->Asteroid[ 5], n)));	}
			else if (n == "asB2")	{ vE.push_back(make_shared<EA01>(EA01(p,	v2f(20.0,20.0),	 0.010,		65*f,		 9 *f,			texture->Asteroid[ 0], n)));	}
			else if (n == "asB3")	{ vE.push_back(make_shared<EA01>(EA01(p,	v2f(24.0,24.0),	 0.010,		80*f,		 10*f,			texture->Asteroid[ 6], n)));	}
			//																									 coldown 																									 				 																																		
			else if (n == "sh01")	{ vE.push_back(make_shared<ES01>(ES01(p,	v2f(5.00,2.70),	 0.009,		6 *f, 3000,  2 *f,			texture->Enemy[ 0], n)));		}
			else if (n == "sh02")	{ vE.push_back(make_shared<ES01>(ES01(p,	v2f(6.00,4.00),	 0.008,		12*f, 2800,  3 *f,			texture->Enemy[ 1], n)));		}
			else if (n == "sh03")	{ vE.push_back(make_shared<ES01>(ES01(p,	v2f(7.00,6.00),	 0.007,		18*f, 2600,  4 *f,			texture->Enemy[10], n)));		}
			else if (n == "sh04")	{ vE.push_back(make_shared<ES01>(ES01(p,	v2f(9.50,8.20),	 0.007,		26*f, 2400,  5 *f,			texture->Enemy[ 9], n)));		}
			else if (n == "sh05")	{ vE.push_back(make_shared<ES01>(ES01(p,	v2f(10.0,6.50),	 0.007,		34*f, 2200,  6 *f,			texture->Enemy[ 3], n)));		}
			else if (n == "sh06")	{ vE.push_back(make_shared<ES01>(ES01(p,	v2f(12.0,5.50),	 0.007,		42*f, 2000,  7 *f,			texture->Enemy[15], n)));		}
			else if (n == "sh07")	{ vE.push_back(make_shared<ES01>(ES01(p,	v2f(15.0,15.0),	 0.006,		52*f, 1900,  8 *f,			texture->Enemy[12], n)));		}
			else if (n == "shB1")	{ vE.push_back(make_shared<ES01>(ES01(p,	v2f(18.0,18.0),	 0.005,		62*f, 1800,  9 *f,			texture->Enemy[ 5], n)));		}
			else if (n == "shB2")	{ vE.push_back(make_shared<ES01>(ES01(p,	v2f(20.0,16.0),	 0.004,		74*f, 1700,  10*f,			texture->Enemy[18], n)));		}
			else if (n == "shB3")	{ vE.push_back(make_shared<ES01>(ES01(p,	v2f(22.0,15.0),	 0.004,		86*f, 1600,  12*f,			texture->Enemy[17], n)));		}
			//																			 						 		  fly   radius																												
			else if (n == "dg01")	{ vE.push_back(make_shared<ED01>(ED01(p,	v2f(5.00,5.00),	 0.007,		8  *f,		 2 *f,  4.00f,	texture->UFO[0],	n)));		}
			else if (n == "dg02")	{ vE.push_back(make_shared<ED01>(ED01(p,	v2f(6.50,6.50),	 0.007,		16 *f,		 4 *f,  4.25f,	texture->UFO[1],	n)));		}
			else if (n == "dg03")	{ vE.push_back(make_shared<ED01>(ED01(p,	v2f(8.00,8.00),	 0.007,		24 *f,		 6 *f,  4.50f,	texture->UFO[2],	n)));		}
			else if (n == "dg04")	{ vE.push_back(make_shared<ED01>(ED01(p,	v2f(9.50,9.50),	 0.007,		32 *f,		 8 *f,  4.75f,	texture->UFO[3],	n)));		}
			else if (n == "dg05")	{ vE.push_back(make_shared<ED01>(ED01(p,	v2f(12.0,12.0),	 0.007,		50 *f,		 12*f,  5.00f,	texture->UFO[4],	n)));		}
			else if (n == "dgB1")	{ vE.push_back(make_shared<ED01>(ED01(p,	v2f(16.0,16.0),	 0.007,		100*f,		 25*f,  6.50f,	texture->UFO[5],	n)));		}
			//																				 					  coldown																									
			else if (n == "tr01")	{ vE.push_back(make_shared<ET01>(ET01(p,	v2f(6.00,6.00),	 0.006,		16 *f, 3000, 4 *f,			texture->Transporter[0], n)));	}
			else if (n == "tr02")	{ vE.push_back(make_shared<ET01>(ET01(p,	v2f(8.00,8.00),	 0.006,		28 *f, 3000, 7 *f,			texture->Transporter[1], n)));	}
			else if (n == "tr03")	{ vE.push_back(make_shared<ET01>(ET01(p,	v2f(10.0,10.0),	 0.006,		40 *f, 2800, 10*f,			texture->Transporter[2], n)));	}
			else if (n == "tr04")	{ vE.push_back(make_shared<ET01>(ET01(p,	v2f(12.0,12.0),	 0.006,		55 *f, 2800, 15*f,			texture->Transporter[3], n)));	}
			else if (n == "tr05")	{ vE.push_back(make_shared<ET01>(ET01(p,	v2f(14.0,14.0),	 0.006,		65 *f, 2600, 20*f,			texture->Transporter[4], n)));	}
																							 																																						
			else if (n == "bl01")	{ vE.push_back(make_shared<EB01>(EB01(p,	v2f(4.00,5.00),	 0.007,		12 *f,		 5 *f,			texture->Enemy[6 ], n, 3500, 750)));	}
			else if (n == "bl02")	{ vE.push_back(make_shared<EB01>(EB01(p,	v2f(7.00,4.50),	 0.007,		18 *f,		 8 *f,			texture->Enemy[13], n, 3300, 600)));	}
			else if (n == "bl03")	{ vE.push_back(make_shared<EB01>(EB01(p,	v2f(10.0,10.0),	 0.007,		30 *f,		 12*f,			texture->Enemy[19], n, 3100, 500)));	}
			else if (n == "bl04")	{ vE.push_back(make_shared<EB01>(EB01(p,	v2f(14.0,12.0),	 0.007,		45 *f,		 17*f,			texture->Enemy[11], n, 2800, 450)));	}
			else if (n == "bl05")	{ vE.push_back(make_shared<EB01>(EB01(p,	v2f(14.0,5.00),	 0.007,		60 *f,		 22*f,			texture->Enemy[16], n, 2500, 350)));	}
																							 																																							
			else if (n == "mr01")	{ vE.push_back(make_shared<EM01>(EM01(p,	v2f(5.00,5.00),	 0.006,		12 *f,		 4 *f,			texture->Enemy[20], n, 200)));			}
			else if (n == "mr02")	{ vE.push_back(make_shared<EM01>(EM01(p,	v2f(9.00,4.00),	 0.006,		20 *f,		 6 *f,			texture->Enemy[2 ], n, 200)));			}
			else if (n == "mr03")	{ vE.push_back(make_shared<EM01>(EM01(p,	v2f(7.00,5.50),	 0.006,		30 *f,		 9 *f,			texture->Enemy[8 ], n, 200)));			}
			else if (n == "mr04")	{ vE.push_back(make_shared<EM01>(EM01(p,	v2f(9.00,6.00),	 0.006,		40 *f,		 12*f,			texture->Enemy[7 ], n, 200)));			}
			else if (n == "mr05")	{ vE.push_back(make_shared<EM01>(EM01(p,	v2f(10.0,7.00),	 0.006,		52 *f,		 16*f,			texture->Enemy[21], n, 200)));			}
			else if (n == "mr06")	{ vE.push_back(make_shared<EM01>(EM01(p,	v2f(12.0,6.00),	 0.006,		64 *f,		 20*f,			texture->Enemy[22], n, 200)));			}
			else if (n == "mr07")	{ vE.push_back(make_shared<EM01>(EM01(p,	v2f(14.0,7.50),	 0.006,		80 *f,		 24*f,			texture->Enemy[23], n, 200)));			}
			//																				 					  coldown																																									
			else if (n == "trb1")	{ vE.push_back(make_shared<ET01>(ET01(p,	v2f(10.0,10.0),	 0.000,		NNN*f, 750,	  1*f,			texture->Transporter[0], n, false, true)));		}
			else if (n == "trb2")	{ vE.push_back(make_shared<ET01>(ET01(p,	v2f(10.0,10.0),	 0.000,		NNN*f, 700,	  1*f,			texture->Transporter[1], n, false, true)));		}
			else if (n == "trb3")	{ vE.push_back(make_shared<ET01>(ET01(p,	v2f(10.0,10.0),	 0.000,		NNN*f, 650,	  1*f,			texture->Transporter[2], n, false, true)));		}
			else if (n == "trb4")	{ vE.push_back(make_shared<ET01>(ET01(p,	v2f(10.0,10.0),	 0.000,		NNN*f, 600,	  1*f,			texture->Transporter[3], n, false, true)));		}
			else if (n == "trb5")	{ vE.push_back(make_shared<ET01>(ET01(p,	v2f(10.0,10.0),	 0.000,		NNN*f, 400,	  1*f,			texture->Transporter[4], n, false, true)));		}
																							 																															
			else if (n == "BO01")	{ vE.push_back(make_shared<EBS1>(EBS1(p,	v2f(15.0,15.0),	 0.500,		200*f,		 25 *f,			texture->Boss_03[0], n, 1200, 3000, true)));	}
			else if (n == "BO02")	{ vE.push_back(make_shared<EBS1>(EBS1(p,	v2f(17.0,17.0),	 0.475,		350*f,		 50 *f,			texture->Boss_03[1], n, 1100, 2750, true)));	}
			else if (n == "BO03")	{ vE.push_back(make_shared<EBS1>(EBS1(p,	v2f(19.0,19.0),	 0.450,		550*f,		 75 *f,			texture->Boss_03[2], n, 1000, 2500, true)));	}
			else if (n == "BO04")	{ vE.push_back(make_shared<EBS1>(EBS1(p,	v2f(21.0,21.0),	 0.425,		800*f,		 100*f,			texture->Boss_03[3], n, 900, 2250, true)));		}
			else if (n == "BO05")	{ vE.push_back(make_shared<EBS1>(EBS1(p,	v2f(25.0,25.0),	 0.400,		999*f,		 125*f,			texture->Boss_03[4], n, 800, 2000, true)));		}

			//else if(name == "circle_fly_01")	vec_Enemy.push_back(make_shared<Enemy_Circle_Fly>(Enemy_Circle_Fly(p, v2f(8,8), 0.0065, 9, 4, texture->Enemy[12], name)));
		}
	}

	virtual void Update()
	{
		// Условие поражения
		// if(tank.ui.people.people <= 0 || tank.ui.hit_point.getCurrent() <= 0) isDefeat = true;

		level_Name.Update();
		background.Update();
		static float timer_mirror_enemy_create = 0;
		timer_mirror_enemy_create += time;
		if(timer_mirror_enemy_create >= 100)
		{
			for(auto& enemy: vec_Enemy)
			{
				for(int i = 1; i < 8; i++)
				{
					if(enemy->name == "mr0"+to_string(i)) 
						vec_Mirror_Spec_Effect.push_back(make_shared<Mirror_Effect_One_No_Rot>(Mirror_Effect_One_No_Rot(enemy->shape)));
				}
			}

			timer_mirror_enemy_create = 0;
		}
		if(!tank.ui.time_slow.isEnd()) time_enemy /= 4;

		if(!isWin && !isDefeat)
		{
			// Столкновение снарядов игрока и врагов
			for(auto& it1 = vec_SOS_Unit.begin(); it1 != vec_SOS_Unit.end();)
			{
				auto& sos_u = *(*it1);
				for(auto& it2 : vec_Enemy)
				{
					auto& e = *it2;
					for(auto& it3 = sos_u.vec_Missle.begin(); it3 != sos_u.vec_Missle.end();)
					{
						auto& m = *(*it3);
						if(GetCollisionCircle(e.shape, m.shape))
						{
							e.Damage(tank.GetDamage(), 1000);
							vec_Bang.push_back(make_shared<Bang_Asteroid>(Bang_Asteroid(e.shape.getPosition(), GetAngle(e.shape, m.shape), 1500, e.GetSizeBang())));
							it3 = sos_u.vec_Missle.erase(it3);
							if(e.IsDead())
							{
								AddDropChanceBonus(e);
							}
						}
						else it3++;
					}
				}
				it1++;
				sos_u.Update();
			}

			for(auto& it1 = tank.vec_Missle.begin(); it1 != tank.vec_Missle.end();)
			{
				auto& missle_t = *(*it1);
				for(auto& it2 = vec_Enemy_Missle.begin(); it2 != vec_Enemy_Missle.end();)
				{
					auto& missle_e = *(*it2);
					if(GetCollisionCircle(missle_t.shape, missle_e.shape))
					{
						vec_Bang.push_back(make_shared<Bang_Damage>(Bang_Damage(missle_e.shape.getPosition(), GetAngle(missle_t.shape, missle_e.shape), 500, missle_e.shape.getSize().x/1.5f)));
						it2 = vec_Enemy_Missle.erase(it2);
					}
					else it2++;
				}
				it1++;
			}

			// Действие замедления
			if(!tank.ui.time_slow.isEnd())
			{
				timer_cleate_mirror_spec_effect += time;

				if(timer_cleate_mirror_spec_effect > 40)
				{
					for(auto tank_missle: tank.vec_Missle)
						vec_Mirror_Spec_Effect.push_back(make_shared<Mirror_Effect_One_No_Rot>(Mirror_Effect_One_No_Rot(tank_missle->shape)));
					timer_cleate_mirror_spec_effect = 0;
				}
			}

			for(auto& it = vec_Mirror_Spec_Effect.begin();  it != vec_Mirror_Spec_Effect.end();)
			{
				auto& mirror = *(*it);
				if(!mirror.getKill()) 
				{
					mirror.Update();
					mirror.Scaling();
					it++;
				}
				else it = vec_Mirror_Spec_Effect.erase(it);
			}

			for(auto& it = vec_Flare.begin(); it != vec_Flare.end();)
			{
				auto& flare = *(*it);
				if(flare.IsEnd())
				{
					it = vec_Flare.erase(it);
				}
				else
				{
					flare.Update();
					it++;
				}
			}
			// Проходимся по всем летящим бонусам
			for(auto& it = vec_Bonus.begin(); it != vec_Bonus.end();)
			{
				auto& bonus = *(*it);

				// Если танк подобрал бонус
				if(GetCollisionCircle(bonus.shpPlato, tank.shpWheel))
				{
					// Если это бонус опыта
					if(bonus.GetType() == "experience")
					{
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, -scr_1*40, cam.getRotation()),2.25f, "Exp +" + to_string((tank.level * 18) + 36) + "!", 2000, sf::Color(180, 0, 165))));
						if(tank.ui.experience.addExp((tank.level * 18) + 36)) 
						{
							tank.LevelUp();
						}
					}
					// Неуязвимость
					else if(bonus.GetType() == "shield")
					{
						tank.ui.world_shield.Run();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-24),2.25f, "Shield!", 1200, sf::Color::White)));
					}
					// Многоструйная атака
					else if(bonus.GetType() == "multiple")
					{
						tank.ui.multiple_attack.Run();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-48),2.25f, "Multiple!", 1200, sf::Color::Cyan)));
					}
					// Замедление времени
					else if(bonus.GetType() == "slow")
					{
						tank.ui.time_slow.Run();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-72),2.25f, "Slow!", 1200, sf::Color(255, 20, 252))));
					}
					// Двойной урон
					else if(bonus.GetType() == "power")
					{
						tank.ui.double_damage.Run();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-96),2.25f, "Power!", 1200, sf::Color::Blue)));
					}
					// Нескончаемая энергия
					else if(bonus.GetType() == "overload")
					{
						tank.ui.hight_overload.Run();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-120),2.25f, "Overload!", 1200, sf::Color(255, 102, 0))));
					}
					// Разрыв врагов при убийстве
					else if(bonus.GetType() == "shards")
					{
						tank.ui.fragment_explosion.Run();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-144),2.25f, "Shards!", 1200, sf::Color(204, 255, 153))));
					}
					// Хронотанк
					else if(bonus.GetType() == "chrono")
					{
						tank.ui.mirror_tank.Run();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-168),2.25f, "Chrono!", 1200, sf::Color(204, 102, 153))));
					}
					// Взрывные снаряды с рикошетом
					else if(bonus.GetType() == "explosive")
					{
						tank.ui.splash_ricochet.Run();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-192),2.25f, "Explosive!", 1200, sf::Color::Red)));
					}
					// Атака плазмой
					else if(bonus.GetType() == "plasm")
					{
						tank.ui.plasm_attack.Run();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-216),2.25f, "Plasm!", 1200, sf::Color(0, 153, 255))));
					}
					// Защитная установка
					else if(bonus.GetType() == "turret")
					{
						tank.ui.turret_defender.KeepTime();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-240),2.25f, "Turret +1", 1200, sf::Color::Yellow)));
					}
					// Пополнение энергии
					else if(bonus.GetType() == "energy")
					{
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-264),2.25f, "Energy +" + to_string(int(tank.ui.energy_point.getMax()/10)), 1200, sf::Color(102, 153, 255))));
						tank.ui.energy_point.Regen(tank.ui.energy_point.getMax()/10);
					}
					// Пополнение здоровья
					else if(bonus.GetType() == "heal")
					{
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-288),2.25f, "Heal +" + to_string(int(tank.ui.hit_point.getMax()/10)), 1200, sf::Color::Green)));
						tank.ui.hit_point.Regen(tank.ui.hit_point.getMax()/10);
					}
					// Сигнал SOS
					else if(bonus.GetType() == "signal_sos")
					{
						
						for(int i = 0; i != tank.ui.signal_sos.getLevel(); i++)
						{
							vec_SOS_Unit.push_back(make_shared<Signal_SOS_Unit_01>(Signal_SOS_Unit_01(SP(), v2f(5,5), 0.0225f, texture->SOS[0], 600, tank.ui.signal_sos.getLevel())));
						}

						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-312),2.25f, "SOS!", 1200, sf::Color::Magenta)));
						tank.ui.signal_sos.Run();
					}
					// Черная дыра
					else if(bonus.GetType() == "blackhole")
					{
						tank.ui.black_hole.Run();
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(GetNormalizedPosition(tank.shpPlanet, scr_1*25, cam.getRotation()-336),2.25f, "Black Hole!", 1200, sf::Color::White)));
						black_Hole.Reset(tank.ui.black_hole.getLevel());
					}
					it = vec_Bonus.erase(it);
				}
				else
				{
					// Двигаем бонусы к танку
					bonus.Update(GetAngle(bonus.shpBonus, tank.shpWheel));
					if(GetDistance(bonus.shpPlato, cam_p) < scr_W*1.5) it++;
					else it = vec_Bonus.erase(it);
				}
			}

			tank.Update(!vec_Enemy.empty());
			tank.ui.Update(!vec_Enemy.empty());
			
			for(auto& it = vec_Splash_Ricochet.begin(); it != vec_Splash_Ricochet.end();)
			{
				Bang_Ricochet& ricochet = *(*it);

				if(!ricochet.IsEnd())
				{
					ricochet.Update();
					it++;
				}
				else
				{
					it = vec_Splash_Ricochet.erase(it);
				}
			}

			if(!tank.ui.black_hole.isEnd()) black_Hole.Update();

			const float damage_BH = black_Hole.GetDamage();

			for(auto& it1 = vec_Enemy.begin(); it1 != vec_Enemy.end();)
			{
				auto& enemy = *(*it1);
				if(!enemy.IsDead())
				{
					enemy.Update();
					if(!tank.ui.world_shield.isEnd()) // Защитное поле
					{
						 // Если враг столкнулся с защитным полем
						if(GetCollisionCircle(tank.ui.world_shield.shpShield[0], enemy.shape) && !enemy.isBoss)
						{
							vec_FloatText.push_back(make_shared<FloatText>(FloatText(enemy.shape.getPosition(),1.f, "Absorb!", 1200, sf::Color::White)));
							enemy.Damage(9999);
						}
					}

					if(!tank.ui.black_hole.isEnd())
					{
						if(GetCollisionCircle(enemy.shape, black_Hole.shape[0])  && !enemy.isBoss  && (enemy.name != "trb1" || enemy.name != "trb2" || enemy.name != "trb3" || enemy.name != "trb4" || enemy.name != "trb5"))
						{
							if(damage_BH > 0)
							{
								enemy.Damage(damage_BH, 100, .33);
								string s = to_string(damage_BH);
								while(s.length() > 4)
								{
									s.pop_back();
									if(s.length() != '0' && s.length() - 1 == '.') break;
								}

								vec_FloatText.push_back(make_shared<FloatText>(FloatText(enemy.shape.getPosition(), 1.75f, s, 500, sf::Color::Green)));
							}
							MoveToAngle(enemy.shape, 0.065f, GetAngle(enemy.shape, black_Hole.shape[0]), false);
						}
					}

					for(auto& it2 = tank.vec_Missle.begin(); it2 != tank.vec_Missle.end();) // Пули танка
					{
						auto& missle = *(*it2);
						// Если пуля танка попала во врага
						if(GetCollisionCircle(missle.shape, enemy.shape) && (enemy.name != "trb1" || enemy.name != "trb2" || enemy.name != "trb3" || enemy.name != "trb4" || enemy.name != "trb5"))
						{
							enemy.Damage(tank.GetDamage(), 1000);
							vec_FloatText.push_back(make_shared<FloatText>(FloatText(enemy.shape.getPosition(), 1.75f, to_string(tank.GetDamage()), 1200, sf::Color::Green)));
							vec_Bang.push_back(make_shared<Bang_Damage>(Bang_Damage(enemy.shape.getPosition(), GetAngle(tank.shpWheel, enemy.shape), 750, 1.5f)));

							if(tank.ui.splash_ricochet.isEnd())
							{
								it2 = tank.vec_Missle.erase(it2);
							}
							else // Если активен сплеш рикошет
							{
								missle.setAngle(GetAngle(enemy.shape, missle.shape));
								missle.Update();
								vec_Splash_Ricochet.push_back(make_shared<Bang_Ricochet>(Bang_Ricochet(enemy.shape.getPosition(), v2f(15,15), 22.5)));
								for(auto& ricochet : vec_Splash_Ricochet)
								{
									// Если враг оказался в зоне поражения взрыва
									for(auto& enemy2 : vec_Enemy)
									{
										if(GetCollisionCircle(ricochet->shape[0], enemy2->shape))
										{
											enemy2->Damage(tank.GetDamage()/2, 1000);
											vec_FloatText.push_back(make_shared<FloatText>(FloatText(tank.shpWheel.getPosition(), 1.75f, to_string(tank.GetDamage()/2), 1200, sf::Color::Green)));
										}
									}
								}
								it2++;
							}
							if(enemy.IsDead()) AddDropChanceBonus(enemy);
						}
						else it2++;
					}

					// Если вражеский корабль врезался в планету
					if(GetCollisionCircle(tank.shpPlanet, enemy.shape))
					{
						enemy.Damage(99999);
						tank.ui.people.Kill(enemy.GetMaxHp() * 2);
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(tank.shpPlanet.getPosition(),2.25f, to_string(int(enemy.GetMaxHp()) * 2) + "!", 2500, sf::Color::Red)));
					}
					// Если вражеский корабль врезался в танк
					if(GetCollisionCircle(tank.shpWheel, enemy.shape))
					{
						enemy.Damage(99999);
						tank.ui.hit_point.Damage(enemy.GetMaxHp());
						vec_FloatText.push_back(make_shared<FloatText>(FloatText(tank.shpWheel.getPosition(), 2.25f, "-" + to_string(int(enemy.GetMaxHp()) / 2) + "!", 2500, sf::Color::Red)));
						vec_Effect_Tank_Damage.push_back(make_shared<Effect_Tank_Damage>(Effect_Tank_Damage(tank.shpWheel.getPosition())));
					}

					// Враг атакует
					if(enemy.IsAttack())
					{
						// Shootings
						if(enemy.name == "sh01") vec_Enemy_Missle.push_back(make_shared<Missle>(Missle(GetNormalizedPosition(enemy.shape, enemy.shape.getSize().y/1.75f, enemy.shape.getRotation()), v2f(4.5,2.1), 0.025, GetAngle(enemy.shape, tank.shpPlanet), texture->MissleT[5], 4, true)));
						else if(enemy.name == "sh02") vec_Enemy_Missle.push_back(make_shared<Missle_Lighting_Ball>(Missle_Lighting_Ball(GetNormalizedPosition(enemy.shape, enemy.shape.getSize().y/1.75f, enemy.shape.getRotation()), v2f(4,4), 0.025f, GetAngle(enemy.shape, tank.shpPlanet), texture->MissleT[9], 8, true)));
						else if(enemy.name == "sh03") vec_Enemy_Missle.push_back(make_shared<Missle>(Missle(GetNormalizedPosition(enemy.shape, enemy.shape.getSize().y/1.75f, enemy.shape.getRotation()), v2f(3.5,1.75), 0.024f, GetAngle(enemy.shape, tank.shpPlanet), texture->MissleT[4], 12, true)));
						else if(enemy.name == "sh04") vec_Enemy_Missle.push_back(make_shared<Missle>(Missle(GetNormalizedPosition(enemy.shape, enemy.shape.getSize().y/1.75f, enemy.shape.getRotation()), v2f(5,2.25), 0.022f, GetAngle(enemy.shape, tank.shpPlanet), texture->MissleT[5], 15, true)));
						else if(enemy.name == "sh05") vec_Enemy_Missle.push_back(make_shared<Missle_Lighting_Ball>(Missle_Lighting_Ball(GetNormalizedPosition(enemy.shape, enemy.shape.getSize().y/1.75f, enemy.shape.getRotation()), v2f(5,5), 0.020f, GetAngle(enemy.shape, tank.shpPlanet), texture->MissleT[13], 18, true)));
						else if(enemy.name == "sh06") vec_Enemy_Missle.push_back(make_shared<Missle>(Missle(GetNormalizedPosition(enemy.shape, enemy.shape.getSize().y/1.75f, enemy.shape.getRotation()), v2f(6,2.75), 0.027f, GetAngle(enemy.shape, tank.shpPlanet), texture->MissleT[3], 21, true)));
						else if(enemy.name == "sh07") vec_Enemy_Missle.push_back(make_shared<Missle_Lighting_Ball>(Missle_Lighting_Ball(GetNormalizedPosition(enemy.shape, enemy.shape.getSize().y/1.75f, enemy.shape.getRotation()), v2f(7.5,7.5), 0.030f, GetAngle(enemy.shape, tank.shpPlanet), texture->MissleT[8], 24, true)));						
						
						// Big shooting
						else if(enemy.name == "shB1") vec_Enemy_Missle.push_back(make_shared<Missle_Lighting_Ball>(Missle_Lighting_Ball(GetNormalizedPosition(enemy.shape, enemy.shape.getSize().y/1.75f, enemy.shape.getRotation()), v2f(7,7), 0.027f, GetAngle(enemy.shape, tank.shpPlanet), texture->MissleT[6], 48, true)));
						else if(enemy.name == "shB2") vec_Enemy_Missle.push_back(make_shared<Missle>(Missle(GetNormalizedPosition(enemy.shape, enemy.shape.getSize().y/1.75f, enemy.shape.getRotation()), v2f(8,3.1), 0.031f, GetAngle(enemy.shape, tank.shpPlanet), texture->MissleT[3], 72, true)));
						else if(enemy.name == "shB3") vec_Enemy_Missle.push_back(make_shared<Missle_Lighting_Ball>(Missle_Lighting_Ball(GetNormalizedPosition(enemy.shape, enemy.shape.getSize().y/1.75f, enemy.shape.getRotation()), v2f(10,10), 0.033f, GetAngle(enemy.shape, tank.shpPlanet), texture->MissleT[15], 96, true)));

						// Обыкновенные транспортёры запускают камикадзе
						typedef Enemy_Kamikadze KA;
						const v2f& epos = enemy.shape.getPosition();

							 if(enemy.name == "tr01") { vec_Enemy.emplace_back(make_shared<KA>(KA(epos, v2f(5,2.5),enemy.GetSpeed(),  6, 2, texture->Kamikadze[0], "ka01")));		break;}
						else if(enemy.name == "tr02") { vec_Enemy.emplace_back(make_shared<KA>(KA(epos, v2f(6,3),	enemy.GetSpeed(), 14, 3, texture->Kamikadze[1], "ka02")));		break;}
						else if(enemy.name == "tr03") { vec_Enemy.emplace_back(make_shared<KA>(KA(epos, v2f(7,3.5),enemy.GetSpeed(), 25, 5, texture->Kamikadze[2], "ka03")));		break;}
						else if(enemy.name == "tr04") { vec_Enemy.emplace_back(make_shared<KA>(KA(epos, v2f(8,4),	enemy.GetSpeed(), 38, 7, texture->Kamikadze[3], "ka04")));		break;}
						else if(enemy.name == "tr05") { vec_Enemy.emplace_back(make_shared<KA>(KA(epos, v2f(9,4.5),enemy.GetSpeed(), 54, 9, texture->Kamikadze[4], "ka05")));		break;}
																																												
						// Транспортёр на боссе выпускает камикадзе																												
						else if(enemy.name == "trb1" && rand()%100 <  6) { vec_Enemy.emplace_back(make_shared<KA>(KA(epos, v2f(5,5), 0.00, 10, 3, texture->Boss_03[0], "kab1")));	break;}
						else if(enemy.name == "trb2" && rand()%100 <  7) { vec_Enemy.emplace_back(make_shared<KA>(KA(epos, v2f(6,6), 0.00, 18, 5, texture->Boss_03[1], "kab2")));	break;}
						else if(enemy.name == "trb3" && rand()%100 <  8) { vec_Enemy.emplace_back(make_shared<KA>(KA(epos, v2f(7,7), 0.00, 30, 8, texture->Boss_03[2], "kab3")));	break;}
						else if(enemy.name == "trb4" && rand()%100 <  9) { vec_Enemy.emplace_back(make_shared<KA>(KA(epos, v2f(8,8), 0.00, 45, 12,texture->Boss_03[3], "kab4")));	break;}
						else if(enemy.name == "trb5" && rand()%100 < 10) { vec_Enemy.emplace_back(make_shared<KA>(KA(epos, v2f(9,9), 0.00, 70, 16,texture->Boss_03[4], "kab5")));	break;}
						
					}
					if(GetDistance(enemy.shape, v2f(0,0)) < scr_W*1.5) it1++;
					else it1 = vec_Enemy.erase(it1);
				}
				else
				{
					// Создаём взрыв от смерти врага
					const short num_flare = rand()%5+4;
					for(int i = 0; i < num_flare; i++) vec_Flare.push_back(make_shared<Flare>(Flare(enemy.shape.getPosition(), enemy.shape.getSize().x/4.f, 2000, 0.008, texture->EFF_Flare)));
					vec_Bang.push_back(make_shared<Bang_Asteroid>(Bang_Asteroid(enemy.shape.getPosition(), GetAngle(tank.shpWheel, enemy.shape), 1600, enemy.GetSizeBang()/1.5)));
					
					// Создаём осколки от взрыва враза
					if(!tank.ui.fragment_explosion.isEnd())
					{
						const float angle = 360/(tank.ui.fragment_explosion.getLevel()+6);

						for(int i = 0; i < tank.ui.fragment_explosion.getLevel()+6; i++)
						{
							if(tank.ui.splash_ricochet.isEnd()) tank.vec_Missle.push_back(make_shared<Missle>(Missle(enemy.shape.getPosition(), v2f(3,1.25), tank.getMissleSpeed(), angle*i, texture->MissleT[2], tank.GetDamage(), false)));
							else tank.vec_Missle.push_back(make_shared<Missle>(Missle(enemy.shape.getPosition(), v2f(3,1.25), tank.getMissleSpeed(), angle*i, texture->MissleT[3], tank.GetDamage(), false)));
						}
					}
					it1 = vec_Enemy.erase(it1);
				}
			}

			// Вражеские пули
			for(auto& it = vec_Enemy_Missle.begin(); it != vec_Enemy_Missle.end();)
			{
				auto& missle = *(*it);
				// Попадание вражеской пули в планету
				if(GetCollisionCircle(missle.shape, tank.shpPlanet))
				{
					tank.ui.people.Kill(missle.getDamage() / 2);
					vec_FloatText.push_back(make_shared<FloatText>(FloatText(tank.shpPlanet.getPosition(),1.5f, to_string(missle.getDamage() / 2) + "!", 1250, sf::Color::Red)));
					vec_Bang.push_back(make_shared<Bang_Damage>(Bang_Damage(missle.shape.getPosition(), GetAngle(missle.shape, tank.shpPlanet), 500, 1)));
					it = vec_Enemy_Missle.erase(it);
				}

				// Попадание вражеской пули в танк
				else if(GetCollisionCircle(missle.shape, tank.shpWheel))
				{
					tank.ui.hit_point.Damage(missle.getDamage());
					vec_FloatText.push_back(make_shared<FloatText>(FloatText(tank.shpWheel.getPosition(),2.f, to_string(missle.getDamage())+"!", 2000, sf::Color::Red)));
					vec_Bang.push_back(make_shared<Bang_Damage>(Bang_Damage(missle.shape.getPosition(), GetAngle(missle.shape, tank.shpPlanet), 500, 1)));
					it = vec_Enemy_Missle.erase(it);
				}
				// Попадание вражеской пули в силовое поле
				else if(!tank.ui.world_shield.isEnd() && GetCollisionCircle(missle.shape, tank.ui.world_shield.shpShield[0]))
				{
					vec_FloatText.push_back(make_shared<FloatText>(FloatText(missle.shape.getPosition(),0.65f, "Absorb!", 1000, sf::Color::White)));
					vec_Bang.push_back(make_shared<Bang_Damage>(Bang_Damage(missle.shape.getPosition(), GetAngle(missle.shape, tank.ui.world_shield.shpShield[0]), 500, 1)));
					it = vec_Enemy_Missle.erase(it);
				}
				else 
				{
					missle.Update();
					it++;			
				}
			}

			// Апдейтим все взрывы
			for(auto& it = vec_Bang.begin(); it != vec_Bang.end();)
			{
				auto& bang = *(*it);
				if(!bang.IsEnd())
				{
					bang.Update();
					it++;
				}
				else
				{
					it = vec_Bang.erase(it);
				}
			}

			// Апдейтим эффект урона по танку
			for(auto &it = vec_Effect_Tank_Damage.begin(); it != vec_Effect_Tank_Damage.end();)
			{
				Effect_Tank_Damage &effect = *(*it);
				if(!effect.IsEnd())
				{
					effect.Update(tank.shpWheel.getPosition());
					it++;
				}
				else it = vec_Effect_Tank_Damage.erase(it);
			}
		}
		else if(isWin)
		{


		}
		else if(isDefeat)
		{


		}
	}

	virtual void Action()
	{
		//if(level_Name.IsEndPreview()) 
		tank.Action();
		if(event.type == sf::Event::MouseButtonPressed)
		{
			if(event.key.code == sf::Mouse::Left)
			{
				if(tank.upgrage_point > 0 )
				{
					if(tank.ui.multiple_attack.IsContains() && tank.level >= tank.ui.multiple_attack.GetLevelUpTrue())			{	tank.ui.multiple_attack.LevelUp(tank.upgrage_point);    if(tank.max_chance_type_bonus < 40) tank.max_chance_type_bonus = 40;	}
					if(tank.ui.hight_overload.IsContains() && tank.level >= tank.ui.hight_overload.GetLevelUpTrue())			{	tank.ui.hight_overload.LevelUp(tank.upgrage_point);		if(tank.max_chance_type_bonus < 50) tank.max_chance_type_bonus = 50;	}
					if(tank.ui.world_shield.IsContains() && tank.level >= tank.ui.world_shield.GetLevelUpTrue())				{	tank.ui.world_shield.LevelUp(tank.upgrage_point);		if(tank.max_chance_type_bonus < 60) tank.max_chance_type_bonus = 60;	}
					if(tank.ui.double_damage.IsContains() && tank.level >= tank.ui.double_damage.GetLevelUpTrue())				{	tank.ui.double_damage.LevelUp(tank.upgrage_point);		if(tank.max_chance_type_bonus < 70) tank.max_chance_type_bonus = 70;	}
					if(tank.ui.time_slow.IsContains() && tank.level >= tank.ui.time_slow.GetLevelUpTrue())						{	tank.ui.time_slow.LevelUp(tank.upgrage_point);			if(tank.max_chance_type_bonus < 80) tank.max_chance_type_bonus = 80;	}
					if(tank.ui.fragment_explosion.IsContains() && tank.level >= tank.ui.fragment_explosion.GetLevelUpTrue())	{	tank.ui.fragment_explosion.LevelUp(tank.upgrage_point);	if(tank.max_chance_type_bonus < 90) tank.max_chance_type_bonus = 90;	}
					if(tank.ui.splash_ricochet.IsContains() && tank.level >= tank.ui.splash_ricochet.GetLevelUpTrue())			{	tank.ui.splash_ricochet.LevelUp(tank.upgrage_point);	if(tank.max_chance_type_bonus < 100) tank.max_chance_type_bonus = 100;	}
					if(tank.ui.signal_sos.IsContains() && tank.level >= tank.ui.signal_sos.GetLevelUpTrue())					{	tank.ui.signal_sos.LevelUp(tank.upgrage_point);			if(tank.max_chance_type_bonus < 110) tank.max_chance_type_bonus = 110;	}
					if(tank.ui.plasm_attack.IsContains() && tank.level >= tank.ui.plasm_attack.GetLevelUpTrue())				{	tank.ui.plasm_attack.LevelUp(tank.upgrage_point);		if(tank.max_chance_type_bonus < 120) tank.max_chance_type_bonus = 120;	}
					if(tank.ui.mirror_tank.IsContains() && tank.level >= tank.ui.mirror_tank.GetLevelUpTrue())					{	tank.ui.mirror_tank.LevelUp(tank.upgrage_point);		if(tank.max_chance_type_bonus < 130) tank.max_chance_type_bonus = 130;	}
					if(tank.ui.turret_defender.IsContains() && tank.level >= tank.ui.turret_defender.GetLevelUpTrue())			{	tank.ui.turret_defender.LevelUp(tank.upgrage_point);	if(tank.max_chance_type_bonus < 140) tank.max_chance_type_bonus = 140;	}
					if(tank.ui.black_hole.IsContains() && tank.level >= tank.ui.black_hole.GetLevelUpTrue())					{	tank.ui.black_hole.LevelUp(tank.upgrage_point);			if(tank.max_chance_type_bonus < 150) tank.max_chance_type_bonus = 150;	}
				}													
			}
		}
	}

	virtual void Draw()
	{
		background.Draw();
		if(!tank.ui.world_shield.isEnd())
		{
			for(int i = 0; i < 2; i++) wnd->draw(tank.ui.world_shield.shpEffect[i]);
			for(int i = 0; i < 2; i++) wnd->draw(tank.ui.world_shield.shpShield[i]);
		}

		for(auto& mirror: vec_Mirror_Spec_Effect) mirror->Draw();
		wnd->setView(cam);
		tank.Draw();
		for(auto& effect: vec_Effect_Tank_Damage) effect->Draw();

		//////////////////////////////////////////////////////////////////////////////////
		if(!tank.ui.black_hole.isEnd()) black_Hole.Draw();

		for(auto& enemy: vec_Enemy) enemy->Draw();
		for(auto& flare: vec_Flare) flare->Draw();
		for(auto& sos_u: vec_SOS_Unit) sos_u->Draw();
		for(auto& bang: vec_Bang) bang->Draw();
		for(auto& ricochet: vec_Splash_Ricochet) ricochet->Draw();
		for(auto& bonus: vec_Bonus) bonus->Draw();
		for(auto& enemy_missle: vec_Enemy_Missle) enemy_missle->Draw();
		
		for(auto& it = vec_FloatText.begin(); it != vec_FloatText.end();)
		{
			FloatText& FText = *(*it);
			if(FText.IsEnd())
			{
				it = vec_FloatText.erase(it);
			}
			else
			{
				FText.Update();
				FText.Draw();
				it++;
			}
		}

		/////////////////////// Поворот
		float angle = cam.getRotation();
		v2f pos = cam.getCenter();
		cam.setCenter(0,0);
		cam.setRotation(0);
		wnd->setView(cam);
		cam.setRotation(angle);
		cur_p = wnd->mapPixelToCoords(sf::Mouse::getPosition(*wnd));
		//level_Name.Draw();

		tank.ui.Draw();

		if(tank.upgrage_point > 0)
		{
			if(tank.level >= tank.ui.multiple_attack.GetLevelUpTrue())		tank.ui.multiple_attack.DrawUpgrade();		
			if(tank.level >= tank.ui.hight_overload.GetLevelUpTrue())		tank.ui.hight_overload.DrawUpgrade();		
			if(tank.level >= tank.ui.world_shield.GetLevelUpTrue())			tank.ui.world_shield.DrawUpgrade();			
			if(tank.level >= tank.ui.double_damage.GetLevelUpTrue())		tank.ui.double_damage.DrawUpgrade();		
			if(tank.level >= tank.ui.time_slow.GetLevelUpTrue())			tank.ui.time_slow.DrawUpgrade();			
			if(tank.level >= tank.ui.fragment_explosion.GetLevelUpTrue())	tank.ui.fragment_explosion.DrawUpgrade();	
			if(tank.level >= tank.ui.splash_ricochet.GetLevelUpTrue())		tank.ui.splash_ricochet.DrawUpgrade();		
			if(tank.level >= tank.ui.signal_sos.GetLevelUpTrue())			tank.ui.signal_sos.DrawUpgrade();			
			if(tank.level >= tank.ui.plasm_attack.GetLevelUpTrue())			tank.ui.plasm_attack.DrawUpgrade();			
			if(tank.level >= tank.ui.mirror_tank.GetLevelUpTrue())			tank.ui.mirror_tank.DrawUpgrade();			
			if(tank.level >= tank.ui.turret_defender.GetLevelUpTrue())		tank.ui.turret_defender.DrawUpgrade();		
			if(tank.level >= tank.ui.black_hole.GetLevelUpTrue())			tank.ui.black_hole.DrawUpgrade();			
		}

		if(tank.level < tank.ui.multiple_attack.GetLevelNeed())		tank.ui.multiple_attack.DrawLock();		
		if(tank.level < tank.ui.hight_overload.GetLevelNeed())		tank.ui.hight_overload.DrawLock();		
		if(tank.level < tank.ui.world_shield.GetLevelNeed())		tank.ui.world_shield.DrawLock();			
		if(tank.level < tank.ui.double_damage.GetLevelNeed())		tank.ui.double_damage.DrawLock();		
		if(tank.level < tank.ui.time_slow.GetLevelNeed())			tank.ui.time_slow.DrawLock();			
		if(tank.level < tank.ui.fragment_explosion.GetLevelNeed())	tank.ui.fragment_explosion.DrawLock();	
		if(tank.level < tank.ui.splash_ricochet.GetLevelNeed())		tank.ui.splash_ricochet.DrawLock();		
		if(tank.level < tank.ui.signal_sos.GetLevelNeed())			tank.ui.signal_sos.DrawLock();			
		if(tank.level < tank.ui.plasm_attack.GetLevelNeed())		tank.ui.plasm_attack.DrawLock();			
		if(tank.level < tank.ui.mirror_tank.GetLevelNeed())			tank.ui.mirror_tank.DrawLock();			
		if(tank.level < tank.ui.turret_defender.GetLevelNeed())		tank.ui.turret_defender.DrawLock();		
		if(tank.level < tank.ui.black_hole.GetLevelNeed())			tank.ui.black_hole.DrawLock();			


		cam.setCenter(pos);
		wnd->setView(cam);
		cur_p = wnd->mapPixelToCoords(sf::Mouse::getPosition(*wnd));

		SCursor.setPosition(cur_p);
		if(!tank.ui.black_hole.isEnd()) 
		{
			SCursor.setFillColor(sf::Color(255,255,255,120));
			SCursor.setScale(v2f(0.6,0.6));
		}
		else
		{
			SCursor.setFillColor(sf::Color::White);
			SCursor.setScale(v2f(1,1));
		}
		wnd->draw(SCursor);
	}

	virtual ~oLevel() { }
};