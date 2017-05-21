#ifndef HUD_H
#define HUD_H

#include <player.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

class hud
{
    public:
        hud();
        ~hud();

        void render(player* pl)
        {
            char hp[sizeof(pl->getHp())+2];
            snprintf(hp, sizeof hp, "%f", pl->getHp());

            mvaddstr(0, 0, hp);

            char thp[sizeof(pl->getTotalHp())+2];
            snprintf(thp, sizeof thp, "%f",pl->getTotalHp());

            mvaddch(0, sizeof(pl->getHp()) + 1, '/');
            mvaddstr(0, sizeof(pl->getHp()) + 2, thp);
            mvaddstr(0, sizeof(pl->getHp()) + sizeof(pl->getTotalHp()) + 3, "HP");
        }


    protected:

    private:
};

#endif // HUD_H
