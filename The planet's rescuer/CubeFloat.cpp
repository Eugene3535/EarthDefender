#include "CubeFloat.h"

CubeFloat::CubeFloat(v2f pos, v2f siz, float iof, float rad) : IOF(iof/=1000.f), radius(rad*scr_1), timer_create_spec_effect(0), timer_anim(16, 100, 0, 0, true), timer_outline(0, 200,0,0, true)
{
	alpha = 0;
	ConstructShape(shape, pos, siz, CLR::Transparent);

	for(int i = 0; i < 2; i++)
	{
		ConstructShape(shpDarkEye[i], pos, siz/1.5f, texture->EFF_DarkEye);
		ConstructShape(shpPortalEffect[i], pos, siz/1.5f, texture->EFF_PortalEffectFire);
	}

	for(int i = 0; i < 4; i++)
	{
		ConstructShape(shpEmitter[i], pos, v2f(siz.x/4.5f, siz.y/4.5f), texture->Emiter);
		shpEmitter[i].setRotation(i*90);
		ConstructShape(shpLighting[i], GetNormalizedPosition(shape, shape.getSize().x/2.25f, shpLighting[i].getRotation()+shape.getRotation()), v2f(siz.x/6, siz.y*0.9), texture->EFF_Lighting_16);
		shpLighting[i].setRotation(i*90);
		shpEmitter[i].setScale(-1,-1);
	}

	shpDarkEye[0].setScale(-1,-1);
	shpPortalEffect[0].setScale(-1,-1);

	SPAWN_POS = shape.getPosition();
}

void CubeFloat::Update()
{
	alpha += IOF*time;

	const float c = cos(alpha);
	const float s = sin(alpha);
	const CLR color(255 * (1.f+s)/2.f, 255 * (1.f+c)/2.f, 255 * (1.f+cos(alpha/2))/2.f, 50);

	shape.setPosition(SPAWN_POS + v2f(cos(alpha), sin(alpha))*radius);
	//shape.setFillColor(CLR(color.b,color.r,color.g,180));
	if(timer_outline.TickEnd())
	{
		shape.setOutlineColor(CLR(color.r,color.g,color.b,180));
		shape.setOutlineThickness(-cos(alpha)*(shape.getSize().x/4.f));
	}
	shape.setRotation(cos(alpha)*45.f);

	timer_create_spec_effect += time;
	if(timer_create_spec_effect > 5)
	{
		timer_create_spec_effect = 0;
		int r = rand()%360;
		vec_SpecEffect.push_back(make_shared<SpecEffect_CubexSpark>(
			SpecEffect_CubexSpark(GetNormalizedPosition(shape, shape.getSize().x/3.f/scr_1, r), shape.getSize()*0.05f/scr_1, shape.getFillColor(), r, 3000, 0.01)));
		vec_SpecEffect.push_back(make_shared<SpecEffect_CubexSpark>(
			SpecEffect_CubexSpark(GetNormalizedPosition(shape, shape.getSize().x/5.f/scr_1, r), shape.getSize()*0.04f/scr_1, shape.getOutlineColor(), r, 2000, 0.02)));
	}

	for(auto& it = vec_SpecEffect.begin(); it != vec_SpecEffect.end();)
	{
		auto& spec_effect = *(*it);
		if(spec_effect.IsEnd()) it = vec_SpecEffect.erase(it);
		else
		{
			spec_effect.Update();
			it++;
		}
	}

	const bool& a = timer_anim.TickEnd();
	for(int i = 0; i < 4; i++) 
	{
		shpEmitter[i].setRotation(shape.getRotation()+(i*90)+45);
		shpLighting[i].setRotation(shape.getRotation()+(i*90));
		shpEmitter[i].setPosition(GetNormalizedPosition(shape.getPosition(), shape.getSize().x/1.6f, shpEmitter[i].getRotation()));
		shpLighting[i].setPosition(GetNormalizedPosition(shape.getPosition(), shape.getSize().x/2.15f, shpLighting[i].getRotation()));

		//const CLR& c1 = shape.getFillColor();
		//const CLR& c2 = shape.getOutlineColor();
		//shpLighting[i].setFillColor(CLR((c1.r + c2.r)/2, (c1.g + c2.g)/2, (c1.b + c2.b)/2));

		if( a ) shpLighting[i].setTextureRect(sf::IntRect(timer_anim.order_current*25,0,25,204));
	}
		shpDarkEye[0].rotate( time*0.3);
		shpDarkEye[1].rotate(-time*0.3);
		shpPortalEffect[0].rotate( time*0.3);
		shpPortalEffect[1].rotate(-time*0.3);
}

void CubeFloat::Draw()
{
	wnd->draw(shape);

	for(auto& spec_effect : vec_SpecEffect) 
		spec_effect->Draw();

	for(int i = 0; i < 2; i++) 
	{
		wnd->draw(shpPortalEffect[i]);
		wnd->draw(shpDarkEye[i]);
		shpPortalEffect[i].setPosition(shape.getPosition());
		shpDarkEye[i].setPosition(shape.getPosition());
	}

	for(int i = 0; i < 4; i++) wnd->draw(shpLighting[i]);
	for(int i = 0; i < 4; i++)
	{
		shpEmitter[i].rotate(-45);
		wnd->draw(shpEmitter[i]);
		shpEmitter[i].rotate(45);
	}
}

void CubeFloat::Action()
{

}

CubeFloat::~CubeFloat(void)
{

}