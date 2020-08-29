#pragma once
#include "UI_People.h"
#include "UI_Hit_Point.h"
#include "UI_Date.h"
#include "UI_Experience.h"
#include "UI_Chance_Drop.h"
#include "oUI_Ability.h"

class UI_Tank : public System
{
public:

	UI_People		people;
	UI_Chance_Drop	chance_drop;
	UI_Hit_Point	hit_point;
	UI_Energy_Point energy_point;
	UI_Date			date;
	UI_EXP_BAR		experience;

	UI_Ability_Double_Damage		double_damage;
	UI_Ability_Fragment_Explosion	fragment_explosion;
	UI_Ability_Hight_Overload		hight_overload;
	UI_Ability_Multiple_Attack		multiple_attack;
	UI_Ability_Time_Slow			time_slow;
	UI_Ability_World_Shield			world_shield;
	UI_Ability_Splash_Ricochet		splash_ricochet;
	UI_Ability_Signal_SOS			signal_sos;
	UI_Ability_Plasm_Attack			plasm_attack;
	UI_Ability_Mirror_Tank			mirror_tank;
	UI_Ability_Turret				turret_defender;
	UI_Ability_Black_Hole			black_hole;

	UI_Tank() : 
		people(1600),
		hit_point(100, 1.0f),
		energy_point(100, 1.0f),
		experience(1,0),
		date(1900,1,1),
		double_damage(0),
		fragment_explosion(0),
		hight_overload(0),
		multiple_attack(0),
		time_slow(0),
		world_shield(0),
		splash_ricochet(0),
		signal_sos(0),
		plasm_attack(0),
		mirror_tank(0),
		turret_defender(0),
		chance_drop(0),
		black_hole(0)
	{
		
	}

	void Update(bool isEnemyEnabled)
	{
		people.Update();
		chance_drop.Update();
		hit_point.Update();
		energy_point.Update();
		date.Update(people.people);	
		experience.Update();

		double_damage.Update();
		fragment_explosion.Update();
		hight_overload.Update();
		multiple_attack.Update();
		time_slow.Update();
		world_shield.Update();
		splash_ricochet.Update();
		signal_sos.Update();
		plasm_attack.Update();
		mirror_tank.Update();
		turret_defender.Update();
		black_hole.Update();

		if(isEnemyEnabled)
		{
			double_damage.TickDuration();
			fragment_explosion.TickDuration();
			hight_overload.TickDuration();
			multiple_attack.TickDuration();
			time_slow.TickDuration();
			world_shield.TickDuration();
			splash_ricochet.TickDuration();
			signal_sos.TickDuration();
			plasm_attack.TickDuration();
			mirror_tank.TickDuration();
			turret_defender.TickDuration();
			black_hole.TickDuration();
		}
	}

	void Action()
	{
		
	}

	void Draw()
	{
		people.Draw();
		chance_drop.Draw();
		hit_point.Draw();
		energy_point.Draw();
		date.Draw();
		experience.Draw();

		/////////////////////////////////////////////////////////////////

		double_damage.Draw();
		fragment_explosion.Draw();
		hight_overload.Draw();
		multiple_attack.Draw();
		time_slow.Draw();
		world_shield.Draw();
		splash_ricochet.Draw();
		signal_sos.Draw();
		plasm_attack.Draw();
		mirror_tank.Draw();
		turret_defender.Draw();
		black_hole.Draw();
	}

	~UI_Tank()
	{

	}
};