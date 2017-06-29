#ifndef FUNC_H
#define FUNC_H

#include <string>
#include <vector>

//#define SDL_WIDTH 1920
//#define SDL_HEIGTH 1080

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

enum textQuality { solid, shaded, blended, solid_uni, shaded_uni, blended_uni };

extern bool SDL_ENABLED;
extern bool NCURSES_ENABLED;
extern bool SDL_IMAGE_ENABLED;

extern short unsigned int resx;
extern short unsigned int resy;

extern short unsigned int chx;
extern short unsigned int chy;

extern short unsigned int imgx;
extern short unsigned int imgy;

class func
{
    public:

        func();
        ~func();
        std::vector<std::string> split(std::string str);
        SDL_Surface* SDL_drawText(TTF_Font* font,  Uint8 fgR, Uint8 fgG, Uint8 fgB, Uint8 fgA, Uint8 bgR, Uint8 bgG, Uint8 bgB, Uint8 bgA, char text[], textQuality quality, Uint16* utext = (Uint16*)2022);
        TTF_Font* loadTTF(char* file, int short ptsize);

    protected:

    private:
};

#endif // FUNC_H
