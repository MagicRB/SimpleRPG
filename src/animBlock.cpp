#include "animBlock.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <func.h>

animBlock::animBlock()
{
    //ctor
}

animBlock::~animBlock()
{
    //dtor
}

void animBlock::render(int cy, int cx)
{
    gettimeofday (&tv, NULL);
    currentTime = (tv.tv_sec) + 0.000001 * tv.tv_usec;

    timeDelta = currentTime - lastTime;

    if (timeDelta >= 1)
    {
        if (ch == 'a')
        {
            ch = 'b';
        } else
        {
            ch = 'a';
        }
        lastTime = currentTime;
    }
    mvaddch(block::y - cy, block::x - cx, ch);
}

void animBlock::SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx)
{
    SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, &ch, shaded);

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

void animBlock::setPos(int y, int x)
{
            block::y = y;
            block::x = x;
}
