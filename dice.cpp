#include "dice.h"

Dice::Dice(void)
{
    this->num_dice = 0;
    this->num_faces = 0;
    this->bonus = NULL;
    this->btype = NONE;
}

Dice::Dice(int num_dice, int num_faces)
{
    this->num_dice = num_dice;
    this->num_faces = num_faces;
    this->bonus = NULL;
    this->btype = NONE;
}

Dice::~Dice()
{
    delete bonus;
}

std::string Dice::str()
{
    std::string out = std::to_string(num_dice) + 'd' + std::to_string(num_faces);
    if (btype)
    {
        if (btype == PLUS)
            out.append('+' + bonus->str());
        if (btype == MINUS)
            out.append('-' + bonus->str());
    }

    return out;
}

int Dice::add_bonus(Dice* bonus, DICE_OP type)
{
    this->btype = type;
    this->bonus = bonus;

    return 0;
}

int Dice::get_dice()
{
    return this->num_dice;
}

int Dice::get_faces()
{
    return this->num_faces;
}

Dice* Dice::get_bonus()
{
    return this->bonus;
}

DICE_OP Dice::get_type()
{
    return this->btype;
}

DICE_OP get_type(const char op)
{
    DICE_OP res = NONE;
    switch (op)
    {
        case '+':
            res = PLUS;
            break;
        case '-':
            res = MINUS;
            break;
        
        default:
            break;
    }

    return res;
}