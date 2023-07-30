#pragma once

#include <vector>
#include <conio.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <thread>
#include <cmath>
#include <algorithm>

#include "map.h"

class entity
{
public:
	int m_HP, m_ATK, m_Defense, m_Speed, m_EID;
	std::string m_Name;

	virtual void SetStats() {};

};
class monster : public entity
{
public:
	bool m_IneffectiveAttack; //if true, player *always* will do 1 damage
	int m_EscPercent, m_Frame, m_Window;
	std::string m_Hitbar;

	virtual void SetStats(int HP, int ATK, int Defense, int Speed, int EscPercent, std::string Hitbar, std::string Name)
	{
		m_HP = HP;
		m_ATK = ATK;
		m_Defense = Defense;
		m_Speed = Speed;
		m_Frame = 85 - (Defense * 2);
		m_Window = 300 - (Speed * 10);
		m_EscPercent = EscPercent;
		m_Hitbar = Hitbar;
		m_Name = Name;
	};

	static monster GetMonster(int id)
	{
		if (id == 1)
		{
			return GetZombie();

		}
		else if (id == 2)
		{
			return GetRat();

		}
		else if (id == 3)
		{
			return GetSkeleton();

		}
		else if (id == 4)
		{
			return GetCultMember();

		}
		else if (id == 5)
		{
			return GetDragon();

		}
		else if (id == 6)
		{
			return GetLesserDemon();

		}
		else if (id == 7)
		{
			return GetGreaterDemon();

		}
		else if (id == 8)
		{
			return GetBear();

		}
		else if (id == 9)
		{
			return GetSnake();

		}
	}

	static monster GetZombie()
	{
		monster Zombie;
		Zombie.SetStats(15, 6, 15, 15, 40, "..ooo000ooo..", "Zombie");
		return Zombie;
	}

	static monster GetRat()
	{
		monster Rat;
		Rat.SetStats(7, 9, 15, 50, 0, ".....000.....", "Rat");
		return Rat;
	}

	static monster GetSkeleton()
	{
		monster Skeleton;
		Skeleton.SetStats(10, 10, 18, 21, 50, "..o0oo.oo0o..", "Skeleton");
		return Skeleton;
	}

	static monster GetCultMember()
	{
		monster CultMember;
		CultMember.SetStats(15, 8, 20, 20, 30, "...oo0o0oo...", "Cult Member");
		return CultMember;
	}

	static monster GetDragon()
	{
		monster Dragon;
		Dragon.SetStats(75, 20, 25, 15, 100, "....oo0oo....", "Dragon");
		return Dragon;
	}

	static monster GetLesserDemon()
	{
		monster LesserDemon;
		LesserDemon.SetStats(20, 9, 25, 15, 20, "..ooo000ooo..", "Lesser Demon");
		return LesserDemon;
	}

	static monster GetGreaterDemon()
	{
		monster GreaterDemon;
		GreaterDemon.SetStats(25, 14, 30, 19, 5, "...oo000oo...", "Greater Demon");
		return GreaterDemon;
	}

	static monster GetBear()
	{
		monster Bear;
		Bear.SetStats(30, 8, 12, 12, 50, "..ooo000ooo..", "Bear");
		return Bear;
	}

	static monster GetSnake()
	{
		monster Snake;
		Snake.SetStats(10, 6, 12, 21, 50, "...o0o0o0o...", "Snake");
		return Snake;
	}
};
class player : public entity
{
public:
	int m_Power, m_Stealth, m_CritMulti, m_HealPot, m_MaxHP; 
	std::string m_Class;
	// all stats out of 20. Power acts as weapon multiplier (x/10), Defense subtracts from incoming hits (x/8),
	// Speed determines dodge window and initiative, and Stealth determines ease of escape and likelyhood of random encounters.

	virtual void SetStats(int HP, int DMG, int Power, int Defense, int Speed, int Stealth, int CritMulti, int HealPot, int MaxHP, std::string Name, std::string Class)
	{
		m_HP = HP;
		m_ATK = DMG * (Power / 10);
		m_Power = Power;
		m_Defense = Defense;
		m_Speed = Speed;
		m_Stealth = Stealth;
		m_CritMulti = CritMulti;
		m_HealPot = HealPot;
		m_Name = Name;
		m_MaxHP = MaxHP;
		m_Class = Class;
	};
};

