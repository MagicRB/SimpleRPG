#ifndef ANIMBLOCK_H
#define ANIMBLOCK_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/curses.h>
#else
    #include <ncurses.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <func.h>

#include <iostream>
#include <block.h>
#include <sys/time.h>

class animBlock : public block
{
    public:
        animBlock();
        ~animBlock();

        timeval tv;

        char ch = 'a';

        int timeDelta = 0;
        int currentTime = 80;
        int lastTime = 0;

        void render(int cy, int cx);
        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx);
        void setPos(int y, int x);

    protected:

        func fc;

    private:
};

#endif // ANIMBLOCK_H
