#include "roller.h"

int roll_bonus(Dice* dice, DICE_OP op)
{
    if (!op) return 0;

    std::vector<int> cur = roll(dice);
    int bonus = std::accumulate(cur.begin(), cur.end(), 0);

    if (dice->get_type()) bonus += roll_bonus(dice->get_bonus(), dice->get_type());

    return (op == MINUS) ? -bonus : bonus;
}

std::vector<int> roll(Dice* dice)
{
    srand(time(NULL));

    size_t num_d = dice->get_dice();
    size_t num_f = dice->get_faces();

    std::vector<int> rolls = std::vector<int>();
    rolls.reserve(num_d+1);

    if (num_d)
        for (size_t ii = 0; ii < num_d; ++ii)
            rolls.push_back(rand() % num_f + 1);
    else
        rolls.push_back(num_f);

    rolls.push_back(roll_bonus(dice->get_bonus(), dice->get_type()));

    return rolls;
}