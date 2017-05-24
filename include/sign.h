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

        void render(int cy, int cx);

        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx);

        void setPos(int y, int x);

        void setText(std::string str);

        void read(hud* hud_o, TTF_Font* font, SDL_Renderer* renderer);

    protected:

        func fc;

    private:
};

#endif // SIGN_H
