#include "argsparser.h"

#include <iostream>
#include <regex>
#include <string>

const std::string s_die = "[0-9]*(d)?[0-9]+";

int* parse_dice_roll(const char* dice)
{
    std::regex re_die(s_die, std::regex_constants::icase);

    std::cout << std::regex_replace(dice, re_die, "[$&]") << std::endl;

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