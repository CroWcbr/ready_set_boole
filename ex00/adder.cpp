#include "adder.hpp"

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
