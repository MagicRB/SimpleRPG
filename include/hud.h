#ifndef HUD_H
#define HUD_H

#include <player.h>
#include <string>

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

        void displayText(std::string str)
        {
            unsigned int by = getmaxy(stdscr) / 8;
            unsigned int bx = getmaxx(stdscr) / 8;

            char ch;

            std::string bstr;

            unsigned int l = by;

            for (unsigned i = 0; i < str.length(); i += getmaxx(stdscr) - 2 * bx)
            {
                bstr = str.substr(i, getmaxx(stdscr) - 2 * bx);
                mvaddstr(l + 1,bx + 1, bstr.c_str());
                l++;
            }
            while (ch != 'q')
            {
                ch = getch();
            }
        }


    protected:

    private:
};

#endif // HUD_H
