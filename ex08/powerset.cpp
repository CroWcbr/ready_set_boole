#include "powerset.hpp"

vec<vec<i32>>	powerset(vec<i32> &input)
{
	vec<vec<i32>>	result;

	for (size_t i = 0, size = input.size(), max = 1 << size; i < max; i++)
	{
		vec<i32>	tmp;
		for (size_t j = 0; j < size; j++)
			if (i & (1 << j))
				tmp.push_back(input[j]);
		result.push_back(tmp);
	}

	return result;
}
