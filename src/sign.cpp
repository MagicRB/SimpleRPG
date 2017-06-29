#include "sign.h"

sign::sign()
{
    //ctor
}

sign::~sign()
{
    //dtor
}

void sign::render(int cy, int cx)
{
    mvaddch(block::y - cy, block::x - cx, 'S');
}

void sign::SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx)
{
    SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, "S", shaded);

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

void sign::setPos(int y, int x)
{
    block::y = y;
    block::x = x;
}

void sign::setText(std::string str)
{
    text = str;
}

void sign::read(hud* hud_o, TTF_Font* font, SDL_Renderer* renderer)
{
    hud_o->displayText(text, font, renderer);
}
