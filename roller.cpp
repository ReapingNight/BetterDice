#include "roller.h"

std::ostream& operator<<(std::ostream& out, const Dice& dice)
{
    out << dice.numDice << 'd' << dice.numFaces;

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