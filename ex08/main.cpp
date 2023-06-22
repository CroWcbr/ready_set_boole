#include "powerset.hpp"
#include <iostream>
#include <signal.h>
#include <sstream>
#include <set>

static void _signal_handler(int signal)
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

static void	check_input(std::string const &str)
{
	for (size_t i = 0, max = str.size(); i < max; i++)
		if (str[i] != ' ' && (str[i] < '0' || str[i] > '9'))
			throw std::runtime_error("Wrong input : " + str.substr(0, i + 1));
}

static vec<i32> _split(std::string const &str, const char &delim)
{
	vec<i32> tmp_split;

	std::stringstream ss(str);
	std::string item;
	while(std::getline(ss, item, delim))
		tmp_split.push_back(stoi(item));
	return tmp_split;
}

static void	check_set(const vec<i32> &vec_input)
{
	// if (vec_input.empty())
	// 	throw std::runtime_error("No element in set");
	if (std::set<i32>(vec_input.begin(), vec_input.end() ).size() != vec_input.size())
		throw std::runtime_error("Duplicated in input vector");
}

static void print_powerser(vec<vec<i32>> &vec_result)
{
	for (const auto &tmp : vec_result)
	{
		std::cout << "\t[ ";
		for (const auto &i : tmp)
			std::cout << i << " ";
		std::cout << "]";
		std::cout << std::endl;
	}
}

int main()
{
	std::string		input;
	vec<i32>		vec_input;
	vec<vec<i32>>	vec_result;

	std::cout << "Powerset - Enter int with a space" << std::endl;

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
			check_input(input);
			vec_input = _split(input, ' ');
			check_set(vec_input);
			vec_result = powerset(vec_input);
			print_powerser(vec_result);
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
