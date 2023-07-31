#pragma once
#include "ASCII-Display-Manager/ASCII/Cursor.h"
#include "ASCII-Display-Manager/ASCII/TextEffects.h"
#include <conio.h>
#include <format>
#include "entity.h"

ASCIIobject bounds;
ASCIIobject panel1;
ASCIIobject panel2;
ASCIIobject panel3;
ASCIIobject seperator;
ASCIIobject input;

vector<int> inputPos = { 10 , 38 };
vector<int> titlePos = { 9 , 6 };
vector<int> descPos = { 9 , 8 };

vector<vector<int>> knownRooms = { {0,0},{0,1},{-1,0 },{-2,0},{-2,1},{-2,-1},{0,-1},{0,-2},{1,-2},{2,-2},{2,-1},{2,0},{-3,0},{-3,1} };
vector<int> currentPos = { 0,0 };

int lineLength = 69;

void printDesc(string tempdesc, int textSpeed);

void refreshInput()
{
	int height = 1;
	int length = 69;
	CsrMoveTo(10, 38);
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < length; ii++)
		{
			cout << getEffect('r') << " ";
		}
		CsrMove('d', 1);
		CsrMove('l', length);
	}
}
void usrInput()
{
	refreshInput();
	CsrMoveTo(inputPos[0], inputPos[1]);
	cout << getColour("blue",1,0);
}
void initializeScreen()
{
	bounds.createCanvas(132, 43, " ", " ");
	panel1.createCanvas(bounds.dimension[0] * .60, bounds.dimension[1] - 4, "-", "{", "-", "}", "o", "o", "o", "o");
	panel2.createCanvas(bounds.dimension[0] * .36, bounds.dimension[1] / 2 - 6);
	panel3.createCanvas(panel2.dimension[0], panel2.dimension[1] + 8);
	seperator.load("seperator.txt");
	input.load("input.txt");
	input.paint(getColour("blue", 1, 0));

	bounds.place(0, 0);

	cout << "please resize your terminal to show the entire recangle, then press anykey" << endl;
	_getch();

	bounds.add(panel1, 3, 2);
	bounds.add(panel2, panel1.dimension[0] + 4, 2);
	bounds.add(panel3, panel1.dimension[0] + 4, panel2.dimension[1] + 3);
	bounds.add(seperator, 8, bounds.dimension[1] - 8);
	bounds.add(input, 8, bounds.dimension[1] - 6);
	bounds.paint(getColour("black", 1, 0));
	//bounds.paint(getEffect('r'));

	string tempTitle = "tempTitle";
	CsrMoveTo(9, 5);
	cout << tempTitle;

	// Get rid off extra text
	CsrMoveTo(0, bounds.dimension[1] + 1);
	cout << "                                                                                                          ";
	CsrMoveTo(11, bounds.dimension[1] - 4);

	bounds.place(0, 0);
	usrInput();
}
void refreshTitle(string title)
{
	CsrMoveTo(titlePos[0], titlePos[1]);
	cout << "                                                                     ";
	CsrMoveTo(titlePos[0], titlePos[1]);
	cout << getEffect('b') << getEffect('u') << title << getEffect('r');
	usrInput();
}
void refreshDesc()
{
	int length = 78 - 9;
	int height = 35 - 8;
	CsrMoveTo(9, 8);
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < length; ii++)
		{
			cout << getEffect('r') << " ";
		}
		CsrMove('d', 1);
		CsrMove('l', length);
	}
}
void printDesc(string tempdesc, int textSpeed) // rfind last space of 69 long string, get that index, cout that, go down 1, delete front till index, repeat. send into ascii object
{
	//string tempdesc = "They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.They put me in a rubber room. They put me in a rubber room with rats! They put me in a rubber room with rubber rats!!! The rats drove me crazy. Crazy?...I was crazy once.";
	//string tempdesc2 = "Imagine Gordon Ramsay's swollen testicles draped over the rats head. The wrinkled skin of his scrot covering the rats eyes as the rat gasps for air. The weight of Ramsay's testicles barely being held by the rats tiny arms. The rat knows this is how he's going to die but its passion for cooking over powers it and with a great desperate squeeze of Ramsay's left nut, Ramsay's blasts someone in the face regarding an inquiry of the location of where the lamb sauce is located.";
	refreshDesc();
	CsrMoveTo(descPos[0], descPos[1]);
	//cout << getEffect('r');
	int index;
	while (tempdesc.length() > 69)
	{
		index = tempdesc.rfind(' ', 69);
		for (int i = 0; i < index; i++)
		{
			cout << tempdesc[i];
			std::this_thread::sleep_for(.01ms * textSpeed);
		}
		tempdesc.erase(0, index + 1);
		cout << endl;
		CsrMove('r', 8);
	}
	for (int i = 0; i < tempdesc.length(); i++)
	{
		cout << tempdesc[i];
	}
	usrInput();
}
void refreshInfo()
{
	int length = 129 - 85;
	int height = 16 - 4;
	CsrMoveTo(85, 4);
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < length; ii++)
		{
			cout << getEffect('r') << " ";
		}
		CsrMove('d', 1);
		CsrMove('l', length);
	}
}
void printInfo(player& player)
{

	refreshInfo();

	//name and class
	CsrMoveTo(87, 5);
	cout << getColour("blue", 1, 0);
	//cout << getEffect('r');
	cout << player.m_Name << " the " << player.m_Class;

	//health
	CsrMoveTo(87, 7);
	if (player.m_MaxHP >= 10) { cout << "HP:" << player.m_HP << "/" << player.m_MaxHP; }
	else { cout << "HP:" << "0" << player.m_HealPot << "/" << player.m_MaxHP; }
	cout << " ";
	//health bar
	for (int i = 0; i < player.m_HP; i++)
	{
		cout << getColour("green", 1, 1) << " " << getEffect('r');
	}
	for (int i = 0; i < player.m_MaxHP - player.m_HP; i++)
	{
		cout << getColour("red", 1, 1) << " " << getEffect('r') << getColour("blue", 1, 0);
	}
	//stats
	CsrMoveTo(87, 10);
	cout << "POWER: " << player.m_Power;
	CsrMoveTo(87, 11);
	cout << "DEFENSE: " << player.m_Defense;
	CsrMoveTo(87, 12);
	cout << "SPEED: " << player.m_Speed;
	CsrMoveTo(87, 13);
	cout << "STEALTH: " << player.m_Stealth;

	//Position
	CsrMoveTo(108, 10);
	cout << "POSITION: ";
	printf("(%i, %i)", currentPos[0], currentPos[1]);
	CsrMoveTo(108, 12);
	cout << "ELEVATION: ";
	printf("(%i)", 0);

	//other
	CsrMoveTo(87, 15);
	cout << "POTIONS: " << player.m_HealPot;
	CsrMoveTo(108, 15);
	cout << "RATS KILLED: " << 420; //temp change later plz

	//go back
	usrInput();
}
void testmap()
{
	CsrMoveTo(91, 21);
	for (int i = 0; i < 20; i++)
	{
		if (i % 4 == 0) {
			cout << "  |      |      |      |      |    ";
			CsrMoveTo(91, 21 + i);
		}
		else {
			cout << "OOOOO--OOOOO--OOOOO--OOOOO--OOOOO";
			CsrMoveTo(91, 21 + i);
		}
	}
	usrInput();
}
void refreshMap()
{
	int length = 129 - 85;
	int height = 40 - 20;
	CsrMoveTo(85, 20);
	for (int i = 0; i < height; i++)
	{
		for (int ii = 0; ii < length; ii++)
		{
			cout << getEffect('r') << " ";
		}
		CsrMove('d', 1);
		CsrMove('l', length);
	}
}
void printMap()
{
	refreshMap();

	ASCIIobject room;
	cout << getColour("yellow", 0, 1);
	room.data = { {"O"," "," "," ","O"},{" "," "," "," "," "},{"O"," "," "," ","O"} };
	room.paint(getColour("red", 0, 1));
	for (int i = 0; i < knownRooms.size(); i++)
	{
		if (knownRooms[i][0] > currentPos[0] + 2 || knownRooms[i][0] < currentPos[0] - 2 || knownRooms[i][1] > currentPos[1] + 2 || knownRooms[i][1] < currentPos[1] - 2) continue;
		room.place((knownRooms[i][0] - currentPos[0]) * 7 + 105, (knownRooms[i][1] - currentPos[1]) * -4 + 29);
	}
	cout << getColour("yellow", 1, 1);
	room.data = { {"O"," "," "," ","O"},{" "," "," "," "," "},{"O"," "," "," ","O"} };
	room.place(knownRooms[0][0] * 7 + 105, knownRooms[0][1] * -4 + 29);
	CsrMoveTo(103, 30);
	cout << getEffect('r');
	//cout << getColour("red", 0, 1) << "[";
	//CsrMoveTo(104, 30);
	//cout << getColour("red", 0, 1) << "]";
	//CsrMoveTo(107, 28);
	//cout << getColour("yellow", 0, 1) << " ";

	cout << getEffect('r') << getColour("blue", 1, 0);
	usrInput();
}
void refreshScreen()
{
	bounds.place(0, 0);
	usrInput();
}