#pragma once

#include "ASCII-Display-Manager/ASCII/Cursor.h"
#include "ASCII-Display-Manager/ASCII/TextEffects.h"
#include "screen.h"
#include <conio.h>
#include "battle.cpp"

int main()
{
	initializeScreen();

	string randomvar;

	refreshScreen();
	printInfo();


	int xcord = 0;
	int ycord = 0;
	int zcord = 0;
	int prevx, prevy, prevz = 0;

	std::vector<std::string> itemobject;
	std::vector<item> items;
	std::vector<item> inventory;
	std::ifstream itemfile("items.txt");


	if (itemfile.is_open())
	{
		std::string line;

		while (std::getline(itemfile, line))
		{
			if (line == "" || line[0] == '$')
			{
				continue;
			}
			else if (line[0] == '*')
			{
				itemobject.push_back(line.substr(1, line.size() - 1));
				items.push_back(swordupgrade(itemobject[0], itemobject[1], itemobject[2], itemobject[3], itemobject[4]));
				itemobject.clear();
			}
			else if (line[0] == '^')
			{
				itemobject.push_back(line.substr(1, line.size() - 1));
				items.push_back(armourupgrade(itemobject[0], itemobject[1], itemobject[2], itemobject[3], itemobject[4]));
				itemobject.clear();
			}
			else if (line[0] == '%')
			{
				itemobject.push_back(line.substr(1, line.size() - 1));
				items.push_back(quest(itemobject[0], itemobject[1], itemobject[2], itemobject[3], itemobject[4]));
				itemobject.clear();
			}
			else
			{
				itemobject.push_back(line);
			}
		}
	}
	else
	{
		printDesc("Error, no item data found!",1);
		return 734;

	}


	std::vector<std::string> roomobject;
	std::vector<room> rooms;
	std::ifstream roomfile("rooms.txt");



	if (roomfile.is_open())
	{
		std::string line;
		while (std::getline(roomfile, line))
		{
			if (line == "" || line[0] == '$')
			{
				continue;
			}
			else if (line[0] == '*')
			{
				roomobject.push_back(line.substr(1, line.size() - 1));
				rooms.push_back(room(roomobject[0], roomobject[1], roomobject[2], roomobject[3], roomobject[4], roomobject[5], roomobject[6], roomobject[7], roomobject[8], roomobject[9]));
				roomobject.clear();
			}
			else
			{
				roomobject.push_back(line);
			}
		}
	}
	else
	{
		printDesc("Error, no room data found!",1);
		return 980;
	}


	printDesc("Welcome Adventurer! Would you like to be a Fighter, Paladin, or Rouge?\n",1);
	std::string input;
	player hero;
	while (true)
	{
		refreshInput();
		usrInput();
		
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		//starting sword damage and crit multiplier is always 3 and 50
		if (input == "paladin")
		{
			printDesc("What should we call you?\n",1);
			std::getline(std::cin, input);
			hero.SetStats(25, 30, 15, 25, 10, 10, 50, 1, 25, input, "Paladin");
			break;

		}
		else if (input == "rouge")
		{
			printDesc("What should we call you?\n",1);
			std::getline(std::cin, input);
			hero.SetStats(15, 3, 15, 10, 25, 25, 50, 1, 15, input, "Rouge");
			break;

		}
		else if (input == "fighter")
		{
			printDesc("What should we call you?\n",1);
			std::getline(std::cin, input);
			hero.SetStats(20, 3, 20, 20, 20, 15, 50, 1, 20, input, "Fighter");
			break;

		}
		else
		{
			cout << "\a";
			//printDesc("Invalid Entry\n",1);
		}
	}


	do{
		int loadedroomid = room::CordLookup(rooms, xcord, ycord, zcord);
		if (loadedroomid == -1)
		{
			printDesc("You can't go that way\n",1);
			xcord = prevx; ycord = prevy; zcord = prevz;
		}
		else
		{

			prevx = xcord; prevy = ycord; prevz = zcord;
		}
		std::cout << rooms[loadedroomid].m_Title << std::endl << "What will you do?\n";
		std::getline(std::cin, input);
		if (input == "")
		{
			printDesc("What's that?\n", 1);
		}
		else if (input == "go north" || (input == "north" || input == "n"))
		{
			++ycord;
		}
		else if (input == "go south" || (input == "south" || input == "s"))
		{
			--ycord;

		}
		else if (input == "go east" || (input == "east" || input == "e"))
		{
			++xcord;
		}
		else if (input == "go west" || (input == "west" || input == "w"))
		{
			--xcord;
		}
		else if (input == "go down" || (input == "down" || input == "d"))
		{
			--zcord;
		}
		else if (input == "go up" || (input == "up" || input == "u"))
		{
			++zcord;
		}
		else if (input == "heal" || (input == "use potion" || input == "use health potion"))
		{
			heal(hero);
		}
		else if (input.substr(0, 3) == "get" || (input.substr(0, 4) == "take" || input.substr(0, 6) == "pickup"))
		{
			if (rooms[loadedroomid].m_ItemID.size() == 0)
			{
				printDesc("No such item here. This room looks empty.", 1);
			}
			else
			{
				size_t tempt = input.find_first_of(" ");
				std::string temp = input.substr(tempt + 1, input.size() - tempt);
				int i = 0;
				while (i < rooms[loadedroomid].m_ItemID.size())
				{
					int itemid = item::GetItem(items, rooms[loadedroomid].m_ItemID[i]);
					if (itemid != -1)
					{
						std::string lowername = items[itemid].m_name;
						transform(lowername.begin(), lowername.end(), lowername.begin(), ::tolower);
						if (lowername == temp)
						{
							inventory.push_back(items[itemid]);
							std::cout << "Got " << items[itemid].m_name << std::endl;
							rooms[loadedroomid].m_ItemID.erase(rooms[loadedroomid].m_ItemID.begin() + i);
						}
						else
						{
							printDesc("No such item here", 1);
						}
					}
					else
					{
						printDesc("No such item here", 1);
					}
					++i;
				}
			}

		}
		else
		{
			std::cout << rooms[loadedroomid].m_ConstDescr << " " << rooms[loadedroomid].m_UnclearedDescr << std::endl;
		}


	} while (true);
	BattleStart(hero, monster::GetZombie());
	BattleStart(hero, monster::GetRat());
	return 0;
}