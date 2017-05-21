#ifndef SIGN_H
#define SIGN_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include <block.h>

#include <hud.h>
#include <string>

class sign : public block
{
    public:
        sign();
        ~sign();

        std::string text;

        void render(int cy, int cx)
        {
            mvaddch(block::y - cy, block::x - cx, 'S');
        }

        void setPos(int y, int x)
        {
            block::y = y;
            block::x = x;
        }

        void setText(std::string str)
        {
            text = str;
        }

        void read(hud* hud_o)
        {
            hud_o->displayText(text);
        }

    protected:

    private:
};

#endif // SIGN_H
