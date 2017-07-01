#include "func.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include <fstream>

#include <chrono>

bool SDL_ENABLED = true;
bool SDL_IMAGE_ENABLED = false;
bool NCURSES_ENABLED = false;

short unsigned int resx = 384;
short unsigned int resy = 216;

extern short unsigned int chx = 14;
extern short unsigned int chy = 28;

extern short unsigned int imgx = 10;
extern short unsigned int imgy = 10;

func::func()
{
    //ctor
}

func::~func()
{
    SDL_FreeSurface(text);
    SDL_DestroyTexture(textTexture);
}

std::vector<std::string> func::split(std::string str) {
    std::stringstream ss(str);

    int i = 0;

    std::vector<std::string> strv;

    std::string token;
    while (ss >> str)
    {
        std::cout << token << std::endl;
        i++;
    }
    return strv;
}

 TTF_Font* func::loadTTF(char* file, int short ptsize)
{
    TTF_Font* tmpFont;
    tmpFont = TTF_OpenFont(file, ptsize);
    if (tmpFont == NULL)
    {

    }
    return tmpFont;
}

SDL_Surface* func::SDL_drawText(TTF_Font* font,  Uint8 fgR, Uint8 fgG, Uint8 fgB, Uint8 fgA, Uint8 bgR, Uint8 bgG, Uint8 bgB, Uint8 bgA, char text[], textQuality quality, Uint16* utext)
{
    SDL_Color tmpFontColor = {fgR,fgG,fgB,fgA};
    SDL_Color tmpfontBGColor = {bgR, bgG, bgB, bgA};

    SDL_Surface* resText;

    if (quality == solid)
    {
        resText = TTF_RenderText_Solid(font, text, tmpFontColor);
    } else if (quality == shaded)
    {
        resText = TTF_RenderText_Shaded(font, text, tmpFontColor, tmpfontBGColor);
    } else if (quality == blended)
    {
        resText = TTF_RenderText_Blended(font, text, tmpFontColor);
    }
        if (quality == solid_uni)
    {
        resText = TTF_RenderUNICODE_Solid(font, utext, tmpFontColor);
    } else if (quality == shaded_uni)
    {
        resText = TTF_RenderUNICODE_Shaded(font, utext, tmpFontColor, tmpfontBGColor);
    } else if (quality == blended_uni)
    {
        resText = TTF_RenderUNICODE_Blended(font, utext, tmpFontColor);
    }

    return resText;
}

std::string func::textInputDialog(std::string str, unsigned int x, unsigned int y, TTF_Font* font, SDL_Renderer* renderer, SDL_Event* event, void (*function)(bool present))
{
    long long int timeDelta = 0;
    long long int currentTime = 80;
    long long int lastTime = 0;

    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());

    text = SDL_drawText(font, 0xff, 0xff, 0xff, 0xFF, 0x00, 0x00, 0x00, 0x00, cstr, shaded);

    textTexture = SDL_CreateTextureFromSurface(renderer, text);

    renRect.x = (resx / 8);
    renRect.y = (resy / 8);
    renRect.w = chx * str.length();
    renRect.h = chy;

    SDL_RenderCopy(renderer, textTexture, NULL, &renRect);

    SDL_StartTextInput();

    std::string istr = "";

    SDL_Delay(60);

    while (!(event->key.keysym.sym == SDLK_RETURN))
    {
        auto time = std::chrono::system_clock::now();

        auto since_epoch = time.time_since_epoch();

        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);

        currentTime = millis.count();

        timeDelta = currentTime - lastTime;

        if (timeDelta >= 20)
        {
            if (SDL_PollEvent(event))
            {
                if (event->type == SDL_KEYDOWN)
                {
                    //Handle backspace
                    if (event->key.keysym.sym == SDLK_BACKSPACE && istr.length() > 0)
                    {
                        //lop off character
                        istr.erase(istr.size()-1);
                    }
                    //Handle copy
                    else if (event->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                    {
                        SDL_SetClipboardText(istr.c_str());
                    }
                    //Handle paste
                    else if (event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
                    {
                        istr = SDL_GetClipboardText();
                    }
                }
                else if (event->type == SDL_TEXTINPUT)
                {
                    //Not copy or pasting
                    if (!((event->text.text[ 0 ] == 'c' || event->text.text[ 0 ] == 'C' ) && ( event->text.text[ 0 ] == 'v' || event->text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL))
                    {
                        //Append character
                        istr += event->text.text[0];
                    }
                }
            }
            function(false);

            std::string cbstr = str + istr;

            char* ccbstr = new char[str.length() + 2 + istr.length()];
            strcpy(ccbstr, cbstr.c_str());

            text = SDL_drawText(font, 0xff, 0xff, 0xff, 0xFF, 0x00, 0x00, 0x00, 0x00, ccbstr, shaded);

            textTexture = SDL_CreateTextureFromSurface(renderer, text);

            renRect.x = (resx / 8);
            renRect.y = (resy / 8);
            renRect.w = chx * (str.length() + istr.length());
            renRect.h = chy;

            SDL_RenderCopy(renderer, textTexture, NULL, &renRect);

            SDL_RenderPresent(renderer);

            delete [] ccbstr;
            lastTime = currentTime;
        }
    }
    delete [] cstr;

    SDL_FlushEvent(SDL_KEYDOWN);

    SDL_StopTextInput();

    return istr;
}





