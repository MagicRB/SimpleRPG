#include "func.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

bool SDL_ENABLED = true;
bool NCURSES_ENABLED = false;

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

 TTF_Font* func::loadTTF(char* file, int short ptsize)
{
    TTF_Font* tmpFont;
    tmpFont = TTF_OpenFont(file, ptsize);
    if (tmpFont == NULL)
    {

    }
    return tmpFont;
}

SDL_Surface* func::SDL_drawText(TTF_Font* font,  Uint8 fgR, Uint8 fgG, Uint8 fgB, Uint8 fgA, Uint8 bgR, Uint8 bgG, Uint8 bgB, Uint8 bgA, char text[], textQuality quality)
{
    SDL_Color tmpFontColor = {fgR,fgG,fgB,fgA};
    SDL_Color tmpfontBGColor = {bgR, bgG, bgB, bgA};

    SDL_Surface* resText;

    if (quality == solid)
    {
        resText = TTF_RenderText_Solid(font, text, tmpFontColor);
    } else if (quality == shaded)
    {
        resText = TTF_RenderText_Shaded(font, text, tmpFontColor, tmpfontBGColor);
    } else if (quality == blended)
    {
        resText = TTF_RenderText_Blended(font, text, tmpFontColor);
    }

    return resText;
}
