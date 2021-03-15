#include "argsparser.h"

const std::string s_die = "[0-9]*(d)?[0-9]+";

Dice* parse_die(const std::string die)
{
    int num_d = 0;
    int num_f = 0;

    std::string delim = "d";

    size_t pos = die.find(delim);

    if (pos != std::string::npos)
    {
        if (pos != 0) num_d = std::stoi(die.substr(0, pos));
        else num_d = 1;

        num_f = std::stoi(die.substr(pos+1, die.length()));
    }
    else
    {
        num_d = 0;
        num_f = std::stoi(die);
    }

    Dice * dice = new Dice(num_d, num_f);

    return dice;
}

int* parse_dice_roll(const std::string dice)
{
    std::regex re_die(s_die, std::regex_constants::icase);

    std::string ops = std::regex_replace(dice, re_die, "");

    auto dice_begin = std::sregex_iterator(dice.begin(), dice.end(), re_die);
    auto dice_end = std::sregex_iterator();

    Dice * die = NULL;
    Dice * temp = NULL;
    int t = 0;
    size_t jj = 0;

    for (std::sregex_iterator ii = dice_begin; ii != dice_end; ++ii)
    {
        std::smatch match = *ii;
        Dice * cur = parse_die(match.str());
        if (!t++) die = cur;
        else 
        {
            DICE_OP type = get_type(ops.at(jj++));
            temp->add_bonus(cur, type);
        }
        temp = cur;
    }

    std::cout << die->str() << std::endl;

    delete die;

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