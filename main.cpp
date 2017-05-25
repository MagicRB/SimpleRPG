#include <iostream>

#if defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncurses/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include "colors.h"

#include <func.h>

#include <player.h>
#include <wall.h>
#include <wall_mark.h>
#include <door.h>
#include <door_switch.h>
#include <animBlock.h>
#include <hud.h>
#include <sign.h>

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

//#include <GL/glut.h>
//#include <GL/gl.h>

#include <sstream>
#include <string>
#include <vector>
#include <fstream>

/// To get position on screen subtract cx, cy.
/// To get position in gameworld add cx, cy


int ch;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;

TTF_Font* font;

long long int timeDelta = 0;
long long int currentTime = 80;
long long int lastTime = 0;

struct timeval tv;

hud hud_o;
player pl;

std::vector<wall_mark> wall_mv;
wall_mark wall_mo;

std::vector<wall> wall_v;
wall wall_o;

std::vector<door> door_v;
door door_o;

std::vector<door_switch> door_sv;
door_switch door_so;

std::vector<animBlock> animBlock_v;
animBlock animBlock_o;

std::vector<sign> sign_v;
sign sign_o;

std::string obj_ln;
std::vector<std::string> splObj_ln;

func fc;

int cy = 0;
int cx = 0;

int numx = 0;
int numy = 0;

look lk = up;

std::string vstr(std::vector<std::string> v, int unsigned short i)
{
    //std::cout << i << v.size() << std::endl;
    std::string str;
    if (i <= v.size() - 1)
    {
        str = v.at(i);
    }else
    {
        str = "";
    }
    return str;
}

void addObjects()
{
    std::ifstream infile("objTutorialRoom.txt");

    //infile.open ("obj.txt");
    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,obj_ln); // Saves the line in STRING.

        std::istringstream ss(obj_ln);
        std::string token;

        //std::cout << obj_ln << std::endl;

        if (obj_ln == "")
        {
            break;
        }

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
        } else if (vstr(splObj_ln, 0) == "door")
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
                    door_v.at(door_v.size() - 1).open = true;
                } else
                {
                    door_v.at(door_v.size() - 1).dch = '/';
                    door_v.at(door_v.size() - 1).open = false;
                }
            }
        } else if (vstr(splObj_ln, 0) == "door_switch")
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

        } else if (vstr(splObj_ln, 0) == "anim_block")
        {
            std::stringstream nystream(vstr(splObj_ln, 1));
            std::stringstream nxstream(vstr(splObj_ln, 2));
            if (nystream >> numy && nxstream >> numx)
            {
                animBlock_v.push_back(animBlock_o);
                animBlock_v.at(animBlock_v.size() - 1).setPos(numy, numx);
            }
        } else if (vstr(splObj_ln, 0) == "sign")
        {
            std::stringstream nystream(vstr(splObj_ln, 1));
            std::stringstream nxstream(vstr(splObj_ln, 2));
            if (nystream >> numy && nxstream >> numx)
            {
                sign_v.push_back(sign_o);
                sign_v.at(sign_v.size() - 1).setPos(numy, numx);
                sign_v.at(sign_v.size() - 1).setText(vstr(splObj_ln, 3));
            }
        } else if (vstr(splObj_ln, 0) == "player")
        {
            std::stringstream nystream(vstr(splObj_ln, 1));
            std::stringstream nxstream(vstr(splObj_ln, 2));
            if (nystream >> numy && nxstream >> numx)
            {
                pl.y = numy;
                pl.x = numx;

            }
        }
        splObj_ln.clear();

    }
	infile.close();
}

void NCurses_Render()
{
    erase();

    for (int unsigned short i = 0; i < wall_v.size(); i++)
    {
        wall_v.at(i).render(cy, cx);
    }
    for (int unsigned short i = 0; i < wall_mv.size(); i++)
    {
        wall_mv.at(i).render(cy, cx);
    }
    for (int unsigned short i = 0; i < door_v.size(); i++)
    {
        door_v.at(i).render(cy, cx);
    }
    for (int unsigned short i = 0; i < door_sv.size(); i++)
    {
        door_sv.at(i).render(cy, cx);
    }
    for (int unsigned short i = 0; i < animBlock_v.size(); i++)
    {
        animBlock_v.at(i).render(cy, cx);
    }
    for (int unsigned short i = 0; i < sign_v.size(); i++)
    {
        sign_v.at(i).render(cy, cx);
    }

    mvaddch(0 - cy, 0 - cx, '$');

    pl.render(cy, cx);

    hud_o.render(&pl);

    refresh();
}

void SDL_Render()
{
    SDL_RenderClear(renderer);

    SDL_Surface* text = fc.SDL_drawText(font, (Uint8)0xFF, (Uint8)0xFF, (Uint8)0xFF, (Uint8)0xFF, (Uint8)0x00, (Uint8)0x00, (Uint8)0x00, (Uint8)0x00, (char*)"$", shaded);

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

    SDL_Rect textRect;
    textRect.x = (0 - cx) * 7;
    textRect.y = (0 - cy) * 14;
    textRect.w = 7;
    textRect.h = 14;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);

    for (int unsigned short i = 0; i < wall_v.size(); i++)
    {
        wall_v.at(i).SDL_render(window, renderer, font, cy, cx);
    }
    for (int unsigned short i = 0; i < wall_mv.size(); i++)
    {

    }
    for (int unsigned short i = 0; i < door_sv.size(); i++)
    {
        door_sv.at(i).SDL_render(window, renderer, font, cy, cx);
    }
    for (int unsigned short i = 0; i < door_v.size(); i++)
    {
        door_v.at(i).SDL_render(window, renderer, font, cy, cx);
    }
    for (int unsigned short i = 0; i < animBlock_v.size(); i++)
    {
        animBlock_v.at(i).SDL_render(window, renderer, font, cy, cx);
    }
    for (int unsigned short i = 0; i < sign_v.size(); i++)
    {
        sign_v.at(i).SDL_render(window, renderer, font, cy, cx);
    }

    pl.SDL_render(window, renderer, font, cy, cx);

    hud_o.SDL_render(window, renderer, font, &pl);

    pl.renderLook(lk, font, renderer, cy, cx);

    SDL_RenderPresent(renderer);
}

void grender()
{
    if (NCURSES_ENABLED == true)
    {
        NCurses_Render();
    }
    if (SDL_ENABLED == true)
    {
        SDL_Render();
    }
}

void init_cpairs()
{
    init_color(COLOR_BROWN, 549, 353, 141);
    init_pair(PAIR_BROWN_BROWN_DARK, COLOR_BROWN_DARK, COLOR_BROWN);
    init_color(COLOR_BROWN_DARK, 388, 212, 24);
}

int SDLInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return -1;
    }

    TTF_Init();

    font = fc.loadTTF("./font.ttf", 15);

    window = SDL_CreateWindow("Kurva", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_WIDTH, SDL_HEIGTH, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //screenSurface = SDL_GetWindowSurface(window);

    return 0;
}

bool checkColl(int y, int x)
{
    for (int unsigned short i = 0; i < wall_v.size(); i++)
    {
        if (pl.y + y == wall_v.at(i).y && pl.x + x == wall_v.at(i).x)
        {
            return true;
        }
    }
    for (int unsigned short i = 0; i < door_v.size(); i++)
    {
        if (pl.y + y == door_v.at(i).y && pl.x + x == door_v.at(i).x && door_v.at(i).open == false)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    std::ofstream outmap;
    outmap.open ("outmap.txt");

    addObjects();

    if (NCURSES_ENABLED == true)
    {
        ///Initialize ncurses
        initscr();
        //cbreak();

        timeout(0);
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);


        start_color();
        init_cpairs();
    }

    if (SDL_ENABLED == true)
    {
        if (SDLInit() != 0)
        {
            return -1;
        }

        SDL_FlushEvent(SDL_KEYDOWN);
    }

    if (SDL_ENABLED == true)
    {
        cy = (-1)*(SDL_HEIGTH / 14 / 2);
        cx = (-1)*(SDL_WIDTH / 7 / 2);
    }

    if (NCURSES_ENABLED == true)
    {
        cy = (-1)*(getmaxy(stdscr) / 2);
        cx = (-1)*(getmaxx(stdscr) / 2);
    }

    grender();

    while (true)
    {
        gettimeofday (&tv, NULL);
        currentTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;

        timeDelta = currentTime - lastTime;

        if (timeDelta >= 20 && NCURSES_ENABLED == true)
        {
            lastTime = currentTime;

            ch = getch();

            if (ch == 'd' && !(checkColl(0, 1)))
            {
                pl.chmove(pl.y, pl.x + 1);
                cx += 1;
                //grender();
            } else if (ch == 'a' && !(checkColl(0, -1)))
            {
                pl.chmove(pl.y, pl.x - 1);
                cx -= 1;
            } else if (ch == 'w' && !(checkColl(-1, 0)))
            {
                pl.chmove(pl.y - 1, pl.x);
                cy -= 1;
            } else if (ch == 's' && !(checkColl(1, 0)))
            {
                pl.chmove(pl.y + 1, pl.x);
                cy += 1;
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
                for (int unsigned i = 0; i < sign_v.size(); i++)
                {
                    if (sign_v.at(i).y == pl.y && sign_v.at(i).x == pl.x)
                    {
                        sign_v.at(i).read(&hud_o, font, renderer);
                    }
                }
            } else if (ch == 'q')
            {
                for (unsigned int i = 0; i < wall_mv.size(); i++)
                {
                    outmap << "wall;" << wall_mv.at(i).y << ";" << wall_mv.at(i).x<< "\n";
                }
                outmap.close();
                break;
            } else if (ch == 'r')
            {
                cy = (-1)*(getmaxy(stdscr) / 2);
                cx = (-1)*(getmaxx(stdscr) / 2);
                cy += pl.y;
                cx += pl.x;
            }
            grender();
        }
        if (timeDelta >= 20 && SDL_ENABLED == true)
        {
            lastTime = currentTime;

            ch = getch();

            SDL_PollEvent(&event);

            if (event.key.keysym.sym == SDLK_d && event.type == SDL_KEYDOWN && !(checkColl(0, 1)))
            {
                pl.chmove(pl.y, pl.x + 1);
                cx += 1;
                //grender();
            } else if (event.key.keysym.sym == SDLK_a && event.type == SDL_KEYDOWN && !(checkColl(0, -1)))
            {
                pl.chmove(pl.y, pl.x - 1);
                cx -= 1;
            } else if (event.key.keysym.sym == SDLK_w && event.type == SDL_KEYDOWN && !(checkColl(-1, 0)))
            {
                pl.chmove(pl.y - 1, pl.x);
                cy -= 1;
            } else if (event.key.keysym.sym == SDLK_s && event.type == SDL_KEYDOWN && !(checkColl(1, 0)))
            {
                pl.chmove(pl.y + 1, pl.x);
                cy += 1;
            } else if (event.key.keysym.sym == SDLK_e && event.type == SDL_KEYDOWN)
            {
                for (int unsigned i = 0; i < door_sv.size(); i++)
                {
                    if (door_sv.at(i).y == pl.y + pl.lky && door_sv.at(i).x == pl.x + pl.lkx)
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
                for (int unsigned i = 0; i < sign_v.size(); i++)
                {
                    if (sign_v.at(i).y == pl.y + pl.lky && sign_v.at(i).x == pl.x + pl.lkx)
                    {
                        sign_v.at(i).read(&hud_o, font, renderer);
                    }
                }
            } else if (event.key.keysym.sym == SDLK_q && event.type == SDL_KEYDOWN)
            {
                unsigned int by = SDL_HEIGTH / 8;
                unsigned int bx = SDL_WIDTH / 8;

                std::string str = "Realy quit? [Y/n]";

                std::string bstr;

                unsigned int l = by / 7;

                for (unsigned i = 0; i < str.length(); i += (SDL_WIDTH - 2 * bx) / 7)
                {
                    bstr = str.substr(i, (SDL_WIDTH - 2 * bx) / 7);

                    char *cstr = new char[bstr.length() + 1];
                    strcpy(cstr, bstr.c_str());

                    SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, cstr, shaded);

                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

                    SDL_FreeSurface(text);

                    SDL_Rect textRect;
                    textRect.x = 1 * bx;
                    textRect.y = 0 + l * 14;
                    textRect.w = 7 * bstr.length();
                    textRect.h = 14;

                    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

                    SDL_DestroyTexture(textTexture);
                    l++;
                }

                SDL_RenderPresent(renderer);

                SDL_PollEvent(&event);

                SDL_FlushEvent(SDL_KEYDOWN);

                while ((event.key.keysym.sym != SDLK_y && event.key.keysym.sym != SDLK_n) && event.type != SDLK_DOWN)
                {
                    SDL_PollEvent(&event);
                }
                if (event.key.keysym.sym == SDLK_y && event.type != SDLK_DOWN)
                {
                    break;
                    for (unsigned int i = 0; i < wall_mv.size(); i++)
                    {
                        outmap << "wall;" << wall_mv.at(i).y << ";" << wall_mv.at(i).x<< "\n";
                    }
                    outmap.close();
                }
            } else if (event.key.keysym.sym == SDLK_KP_1 && event.type == SDL_KEYDOWN)
            {
                lk = left_down;
            } else if (event.key.keysym.sym == SDLK_KP_2 && event.type == SDL_KEYDOWN)
            {
                lk = down;
            } else if (event.key.keysym.sym == SDLK_KP_3 && event.type == SDL_KEYDOWN)
            {
                lk = right_down;
            } else if (event.key.keysym.sym == SDLK_KP_4 && event.type == SDL_KEYDOWN)
            {
                lk = left;
            } else if (event.key.keysym.sym == SDLK_KP_6 && event.type == SDL_KEYDOWN)
            {
                lk = right;
            } else if (event.key.keysym.sym == SDLK_KP_7 && event.type == SDL_KEYDOWN)
            {
                lk = left_up;
            } else if (event.key.keysym.sym == SDLK_KP_8 && event.type == SDL_KEYDOWN)
            {
                lk = up;
            } else if (event.key.keysym.sym == SDLK_KP_9 && event.type == SDL_KEYDOWN)
            {
                lk = right_up;
            }
            grender();
        }
    }
    endwin();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
