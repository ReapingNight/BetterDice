#pragma once

#include<iostream>

enum DICE_OP {NONE, PLUS, MINUS};

class Dice
{
    public:
        size_t numDice = 0;
        size_t numFaces = 0;
        Dice* bonus = NULL;
        DICE_OP btype = NONE;
    
        friend std::ostream& operator<<(std::ostream& out, const Dice& dice);
        void free(Dice * die);
};