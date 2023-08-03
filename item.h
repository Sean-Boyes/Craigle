#pragma once


class item
{
public:
	int m_itemid, m_assign1, m_assign2, m_type;
	std::string m_name, m_description;
	std::vector<int> m_combinables, m_combinies;

	item(std::string name, std::string description, std::string assign1, std::string assign2, std::string combinabales, std::string id, int type) : m_type(type), m_name(name), m_description(description) 
	{
		m_itemid = stoi(id);
		if (assign1 != "-")
		{
			m_assign1 = stoi(assign1);
		}
		if (assign2 != "-")
		{
			m_assign2 = stoi(assign2);
		}
		std::string temp;
		for (char& c : combinabales)
		{
			if (c == ',')
			{
				m_combinables.push_back(stoi(temp));
				temp.clear();
			}
			else if (c == '$')
			{
				m_combinies.push_back(stoi(temp));
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
