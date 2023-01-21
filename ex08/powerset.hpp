#pragma once

#include <string>
#include <vector>
#include <stdint.h>

#define vec		std::vector
#define i32		int32_t

vec<vec<i32>>	powerset(vec<i32> &input);
