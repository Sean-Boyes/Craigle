#pragma once

#include "entity.h"


inline int roll(int x, int y)
{

    std::random_device rd;
    std::mt19937 engine{ rd() };
    std::uniform_int_distribution<> randomDie(x, y);
    return randomDie(engine);

}

inline int Attack(std::string hit, int frame)
{
    std::cout << "\x1b[1;37m" << "\r";
    if (_kbhit())
    {
        _getch();
    }
    bool forwardcheck = 1;
    int hitstate = 0;
    std::cout << hit;
    auto start = std::chrono::steady_clock::now();
    while (true)
    {
        if (std::chrono::steady_clock::now() - start > std::chrono::milliseconds(frame))
        {
            char temp = hit[hitstate];
            hit[hitstate] = '|';
            std::cout << "\r" << hit;
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
        std::cout << "\r" << "\x1b[1;31m" << "Miss!            \n" << "\x1b[1;37m";
        return 1;
    }
    else if (hit[hitstate] == 'o')
    {
        std::cout << "\r" << "\x1b[1;33m" << "Hit!            \n" << "\x1b[1; 37m";
        return 2;
    }
    else if (hit[hitstate] == '0')
    {
        std::cout << "\r" << "\x1b[1;32m" << "Crit!            \n" << "\x1b[1;37m";
        return 3;
    }


}

inline bool Dodge(int window) 
{
    bool dodge = false;
    std::cout << "\x1b[1;37m" << "\r" << "Dodge!           \n";
    if (_kbhit())
    {
        _getch();
    }
    std::cout << "\r" << "-<{[=#=]}>-           ";
    auto timer = std::chrono::seconds(roll(2, 6));
    bool early = 0;
    auto start = std::chrono::steady_clock::now();
    while (true)
    {
        if (_kbhit())
        {
            std::cout << "\r" << "\x1b[1;31m" << "-<{[=#=]}>-          ";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "\r" << "Miss!          \n" << "\x1b[1;37m";
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
        std::cout << "\r" << "\x1b[1;33m" << "{[[[=#=]]]}          ";
        start = std::chrono::steady_clock::now();
        while (true)
        {
            if (_kbhit())
            {
                std::cout << "\r" << "\x1b[1;32m" << "-<{[=#=]}>-          ";
                std::this_thread::sleep_for(std::chrono::milliseconds(window));
                std::cout << "\r" << "Dodged!          \n" << "\x1b[1;37m";
                dodge = true;
                _getch();
                break;
            }
            if (std::chrono::steady_clock::now() - start > std::chrono::seconds(1))
            {
                std::cout << "\r" << "\x1b[1;31m" << "-<{[=#=]}>-          ";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "\r" << "Miss!          \n" << "\x1b[1;37m";
                break;
            }

        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return dodge;
}

inline int heal(player& hero)
{
    if (hero.m_HealPot == 0)
    {
        std::cout << "Out of potions!\n";
        return false;
    }
    else if (hero.m_HP == hero.m_MaxHP)
    {
        std::cout << "Already at max HP!\n";
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