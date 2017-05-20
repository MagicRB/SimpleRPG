#ifndef ANIMBLOCK_H
#define ANIMBLOCK_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include <iostream>
#include <block.h>
#include <sys/time.h>

class animBlock : public block
{
    public:
        animBlock();
        ~animBlock();

        timeval tv;

        char ch = 'a';

        int timeDelta = 0;
        int currentTime = 80;
        int lastTime = 0;

        void render(int cy, int cx)
        {
            gettimeofday (&tv, NULL);
            currentTime = (tv.tv_sec) + 0.000001 * tv.tv_usec;

            timeDelta = currentTime - lastTime;

            if (timeDelta >= 1)
            {
                if (ch == 'a')
                {
                    ch = 'b';
                } else
                {
                    ch = 'a';
                }
                lastTime = currentTime;
            }
            mvaddch(block::y - cy, block::x - cx, ch);
        }

        void setPos(int y, int x)
        {
            block::y = y;
            block::x = x;
        }

    protected:

    private:
};

#endif // ANIMBLOCK_H
