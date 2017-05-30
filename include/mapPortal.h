#ifndef MAPPORTAL_H
#define MAPPORTAL_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/curses.h>
#else
    #include <ncurses.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <fstream>
#include <string>

#include <hud.h>
#include <func.h>

#include <block.h>

class mapPortal : public block
{
    public:
        mapPortal();
        ~mapPortal();

        void setPos(int y, int x);

        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx);

        char* loadMap();

        void setMap(char*);

        char* obj_map;

    protected:

        func fc;

    private:
};

#endif // MAPPORTAL_H
