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

#include "tut.hpp"
#include "battle.hpp"
#include "entity.hpp"
#include "map.hpp"
#include "item.hpp"
#include "screen.hpp"

int main()
{
	initializeScreen();
	usrInput();

	std::string input;
	printDesc("Would you like to play the tutorial? Yes/No ",1);
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "yes" || input == "y")
		{
			tutorial();
			break;
		}
		else if (input == "no" || input == "n")
		{
			break;
		}
		else
		{
			printDesc2("Invalid Entry ",1);
		}
	}
	 
	int xcord = 0;
	int ycord = 0;
	int zcord = 0;
	int prevx = 0;
	int prevy = 0;
	int prevz = 0;

	int endx = -3;
	int endy = 1;
	int endz = 0;

	std::string tmpDesc = "";

	std::vector<std::string> itemobject;
	std::vector<item> items;
	std::vector<item> inventory;
	std::ifstream itemfile("items.txt");

	// Load Item File(s)
	if (itemfile.is_open())
	{
		std::string line;

		while (std::getline(itemfile, line))
		{
			if (line == "" || line[0] == '#')
			{
				continue;
			}
			else if (line[0] == '*')
			{
				itemobject.push_back(line.substr(1, line.size() - 1));
				items.push_back(item(itemobject[0], itemobject[1], itemobject[2], itemobject[3], itemobject[4], itemobject[5], 1));
				itemobject.clear();
			}
			else if (line[0] == '^')
			{
				itemobject.push_back(line.substr(1, line.size() - 1));
				items.push_back(item(itemobject[0], itemobject[1], itemobject[2], itemobject[3], itemobject[4], itemobject[5], 2));
				itemobject.clear();
			}
			else if (line[0] == '%')
			{
				itemobject.push_back(line.substr(1, line.size() - 1));
				items.push_back(item(itemobject[0], itemobject[1], itemobject[2], itemobject[3], itemobject[4], itemobject[5], 3));
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
		printDesc2("Error, no item data found! ", 1);
		return 734;

	}


	std::vector<std::string> roomobject;
	std::vector<room> rooms;
	std::ifstream roomfile("rooms.txt");


	// Load Room File(s)
	if (roomfile.is_open())
	{
		std::string line;
		while (std::getline(roomfile, line))
		{
			if (line == "" || line[0] == '#')
			{
				continue;
			}
			else if (line[0] == '*')
			{
				roomobject.push_back(line.substr(1, line.size() - 1));
				rooms.push_back(room(roomobject[0], roomobject[1], roomobject[2], roomobject[3], roomobject[4], roomobject[5], roomobject[6], roomobject[7], roomobject[8], roomobject[9], roomobject[10], roomobject[11], roomobject[12]));
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
		std::cout << "\a"; // error sound
		printDesc2("Error, no room data found!", 1);
		return 980;
	}

	// Class Selection
	printDesc("\x1b[1;37mWelcome Adventurer! Would you like to be a Fighter, Paladin, or Rogue? ", 1);
	player hero;
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "paladin")
		{
			printDesc2("What should we call you? ", 1);
			std::getline(std::cin, input);
			hero.SetStats(25, 0, 15, 25, 10, 10, 0, 1, 25, input, "Paladin", 0, false);
			printInfo(hero);
			break;

		}
		else if (input == "rogue")
		{
			printDesc2("What should we call you? ", 1);
			std::getline(std::cin, input);
			hero.SetStats(15, 0, 15, 10, 25, 25, 0, 1, 15, input, "Rouge", 0, false);
			printInfo(hero);
			break;

		}
		else if (input == "fighter")
		{
			printDesc2("What should we call you? ", 1);
			std::getline(std::cin, input);
			hero.SetStats(20, 0, 20, 20, 20, 15, 0, 1, 20, input, "Fighter", 0, false);
			printInfo(hero);
			break;

		}
		else
		{
			printDesc2("Invalid Entry ", 1);
		}
	}

	// Introduction
	bool introskip = true;
	if (!introskip)
	{
		printDesc("Trudging through the caliginous forest, the adventurer pushes forward. " + hero.m_Name + " the " + hero.m_Class + " is in search of mythical anceint riches said to reside in this forest. You have been hunting this treasure for a many fortnight by now, yet you feel you are near the end of their journey.\n\n   \x1b[90m{\x1b[0m    The forest is quiet and peaceful, but not in a comforting way. Every so often you swear you hear a quiet rustle nearby, yet nothing ever comes of it. Through the foliage the adventurer presses on. Suddenly, with an uncareful step you slip on a mud covered hillside! Down the hill you tumble, until with a crash everything goes black.", 2);
		printDesc2("You awake with a hurting head and a few more bruises than before, and find yourself in the bottom of giant cavern, with seemingly no easy way back up.Upon looking up towards the top of the cavern, you see not the forest you were akin to but what seems to be a purple ceiling of magic.Whatever place you have found yourself in, it is clear you need to find yourself at the exit sooner than later...", 2);
		betterGetch();
	}

	bool death = false;
	bool movecheck = true;
	bool runchck = false;
	int prevloadedroomid;

	// Main loop
	do{
		if (xcord == endx && (ycord == endy && zcord == endz))
		{
			break;
		}
		int loadedroomid = room::CordLookup(rooms, xcord, ycord, zcord);

		// Room does not exist
		if (loadedroomid == -1)
		{
			printDesc2("You can't go that way ", 1);
			xcord = prevx; ycord = prevy; zcord = prevz;
			loadedroomid = prevloadedroomid;
		}
		lookAround(rooms, xcord, ycord, zcord);
		printMap();

		tmpDesc = "";

		// Room is too dark
		if (rooms[loadedroomid].m_properties[6] == true)
		{
			printInfo(hero);
			tmpDesc += "It's too dark to see anything ";
			refreshTitle("? ? ?");
		}
		else
		{
			printInfo(hero);
			lookAround(rooms, xcord, ycord, zcord);
			refreshTitle(rooms[loadedroomid].m_Title);

			if (rooms[loadedroomid].m_properties[6] == true) // not sure if this is needed
			{
				tmpDesc += "It's too dark to see anything ";
			}
			else
			{
				tmpDesc += rooms[loadedroomid].m_ConstDescr;
				if (rooms[loadedroomid].m_ItemID.size() == 0)
				{
					tmpDesc += rooms[loadedroomid].m_PostitemDescr;
				}
				else
				{
					tmpDesc += rooms[loadedroomid].m_PreitemDescr;
				}
				if (rooms[loadedroomid].m_roomevent.size() == 0)
				{
					tmpDesc += rooms[loadedroomid].m_PosteventDescr;
				}
				else
				{
					tmpDesc += rooms[loadedroomid].m_PreeventDescr;
				}
			}

			// multithread opening text
			std::thread t1(printDesc, tmpDesc, 1);
			//std::this_thread::sleep_for(std::chrono::milliseconds(500));
			_getch();
			CsrMoveTo(48, 35);
			std::cout << "                              ";
			interupt = true;
			//std::this_thread::sleep_for(std::chrono::milliseconds(10));
			t1.join();
			interupt = false;

		}
		// end multithread opening text

		//if (loadedroomid == -1)
		//{
		//	printDesc2("You can't go that way ", 1);
		//	xcord = prevx; ycord = prevy; zcord = prevz;
		//	loadedroomid = prevloadedroomid;
		//}
		if (rooms[loadedroomid].m_properties[6] == true) // again not sure if needed, legacy code maybe
		{
			refreshTitle("? ? ?");
			printDesc("It's too dark to see anything ", 1);
		}
		else
		{
			refreshTitle(rooms[loadedroomid].m_Title);
		}

		bool battlecheck = false;
		


		if (runchck != true && movecheck == true)
		{
			int counter = 0;
			while (counter < rooms[loadedroomid].m_RandEnc.size())
			{
				int percent = rooms[loadedroomid].m_RandEnc[counter];
				int mid = rooms[loadedroomid].m_RandEnc[counter + 1];
				int chance2 = roll(1, 100);
				if (percent < chance2)
				{
					battlecheck = true;
					runchck = true;
					int battle = BattleStart(hero, monster::GetMonster(mid, hero));
					if (battle == 1)
					{
						death = true;
						break;
					}
					if (battle == 3)
					{
						xcord = prevx; ycord = prevy; zcord = prevz;
						loadedroomid = prevloadedroomid;
						refreshTitle(rooms[loadedroomid].m_Title);
						break;
					}
					else
					{
						++hero.m_Kills;
						printInfo(hero);
					}
				}
				counter = counter + 2;
			}
			for (int& monster : rooms[loadedroomid].m_MonsterID)
			{
				battlecheck = true;
				runchck = true;
				int battle = BattleStart(hero, monster::GetMonster(monster, hero));
				if (battle == 1)
				{
					death = true;
					break;
				}
				if (battle == 3)
				{
					xcord = prevx; ycord = prevy; zcord = prevz;
					loadedroomid = prevloadedroomid;
					refreshTitle(rooms[loadedroomid].m_Title);
					printInfo(hero);
					lookAround(rooms,xcord,ycord,zcord); // probably not needed here
					printMap(); // probably not needed here
					break;
				}
				else
				{
					++hero.m_Kills;
					printInfo(hero);
				}
				printInfo(hero);
				lookAround(rooms, xcord, ycord, zcord);
				printMap();
			}
		}
		if (death == true)
		{
			break;
		}

		if (battlecheck == true)
		{
			std::getline(std::cin, input);
		}
		runchck = false;

		rooms[loadedroomid].m_MonsterID.clear();
		prevx = xcord; prevy = ycord; prevz = zcord;
		prevloadedroomid = loadedroomid;
		lookAround(rooms, xcord, ycord, zcord); // maybe not needed here
		printMap(); // maybe not needed here

		movecheck = false;

		printDesc3("What will you do now? ", 1);
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "")
		{
			printDesc2("What's that? ", 1);
		}
		else if (input == "go north" || (input == "north" || input == "n"))
		{
			if (rooms[loadedroomid].m_properties[0] == true)
			{
				printDesc2("You can't go that way ", 1);
			}
			else
			{
				++ycord;
				movecheck = true;
			}
		}
		else if (input == "go south" || (input == "south" || input == "s"))
		{
			if (rooms[loadedroomid].m_properties[1] == true)
			{
				printDesc2("You can't go that way ", 1);
			}
			else
			{
				--ycord;
				movecheck = true;
			}
		}
		else if (input == "go east" || (input == "east" || input == "e"))
		{
			if (rooms[loadedroomid].m_properties[2] == true)
			{
				printDesc2("You can't go that way ", 1);
			}
			else
			{
				++xcord;
				movecheck = true;
			}
		}
		else if (input == "go west" || (input == "west" || input == "w"))
		{
			if (rooms[loadedroomid].m_properties[3] == true)
			{
				printDesc2("You can't go that way ", 1);
			}
			else
			{
				--xcord;
				movecheck = true;
			}
		}
		else if (input == "go down" || (input == "down" || input == "d"))
		{
			--zcord;
			movecheck = true;
		}
		else if (input == "go up" || (input == "up" || input == "u"))
		{
			++zcord;
			movecheck = true;
		}
		else if (input == "heal" || (input == "use potion" || input == "use health potion"))
		{
			heal(hero);
			printInfo(hero);
		}
		else if (((input.substr(0, 3) == "get") || (input.substr(0, 4) == "grab")) || (input.substr(0, 4) == "take" || input.substr(0, 6) == "pickup"))
		{
			if (rooms[loadedroomid].m_ItemID.size() == 0)
			{
				printDesc2("No such item here. This room looks empty.", 1);
			}
			else
			{
				size_t tempt = input.find_first_of(" ");
				std::string temp = input.substr(tempt + 1, input.size() - tempt);
				int i = 0;
				bool grabcheck = false;
				while (i < rooms[loadedroomid].m_ItemID.size())
				{
					int itemid = item::GetItem(items, rooms[loadedroomid].m_ItemID[i]);
					if (itemid != -1)
					{
						std::string lowername = items[itemid].m_name;
						transform(lowername.begin(), lowername.end(), lowername.begin(), ::tolower);
						if (lowername == temp)
						{
							if (items[itemid].m_type == 1)
							{
								hero.m_ATK = items[itemid].m_assign1;
								hero.m_CritMulti = items[itemid].m_assign2;
								printInfo(hero);
							}

							inventory.push_back(items[itemid]);
							printDesc2("Got " + items[itemid].m_name, 1);
							grabcheck = true;
							rooms[loadedroomid].m_ItemID.erase(rooms[loadedroomid].m_ItemID.begin() + i);
						}
					}
					++i;
				}
				if (grabcheck == false)
				{
					printDesc2("No such item here", 1);
				}
			}

		}
		else if ((input.substr(0, 4) == "view" || input.substr(0, 7) == "look at") || (input.substr(0, 6) == "ponder" || input.substr(0, 7) == "inspect"))
		{
			if (input.substr(0, 7) == "look at")
			{
				input = input.substr(8, input.size() - 8);
			}
			else
			{
				size_t tempt = input.find_first_of(" ");
				input = input.substr(tempt + 1, input.size() - tempt);
			}
			bool itemcheck = false;
			std::string itemdesc;
			int i = 0;
			while (i < inventory.size())
			{
				std::string temps2 = inventory[i].m_name;
				transform(temps2.begin(), temps2.end(), temps2.begin(), ::tolower);

				if (input == temps2)
				{
					itemcheck = true;
					itemdesc = inventory[i].m_description;
				}
				++i;
			}
			if (itemcheck == true)
			{
				printDesc2(itemdesc, 1);
			}
			else
			{
				printDesc2("You have no such thing ", 1);
			}
		}
		else if (input == "look")
		{
			std::string tmp = "";
			if (rooms[loadedroomid].m_properties[6] == true)
			{
				tmp += "It's too dark to see anything ";
			}
			else
			{
				tmp += rooms[loadedroomid].m_ConstDescr + " ";
				if (rooms[loadedroomid].m_ItemID.size() == 0)
				{
					tmp += rooms[loadedroomid].m_PostitemDescr + " ";
				}
				else
				{
					tmp += rooms[loadedroomid].m_PreitemDescr + " ";
				}
				if (rooms[loadedroomid].m_roomevent.size() == 0)
				{
					tmp += rooms[loadedroomid].m_PosteventDescr + "\n";
				}
				else
				{
					tmp += rooms[loadedroomid].m_PreeventDescr + "\n";
				}
			}
			printDesc(tmp, 1);
		}
		else if (input.substr(0, 5) == "equip")
		{	
			if(hero.m_ArmourEquip == true)
			{
				printDesc2("Already have armour equiped ", 1);
			}
			else
			{
				input = input.substr(6, input.size() - 6);
				int itemtype, def;
				bool itemcheck = false;
				int i = 0;
				while (i < inventory.size())
				{
					std::string temps2 = inventory[i].m_name;
					transform(temps2.begin(), temps2.end(), temps2.begin(), ::tolower);

					if (input == temps2)
					{
						itemcheck = true;
						itemtype = inventory[i].m_type;
						def = inventory[i].m_assign1;
					}
					++i;
				}
				if (itemcheck == true)
				{
					if (itemtype == 2)
					{
						hero.m_ArmourEquip = true;
						hero.m_Defense = hero.m_Defense + def;
						printDesc2("Equiped! ", 1);
						printInfo(hero);
					}
					else
					{
						printDesc2("Cannot equip this ", 1);
					}
				}
				else
				{
					printDesc2("You have no such thing ", 1);
				}
			}

	    }		
		else if (input.substr(0, 7) == "unequip")
		{
		if (hero.m_ArmourEquip == false)
		{
			printDesc2("Nothing to unequip ", 1);
		}
		else
		{
			input = input.substr(8, input.size() - 8);
			int itemtype, def;
			bool itemcheck = false;
			int i = 0;
			while (i < inventory.size())
			{
				std::string temps2 = inventory[i].m_name;
				transform(temps2.begin(), temps2.end(), temps2.begin(), ::tolower);

				if (input == temps2)
				{
					itemcheck = true;
					itemtype = inventory[i].m_type;
					def = inventory[i].m_assign1;
				}
				++i;
			}
			if (itemcheck == true)
			{
				if (itemtype == 2)
				{
					hero.m_ArmourEquip = false;
					hero.m_Defense = hero.m_Defense - def;
					printDesc2("Unequiped! ", 1);
					printInfo(hero);
				}
				else
				{
					printDesc2("You are not wearing this ", 1);
				}
			}
			else
			{
				printDesc2("You have no such thing ", 1);
			}
		}

		}
		else if (input == "inventory")
		{
			std::string tmp = "";
			for (item i : inventory)
			{
				tmp += i.m_name + ", ";
			}
			if (tmp.size() != 0) tmp += "and nothing more";
			else tmp = "You have nothing";
			printDesc2(tmp, 1);
		}
		else if (input == "search")
		{
			if (rooms[loadedroomid].m_properties[6] == true)
			{
				printDesc2("It's too dark to see anything ", 1);
			}
			else if (rooms[loadedroomid].m_Search == "-")
			{
				printDesc2("There is nothing more to be seen here ", 1);
			}
			else
			{
				printDesc2(rooms[loadedroomid].m_Search, 1);
			}
		}
		else if (input.substr(0, 7) == "combine")
		{
			std::vector<std::string> itemcheck;
			input = input.substr(8, input.size() - 8);
			transform(input.begin(), input.end(), input.begin(), ::tolower);
			size_t acheck = input.find("and");
			if (acheck == std::string::npos)
			{
				printDesc2("Cannot understand entry ", 1);
			}
			else
			{
				bool item1check = false;
				bool item2check = false;
				int checkid;
				int item1place, item2place;
				std::vector<int> checkcombin;
				itemcheck.push_back(input.substr(0, acheck - 1));
				itemcheck.push_back(input.substr(acheck + 4, input.size() - acheck - 4));
				int i = 0;
				for (item it : inventory)
				{
					std::string temps2 = it.m_name;
					transform(temps2.begin(), temps2.end(), temps2.begin(), ::tolower);
					if (temps2 == itemcheck[0])
					{
						item1check = true;
						checkid = it.m_itemid;
						item1place = i;
					}
					++i;
				}
				i = 0;
				for (item it : inventory)
				{
					std::string temps2 = it.m_name;
					transform(temps2.begin(), temps2.end(), temps2.begin(), ::tolower);
					if (temps2 == itemcheck[1])
					{
						item2check = true;
						checkcombin = it.m_combinables;
						item2place = i;
					}
				}
				if (item1check == true && item2check == true)
				{
					int ii = 0;
					bool printcheck = false;
					for (int i : checkcombin)
					{
						if (i == checkid)
						{
							int resultid = inventory[item1place].m_combinies[ii];
							int counter = 0;
							int del1, del2;
							for (item it : inventory)
							{
								std::string temps = it.m_name;
								transform(temps.begin(), temps.end(), temps.begin(), ::tolower);
								if (temps == itemcheck[0])
								{
									del1 = counter;
								}
								++counter;
							}
							inventory.erase(inventory.begin() + del1);
							counter = 0;
							for (item it : inventory)
							{
								std::string temps = it.m_name;
								transform(temps.begin(), temps.end(), temps.begin(), ::tolower);
								if (temps == itemcheck[1])
								{
									del2 = counter;
								}
								++counter;
							}
							inventory.erase(inventory.begin() + del2);
							inventory.push_back(items[item::GetItem(items, resultid)]);
							if (inventory[inventory.size() - 1].m_type == 1)
							{
								hero.m_ATK = inventory[inventory.size() - 1].m_assign1;
								hero.m_CritMulti = inventory[inventory.size() - 1].m_assign2;
								printInfo(hero);

							}
							printDesc2("Made " + inventory[inventory.size() - 1].m_name, 1);
							printcheck = true;
							break;
						}
						++ii;
					}
					if (printcheck == false)
					{
						printDesc2("Cannot combines these in any meaningful way ", 1);
					}
				}
				else
				{
					printDesc2("You have no such thing ", 1);
				}
			} 
			
		}
		else if (input.substr(0, 3) == "use" && input.size() > 4)
		{
			input = input.substr(4, input.size() - 3);
			int i = 0;
			bool itemcheck = false;
			bool printcheck = false;
			int itemname;

			while (i < inventory.size())
			{
				std::string temps2 = inventory[i].m_name;
				transform(temps2.begin(), temps2.end(), temps2.begin(), ::tolower);

				if (input == temps2)
				{
					itemcheck = true;
					itemname = inventory[i].m_itemid;
				}
				++i;
			}
			if (itemcheck == true)
			{
				i = 0;
				while (i < rooms[loadedroomid].m_roomevent.size())
				{
					int ii = 0;
					std::vector<int> temp;
					std::string temps;
					while (ii < rooms[loadedroomid].m_roomevent[i].length())
					{
						if (rooms[loadedroomid].m_roomevent[i][ii] == '>')
						{
							temp.push_back(stoi(temps));
							temps.clear();
							++ii;
						}
						else
						{
							temps.push_back(rooms[loadedroomid].m_roomevent[i][ii]);
							++ii;
						}
					}
					for (int& iii : temp)
					{
						if (iii == itemname)
						{
							printcheck = true;
							std::string propcheck = rooms[loadedroomid].m_roomevent[i + 1];

							int iiii = 0;
							std::vector<int> tempv2;
							std::string temps3;
							while (iiii < rooms[loadedroomid].m_roomevent[i + 1].length())
							{
								if (rooms[loadedroomid].m_roomevent[i + 1][iiii] == '>')
								{
									tempv2.push_back(stoi(temps3));
									temps3.clear();
									++iiii;
								}
								else
								{
									temps3.push_back(rooms[loadedroomid].m_roomevent[i + 1][iiii]);
									++iiii;
								}
							}

							for (int entry : tempv2)
							{
								rooms[loadedroomid].m_properties[entry] = !rooms[loadedroomid].m_properties[entry]; // caises index out of range error me thinks
							}

							printDesc2(rooms[loadedroomid].m_roomevent[i + 2], 1);
							rooms[loadedroomid].m_roomevent.erase(rooms[loadedroomid].m_roomevent.begin() + i + 2);
							rooms[loadedroomid].m_roomevent.erase(rooms[loadedroomid].m_roomevent.begin() + i + 1);
							rooms[loadedroomid].m_roomevent.erase(rooms[loadedroomid].m_roomevent.begin() + i);
							betterGetch();
							//std::this_thread::sleep_for(std::chrono::seconds(2)); // replace later
							break;
						}
					}
					i = i + 3;
				}
				if (printcheck == false)
				{
					printDesc2("Cannot use here ", 1);
				}
			}
			else
			{
				printDesc2("You have no such thing ", 1);
			}

		}
		else
		{
			printDesc2("Cannot understand entry ", 1);
		}

	} while (true);
	if (death == true)
	{
		std::cout << "The Adventurer has fallen.\n";
	}
	return 0;
}