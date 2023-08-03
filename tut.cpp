#pragma once

#include "battle.h"


void tutorial()
{
	//printDesc2("", 1)
	std::string input;
	std::cout << "\x1b[1;37m" << "Welcome Adventurer! Before we get started its best to introduce you to the system!\n\nIt looks like there is a room to the East, try moving there now by typing \"Go East\"\n";
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "go east")
		{
			break;
		}
		else
		{
			std::cout << "Not quite, try again!\n";
		}
	}
	std::cout << "Nice job! You are now in the next room over to the east! You can move around in simialr way for North, South, West, Up, and Down!\nLooks like there is a Sword in here, how about you try taking it with \"Take Sword\"!\n";
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "take sword")
		{
			break;
		}
		else
		{
			std::cout << "Not quite, try again!\n";
		}
	}
	std::cout << "Great! You got the Sword!\nUh-oh, Looks like there is a Zombie in here now though. Some rooms have enemies, and if they do you will be launched into combat against them immedietly. Let's practice!\nLooks like the Zombie will attack first! now to dodge an attack, press any key when the indicator turns yellow. Let's give it a try!\n";
	bool dodge = false;
	do
	{
		dodge = Dodge(30);
	} while (dodge == false);
	std::cout << "Awesome, looks like you dodged it! Now it's your turn to strike! How attacking works is each enemy has an Attack Bar and a moving Pipe. By pressing any key, you will stop the Pipe. If the Pipe lands on \".\", you miss. If it lands on \"o\", you hit. If it lands on \"0\" you get a critical hit! Try getting a critial hit on the Zombie!\n";
	int attack = 0;
	do
	{
		attack = Attack("..ooo000ooo..", 90);
	} while (attack != 3);
	std::cout << "Fantastic! You slautered that bastard! Looks like he had half a key too. Why don't you try picking it up with \"Take Key Half 1\".\n";
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "take key half 1")
		{
			break;
		}
		else
		{
			std::cout << "Not quite, try again!\n";
		}
	}
	std::cout << "Looks like there is another half too. Try grabbing it with \"Take Key Half 2\".\n";
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "take key half 2")
		{
			break;
		}
		else
		{
			std::cout << "Not quite, try again!\n";
		}
	}
	std::cout << "Seems like the halves may fit together...why not try it out? Use \"Combine Key Half 1 And Key Half 2\".\n";
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "combine key half 1 and key half 2" || input == "combine key half 2 and key half 1")
		{
			break;
		}
		else
		{
			std::cout << "Not quite, try again!\n";
		}
	}
	std::cout << "Like a glove! Now that we have this key we need a place to use it. Not seeing much of anything though. Try looking around with \"Search\"!\n";
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "search")
		{
			break;
		}
		else
		{
			std::cout << "Not quite, try again!\n";
		}
	}
	std::cout << "Hey, looks like there is a locked door to the North, why don't you try the key on that! Use \"Use Key\"!\n";
	while (true)
	{
		std::getline(std::cin, input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if (input == "use key")
		{
			break;
		}
		else
		{
			std::cout << "Not quite, try again!\n";
		}
	}
	std::cout << "The door opened! Looks like you got the idea of how to play now too! Last thing to do is pick your class!\n";

	return;

}
