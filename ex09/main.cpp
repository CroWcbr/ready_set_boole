#include "eval_set.hpp"
#include <iostream>
#include <signal.h>
#include <set>
#include <sstream>

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

static std::string	input_formula()
{
	std::string	input;

	std::cout << "Input formula > ";
	getline(std::cin, input);

	if (std::cin.eof())				//Ctrl + 'D'
		_signal_handler(-1);

	if (input == "quit" || input == "exit")
		exit (0);
	
	return input;
}

static Vec<i32>	_split(std::string const &str, const char &delim)
{
	Vec<i32> tmp_split;

	std::stringstream ss(str);
	std::string item;
	while(std::getline(ss, item, delim))
		tmp_split.push_back(stoi(item));
	return tmp_split;
}

static void	check_input_vector(std::string const &str)
{
	for (size_t i = 0, max = str.size(); i < max; i++)
		if (str[i] != ' ' && (str[i] < '0' || str[i] > '9'))
			throw std::runtime_error("Wrong input : " + str.substr(0, i + 1));
}

static void	check_set(const Vec<i32> &vec_input)
{
	if (vec_input.empty())
		throw std::runtime_error("No element in set");
	if (std::set<i32>(vec_input.begin(), vec_input.end() ).size() != vec_input.size())
		throw std::runtime_error("Duplicated in input vector");
}

static Vec<Vec<i32>>	input_vector(const std::string &input_formula)
{
	std::set<char>	distinct_sets;
	std::string		input;
	Vec<Vec<i32>>	vec_result;
	Vec<i32>		tmp;

	for (const auto &c : input_formula)
		if (c >= 'A' && c <= 'Z')
			distinct_sets.insert(c);

	if (distinct_sets.empty())
		throw std::runtime_error("Formula have not any sets : ");

	for (const auto &c : distinct_sets)
	{
		std::cout << "Input " << c << " set > ";
	 	getline(std::cin, input);

		if (std::cin.eof())				//Ctrl + 'D'
			_signal_handler(-1);
		
		check_input_vector(input);
		tmp = _split(input, ' ');
		check_set(tmp);
		vec_result.push_back(tmp);
	}

	return vec_result;
}

static void	print_input_info(const std::string &input_formula, Vec<Vec<i32>> &vec_print)
{
	std::cout << "-------------" << std::endl;

	std::cout << "Formula :" << std::endl;
	std::cout << "\t" << input_formula << std::endl;
	std::cout << "Sets : " << std::endl;
	for (const auto &tmp : vec_print)
	{
		std::cout << "\t[ ";
		for (const auto &i : tmp)
			std::cout << i << " ";
		std::cout << "]";
		std::cout << std::endl;
	}
	std::cout << "-------------" << std::endl;
}

static void	print_result_vector(Vec<i32> &vec_print)
{
	std::cout << "-------------" << std::endl;
	std::cout << "Result :" << std::endl;
	std::cout << "\t[ ";
	for (const auto &tmp : vec_print)
		std::cout << tmp << " ";
	std::cout << "]";
	std::cout << std::endl;
	std::cout << "-------------" << std::endl;
}

int main()
{
	std::string		formula_input;
	Vec<Vec<i32>>	vector_input;
	Vec<i32>		result;
	bool			test;

	std::cout << "Set evaluation programm" << std::endl;

	signal(SIGINT, _signal_handler);	//Ctrl + 'C'
	signal(SIGQUIT, _signal_handler);	//Ctrl + '\'
	signal(SIGTSTP, _signal_handler);	//Ctrl + 'Z'

	test = 0;
	while (true)
	{
		try
		{
			if (test)
			{
				formula_input = "AB=";
				vector_input =	{
								{0, 1, 2},
								{0, 3, 4}
								};
			}
			else
			{
				formula_input = input_formula();
				vector_input = input_vector(formula_input);
			}
			
			print_input_info(formula_input, vector_input);
			result = eval_set(formula_input, vector_input);
			print_result_vector(result);
			if (test)
				break;
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
