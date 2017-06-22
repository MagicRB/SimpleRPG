#include "wall.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/curses.h>
#else
    #include <ncurses.h>
#endif


wall::wall()
{

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

void wall::SDL_render(SDL_Window* window, SDL_Renderer* renderer, int cy, int cx)
{
    SDL_Rect textRect;
    textRect.x = (block::x - cx) * chx;
    textRect.y = (block::y - cy) * chy;
    textRect.w = chx;
    textRect.h = chy;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

void wall::init(SDL_Renderer* renderer, TTF_Font* font)
{
    block::player_collide = true;

    if (SDL_ENABLED == true)
    {
        text = fc.SDL_drawText(font, 0x93, 0x81, 0x6du, 0xFF, 0xaa, 0xa3, 0x94, 0x00, "#", shaded);

        textTexture = SDL_CreateTextureFromSurface(renderer, text);

        SDL_FreeSurface(text);
    }
    if (SDL_IMAGE_ENABLED == true)
    {
        img = IMG_LoadTexture(renderer, "smile.png");
    }
}

void wall::IMG_render(SDL_Renderer* renderer, int cy, int cx)
{
	SDL_Rect texr;
	texr.x = (block::x - cx) * 7;
	texr.y = (block::y - cy) * 14;
	texr.w = 7;
	texr.h = 14;

	SDL_RenderCopy(renderer, img, NULL, &texr);
}


