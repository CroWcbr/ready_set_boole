#include "negation_normal_form.hpp"

std::string negation_normal_form(const std::string &str)
{
	Tree	tree(str);

	return tree.negation_normal_form();
}
