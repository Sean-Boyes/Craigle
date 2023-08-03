
#include "battle.cpp"

int main()
{
	int xcord = 0;
	int ycord = 0;
	int zcord = 0;
	int prevx = 0;
	int prevy = 0;
	int prevz = 0;

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
		std::cout << "Error, no room data found!";
		return 980;
	}


	std::cout << "\x1b[1;37m" << "Welcome Adventurer! Would you like to be a Fighter, Paladin, or Rogue?\n";
	std::string input;
	player hero;
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "paladin")
		{
			std::cout << "What should we call you?\n";
			std::getline(std::cin, input);
			hero.SetStats(25, 0, 15, 25, 10, 10, 0, 1, 25, input, "Paladin", 0, false);
			break;

		}
		else if (input == "rogue")
		{
			std::cout << "What should we call you?\n";
			std::getline(std::cin, input);
			hero.SetStats(15, 0, 15, 10, 25, 25, 0, 1, 15, input, "Rouge", 0, false);
			break;

		}
		else if (input == "fighter")
		{
			std::cout << "What should we call you?\n";
			std::getline(std::cin, input);
			hero.SetStats(20, 0, 20, 20, 20, 15, 0, 1, 20, input, "Fighter", 0, false);
			break;

		}
		else
		{
			std::cout << "Invalid Entry\n";
		}
	}


	bool death = false;
	int prevloadedroomid;
	do{
		int loadedroomid = room::CordLookup(rooms, xcord, ycord, zcord);
		if (loadedroomid == -1)
		{
			std::cout << "You can't go that way\n";
			xcord = prevx; ycord = prevy; zcord = prevz;
			loadedroomid = prevloadedroomid;
		}
		if (rooms[loadedroomid].m_properties[6] == true)
		{
			std::cout << "? ? ?" << std::endl;
		}
		else
		{
			std::cout << rooms[loadedroomid].m_Title << std::endl;
		}

		bool battlecheck = false;
		for (int& monster : rooms[loadedroomid].m_MonsterID)
		{
			battlecheck = true;
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
				std::cout << rooms[loadedroomid].m_Title << std::endl;
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
		prevx = xcord; prevy = ycord; prevz = zcord;
		prevloadedroomid = loadedroomid;

		std::cout << "What will you do now?\n";
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "")
		{
			std::cout << "What's that?\n";
		}
		else if (input == "go north" || (input == "north" || input == "n"))
		{
			if (rooms[loadedroomid].m_properties[0] == true)
			{
				std::cout << "You can't go that way\n";
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
				std::cout << "You can't go that way\n";
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
				std::cout << "You can't go that way\n";
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
				std::cout << "You can't go that way\n";
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
		else if (((input.substr(0, 3) == "get") || (input.substr(0, 4) == "grab")) || (input.substr(0, 4) == "take" || input.substr(0, 6) == "pickup"))
		{
			if (rooms[loadedroomid].m_ItemID.size() == 0)
			{
				std::cout << "No such item here. This room looks empty." << std::endl;
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

							}

							inventory.push_back(items[itemid]);
							std::cout << "Got " << items[itemid].m_name << std::endl;
							grabcheck = true;
							rooms[loadedroomid].m_ItemID.erase(rooms[loadedroomid].m_ItemID.begin() + i);
						}
					}
					++i;
				}
				if (grabcheck == false)
				{
					std::cout << "No such item here" << std::endl;
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
				std::cout << itemdesc << std::endl;
			}
			else
			{
				std::cout << "You have no such thing\n";
			}
		}
		else if (input == "look")
		{
			if (rooms[loadedroomid].m_properties[6] == true)
			{
				std::cout << "It's too dark to see anything\n";
			}
			else
			{
				std::cout << rooms[loadedroomid].m_ConstDescr << " ";
				if (rooms[loadedroomid].m_ItemID.size() == 0)
				{
					std::cout << rooms[loadedroomid].m_PostitemDescr << " ";
				}
				else
				{
					std::cout << rooms[loadedroomid].m_PreitemDescr << " ";
				}
				if (rooms[loadedroomid].m_roomevent.size() == 0)
				{
					std::cout << rooms[loadedroomid].m_PosteventDescr << "\n";
				}
				else
				{
					std::cout << rooms[loadedroomid].m_PreeventDescr << "\n";
				}
			}
		}
		else if (input.substr(0, 5) == "equip")
		{	
			if(hero.m_ArmourEquip == true)
			{
				std::cout << "Already have armour equiped\n";
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
						std::cout << "Equiped!\n";
					}
					else
					{
						std::cout << "Cannot equip this\n";
					}
				}
				else
				{
					std::cout << "You have no such thing\n";
				}
			}

	    }		
		else if (input.substr(0, 7) == "unequip")
		{
		if (hero.m_ArmourEquip == false)
		{
			std::cout << "Nothing to unequip\n";
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
					std::cout << "Unequiped!\n";
				}
				else
				{
					std::cout << "You are not wearing this\n";
				}
			}
			else
			{
				std::cout << "You have no such thing\n";
			}
		}

		}
		else if (input == "inventory")
		{
			for (item i : inventory)
			{
				std::cout << i.m_name << std::endl;
			}
		}
		else if (input == "search")
		{
			if (rooms[loadedroomid].m_properties[6] == true)
			{
				std::cout << "It's too dark to see anything\n";
			}
			else if (rooms[loadedroomid].m_Search == "-")
			{
				std::cout << "There is nothing more to be seen here\n";
			}
			else
			{
				std::cout << rooms[loadedroomid].m_Search << std::endl;
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
				std::cout << "Cannot understand entry\n";
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

							}
							std::cout << "Made " << inventory[inventory.size() - 1].m_name << std::endl;
							printcheck = true;
							break;
						}
						++ii;
					}
					if (printcheck == false)
					{
						std::cout << "Cannot combines these in any meaningful way\n";
					}
				}
				else
				{
					std::cout << "You have no such thing\n";
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
								rooms[loadedroomid].m_properties[entry] = !rooms[loadedroomid].m_properties[entry];
							}

							std::cout << rooms[loadedroomid].m_roomevent[i + 2] << std::endl;
							rooms[loadedroomid].m_roomevent.erase(rooms[loadedroomid].m_roomevent.begin() + i + 2);
							rooms[loadedroomid].m_roomevent.erase(rooms[loadedroomid].m_roomevent.begin() + i + 1);
							rooms[loadedroomid].m_roomevent.erase(rooms[loadedroomid].m_roomevent.begin() + i);
							break;
						}
					}
					i = i + 3;
				}
				if (printcheck == false)
				{
					std::cout << "Cannot use here\n";
				}
			}
			else
			{
				std::cout << "You have no such thing\n";
			}

		}
		else
		{
			std::cout << "Cannot understand entry\n";
		}

	} while (true);
	return 0;
}