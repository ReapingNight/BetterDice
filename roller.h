#pragma once

#include<iostream>

class Dice
{
    public:
        size_t numDice = 1;
        size_t numFaces = 0;
        Dice* bonus = NULL;
    
        friend std::ostream& operator<<(std::ostream& out, const Dice& dice);
};