#include <iostream>

#define SDL_MAIN_HANDLED

#if defined(__WINDOWS__) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <ncursesw/curses.h>
    #include "windows.h"
#else
    #include <ncurses.h>
#endif

#include "colors.h"

#include <func.h>

#include <chrono>

#include <player.h>
#include <wall.h>
#include <wall_mark.h>
#include <door.h>
#include <door_switch.h>
#include <animBlock.h>
#include <hud.h>
#include <sign.h>
#include <mapPortal.h>

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

std::vector<mapPortal> mapPortal_v;
mapPortal mapPortal_o;

std::string obj_ln;
std::vector<std::string> splObj_ln;

func fc;

int cy = 0;
int cx = 0;

int numx = 0;
int numy = 0;

std::string inputText;

look lk = up;

short unsigned int window_mode;

namespace sc = std::chrono;

SDL_Texture* startTexture;
SDL_Rect startRect;

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

void clearObjects()
{
    door_v.clear();
    door_sv.clear();
    wall_v.clear();
    animBlock_v.clear();
    sign_v.clear();
    mapPortal_v.clear();
}

void saveObjects(char* file)
{
    std::ofstream outmap;
    outmap.open (file);

    for (int unsigned short i = 0; i < wall_v.size(); i++)
    {
        outmap << "wall;" << wall_v.at(i).y << ';' << wall_v.at(i).x << '\n';
    } for (int unsigned short i = 0; i < door_v.size(); i++)
    {
        outmap << "door;" << door_v.at(i).y << ';' << door_v.at(i).x << ';' << (door_v.at(i).open ? "open" : "closed") << '\n';
    } for (int unsigned short i = 0; i < door_sv.size(); i++)
    {
        outmap << "door_switch;" << door_sv.at(i).y << ';' << door_sv.at(i).x << ';' << door_sv.at(i).dy << ';' << door_sv.at(i).dx << '\n';
    } for (int unsigned short i = 0; i < animBlock_v.size(); i++)
    {
        outmap << "anim_block;" << animBlock_v.at(i).y << ';' << animBlock_v.at(i).x << '\n';
    } for (int unsigned short i = 0; i < sign_v.size(); i++)
    {
        outmap << "sign;" << sign_v.at(i).y << ';' << sign_v.at(i).x << ';' << sign_v.at(i).text << '\n';
    } for (int unsigned short i = 0; i < mapPortal_v.size(); i++)
    {
        outmap << "mapPortal;" << mapPortal_v.at(i).y << ';' << mapPortal_v.at(i).x << ';' << mapPortal_v.at(i).obj_map << '\n';
    }
    outmap << "player;" << pl.y << ';' << pl.x << '\n';
}

void loadSettings()
{
    std::ifstream infile;
    infile.open("data/settings.txt");
    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,obj_ln); // Saves the line in STRING.

        std::istringstream ss(obj_ln);
        std::string token;

        if (obj_ln == "")
        {
            break;
        }

        while (std::getline(ss, token, ';'))
        {
            splObj_ln.push_back(token);
        }

        if (vstr(splObj_ln, 0) == "resolution")
        {
            std::stringstream nxstream(vstr(splObj_ln, 1));
            std::stringstream nystream(vstr(splObj_ln, 2));

            if (nxstream >> numx && nystream >> numy)
            {
                resx = numx;
                resy = numy;
            }
        } else if (vstr(splObj_ln, 0) == "SDL")
        {
            if (vstr(splObj_ln, 1) == "true")
            {
                SDL_ENABLED = true;
            } else if (vstr(splObj_ln, 1) == "false")
            {
                SDL_ENABLED = false;
            }
        } else if (vstr(splObj_ln, 0) == "SDL_IMAGE")
        {
            if (vstr(splObj_ln, 1) == "true")
            {
                SDL_IMAGE_ENABLED = true;
            } else if (vstr(splObj_ln, 1) == "false")
            {
                SDL_IMAGE_ENABLED = false;
            }
        } else if (vstr(splObj_ln, 0) == "NCURSES")
        {
            if (vstr(splObj_ln, 1) == "true")
            {
                NCURSES_ENABLED = true;
            } else if (vstr(splObj_ln, 1) == "false")
            {
                NCURSES_ENABLED = false;
            }
        } else if (vstr(splObj_ln, 0) == "window_mode")
        {
            if (vstr(splObj_ln, 1) == "fullscreen")
            {
                window_mode = SDL_WINDOW_FULLSCREEN_DESKTOP;
            } else if (vstr(splObj_ln, 1) == "windowed")
            {
                window_mode = 0;
            }
        }

        splObj_ln.clear();
    }
    infile.close();
}

int addObjects(bool askMap, char* objMap = "obj.txt")
{
    std::ifstream infile;
    clearObjects();

    if (askMap == true)
    {
        std::string fl;
        std::cout << "Enter name of .txt file which to load map from: ";
        std::cin >> fl;
        infile.open(fl);
        if (!infile.is_open())
        {
            return -1;
        }
    } else if (askMap == false && objMap != NULL)
    {
        std::string str(objMap);
        infile.open(objMap);
        if (!infile.is_open())
        {
            return -1;
        }
    }

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
        } else if (vstr(splObj_ln, 0) == "mapPortal")
        {
            std::stringstream nystream(vstr(splObj_ln, 1));
            std::stringstream nxstream(vstr(splObj_ln, 2));

            if (nystream >> numy && nxstream >> numx)
            {
                mapPortal_v.push_back(mapPortal_o);
                mapPortal_v.at(mapPortal_v.size() - 1).setPos(numy, numx);
                char* chm = strdup(vstr(splObj_ln, 3).c_str());//, vstr(splObj_ln, 3).size());
                std::cout << chm <<  std::endl;
                mapPortal_v.at(mapPortal_v.size() - 1).setMap(chm);
                //std::cout << mapPortal_v.at(mapPortal_v.size() - 1).str;
            }
        }
        splObj_ln.clear();
    }
    cy = (-1)*(resy / chy / 2);
    cx = (-1)*(resx / chx / 2);
    cy += pl.y;
    cx += pl.x;

	infile.close();
	return 0;
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

void SDL_Render(bool present)
{
    SDL_RenderClear(renderer);

    startRect.x = (0 - cx) * chx;
    startRect.y = (0 - cy) * chy;
    startRect.w = chx;
    startRect.h = chy;

    SDL_RenderCopy(renderer, startTexture, NULL, &startRect);

    for (int unsigned short i = 0; i < wall_v.size(); i++)
    {
        wall_v.at(i).SDL_render(window, renderer, cy, cx);
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
    for (int unsigned short i = 0; i < mapPortal_v.size(); i++)
    {
        mapPortal_v.at(i).SDL_render(window, renderer, font, cy, cx);
    }

    pl.SDL_render(window, renderer, font, cy, cx);

    hud_o.SDL_render(window, renderer, font, &pl);

    pl.renderLook(lk, font, renderer, cy, cx);

    if (present == true)
    {
        SDL_RenderPresent(renderer);
    }
}

void SDL_IMG_Render(bool present)
{
    SDL_RenderClear(renderer);

    startRect.x = (0 - cx) * chx;
    startRect.y = (0 - cy) * chy;
    startRect.w = chx;
    startRect.h = chy;

    SDL_RenderCopy(renderer, startTexture, NULL, &startRect);

    for (int unsigned short i = 0; i < wall_v.size(); i++)
    {
        wall_v.at(i).IMG_render(renderer, cy, cx);
    }
    for (int unsigned short i = 0; i < wall_mv.size(); i++)
    {

    }
    for (int unsigned short i = 0; i < door_sv.size(); i++)
    {
        //door_sv.at(i).SDL_render(window, renderer, font, cy, cx);
    }
    for (int unsigned short i = 0; i < door_v.size(); i++)
    {
        //door_v.at(i).SDL_render(window, renderer, font, cy, cx);
    }
    for (int unsigned short i = 0; i < animBlock_v.size(); i++)
    {
        //animBlock_v.at(i).SDL_render(window, renderer, font, cy, cx);
    }
    for (int unsigned short i = 0; i < sign_v.size(); i++)
    {
        //sign_v.at(i).SDL_render(window, renderer, font, cy, cx);
    }
    for (int unsigned short i = 0; i < mapPortal_v.size(); i++)
    {
        //mapPortal_v.at(i).SDL_render(window, renderer, font, cy, cx);
    }

    pl.IMG_render(renderer, cy, cx);

    hud_o.SDL_render(window, renderer, font, &pl);

    pl.renderLook(lk, font, renderer, cy, cx);
    if (present == true)
    {
        SDL_RenderPresent(renderer);
    }
}

void grender(bool present)
{
    if (NCURSES_ENABLED == true)
    {
        NCurses_Render();
    }
    if (SDL_ENABLED == true)
    {
        SDL_Render(present);
    }
    if (SDL_IMAGE_ENABLED == true)
    {
        SDL_IMG_Render(present);
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

    //set opengl attributes, supposed to happen before window creation
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //OpenGL core profile
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 4); //OpenGL 3+
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 5); //OpenGL 3.3

    TTF_Init();

    font = fc.loadTTF("data/font.ttf", 15);

    window = SDL_CreateWindow("Kurva", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resx, resy, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    screenSurface = SDL_GetWindowSurface(window);

    SDL_SetWindowFullscreen(window, window_mode);

    SDL_Surface* text = fc.SDL_drawText(font, (Uint8)0xFF, (Uint8)0xFF, (Uint8)0xFF, (Uint8)0xFF, (Uint8)0x00, (Uint8)0x00, (Uint8)0x00, (Uint8)0x00, (char*)"$", shaded);

    startTexture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_FreeSurface(text);

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

void initObjects()
{
    for (int unsigned short i = 0; i < wall_v.size(); i++)
    {
        wall_v.at(i).init(renderer, font);
    }

    pl.init(renderer, font);
}

void changeSize(short int x, short int y)
{
    if (!(chx + x <= 0))
    {
        chx = chx + x;
    }
    if (!(chy + y <= 0))
    {
        chy = chy + y;
    }
    cy = (-1)*(resy / chy / 2);
    cx = (-1)*(resx / chx / 2);
    cy += pl.y;
    cx += pl.x;
}

int main()
{
    addObjects(false, "maps/obj.txt");
    loadSettings();

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

    if (SDL_ENABLED == true || SDL_IMAGE_ENABLED == true)
    {
        if (SDLInit() != 0)
        {
            return -1;
        }

        SDL_FlushEvent(SDL_KEYDOWN);
    }

    if (SDL_ENABLED == true || SDL_IMAGE_ENABLED == true)
    {
        cy = (-1)*(resy / chy / 2);
        cx = (-1)*(resx / chx / 2);
    }

    if (NCURSES_ENABLED == true)
    {
        cy = (-1)*(getmaxy(stdscr) / 2);
        cx = (-1)*(getmaxx(stdscr) / 2);
    }

    initObjects();

    grender(true);

    while (true)
    {
        auto time = std::chrono::system_clock::now();

        auto since_epoch = time.time_since_epoch();

        auto millis = sc::duration_cast<std::chrono::milliseconds>(since_epoch);

        currentTime = millis.count();

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
                    //outmap << "wall;" << wall_mv.at(i).y << ";" << wall_mv.at(i).x<< "\n";
                }
                //outmap.close();
                break;
            } else if (ch == 'r')
            {
                cy = (-1)*(getmaxy(stdscr) / 2);
                cx = (-1)*(getmaxx(stdscr) / 2);
                cy += pl.y;
                cx += pl.x;
            }
            grender(true);
        }
        if (timeDelta >= 20 && (SDL_ENABLED == true || SDL_IMAGE_ENABLED == true))
        {
            lastTime = currentTime;

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
                for (int unsigned i = 0; i < mapPortal_v.size(); i++)
                {
                    if (mapPortal_v.at(i).y == pl.y + pl.lky && mapPortal_v.at(i).x == pl.x + pl.lkx)
                    {
                        addObjects(false, mapPortal_v.at(i).loadMap());
                        initObjects();
                        cy = (-1)*(resy / chy / 2);
                        cx = (-1)*(resx / chx / 2);
                    }
                }
            } else if (event.key.keysym.sym == SDLK_q && event.type == SDL_KEYDOWN)
            {
                unsigned int by = resy / 8;
                unsigned int bx = resx / 8;

                std::string str = "Realy quit? [Y/n]";

                std::string bstr;

                unsigned int l = by / chx;

                for (unsigned i = 0; i < str.length(); i += (resx - 2 * bx) / chx)
                {
                    bstr = str.substr(i, (resx - 2 * bx) / chx);

                    char *cstr = new char[bstr.length() + 1];
                    strcpy(cstr, bstr.c_str());

                    SDL_Surface* text = fc.SDL_drawText(font, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, cstr, shaded);

                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, text);

                    SDL_FreeSurface(text);

                    SDL_Rect textRect;
                    textRect.x = 1 * bx;
                    textRect.y = 0 + l * chy;
                    textRect.w = chx * bstr.length();
                    textRect.h = chy;

                    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

                    SDL_DestroyTexture(textTexture);
                    l++;
                }

                SDL_RenderPresent(renderer);

                SDL_PollEvent(&event);

                SDL_FlushEvent(SDL_KEYDOWN);

                while ((event.key.keysym.sym != SDLK_y && event.key.keysym.sym != SDLK_n) && event.type != SDLK_DOWN)
                {
                    auto time = std::chrono::system_clock::now();

                    auto since_epoch = time.time_since_epoch();

                    auto millis = sc::duration_cast<std::chrono::milliseconds>(since_epoch);

                    currentTime = millis.count();

                    timeDelta = currentTime - lastTime;
                    if (timeDelta >= 20)
                    {
                        lastTime = currentTime;
                        SDL_PollEvent(&event);

                        SDL_RenderPresent(renderer);
                    }
                }
                if (event.key.keysym.sym == SDLK_y && event.type != SDLK_DOWN)
                {
//                    for (unsigned int i = 0; i < wall_mv.size(); i++)
//                    {
//                        //outmap << "wall;" << wall_mv.at(i).y << ";" << wall_mv.at(i).x<< "\n";
//                    }
                    //outmap.close();
                    break;
                }
            } else if (event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN)
            {
                std::string qstr = "maps/" + fc.textInputDialog("Input name of .obj file to load: ", 5, 5, font, renderer, &event, &grender);
                char* cqstr = new char[qstr.length() + 1];
                strcpy(cqstr, qstr.c_str());
                addObjects(false, cqstr);
                initObjects();
                delete [] cqstr;
            } else if (event.key.keysym.sym == SDLK_F5 && event.type == SDL_KEYDOWN)
            {
                std::string qstr = fc.textInputDialog("Input name of .obj file to save to: ", 5, 5, font, renderer, &event, &grender);
                char* cqstr = new char[qstr.length() + 1];
                strcpy(cqstr, qstr.c_str());
                saveObjects(cqstr);
                delete [] cqstr;
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
            } else if (event.key.keysym.sym == SDLK_f && event.type == SDL_KEYDOWN)
            {
                Uint32 flags = SDL_GetWindowFlags(window);
                if ((flags & SDL_WINDOW_FULLSCREEN) == true)
                {
                    SDL_SetWindowFullscreen(window, 0);
                } else
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }

            } else if (event.key.keysym.sym == SDLK_UP && event.type == SDL_KEYDOWN)
            {
                changeSize(7,14);
            } else if (event.key.keysym.sym == SDLK_DOWN && event.type == SDL_KEYDOWN)
            {
                changeSize(-7,-14);
            } else if (event.type == SDL_QUIT)
            {
                break;
            }
            grender(true);
        }
    }
    endwin();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(startTexture);

    SDL_Quit();

    return 0;
}
