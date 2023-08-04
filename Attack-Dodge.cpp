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

#include "entity.hpp"
#include "screen.hpp"
#include "entity.hpp"

inline int roll(int x, int y)
{
    std::random_device rd;
    std::mt19937 engine{ rd() };
    std::uniform_int_distribution<> randomDie(x, y);
    return randomDie(engine);

};

inline int Attack(std::string hit, int frame)
{
    CsrMoveTo(descPos2[0], descPos2[1]);
    std::cout << "\x1b[1;37m";
    if (_kbhit())
    {
        _getch();
    }
    bool forwardcheck = 1;
    int hitstate = 0;
    printDesc2(hit, 1);
    auto start = std::chrono::steady_clock::now();
    while (true)
    {
        if (std::chrono::steady_clock::now() - start > std::chrono::milliseconds(frame))
        {
            char temp = hit[hitstate];
            hit[hitstate] = '|'; 
            CsrMoveTo(descPos2[0], descPos2[1]);
            std::cout << hit;
            hit[hitstate] = temp;
            if (forwardcheck == 1)
            {
                ++hitstate;
            }
            else
            {
                --hitstate;
            }
            if (hitstate == hit.size())
            {
                hitstate = hitstate - 2;
                forwardcheck = 0;
            }
            else if (hitstate < 0)
            {
                hitstate = hitstate + 2;
                forwardcheck = 1;
            }
            start = std::chrono::steady_clock::now();

        }
        if (_kbhit())
        {
            break;
        }

    }
    _getch();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (forwardcheck == 1)
    {
        --hitstate;
    }
    else
    {
        ++hitstate;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (hit[hitstate] == '.')
    {
        CsrMoveTo(descPos2[0], descPos2[1]);
        std::cout << "\x1b[1;31m" << "Miss!" << "\x1b[1; 37m";
        //printInfo(hero);
        usrInput();
        return 1;
    }
    else if (hit[hitstate] == 'o')
    {
        CsrMoveTo(descPos2[0], descPos2[1]);
        std::cout << "\x1b[1;33mHit!            \x1b[1; 37m";
        usrInput();
        return 2;
    }
    else if (hit[hitstate] == '0')
    {
        CsrMoveTo(descPos2[0], descPos2[1]);
        std::cout << "\x1b[1;32mCrit!            \x1b[1;37m";
        usrInput();
        return 3;
    }


};

inline bool Dodge(int window)
{
    bool dodge = false;
    CsrMoveTo(descPos2[0], descPos2[1]);
    std::cout << "\x1b[1;37mDodge!           ";
    usrInput();
    if (_kbhit())
    {
        _getch();
    }
    CsrMoveTo(descPos3[0], descPos3[1]);
    std::cout << "-<{[=#=]}>-           ";
    usrInput();
    auto timer = std::chrono::seconds(roll(2, 6));
    bool early = 0;
    auto start = std::chrono::steady_clock::now();
    while (true)
    {
        if (_kbhit())
        {
            CsrMoveTo(descPos3[0], descPos3[1]);
            std::cout << "\x1b[1;31m-<{[=#=]}>-          ";
            usrInput();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            CsrMoveTo(descPos2[0], descPos2[1]);
            std::cout << "Miss!          \x1b[1;37m";
            //printInfo();
            usrInput();
            early = 1;
            _getch();
            break;
        }
        if (std::chrono::steady_clock::now() - start > timer)
        {
            break;
        }

    }
    if (early == 0)
    {
        CsrMoveTo(descPos3[0], descPos3[1]);
        std::cout << "\x1b[1;33m{[[[=#=]]]}          ";
        usrInput();
        start = std::chrono::steady_clock::now();
        while (true)
        {
            if (_kbhit())
            {
                CsrMoveTo(descPos3[0], descPos3[1]);
                std::cout << "\x1b[1; 32m - <{ [=#=] }>-";
                usrInput();
                std::this_thread::sleep_for(std::chrono::milliseconds(window));
                CsrMoveTo(descPos2[0], descPos2[1]);
                std::cout << "Dodged!          \x1b[1;37m";
                usrInput();
                dodge = true;
                _getch();
                break;
            }
            if (std::chrono::steady_clock::now() - start > std::chrono::seconds(1))
            {
                CsrMoveTo(descPos3[0], descPos3[1]);
                std::cout << "\x1b[1; 31m - <{ [=#=] }>-";
                usrInput();
                std::this_thread::sleep_for(std::chrono::seconds(1));
                CsrMoveTo(descPos2[0], descPos2[1]);
                std::cout << "Miss!          \x1b[1;37m";
                //printInfo();
                usrInput();
                break;
            }

        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return dodge;
};

inline int heal(player& hero)
{
    if (hero.m_HealPot == 0)
    {
        CsrMoveTo(descPos2[0], descPos2[1]);
        std::cout << "Out of potions! ";
        //printInfo();
        usrInput();
        return false;
    }
    else if (hero.m_HP == hero.m_MaxHP)
    {
        CsrMoveTo(descPos2[0], descPos2[1]);
        std::cout << "Already at max HP! ";
        //printInfo();
        usrInput();
        return false;
    }
    else
    {
        hero.m_HP = hero.m_HP + 7;
        if (hero.m_HP > hero.m_MaxHP)
        {
            hero.m_HP = hero.m_MaxHP;
        }
        return true;
    }
}