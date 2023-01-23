#include "reverse_map.hpp"

std::pair<uint16_t, uint16_t>	reverse_map(double n)
{
	uint16_t	x;
	uint16_t	y;

	x = y = 0;
	uint32_t z = (uint32_t)(n * std::numeric_limits<unsigned int>::max());
	for (int i = 0; i < 16; i++)
	{
		x |= (z & (1 << (i << 1))) >> i;
		y |= (z & (1 << ((i << 1) + 1))) >> (i + 1);
	}
	return std::pair<uint16_t,uint16_t>(x, y);
}
