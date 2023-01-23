#include "map.hpp"

//Morton curve space-filling algorithm
double map(uint16_t x, uint16_t y)
{
	uint32_t z = 0;
	for (int i = 0; i < 16; i++)
	{
		z |= (x & (1 << i)) << i;
		z |= (y & (1 << i)) << (i + 1);
	}
	return static_cast<double>(z) / static_cast<double>(1ull << 32);
}
