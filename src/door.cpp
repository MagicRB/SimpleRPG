#include "door.h"

door::door()
{
    //ctor
}

door::~door()
{
    //dtor
}

void door::SDL_render(SDL_Window* window, SDL_Renderer* renderer, int cy, int cx)
{
    renRect.x = (block::x - cx) * chx;
    renRect.y = (block::y - cy) * chy;
    renRect.w = chx;
    renRect.h = chy;

    SDL_RenderCopy(renderer, texture, NULL, &renRect);
}

void door::render(int cy, int cx)
{
    mvaddch(block::y - cy, block::x - cx, dch);
}

void door::init(SDL_Renderer* renderer, TTF_Font* font)
{
    block::player_collide = true;

    if (SDL_ENABLED == true)
    {
        text = fc.SDL_drawText(font, 0x93, 0x81, 0x6du, 0xFF, 0xaa, 0xa3, 0x94, 0x00, (char*)dch, shaded);

        texture = SDL_CreateTextureFromSurface(renderer, text);

        SDL_FreeSurface(text);
    }
    if (SDL_IMAGE_ENABLED == true)
    {
        //img = SDL_LoadBMP("data/textures/wall.bmp");

        //texture = IMG_LoadTexture(renderer, dimg);//SDL_CreateTextureFromSurface(renderer, img);
    }
}

void door::IMG_render(SDL_Renderer* renderer, int cy, int cx)
{
    texture = IMG_LoadTexture(renderer, dimg.c_str());

	renRect.x = (block::x - cx) * chx;
	renRect.y = (block::y - cy) * chy;
	renRect.w = chx;
	renRect.h = chy;

	SDL_RenderCopy(renderer, texture, NULL, &renRect);
}

void door::setPos(int y, int x)
{
    block::y = y;
    block::x = x;
}

void door::switchState(std::string worldPrefix)
{
    if (NCURSES_ENABLED == true)
    {
        if (open == false)
        {
            dch = '*';
        } else if (open == true)
        {
            dch = '/';
        }
        open = !open;
    }
    if (SDL_IMAGE_ENABLED == true || SDL_ENABLED == true)
    {
        if (open == false)
        {
            dimg = "maps/" + worldPrefix + "/textures/" + "door_open.png";
        } else if (open == true)
        {
            dimg = "maps/" + worldPrefix + "/textures/" + "door_closed.png";
        }
        open = !open;
    }
}
