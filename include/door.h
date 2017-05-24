#ifndef DOOR_H
#define DOOR_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/curses.h>
#else
    #include <ncurses.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <func.h>

#include <block.h>


class door : public block
{
    public:
        door();
        ~door();

        bool open = false;
        char dch = '/';

        void render(int cy, int cx);
        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx);
        void setPos(int y, int x);

        void switchState()
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

    protected:

        func fc;

    private:
};

#endif // DOOR_H
