#include "door.h"

door::door()
{
    //ctor
}

void door::render(int cy, int cx)
{
    mvaddch(block::y - cy, block::x - cx, dch);
}

void door::SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx)
{
    SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, &dch, shaded);

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

    void door::setPos(int y, int x)
    {
        block::y = y;
        block::x = x;
    }



door::~door()
{
    //dtor
}
