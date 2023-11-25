#include "System.h"

class UI_People : public System
{
private:

	sf::Text text;
	Shape shpIcoPlanet;
	Shape barPlanet;
	Shape shpPlanet;

public:

	long people;

	UI_People(long piple) : people(piple)
	{
		ConstructShape(barPlanet, v2f(34,-45), v2f(25,7), texture->UI_Bar);
		ConstructShape(shpIcoPlanet, v2f(50,-45), v2f(7,7), texture->UI_Ico);
		ConstructText(text, v2f(34,-45)*scr_1, 2, "People: " + to_string(piple) + "M", font_freshman, CLR::White);
		ConstructShape(shpPlanet, v2f(50,-45), v2f(7,7), texture->UI_People);
	}

	virtual void Update()
	{
		 ConstructText(text, v2f(34,-45)*scr_1, 2, "People: " + to_string(people) + "M", font_freshman, CLR::White);
	}

	virtual void Draw()
	{
		wnd->draw(barPlanet);
		wnd->draw(shpIcoPlanet);
		wnd->draw(shpPlanet);
		wnd->draw(text);
	}

	void Kill(unsigned long number)
	{
		people -= number;
		if(people < 0) people = 0;
	}

	virtual ~UI_People() {}
};