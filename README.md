# SimpleRPG

This is very simple RPG in C++ with ncurses. Compatible with linux-GCC and Windows-MinGW ~~(You must compile this on linux)~~
Prefarably use CodeBlocks for ease of compilation

## Compilation

Use Code::Blocks!! It's easy.  
To compile on windows for windows use Windows - Debug  
To compile on linux for linux use Linux - Debug  
To compole on linux for windows use Windows from Linux - Debug

When compiling for windows your compiler must #define this:
>WINVER=0x0400  
\_\_WIN95\_\_  
\_\_GNUWIN32\_\_  
STRICT  
HAVE_W32API_H  
\_\_WXMSW\_\_  
\_\_WINDOWS\_\_  


## Required libs

On linux you need to have ncurses installed to run and compile this  
When cross compiling from Linux to Windows follow [this](https://sourceforge.net/p/mingw-w64/wiki2/NCurses/), change prefix to some sensible place (on Arch linux /usr/)  
when compiling on Windows you need [this](www.google.com) (Just a placeholder)  

On Linux GCC link againt lib ncurses with -lncurses
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

Set Search Dirs like this:
* Compiler: $prefix/mingw../include
* Linker: $prefix/mingw../lib
* Resource compiler: $prefix/mingw../include

On Windows.... I have to look

## Download section

Windows x86_64 Binary [Download](http://62.168.71.236/SimpleRPG/RPG.exe)  
Arch Linux x86_64 Binary [Download](http://62.168.71.236/SimpleRPG/RPG)  
Example obj file [Download](http://62.168.71.236/SimpleRPG/obj.txt)  
Required dlls (Windows only) [Download](http://62.168.71.236/SimpleRPG/dlls.zip)
