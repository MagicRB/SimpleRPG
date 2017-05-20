g++ -Wall -fexceptions -g -Iinclude -c main.cpp -o obj/Debug/main.o
g++ -Wall -fexceptions -g -Iinclude -c src/block.cpp -o obj/Debug/src/block.o
g++ -Wall -fexceptions -g -Iinclude -c src/character.cpp -o obj/Debug/src/character.o
g++ -Wall -fexceptions -g -Iinclude -c src/func.cpp -o obj/Debug/src/func.o
g++ -Wall -fexceptions -g -Iinclude -c src/player.cpp -o obj/Debug/src/player.o
g++ -Wall -fexceptions -g -Iinclude -c src/wall.cpp -o obj/Debug/src/wall.o
g++ -Wall -fexceptions -g -Iinclude -c src/wall_mark.cpp -o obj/Debug/src/wall_mark.o
g++ -Wall -fexceptions -g -Iinclude -c src/door.cpp -o obj/Debug/src/door.o
g++ -Wall -fexceptions -g -Iinclude -c src/door_switch.cpp -o obj/Debug/src/door_switch.o
g++  -o bin/Debug/RPG obj/Debug/main.o obj/Debug/src/block.o obj/Debug/src/character.o obj/Debug/src/func.o obj/Debug/src/player.o obj/Debug/src/wall.o obj/Debug/src/wall_mark.o obj/Debug/src/door.o obj/Debug/src/door_switch.o  -lcurses
