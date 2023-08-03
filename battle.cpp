#pragma once


#include "Attack-Dodge.h"

inline int BattleStart(player& hero, monster enemy)
{
	std::string input;
	std::cout << "A " << enemy.m_Name << " appears!\n";
	bool herogo = false;
	if (hero.m_Speed > enemy.m_Speed)
	{
		herogo = true;
	}
	do
	{
		if (herogo == true)
		{
			std::cout << "What will you do now?\n";

			std::cin >> input;
			transform(input.begin(), input.end(), input.begin(), ::tolower);
				if (input == "attack")
				{
					int swipe = Attack(enemy.m_Hitbar, enemy.m_Frame);

					if (swipe == 2)
					{
						enemy.m_HP = enemy.m_HP - hero.m_ATK;
					}
					else if (swipe == 3)
					{
						enemy.m_HP = (enemy.m_HP - round(hero.m_ATK * (hero.m_CritMulti / 100.00)));
					}
					else
					{
						std::cout << "You missed!\n";
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
					std::cout << hero.m_HP << std::endl;
				}
				else if (input == "run")
				{
					int esc = roll(0, 100);
					if (esc < enemy.m_EscPercent)
					{
						std::cout << "Escaped!\n";
						return 3;
					}
					else
					{
						std::cout << "Miss!\n";
					}
					herogo = false;

				}
				else
				{
					std::cout << "Invalid Entry\n";
				}


		}
		else
		{
			bool jump = Dodge(enemy.m_Window);
			if (jump == false)
			{
				hero.m_HP = hero.m_HP - enemy.m_ATK + round(hero.m_Defense/8);
			}
			herogo = true;
		}
		if (hero.m_HP <= 0)
		{
			std::cout << "You died!\n";
			return 1;
			break;
		}
		else if (enemy.m_HP <= 0)
		{
			std::cout << "Enemy Slaughtered!\n";
			return 2;
			break;
		}
	} while (true);
}


