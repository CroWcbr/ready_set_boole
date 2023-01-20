#include "conjunctive_normal_form.hpp"

std::string conjunctive_normal_form(const std::string &str)
{
	Tree	tree(str);

	return tree.conjunctive_normal_form();
}
