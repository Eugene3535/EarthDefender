#include "oLevel.h"

class Level_01 : public oLevel
{
private:

	float timer_start_wave;		// ����� ����� �������� ����
	uint WAVE_PART_MAX;			// ������ ��������� � �����
	uint wave_num;				// ����� ������� �����
	uint WAVE_NUM_END;			// ����� ���� �� ������
	uint wave_part;				// ����� ����� �����

	float timer_alpha_wname;	// ����� �� ������ ������������ ������ �������� �����
	bool isBossLife;			// ���� ���
	bool isBossCreateTime;		// ������� ����� �����

public:

	Level_01() : WAVE_PART_MAX(10), WAVE_NUM_END(3), timer_alpha_wname(0), isBossLife(false), isBossCreateTime(false)
	{
		wave_part = 0;
		wave_num = 1;
		timer_start_wave = 6000;
		level_Name = LevelName(1);
		audio->music_game[0].play();
	}

	inline void CreateBoss()
	{
		static float timer_spawner = 0;
		timer_spawner += time;
		static int a = 0;

		if(timer_spawner >= 100)
		{
			if(a < 360) 
			{
				SPEN(1, "trb1", 1.0, GetNormalizedPosition(tank.shpPlanet, 75*scr_1, a));
				a += 10;
			}
			else
			{
				SPEN(1,"BO01", 1.0, GetNormalizedPosition(tank.shpPlanet, 68*scr_1, rand()%360));
				isBossLife = true;
				isBossCreateTime = false;
			}
			timer_spawner = 0;
		}
	}

	inline void BossLife()
	{
		bool kill_boss = true;
		for(auto it = vec_Enemy.begin(); it != vec_Enemy.end();)
		{
			auto& enemy = *(*it);
			if(enemy.isBoss) kill_boss = false;
			it++;
		}

		static float timer_killer = 0;

		if(!vec_Enemy.empty()) timer_killer += time;
		else isBossLife = false;

		if(kill_boss && timer_killer >= 200) 
		{ 
			timer_killer = 0; 
			vec_Enemy.back()->Damage(99999999);
			vec_Bonus.push_back(make_shared<Bonus>(Bonus(vec_Enemy.back()->shape.getPosition(), 0.075f, "experience")));
		}
	}

	virtual void Update()
	{
		// ���� ����������� ����������� � ������ ������ ����
		if(level_Name.IsEndPreview() && vec_Enemy.empty()) timer_start_wave -= time;

		if(timer_alpha_wname > 0) timer_alpha_wname -= time;
		else timer_alpha_wname = 0;

		// ������ ���� ���������
		if(timer_start_wave <= 0)
		{
			timer_alpha_wname = 6000;
			timer_start_wave = 6000; // ������ 6 ������ �� ��������� ����� (���� ��� ����� ���� ��������� ��� ��� ������ �����)

			if(vec_Enemy.empty()) 
			{
				if(WAVE_PART_MAX <= wave_part) { wave_num++; wave_part = 1; }
				else wave_part++;
				const v2f& tpos = tank.shpPlanet.getPosition();
				ConstructText(text_wave_name, v2f(tpos.x, tpos.y + (scr_1 * 20)), 6.f, sf::String("WAVE " + to_string(wave_num) + " OF 3 : PART " + to_string(wave_part) + " OF " + to_string(WAVE_PART_MAX) + "."), font_freshman, sf::Color::Red);
				vec_Enemy.clear();
				vec_Enemy_Missle.clear();
			}

			// WAVE # 1
			if(wave_num == 1)
			{
					 if(wave_part == 1) { SPEN(2, "as01"); SPEN(1, "as02"); 																															  											}
				else if(wave_part == 2) { SPEN(3, "as01"); SPEN(1, "as02"); 																															 											}
				else if(wave_part == 3) { SPEN(2, "as01"); SPEN(2, "as02"); SPEN(1, "as03");								 																															}
				else if(wave_part == 4) { SPEN(1, "sh01"); SPEN(2, "as01"); SPEN(1, "as03");								 																															}
				else if(wave_part == 5) { SPEN(3, "as01"); SPEN(2, "as02"); SPEN(1, "as03"); SPEN(1, "as04"); 																																		}
				else if(wave_part == 6) { SPEN(2, "sh01"); SPEN(3, "as02"); SPEN(1, "as04"); 							 																															}
				else if(wave_part == 7) { SPEN(1, "sh02"); SPEN(5, "as01"); 				 								 																														}
				else if(wave_part == 8) { SPEN(3, "sh01"); SPEN(1, "sh02"); SPEN(1, "as04"); 							 																															}
				else if(wave_part == 9) { SPEN(4, "as01"); SPEN(3, "as02"); SPEN(2, "as03"); SPEN(1, "as04"); 																																		}
				else if(wave_part == 10){ SPEN(3, "as01"); SPEN(1, "as03"); SPEN(1, "sh03"); SPEN(1, "sh02"); SPEN(2, "sh01");																														}
			}														    							  																															  
																	    							  																															  
			// WAVE # 2												    							  																															  
			else if(wave_num == 2)										    							  																															  
			{														    							  																															  
					 if(wave_part == 1) { SPEN(3, "as01"); SPEN(3, "as02"); SPEN(1, "dg01", 1.5);																														 	}
				else if(wave_part == 2) { SPEN(1, "sh04"); SPEN(2, "dg01"); SPEN(4, "as01");																																}
				else if(wave_part == 3) { SPEN(1, "as01", 20); 																																												}
				else if(wave_part == 4) { SPEN(1, "tr01"); SPEN(3, "as05", 0.75);																																				}
				else if(wave_part == 5) { SPEN(2, "dg01"); SPEN(1, "dg02");	SPEN(2, "tr01");																															}
				else if(wave_part == 6) { SPEN(2, "sh03"); SPEN(4, "sh01");	SPEN(1, "dg02");																																				}
				else if(wave_part == 7) { SPEN(4, "dg01"); SPEN(2, "as06"), SPEN(3, "sh01", 1.3);																																									}
				else if(wave_part == 8) { SPEN(8, "sh01"); SPEN(2, "sh03"); 																																														}
				else if(wave_part == 9) { SPEN(1, "mr01"); SPEN(3, "tr01"); SPEN(5, "as03");																																														}
				else if(wave_part == 10){ SPEN(4, "mr01"); SPEN(3, "tr01"); SPEN(1, "tr02");																																														}
			}														    							  																															  
																	    							  																															  
			// WAVE # 3												    							  																															  
			else if(wave_num == 3)										    							  																															  
			{														    							  																															  
					 if(wave_part == 1) { SPEN(3, "dg01"); SPEN(2, "dg02"); SPEN(1, "dg03");																															 									}
				else if(wave_part == 2) { SPEN(1, "bl01"); SPEN(3, "sh03"); 																															 									}
				else if(wave_part == 3) { SPEN(5, "mr01"); SPEN(1, "mr02");								 																													}
				else if(wave_part == 4) { SPEN(4, "tr01"); SPEN(1, "tr02");								 																												}
				else if(wave_part == 5) { SPEN(3, "bl01"); SPEN(1, "bl02"); SPEN(1, "sh02");																																	}
				else if(wave_part == 6) { SPEN(1, "sh04"); SPEN(3, "sh02"); SPEN(1, "dg02");						 																														}
				else if(wave_part == 7) { SPEN(2, "sh01"); SPEN(2, "sh02"); SPEN(2, "sh03"); SPEN(4, "as01");											 																														}
				else if(wave_part == 8) { SPEN(3, "sh01"); SPEN(1, "sh02"); SPEN(1, "as04");						 																														}
				else if(wave_part == 9) { SPEN(4, "as02"); SPEN(4, "sh02"); SPEN(4, "dg02"); 																																	}
				else if(wave_part == 10){ isBossCreateTime = true;																																							}
			}
			else if(wave_num >= WAVE_NUM_END) isWin = true;
		}


		if(isBossCreateTime) CreateBoss();	// ������� ��������� �����
		if(isBossLife) BossLife();			// ���� ���� ���

		const sf::Color c = text_wave_name.getColor();
		text_wave_name.setColor(sf::Color(c.r, c.g, c.b, 255 * timer_alpha_wname/6000.f));

		oLevel::Update();
	}

	virtual void Action()
	{
		oLevel::Action();
	}

	virtual bool IsWin () 
	{
		return isWin;
	}

	virtual void Draw()
	{
		oLevel::Draw();
		wnd->draw(text_wave_name);
	}

	virtual ~Level_01() {}
};