#include "System.h"

SettingsConfig			System::settings_config;
sf::RenderWindow*		System::wnd;
sf::Clock				System::clock;
sf::Event				System::event;
sf::View				System::cam;
sf::Font*				System::font_freshman;
float					System::time;
float					System::time_in_pause;
float					System::time_enemy;
int						System::scr_W;
int						System::scr_H;
float					System::scr_1;
float					System::scr_1w;
v2f						System::cam_p;
v2f						System::cur_p;
v2f						System::planet_p;
Texture*				System::texture;
Audio*					System::audio;
enum System::GSTATE			System::gState;
bool					System::isPauseGame;
bool					System::isSound_Music_On;
bool					System::isSound_Effects_On;
bool					System::isVideo_Smoth_On;
bool					System::isVideo_VertSync_On;
bool					System::isLanguageRU;
uint					System::sound_Vol_Music;
uint					System::sound_Vol_Effects;
Shape					System::SCursor;

sf::FloatRect System::getVisible()
{
	return sf::FloatRect(float(planet_p.x - (scr_W/2)*1.4f), float(planet_p.y - (scr_H/2)*1.4f),  float(scr_W*1.8),  float(scr_H*1.8));
}

void System::SystemTime()
{
	time = float(clock.getElapsedTime().asMicroseconds() / 1000.f), clock.restart();
	time_enemy = time;
	cam_p = cam.getCenter();
	if(!isPauseGame) time_in_pause = time;
	else time_in_pause = 0;
	SCursor.rotate(0.1*time);
}

v2f System::GetNormalizedPosition(const v2f& pos, float dist, float angle)
{
	const float& A = angle * RAD;
	return pos + v2f(cosf(A),sinf(A))*dist;
}

v2f System::GetNormalizedPosition(Shape& shape, float dist, float angle)
{
	const float& A = angle * RAD;
	return shape.getPosition() + v2f(cosf(A),sinf(A))*dist;
}

void System::MoveToAngle(Shape &shape, float speed, float angle, bool is_Enemy_Time)
{
	const float& A = angle * RAD;
	const float S = speed * scr_1;
	if(is_Enemy_Time) shape.move(v2f(cosf(A),sinf(A)) * (S * time_enemy)); 
	else shape.move(v2f(cosf(A),sinf(A)) * (S * time)); 
}

void System::MoveToAngle(v2f& point, float speed, float angle, bool is_Enemy_Time)
{
	const float& A = angle * RAD;
	const float& S = speed * scr_1;
	if(is_Enemy_Time) point += v2f(cosf(A),sinf(A)) * (S * time_enemy);
	else point += v2f(cosf(A),sinf(A)) * (S * time);
}

bool System::GetCollisionCircle(Shape& c1, Shape& c2)
{
	const float r1 = c1.getSize().x / 2.f;
	const float r2 = c2.getSize().x / 2.f;
	const v2f& p1 = c1.getPosition();
	const v2f& p2 = c2.getPosition();
	return GetDistance(p1, p2) > float(r1 + r2) ? false : true;
}

float System::GetDistance(const v2f& p1, const v2f& p2)
{
	return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
}

float System::GetDistance(Shape& s1, Shape& s2)
{
	const v2f& p1 = s1.getPosition();	
	const v2f& p2 = s2.getPosition();
	return GetDistance(p1, p2);
}

float System::GetDistance(Shape& s1, const  v2f& pos)
{
	const v2f& p1 = s1.getPosition();
	return GetDistance(p1, pos);
}

void System::ConstructShape(Shape& shp, v2f pos, v2f siz, sf::Texture& png, const bool perc_pos)
{
	shp.setOrigin(siz*scr_1/2.f);
	shp.setSize(siz*scr_1);
	if(perc_pos) shp.setPosition(pos*scr_1);
	else shp.setPosition(pos);
	shp.setTexture(&png);
}

void System::ConstructShape(Shape& shp, v2f pos, v2f siz, const bool perc_pos)
{
	shp.setOrigin(siz*scr_1/2.f);
	shp.setSize(siz*scr_1);
	if(perc_pos) shp.setPosition(pos*scr_1);
	else shp.setPosition(pos);
}

void System::ConstructShape(Shape& shp, v2f pos, v2f siz, sf::Color color, bool perc_pos)
{
	shp.setSize(siz*scr_1);
	shp.setOrigin(siz*scr_1/2.f);
	shp.setFillColor(color);
	if(perc_pos) shp.setPosition(pos*scr_1);
	else shp.setPosition(pos);
}

void System::ConstructText(sf::Text& text, v2f pos, float siz, sf::String str, sf::Font* font, sf::Color col)
{
	text.setFont(*font);
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(uint(siz*scr_1));
	text.setColor(col);
	text.setString(str);
	text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
	text.setPosition(pos);
}

float System::GetAngle(const v2f& p1, const v2f& p2)
{
	return atan2f(p2.y - p1.y, p2.x - p1.x) * DEG;
}

float System::GetAngle(Shape& shp, const v2f& p)
{
	return atan2f(p.y - shp.getPosition().y, p.x - shp.getPosition().x) * DEG;
}

float System::GetAngle(Shape& shp1, Shape& shp2)
{
	const v2f& p1 = shp1.getPosition();
	const v2f& p2 = shp2.getPosition();
	return atan2f(p2.y - p1.y, p2.x - p1.x) * DEG;
}

void System::CenteringText(sf::Text& text)
{
	text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 1.5f);
}

System::System(bool init)
{
	if(init)
	{
		// Load configuration
		settings_config.is_cam_static = true;
		isLanguageRU = false;
		isPauseGame = false;
		gState = main_menu;
		scr_W = sf::VideoMode::getDesktopMode().width; 
		scr_H = sf::VideoMode::getDesktopMode().height;
		scr_1 = scr_H / 100.f;
		scr_1w = scr_W / 100.f;
		time_in_pause = 0;
		time = 0;

		wnd = new sf::RenderWindow(sf::VideoMode(scr_W,scr_H), "Game", sf::Style::Default, sf::ContextSettings(0,0,32));
		texture = new Texture();
		audio = new Audio();
		audio->setVolMusic(0);
		ConstructShape(SCursor, cur_p, v2f(4,4), texture->UI_Cursor);
		texture->setSmoth(true);
		font_freshman = new sf::Font;
		font_freshman->loadFromFile("res/Font/freshman.ttf");
		cam.reset(sf::FloatRect(0, 0, float(scr_W), float(scr_H)));
		cam.setCenter(0,0);
		cam_p = cam.getCenter();
		cur_p = v2f(0,0);
		wnd->setView(cam);
		wnd->setMouseCursorVisible(false);
		wnd->setFramerateLimit(60);
		srand(::time(0));
		clock.restart();
	}
}