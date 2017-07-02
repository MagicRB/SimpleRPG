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

void hud::displayText(std::string str, TTF_Font* font, SDL_Renderer* renderer)
{
    if (NCURSES_ENABLED == true)
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
    else if (SDL_ENABLED == true)
    {
        unsigned int by = resy / 8;
        unsigned int bx = resx / 8;

        std::string bstr;

        unsigned int l = by / chx;

        for (unsigned i = 0; i < str.length(); i += (resx - 2 * bx) / 7)
        {
            bstr = str.substr(i, (resx - 2 * bx) / chx);

            char *cstr = new char[bstr.length() + 1];
            strcpy(cstr, bstr.c_str());

            SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, cstr, shaded);

            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

            SDL_FreeSurface(text);

            SDL_Rect textRect;
            textRect.x = 1 * bx;
            textRect.y = 0 + l * chy;
            textRect.w = chx * bstr.length();
            textRect.h = chy;

            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

            SDL_DestroyTexture(textTexture);
            l++;
        }

        SDL_RenderPresent(renderer);

        SDL_PollEvent(&event);

        SDL_FlushEvent(SDL_KEYDOWN);

        while (event.key.keysym.sym != SDLK_q && event.type != SDLK_DOWN)
        {
            SDL_PollEvent(&event);
            gettimeofday (&tv, NULL);
            currentTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;

            timeDelta = currentTime - lastTime;
            if (timeDelta >= 20)
            {
                lastTime = currentTime;
                SDL_RenderPresent(renderer);
            }
        }
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
    textRect.w = chx * sizeof(hp);
    textRect.h = chy;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}
