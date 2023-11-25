#pragma once
#include "System.h"

//////////////////////////////////////////////
// ����� ����������� ��������� ������������ //
//////////////////////////////////////////////

class UI_Ability_Description : public System
{
	
public:

	Shape shape;
	sf::Text text;

	UI_Ability_Description()
	{
	}

	virtual void setParam(v2f pos, sf::String str)
	{
		ConstructText(text, v2f(0, (37*scr_1)), 1.75, str, font_freshman, sf::Color::Yellow);
		ConstructShape(shape, v2f(0, (37*scr_1)), (v2f(text.getGlobalBounds().width+(scr_1*2), text.getGlobalBounds().height+(scr_1*2))/scr_1), texture->UI_Bar, false);
		shape.move(0, -shape.getSize().y/2);
		text.setPosition(shape.getPosition());
	}

	virtual void Draw()
	{
		wnd->draw(shape);
		wnd->draw(text );
	}

	virtual ~UI_Ability_Description() {}
};

////////////////////////////
// ���������� "��������" //
////////////////////////////

class Effect_Upgrade_Star : public System
{
private:

	Shape shape;
	float alpha;
	float timer;
	float TIMER;

public:

	Effect_Upgrade_Star(v2f pos) : alpha(rand()%8-4), timer(750), TIMER(750)
	{
		ConstructShape(shape, pos, v2f(0.25,0.25)*float(rand()%6+1),texture->EFF_Effect_Star, false);
	}

	virtual void Update()
	{
		alpha += time*0.0008;
		timer -= time;
		if(timer < 0) timer = 0;
		shape.move(cos(alpha), (-0.05*time)*scr_1);
		shape.setFillColor(sf::Color(255,255,255, 255*(timer/TIMER)));
		shape.rotate(0.05*time);
	}

	virtual bool IsEnd() const
	{
		return timer == 0.f;
	}

	virtual void Draw()
	{
		wnd->draw(shape);
	}
};


///////////////////////////////////////////////
// ����������� ����� ���������� ������������ //
///////////////////////////////////////////////

class oUI_Ability : public System
{
protected:

	float alpha;
	int level;
	float duration, duration_plus, DURATION_START;
	float timer_Effect;

	int level_Need;
	int level_Skip;

	Shape shpBonus;
	Shape shpIco;
	Shape shpPlato;
	Shape shpUpgrade;
	Shape shpBlocked;

	vector<shared_ptr<Effect_Upgrade_Star>> vec_Effect_Star;
	sf::Text text_time;
	bool isShowDescript;

	static UI_Ability_Description description;
	static sf::String strDuration;
	static sf::String strLevelNeed;
	static sf::String strLevelCur;

	sf::Text text_hotkey;
	sf::Text text_level;

	virtual void setHotKey(string key)
	{
		ConstructText(text_hotkey, shpIco.getPosition()+(v2f(2,4)*scr_1), 2, "Key " + key, font_freshman, sf::Color::Yellow); 
		ConstructShape(shpUpgrade, shpIco.getPosition(), v2f(7,7), texture->UI_Button_Upgrade, false);
		shpUpgrade.setFillColor(sf::Color::Transparent);
		ConstructText(text_level, shpIco.getPosition()+((v2f(-2, -4))*scr_1),2, "lvl "+to_string(level), font_freshman, sf::Color::Yellow);
		shpPlato.setFillColor(sf::Color(255,255,255,125));
	}

	bool isCheked;
	bool isDecor;

public:

	oUI_Ability(uint lvl, bool isDecor = false) : level(lvl), duration(0), isShowDescript(false), timer_Effect(0), isCheked(false), alpha(0), isDecor(isDecor)
	{
		DURATION_START = 0;
		duration = 0; 
		duration_plus = 0;
		shpBonus.setFillColor(sf::Color(255,255,255,200));
	}

	virtual int GetLevelNeed()
	{
		return level_Need;
	}

	virtual int GetLevelSkip()
	{
		return level_Skip;
	}

	virtual int GetLevelUpTrue()
	{
		return level_Need + (level_Skip * level);
	}

	virtual void Effect_Update()
	{
		timer_Effect += time;
		if(timer_Effect > 40)
		{
			timer_Effect = 0;
			vec_Effect_Star.push_back(make_shared<Effect_Upgrade_Star>(Effect_Upgrade_Star(shpUpgrade.getPosition())));
		}

		for(auto& it = vec_Effect_Star.begin(); it != vec_Effect_Star.end();)
		{
			auto& effect = *(*it);
			if(!effect.IsEnd())
			{
				effect.Update();
				it++;
			}
			else
			{
				it = vec_Effect_Star.erase(it);
			}
		}
	}

	virtual void DrawLock()
	{
		wnd->draw(shpBlocked);
	}

	virtual bool IsContains() 
	{ 
		return isShowDescript; 
	}

	virtual void DescriptionReset(sf::String str)
	{
		if(!isShowDescript)
		{
			if(shpIco.getGlobalBounds().contains(cur_p))
			{
				description.setParam(v2f(shpIco.getPosition()), str);
				isShowDescript = true;
			}
		}
		else
		{
			if(!shpIco.getGlobalBounds().contains(cur_p)) 
				isShowDescript = false;
		}
	}

	virtual void TickDuration()
	{
		if(!isCheked)
		{
			if(duration > 0) 
			{
				duration -= time;
			}
			else duration = 0;
		}
	}

	virtual void Update()
	{
		std::string str;
		for(int i = 0; i < 4; i++) str.push_back(to_string(duration/1000)[i]);

		ConstructText(text_time, v2f(shpIco.getPosition().x, shpIco.getPosition().y - (7.f*scr_1)), 2.0, str, font_freshman, sf::Color::White);
		shpPlato.rotate(0.03*time);

		alpha += time*0.003f;
		shpUpgrade.setFillColor(sf::Color( 255, 255, 255, abs(cos(alpha)) * 150 ));
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Draw()
	{
		wnd->draw(shpIco);
		wnd->draw(shpPlato);
		wnd->draw(shpBonus);

		if(!isEnd()) 
		{
			wnd->draw(text_time);
		}
		else shpBonus.setRotation(0);
		wnd->draw(text_hotkey);	
		wnd->draw(text_level);
		if(isShowDescript) description.Draw();
	}

	virtual void DrawUpgrade()
	{
		wnd->draw(shpUpgrade);
		for(auto& effect: vec_Effect_Star)
			effect->Draw();
	}

	virtual int getLevel() const { return level; }
	virtual float getDuration() const { return duration; }

	virtual void LevelUp(int& upgp) 
	{ 
		level++; 
		upgp--; 
		ConstructText(text_level, shpIco.getPosition()+((v2f(-2, -4))*scr_1),2, "lvl "+ to_string(level), font_freshman, sf::Color::Yellow);
	}

	virtual void Check() {}
	virtual void Cancel() {}
	virtual bool IsChecked() const { return false; }

	virtual void KeepTime() 
	{ 
		if(level > 0)
		{
			isCheked = true; 
			if(duration < 500) duration = DURATION_START + (level * duration_plus);
			else duration += (level * duration_plus);
		}
	}

	virtual int getLevel()
	{
		return level;
	}
	
	virtual void Run() 
	{
		if(duration < 500) duration = DURATION_START + (level * duration_plus);
		else duration += (level * duration_plus);
	}

	virtual void StringsReset()
	{
		string  s_dur, s_dur_p;

		if(isLanguageRU)
		{
			if(isDecor) strLevelNeed = sf::String(L"����� ������ ��������� ��� ��������.\n�������� ��� �������� � ���� ���� ���\n����� ����� ����������.\n��������� ") + sf::String(to_string(level_Need)) + L" �������.\n\n";
			else strLevelNeed = L"��������� �������: " + sf::String(to_string(level_Need)) + L"\n������� ������: " + sf::String(to_string(level_Skip)) + L"\n\n";
		}
		else
		{
			if(isDecor) strLevelNeed = "Required level: " + to_string(level_Need) + "\nLevel skip: " + to_string(level_Skip) + "\n\n";
			else strLevelNeed = "Required level: " + to_string(level_Need) + "\nLevel skip: " + to_string(level_Skip) + "\n\n";
		}

		if(level == 0) s_dur = to_string((DURATION_START + duration_plus) / 1000.f);
		else s_dur = to_string( ((DURATION_START) / 1000.f) + (duration_plus / 1000.f) * level);
		s_dur_p = to_string(duration_plus/1000);

		while (s_dur.length() > 4)
		{
			s_dur.pop_back();
			if(s_dur.length() - 1 == '.') break;
		}
		while (s_dur_p.length() > 4)
		{
			s_dur_p.pop_back();
			if(s_dur_p.length() - 1 == '.') break;
		}

		if(isLanguageRU)
		{
			if(isDecor) strDuration = L"\n\n����������� ��������� ��������\n������������ �������������.\n.";
			else strDuration = L"\n\n����� ��������: " + sf::String(s_dur) + L" ���.\n��������� ������� +" + sf::String(s_dur_p) + L" ���. � ��������.";
		}
		else 
		{
			if(isDecor) strDuration = "\n\nDuration time: " + sf::String(s_dur) + " sec.\nUpgrade add +" + sf::String(s_dur_p) + " sec. to action time.";
			else strDuration = "\n\nDuration time: " + sf::String(s_dur) + " sec.\nUpgrade add +" + sf::String(s_dur_p) + " sec. to action time.";
		}
	}

	virtual ~oUI_Ability() { }
};

UI_Ability_Description oUI_Ability::description;
sf::String oUI_Ability::strDuration;
sf::String oUI_Ability::strLevelNeed;
sf::String oUI_Ability::strLevelCur;

////////////////////////
// �������� � ������� //
////////////////////////

class UI_Ability_Multiple_Attack : public oUI_Ability
{
public:

	UI_Ability_Multiple_Attack(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 1;
		level_Skip = 2;

		DURATION_START = 2000;
		duration_plus = 250;
		duration = 0; 

		const v2f pos(-55,44);
		ConstructShape(shpIco, pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Multiple[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		setHotKey("1");
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual void Run() 
	{
		oUI_Ability::Run();
		shpBonus.setTexture(&texture->Bonus_Multiple[1]);
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Multiple[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"��������� ��������� �������� ����� ���������\n������������, ��������� �� � ������ �������.\n��������� ���� �� 30% ������ ��������." + strDuration);
		else DescriptionReset(strLevelCur + strLevelNeed + L"The amplifier allows to shoot with 3 shards\nin the same time in different directions.\nDamage is 30% lower the initial one." + strDuration);
		oUI_Ability::Draw();
	}

	virtual ~UI_Ability_Multiple_Attack() {}
};

/////////////////////////////////
// �������� ��� ������ ������� //
/////////////////////////////////

class UI_Ability_Hight_Overload : public oUI_Ability
{
public:

	UI_Ability_Hight_Overload(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 2;
		level_Skip = 2;

		DURATION_START = 2000;
		duration_plus = 500;
		duration = 0; 

		const v2f pos(-45, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		ConstructShape(shpIco, pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Shock[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		setHotKey("2");
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Shock[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Run() 
	{
		oUI_Ability::Run();
		shpBonus.setTexture(&texture->Bonus_Shock[1]);
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"����������� ���� ������� �������\n��� ��������� �������� ��� ������ �������." + strDuration);
		else DescriptionReset(strLevelCur + strLevelNeed + L"Activates an battery-core which allows\nto shoot without any energy use." + strDuration);
		oUI_Ability::Draw();
	}

	virtual ~UI_Ability_Hight_Overload() {}
};

//////////////////////////
// ������������ ������� //
//////////////////////////

class UI_Ability_World_Shield : public oUI_Ability
{
public:

	Shape shpShield[2];
	Shape shpEffect[2];

	UI_Ability_World_Shield(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 6;
		level_Skip = 5;

		DURATION_START = 2500;
		duration_plus = 250;
		duration = 0; 

		const v2f pos(-35, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);

		ConstructShape(shpIco, pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Shield[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		for(int i = 0; i < 2; i++) 
		{
			ConstructShape(shpShield[i], v2f(0,0), v2f(30,30), texture->EFF_Shield);
			ConstructShape(shpEffect[i], v2f(0,0), v2f(30,30), texture->EFF_Shield_Effect);
		}
		setHotKey("3");
	}

	virtual void Update()
	{
		oUI_Ability::Update();
		shpShield[0].rotate( 0.05*time);
		shpShield[1].rotate(-0.05*time);
		shpEffect[0].rotate( 0.75*time);
		shpEffect[1].rotate(-0.75*time);
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Shield[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Run() 
	{
		oUI_Ability::Run();
		shpBonus.setTexture(&texture->Bonus_Shield[1]);
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"��������� ����� ���������� ������-�����.\n��������� ��� ����� �����������\n� ��������� ���������� ����� ��� ������������.\n�� ��������� �� ��������� ������." + strDuration);
		else DescriptionReset(strLevelCur + strLevelNeed + L"Covers the Earth with strong unbreakable shield.\nIt blocks all attacks of the enemy and\ndestroys them if they collide into it." + strDuration);
		oUI_Ability::Draw();
	}

	virtual ~UI_Ability_World_Shield() {}
};

//////////////////
// ������� ���� //
//////////////////

class UI_Ability_Double_Damage : public oUI_Ability
{
public:

	UI_Ability_Double_Damage(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 10;
		level_Skip = 5;

		DURATION_START = 3000;
		duration_plus = 500;
		duration = 0; 

		const v2f pos(-25, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		ConstructShape(shpIco, pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Power[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		setHotKey("4");
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Power[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Run() 
	{
		oUI_Ability::Run();
		shpBonus.setTexture(&texture->Bonus_Power[1]);
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"��� ��������� ����� �������� ���� ����� ������� ������� ����.\n�� ���������������� �� \"�������� ���������\"\n� �������� ���������." + strDuration);
		else DescriptionReset(strLevelCur + strLevelNeed + L"Your attacks do double damage. Allows you to quickly\ndestroy opponents with accurate shots." + strDuration);
		oUI_Ability::Draw();
	}

	virtual ~UI_Ability_Double_Damage() {}
};

///////////////////////////////////////
// ���������� ������������ � ������� //
///////////////////////////////////////

class UI_Ability_Time_Slow : public oUI_Ability
{
public:

	UI_Ability_Time_Slow(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 12;
		level_Skip = 6;

		DURATION_START = 2400;
		duration_plus = 400;
		duration = 0; 

		const v2f pos(-15, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		ConstructShape(shpIco,   pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Slow[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		setHotKey("Q");
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual void Run() 
	{
		oUI_Ability::Run();
		shpBonus.setTexture(&texture->Bonus_Slow[1]);
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Slow[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"���������� ���������� ���� ������������ �������� � �� ��������.\n��� ��������� �� ���������� � ���������� �����������." + strDuration);
		else DescriptionReset(strLevelCur + strLevelNeed + L"Global slows down all enemy alien spaceships\nand their shards. This makes aiming easier." + strDuration);
		oUI_Ability::Draw();
	}

	virtual ~UI_Ability_Time_Slow() {}
};


/////////////////////////////////////////
// ���������� ����� �� �������� ������ //
/////////////////////////////////////////

class UI_Ability_Fragment_Explosion : public oUI_Ability
{
public:

	UI_Ability_Fragment_Explosion(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 20;
		level_Skip = 8;

		DURATION_START = 3000;
		duration_plus = 600;
		duration = 0; 

		const v2f pos(-5, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		ConstructShape(shpIco,   pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Fragment_Explosion[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		setHotKey("E");
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual void Run() 
	{
		oUI_Ability::Run();
		shpBonus.setTexture(&texture->Bonus_Fragment_Explosion[1]);
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Fragment_Explosion[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"��� ����������� ������ ��� ������������ ����� ��������\n��������� �� �� �������, ������� ���������� ��������\n���� ������������ ��������." + strDuration + L" � ��������� +1 �������.");
		else DescriptionReset(strLevelCur + strLevelNeed + L"After using this amplifier any enemy spaceship\nthat get destroyed sends debris hurling towards\nenemy space ships and dealing damage." + strDuration + "and +1 shard.");
		oUI_Ability::Draw();
	}

	virtual ~UI_Ability_Fragment_Explosion() {}
};

///////////////////
// �����-������� //
///////////////////

class UI_Ability_Splash_Ricochet : public oUI_Ability
{
public:

	UI_Ability_Splash_Ricochet(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 24;
		level_Skip = 8;

		DURATION_START = 4000;
		duration_plus = 400;
		duration = 0; 

		const v2f pos(5, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		ConstructShape(shpIco,   pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Splash_Ricochet[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		setHotKey("R");
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual void Run() 
	{
		oUI_Ability::Run();
		shpBonus.setTexture(&texture->Bonus_Splash_Ricochet[1]);
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Splash_Ricochet[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"������ ������ ��� ����������� ������� ��������� �����������.\n��� ������� ���������� ��� ������������ � ���������\n��������� �������� ������ ����." + strDuration);
		else DescriptionReset(strLevelCur + strLevelNeed + L"Powerful weapon for eliminating large groups of aliens.\nYour projectile ricochets of targets and\ndeals massive damage to any enemies around." + strDuration);
		oUI_Ability::Draw();
	}

	virtual ~UI_Ability_Splash_Ricochet() {}
};

////////////////
// ������ SOS //
////////////////

class UI_Ability_Signal_SOS : public oUI_Ability
{
public:

	UI_Ability_Signal_SOS(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 30;
		level_Skip = 10;

		DURATION_START = 5000;
		duration_plus = 0;
		duration = 0; 

		const v2f pos(15, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		ConstructShape(shpIco,   pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Signal_SOS[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		setHotKey("F");
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Signal_SOS[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Run() 
	{
		duration = 5000;
		shpBonus.setTexture(&texture->Bonus_Signal_SOS[1]);
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"������ ��� ���� � ������ �������� �� ���������.\n���� ��������� ��������� �� ������ ������� ��������\n��������� ������ �� ���� ����.\n\n������ " + sf::String(to_string(level)) + L" ���������.\n\n��������� ����������� ���-�� ����������� ��������� �� 1 ��.");
		else DescriptionReset(strLevelCur + strLevelNeed + L"Luckily there are friendly creatures in the universe!\nThe amplifier summons allied spaceships who attack\nthe enemy on their way.\n\nSummons ships " + sf::String(to_string(level)) + L".\n\nImproving increases the number of summoned ships by 1.");
		oUI_Ability::Draw();
	}

	virtual ~UI_Ability_Signal_SOS() {}
};

//////////////////////
// �������� ������� //
//////////////////////

class UI_Ability_Plasm_Attack : public oUI_Ability
{
public:

	UI_Ability_Plasm_Attack(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 36;
		level_Skip = 10;

		DURATION_START = 4800;
		duration_plus = 600;
		duration = 0; 

		const v2f pos(25, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		ConstructShape(shpIco,   pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Plasm_Attack[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		setHotKey("Z");
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual void Run() 
	{
		oUI_Ability::Run();
		shpBonus.setTexture(&texture->Bonus_Plasm_Attack[1]);
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Plasm_Attack[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"���������� ��������� �������� ���� ������, ��������\n�������� ��������, �� �������� ������� ����������.\n�������� ��������� �������." + strDuration);
		else DescriptionReset(strLevelCur + strLevelNeed + L"The plasmic amplifier upgrades your weapon by\nincreasing the fire rate but slightly lowering the accuracy." + strDuration);
		oUI_Ability::Draw();
	}

	virtual ~UI_Ability_Plasm_Attack() {}
};

//////////////////////////////////////////////
// ������� ����� �� ��������������� ������� //
//////////////////////////////////////////////

class UI_Ability_Mirror_Tank : public oUI_Ability
{
public:

	UI_Ability_Mirror_Tank(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 40;
		level_Skip = 12;

		DURATION_START = 6500;
		duration_plus = 500;
		duration = 0; 

		const v2f pos(35, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		ConstructShape(shpIco,   pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Mirror_Tank[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		setHotKey("X");
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual void Run() 
	{
		oUI_Ability::Run();
		shpBonus.setTexture(&texture->Bonus_Mirror_Tank[1]);
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Mirror_Tank[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"������ ����� ���� � ���������� ����������\n�� ��������������� ������� �������.\n������� ��������� ��� ���� ��������." + strDuration);
		else DescriptionReset(strLevelCur + strLevelNeed + L"Creates a chrono-tank which mirrors all your\nactions on the other side of a planet." + strDuration);
		oUI_Ability::Draw();
	}

	virtual ~UI_Ability_Mirror_Tank() {}
};

////////////////////////
// �������� ��������� //
////////////////////////

class UI_Ability_Turret : public oUI_Ability
{
private:

	bool isCheck;
	float alpha;
	sf::Text text_Error_Install;
	sf::Text text_Charges;
	float timer_text;
	int charges;

public:

	Shape shpTurret;
	Shape shpWheel;
	Shape shpInstaller_A[4], shpInstaller_B[4];

	UI_Ability_Turret(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor), isCheck(false), alpha(0), timer_text(0), charges(0)
	{
		level_Need = 45;
		level_Skip = 15;

		DURATION_START = 2500;
		duration_plus = 750;
		duration = 0; 

		const v2f pos(45, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		ConstructShape(shpIco,   pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Turret_Defender[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);

		ConstructShape(shpTurret, cur_p, v2f(5,3), texture->Defender_Turret, false);
		ConstructText(text_Charges, shpIco.getPosition(), 3, to_string(charges), font_freshman, sf::Color::Cyan);
		shpTurret.setFillColor(sf::Color(255,255,255,200));
		ConstructShape(shpWheel, cur_p, v2f(4,4), texture->Defender_Wheel, false);
		shpWheel.setFillColor(sf::Color(255,255,255,200));
		for(int i = 0; i < 4; i++)
		{
			ConstructShape(shpInstaller_A[i], GetNormalizedPosition(cam_p, 30, i*90), v2f(6,6), texture->Turret_Installer);
			ConstructShape(shpInstaller_B[i], GetNormalizedPosition(cam_p, 30, i*90), v2f(6,6), texture->Turret_Installer);
			shpInstaller_B[i].setScale(-1,0);
		}
		ConstructText(text_Error_Install, v2f(0,0), 3, "Unable to install here...", font_freshman, sf::Color(255,0,0,255));
		setHotKey("C");
	}

	virtual void Check() { if(charges > 0) isCheck = true; }
	virtual void Cancel() { isCheck = false; }
	virtual bool IsChecked() const { return isCheck; }

	virtual void KeepTime() 
	{ 
		if(level < 0)
		{
			shpBonus.setTexture(&texture->Bonus_Turret_Defender[1]);
			isCheked = true; 
			duration += ( DURATION_START + ( level * duration_plus ) ); 
			charges++;
			ConstructText(text_Charges, shpIco.getPosition(), 3, to_string(charges), font_freshman, sf::Color::Cyan);
		}
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual void Run() 
	{
		charges = 0;
		ConstructText(text_Charges, shpIco.getPosition(), 3, to_string(charges), font_freshman, sf::Color::Cyan);
		duration = 0;
		shpBonus.setTexture(&texture->Bonus_Turret_Defender[0]);
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) DescriptionReset(strLevelCur + strLevelNeed + L"����������� ������ ������� ��������� ����������\n���������� �������� ���������.\n���� ������ ���� � �������, ������� ���,\n� ���������� ���������  ����� ��� �� ����� �� ������ ��������." + strDuration);
		else DescriptionReset(strLevelCur + strLevelNeed + L"Accumulates charges for the defence station.\nWhen charges are available right click\nto build a station on one of the four platforms." + strDuration);
		wnd->draw(shpIco);
		wnd->draw(shpPlato);
		wnd->draw(shpBonus);


		wnd->draw(text_hotkey);	
		wnd->draw(text_level);
		wnd->draw(text_Charges);
		shpTurret.setFillColor(sf::Color(255,255,255,abs(cos(alpha)*200)));
		shpWheel.setFillColor(sf::Color(255,255,255,abs(cos(alpha)*200)));
		if(isShowDescript) description.Draw();
	}

	virtual void ShowErrorInstall ( bool isShow = true ) { if ( isShow ) timer_text = 3000; else timer_text = 0; }

	virtual void DrawTurret()
	{
		alpha += time*0.005;
		if(isCheck)
		{
			wnd->draw(shpWheel);
			wnd->draw(shpTurret);
		}

		if(charges > 0)
		{
			for(int i = 0; i < 4; i++)
			{
				shpInstaller_A[i].rotate( 0.1*time);
				shpInstaller_B[i].rotate(-0.1*time);
				wnd->draw(shpInstaller_A[i]);
				wnd->draw(shpInstaller_B[i]);
			}
		}

		shpTurret.setPosition(cur_p);
		shpWheel.setPosition(cur_p);
		timer_text -= time;
		text_Error_Install.setColor(sf::Color(255,0,0,255*(timer_text/3000)));
		text_Error_Install.setPosition(GetNormalizedPosition(cam_p, 30*scr_1, cam.getRotation()-90));
		text_Error_Install.setRotation(cam.getRotation());
		if(timer_text > 0) wnd->draw(text_Error_Install);
	}

	virtual ~UI_Ability_Turret() {}
};

////////////////
// Black Hole //
////////////////

class UI_Ability_Black_Hole : public oUI_Ability
{
public:

	UI_Ability_Black_Hole(uint lvl, bool isDecor = false) : oUI_Ability(lvl, isDecor)
	{
		level_Need = 60;
		level_Skip = 20;

		DURATION_START = 8000;
		duration_plus = 1500;
		duration = 0; 

		const v2f pos(55, 44);
		ConstructShape(shpBlocked, pos, v2f(7,7), texture->UI_Locked);
		ConstructShape(shpIco,   pos, v2f(10,10), texture->UI_Ico);
		ConstructShape(shpBonus, pos, v2f(8.5,8.5), texture->Bonus_Black_Hole[0]);
		ConstructShape(shpPlato, pos, v2f(10,10), texture->Bonus_Plato);
		setHotKey("V");
	}

	virtual void LevelUp(int& upgp)
	{
		oUI_Ability::LevelUp(upgp);
		// ��� ������������ �����������
	}

	virtual void Run() 
	{
		oUI_Ability::Run();
		shpBonus.setTexture(&texture->Bonus_Black_Hole[1]);
	}

	virtual bool isEnd() 
	{
		if(level == 0 || duration < 0.f)
		{
			duration = 0;
			shpBonus.setTexture(&texture->Bonus_Black_Hole[0]);
			return true;
		}
		return duration <= 0.f;
	}

	virtual void Draw()
	{
		StringsReset();
		if(isLanguageRU) 
		{
			if(isDecor) DescriptionReset(strLevelCur + strLevelNeed + L"��* �*��** �*****���** � �***��\n��**** �***, ******��*���� � ��*��\n*��*� �� � ������� ���*** �***\n� *��**�* ��**��**�*�** ��**." + strDuration + L"\n�������� ��������� ���� � ���. ������.");
			else DescriptionReset(strLevelCur + strLevelNeed + L"��� ������ ������������ � ������\n������ ����, ������������� � ������\n����� �� � ������� ������ ����\n� ������� ������������� ����." + strDuration + L"\n�������� ��������� ���� � ���. ������.");
		}
		else 
		{
			DescriptionReset(strLevelCur + strLevelNeed + L"Your crosshair becomes an analog of a black hole.\nAny enemy that is touched is pulled towards the\ncenter and received damage on its way."+ strDuration + L"\nincreases damage and physic size.");
		}
			oUI_Ability::Draw();
	}

	virtual ~UI_Ability_Black_Hole() {}
};