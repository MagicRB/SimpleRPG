#include "player.h"

#if defined(__WINDOWS__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/curses.h>
#else
    #include <ncurses.h>
#endif


player::player()
{
    //ctor
}

player::~player()
{
    //dtor
}

void player::SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx)
{
    SDL_Surface* text = fc.SDL_drawText(font, 0x83, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, "@", shaded);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    SDL_Rect textRect;
    textRect.x = (character::x - cx) * 7;
    textRect.y = (character::y - cy) * 14;
    textRect.w = 7;
    textRect.h = 14;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}

void player::chmove(int y, int x)
{
    character::y = y;
    character::x = x;
}

void character::render(int cy, int cx)
{
    mvaddch(character::y - cy, character::x - cx, '@');
}

void player::renderLook(look lk, TTF_Font* font, SDL_Renderer* renderer, int cy, int cx)
{
    SDL_Surface* text = fc.SDL_drawText(font, 0xCF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, "-", solid, (Uint16*)2022);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    if (lk == down)
    {
        lky = 1;
        lkx = 0;
    } else if (lk == up)
    {
        lky = -1;
        lkx = 0;
    } else if (lk == left)
    {
        lky = 0;
        lkx = -1;
    } else if (lk == right)
    {
        lky = 0;
        lkx = 1;
    } else if (lk == left_down)
    {
        lky = 1;
        lkx = -1;
    } else if (lk == left_up)
    {
        lky = -1;
        lkx = -1;
    } else if (lk == right_down)
    {
        lky = 1;
        lkx = 1;
    } else if (lk == right_up)
    {
        lky = -1;
        lkx = 1;
    }

    SDL_Rect textRect;
    textRect.x = (character::x - cx + lkx) * 7;
    textRect.y = (character::y - cy + lky) * 14;
    textRect.w = 7;
    textRect.h = 14;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}
