#include <iostream>

#if defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include "colors.h"

#include <player.h>
#include <wall.h>
#include <wall_mark.h>
#include <door.h>
#include <door_switch.h>

#include <sstream>
#include <string>
#include <vector>
#include <fstream>

/// To get position on screen subtract cx, cy.
/// To get position in gameworld add cx, cy


int ch;

player pl;

std::vector<wall_mark> wall_mv;
wall_mark wall_mo;

std::vector<wall> wall_v;
wall wall_o;

std::vector<door> door_v;
door door_o;

std::vector<door_switch> door_sv;
door_switch door_so;

std::string obj_ln;
std::vector<std::string> splObj_ln;

int cy = 0;
int cx = 0;

int numx = 0;
int numy = 0;

std::string vstr(std::vector<std::string> v, int short i)
{
    std::string str;
    try
    {
        str = v.at(i);
    }
    catch (const std::out_of_range& e)
    {
        str = "";
    }
    return str;
}


void addObjects()
{
    std::ifstream infile;

    infile.open ("obj.txt");
    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,obj_ln); // Saves the line in STRING.

        std::istringstream ss(obj_ln);
        std::string token;

        while (std::getline(ss, token, ';'))
        {
            splObj_ln.push_back(token);
        }

        if (vstr(splObj_ln, 0) == "wall")
        {
            std::stringstream nystream(vstr(splObj_ln, 1));
            std::stringstream nxstream(vstr(splObj_ln, 2));

            if (nystream >> numy && nxstream >> numx)
            {
                wall_v.push_back(wall_o);
                wall_v.at(wall_v.size() - 1).setPos(numy, numx);
            }
        }
        if (vstr(splObj_ln, 0) == "door")
        {
            std::stringstream nystream(vstr(splObj_ln, 1));
            std::stringstream nxstream(vstr(splObj_ln, 2));

            if (nystream >> numy && nxstream >> numx && (vstr(splObj_ln, 3) == "open" || vstr(splObj_ln, 3) == "closed" ))
            {
                door_v.push_back(door_o);
                door_v.at(door_v.size() - 1).setPos(numy, numx);
                if (vstr(splObj_ln, 3) == "open")
                {
                    door_v.at(door_v.size() - 1).dch = '*';
                } else
                {
                    door_v.at(door_v.size() - 1).dch = '/';
                }
            }
        }
        if (vstr(splObj_ln, 0) == "door_switch")
        {
            std::stringstream nystream(vstr(splObj_ln, 1));
            std::stringstream nxstream(vstr(splObj_ln, 2));
            std::stringstream ndystream(vstr(splObj_ln, 3));
            std::stringstream ndxstream(vstr(splObj_ln, 4));

            int numdy;
            int numdx;

            if (nystream >> numy && nxstream >> numx && ndystream >> numdy && ndxstream >> numdx)
            {
                door_sv.push_back(door_so);
                door_sv.at(door_sv.size() - 1).setPos(numy, numx, numdy, numdx);
            }

        }
        splObj_ln.clear();

    }
	infile.close();
}

void grender()
{
    erase();


    for (int unsigned i = 0; i < wall_v.size(); i++)
    {
        attron(COLOR_PAIR(PAIR_BROWN_BROWN_DARK));
        wall_v.at(i).render(cy, cx);
        attroff(COLOR_PAIR(PAIR_BROWN_BROWN_DARK));
    }
    for (int unsigned i = 0; i < wall_mv.size(); i++)
    {
        wall_mv.at(i).render(cy, cx);
    }
    for (int unsigned i = 0; i < door_v.size(); i++)
    {
        door_v.at(i).render(cy, cx);
    }
    for (int unsigned i = 0; i < door_sv.size(); i++)
    {
        door_sv.at(i).render(cy, cx);
    }

    mvaddch(0 - cy, 0 - cx, '$');

    refresh();

    pl.render(cy, cx);
}

void init_cpairs()
{
    init_color(COLOR_BROWN, 549, 353, 141);
    init_pair(PAIR_BROWN_BROWN_DARK, COLOR_BROWN_DARK, COLOR_BROWN);
    init_color(COLOR_BROWN_DARK, 388, 212, 24);
}

int main()
{
    std::ofstream outmap;
    outmap.open ("outmap.txt");

    addObjects();

    /// Initialize ncurses
    initscr();
    //cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);


    start_color();
    init_cpairs();


    cy = (-1)*(getmaxy(stdscr) / 2);
    cx = (-1)*(getmaxx(stdscr) / 2);

    grender();

    while (true)
    {
        ch = getch();

        if (ch == 'd' && !(pl.checkColl(0, 1, cy, cx)))
        {
            pl.chmove(pl.y, pl.x + 1);
            cx += 1;
            grender();
        } else if (ch == 'a' && !(pl.checkColl(0, -1, cy, cx)))
        {
            pl.chmove(pl.y, pl.x - 1);
            cx -= 1;
            grender();
        }
        if (ch == 'w' && !(pl.checkColl(-1, 0, cy, cx)))
        {
            pl.chmove(pl.y - 1, pl.x);
            cy -= 1;
            grender();
        } else if (ch == 's' && !(pl.checkColl(1, 0, cy, cx)))
        {
            pl.chmove(pl.y + 1, pl.x);
            cy += 1;
            grender();
//        } else if (ch == '/')
//        {
//            wall_mv.push_back(wall_mo);
//            wall_mv.at(wall_mv.size()-1).setPos(pl.y, pl.x);
//        } else if (ch == '.')
//        {
//            for (unsigned int i = 0; i < wall_mv.size(); i++)
//            {
//                if (wall_mv.at(i).y == pl.y && wall_mv.at(i).x == pl.x)
//                {
//                    wall_mv.erase(wall_mv.begin() + i);
//                    wall_mv.shrink_to_fit();
//                }
//            }
        } else if (ch == 'e')
        {
            for (int unsigned i = 0; i < door_sv.size(); i++)
            {
                if (door_sv.at(i).y == pl.y && door_sv.at(i).x == pl.x)
                {
                    for (int unsigned di = 0; di < door_v.size(); di++)
                    {
                        if (door_v.at(di).x == door_sv.at(i).dx && door_v.at(di).y == door_sv.at(i).dy)
                        {
                            door_v.at(di).switchState();
                        }
                    }
                }
            }
            grender();
        } else if (ch == 'q')
        {
            for (unsigned int i = 0; i < wall_mv.size(); i++)
            {
                outmap << "wall;" << wall_mv.at(i).y << ";" << wall_mv.at(i).x<< "\n";
            }
            outmap.close();
            break;
        }


//        mvaddch(-5 - cy, -5 - cx, '#');
//        mvaddch(-3 - cy, -10 - cx, '#');
//        mvaddch(-2 - cy, -10 - cx, '#');
//        mvaddch(0 - cy, 0 - cx, '$');

    }
    endwin();

    return 0;
}
