#pragma once
#include"System.h"

class oMirror_Effect : public System
{
public:

	oMirror_Effect() {}
	virtual ~oMirror_Effect(void) {}
	virtual void Update() = 0;
	virtual void Scaling() = 0;
	virtual bool getKill() const = 0;
	virtual void Draw() = 0;
};

// Эффект для одного шейпа. БЕЗ ВРАЩЕНИЯ.
class Mirror_Effect_One_No_Rot : public oMirror_Effect
{
protected:

	Shape shape;
	float alpha;
	sf::Color color;

public:

	Mirror_Effect_One_No_Rot(Shape& shp)
	{
		shape = shp;
		color = shp.getFillColor();
		alpha = color.a;
	}

	virtual void Update()
	{
		alpha -= 0.5f * time;
		if(alpha < 0) alpha = 0;
		shape.setFillColor(sf::Color(color.r,color.g,color.b,uint(alpha)));
	}

	virtual void Scaling()
	{
		shape.setScale(v2f(shape.getFillColor().a,shape.getFillColor().a)/float(color.a));
	}

	virtual bool getKill() const
	{
		return alpha == 0;
	}

	virtual void Draw()
	{
		wnd->draw(shape);
	}

	virtual ~Mirror_Effect_One_No_Rot(void)
	{

	}
};

// Эффект для одного шейпа. С ВРАЩЕНИЕМ.
class Mirror_Effect_One_Yes_Rot : public oMirror_Effect
{
protected:

	Shape shape;
	float alpha;
	short isLeft;
	sf::Color color;

public:

	Mirror_Effect_One_Yes_Rot(Shape shp) : isLeft(rand()%2)
	{
		shape = shp;
		color = shp.getFillColor();
		alpha = color.a;
	}

	virtual void Update()
	{
		alpha -= 0.5f * time;
		if(alpha < 0) alpha = 0;
		if(isLeft == 0) shape.rotate(0.08f * time);
		else shape.rotate(-0.08f * time);
		shape.setFillColor(sf::Color(color.r,color.g,color.b,uint(alpha)));
	}

	virtual void Scaling()
	{
		shape.setScale(v2f(shape.getFillColor().a,shape.getFillColor().a)/float(color.a));
	}

	bool getKill() const
	{
		return alpha == 0;
	}

	virtual void Draw()
	{
		wnd->draw(shape);
	}

	virtual ~Mirror_Effect_One_Yes_Rot(void)
	{

	}
};