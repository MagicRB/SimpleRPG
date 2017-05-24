#ifndef HUD_H
#define HUD_H

#include <player.h>
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include <func.h>

class hud
{
    public:
        hud();
        ~hud();

        void render(player* pl);
        void displayText(std::string str, TTF_Font* font, SDL_Renderer* renderer);
        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, player* pl);


    protected:

        func fc;

        SDL_Event event;

    private:
};

#endif // HUD_H
