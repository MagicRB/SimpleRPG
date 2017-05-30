#include "mapPortal.h"

mapPortal::mapPortal()
{
    //ctor
}

mapPortal::~mapPortal()
{
    //dtor
}

void mapPortal::setPos(int y, int x)
{
    block::y = y;
    block::x = x;
}

void mapPortal::SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx)
{
    SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0x5C, 0x1C, 0xFF, 0x00, 0x00, 0x00, 0x00, "O", shaded);

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

char* mapPortal::loadMap()
{
    return obj_map;
}

void mapPortal::setMap(char* strr)
{
    obj_map = strr;
}




