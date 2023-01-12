#include "gray_code.hpp"
#include <iostream>

static void print_bit(u32 &a)
{
	uint8_t	*tmp = (uint8_t*)&a;

	for (int byte = 0; byte < 4; byte++)
	{
		for (int bit = 7; bit >=0; bit--)
			std::cout << ((tmp[byte] >> bit) & 1);
		std::cout << " ";
	}
}

int main()
{
	u32	n;
	u32	result;
	std::string	input;

	std::cout << "GRAY_CODE" << std::endl;
	while (true)
	{
		std::cout << " input a > ";
		getline(std::cin, input);
		n = stoi(input);

		result = gray_code(n);

		print_bit(n);
		std::cout << "\t" << n << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		print_bit(result);
		std::cout << "\t" << result << std::endl;
		std::cout << std::endl;

		print_bit(n);
		std::cout << std::endl;
		u32	nn = n >> 1;
		print_bit(nn);
		std::cout << std::endl;
		print_bit(result);
		std::cout << std::endl;
	}
	std::cout << "THE END" << std::endl;
	return 0;
}
