#include "print_truth_table.hpp"

void print_truth_table(const std::string &str)
{
	Tree					tree(str);
	std::map<char, bool>	key_map;

	for (const auto &c : str)
		if (c >= 'A' && c <= 'Z')
			key_map.insert(std::pair<char, bool>(c, 0));

	std::cout << "| ";
	for (const auto &c : key_map)
		std::cout << c.first << " | ";
	std::cout << "= |" << std::endl;

	std::map<char, bool>::iterator it;
	for (size_t i_key = 0, size = key_map.size(), max = 1 << size; i_key < max; i_key++)
	{
		it = key_map.begin();
		std::cout << "| ";
		for (uint32_t i = 0; i < size; i++)
		{
			it->second = ((i_key >> size - i - 1) & 1);
			std::cout << it->second << " | ";
			it++;
		}
		std::cout << tree.result(key_map) <<" |" << std::endl;
	}
}
