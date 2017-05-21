# SimpleRPG

This is very simple RPG in C++ with ncurses. Compatible with linux-GCC and Windows-MinGW (You must compile this on linux)
Prefarably use CodeBlocks for ease of compilation

## Latest compilation commands

g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/main.cpp -o obj/Debug/main.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/animBlock.cpp -o obj/Debug/src/animBlock.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/block.cpp -o obj/Debug/src/block.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/character.cpp -o obj/Debug/src/character.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/door.cpp -o obj/Debug/src/door.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/door_switch.cpp -o obj/Debug/src/door_switch.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/func.cpp -o obj/Debug/src/func.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/hud.cpp -o obj/Debug/src/hud.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/player.cpp -o obj/Debug/src/player.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/sign.cpp -o obj/Debug/src/sign.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/wall.cpp -o obj/Debug/src/wall.o
g++ -Wall -fexceptions -g -Iinclude -c /home/main/C++/SimpleRPG/src/wall_mark.cpp -o obj/Debug/src/wall_mark.o
g++  -o bin/Debug/RPG obj/Debug/main.o obj/Debug/src/animBlock.o obj/Debug/src/block.o obj/Debug/src/character.o obj/Debug/src/door.o obj/Debug/src/door_switch.o obj/Debug/src/func.o obj/Debug/src/hud.o obj/Debug/src/player.o obj/Debug/src/sign.o obj/Debug/src/wall.o obj/Debug/src/wall_mark.o   -lncurses

## Download section

Windows x86_64 Binary [Download](http://62.168.71.236/SimpleRPG/RPG.exe)  
Arch Linux x86_64 Binary [Download](http://62.168.71.236/SimpleRPG/RPG) !!Outdate (Actually not working)
