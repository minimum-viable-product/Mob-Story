MSVC:
```
cl shell32.lib SDL2.lib SDL2main.lib SDL2_image.lib main.c /Ic:\path\to\sdl2\include /Ic:\path\to\sdl2_image\include /link /subsystem:windows /libpath:c:\path\to\sdl2\lib\x86 /libpath:c:\path\to\sdl2_image\lib\x86
```

MINGW:
```
gcc main.c -I /c/gcc/SDL2-2.0.14/i686-w64-mingw32/include/SDL2 -I /c/gcc/SDL2_image-2.0.5/i686-w64-mingw32/include/SDL2 -L /c/gcc/SDL2-2.0.14/i686-w64-mingw32/lib -L /c/gcc/SDL2_image-2.0.5/i686-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -o main.exe
```
