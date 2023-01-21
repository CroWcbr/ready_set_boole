#include "sat.hpp"

bool	sat(const std::string &str)
{
	std::map<char, bool>	key_map;
	Tree					tree(str);

	for (const auto &c : str)
		if (c >= 'A' && c <= 'Z')
			key_map.insert(std::pair<char, bool>(c, 0));

	std::map<char, bool>::iterator it;
	for (size_t i_key = 0, size = key_map.size(), max = 1 << size; i_key < max; i_key++)
	{
		it = key_map.begin();
		for (uint32_t i = 0; i < size; i++)
		{
			it->second = ((i_key >> (size - i - 1)) & 1);
			it++;
		}
		if (tree.result_key_map(key_map))
			return true;
	}

	return false;
}
