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


#include "TextEffects.hpp"
#include "Cursor.hpp"
#include "map.hpp"
#include "entity.hpp"

inline ASCIIobject bounds;
inline ASCIIobject panel1;
inline ASCIIobject panel2;
inline ASCIIobject panel3;
inline ASCIIobject seperator;
inline ASCIIobject input;
inline ASCIIobject croom;

inline std::string preTitle = "";
inline std::string preDesc = "";

inline bool interupt = false;

static std::vector<int> inputPos = { 10 , 38 };
static std::vector<int> titlePos = { 9 , 6 };
static std::vector<int> descPos = { 9 , 8 };
static std::vector<int> descPos2 = { 9 , 25 };
static std::vector<int> descPos3 = { 9 , 35 };

inline std::vector<std::vector<int>> knownRooms = { {0,0} };
inline std::vector<int> currentPos = { 0,0 };
inline std::vector<int> aroundPos = { 0,0 };

static int lineLength = 69;
inline void refreshDesc2();
inline void refreshDesc3();
inline void printDesc(std::string tempdesc, int textSpeed);
inline void printDescForce(std::string tempdesc, int textSpeed);

inline void refreshInput()
{
	int height = 1;
	int length = 69;
	CsrMoveTo(10, 38);
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < length; ii++)
		{
			std::cout << getEffect('r') << " ";
		}
		CsrMove('d', 1);
		CsrMove('l', length);
	}
}
inline void usrInput()
{
	refreshInput();
	CsrMoveTo(inputPos[0] - 1, inputPos[1]);
	std::cout << getColour("blue", 1, 0) << ">";
}
inline void initializeScreen()
{
	bounds.createCanvas(132, 43, " ", " ");
	panel1.createCanvas(bounds.dimension[0] * .60, bounds.dimension[1] - 4, "-", "{", "-", "}", "o", "o", "o", "o");
	panel2.createCanvas(bounds.dimension[0] * .36, bounds.dimension[1] / 2 - 6);
	panel3.createCanvas(panel2.dimension[0], panel2.dimension[1] + 8);
	seperator.load("seperator.txt");
	input.load("input.txt");
	input.paint(getColour("blue", 1, 0));

	bounds.place(0, 0);

	std::cout << "please resize your terminal to show the entire recangle, then press anykey" << std::endl;
	_getch();

	bounds.add(panel1, 3, 2);
	bounds.add(panel2, panel1.dimension[0] + 4, 2);
	bounds.add(panel3, panel1.dimension[0] + 4, panel2.dimension[1] + 3);
	bounds.add(seperator, 8, bounds.dimension[1] - 8);
	bounds.add(input, 8, bounds.dimension[1] - 6);
	bounds.paint(getColour("black", 1, 0));
	//bounds.paint(getEffect('r'));

	std::string tempTitle = "tempTitle";
	CsrMoveTo(9, 5);
	std::cout << tempTitle;

	// Get rid off extra text
	CsrMoveTo(0, bounds.dimension[1] + 1);
	std::cout << "                                                                                                          ";
	CsrMoveTo(11, bounds.dimension[1] - 4);

	bounds.place(0, 0);
	usrInput();
}
inline void refreshTitle(std::string title)
{
	if (preTitle == title)
	{
		return;
	}
	preTitle = title;
	CsrMoveTo(titlePos[0], titlePos[1]);
	std::cout << "                                                                     ";
	CsrMoveTo(titlePos[0], titlePos[1]);
	std::cout << getEffect('b') << getEffect('u') << title << getEffect('r');
	usrInput();
}
inline void refreshDesc()
{
	int length = 78 - 9;
	int height = 35 - 18;
	CsrMoveTo(9, 8);
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < length; ii++)
		{
			std::cout << getEffect('r') << " ";
		}
		CsrMove('d', 1);
		CsrMove('l', length);
	}
}
inline void printDesc(std::string tempdesc, int textSpeed) // rfind last space of 69 long string, get that index, cout that, go down 1, delete front till index, repeat. send into ascii object
{
	if (preDesc == tempdesc)
	{
		return;
	}
	preDesc = tempdesc;
	refreshDesc();
	refreshDesc2();
	refreshDesc3();
	CsrMoveTo(descPos[0], descPos[1]);
	//cout << getEffect('r');
	int index;
	while (tempdesc.length() > 69)
	{
		if (interupt)
		{
			printDescForce(preDesc, textSpeed);
			interupt = false;
			return;
		}
		index = tempdesc.rfind(' ', 69);
		for (int i = 0; i < index; i++)
		{
			if (interupt)
			{
				printDescForce(preDesc, textSpeed);
				interupt = false;
				return;
			}
			std::cout << tempdesc[i];
			if (textSpeed == 0) break;
			std::this_thread::sleep_for(std::chrono::milliseconds(1) * textSpeed * 0.01);

		}
		tempdesc.erase(0, index + 1);
		std::cout << std::endl;
		CsrMove('r', 8);
	}
	for (int i = 0; i < tempdesc.length(); i++)
	{
		std::cout << tempdesc[i];
		if (textSpeed == 0) break;
		std::this_thread::sleep_for(std::chrono::milliseconds(1) * textSpeed * 0.01);
	}
	usrInput();
}
inline void printDescForce(std::string tempdesc, int textSpeed) // rfind last space of 69 long string, get that index, cout that, go down 1, delete front till index, repeat. send into ascii object
{
	preDesc = tempdesc;
	refreshDesc();
	refreshDesc2();
	refreshDesc3();
	CsrMoveTo(descPos[0], descPos[1]);
	//cout << getEffect('r');
	int index;
	while (tempdesc.length() > 69)
	{
		index = tempdesc.rfind(' ', 69);
		for (int i = 0; i < index; i++)
		{
			std::cout << tempdesc[i];
		}
		tempdesc.erase(0, index + 1);
		std::cout << std::endl;
		CsrMove('r', 8);
	}
	for (int i = 0; i < tempdesc.length(); i++)
	{
		std::cout << tempdesc[i];
	}
	usrInput();
}
inline void refreshDesc2()
{
	int length = 78 - 9;
	int height = 35 - 26;
	CsrMoveTo(9, 25);
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < length; ii++)
		{
			std::cout << getEffect('r') << " ";
		}
		CsrMove('d', 1);
		CsrMove('l', length);
	}
}
inline void printDesc2(std::string tempdesc, int textSpeed)
{
	refreshDesc2();
	refreshDesc3();
	CsrMoveTo(descPos2[0], descPos2[1]);
	//cout << getEffect('r');
	int index;
	while (tempdesc.length() > 69)
	{
		index = tempdesc.rfind(' ', 69);
		for (int i = 0; i < index; i++)
		{
			std::cout << tempdesc[i];
			if (textSpeed == 0) break;
			std::this_thread::sleep_for(std::chrono::milliseconds(1) * textSpeed * 0.01);
		}
		tempdesc.erase(0, index + 1);
		std::cout << std::endl;
		CsrMove('r', 8);
	}
	for (int i = 0; i < tempdesc.length(); i++)
	{
		std::cout << tempdesc[i];
		if (textSpeed == 0) break;
		std::this_thread::sleep_for(std::chrono::milliseconds(1) * textSpeed * 0.01);
	}
	usrInput();
}
inline void refreshDesc3()
{
	int length = 78 - 9;
	int height = 1;
	CsrMoveTo(9, 35);
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < length; ii++)
		{
			std::cout << getEffect('r') << " ";
		}
		CsrMove('d', 1);
		CsrMove('l', length);
	}
}
inline void printDesc3(std::string tempdesc, int textSpeed)
{
	refreshDesc3();
	CsrMoveTo(descPos3[0], descPos3[1]);
	//cout << getEffect('r');
	int index;
	while (tempdesc.length() > 69)
	{
		index = tempdesc.rfind(' ', 69);
		for (int i = 0; i < index; i++)
		{
			std::cout << tempdesc[i];
			if (textSpeed == 0) break;
			std::this_thread::sleep_for(std::chrono::milliseconds(1) * textSpeed * 0.01);
		}
		tempdesc.erase(0, index + 1);
		std::cout << std::endl;
		CsrMove('r', 8);
	}
	for (int i = 0; i < tempdesc.length(); i++)
	{
		std::cout << tempdesc[i];
		if (textSpeed == 0) break;
		std::this_thread::sleep_for(std::chrono::milliseconds(1) * textSpeed * 0.01);
	}
	usrInput();
}
inline void refreshInfo()
{
	int length = 129 - 85;
	int height = 16 - 4;
	CsrMoveTo(85, 4);
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < length; ii++)
		{
			std::cout << getEffect('r') << " ";
		}
		CsrMove('d', 1);
		CsrMove('l', length);
	}
}
inline void printInfo(player& player)
{

	refreshInfo();

	//name and class
	CsrMoveTo(87, 5);
	std::cout << getColour("blue", 1, 0);
	//cout << getEffect('r');
	std::cout << player.m_Name << " the " << player.m_Class;

	//health
	CsrMoveTo(87, 7);
	if (player.m_MaxHP >= 10) { std::cout << "HP:" << player.m_HP << "/" << player.m_MaxHP; }
	else { std::cout << "HP:" << "0" << player.m_HealPot << "/" << player.m_MaxHP; }
	std::cout << " ";
	//health bar
	for (int i = 0; i < player.m_HP; i++)
	{
		std::cout << getColour("green", 1, 1) << " " << getEffect('r');
	}
	for (int i = 0; i < player.m_MaxHP - player.m_HP; i++)
	{
		std::cout << getColour("red", 1, 1) << " " << getEffect('r') << getColour("blue", 1, 0);
	}
	//stats
	CsrMoveTo(87, 10);
	std::cout << "POWER: " << player.m_Power;
	CsrMoveTo(87, 11);
	std::cout << "DEFENSE: " << player.m_Defense;
	CsrMoveTo(87, 12);
	std::cout << "SPEED: " << player.m_Speed;
	CsrMoveTo(87, 13);
	std::cout << "STEALTH: " << player.m_Stealth;

	//Position
	CsrMoveTo(108, 10);
	std::cout << "POSITION: ";
	printf("(%i, %i)", currentPos[0], currentPos[1]);
	CsrMoveTo(108, 12);
	std::cout << "ELEVATION: ";
	printf("(%i)", 0);

	//other
	CsrMoveTo(87, 15);
	std::cout << "POTIONS: " << player.m_HealPot;
	CsrMoveTo(108, 15);
	std::cout << "RATS KILLED: " << 420; //temp change later plz

	//go back
	usrInput();
}
inline void testmap()
{
	CsrMoveTo(91, 21);
	for (int i = 0; i < 20; i++)
	{
		if (i % 4 == 0) {
			std::cout << "  |      |      |      |      |    ";
			CsrMoveTo(91, 21 + i);
		}
		else {
			std::cout << "OOOOO--OOOOO--OOOOO--OOOOO--OOOOO";
			CsrMoveTo(91, 21 + i);
		}
	}
	usrInput();
}
inline void refreshMap()
{
	int length = 129 - 85;
	int height = 40 - 20;
	CsrMoveTo(85, 20);
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < length; ii++)
		{
			std::cout << getEffect('r') << " ";
		}
		CsrMove('d', 1);
		CsrMove('l', length);
	}
}
inline void printMap()
{
	refreshMap();


	std::cout << getColour("yellow", 0, 1);
	croom.data = { {"O"," "," "," ","O"},{" "," "," "," "," "},{"O"," "," "," ","O"} };
	croom.paint(getColour("red", 0, 1));
	for (int i = 0; i < knownRooms.size(); i++)
	{
		if (knownRooms[i][0] > currentPos[0] + 2 || knownRooms[i][0] < currentPos[0] - 2 || knownRooms[i][1] > currentPos[1] + 2 || knownRooms[i][1] < currentPos[1] - 2) continue;
		croom.place((knownRooms[i][0] - currentPos[0]) * 7 + 105, (knownRooms[i][1] - currentPos[1]) * -4 + 29);
	}
	std::cout << getColour("yellow", 1, 1);
	croom.data = { {"O"," "," "," ","O"},{" "," "," "," "," "},{"O"," "," "," ","O"} };
	croom.place(knownRooms[0][0] * 7 + 105, knownRooms[0][1] * -4 + 29);
	CsrMoveTo(103, 30);
	std::cout << getEffect('r');
	//cout << getColour("red", 0, 1) << "[";
	//CsrMoveTo(104, 30);
	//cout << getColour("red", 0, 1) << "]";
	//CsrMoveTo(107, 28);
	//cout << getColour("yellow", 0, 1) << " ";

	std::cout << getEffect('r') << getColour("blue", 1, 0);
	usrInput();
}
inline void refreshScreen()
{
	bounds.place(0, 0);
	usrInput();
}
inline void lookAround(std::vector<room> rooms, int xcord, int ycord)
{
	//loop throught rooms in 4 directions removing corners
	currentPos = { xcord, ycord };
	for (int i = -1; i <= 1; i++)
	{
		for (int ii = -1; ii <= 1; ii++)
		{
			aroundPos = { (currentPos[0] + ii),(currentPos[1] + i) };
			int roomid = room::CordLookup(rooms, aroundPos[0], aroundPos[1], 0);
			if (ii == i || -ii == i)
			{
				continue;
			}
			if (std::find(knownRooms.begin(), knownRooms.end(), aroundPos) != knownRooms.end()) // problematic
			{
				//cout << "element exists ";//element exists
			}
			else if (roomid != -1)
			{
				knownRooms.push_back(aroundPos);
			}
		}
	}

	printMap();
}
inline void interuptThread()
{
	_getch();
	interupt = true;
}