#include "adder.hpp"
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
	u32	a;
	u32	b;
	u32	result;
	std::string	input;

	std::cout << "ADDER" << std::endl;
	while (true)
	{
		std::cout << " input a > ";
		getline(std::cin, input);
		a = stoi(input);

		std::cout << " input b > ";
		getline(std::cin, input);
		b = stoi(input);

		result = adder(a, b);


		print_bit(a);
		std::cout << "\t" << a << std::endl;
		print_bit(b);
		std::cout << "\t" << b << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		print_bit(result);
		std::cout << "\t" << result << std::endl;
		std::cout << std::endl;
	}
	std::cout << "THE END" << std::endl;
	return 0;
}
