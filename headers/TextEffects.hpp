#pragma once

#include "TextEffects.cpp"

inline std::string getColour(std::string colour, bool isBright, bool isBackground);

inline std::string getColour(uint8_t colourId, bool isBackground); // 8-bit colour depth (3-3-2), see 256 color lookup table 

inline std::string getColour(uint8_t red, uint8_t green, uint8_t blue, bool isBackground); // 24-bit colour depth (8-8-8), only avaliable on modern terminals

inline std::string getEffect(char effect); // b: bold, u: underline, i: inverted, r: reset

inline void SGRCodeTest(); // Outputs all SGR codes to Terminal

inline void ANSI4bitColourTest();