#include "die.h"

Die::Die()
{
    this->faces = 0;
    this->roll = 0;
    this->rolled = std::vector<int>();
}

Die::Die(int faces)
{
    this->faces = faces;
    this->roll = 0;
    this->rolled = std::vector<int>();
}

Die::~Die() 
{ 
    rolled.clear();
}

std::string Die::str()
{
    std::string res;

    if (rolled.size() > 1)
    {
        res += "(";

        for (int ii : rolled)
        {
            res += std::to_string(ii) + ",";
        }
        res.pop_back();

        res += ")";
    }
    else if (rolled.size() > 0)
    {
        res += std::to_string(rolled.front());
    }

    return res;
}

std::vector<int> Die::roll_die(int (*rand)(void), const int adv)
{
    rolled.clear();

    int ii = abs(adv);

    while (ii >= 0)
    {
        rolled.push_back(rand() % faces + 1);
        --ii;
    }

    if (adv)
    {
        roll = *((adv > 0) ? std::max_element(rolled.begin(), rolled.end()) : std::min_element(rolled.begin(), rolled.end()));
    }

    return rolled;
}
