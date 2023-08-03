
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


class room
{
public:
	int m_xcord, m_ycord, m_zcord;
    bool m_Cleared;
    std::string m_Title, m_ConstDescr, m_PreitemDescr, m_PostitemDescr, m_PreeventDescr, m_PosteventDescr, m_Search;
    std::vector<int> m_MonsterID, m_ItemID, m_RandEnc;
    std::vector<std::string> m_roomevent;
    std::vector<bool> m_properties;


    room() {};

    room(std::string Title, std::string ConstDescr, std::string PreitemDescr, std::string PostitemDescr, std::string PreeventDescr, std::string PosteventDescr, std::string Search, std::string MonsterID, std::string ItemID, std::string RandEnc, std::string properties, std::string roomevent, std::string cords) : m_Title(Title), m_ConstDescr(ConstDescr), m_PreeventDescr(PreeventDescr), m_PosteventDescr(PosteventDescr), m_PreitemDescr(PreitemDescr), m_PostitemDescr(PostitemDescr), m_Search(Search), m_Cleared(false)
    {
        //propety order:: lockednorth, lockedsouth, lockedeast, lockedwest, lockeddown, lockedup, dark, flooded, freezing
        size_t x = cords.find(',');
        size_t z = cords.rfind(',');
        m_xcord = stoi(cords.substr(0, x));
        m_zcord = stoi(cords.substr(z + 1, cords.size() - z));
        m_ycord = stoi(cords.substr(x + 1, z - x));

        std::string temp;
        for (char& c : MonsterID)
        {
            if (c == ',')
            {
                m_MonsterID.push_back(stoi(temp));
                temp.clear();
            }
            else if (isdigit(c) == false)
            {
                continue;
            }
            else
            {
                temp.push_back(c);
            }
        }
 
        for (char& c : ItemID)
            {
                if (c == ',')
                {
                    if (temp != "")
                    {
                        m_ItemID.push_back(stoi(temp));
                    }
                    temp.clear();
                }
                else if (c == '-')
                {
                    continue;
                }
                else
                {
                    temp.push_back(c);
                }

            }

        for (char& c : RandEnc)
        {
            if (c == ',' || c == '|')
            {
                m_RandEnc.push_back(stoi(temp));
                temp.clear();
            }
            else if (c == '-')
            {
                continue;
            }
            else
            {
                temp.push_back(c);
            }
        }
        
        for (char& c : properties)
        {
            if (c == '0')
            {
                m_properties.push_back(false);
            }
            else
            {
                m_properties.push_back(true);
            }
        }

        for (char& c : roomevent)
        {
            if (c == '$')
            {
                m_roomevent.push_back(temp);
                temp.clear();
            }
            else if (c == '-')
            {
                continue;
            }
            else
            {
                temp.push_back(c);
            }
        }

    };
 

    static int CordLookup(const std::vector<room>& Rooms, int xcord, int ycord, int zcord) {
        int i = 0;
        for (const room& r : Rooms) {
            if (r.m_xcord == xcord && (r.m_ycord == ycord && r.m_zcord == zcord)) {
                return i;
            }
            ++i;
        }
        return -1;
    }

};