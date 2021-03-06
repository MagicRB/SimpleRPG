#include "wall.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncursesw/curses.h>
#else
    #include <ncurses.h>
#endif


wall::wall()
{

}

wall::~wall()
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(img);
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
    renRect.x = (block::x - cx) * chx;
    renRect.y = (block::y - cy) * chy;
    renRect.w = chx;
    renRect.h = chy;

    SDL_RenderCopy(renderer, texture, NULL, &renRect);
}

void wall::init(SDL_Renderer* renderer, TTF_Font* font)
{
    block::player_collide = true;

    if (SDL_ENABLED == true)
    {
        text = fc.SDL_drawText(font, 0x93, 0x81, 0x6du, 0xFF, 0xaa, 0xa3, 0x94, 0x00, "#", shaded);

        texture = SDL_CreateTextureFromSurface(renderer, text);

        SDL_FreeSurface(text);
    }
    if (SDL_IMAGE_ENABLED == true)
    {
        //img = SDL_LoadBMP("data/textures/wall.bmp");

        texture = IMG_LoadTexture(renderer, pathTexture.c_str());//SDL_CreateTextureFromSurface(renderer, img);
        std::cout << pathTexture << std::endl;
    }
}

void wall::IMG_render(SDL_Renderer* renderer, int cy, int cx)
{
	renRect.x = (block::x - cx) * chx;
	renRect.y = (block::y - cy) * chy;
	renRect.w = chx;
	renRect.h = chy;

	SDL_RenderCopy(renderer, texture, NULL, &renRect);
}


