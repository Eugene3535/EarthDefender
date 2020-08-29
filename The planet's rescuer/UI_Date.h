#include "System.h"

class UI_Date : public System
{
private:

	Shape shpBack;
	sf::Text text_Date;
	int year, month, day;
	bool isHighbrow;
	float timer_date;

public:

	UI_Date(int year, int month, int day) : 
		year(year),
		month(month),
		day(day),
		isHighbrow(false)
	{
		ConstructShape(shpBack, v2f(0,-scr_1*46.5), v2f(33.5,3.5), texture->UI_Bar,false);
		ConstructText(text_Date, v2f(0,-scr_1*46.5), 1.75, "Year : " + to_string(year) + " Month : " + to_string(month) + " Day : " + to_string(day), font_freshman, CLR::White);
	}

	virtual void Update(long &population)
	{
		timer_date += time;

		if(timer_date >= 180)
		{
			timer_date = 0;
			day++;

			if(day > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10)) { population += 5; month++; day = 1; }
			if(day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) { population += 5; month++; day = 1; }

			if(month == 2)
			{
				if(isHighbrow && day > 29) { month++; day = 1; population += 5; }
				else if(day > 28) { month++; day = 1; population += 5; }
			}

			if(month == 12)
			{
				if(day > 31)
				{
					month=1; 
					day = 1;
					year++;
					if((year - 1900)/4 == 0) isHighbrow = true;
					else isHighbrow = false;
					population += 5;
				}
			}
			text_Date.setString("Year " + to_string(year) + " : Month " + to_string(month) + " : Day " + to_string(day));
		}
	}

	virtual void Draw()
	{
		wnd->draw(shpBack);
		wnd->draw(text_Date);
	}

	virtual ~UI_Date() {}
};