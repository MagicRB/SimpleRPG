#include "wall_mark.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

wall_mark::wall_mark()
{
    //ctor
}

wall_mark::~wall_mark()
{
    //dtor
}
