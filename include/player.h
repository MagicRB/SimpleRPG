#ifndef PLAYER_H
#define PLAYER_H

#include <character.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <func.h>

class player : public character
{
    public:

        player();
        ~player();

        void SDL_render(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, int cy, int cx)
        {
            SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, "@", shaded);

            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

            SDL_FreeSurface(text);

            SDL_Rect textRect;
            textRect.x = (character::x - cx) * 7;
            textRect.y = (character::y - cy) * 14;
            textRect.w = 7;
            textRect.h = 14;

            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

            SDL_DestroyTexture(textTexture);
        }

        void chmove(int y, int x)
        {
            character::y = y;
            character::x = x;
        }
    protected:

        int short reqxp = 100;
        int short xp = 0;

        func fc;

    private:
};

#endif // PLAYER_H
