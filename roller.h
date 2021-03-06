#pragma once

#include "dice.h"

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <numeric>

std::vector<int> roll(Dice* dice);
int roll_bonus(Dice* dice, DICE_OP op);