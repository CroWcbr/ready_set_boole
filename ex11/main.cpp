#include "reverse_map.hpp"
#include "map.hpp"
#include <iostream>
#include <signal.h>
#include <string>

static void	_signal_handler(int signal)
{
	{
		std::string msg = "\rSTOP SIGNAL";
		if (signal == -1)
			msg.append(" Ctrl + D ");
		else if (signal == 2)
			msg.append(" Ctrl + C ");
		else if (signal == 3)
			msg.append(" Ctrl + / ");
		else if (signal == 20)
			msg.append(" Ctrl + Z ");
		else
			msg.append(" Unknown signal ");

		msg.append("from user");

		std::cout << "\033[93m";
		std::cout << msg << std::endl;
		std::cout << "\033[0m";
	}
	exit(signal);
}

static double	input_double()
{
	std::string	input;
	double		result;

	std::cout << "Input n > ";
	getline(std::cin, input);

	if (std::cin.eof())				//Ctrl + 'D'
		_signal_handler(-1);

	try
	{
		result = std::stod(input);
	}
	catch(...)
	{
		throw std::runtime_error("WRONG Enter");
	}
	
	if (result < 0 || result > 1)
		throw std::runtime_error("Enter DOUBLE is wrong. MUST be >=0 && <=1");

	return result;
}

static void print_bit_16(uint16_t &a)
{
	uint8_t	*tmp = (uint8_t*)&a;

	for (int byte = 0; byte < 2; byte++)
	{
		for (int bit = 7; bit >=0; bit--)
			std::cout << ((tmp[byte] >> bit) & 1);
		std::cout << " ";
	}
	std::cout << std::endl;
}

static void print_bit_32(uint32_t &a)
{
	uint8_t	*tmp = (uint8_t*)&a;

	for (int byte = 0; byte < 4; byte++)
	{
		for (int bit = 7; bit >=0; bit--)
			std::cout << ((tmp[byte] >> bit) & 1);
		std::cout << " ";
	}
	std::cout << std::endl;
}

static void test_reverse_map(uint16_t x, uint16_t y)
{
	std::pair<uint16_t, uint16_t> result;

	std::cout << "------------------------------------" << std::endl;
	std::cout << "INPUT = (" << x << ", " << y << ")" << std::endl;
	double r = map(x, y);
	std::cout << "map\t\t=\t" << r << std::endl;
	result = reverse_map(r);
	uint32_t rr = (uint32_t)(r * std::numeric_limits<uint32_t>::max());
	std::cout << "map_uint32\t=\t" << rr << std::endl;
	print_bit_32(rr);
	std::cout << "x\t\t=\t" << result.first << std::endl;
	print_bit_16(x);
	std::cout << "y\t\t=\t" << result.second << std::endl;
	print_bit_16(y);
	std::cout << "------------------------------------" << std::endl;
}

int main()
{
	bool			test;

	std::cout << "Set evaluation programm" << std::endl;

	signal(SIGINT, _signal_handler);	//Ctrl + 'C'
	signal(SIGQUIT, _signal_handler);	//Ctrl + '\'
	signal(SIGTSTP, _signal_handler);	//Ctrl + 'Z'

	test = 1;
	while (true)
	{
		try
		{
			if (test)
			{
				test_reverse_map(0, 0);
				test_reverse_map(2, 3);
				test_reverse_map(333, 333);
				test_reverse_map(3232, 2323);
				test_reverse_map(9876, 6789);
				test_reverse_map(2100, 2100);
				test_reverse_map(4200, 4200);
				test_reverse_map(65535, 65535);
				break;
			}
			else
			{
				std::pair<uint16_t, uint16_t> result;
				double	n = input_double();
				std::cout << "------------------------------------" << std::endl;
				std::cout << "n = " << n << std::endl;
				uint32_t rr = (uint32_t)(n * std::numeric_limits<uint32_t>::max());
				std::cout << "map_uint32\t=\t" << rr << std::endl;
				result = reverse_map(n);
				std::cout << "x\t\t=\t" << result.first << std::endl;
				print_bit_16(result.first);
				std::cout << "y\t\t=\t" << result.second << std::endl;
				print_bit_16(result.second);
				std::cout << "------------------------------------" << std::endl;
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	std::cout << "THE END" << std::endl;
	return 0;
}
