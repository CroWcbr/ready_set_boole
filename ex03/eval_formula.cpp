#include "eval_formula.hpp"
#include "tree.hpp"
#include <iostream>

bool eval_formula(const std::string &str)
{
	Tree	tree(str);
//	tree.print();
	return tree.result();
}
