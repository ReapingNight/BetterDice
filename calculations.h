#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

std::vector<int> apply_to_hit(const std::vector<int> rolls, int bonus);
std::vector<int> filter(const std::vector<int> rolls, int dc);
int sum_dice(const std::vector<int> rolls);