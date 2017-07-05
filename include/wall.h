#ifndef WALL_H
#define WALL_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncursesw/curses.h>
#else
    #include <ncurses.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include <func.h>

#include <block.h>


class wall : public block
{
    public:
        wall();
        ~wall();

        std::string pathTexture;
        std::string pathTTemplate;

        void render(int cy, int cx);

        void setPos(int y, int x);

        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, int cy, int cx);
        void IMG_render(SDL_Renderer* renderer, int cy, int cx);
        void init(SDL_Renderer* renderer, TTF_Font* font);

    protected:

        func fc;

        SDL_Texture* texture;
        SDL_Surface* img;
        SDL_Surface* text;

    private:

        SDL_Rect renRect;
};

#endif // WALL_H
