#include "argsparser.h"

const std::string s_die = "[0-9]*(d)?[0-9]+";

/**
 * Parse a std::string representation of a singular die into a Dice object
 * 
 * @param die std::string representation of a die without any bonusses.
 * @return Pointer to the Dice object equivalent of the input string.
 */
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

/**
 * Parse a std::string representation of dice roll into Dice object
 * 
 * @param dice std::string representation of dice roll.
 * @return Pointer to the Dice object equivalent of the input string.
 */
Dice * parse_dice_roll(const std::string dice)
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
        Dice * cur = parse_die((*ii).str());
        if (!t++) die = cur;
        else 
        {
            DICE_OP type = get_type(ops.at(jj++));
            temp->add_bonus(cur, type);
        }
        temp = cur;
    }

    return die;
}

/**
 * Parse the std::string representation of the dc to an int
 * 
 * @param dc std::string representation of the dc.
 * @return integer representation of the dc.
 */
int parse_dc(const std::string dc)
{
    std::regex re_num("[0-9]+");

    auto num_begin = std::sregex_iterator(dc.begin(), dc.end(), re_num);
    std::string s = (*num_begin).str();

    char * num = &s[0];

    return std::atoi(num);
}

void parse_args(int argc, char const *argv[])
{
    std::regex re_roll("^roll$");
    std::regex re_bonus("^[\\+|-]" + s_die + "$", std::regex_constants::icase);
    std::regex re_dc("^(-)?dc=[0-9]+$", std::regex_constants::icase);
    std::regex re_adv("^(-)?a$", std::regex_constants::icase);
    std::regex re_dis("^(-)?d$", std::regex_constants::icase);

    std::vector<int> rolls;
    Dice * dice = NULL;
    int bonus = 0;
    size_t dc = 0;
    int sum = 0;
    int adv = 0;

    // Parse individual arguments
    for ( size_t ii = 0; ii < argc; ++ii)
    {
        if (std::regex_search(argv[ii], re_roll))
        {
            // roll
            dice = parse_dice_roll(argv[++ii]);
        }
        else if (std::regex_search(argv[ii], re_bonus))
        {
            // +[n]d[n]
            Dice * die = parse_die(argv[ii]);
            DICE_OP op = PLUS;
            if (argv[ii][0] == '-') op = MINUS;
            bonus += roll_bonus(die, op);
        }
        else if (std::regex_search(argv[ii], re_dc))
        {
            // -dc=[n]
            dc = parse_dc(argv[ii]);
        }
        else if (std::regex_search(argv[ii], re_adv))
        {
            // -adv
            adv = 1;
        }
        else if (std::regex_search(argv[ii], re_dis))
        {
            // -dis
            adv = -1;
        }
        else std::cout << "Unknown argument: " << argv[ii] << std::endl;
    }

    // Roll (with advantage or disadvantage)
    rolls = roll(dice, adv);
    delete dice;

    // Add to hit
    if (bonus) rolls = apply_to_hit(rolls, bonus);

    // Apply dc
    if (dc) rolls = filter(rolls, dc);
    
    sum = sum_dice(rolls);

    // PRINTIN
    std::cout << '[';
    if (rolls.size() > 1)
    {
        for (size_t ii = 0; ii < rolls.size() - 2; ++ii) std::cout << rolls[ii] << ", ";
        std::cout << rolls[rolls.size()-2];
    }
    else
    {
        std::cout << 0;
    }
    std::cout << ']' << std::endl;
    std::cout << '[' << rolls.size() - 1 << "] - [" << sum << ']' << std::endl;
}