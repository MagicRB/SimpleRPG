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
        void IMG_render(SDL_Renderer* renderer, int cy, int cx);
        void init(SDL_Renderer* renderer, TTF_Font* font);
        void chmove(int y, int x);
        void renderLook(look lk, TTF_Font* font, SDL_Renderer* renderer, int cy, int cx);

        int lky;
        int lkx;

    protected:

        SDL_Texture* texture;
        SDL_Surface* img;
        SDL_Surface* text;


        int short reqxp = 100;
        int short xp = 0;

        func fc;

    private:

        SDL_Rect renRect;
};

#endif // PLAYER_H
