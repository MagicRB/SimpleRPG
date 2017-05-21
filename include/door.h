#ifndef DOOR_H
#define DOOR_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/curses.h>
#else
    #include <ncurses.h>
#endif

#include <block.h>


class door : public block
{
    public:
        door();
        ~door();

        bool open = false;
        char dch = '/';

        void render(int cy, int cx)
        {
            mvaddch(block::y - cy, block::x - cx, dch);
        }

        void setPos(int y, int x)
        {
            block::y = y;
            block::x = x;
        }

        void switchState()
        {
            if (dch == '/')
            {
                dch = '*';
            } else if (dch == '*')
            {
                dch = '/';
            }
        }

    protected:

    private:
};

#endif // DOOR_H
