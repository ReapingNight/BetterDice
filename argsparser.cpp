#include "argsparser.h"

#include <iostream>
#include <regex>
#include <string>

void parse_args(int argc, char const *argv[])
{
    Flags flags;

    std::string s_die = "[0-9]*(d)?[0-9]+";
    std::regex re_roll("^roll$");
    std::regex re_die("^" + s_die + "$", std::regex_constants::icase);
    std::regex re_bonus("^[\\+|-]" + s_die + "$", std::regex_constants::icase);
    std::regex re_dc("^(-)?dc=[0-9]+$", std::regex_constants::icase);

    for ( size_t ii = 0; ii < argc; ++ii)
    {
        if (std::regex_search(argv[ii], re_roll))
            printf("%s match roll\n", argv[ii]);
        else if (std::regex_search(argv[ii], re_bonus))
            printf("%s match bonus\n", argv[ii]);
        else if (std::regex_search(argv[ii], re_dc))
            printf("%s match dc\n", argv[ii]);
    }
}