#include "argsparser.h"
#include "roller.h"

#include <iostream>
#include <iterator>
#include <regex>
#include <string>

const std::string s_die = "[0-9]*(d)?[0-9]+";

Dice parse_die(const std::string die)
{
    Dice dice;

    std::string delim = "d";

    dice.numDice = std::stoi(die.substr(0, die.find(delim)));
    dice.numFaces = std::stoi(die.substr(die.find(delim)+1, die.length()));

    return dice;
}

int* parse_dice_roll(const std::string dice)
{
    std::regex re_die(s_die, std::regex_constants::icase);

    std::cout << std::regex_replace(dice, re_die, "[$&]") << std::endl;

    auto dice_begin = std::sregex_iterator(dice.begin(), dice.end(), re_die);
    auto dice_end = std::sregex_iterator();

    Dice prev;
    for (std::sregex_iterator ii = dice_begin; ii != dice_end; ++ii)
    {
        std::smatch match = *ii;
        Dice cur;
        cur = parse_die(match.str());
        if (ii != dice_begin) prev.bonus = &cur;
        prev = cur;
    }

    return NULL;
}

void parse_args(int argc, char const *argv[])
{
    std::regex re_roll("^roll$");
    std::regex re_bonus("^[\\+|-]" + s_die + "$", std::regex_constants::icase);
    std::regex re_dc("^(-)?dc=[0-9]+$", std::regex_constants::icase);

    for ( size_t ii = 0; ii < argc; ++ii)
    {
        if (std::regex_search(argv[ii], re_roll))
            parse_dice_roll(argv[++ii]);
        else if (std::regex_search(argv[ii], re_bonus))
            parse_dice_roll(argv[ii]);
        else if (std::regex_search(argv[ii], re_dc))
            printf("%s match dc\n", argv[ii]);
    }
}