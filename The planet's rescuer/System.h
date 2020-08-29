#pragma once
#include "Texture.h"
#include "Audio.h"

class System
{
public:

	System(void* init);
	System(void);
	static void SystemTime();

	static void ConstructShape(Shape& shp, v2f pos, v2f siz, IMG& png, const bool perc_pos = true);
	static void ConstructShape(Shape& shp, v2f pos, v2f siz, const bool perc_pos = true);
	static void ConstructShape(Shape& shp, v2f pos, v2f siz, CLR clr, bool perc_pos = true);

	static void ConstructText(sf::Text& text, v2f pos, float siz, sf::String str, sf::Font* font, CLR col = CLR());
	static void CenteringText(sf::Text& text);

public:

	static SettingsConfig settings_config;
	static sf::RenderWindow* wnd;
	static sf::Clock clock;
	static sf::Event event;
	static sf::View cam;
	static sf::Font *font_freshman;
	static Shape SCursor;

	static float time;
	static float time_in_pause;
	static float time_enemy;
	static int scr_W;
	static int scr_H;
	static float scr_1;
	static float scr_1w;
	static v2f cam_p;
	static v2f cur_p;
	static v2f planet_p;
	static Texture* texture;
	static Audio* audio;
	static enum GSTATE {main_menu, game} gState;
	static bool isPauseGame;

	static bool isSound_Music_On;
	static bool isSound_Effects_On;
	static bool isVideo_Smoth_On;
	static bool isVideo_VertSync_On;
	static bool isLanguageRU;
	static uint sound_Vol_Music;
	static uint sound_Vol_Effects;

public:

	static float GetDistance(const v2f& p1, const v2f& p2);
	static float GetDistance(Shape& shape, const v2f& pos);
	static float GetDistance(Shape& s1, Shape& s2);

	static void MoveToAngle(Shape &shape, float speed, float angle, bool is_Enemy_Time = false);
	static void MoveToAngle(v2f& pos, float speed, float angle, bool is_Enemy_Time = false);

	static sf::FloatRect getVisible();

	static bool  GetCollisionCircle(Shape& s1, Shape& s2);

	static v2f GetNormalizedPosition(const v2f& pos, float dist, float angle);
	static v2f GetNormalizedPosition(Shape& shape, float dist, float angle);

	static float GetAngle(const v2f& p1, const v2f& p2);
	static float GetAngle(Shape& shp, const v2f& p);
	static float GetAngle(Shape& shp1, Shape& shp2);
};