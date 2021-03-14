#include "roller.h"

std::ostream& operator<<(std::ostream& out, const Dice& dice)
{
    out << dice.numDice << 'd' << dice.numFaces;
    // if (dice.btype) out << (dice.btype == PLUS) ? "+" : "-";

    return out;
}

void Dice::free(Dice * die)
{
    if (!die) return;

    Dice * temp = die;
    while (temp)
    {
        temp = die->bonus;
        free(die);
    }
}