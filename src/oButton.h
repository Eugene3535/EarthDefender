#pragma once
#include "System.h"

class oButton : public System
{

protected:

	bool is_Inside;
	bool is_Click;
	Shape glow;

	string name_id;

public:

	Shape shpText;
	Shape shape;

	oButton::oButton(v2f pos, v2f siz, sf::Texture& img, sf::Texture& text, const sf::String str_id) :
		name_id(str_id),
		is_Inside(false), 
		is_Click(false)
	{
		ConstructShape(shape, pos, siz, img, true);
		ConstructShape(shpText, pos, siz, text, true);
		ConstructShape(glow, pos, siz, texture->EFF_Glow, true);
	}

	virtual ~oButton(void)
	{
	}

	virtual void Update()
	{
		is_Inside ? shpText.setFillColor(sf::Color(180,180,180)) : shpText.setFillColor(sf::Color::White);
	}

	virtual void Draw()
	{
		wnd->draw(shape);
		if(is_Inside) wnd->draw(glow);
		wnd->draw(shpText);
	}

	virtual bool isActivate()
	{
		if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseMoved )
		{
			shape.getGlobalBounds().contains(cur_p) ? is_Inside = true : is_Inside = false;
		}

		if(event.type == sf::Event::MouseButtonPressed)
		{
			if(event.key.code == sf::Mouse::Left && is_Inside)
			{
				shape.setScale(v2f(.95f,.95f));
				is_Click = true;
			}
		}

		if(event.type == sf::Event::MouseButtonReleased)
		{
			if(event.key.code == sf::Mouse::Left && is_Click) 
			{
				is_Click = false; 
				shape.setScale(v2f(1,1));
				if(is_Inside) 
				{
					//sound->ClickButton.play();
					is_Inside = false;
					return true;
				}
			}
		}
		return false;
	}

	virtual void setPosition(const v2f& p)
	{
		shape.setPosition(p);
		shpText.setPosition(p);
		glow.setPosition(p);
	}

	void setTextString(const sf::String& str)
	{
		cout << "oButton::Function setTextString empty...\n";
		//text.setString(str);
	}

	string getNameID() const
	{
		return name_id;
	}

	virtual void setFillColor(sf::Color color)
	{
		shape.setFillColor(color);
		shpText.setFillColor(color);
		glow.setFillColor(color);
	}
};

// Класс плавающей кнопки

class Button_Float : public oButton
{
private:

	const v2f pos_deft;
	float alpha;

public:

	Button_Float(v2f pos, v2f siz, sf::Texture& img, sf::Texture& text, const sf::String& str_text,const sf::String& str_id) : 
		oButton(pos, siz, img, text, str_id), 
		pos_deft(shape.getPosition()), 
		alpha(0)
	{
	}
	
	virtual void Update()
	{
		oButton::Update();
		if(is_Inside)
		{
			alpha += 0.0010f*time;
			shape.setPosition(pos_deft.x + scr_1 * cosf(alpha),pos_deft.y);
			glow.setPosition(pos_deft.x + scr_1 * cosf(alpha),pos_deft.y);
			shpText.setPosition(pos_deft.x + scr_1 * cosf(alpha),pos_deft.y);
		}
		else
		{
			shape.setPosition(pos_deft);
			glow.setPosition(pos_deft);
			shpText.setPosition(pos_deft);
		}
	}
	
	~Button_Float(void){}
};

// Класс кнопки с возможностью выбора

class Button_Picked : public oButton
{
public:

	Button_Picked(v2f pos, v2f siz, sf::Texture& img, sf::Texture& text,const sf::String& str_id) : 
		oButton(pos, siz, img, text, str_id)
	{
	}

	virtual void Update()
	{
		oButton::Update();
		if(is_Inside)
		{
			shape.setFillColor(sf::Color::Green);
			shpText.setFillColor(sf::Color(0,200,155));
		}
		else
		{
			shape.setFillColor(sf::Color::White);
			shpText.setFillColor(sf::Color(180,180,180));
		}
	}

	~Button_Picked(void){}
};

// Обыкновенная кнопка

class Button_YN : public oButton
{
public:

	Button_YN(v2f pos, v2f siz, sf::Texture& img, sf::Texture& text,const sf::String& str_id) : 
		oButton(pos, siz, img, text, str_id){}

	~Button_YN(void){}
};