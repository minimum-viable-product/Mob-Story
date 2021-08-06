
#include "SDL.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

//global variables
SDL_Window* gWindow = NULL;         //The window we'll be rendering to
SDL_Surface* gScreenSurface = NULL; //The surface contained by the window
SDL_Surface* gHelloWorld = NULL;    //The image we will load and show on the screen

//functions
bool init();        //start up SDL and create window
bool loadMedia();   //loads media
void close();       //frees media and shuts down SDL

int main(int argc, char* argv[]) {

    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            SDL_UpdateWindowSurface(gWindow);
            SDL_Delay(2000);
        }
    }
    close();
    return 0;
}

//start up SDL and create window
bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        gWindow = SDL_CreateWindow(
            "An SDL2 window",                   // window title
            SDL_WINDOWPOS_UNDEFINED,            // initial x position
            SDL_WINDOWPOS_UNDEFINED,            // initial y position
            640,                                // width, in pixels
            480,                                // height, in pixels
            SDL_WINDOW_SHOWN                    // flags - see below
        );
        if (gWindow == NULL)
        {
            printf("Could not create window: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return true;
}

//loads media
bool loadMedia()
{
    gHelloWorld = IMG_Load("gear.png");
    if (gHelloWorld == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
        return false;
    }
    return true;
}

//frees media and shuts down SDL
void close()
{
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}
