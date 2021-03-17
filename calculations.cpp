#include "calculations.h"

std::vector<int> apply_to_hit(const std::vector<int> rolls, int bonus)
{
    int n = rolls.size();

    std::vector<int> res = std::vector<int>();
    res.reserve(n);

    for (size_t ii = 0; ii < n - 1; ++ii)
        res.push_back(rolls.at(ii) + bonus);
    
    res.push_back(rolls.back());

    return res;
}

std::vector<int> filter(const std::vector<int> rolls, int dc)
{
    size_t n = rolls.size();
    std::vector<int> res = std::vector<int>();
    res.reserve(n);
    size_t size = 1;

    for (size_t ii = 0; ii < n-1; ++ii)    
    {
        int cur = rolls.at(ii);

        if (cur >= dc)
        {
            res.push_back(cur);
            size++;
        }
    }
    res.push_back(rolls.back());
    res.resize(size);

    return res;    
}

int sum_dice(std::vector<int> rolls)
{
    return std::accumulate(rolls.begin(), rolls.end(), 0);
}