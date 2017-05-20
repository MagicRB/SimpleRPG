#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <ncurses.h>


#include <player.h>
//#include <func.h>

//func f;
player pl;

std::string command;

std::vector<std::string> splCommand;

int short num = 0;

short int i;

std::string vstr(std::vector<std::string> v, int short i)
{
    std::string str;
    try
    {
        str = v.at(i);
    }
    catch (const std::out_of_range& e)
    {
        str = "";
    }
    return str;
}

void cmdHp() /// Hp related commands
{
        if (vstr(splCommand, 0) == "hp")
        {
            std::stringstream nstream(vstr(splCommand, 2));
            if (vstr(splCommand, 1) == "add" && nstream >> num)  /// Add player's hp
            {
                    pl.addHp(num);
                    std::cout << "Adding " << num << "HP to your health" << std::endl;
            }
            else if (vstr(splCommand, 1) == "rm" && nstream >> num) /// Rm player's hp
            {
                    pl.rmHp(num);
                    std::cout << "Removing " << num << "HP from your health" << std::endl;
            }
            else if ((vstr(splCommand, 1) == "rm" || vstr(splCommand, 1) == "add") && !(nstream >> num)) /// Check if user entered a number when required
            {
                std::cout << "\"" << vstr(splCommand, 2) << "\" is not a number" << std::endl;
            }
            else if (vstr(splCommand, 1) == "get") /// Get and list player's hp
            {
                std::cout << "You have "<< pl.getHp() << "HP/" << pl.getTotalHp() << "HP" << std::endl;
            }
            else /// If user entered bullcrap
            {
                std::cout << "\"" << vstr(splCommand, 1) << "\" is not a option for \"hp\"" << std::endl;
            }
        }
}

void clearSplCommand()
{
    splCommand.clear();

}

void doCommand()
{
    cmdHp(); /// Check for "hp" commands
}

int main()
{
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, command, '\n');

        std::istringstream stm(command);
        std::string word;
        while (stm >> word)
        {
            splCommand.push_back(word);
        }

        doCommand(); /// Execute received command
        clearSplCommand(); /// Clear splCommand array
    }
    return 0;
}
