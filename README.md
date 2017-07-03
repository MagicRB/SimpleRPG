# SimpleRPG

This is very simple RPG in C++ with ncurses. Compatible with linux-GCC and Windows-MinGW ~~(You must compile this on linux)~~
Prefarably use CodeBlocks for ease of compilation

## Compilation

Use Code::Blocks!! It's easy.  
To compile on windows for windows use Windows - Debug  
To compile on linux for linux use Linux - Debug  
To compile on linux for windows use Windows from Linux - Debug

When compiling for windows your compiler must #define this:
>WINVER=0x0400  
\_\_WIN95\_\_  
\_\_GNUWIN32\_\_  
STRICT  
HAVE_W32API_H  
\_\_WXMSW\_\_  
\_\_WINDOWS\_\_  


## Required libs

On linux you need to have ncurses and sdl2, sdl2_ttf, sdl2_image, installed to run and compile this, just link against these libs.
When cross compiling from Linux to Windows follow [this](https://sourceforge.net/p/mingw-w64/wiki2/NCurses/), change prefix to some sensible place (on Arch linux /usr/) also download SDL2 for windows and unpack bin, include, libs into the prefix you gave to ncurses
When compiling on Windows you need to download [these](https://62.168.71.236/SimpleRPG/req_libs.rar) libs 
On Linux when cross compiling for Windows use linker options:
> -lstdc++  
-lgcc  
-lodbc32  
-lwsock32  
-lwinspool  
-lwinmm  
-lshell32  
-lcomctl32  
-lodbc32  
-ladvapi32  
-lodbc32  
-lwsock32  
-lopengl32  
-lglu32  
-lole32  
-loleaut32  
-luuid  
-lncurses
-lSDL2
-lSDL2main
-lSDL2_ttf
-lSDL2_image

Set Search Dirs like this:
* Compiler: $prefix/mingw../include
* Linker: $prefix/mingw../lib
* Resource compiler: $prefix/mingw../include

## Download section
Just download this... This is all you need to get it running. [DOWNLOAD](https://github.com/MagicRB/SimpleRPG/raw/master/bin/Release.zip)
