#pragma once
#include "Level_01.h"
#include "Main_Menu.h"
#include <chrono>
#include<thread>
#include<mutex>

class Game : public System
{
private:

	vector<shared_ptr<oLevel>> vec_Level;
	vector<shared_ptr<Main_Menu>> vec_MainMenu;

public:

	sf::Thread* thread;

	Game() : System(true)
	{
		gState = main_menu;
		vec_MainMenu.push_back(make_shared<Main_Menu>(Main_Menu()));
		time = 0;
		wnd->setActive(false);
		//thread = new sf::Thread(&Game :: Thread, this);
		//thread->launch();

		Thread();

		// while (wnd->isOpen())
		// {
		// 	while(wnd->pollEvent(event))
		// 	{
		// 		if(event.type == sf::Event::Closed) wnd->close();

		// 		switch (gState)
		// 		{
		// 			case System::main_menu:

		// 				for(auto menu: vec_MainMenu) menu->Action();

		// 				break;

		// 			case System::game:

		// 				if(!vec_MainMenu.empty()) vec_MainMenu.clear();
		// 				for(auto level: vec_Level) level->Action(); 

		// 				break;
		// 		}
		// 	}
		// 	sf::sleep(sf::milliseconds(50));
		// }

		//thread->terminate();
	}

	void Thread()
	{
		sf::Text text_fps;
		int counter_frame = 0;
		float timer = 0;

		while (wnd->isOpen())
		{
			while(wnd->pollEvent(event))
			{
				if(event.type == sf::Event::Closed) wnd->close();

				switch (gState)
				{
					case System::main_menu:

						for(auto menu: vec_MainMenu) menu->Action();

						break;

					case System::game:

						if(!vec_MainMenu.empty()) vec_MainMenu.clear();
						for(auto level: vec_Level) level->Action(); 

						break;
				}
			}

			cur_p = wnd->mapPixelToCoords(sf::Mouse::getPosition(*wnd));
			SystemTime();
			timer+=time;
			counter_frame++;

			if(timer >= 250)
			{
				ConstructText(text_fps, v2f(0,0),1.5, sf::String(to_string(counter_frame*4)), font_freshman, sf::Color::Green);
				timer = 0;
				counter_frame = 0;
			}

			switch (gState)
			{
				case System::main_menu:
					
					for(auto menu: vec_MainMenu) menu->Update();
					break;

				case System::game:
					
					if(vec_Level.empty()) 
					{
						vec_Level.push_back(make_shared<Level_01>(Level_01()));
					}
					for(auto level: vec_Level) level->Update();

					break;
			}

			text_fps.setRotation(cam.getRotation());

			wnd->clear();

			switch (gState)
			{
			case System::main_menu:

				for(auto menu: vec_MainMenu) menu->Draw();

				break;

			case System::game:

				for(auto level: vec_Level) level->Draw();

				break;
			}

			wnd->draw(text_fps);
			wnd->display();
		}
	}

	~Game() {}
};
