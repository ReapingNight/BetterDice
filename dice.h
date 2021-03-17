#pragma once

#include <string>

enum DICE_OP {NONE, PLUS, MINUS};

class Dice
{
    private:
        int num_dice;
        int num_faces;
        Dice* bonus;
        DICE_OP btype;
    public:
        Dice();
        Dice(int num_dice, int num_faces);
        ~Dice();
        std::string str(void);
        int add_bonus(Dice* bonus, DICE_OP type);

        int get_dice(void);
        int get_faces(void);
        Dice* get_bonus(void);
        DICE_OP get_type(void);
};

DICE_OP get_type(const char op);