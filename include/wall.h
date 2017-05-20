#ifndef WALL_H
#define WALL_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include <block.h>


class wall : public block
{
    public:
        wall();
        ~wall();

        void render(int cy, int cx)
        {
            mvaddch(block::y - cy, block::x - cx, '#');
        }

        void setPos(int y, int x)
        {
            block::y = y;
            block::x = x;
        }


    protected:

    private:
};

#endif // WALL_H
