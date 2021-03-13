#pragma once

#include<iostream>

class Dice
{
    public:
        size_t numDice = 0;
        size_t numFaces = 0;
        Dice* bonus = NULL;
    
        friend std::ostream& operator<<(std::ostream& out, const Dice& dice);
        static void free(Dice * die);
};