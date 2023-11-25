#pragma once
#include "Turret_Defender.h"
#include "UI_Tank.h"

// В 1900 году население Земли составляло 1,6 миллиардов
// В 1950 – 2,5 миллиарда
// население Земли достигло отметки 7 миллиардов 2011г 31 октября
// 2017 год составляет больше 7,5 миллиардов

class MirrorTank : public System
{
public:

	Shape shpTurret, shpWheel;

	MirrorTank()
	{
		ConstructShape(shpWheel, v2f(0,0), v2f(4,4), texture->Tank_Wheel); shpWheel.setTextureRect(sf::IntRect(0,0,168,168));
		ConstructShape(shpTurret, shpWheel.getPosition(), v2f(4.5,2), texture->Tank_Turret, false);
		shpTurret.setOrigin(shpTurret.getSize().x/3.5f, shpTurret.getSize().y/2.f);
		shpWheel.setFillColor(sf::Color(255,255,255,180));
		shpTurret.setFillColor(sf::Color(255,255,255,180));
	}

	virtual void Update(const v2f& shpRadPos, float& alpha, float& radius, float angle)
	{
		shpWheel.setPosition(v2f(cos(alpha), sin(alpha))*(-radius*0.9f));
		shpWheel.setRotation(GetAngle(shpWheel, shpRadPos)+90);
		shpTurret.setPosition(shpWheel.getPosition());
		shpTurret.setRotation(angle);
	}

	virtual void Draw()
	{
		wnd->draw(shpWheel);
		wnd->draw(shpTurret);
	}

	virtual ~MirrorTank() {}

};

class Effect_Tank_Damage : public System
{
private:

	float timer_life;

public:

	Shape shape[2];
	

	Effect_Tank_Damage(v2f pos)
	{

		ConstructShape(shape[0], pos, v2f(10,10), texture->EFF_Shock_01, false);
		ConstructShape(shape[1], pos, v2f(-10,-10), texture->EFF_Shock_01, false);
		timer_life = 1400;
	}

	virtual void Update(const v2f& posShpWheel)
	{
		timer_life -= time;
		if(timer_life < 0) timer_life = 0;
		shape[0].rotate(-0.2*time);
		shape[1].rotate( 0.2*time);
		for(int i = 0; i < 2; i++)
		{
			shape[i].setPosition(posShpWheel);
			shape[i].setFillColor(sf::Color(255,255,255,255*(timer_life/1400)));
		}
	}

	virtual bool IsEnd()
	{
		return timer_life > 0 ? false : true;
	}

	virtual void Draw()
	{
		for(int i = 0; i < 2; i++)
			wnd->draw(shape[i]);
	}

	virtual ~Effect_Tank_Damage() {}
};

class Tank : public System
{
private:

	float radius, alpha;
	bool isLeft, isRight;
	int frame;
	float timer_animation_tank;

	// Характеристики танка
	
	float speed_move;					// Скорость вращения
	float speed_missle;					// Скорость снарядов
	int damage;							// Урон танка
	float timer_animation_planet;		// Таймер анимации
	int frame_count;
	bool isInstallTurrer;
	bool is_LKM;
	float timer_Plasm_Shoot, TIMER_PLASM_SHOOT;
	float timer_Standart_Shoot, TIMER_STANDART_SHOOT;

public:

	int max_chance_type_bonus; // Ограничитель по выпаду бонусов для непрокачанных способностей
	int upgrage_point;
	MirrorTank mirror;
	UI_Tank ui;

public:

	static Shape shpRadius; 
	static Shape shpWheel; 
	static Shape shpTurret; 
	static Shape shpPlanet; 
	static Shape shpAtmosphere;
	static int level;

public:

	vector<shared_ptr<oMissle>> vec_Missle;
	vector<shared_ptr<Turret_Defender>> vec_Turret_Defender;
	enum STATE_BULLET {standart, ricochet} state_bullet;

	Tank(float radius, int level) : 
		radius(radius*scr_1),
		alpha(0),
		isLeft(false),
		isRight(false),
		timer_animation_tank(0),
		timer_animation_planet(0),
		frame(0),
		speed_missle(0.06),
		speed_move(1.0),
		damage(2),
		state_bullet(standart),
		upgrage_point(1),
		isInstallTurrer(false),
		is_LKM(false),
		timer_Plasm_Shoot(0),
		TIMER_PLASM_SHOOT(113),
		timer_Standart_Shoot(0),
		TIMER_STANDART_SHOOT(216)
	{
		max_chance_type_bonus = 30;
		this->level = level;
		frame_count = 0;
		ConstructShape(shpWheel, v2f(0,-radius/2.f), v2f(4,4), texture->Tank_Wheel); shpWheel.setTextureRect(sf::IntRect(0,0,168,168));
		ConstructShape(shpTurret, shpWheel.getPosition(), v2f(4.5,2.0), texture->Tank_Turret, false);
		ConstructShape(shpRadius, v2f(0,0), v2f(radius,radius)*2.25f, texture->Tank_Radius);
		ConstructShape(shpPlanet, v2f(0,0), v2f(radius, radius)*1.17f, texture->Earth[0]);
		ConstructShape(shpAtmosphere, v2f(0,0), v2f(radius, radius)*1.4f, texture->Tank_Radius);
		shpTurret.setOrigin(shpTurret.getSize().x/3.5f, shpTurret.getSize().y/2.f);
		shpAtmosphere.setFillColor(CLR(140,140,255));
	}

	virtual void LevelUp() 
	{ 
		level++; 
		upgrage_point++; 
		damage = 2 + ( level / (5 + (damage - 2)));
		const float factor = 1.00 + (float(level-1) * 0.01);

		ui.hit_point.setMax(100 * factor);
		ui.energy_point.setMax(150 * factor);

		ui.hit_point.setRegen(ui.hit_point.getRegenStart() + (float(level-1)*0.05f));
		ui.energy_point.setRegen(ui.energy_point.getRegenStart() + (float(level-1)*0.05f));

		ui.hit_point.Regen(level);
		ui.energy_point.Regen(level);
	}

	virtual int GetUpgPts() { return upgrage_point > 0; }
	virtual uint getLevel() const { return level; }

	virtual int GetDamage()
	{
		if(ui.double_damage.isEnd()) return damage;
			return damage*2;
	}

	virtual float getMissleSpeed() const
	{
		return speed_missle;
	}

	virtual void Action()
	{
		if(event.type == sf::Event::KeyPressed)
		{
			if(event.key.code == Key::A || event.key.code == Key:: Left) isLeft = true;
			if(event.key.code == Key::D || event.key.code == Key::Right) isRight = true;

			if(upgrage_point > 0)
			{
				if(event.key.code == Key::Num1		&&	level >= ui.multiple_attack.GetLevelUpTrue())		{ ui.multiple_attack.LevelUp(upgrage_point);		if(max_chance_type_bonus < 40) max_chance_type_bonus = 40;		}
				else if(event.key.code == Key::Num2 &&	level >= ui.hight_overload.GetLevelUpTrue())		{ ui.hight_overload.LevelUp(upgrage_point);			if(max_chance_type_bonus < 50) max_chance_type_bonus = 50;		}
				else if(event.key.code == Key::Num3 &&	level >= ui.world_shield.GetLevelUpTrue())			{ ui.world_shield.LevelUp(upgrage_point);			if(max_chance_type_bonus < 60) max_chance_type_bonus = 60;		}
				else if(event.key.code == Key::Num4 &&	level >= ui.double_damage.GetLevelUpTrue())			{ ui.double_damage.LevelUp(upgrage_point);			if(max_chance_type_bonus < 70) max_chance_type_bonus = 70;		}
				else if(event.key.code == Key::Q &&		level >= ui.time_slow.GetLevelUpTrue())				{ ui.time_slow.LevelUp(upgrage_point);				if(max_chance_type_bonus < 80) max_chance_type_bonus = 80;		}
				else if(event.key.code == Key::E &&		level >= ui.fragment_explosion.GetLevelUpTrue())	{ ui.fragment_explosion.LevelUp(upgrage_point);		if(max_chance_type_bonus < 90) max_chance_type_bonus = 90;		}
				else if(event.key.code == Key::R &&		level >= ui.splash_ricochet.GetLevelUpTrue())		{ ui.splash_ricochet.LevelUp(upgrage_point);		if(max_chance_type_bonus < 100) max_chance_type_bonus = 100;	}
				else if(event.key.code == Key::F &&		level >= ui.signal_sos.GetLevelUpTrue())			{ ui.signal_sos.LevelUp(upgrage_point);				if(max_chance_type_bonus < 110) max_chance_type_bonus = 110;	}
				else if(event.key.code == Key::Z &&		level >= ui.plasm_attack.GetLevelUpTrue())			{ ui.plasm_attack.LevelUp(upgrage_point);			if(max_chance_type_bonus < 120) max_chance_type_bonus = 120;	}
				else if(event.key.code == Key::X &&		level >= ui.mirror_tank.GetLevelUpTrue())			{ ui.mirror_tank.LevelUp(upgrage_point);			if(max_chance_type_bonus < 130) max_chance_type_bonus = 130;	}
				else if(event.key.code == Key::C &&		level >= ui.turret_defender.GetLevelUpTrue())		{ ui.turret_defender.LevelUp(upgrage_point);		if(max_chance_type_bonus < 140) max_chance_type_bonus = 140;	}
				else if(event.key.code == Key::V &&		level >= ui.black_hole.GetLevelUpTrue())			{ ui.black_hole.LevelUp(upgrage_point);				if(max_chance_type_bonus < 150) max_chance_type_bonus = 150;	}
			}
		}


		if(event.type == sf::Event::KeyReleased)
		{
			if(event.key.code == Key::A || event.key.code == Key:: Left) isLeft = false;
			if(event.key.code == Key::D || event.key.code == Key::Right) isRight = false;
		}

		if(event.type == sf::Event::MouseButtonPressed)
		{
			if(event.key.code == sf::Mouse::Left)
			{
				is_LKM = true;

				UI_Ability_Turret& defender = ui.turret_defender;
				if(defender.IsChecked())
				{
					bool isNoInstall = true;
					for(int i = 0; i < 4; i++)
					{
						Shape& installer = defender.shpInstaller_A[i];
						if(GetDistance(installer, cur_p) < installer.getSize().x/2.f)
						{
							for(auto& it = vec_Turret_Defender.begin(); it != vec_Turret_Defender.end(); it++)
							{
								if(GetDistance((*it)->shpWheel, cur_p) < installer.getSize().x/2.f) isNoInstall = false;
							}
							if(isNoInstall)
							{
								vec_Turret_Defender.push_back(make_shared<Turret_Defender>(Turret_Defender(installer.getPosition(), TIMER_PLASM_SHOOT, defender.getDuration())));
								defender.Run();
								defender.Cancel();
							}
						}
					}
					if(isNoInstall) defender.ShowErrorInstall(false);
					else defender.ShowErrorInstall();
				}
				else
				{
					switch (state_bullet)
					{
						case Tank::standart:

						break;

						case Tank::ricochet:

						break;
					}
				}
			}
			if(event.key.code == sf::Mouse::Right)
			{
				if(ui.turret_defender.IsChecked())
				{
					ui.turret_defender.Cancel();
					isInstallTurrer = false;
				}
				else ui.turret_defender.Check();
				
			}
		}

		if(event.type == sf::Event::MouseButtonReleased)
		{
			is_LKM = false;
		}
	}

	virtual void Update(bool isEnemyEnable)
	{
		timer_animation_planet += time;

		if(is_LKM)
		{
			// Стрельба плазмой
			if(!ui.plasm_attack.isEnd())
			{
				timer_Plasm_Shoot -= time;

				if(timer_Plasm_Shoot < 0)
				{
					timer_Plasm_Shoot = TIMER_PLASM_SHOOT;
					float cost_shoot = 0.25;
					float angle = 0;
					if(!ui.multiple_attack.isEnd()) { angle = 30; cost_shoot = 0.50; }
					if(ui.energy_point.getCurrent() > cost_shoot)
					{
						if(ui.multiple_attack.isEnd()) // Если тройная струя выключена
						{
							if(ui.splash_ricochet.isEnd())
							{
								vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(shpTurret, shpTurret.getSize().x/1.5, shpTurret.getRotation()), 
									v2f(2,2), speed_missle*1.5f, shpTurret.getRotation()+angle+(rand()%15-7), texture->MissleT[12], damage, false,false)));

								if(!ui.mirror_tank.isEnd()) 
								{
									vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(mirror.shpTurret, mirror.shpTurret.getSize().x/1.5, mirror.shpTurret.getRotation()), 
										v2f(2,2), speed_missle*1.5f, mirror.shpTurret.getRotation()+angle+(rand()%15-7), texture->MissleT[12], level, false,false)));
								}
							}
							else
							{
								vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(shpTurret, shpTurret.getSize().x/1.5, shpTurret.getRotation()), 
									v2f(2,2), speed_missle*1.5f, shpTurret.getRotation()+angle+(rand()%15-7), texture->MissleT[15], level, false,true)));

								if(!ui.mirror_tank.isEnd()) 
								{
									vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(mirror.shpTurret, mirror.shpTurret.getSize().x/1.5, mirror.shpTurret.getRotation()), 
										v2f(2,2), speed_missle*1.5f, mirror.shpTurret.getRotation()+angle+(rand()%15-7), texture->MissleT[15], level, false,true)));
								}
							}
						}
						else // включена тройная атака
						{
							for(int i = 0; i < 3; i++)
							{
								if(ui.splash_ricochet.isEnd())
								{
									vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(shpTurret, shpTurret.getSize().x/1.5, shpTurret.getRotation()), 
										v2f(2,2), speed_missle*1.5f, shpTurret.getRotation()+angle*i+(rand()%15-7)-30, texture->MissleT[12], level, false,false)));
									
									if(!ui.mirror_tank.isEnd()) 
									{
										vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(mirror.shpTurret, mirror.shpTurret.getSize().x/1.5, mirror.shpTurret.getRotation()), 
											v2f(2,2), speed_missle*1.5f, mirror.shpTurret.getRotation()+angle*i+(rand()%15-7)-30, texture->MissleT[12], level, false,false)));
									}
								}
								else
								{
									vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(shpTurret, shpTurret.getSize().x/1.5, shpTurret.getRotation()), 
										v2f(2,2), speed_missle*1.5f, shpTurret.getRotation()+angle*i+(rand()%15-7)-30, texture->MissleT[15], level, false,true)));

									if(!ui.mirror_tank.isEnd()) 
									{
										vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(mirror.shpTurret, mirror.shpTurret.getSize().x/1.5, mirror.shpTurret.getRotation()), 
											v2f(2,2), speed_missle*1.5f, mirror.shpTurret.getRotation()+angle*i+(rand()%15-7)-30, texture->MissleT[15], level, false,true)));
									}
								}
							}
						}
						if(ui.hight_overload.isEnd()) ui.energy_point.Cast(cost_shoot);
					}
				}
			}
			else // Обычная стрельба
			{
				timer_Standart_Shoot -= time;
				if(timer_Standart_Shoot < 0)
				{
					timer_Standart_Shoot = TIMER_STANDART_SHOOT;
					int c_bullet = 1;
					int cost_shoot = 0;
					float angle = 0;
					if(ui.hight_overload.isEnd()) cost_shoot = 2;
					if(!ui.multiple_attack.isEnd()) { angle = 30; c_bullet = 3; cost_shoot = 3; }
					if(!ui.hight_overload.isEnd()) { cost_shoot = 0; }

					auto Shoot = [c_bullet, angle] (vector<shared_ptr<oMissle>>& vec_Missle, Shape& shape, float& speed_missle, IMG& img) -> void
					{
						for(int i = c_bullet; i > 0; i--)
						{
							vec_Missle.push_back(make_shared<oMissle>(Missle(GetNormalizedPosition(shape, shape.getSize().x/1.5, shape.getRotation()), v2f(2.5,1.25), speed_missle, shape.getRotation()+(i-1)*30-angle, img, level, false)));
						}
					};

					if(ui.energy_point.getCurrent() >= cost_shoot)
					{
						if(!ui.mirror_tank.isEnd()) 
						{
							if(ui.splash_ricochet.isEnd()) Shoot(vec_Missle, mirror.shpTurret, speed_missle, texture->MissleT[2]);
							else Shoot(vec_Missle, mirror.shpTurret, speed_missle, texture->MissleT[3]);
						}
						if(ui.splash_ricochet.isEnd()) Shoot(vec_Missle, shpTurret, speed_missle, texture->MissleT[2]);
						else Shoot(vec_Missle, shpTurret, speed_missle, texture->MissleT[3]);
						ui.energy_point.Cast(cost_shoot);
					}
				}
			}
		}

		if(timer_animation_planet > 16)
		{
			timer_animation_planet = 0;
			shpPlanet.setTexture(&texture->Earth[frame_count]);
			frame_count++;
			if(frame_count > 65) 
			{
				frame_count = 0;
			}
		}
		
		for(auto& it = vec_Turret_Defender.begin(); it != vec_Turret_Defender.end();)
		{
			auto& defender = *(*it);
			if(!defender.IsEnd())
			{
				defender.Update(isEnemyEnable);
				if(defender.Attack())
				{
					float angle = 0;
					if(!ui.multiple_attack.isEnd()) { angle = 30; }
					if(ui.multiple_attack.isEnd())
					{
						if(ui.splash_ricochet.isEnd())
						{
							vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(defender.shpTurret, defender.shpTurret.getSize().x/1.5, defender.shpTurret.getRotation()), 
								v2f(2,2), speed_missle*1.5f, defender.shpTurret.getRotation()+angle+(rand()%15-7), texture->MissleT[12], level, false,false)));
						}
						else
						{
							vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(defender.shpTurret, defender.shpTurret.getSize().x/1.5, defender.shpTurret.getRotation()), 
								v2f(2,2), speed_missle*1.5f, defender.shpTurret.getRotation()+angle+(rand()%15-7), texture->MissleT[15], level, false,true)));
						}
					}
					else
					{
						for(int i = 0; i < 3; i++)
						{
							if(ui.splash_ricochet.isEnd())
							{
								vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(defender.shpTurret, defender.shpTurret.getSize().x/1.5, defender.shpTurret.getRotation()), 
									v2f(2,2), speed_missle*1.5f, defender.shpTurret.getRotation()+angle*i+(rand()%15-7)-30, texture->MissleT[12], level, false,false)));
							}
							else
							{
								vec_Missle.push_back(make_shared<Missle_Plasm>(Missle_Plasm(GetNormalizedPosition(defender.shpTurret, defender.shpTurret.getSize().x/1.5, defender.shpTurret.getRotation()), 
									v2f(2,2), speed_missle*1.5f, defender.shpTurret.getRotation()+angle*i+(rand()%15-7)-30, texture->MissleT[15], level, false,true)));
							}
						}
					}
				}
				it++;
			}
			else it = vec_Turret_Defender.erase(it);
		}

		if(isLeft || isRight)
		{
			timer_animation_tank += time;

			if(isLeft)
			{
				alpha -= time/300;
				if(timer_animation_tank >= 90)
				{
					frame--;
					if(frame <= 0) 
					{
						frame = 3;
					}
					shpWheel.setTextureRect(sf::IntRect(frame*169,0,169,169));

					if(!ui.mirror_tank.isEnd())
					{
						mirror.shpWheel.setTextureRect(sf::IntRect(frame*169,0,169,169));
					}
					timer_animation_tank = 0;
				}
				
			}

			if(isRight)
			{
				alpha += time/300;
				if(timer_animation_tank >= 90)
				{
					frame++;
					if(frame >=3) 
					{
						frame = 0;
					}
					shpWheel.setTextureRect(sf::IntRect(frame*169,0,169,169));

					if(!ui.mirror_tank.isEnd()) 
					{
						mirror.shpWheel.setTextureRect(sf::IntRect(frame*169,0,169,169));
					}
					timer_animation_tank = 0;
				}
			}
		}

		if(ui.turret_defender.IsChecked())
		{
			for(int i = 0; i < 4; i++)
			{
				if(GetDistance(ui.turret_defender.shpInstaller_A[i], cur_p) < ui.turret_defender.shpInstaller_A[i].getSize().x/2.f)
				{
					isInstallTurrer = true;
					ui.turret_defender.shpTurret.setPosition(ui.turret_defender.shpInstaller_A[i].getPosition());
					ui.turret_defender.shpTurret.setFillColor(CLR::Green);
					ui.turret_defender.shpWheel.setPosition(ui.turret_defender.shpInstaller_A[i].getPosition());
					ui.turret_defender.shpWheel.setFillColor(CLR::Green);
				}
				else
				{
					isInstallTurrer = false;
				}
			}
		}

		shpWheel.setPosition(v2f(cos(alpha), sin(alpha))*(radius*0.9f));
		shpWheel.setRotation(GetAngle(shpRadius, shpWheel)+90);
		shpTurret.setPosition(shpWheel.getPosition());
		shpTurret.setRotation(GetAngle(shpWheel, cur_p));
		
		if(!ui.mirror_tank.isEnd()) 
		{
			mirror.Update(shpRadius.getPosition(), alpha, radius, shpTurret.getRotation()-180);
		}

		shpPlanet.rotate(0.01*time);

		for(auto& it = vec_Missle.begin(); it != vec_Missle.end();)
		{
			auto& missle = *(*it);
			if(GetDistance(missle.shape, cam_p) < scr_W*1.5)
			{
				missle.Update();
				it++;
			}
			else
			{
				it = vec_Missle.erase(it);
			}
		}

		cam.setCenter(GetNormalizedPosition(shpWheel.getPosition(), scr_1*15, shpWheel.getRotation()-90));
		if(settings_config.is_cam_static == false) cam.setRotation(shpWheel.getRotation());

		if(upgrage_point > 0) 
		{
			// Если уровень танка достиг требуемого уровня прокачки, то показываем ПЛЮС и ЗВЕЗДОЧКИ
			if( this->level >= ui.multiple_attack.GetLevelUpTrue())		ui.multiple_attack.Effect_Update();
			if( this->level >= ui.hight_overload.GetLevelUpTrue())		ui.hight_overload.Effect_Update();
			if( this->level >= ui.world_shield.GetLevelUpTrue())		ui.world_shield.Effect_Update();
			if( this->level >= ui.double_damage.GetLevelUpTrue())		ui.double_damage.Effect_Update();
			if( this->level >= ui.time_slow.GetLevelUpTrue())			ui.time_slow.Effect_Update();
			if( this->level >= ui.fragment_explosion.GetLevelUpTrue())	ui.fragment_explosion.Effect_Update();
			if( this->level >= ui.splash_ricochet.GetLevelUpTrue())		ui.splash_ricochet.Effect_Update();
			if( this->level >= ui.signal_sos.GetLevelUpTrue())			ui.signal_sos.Effect_Update();
			if( this->level >= ui.plasm_attack.GetLevelUpTrue())		ui.plasm_attack.Effect_Update();
			if( this->level >= ui.mirror_tank.GetLevelUpTrue())			ui.mirror_tank.Effect_Update();
			if( this->level >= ui.turret_defender.GetLevelUpTrue())		ui.turret_defender.Effect_Update();
			if( this->level >= ui.black_hole.GetLevelUpTrue())			ui.black_hole.Effect_Update();
		}
	}

	virtual void Draw()
	{
		wnd->draw(shpRadius);
		wnd->draw(shpPlanet);
		wnd->draw(shpAtmosphere);
		wnd->draw(shpWheel);
		if(!ui.mirror_tank.isEnd()) mirror.Draw();
		for(auto& missle : vec_Missle) missle->Draw();
		wnd->draw(shpTurret);
		for(auto& defender: vec_Turret_Defender) defender->Draw();
		ui.turret_defender.DrawTurret();
	}


	virtual ~Tank()
	{

	}
};

Shape Tank::shpRadius; 
Shape Tank::shpWheel; 
Shape Tank::shpTurret; 
Shape Tank::shpPlanet; 
Shape Tank::shpAtmosphere;
int   Tank::level;

typedef Tank T;