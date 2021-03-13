#include "roller.h"

std::ostream& operator<<(std::ostream& out, const Dice& dice)
{
    out << dice.numDice << 'd' << dice.numFaces;

    return out;
}