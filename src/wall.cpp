#include "wall.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/curses.h>
#else
    #include <ncurses.h>
#endif


wall::wall()
{
    block::player_collide = true;
}

wall::~wall()
{
    //dtor
}

void wall::render(int cy, int cx)
{
    mvaddch(block::y - cy, block::x - cx, '#');
}

void wall::setPos(int y, int x)
{
    block::y = y;
    block::x = x;
}

void wall::SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx)
{
    SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, "#", shaded);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    SDL_Rect textRect;
    textRect.x = (block::x - cx) * 7;
    textRect.y = (block::y - cy) * 14;
    textRect.w = 7;
    textRect.h = 14;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}
