#ifndef DOOR_SWITCH_H
#define DOOR_SWITCH_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include <block.h>


class door_switch : public block
{
    public:
        door_switch();
        ~door_switch();

        int dy;
        int dx;

        void render(int cy, int cx)
        {
            mvaddch(block::y - cy, block::x - cx, '+');
        }

        void setPos(int y, int x, int dyr, int dxr)
        {
            block::y = y;
            block::x = x;
            dy = dyr;
            dx =dxr;
        }

    protected:

    private:
};

#endif // DOOR_SWITCH_H
