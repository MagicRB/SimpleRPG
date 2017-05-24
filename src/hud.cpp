#include "hud.h"

#include <player.h>

hud::hud()
{
    //ctor
}

hud::~hud()
{
    //dtor
}

void hud::render(player* pl)
{
    char hp[sizeof(pl->getHp())+2];
    snprintf(hp, sizeof hp, "%f", pl->getHp());

    mvaddstr(0, 0, hp);

    char thp[sizeof(pl->getTotalHp())+2];
    snprintf(thp, sizeof thp, "%f",pl->getTotalHp());

    mvaddch(0, sizeof(pl->getHp()) + 1, '/');
    mvaddstr(0, sizeof(pl->getHp()) + 2, thp);
    mvaddstr(0, sizeof(pl->getHp()) + sizeof(pl->getTotalHp()) + 3, "HP");
}

void hud::displayText(std::string str)
{
    unsigned int by = getmaxy(stdscr) / 8;
    unsigned int bx = getmaxx(stdscr) / 8;

    char ch;

    std::string bstr;

    unsigned int l = by;

    for (unsigned i = 0; i < str.length(); i += getmaxx(stdscr) - 2 * bx)
    {
        bstr = str.substr(i, getmaxx(stdscr) - 2 * bx);
        mvaddstr(l + 1,bx + 1, bstr.c_str());
        l++;
    }
    while (ch != 'q')
    {
        ch = getch();
    }
}

void hud::SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, player* pl)
{
    char hp[sizeof(pl->getHp())+2];
    snprintf(hp, sizeof hp, "%f", pl->getHp());

    char thp[sizeof(pl->getTotalHp())+2];
    snprintf(thp, sizeof thp, "%f",pl->getTotalHp());

    SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, hp, shaded);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    SDL_Rect textRect;
    textRect.x = 0;
    textRect.y = 0;
    textRect.w = 7 * sizeof(hp)
    ;
    textRect.h = 14;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}
