#include "System.h"
// ��������� ���� ������� ����� ������� ���� �������
// ����� ����� ����� 3 + (tank.level / 4);

SettingsConfig			B::settings_config;
sf::RenderWindow*		B::wnd;
sf::Clock				B::clock;
sf::Event				B::event;
sf::View				B::cam;
sf::Font*				B::font_freshman;
float					B::time;
float					B::time_in_pause;
float					B::time_enemy;
int						B::scr_W;
int						B::scr_H;
float					B::scr_1;
float					B::scr_1w;
v2f						B::cam_p;
v2f						B::cur_p;
v2f						B::planet_p;
Texture*				B::texture;
Audio*					B::audio;
enum B::GSTATE			B::gState;
bool					B::isPauseGame;
bool					B::isSound_Music_On;
bool					B::isSound_Effects_On;
bool					B::isVideo_Smoth_On;
bool					B::isVideo_VertSync_On;
bool					B::isLanguageRU;
uint					B::sound_Vol_Music;
uint					B::sound_Vol_Effects;
Shape					B::SCursor;

sf::FloatRect B::getVisible()
{
	return sf::FloatRect(float(planet_p.x - (scr_W/2)*1.4f), float(planet_p.y - (scr_H/2)*1.4f),  float(scr_W*1.8),  float(scr_H*1.8));
}

void B::SystemTime()
{
	time = float(clock.getElapsedTime().asMicroseconds() / 1000.f), clock.restart();
	time_enemy = time;
	cam_p = cam.getCenter();
	if(!isPauseGame) time_in_pause = time;
	else time_in_pause = 0;
	SCursor.rotate(0.1*time);
}

v2f B::GetNormalizedPosition(const v2f& pos, float dist, float angle)
{
	const float& A = angle * RAD;
	return pos + v2f(cosf(A),sinf(A))*dist;
}

v2f B::GetNormalizedPosition(Shape& shape, float dist, float angle)
{
	const float& A = angle * RAD;
	return shape.getPosition() + v2f(cosf(A),sinf(A))*dist;
}

void B::MoveToAngle(Shape &shape, float speed, float angle, bool is_Enemy_Time)
{
	const float& A = angle * RAD;
	const float S = speed * scr_1;
	if(is_Enemy_Time) shape.move(v2f(cosf(A),sinf(A)) * (S * time_enemy)); 
	else shape.move(v2f(cosf(A),sinf(A)) * (S * time)); 
}

void B::MoveToAngle(v2f& point, float speed, float angle, bool is_Enemy_Time)
{
	const float& A = angle * RAD;
	const float& S = speed * scr_1;
	if(is_Enemy_Time) point += v2f(cosf(A),sinf(A)) * (S * time_enemy);
	else point += v2f(cosf(A),sinf(A)) * (S * time);
}

bool B::GetCollisionCircle(Shape& c1, Shape& c2)
{
	const float r1 = c1.getSize().x / 2.f;
	const float r2 = c2.getSize().x / 2.f;
	const v2f& p1 = c1.getPosition();
	const v2f& p2 = c2.getPosition();
	return GetDistance(p1, p2) > float(r1 + r2) ? false : true;
}

float B::GetDistance(const v2f& p1, const v2f& p2)
{
	return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
}

float B::GetDistance(Shape& s1, Shape& s2)
{
	const v2f& p1 = s1.getPosition();	
	const v2f& p2 = s2.getPosition();
	return GetDistance(p1, p2);
}

float B::GetDistance(Shape& s1, const  v2f& pos)
{
	const v2f& p1 = s1.getPosition();
	return GetDistance(p1, pos);
}

void B::ConstructShape(Shape& shp, v2f pos, v2f siz, IMG& png, const bool perc_pos)
{
	shp.setOrigin(siz*scr_1/2.f);
	shp.setSize(siz*scr_1);
	if(perc_pos) shp.setPosition(pos*scr_1);
	else shp.setPosition(pos);
	shp.setTexture(&png);
}

void B::ConstructShape(Shape& shp, v2f pos, v2f siz, const bool perc_pos)
{
	shp.setOrigin(siz*scr_1/2.f);
	shp.setSize(siz*scr_1);
	if(perc_pos) shp.setPosition(pos*scr_1);
	else shp.setPosition(pos);
}

void B::ConstructShape(Shape& shp, v2f pos, v2f siz, CLR clr, bool perc_pos)
{
	shp.setSize(siz*scr_1);
	shp.setOrigin(siz*scr_1/2.f);
	shp.setFillColor(clr);
	if(perc_pos) shp.setPosition(pos*scr_1);
	else shp.setPosition(pos);
}

void B::ConstructText(sf::Text& text, v2f pos, float siz, sf::String str, sf::Font* font, CLR col)
{
	text.setFont(*font);
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(uint(siz*scr_1));
	text.setColor(col);
	text.setString(str);
	text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
	text.setPosition(pos);
}

float B::GetAngle(const v2f& p1, const v2f& p2)
{
	return atan2f(p2.y - p1.y, p2.x - p1.x) * DEG;
}

float B::GetAngle(Shape& shp, const v2f& p)
{
	return atan2f(p.y - shp.getPosition().y, p.x - shp.getPosition().x) * DEG;
}

float B::GetAngle(Shape& shp1, Shape& shp2)
{
	const v2f& p1 = shp1.getPosition();
	const v2f& p2 = shp2.getPosition();
	return atan2f(p2.y - p1.y, p2.x - p1.x) * DEG;
}

void B::CenteringText(sf::Text& text)
{
	text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 1.5f);
}

B::System(){}

B::System(bool init)
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
//		wnd->setFramerateLimit(60);
		srand(::time(0));
		clock.restart();
	}
}