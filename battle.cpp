#pragma once

#include <string>
#include <unordered_map>
#include <format>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <thread>
#include <cmath>
#include <algorithm>

#include "entity.hpp"
#include "Attack-Dodge.hpp"
#include "screen.hpp"

inline int BattleStart(player& hero, monster enemy)
{
	bool godmode = false;
	CsrMoveTo(9, 23);
	std::cout << "A " << enemy.m_Name << " appears!";
	betterGetch();
	std::string input;
	bool herogo = false;
	int enemyMaxHp = enemy.m_HP;
	if (hero.m_Speed > enemy.m_Speed)
	{
		herogo = true;
	}
	do
	{
		CsrMoveTo(9, 23);
		std::cout << enemy.m_Name << " HP: " << enemy.m_HP << " / " << enemyMaxHp << "       ";
		if (herogo == true)
		{

			printDesc3("What will you do now? ", 1);

			std::cin >> input;
			transform(input.begin(), input.end(), input.begin(), ::tolower);
			if (input == "attack")
			{
				if (godmode) { enemy.m_HP = 0; break; }
				int swipe = Attack(enemy.m_Hitbar, enemy.m_Frame);

				if (swipe == 2)
				{
					enemy.m_HP = enemy.m_HP - hero.m_ATK;
					printInfo(hero);
				}
				else if (swipe == 3)
				{
					enemy.m_HP = (enemy.m_HP - round(hero.m_ATK * (hero.m_CritMulti / 100.00)));
					printInfo(hero);
				}
				else
				{
					printDesc2("You missed! ", 1);
				}
				herogo = false;
			}
			else if (input == "heal")
			{
				bool healcheck = heal(hero);
				if (healcheck == true)
				{
					herogo = false;
				}
			}
			else if (input == "hp" || input == "check hp")
			{
				CsrMoveTo(descPos2[0], descPos2[2]);
				std::cout << hero.m_HP << std::endl;
				usrInput();
			}
			else if (input == "run")
			{
				int esc = roll(0, 100);
				if (esc < enemy.m_EscPercent)
				{
					printDesc2("Escaped! ", 1);
					printInfo(hero);
					CsrMoveTo(9, 23);
					std::cout << "                             ";
					return 3;
				}
				else
				{
					printDesc2("Miss! ", 1);
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}
				herogo = false;

			}
			else
			{
				printDesc2("Invalid Entry ", 1);
			}


		}
		else
		{
			bool jump = Dodge(enemy.m_Window);
			if (jump == false)
			{
				hero.m_HP = hero.m_HP - enemy.m_ATK + round(hero.m_Defense / 8);
				printInfo(hero);
			}
			herogo = true;
		}
		if (hero.m_HP <= 0)
		{
			printDesc2("You died! ", 1);
			CsrMoveTo(9, 23);
			std::cout << "                             ";
			return 1;
			break;
		}
		else if (enemy.m_HP <= 0)
		{
			printDesc2("Enemy Slaughtered! ", 1);
			CsrMoveTo(9, 23);
			std::cout << "                             ";
			return 2;
			break;
		}
	} while (true);
};


