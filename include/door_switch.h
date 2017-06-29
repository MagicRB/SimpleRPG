#ifndef DOOR_SWITCH_H
#define DOOR_SWITCH_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncursesw/curses.h>
#else
    #include <ncurses.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <func.h>

#include <block.h>


class door_switch : public block
{
    public:
        door_switch();
        ~door_switch();

        int dy;
        int dx;

        void render(int cy, int cx)
        {
            mvaddch(block::y - cy, block::x - cx, '+');
        }

        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx)
        {
            SDL_Surface* text = fc.SDL_drawText(font, (Uint8)0xFF, (Uint8)0xFF, (Uint8)0xFF, (Uint8)0xFF, (Uint8)0x00, (Uint8)0x00, (Uint8)0x00, (Uint8)0x00, (char*)"+", shaded);

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

        void setPos(int y, int x, int dyr, int dxr)
        {
            block::y = y;
            block::x = x;
            dy = dyr;
            dx =dxr;
        }

    protected:

        func fc;

    private:
};

#endif // DOOR_SWITCH_H
