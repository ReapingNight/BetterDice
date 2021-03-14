#include "argsparser.h"
#include "roller.h"

const std::string s_die = "[0-9]*(d)?[0-9]+";

Dice * parse_die(const std::string die)
{
    Dice * dice = (Dice*) calloc(1, sizeof(Dice*));
    if (!dice) exit(ENOMEM);

    std::string delim = "d";

    size_t pos = die.find(delim);

    if (pos != std::string::npos)
    {
        if (pos != 0) dice->numDice = std::stoi(die.substr(0, pos));
        else dice->numDice = 1;

        dice->numFaces = std::stoi(die.substr(pos+1, die.length()));
    }
    else
    {
        dice->numDice = 0;
        dice->numFaces = std::stoi(die.substr(0, die.length()));
    }

    dice->bonus = NULL;
    dice->btype = NONE;

    return dice;
}


// THIS SHIT BUGGY AF?!?
int* parse_dice_roll(const std::string dice)
{
    std::regex re_die(s_die, std::regex_constants::icase);

    std::string ops = std::regex_replace(dice, re_die, "");

    auto dice_begin = std::sregex_iterator(dice.begin(), dice.end(), re_die);
    auto dice_end = std::sregex_iterator();

    Dice * die = NULL;
    Dice * temp = NULL;
    int t = 0;

    for (std::sregex_iterator ii = dice_begin; ii != dice_end; ++ii)
    {
        std::smatch match = *ii;
        std::cout << " - " << match.str() << std::endl;
        Dice * cur = parse_die(match.str());
        if (!t++) die = cur;
        else temp->bonus = cur;
        temp = cur;
    }

    temp = die;
    while (temp)
    {
        std::cout << *die << std::endl;
        temp = temp->bonus;
    }

    std::cout << "gonna do stuff" << std::endl;

    temp = die;
    std::cout << ops.length() << std::endl;
    for (size_t ii = 0; ii < ops.length(); ++ii)
    {
        switch (ops[ii])
        {
            case '+':
                std::cout << "Found a plus" << std::endl;
                temp->btype = PLUS;
                break;
            case '-':
                std::cout << "Found a minus" << std::endl;
                temp->btype = MINUS;
            
            default:
                break;
        }

        temp = temp->bonus;
    }

    std::cout << "FUCK" << std::endl;

    while (die)
    {
        std::cout << *die << std::endl;
        die = die->bonus;
    }

    die->free(die);
    free(die);

    std::cout.flush();

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