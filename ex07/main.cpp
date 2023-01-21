#include "sat.hpp"
#include <iostream>
# include <signal.h>

void _signal_handler(int signal)
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

int main()
{
	std::string	input;

	std::cout << "Boolean evaluation" << std::endl;

	signal(SIGINT, _signal_handler);	//Ctrl + 'C'
	signal(SIGQUIT, _signal_handler);	//Ctrl + '\'
	signal(SIGTSTP, _signal_handler);	//Ctrl + 'Z'

	while (true)
	{
		std::cout << "> ";
		getline(std::cin, input);

		if (std::cin.eof())				//Ctrl + 'D'
		_signal_handler(-1);

		if (input == "quit" || input == "exit")
			break;

		try
		{
			std::cout << sat(input) << std::endl;
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
