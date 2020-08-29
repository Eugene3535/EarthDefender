#pragma once
#include "System.h"

/* Содержание: 

	# oButton
	# Button_Float 
	# Button_Picked 
	# Button_YN

*/

// Обыкновенная кнопка

class Button :
	public System
{

protected:

	bool is_Inside;
	bool is_Click;
	Shape glow;
	Shape shape;
	sf::Text text;
	string name_id;

public:

	Button(v2f pos, v2f siz, IMG& img, const sf::String& str_text, const sf::String str_id) :
		name_id(str_id),
		is_Inside(false), 
		is_Click(false)
	{
		ConstructShape(shape, pos, siz, img, true);
		ConstructShape(glow, pos, siz, texture->UI_Ico, true);
		ConstructText(text, shape.getPosition(), siz.y/2.f, str_text, font_freshman, CLR(180,180,180));
	}

	virtual ~Button(void)
	{
	}

	virtual void Update()
	{
		is_Inside ? text.setColor(CLR(0,200,155)) : text.setColor(CLR(180,180,180));
	}

	virtual void Draw()
	{
		wnd->draw(shape);
		if(is_Inside) wnd->draw(glow);
		wnd->draw(text);
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
		text.setPosition(p.x, p.y);
		glow.setPosition(p);
	}

	void setTextString(const sf::String& str)
	{
		text.setString(str);
	}

	string getNameID() const
	{
		return name_id;
	}

	virtual void setFillColor(CLR color)
	{
		shape.setFillColor(color);
	}
};

// Класс плавающей кнопки

class Button_Float :
	public Button
{
private:

	const v2f pos_deft;
	float alpha;
public:

	Button_Float(v2f pos, v2f siz, IMG& texture, const sf::String& str_text,const sf::String& str_id) : 
		Button(pos, siz, texture, str_text, str_id), 
		pos_deft(shape.getPosition()), 
		alpha(0)
	{
	}
	
	virtual void Update()
	{
		Button::Update();
		if(is_Inside)
		{
			alpha += 0.0010f*time;
			shape.setPosition(pos_deft.x + scr_1 * cosf(alpha),pos_deft.y);
			glow.setPosition(pos_deft.x + scr_1 * cosf(alpha),pos_deft.y);
			text.setPosition(pos_deft.x + scr_1 * cosf(alpha),pos_deft.y);
		}
		else
		{
			shape.setPosition(pos_deft);
			glow.setPosition(pos_deft);
			text.setPosition(pos_deft);
		}
	}
	
	~Button_Float(void){}
};

// Класс кнопки с возможностью выбора

class Button_Picked :
	public Button
{
public:

	Button_Picked(v2f pos, v2f siz, IMG& texture, const sf::String& str_text,const sf::String& str_id) : 
		Button(pos, siz, texture, str_text, str_id){}

	virtual void Update()
	{
		Button::Update();
		if(is_Inside)
		{
			shape.setFillColor(CLR::Green);
			text.setColor(CLR(0,200,155));
		}
		else
		{
			shape.setFillColor(CLR::White);
			text.setColor(CLR(180,180,180));
		}
	}

	~Button_Picked(void){}
};