#pragma once

#include "tree.hpp"
#include <string>
#include <vector>

#define Vec		std::vector
#define i32		int32_t

Vec<i32>	eval_set(const std::string &str, Vec<Vec<i32>> &vector_input);
