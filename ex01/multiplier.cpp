#include "multiplier.hpp"

u32 adder(u32 a, u32 b)
{
	u32	tmp;

	while (a)
	{
		tmp = (a & b) << 1;
		b = b ^ a;
		a = tmp;
	}
	return b;
}

u32 multiplier(u32 a, u32 b)
{
	u32	tmp = 0;

	while (a)
	{
		if (a & 1)
			tmp = adder(tmp, b);
		a >>= 1;
		b <<= 1;
	}
	return tmp;
}
