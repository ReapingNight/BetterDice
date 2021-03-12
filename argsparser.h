#pragma once

class Flags
{
    public:
        size_t dice = 0;
        size_t faces = 0;
        int toOne = 0;
        int toAll = 0;
        size_t dc = 0;

};


void parse_args(int argc, char const *argv[]);
