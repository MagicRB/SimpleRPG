#ifndef PLAYER_H
#define PLAYER_H

#include <character.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <func.h>

enum look { up, down, left, right, left_down, left_up, right_down, right_up };

class player : public character
{
    public:

        player();
        ~player();

        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx);
        void chmove(int y, int x);
        void renderLook(look lk, TTF_Font* font, SDL_Renderer* renderer, int cy, int cx);


    protected:

        int short reqxp = 100;
        int short xp = 0;

        int lky;
        int lkx;

        func fc;

    private:
};

#endif // PLAYER_H
