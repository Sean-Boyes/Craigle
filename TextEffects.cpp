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



const long long rt5 = (int)(sqrt(5) * 1000000);
const long long rt7 = (int)(sqrt(11) * 1000000);

inline std::string getColour(std::string colour, bool isBright, bool isBackground) // 3:4 bit colour depth, most portable
{
	// 511
	// nothing to see here :3
	std::hash<std::string> hasher;
	size_t hash = hasher(colour);
	hash += (isBright * (rt5)+1) * (isBackground * (rt7)+1);
	int index = hash % 511; // 13 for 8 colours
	//cout << index << endl;
	switch (index) // hash table
	{
	case 244: return "\x1b[90;100m"; // black 
	case 315: return "\x1b[90m";
	case 107: return "\x1b[30;40m";
	case 384: return "\x1b[30m";
	case 179: return "\x1b[91;101m"; // red 
	case 250: return "\x1b[91m";
	case 42:  return "\x1b[31;41m";
	case 319: return "\x1b[31m";
	case 378: return "\x1b[92;102m"; // green 
	case 449: return "\x1b[92m";
	case 241: return "\x1b[32;42m";
	case 7:   return "\x1b[32m";
	case 29: return "\x1b[93;103m"; // yellow 
	case 100: return "\x1b[93m";
	case 403: return "\x1b[33;43m";
	case 169: return "\x1b[33m";
	case 365: return "\x1b[96;104m"; // blue 
	case 436: return "\x1b[96m";
	case 228: return "\x1b[34;44m";
	case 505: return "\x1b[34m";
	case 318: return "\x1b[95;105m"; // magenta 
	case 389: return "\x1b[95m";
	case 181: return "\x1b[35;45m";
	case 458: return "\x1b[35m";
	case 261: return "\x1b[96;106m"; // cyan 
	case 332: return "\x1b[96m";
	case 124: return "\x1b[36;46m";
	case 401: return "\x1b[36m";
	case 333: return "\x1b[97;107m"; // white 
	case 404: return "\x1b[97m";
	case 196: return "\x1b[37;107m";
	case 473: return "\x1b[37m";
	default: return ("\x1b[0m"); // Out of Bound
	}
}
inline std::string getColour(uint8_t colourId, bool isBackground) // 8-bit colour depth (3-3-2), see 256 color lookup table 
{
	if (isBackground) { return std::format("\x1b[48;5;{}m", colourId); }
	else { return std::format("\x1b[38;5;{}m", colourId); }
}
inline std::string getColour(uint8_t red, uint8_t green, uint8_t blue, bool isBackground) // 24-bit colour depth (8-8-8), only avaliable on modern terminals
{
	if (isBackground) { return std::format("\x1b[48;2;{};{};{}m", red, green, blue); }
	else { return std::format("\x1b[38;2;{};{};{}m", red, green, blue); }
}
inline std::string getEffect(char effect) // b: bold, u: underline, i: inverted, r: reset
{
	switch (effect)
	{
	case 'b': return ("\x1b[1m");
	case 'u': return ("\x1b[4m");
	case 'i': return ("\x1b[7m");
	case 'r': return ("\x1b[0m");
	default: return ("\x1b[0m"); // Out of Bound
	}
}
inline void SGRCodeTest() // Outputs all SGR codes to Terminal
{
	for (int i = 0; i < 107; i++)
	{
		std::cout << std::format("\x1b[{}m SGR code: {}   \x1b[0m", i, i) << std::endl;
	}
}
inline void ANSI4bitColourTest()
{
	std::string color[8] = { "black","red","green","yellow","blue","magenta","cyan","white" };
	for (int i = 0; i < 8; i++)
	{
		std::cout << getColour(color[i], 1, 1) << "bruh" << "\x1b[0m" << std::endl;
		std::cout << getColour(color[i], 1, 0) << "bruh" << "\x1b[0m" << std::endl;
		std::cout << getColour(color[i], 0, 1) << "bruh" << "\x1b[0m" << std::endl;
		std::cout << getColour(color[i], 0, 0) << "bruh" << "\x1b[0m" << std::endl;
	}
}