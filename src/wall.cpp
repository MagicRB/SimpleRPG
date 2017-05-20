#include "wall.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif


wall::wall()
{
    block::player_collide = true;
}

wall::~wall()
{
    //dtor
}
