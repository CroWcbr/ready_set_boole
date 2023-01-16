#include "eval_formula.hpp"

bool eval_formula(const std::string &str)
{
	Tree	tree(str);
//	tree.print();
	return tree.result();
}
