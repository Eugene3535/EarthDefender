#pragma once
#include "oButton.h"
#include "SpecEffect.h"
#include "oUI_Ability.h"

class Main_Menu : public B
{
private:

	UI_Ability_Double_Damage		double_damage;
	UI_Ability_Fragment_Explosion	fragment_explosion;
	UI_Ability_Hight_Overload		hight_overload;
	UI_Ability_Multiple_Attack		multiple_attack;
	UI_Ability_Time_Slow			time_slow;
	UI_Ability_World_Shield			world_shield;
	UI_Ability_Splash_Ricochet		splash_ricochet;
	UI_Ability_Signal_SOS			signal_sos;
	UI_Ability_Plasm_Attack			plasm_attack;
	UI_Ability_Mirror_Tank			mirror_tank;
	UI_Ability_Turret				turret_defender;
	UI_Ability_Black_Hole			black_hole;

	vector<shared_ptr<oButton>> vec_Button_Main; 
	vector<shared_ptr<oButton>> vec_Button_Settings;
	vector<shared_ptr<oButton>> vec_Button_Graphics;

	vector<shared_ptr<BackGround>> vec_BG;
	vector<shared_ptr<SpecEffect_Turbo>> vec_Turbo;
	vector<shared_ptr<Shape>> vec_EnemyShape;

	Shape shpPlanet, shpWheel, shpTurret, shpCircle;
	Shape shpHelp, shpDialog, shpGameName;

	bool is_Start_Pressed;
	int frame_count;
	float timer_create_turbo; 
	float timer_animation_planet;
	float timer_animation_tank;
	float frame_tank;
	enum MAIN_MENU_STATAE { main, settings, graphics } mmState;

public:

	// ���� �� ���������� � ��������� ������ � ��������� ���� � ����

	Main_Menu() : timer_animation_planet(0), frame_count(0), timer_create_turbo(0), timer_animation_tank(0), frame_tank(0), mmState(main), is_Start_Pressed(false),
		double_damage(0, 1),
		fragment_explosion(0, 1),
		hight_overload(0, 1),
		multiple_attack(0, 1),
		time_slow(0, 1),
		world_shield(0, 1),
		splash_ricochet(0, 1),
		signal_sos(0, 1),
		plasm_attack(0, 1),
		mirror_tank(0, 1),
		turret_defender(0, 1),
		black_hole(0, 1)
	{

		// ��������������� ������ ������� ���� �� �� �������� ������ � ������� � ������
		ConstructShape(shpPlanet, v2f(53,-35), v2f(25,25), texture->Earth[0]); 

		ConstructShape(shpWheel, v2f(-40, 35), v2f(15,15), texture->Tank_Wheel); shpWheel.setTextureRect(sf::IntRect(0,0,168,168));
		ConstructShape(shpTurret, shpWheel.getPosition(), v2f(15.5,8), texture->Tank_Turret, false);
		ConstructShape(shpCircle, shpPlanet.getPosition(), v2f(30,30), texture->Tank_Radius, false);
		ConstructShape(shpDialog, v2f(26,-30), v2f(30,15), texture->UI_Dialog);
		ConstructShape(shpHelp, v2f(26, -29), v2f(21,10), texture->UI_Text_Help);
		ConstructShape(shpGameName, v2f(0,-45), v2f(85,12), texture->UI_Text_The_Planet_Rescuer);

		shpCircle.setFillColor(CLR(140,140,255));
		shpTurret.setOrigin(shpTurret.getSize().x/3.5f, shpTurret.getSize().y/2.f);
		shpTurret.setRotation(GetAngle(shpTurret, shpPlanet));
		shpWheel.setRotation(GetAngle(shpTurret, shpPlanet)+180);


		vec_BG.push_back(make_shared<BackGround>(BackGround()));
		GoToMain(); // ������ ������ �������� ����

		vec_EnemyShape.push_back(make_shared<Shape>(Shape()));
		ConstructShape(*vec_EnemyShape.back(), v2f(100,100), v2f(6,3.1), texture->Enemy[1]);
		vec_EnemyShape.back()->setRotation(GetAngle(*vec_EnemyShape.back(), cam_p));

		vec_EnemyShape.push_back(make_shared<Shape>(Shape()));
		ConstructShape(*vec_EnemyShape.back(), v2f(100,-100), v2f(6,6), texture->Enemy[5]);
		vec_EnemyShape.back()->setRotation(GetAngle(*vec_EnemyShape.back(), cam_p));

		vec_EnemyShape.push_back(make_shared<Shape>(Shape()));
		ConstructShape(*vec_EnemyShape.back(), v2f(-100,-100), v2f(6,5), texture->Enemy[8]);
		vec_EnemyShape.back()->setRotation(GetAngle(*vec_EnemyShape.back(), cam_p));

		vec_EnemyShape.push_back(make_shared<Shape>(Shape()));
		ConstructShape(*vec_EnemyShape.back(), v2f(-100,100), v2f(6.5,6.5), texture->UFO[0]);
		vec_EnemyShape.back()->setRotation(GetAngle(*vec_EnemyShape.back(), cam_p));
		vec_EnemyShape.back()->setTextureRect(sf::IntRect(0,0,64,64));
		audio->music_main_menu.play();
	}

	virtual void GoToGraphics()
	{
		mmState = MAIN_MENU_STATAE::graphics;
		vec_Button_Settings.clear();

		vec_Button_Graphics.push_back(make_shared<Button_Float>(Button_Float(v2f(25,30), v2f(30,10), texture->UI_Button_Main, texture->UI_Text_Save, string("Save"), "Save")));
		vec_Button_Graphics.push_back(make_shared<Button_Float>(Button_Float(v2f(-25,30), v2f(30,10), texture->UI_Button_Main, texture->UI_Text_Cancel, string("Cancel"), "Cancel")));
	}

	virtual void GoToMain()
	{
		mmState = MAIN_MENU_STATAE::main;
		vec_Button_Settings.clear();

		vec_Button_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(-20,-8), v2f(25,8), texture->UI_Button_Main, texture->UI_Text_Play, string("Play"), "Play")));
		vec_Button_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(-20, 0), v2f(25,8), texture->UI_Button_Main, texture->UI_Text_Options, string("Options"), "Options")));
		vec_Button_Main.push_back(make_shared<Button_Float>(Button_Float(v2f(-20, 8),  v2f(25,8), texture->UI_Button_Main, texture->UI_Text_Exit, string("Exit"), "Exit")));
	}

	virtual void GoToOptions()
	{
		mmState = MAIN_MENU_STATAE::settings;
		vec_Button_Main.clear();
		vec_Button_Graphics.clear();

		vec_Button_Settings.push_back(make_shared<Button_Float>(Button_Float(v2f(0,-15), v2f(30,10), texture->UI_Button_Main, texture->UI_Text_Graphics, string("Graphics"), "Graphics")));
		vec_Button_Settings.push_back(make_shared<Button_Float>(Button_Float(v2f(0,0), v2f(30,10), texture->UI_Button_Main, texture->UI_Text_Sound, string("Sound"), "Sound")));
		vec_Button_Settings.push_back(make_shared<Button_Float>(Button_Float(v2f(0,15), v2f(30,10), texture->UI_Button_Main, texture->UI_Text_Back, string("Back"), "Back")));
		vec_Button_Settings.push_back(make_shared<Button_Float>(Button_Float(v2f(0,30), v2f(30,10), texture->UI_Button_Main, texture->UI_Text_Language_EN, string("Language"), "Language")));
	}

	virtual void Update()
	{
		static float alpha = 0;
		alpha += 0.001*time;
		shpHelp.setFillColor(CLR(140,140,255, abs(cos(alpha)*255)));
		timer_create_turbo += time;
		timer_animation_planet += time;
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

		shpTurret.setRotation(GetAngle(shpTurret, SCursor));
		shpPlanet.rotate(0.05*time);
		timer_animation_tank += time;
		if(timer_animation_tank >= 90)
		{
			frame_tank--;
			if(frame_tank <= 0) 
			{
				frame_tank = 3;
			}
			shpWheel.setTextureRect(sf::IntRect(frame_tank*169,0,169,169));
			timer_animation_tank = 0;
		}

		if(timer_create_turbo >= 180)
		{
			timer_create_turbo = 0;
			vec_Turbo.push_back(make_shared<SpecEffect_Turbo>(SpecEffect_Turbo(shpWheel.getPosition(), v2f(10,20), texture->EFF_Turbo, shpWheel.getRotation()-180, 750)));
		}

		for(auto it = vec_Turbo.begin(); it != vec_Turbo.end();)
		{
			SpecEffect& t = *(*it);
			if(!t.IsEnd())
			{
				t.Update();
				it++;
			}
			else it = vec_Turbo.erase(it);
		}

		for(auto bg : vec_BG)
		{
			bg->Update();
		}

		// ������ �������� ����
		for(auto b : vec_Button_Main) b->Update();
		// ������ ��������
		for(auto b : vec_Button_Settings) b->Update();
		// ������ �������� Graphics
		for(auto b : vec_Button_Graphics) b->Update();

		if(is_Start_Pressed)
		{
			static float duration_start_animation = 4000.f;
			duration_start_animation -= time;
			audio->music_main_menu.setVolume(100 * (duration_start_animation/4000.f));
			shpGameName.setFillColor(sf::Color(255,255,255,255*(duration_start_animation/4000.f)));

			shpGameName.setScale(1.5f-(0.5f*(duration_start_animation/4000.f)), 1.5f-(0.5*(duration_start_animation/4000.f)));
			shpPlanet.setScale(1.5f-(0.5f*(duration_start_animation/4000.f)), 1.5f-(0.5*(duration_start_animation/4000.f)));
			shpCircle.setScale(1.5f-(0.5f*(duration_start_animation/4000.f)), 1.5f-(0.5*(duration_start_animation/4000.f)));
			shpWheel.setScale(0.5f+(0.5f*(duration_start_animation/4000.f)), 0.5f+(0.5*(duration_start_animation/4000.f)));
			shpTurret.setScale(0.5f+(0.5f*(duration_start_animation/4000.f)), 0.5f+(0.5*(duration_start_animation/4000.f)));
			float spdName = GetDistance(shpGameName, cam_p)/4000.f;
			float spdPlanet = GetDistance(shpPlanet,cam_p)/4000.f;
			float spdTank = GetDistance(shpWheel,cam_p)/5000.f;
			
			MoveToAngle(*vec_EnemyShape[0], GetDistance(*vec_EnemyShape[0],v2f(25,25)*scr_1)/6000.f, GetAngle(*vec_EnemyShape[0],cam_p));
			MoveToAngle(*vec_EnemyShape[1], GetDistance(*vec_EnemyShape[1],v2f(25,-25)*scr_1)/6000.f, GetAngle(*vec_EnemyShape[1],cam_p));
			MoveToAngle(*vec_EnemyShape[2], GetDistance(*vec_EnemyShape[2],v2f(-25,-25)*scr_1)/6000.f, GetAngle(*vec_EnemyShape[2],cam_p));
			MoveToAngle(*vec_EnemyShape[3], GetDistance(*vec_EnemyShape[3],v2f(-25,25)*scr_1)/6000.f, GetAngle(*vec_EnemyShape[3],cam_p));

			MoveToAngle(shpGameName,spdName/4,GetAngle(shpGameName,cam_p));
			MoveToAngle(shpPlanet,spdPlanet/4,GetAngle(shpPlanet,cam_p));
			MoveToAngle(shpCircle,spdPlanet/4,GetAngle(shpCircle,cam_p));
			

			MoveToAngle(shpWheel,spdTank/4,GetAngle(shpWheel,cam_p));
			MoveToAngle(shpTurret,spdTank/4,GetAngle(shpTurret,cam_p));

			if(duration_start_animation <= 0.f) 
			{
				duration_start_animation = 4000.f;
				is_Start_Pressed = false;
				gState = GSTATE::game;
				audio->music_main_menu.stop();
			}
		}
	}

	virtual void Action()
	{
		// UI � �������� ����
		for(auto b : vec_Button_Main)
		{
			if(b->isActivate())
			{
				if(b->getNameID() == "Play")
				{
					is_Start_Pressed = true;
					shpHelp = Shape();
					shpDialog = Shape();
					vec_Button_Main.clear();
					break;
				}
				if(b->getNameID() == "Options")
				{
					 GoToOptions();
					 break;
				}
				if(b->getNameID() == "Exit")
				{
					wnd->close();
					break;
				}
			}
		}

		// UI � ������ ��������
		for(auto b : vec_Button_Settings)
		{
			if(b->isActivate())
			{
				if(b->getNameID() == "Graphics")
				{
					GoToGraphics();
					break;
				}

				if(b->getNameID() == "Back")
				{
					GoToMain();
					break;
				}

				if(b->getNameID() == "Language")
				{
					isLanguageRU = !isLanguageRU;
					if(isLanguageRU) b->shpText.setTexture(&texture->UI_Text_Language_RU);
					else b->shpText.setTexture(&texture->UI_Text_Language_EN);
				}
			}
		}

		// UI � ����������� �������
		for(auto b : vec_Button_Graphics)
		{
			if(b->isActivate())
			{
				if(b->getNameID() == "Save")
				{
					GoToGraphics();
					cout << "\nSaved\n";
					break;
				}

				if(b->getNameID() == "Cancel")
				{
					GoToOptions();
					break;
				}
			}
		}
	}

	virtual void Draw()
	{
		for(auto bg : vec_BG) bg->Draw();
		wnd->draw(shpPlanet);
		wnd->draw(shpCircle);
		for(auto enemy: vec_EnemyShape) wnd->draw(*enemy);
		wnd->draw(shpDialog);
		wnd->draw(shpHelp);
		for(auto t : vec_Turbo) t->Draw();
		wnd->draw(shpWheel);
		wnd->draw(shpTurret);
		
		for(auto b : vec_Button_Main) b->Draw();
		for(auto b : vec_Button_Settings) b->Draw();
		for(auto b : vec_Button_Graphics) b->Draw();

		wnd->draw(shpGameName);
		SCursor.setPosition(cur_p);

		double_damage.Draw();
		fragment_explosion.Draw();
		hight_overload.Draw();
		multiple_attack.Draw();
		time_slow.Draw();
		world_shield.Draw();
		splash_ricochet.Draw();
		signal_sos.Draw();
		plasm_attack.Draw();
		mirror_tank.Draw();
		turret_defender.Draw();
		black_hole.Draw();

		multiple_attack.DrawLock();	
		hight_overload.DrawLock();	
		world_shield.DrawLock();	
		double_damage.DrawLock();	
		time_slow.DrawLock();		
		fragment_explosion.DrawLock();
		splash_ricochet.DrawLock();	
		signal_sos.DrawLock();		
		plasm_attack.DrawLock();	
		mirror_tank.DrawLock();		
		turret_defender.DrawLock();	
		black_hole.DrawLock();		

		wnd->draw(SCursor);
	}

	virtual ~Main_Menu() {}
};