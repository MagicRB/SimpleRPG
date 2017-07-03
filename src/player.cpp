#include "player.h"

#if defined(__WINDOWS__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncursesw/curses.h>
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
    renRect.x = (player::x - cx) * chx;
    renRect.y = (player::y - cy) * chy;
    renRect.w = chx;
    renRect.h = chy;

    SDL_RenderCopy(renderer, texture, NULL, &renRect);
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
    textRect.x = (character::x - cx + lkx) * chx;
    textRect.y = (character::y - cy + lky) * chy;
    textRect.w = chx;
    textRect.h = chy;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}

void player::init(SDL_Renderer* renderer, TTF_Font* font)
{
    if (SDL_ENABLED == true)
    {
        text = fc.SDL_drawText(font, 0x93, 0x81, 0x6u, 0xFF, 0xaa, 0xa3, 0x94, 0x00, "@", shaded);

        texture = SDL_CreateTextureFromSurface(renderer, text);

        SDL_FreeSurface(text);
    }
    if (SDL_IMAGE_ENABLED == true)
    {
        img = SDL_LoadBMP("data/textures/smile.bmp");

        texture = SDL_CreateTextureFromSurface(renderer, img);
    }
}

void player::IMG_render(SDL_Renderer* renderer, int cy, int cx)
{
	renRect.x = (player::x - cx) * chx;
	renRect.y = (player::y - cy) * chy;
	renRect.w = chx;
	renRect.h = chy;

	SDL_RenderCopy(renderer, texture, NULL, &renRect);
}
