#ifndef SIGN_H
#define SIGN_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <func.h>

#include <block.h>

#include <hud.h>
#include <string>

class sign : public block
{
    public:
        sign();
        ~sign();

        std::string text;

        void render(int cy, int cx)
        {
            mvaddch(block::y - cy, block::x - cx, 'S');
        }

        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx)
        {
            SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, "S", shaded);

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

        void setPos(int y, int x)
        {
            block::y = y;
            block::x = x;
        }

        void setText(std::string str)
        {
            text = str;
        }

        void read(hud* hud_o)
        {
            hud_o->displayText(text);
        }

    protected:

        func fc;

    private:
};

#endif // SIGN_H
