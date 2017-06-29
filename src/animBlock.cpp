#include "animBlock.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <chrono>

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
    auto time = std::chrono::system_clock::now();

    auto since_epoch = time.time_since_epoch();

    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);

    currentTime = millis.count();

    timeDelta = currentTime - lastTime;

    if (timeDelta >= 1000)
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
    auto time = std::chrono::system_clock::now();

    auto since_epoch = time.time_since_epoch();

    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);

    currentTime = millis.count();

    timeDelta = currentTime - lastTime;

    std::cout << timeDelta << std::endl;

    if (timeDelta >= 1000)
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
    SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, &ch, shaded);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    SDL_Rect textRect;
    textRect.x = (block::x - cx) * chx;
    textRect.y = (block::y - cy) * chy;
    textRect.w = chx;
    textRect.h = chy;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
}

void animBlock::setPos(int y, int x)
{
            block::y = y;
            block::x = x;
}
