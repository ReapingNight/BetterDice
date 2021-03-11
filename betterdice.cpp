#include <iostream>
#include <string>
#include <regex>

int main(int argc, char const *argv[])
{
    if (argc < 2) exit(1);

    const std::string pattern = "^[0-9]*(d)?[0-9]+([\\+|-][0-9]+)?$";

    std::regex word_regex(pattern);

    if (std::regex_search(argv[1], word_regex))
    {
        std::cout << argv[1] << " matches " << pattern << std::endl;
    }
    else
    {
        std::cout << argv[1] << " no " << pattern << std::endl;
    }    

    return 0;
}
