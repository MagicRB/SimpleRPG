#ifndef WALL_MARK_H
#define WALL_MARK_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include <block.h>


class wall_mark : public block
{
    public:
        wall_mark();
        ~wall_mark();

        void render(int cy, int cx)
        {
            mvaddch(block::y - cy, block::x - cx, '%');
        }

        void setPos(int y, int x)
        {
            block::y = y;
            block::x = x;
        }



    protected:

    private:
};

#endif // WALL_MARK_H
