#include "func.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

func::func()
{
    //ctor
}

func::~func()
{
    //dtor
}

std::vector<std::string> func::split(std::string str) {
    std::stringstream ss(str);

    int i = 0;

    std::vector<std::string> strv;

    std::string token;
    while (ss >> str)
    {
        std::cout << token << std::endl;
        i++;
    }
    return strv;
}
