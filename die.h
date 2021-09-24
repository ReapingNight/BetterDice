#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

class Die
{
    private:
        int faces;
        int roll;
        std::vector<int> rolled;
    public:
        Die();
        Die(int faces);
        ~Die();
        std::string str(void);
        std::vector<int> roll_die(int (*rand)(void), const int adv);
};