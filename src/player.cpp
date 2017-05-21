#include "player.h"

#if defined(__WINDOWS__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/curses.h>
#else
    #include <ncurses.h>
#endif


player::player()
{
    //ctor
}

player::~player()
{
    //dtor
}

void character::render(int cy, int cx)
{
    mvaddch(character::y - cy, character::x - cx, '@');
}

void character::erasel(int cy, int cx)
{
    mvaddch(character::ly - cy, character::lx - cx, ' ');
}

void character::chmove(int y, int x)
{
    character::lx = character::x;
    character::ly = character::y;
    character::x = x;
    character::y = y;
}

bool character::checkColl(int y, int x,int cy, int cx)
{
    int ch = mvwinch(stdscr, character::y + y - cy, character::x + x - cx) & A_CHARTEXT;
    if (ch == '#' || ch == '/')
    {
        return true;
    } else
    {
        return false;
    }
}
