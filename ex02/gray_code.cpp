#include "gray_code.hpp"

u32	gray_code(u32 n)
{
	return n ^ (n >> 1);
}
