#pragma once


class item
{
public:
	int m_itemid;
	std::string m_name, m_description, m_combinabales;

	virtual void itemset() {};

	static int GetItem(std::vector<item> items, int id) 
	{
		int i = 0;
		for (const item& it : items) {
			if (it.m_itemid == id) {
				return i;
			}
			++i;
		}
		return -1;
	};
};

class swordupgrade : public item
{
public:
	std::vector<std::string> activeinteractions{ "use", "swing", "slash" };

	std::string m_atk;
	swordupgrade(std::string name, std::string description, std::string atk, std::string combinabales, std::string id)
	{
		m_name = name;
		m_description = description;
		m_combinabales = combinabales;
		m_itemid = stoi(id);
		m_atk = stoi(atk);
	};
};

class armourupgrade : public item
{
public:
	std::vector<std::string> activeinteractions{"wear", "equip", "put on", "use"};
	std::vector<std::string> inactiveinteractions{"unequip", "take off", "remove"};

	std::string m_def;
	armourupgrade(std::string name, std::string description, std::string def, std::string combinabales, std::string id)
	{
		m_name = name;
		m_description = description;
		m_combinabales = combinabales;
		m_itemid = stoi(id);
		m_def = stoi(def);
	}
};

class quest : public item
{
public:
	std::string activeinteraction = "use";

	quest(std::string name, std::string description, std::string combinabales, std::string id)
	{
		m_name = name;
		m_description = description;
		m_itemid = stoi(id);
		m_combinabales = combinabales;
	}
};