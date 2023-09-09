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




typedef std::vector<std::string> line;
typedef std::vector<line> image;


// Cursor functions
// Have to be inline

inline void CsrMoveTo(int x, int y) // Moves cursor 'x' from the top, and 'y' from the left.
{
	printf("\x1b[%i;%iH", y, x);
}
inline void CsrMove(char direction, int n)
{
	switch (direction)
	{
	case 'u':
		printf("\x1b[%iA", n);
		break;
	case 'd':
		printf("\x1b[%iB", n);
		break;
	case 'r':
		printf("\x1b[%iC", n);
		break;
	case 'l':
		printf("\x1b[%iD", n);
		break;
	default:
		printf("Invalid Direction input in 'move' function. \n");
		break;
	}
}