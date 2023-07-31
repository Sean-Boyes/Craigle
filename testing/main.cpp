#pragma once

#include "screen.h"
#include "battle.cpp"

int main()
{
	initializeScreen();
	refreshScreen();
	string tmp; //temp temp temp

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
			if (line == "" || line[0] == '#')
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
				items.push_back(quest(itemobject[0], itemobject[1], itemobject[2], itemobject[3]));
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
		std::cout << "Error, no item data found!";
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
			if (line == "" || line[0] == '#')
			{
				continue;
			}
			else if (line[0] == '*')
			{
				roomobject.push_back(line.substr(1, line.size() - 1));
				rooms.push_back(room(roomobject[0], roomobject[1], roomobject[2], roomobject[3], roomobject[4], roomobject[5], roomobject[6], roomobject[7], roomobject[8], roomobject[9], roomobject[10], roomobject[11]));
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
		std::cout << "Error, no room data found!";
		return 980;
	}


	printDesc("\x1b[1;37mWelcome Adventurer! Would you like to be a Fighter, Paladin, or Rouge?",1);
	std::string input;
	player hero;
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		//starting sword damage and crit multiplier is always 3 and 50
		if (input == "paladin")
		{
			printDesc("What should we call you?",1);
			std::getline(std::cin, input);
			hero.SetStats(25, 30, 15, 25, 10, 10, 50, 1, 25, input, "Paladin");
			printInfo(hero);
			break;

		}
		else if (input == "rouge")
		{
			printDesc("What should we call you?",1);
			std::getline(std::cin, input);
			hero.SetStats(15, 3, 15, 10, 25, 25, 50, 1, 15, input, "Rouge");
			printInfo(hero);
			break;

		}
		else if (input == "fighter")
		{
			printDesc("What should we call you?",1);
			std::getline(std::cin, input);
			hero.SetStats(20, 3, 20, 20, 20, 15, 50, 1, 20, input, "Fighter");
			printInfo(hero);
			break;

		}
		else
		{
			cout << "\a";
			//printDesc("Invalid Entry",1);
			// move types lower
		}
	}


	bool death = false;
	int prevloadedroomid;
	do{
		int loadedroomid = room::CordLookup(rooms, xcord, ycord, zcord);
		if (loadedroomid == -1)
		{
			printDesc("You can't go that way",1);
			xcord = prevx; ycord = prevy; zcord = prevz;
			loadedroomid = prevloadedroomid;
		}
		if (rooms[loadedroomid].m_properties[12] == true)
		{
			printDesc("? ? ?", 1);
		}
		else
		{
			refreshTitle(rooms[loadedroomid].m_Title);
		}

		bool battlecheck = false;
		for (int& monster : rooms[loadedroomid].m_MonsterID)
		{
			battlecheck = true;
			int battle = BattleStart(hero, monster::GetMonster(monster));
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
		}
		if (death == true)
		{
			break;
		}

		if (battlecheck == true)
		{
			std::getline(std::cin, input);
		}

		rooms[loadedroomid].m_MonsterID.clear();


		tmp += "What will you do now?";
		printDesc(tmp, 1);
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "")
		{
			printDesc("What's that?",1);
		}
		else if (input == "go north" || (input == "north" || input == "n"))
		{
			if (rooms[loadedroomid].m_properties[0] == true)
			{
				printDesc("You can't go that way",1);
			}
			else
			{
				++ycord;
			}
		}
		else if (input == "go south" || (input == "south" || input == "s"))
		{
			if (rooms[loadedroomid].m_properties[1] == true)
			{
				printDesc("You can't go that way",1);
			}
			else
			{
				--ycord;
			}
		}
		else if (input == "go east" || (input == "east" || input == "e"))
		{
			if (rooms[loadedroomid].m_properties[2] == true)
			{
				printDesc("You can't go that way",1);
			}
			else
			{
				++xcord;
			}
		}
		else if (input == "go west" || (input == "west" || input == "w"))
		{
			if (rooms[loadedroomid].m_properties[3] == true)
			{
				printDesc("You can't go that way",1);
			}
			else
			{
				--xcord;
			}
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
							printDesc("Got " + items[itemid].m_name, 1);
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
		else if (input == "look")
		{
			tmp = "";
			if (rooms[loadedroomid].m_properties[12] == true)
			{
				tmp += "It's too dark to see anything";
			}
			else
			{
				tmp += rooms[loadedroomid].m_ConstDescr;
				// move to predest area for extra text 5 lines
				//// temp fix band-aid
				//cout << endl;
				//CsrMove('r', 10);
				if (rooms[loadedroomid].m_ItemID.size() == 0)
				{
					tmp += (rooms[loadedroomid].m_PostitemDescr + " ");
				}
				else
				{
					tmp += (rooms[loadedroomid].m_PreitemDescr + " ");
				}
				if (rooms[loadedroomid].m_roomevent.size() == 0)
				{
					tmp += (rooms[loadedroomid].m_PosteventDescr + " ");
				}
				else
				{
					tmp += (rooms[loadedroomid].m_PreeventDescr + " ");
				}
			}
			printDesc(tmp, 1);
		}
		else if (input.substr(0, 3) == "use")
		{
			input = input.substr(4, input.size() - 3);
			int i = 0;
			bool itemcheck = false;
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
							rooms[loadedroomid].m_properties[stoi(rooms[loadedroomid].m_roomevent[i + 1])] = !rooms[loadedroomid].m_properties[stoi(rooms[loadedroomid].m_roomevent[i + 1])];
							printDesc(rooms[loadedroomid].m_roomevent[i + 2], 1);
							rooms[loadedroomid].m_roomevent.erase(rooms[loadedroomid].m_roomevent.begin() + i + 2);
							rooms[loadedroomid].m_roomevent.erase(rooms[loadedroomid].m_roomevent.begin() + i + 1);
							rooms[loadedroomid].m_roomevent.erase(rooms[loadedroomid].m_roomevent.begin() + i);
							break;
						}
					}
					i = i + 3;
				}
			}
			else
			{
				printDesc("You have no such thing",1);
			}

		}
		else
		{
			cout << "\a";
			printDesc("Invalid Entry",1);
		}

		prevx = xcord; prevy = ycord; prevz = zcord;
		prevloadedroomid = loadedroomid;

	} while (true);
	BattleStart(hero, monster::GetZombie());
	BattleStart(hero, monster::GetRat());
	return 0;
}