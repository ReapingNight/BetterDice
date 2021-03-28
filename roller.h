#pragma once

#include "dice.h"

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <numeric>
#include <algorithm>

std::vector<int> roll(Dice* dice, const int adv = 0);
int roll_bonus(Dice* dice, DICE_OP op);