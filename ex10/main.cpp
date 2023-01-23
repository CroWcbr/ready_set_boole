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

static uint16_t	input_int(char c)
{
	std::string	input;

	std::cout << "Input " << c << " > ";
	getline(std::cin, input);

	if (std::cin.eof())				//Ctrl + 'D'
		_signal_handler(-1);

	for (const auto &c : input)
		if (c < '0' || c > '9')
			throw std::runtime_error("UINT has invalid characters");
	
	if (std::stoi(input) > 65535)
		throw std::runtime_error("Input is too big. Correct input >0 && <65535");

	return (uint16_t)std::stoi(input);
}

// static void print_bit(uint32_t &a)
// {
// 	uint8_t	*tmp = (uint8_t*)&a;

// 	for (int byte = 0; byte < 4; byte++)
// 	{
// 		for (int bit = 7; bit >=0; bit--)
// 			std::cout << ((tmp[byte] >> bit) & 1);
// 		std::cout << " ";
// 	}
// 	std::cout << std::endl;
// }

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
				std::cout << "test 1 : \t" << map(0, 0) << std::endl;
				std::cout << "test 2 : \t" << map(2, 3) << std::endl;
				std::cout << "test 3 : \t" << map(333, 333) << std::endl;
				std::cout << "test 4 : \t" << map(3232, 2323) << std::endl;
				std::cout << "test 5 : \t" << map(9876, 6789) << std::endl;
				std::cout << "test 6 : \t" << map(2100, 2100) << std::endl;
				std::cout << "test 7 : \t" << map(4200, 4200) << std::endl;
				std::cout << "test 8 : \t" << map(65535, 65535) << std::endl;
				break;
			}
			else
			{
				uint16_t x = input_int('X');
				uint16_t y = input_int('Y');
				std::cout << map(x, y) << std::endl;
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (...)
		{
			std::cerr << "bad_alloc: Wrong memory operator NEW" << std::endl;
		}
	}
	std::cout << "THE END" << std::endl;
	return 0;
}
