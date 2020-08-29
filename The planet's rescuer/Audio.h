#pragma once
#include <SFML\Audio.hpp>
typedef sf::SoundBuffer Buff;
typedef unsigned int uint;
using namespace std;

class Audio
{
public:

	Buff testBuff;
	sf::Sound testSound;

	sf::Music music_main_menu;
	sf::Music music_game[9];
	sf::Music music_victory;

public:

	void setVolEffects(uint vol)
	{
		testSound.setVolume(vol);
	}

	void setVolMusic(uint vol)
	{
		music_main_menu.setVolume(vol);
		music_victory.setVolume(vol);
		for(int i = 0; i < 9; i++) music_game[i].setVolume(vol);
	}

	Audio(void)
	{
		LoadSound("000testSound.wav", testSound, testBuff);

		LoadMusic("RWG - Starfall.ogg", music_main_menu);
		LoadMusic("RWG - Arcade.ogg", music_game[0]);
		LoadMusic("RWG - Autumn.ogg", music_game[1]);
		LoadMusic("RWG - Dungeon Of Immolation.ogg", music_game[2]);
		LoadMusic("RWG - Echo.ogg", music_game[3]);
		LoadMusic("RWG - Glowing Lights.ogg", music_game[4]);
		LoadMusic("RWG - Incoming Message.ogg", music_game[5]);
		LoadMusic("RWG - Last Chance.ogg", music_game[6]);
		LoadMusic("RWG - Overload.ogg", music_game[7]);
		LoadMusic("RWG - Pulse.ogg", music_game[8]);
				   
		LoadMusic("RWG - Heavy Rain.ogg", music_victory);
	}

	void stopMusic()
	{
		music_main_menu.stop();
		music_victory.stop();
		for(int i = 0; i < 9; i++) music_game[i].stop();
	}

	~Audio(void){}

private:

	inline void LoadSound(string file, sf::Sound& s, sf::SoundBuffer& b)
	{
		b.loadFromFile("Resources/Sounds/"+file);
		s.setBuffer(b);
	}

	inline void LoadMusic(string file, sf::Music& m)
	{
		m.openFromFile("Resources/Music/"+file);
		m.setLoop(true);
	}
};