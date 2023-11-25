#pragma once
#include"Define.h"

class Texture
{
public: sf::Texture

	// UI

	UI_Cursor, 
	UI_Ico, 
	UI_Bar, 
	UI_Bar_x2, 
	UI_HP_Line, 
	UI_Energy_Line, 
	UI_EXP_Line,
	UI_People, 
	UI_Chance_Drop,
	UI_Button_Upgrade, 
	UI_Dialog,
	UI_Button_Main,

	UI_Text_Play,
	UI_Text_Options,
	UI_Text_Exit,
	UI_Text_Help,
	UI_Text_Level, 
	UI_Text_Back,
	UI_Text_Sound,
	UI_Text_Save,
	UI_Text_Graphics,
	UI_Text_The_Planet_Rescuer,
	UI_Text_Cancel,
	UI_Text_Resume,
	UI_Text_Language_RU,
	UI_Text_Language_EN,

	UI_Num[10], 
	UI_Ico_vp, 
	UI_Ico_dt, 
	UI_Ico_kim,
	UI_Locked,
	
	// Bonuses

	Bonus_Plato, 
	Bonus_HP[3], 
	Bonus_Energy[3], 
	Bonus_Power[3], 
	Bonus_Shock[3], 
	Bonus_Experience[3], 
	Bonus_Multiple[3], 
	Bonus_Fragment_Explosion[3], 
	Bonus_Slow[3], 
	Bonus_Shield[3], 
	Bonus_Splash_Ricochet[3], 
	Bonus_Signal_SOS[3], 
	Bonus_Plasm_Attack[3], 
	Bonus_Mirror_Tank[3], 
	Bonus_Turret_Defender[3],
	Bonus_Black_Hole[3],

	// Tank

	Tank_Wheel, 
	Tank_Turret, 
	Tank_Radius, 
	Earth[66], 
	Defender_Wheel, 
	Defender_Turret, 
	Turret_Installer,
	SOS[2],

	// Enemy

	Asteroid[7], 
	Enemy[25], 
	Kamikadze[5],
	UFO[6],
	Transporter[5],
	Boss_03[5],

	// Effects

	EFF_FireFlash, 
	EFF_Bang_01, 
	EFF_Bang_02, 
	EFF_Bang_03, 
	EFF_Shield, 
	EFF_Shield_Effect,
	EFF_Shock_01, 
	EFF_Glow,
	EFF_Effect_Star,
	EFF_Flare, 
	EFF_Warning_Red_Circle,
	EFF_Portal_Dark,
	EFF_Portal_Tornado_Dark,
	EFF_Shard_Green,
	EFF_Shard_Red,

	EFF_Turbo, 
	EFF_Turbo_Boss,
	EFF_Locust_Shards,
	EFF_Bonus_Border, 
	EFF_Lighting_16,

	EFF_BlackHole[4],

	// Missle

	MissleT[17],

	// BackGround

	BG_Galaxy[20], 
	BG_Star[10], 
	Universe1, 
	Universe2;

	inline void Load(sf::Texture& texture, const string& file)
	{
		texture.loadFromFile("res/Texture/"+file);
	}

public: 

	void setSmoth(bool isSmooth)
	{
		// UI

		UI_Cursor.setSmooth(isSmooth), 
		UI_Ico.setSmooth(isSmooth), 
		UI_Bar.setSmooth(isSmooth), 
		UI_Bar_x2.setSmooth(isSmooth),
		UI_HP_Line.setSmooth(isSmooth), 
		UI_Energy_Line.setSmooth(isSmooth),
		UI_HP_Line.setSmooth(isSmooth), 
		UI_People.setSmooth(isSmooth), 
		UI_Chance_Drop.setSmooth(isSmooth),
		UI_Button_Upgrade.setSmooth(isSmooth),
		UI_Button_Main.setSmooth(isSmooth), 

		UI_Text_The_Planet_Rescuer.setSmooth(isSmooth),
		UI_Text_Play.setSmooth(isSmooth), 
		UI_Text_Back.setSmooth(isSmooth),
		UI_Text_Options.setSmooth(isSmooth), 
		UI_Text_Exit.setSmooth(isSmooth), 
		UI_Text_Help.setSmooth(isSmooth),
		UI_Text_Level.setSmooth(isSmooth), 
		UI_Text_Save.setSmooth(isSmooth),
		UI_Text_Sound.setSmooth(isSmooth),
		UI_Text_Graphics.setSmooth(isSmooth),
		UI_Text_Cancel.setSmooth(isSmooth),
		UI_Text_Resume.setSmooth(isSmooth),
		UI_Text_Language_RU.setSmooth(isSmooth),
		UI_Text_Language_EN.setSmooth(isSmooth),

		UI_Ico_dt.setSmooth(isSmooth), 
		UI_Ico_vp.setSmooth(isSmooth), 
		UI_Ico_kim.setSmooth(isSmooth);
		UI_Locked.setSmooth(isSmooth);

		for(int i = 0; i < 10; i++)
		{
			UI_Num[i].setSmooth(isSmooth);
		}

		// Bonuses
		Bonus_Plato.setSmooth(isSmooth);

		for(int i = 0; i < 3; i++)
		{
			Bonus_HP[i].setSmooth(isSmooth), 
			Bonus_Energy[i].setSmooth(isSmooth),
			Bonus_Power[i].setSmooth(isSmooth), 
			Bonus_Shock[i].setSmooth(isSmooth), 
			Bonus_Experience[i].setSmooth(isSmooth),
			Bonus_Multiple[i].setSmooth(isSmooth),
			Bonus_Fragment_Explosion[i].setSmooth(isSmooth), 
			Bonus_Slow[i].setSmooth(isSmooth), 
			Bonus_Shield[i].setSmooth(isSmooth), 
			Bonus_Splash_Ricochet[i].setSmooth(isSmooth),
			Bonus_Signal_SOS[i].setSmooth(isSmooth), 
			Bonus_Plasm_Attack[i].setSmooth(isSmooth), 
			Bonus_Mirror_Tank[i].setSmooth(isSmooth), 
			Bonus_Turret_Defender[i].setSmooth(isSmooth);
		}

		// Tank

		Tank_Wheel.setSmooth(isSmooth), 
		Tank_Turret.setSmooth(isSmooth), 
		Tank_Radius.setSmooth(isSmooth),
		Turret_Installer.setSmooth(isSmooth);

		for(int i = 0; i < 2; i++)
		{
			SOS[i].setSmooth(isSmooth);
		}

		for(int i = 0; i < 66; i++)
		{
			Earth[i].setSmooth(isSmooth);
		}

		// BackGround

		for(int i = 0; i < 20; i++)
		{
			BG_Galaxy[i].setSmooth(isSmooth);
		}

		for(int i = 0; i < 10; i++)
		{
			BG_Star[i].setSmooth(isSmooth);
		}

		Universe1.setSmooth(isSmooth),
		Universe2.setSmooth(isSmooth),
		Defender_Turret.setSmooth(isSmooth), 
		Defender_Wheel.setSmooth(isSmooth);

		// Enemy

		for(int i = 0; i < 25; i++) 
		{
			Enemy[i].setSmooth(isSmooth);
		}

		for(int i = 0; i < 7; i++) Asteroid[i].setSmooth(isSmooth);

		for(int i = 0; i < 6; i++) UFO[i].setSmooth(isSmooth);
		for(int i = 0; i < 5; i++) 
		{
			Transporter[i].setSmooth(isSmooth);
			Kamikadze[i].setSmooth(isSmooth);
		}
		for(int i = 0; i < 5; i++) Boss_03[i].setSmooth(isSmooth);

		// Missle

		for(int i = 0; i < 17; i++)
		{
			MissleT[i].setSmooth(isSmooth);
		}

		// Effects

		EFF_Shock_01.setSmooth(isSmooth), 
		EFF_Turbo.setSmooth(isSmooth), 
		EFF_Turbo_Boss.setSmooth(isSmooth),
		EFF_Flare.setSmooth(isSmooth), 
		EFF_Bang_01.setSmooth(isSmooth), 
		EFF_Bang_02.setSmooth(isSmooth), 
		EFF_Bang_03.setSmooth(isSmooth), 
		EFF_Shield.setSmooth(isSmooth), 
		EFF_Shield_Effect.setSmooth(isSmooth), 
		EFF_Glow.setSmooth(isSmooth), 
		EFF_Effect_Star.setSmooth(isSmooth),
		EFF_Lighting_16.setSmooth(isSmooth),
		EFF_Bonus_Border.setSmooth(isSmooth),
		EFF_Locust_Shards.setSmooth(isSmooth);
		EFF_Warning_Red_Circle.setSmooth(isSmooth);
		EFF_Portal_Dark.setSmooth(isSmooth);
		EFF_Portal_Tornado_Dark.setSmooth(isSmooth);
		EFF_Shard_Green.setSmooth(isSmooth);
		EFF_Shard_Red.setSmooth(isSmooth);

		for(int i = 0; i < 4; i++) EFF_BlackHole[i].setSmooth(isSmooth);
	}

	Texture()
	{
		//  UI

		Load ( UI_Cursor,				"UI/Cursor.png" );
		Load ( UI_Ico,					"UI/Ico.png" );
		Load ( UI_Bar,					"UI/Bar.png");
		Load ( UI_Bar_x2,				"UI/Bar_x2.png");
		Load ( UI_HP_Line,				"UI/HPLine.png");
		Load ( UI_Energy_Line,			"UI/EnergyLine.png");
		Load ( UI_EXP_Line,				"UI/EXPLine.png");
		Load ( UI_People,				"UI/People.png");
		Load ( UI_Chance_Drop,			"UI/Chance_Drop.png");
		Load ( UI_Button_Upgrade,		"UI/Button_Upgrade.png");
		Load ( UI_Dialog,				"UI/Dialog.png");
		Load ( UI_Button_Main,			"UI/Button.png");

		Load ( UI_Text_The_Planet_Rescuer,"UI/Text_The_Planet_Rescuer.png");
		Load ( UI_Text_Help,			"UI/Text_Help.png");
		Load ( UI_Text_Play,			"UI/Text_Play.png");
		Load ( UI_Text_Options,			"UI/Text_Options.png");
		Load ( UI_Text_Exit,			"UI/Text_Exit.png");
		Load ( UI_Text_Level,			"UI/Text_Level.png");
		Load ( UI_Text_Back,			"UI/Text_Back.png");
		Load ( UI_Text_Save,			"UI/Text_Save.png");
		Load ( UI_Text_Graphics,		"UI/Text_Graphics.png");
		Load ( UI_Text_Sound,			"UI/Text_Sound.png");
		Load ( UI_Text_Cancel,			"UI/Text_Cancel.png");
		Load ( UI_Text_Resume,			"UI/Text_Resume.png");
		Load ( UI_Text_Language_RU,		"UI/Text_Language_RU.png");
		Load ( UI_Text_Language_EN,		"UI/Text_Language_EN.png");
		Load ( UI_Locked,				"Bonus/Locked.png");

		for(int i = 0; i < 10; i++) Load ( UI_Num[i], "UI/n" + to_string(i) + ".png");

		// Bonuses
		Load ( Bonus_Plato, "Bonus/Bonus_Plato.png" );

		for(int i = 0; i < 3; i++)
		{
			const int c = i+1;

			Load ( Bonus_HP[i],						"Bonus/Bonus_HP"+to_string(c)+".png" );
			Load ( Bonus_Energy[i],					"Bonus/Bonus_Energy"+to_string(c)+".png" );
			Load ( Bonus_Power[i],					"Bonus/Bonus_Power"+to_string(c)+".png" );
			Load ( Bonus_Shock[i],					"Bonus/Bonus_Shock"+to_string(c)+".png" );
			Load ( Bonus_Experience[i],				"Bonus/Bonus_Experience"+to_string(c)+".png" );
			Load ( Bonus_Multiple[i],				"Bonus/Bonus_Multiple"+to_string(c)+".png" );
			Load ( Bonus_Fragment_Explosion[i],		"Bonus/Bonus_Fragment_Explosion"+to_string(c)+".png" );
			Load ( Bonus_Slow[i],					"Bonus/Bonus_Slow"+to_string(c)+".png" );
			Load ( Bonus_Shield[i],					"Bonus/Bonus_Shield"+to_string(c)+".png" );
			Load ( Bonus_Splash_Ricochet[i],		"Bonus/Bonus_Splash_Ricochet"+to_string(c)+".png");
			Load ( Bonus_Signal_SOS[i],				"Bonus/Bonus_Signal_SOS"+to_string(c)+".png");
			Load ( Bonus_Plasm_Attack[i],			"Bonus/Bonus_Plasm_Attack"+to_string(c)+".png");
			Load ( Bonus_Mirror_Tank[i],			"Bonus/Bonus_Mirror_Tank"+to_string(c)+".png");
			Load ( Bonus_Turret_Defender[i],		"Bonus/Bonus_Turret_Defender"+to_string(c)+".png");
			Load ( Bonus_Black_Hole[i],				"Bonus/Bonus_Black_Hole"+to_string(c)+".png");
		}

		Load ( Defender_Turret,				"Tank/Defender_Turret.png");
		Load ( Defender_Wheel,				"Tank/Defender_Wheel.png");

		// Tank

		Load ( Tank_Wheel,					"Tank/Wheel.png" );
		Load ( Tank_Turret,					"Tank/Turret.png");
		Load ( Tank_Radius,					"Tank/Radius.png");
		Load ( Turret_Installer,			"Tank/Turret_Installer.png");

		for(int i = 0; i < 2; i++) Load ( SOS[i], "Tank/Sos_0"+to_string(i+1)+".png");

		for(int i = 0; i < 66; i++)
		{
			Load ( Earth[i], "Tank/Earth/"+to_string(i)+".png");
		}

		// BackGround

		for(int i = 0; i < 20; i++)
		{
			Load ( BG_Galaxy[i], "BackGround/Galaxy" + to_string(i+1) + ".png");
		}

		for(int i = 0; i < 10; i++)
		{
			Load ( BG_Star[i], "BackGround/star" + to_string(i+1) + ".png");
		}

		Load(Universe1,			"BackGround/Universe1.png");
		Load(Universe2,			"BackGround/Universe2.png");

		// Enemy

		for(int i = 0; i < 25; i++) 
		{
			Load ( Enemy[i], "Enemy/Enemy_" + to_string(i+1) + ".png");
		}

		for(int i = 0; i < 7; i++) Load ( Asteroid[i],		"Enemy/Asteroid_"+to_string(i+1)+".png");
		for(int i = 0; i < 6; i++) Load ( UFO[i],			"Enemy/UFO_0"+to_string(i+1)+".png");
		for(int i = 0; i < 5; i++) 
		{
			Load ( Transporter[i],		"Enemy/Transporter_"+to_string(i+1)+".png");
			Load ( Kamikadze[i],		"Enemy/Kamikadze_"+to_string(i+1)+".png");
		}

		for(int i = 0; i < 5; i++) Load (Boss_03[i], "Enemy/Boss_03_" + to_string(i+1) + ".png");
		// Missle 
		for(int i = 0; i < 17; i++) Load(MissleT[i], "Missle/Missle_" + to_string(i+1) + ".png");
		// Effects
		for(int i = 0; i < 4; i++) Load( EFF_BlackHole[i], "Effects/BlackHole" + to_string(i+1) + ".png");

		Load ( EFF_Bonus_Border,		"Effects/Bonus_Border.png");
		Load ( EFF_Flare,				"Effects/Flare.png");
		Load ( EFF_Effect_Star,			"UI/Effect_Star.png");
		Load ( EFF_FireFlash,			"Effects/FireFlash.png");
		Load ( EFF_Bang_01,				"Effects/Bang_01.png");
		Load ( EFF_Bang_02,				"Effects/Bang_02.png");
		Load ( EFF_Bang_03,				"Effects/Bang_03.png");
		Load ( EFF_Shield,				"Effects/Shield.png");
		Load ( EFF_Shield_Effect,		"Effects/Shield_Effect.png");
		Load ( EFF_Shock_01,			"Effects/Shock_01.png");
		Load ( EFF_Glow,				"Effects/GlowEnable.png");
		Load ( EFF_Turbo,				"Effects/Turbo.png");
		Load ( EFF_Turbo_Boss,			"Effects/TurboBoss03.png");
		Load ( EFF_Warning_Red_Circle,	"Effects/WarningRedCircle.png");
		Load ( EFF_Portal_Dark,			"Effects/PortalDark.png");
		Load ( EFF_Portal_Tornado_Dark, "Effects/PortalTornadoDark.png");
		Load ( EFF_Shard_Green,			"Effects/Shard_Green.png");
		Load ( EFF_Shard_Red,			"Effects/Shard_Red.png");
	}

	~Texture(void){}
};