#include "eval_set.hpp"

Vec<i32>	eval_set(const std::string &str, Vec<Vec<i32>> &vector_input)
{
	Tree						tree(str);
	std::map<char, Vec<i32>>	key_map;

	for (const auto &c : str)
		if (c >= 'A' && c <= 'Z')
			key_map.insert(std::pair<char, Vec<i32>>(c, NULL));

	size_t i = 0;
	for (auto &c : key_map)
		c.second = vector_input[i++];

	return tree.result_key_map_sets(key_map);
}
