#pragma once
#include"System.h"

class oMissle : public System
{
protected:

	float angle;
	float speed;
	bool isEnemy;
	const int damage;

public:

	Shape shape;

	oMissle(v2f pos, v2f siz, float speed, float angle, int damage, bool isEnemy) : speed(speed), angle(angle), isEnemy(isEnemy), damage(damage)
	{
		shape.setRotation(angle);
	}

	oMissle(const int damage) : damage(damage) { shape.setRotation(angle); }

	virtual void Update()
	{
		MoveToAngle(shape, speed, angle, isEnemy);
	}

	virtual int getDamage() const
	{
		return damage;
	}

	virtual void setAngle(float angle)
	{
		this->angle = angle;
		shape.setRotation(this->angle);
	}

	virtual void Draw()
	{
		wnd->draw(shape);
	}

	virtual ~oMissle(){}
	
};

class Missle : public oMissle
{
public:

	Missle(v2f pos, v2f siz, float speed, float angle, sf::Texture& img, int damage, bool isEnemy) : oMissle(pos, siz, speed, angle, damage, isEnemy)
	{
		ConstructShape(shape, pos, siz, false);
		shape.setTexture(&img);
		shape.setRotation(angle);
	}

	virtual void Update()
	{
		MoveToAngle(shape, speed, angle, isEnemy);
	}

	virtual void Draw()
	{
		wnd->draw(shape);
	}

	virtual ~Missle(){}
	
};

class Missle_Plasm : public oMissle
{
private:

	Shape shape2;
	v2f size;
	v2f pos_snap;
	float alpha;
	bool isRotDir;
	const float radius;
	sf::Color color;

public:

	Missle_Plasm(v2f pos, v2f siz, float speed, float angle, sf::Texture& img, int damage,  bool isEnemy, bool isRicochet) : 
		oMissle(pos, siz, speed, angle, damage, isEnemy), 
		color(color),
		alpha(0),
		radius(0.75*scr_1),
		isRotDir(bool(rand()%2))
	{
		ConstructShape(shape, pos, siz, img, false);
		shape.setRotation(angle);
		shape2 = shape;
		shape2.setSize(shape.getSize()/1.5f);
		shape2.setScale(-1,-1);
		pos_snap = shape.getPosition();

		if(!isRicochet)
		{
			shape.setFillColor(sf::Color(rand()%156+100,rand()%156+100,rand()%156+100));
			shape2.setFillColor(shape.getFillColor());
		}
		else
		{
			shape.setFillColor(sf::Color(255,rand()%50+100,rand()%50+100));
			shape2.setFillColor(sf::Color(255,rand()%50+100,rand()%50+100));
		}
	}

	virtual void Update()
	{
		alpha += time*0.075;
		MoveToAngle(pos_snap, speed, angle, false); 
		shape.rotate (0.5*time);
		shape2.rotate(-.5*time);
		shape.setPosition(pos_snap + v2f(cos(alpha), sin(alpha))*radius);
		shape2.setPosition(pos_snap + v2f(cos(alpha), sin(alpha))*radius);
	}

	virtual void Draw()
	{
		wnd->draw(shape);
		wnd->draw(shape2);
	}

	virtual ~Missle_Plasm(){}
	
};


class Missle_Lighting_Ball : public oMissle
{
public:

	Shape shape2;

	Missle_Lighting_Ball(v2f pos, v2f siz, float speed, float angle, sf::Texture& img, int damage,  bool isEnemy) : oMissle(pos, siz, speed, angle, damage, isEnemy)
	{
		ConstructShape(shape, pos, siz, img, false);
		shape2 = shape;
		shape2.setScale(-1,-1);
	}

	virtual void Update()
	{
		oMissle::Update();
		shape2.setPosition(shape.getPosition());
		shape.rotate(0.5f*time);
		shape2.rotate(-0.5f*time);
	}

	virtual void Draw()
	{
		wnd->draw(shape);
		wnd->draw(shape2);
	}

	virtual ~Missle_Lighting_Ball() {}
};
