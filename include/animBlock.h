#ifndef ANIMBLOCK_H
#define ANIMBLOCK_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncursesw/curses.h>
    #include "windows.h"
#else
    #include <ncurses.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <func.h>

#include <chrono>

#include <iostream>
#include <block.h>


class animBlock : public block
{
    public:
        animBlock();
        ~animBlock();

        char ch = 'a';

        long long int timeDelta = 0;
        long long int currentTime = 80;
        long long int lastTime = 0;

        void render(int cy, int cx);
        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx);
        void setPos(int y, int x);

    protected:

        func fc;

    private:
};

#endif // ANIMBLOCK_H
