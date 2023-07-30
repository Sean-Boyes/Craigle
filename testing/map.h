
#pragma once

#include <vector>
#include <string>

#include "item.h"

class room
{
public:
	int m_xcord, m_ycord, m_zcord, m_roomevent;
    bool m_Cleared;
    std::string m_Title, m_ConstDescr, m_ClearedDescr, m_UnclearedDescr;
    std::vector<int> m_MonsterID, m_ItemID, m_RandEnc;
    std::vector<bool> m_properties;

    room() {};

    room(std::string Title, std::string ConstDescr, std::string UnclearedDescr, std::string ClearedDescr, std::string MonsterID, std::string ItemID, std::string RandEnc, std::string properties, std::string roomevent, std::string cords) : m_Title(Title), m_ConstDescr(ConstDescr), m_ClearedDescr(ClearedDescr), m_UnclearedDescr(UnclearedDescr), m_Cleared(false)
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
            if (c == 0)
            {
                m_properties.push_back(false);
            }
            else
            {
                m_properties.push_back(true);
            }
        }

        if (roomevent != "-")
        {
            m_roomevent = stoi(roomevent);
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