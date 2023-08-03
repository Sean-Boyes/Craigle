#pragma once

#include "screen.cpp"

inline void refreshInput();
inline void usrInput();
inline void initializeScreen();
inline void refreshTitle(std::string title);
inline void refreshDesc();
inline void printDesc(std::string tempdesc, int textSpeed); // rfind last space of 69 long string, get that index, cout that, go down 1, delete front till index, repeat. send into ascii object
inline void printDescForce(std::string tempdesc, int textSpeed); // rfind last space of 69 long string, get that index, cout that, go down 1, delete front till index, repeat. send into ascii object
inline void refreshDesc2();
inline void printDesc2(std::string tempdesc, int textSpeed);
inline void refreshDesc3();
inline void printDesc3(std::string tempdesc, int textSpeed);
inline void refreshInfo();
inline void printInfo(player& player);
inline void testmap();
inline void refreshMap();
inline void printMap();
inline void refreshScreen();
inline void lookAround(std::vector<room> rooms, int xcord, int ycord);
inline void interuptThread();
