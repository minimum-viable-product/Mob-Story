
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "SDL.h"
#include "SDL_image.h"

//global variables
SDL_Window*   gWindow        = NULL; //The window we'll be rendering to
SDL_Surface*  gScreenSurface = NULL; //The surface contained by the window
SDL_Surface*  gGear          = NULL; //The image of gear
SDL_Surface*  gSprite        = NULL; //The image of person
SDL_Surface*  gWoodTile      = NULL; //The image of wood tile
SDL_Renderer* gMainRenderer  = NULL;
SDL_Texture*  gTexture       = NULL;
SDL_Rect gSrcRectGear   = { 0,0,64,64 };
SDL_Rect gSrcRectSprite = { 0,0,32,20 };
SDL_Rect gDstRectSprite = { 0,0,32,20 };
SDL_Rect gDstRectWoodTile = { 0,0,32,20 };
SDL_Rect gDstRectLeft   = { 0,0,64*6,64*6 };
SDL_Rect gDstRectRight  = { 46*6,0,64*6,64*6 };

//functions
bool init();        //start up SDL and create window
bool loadMedia();   //loads media
int  close();       //frees media and shuts down SDL
bool showError();


int main(int argc, char* argv[])
{
    SDL_Event event;
    int rotate_angle = 0;
    //int offsetX = 0;
    //int offsetY = 0;
    clock_t t;

    if (!init())
    {
        printf("Failed to initialize!\n");
        return 1;
    }
    if (!loadMedia())
    {
        printf("Failed to load media!\n");
        return 1;
    }

    //set background to blue
    SDL_SetRenderDrawColor(gMainRenderer, 0, 0, 255, 0);
    SDL_RenderClear(gMainRenderer);
    t = clock();

    while (true)
    {
        gDstRectWoodTile.x = 0;
        gDstRectWoodTile.y = 0;
        if ((clock() - t) >= 500)
        {
            SDL_RenderClear(gMainRenderer);
            SDL_RenderPresent(gMainRenderer);
            SDL_SetRenderDrawColor(gMainRenderer, 0, 0, 255, 0);
            SDL_RenderClear(gMainRenderer);
            gTexture = SDL_CreateTextureFromSurface(gMainRenderer, gWoodTile);
            for (int i = 0; i < 20; ++i)
            {
                for (int j = 0; j < 20; ++j)
                {
                    gDstRectWoodTile.x = 32 * i;
                    gDstRectWoodTile.y = 20 * j;
                    SDL_RenderCopy(gMainRenderer, gTexture, &gSrcRectSprite, &gDstRectWoodTile);
                }
            }
            gTexture = SDL_CreateTextureFromSurface(gMainRenderer, gGear);
            SDL_RenderCopyEx(gMainRenderer, gTexture, &gSrcRectGear, &gDstRectLeft, rotate_angle + 23, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(gMainRenderer, gTexture, &gSrcRectGear, &gDstRectRight, -rotate_angle, NULL, SDL_FLIP_NONE);
            rotate_angle += 10;
            if (rotate_angle == 360)  rotate_angle = 0;
            t = clock();
        }
        else
        {
            SDL_RenderClear(gMainRenderer);
            SDL_RenderPresent(gMainRenderer);
            SDL_SetRenderDrawColor(gMainRenderer, 0, 0, 255, 0);
            SDL_RenderClear(gMainRenderer);
            gTexture = SDL_CreateTextureFromSurface(gMainRenderer, gWoodTile);
            for (int i = 0; i < 32; ++i)
            {
                for (int j = 0; j < 20; ++j)
                {
                    gDstRectWoodTile.x = 32 * i;
                    gDstRectWoodTile.y = 20 * j;
                    SDL_RenderCopy(gMainRenderer, gTexture, &gSrcRectSprite, &gDstRectWoodTile);
                }
            }
            gTexture = SDL_CreateTextureFromSurface(gMainRenderer, gGear);
            SDL_RenderCopyEx(gMainRenderer, gTexture, &gSrcRectGear, &gDstRectLeft, rotate_angle + 23, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(gMainRenderer, gTexture, &gSrcRectGear, &gDstRectRight, -rotate_angle, NULL, SDL_FLIP_NONE);
        }
        gTexture = SDL_CreateTextureFromSurface(gMainRenderer, gSprite);
        SDL_RenderCopy(gMainRenderer, gTexture, &gSrcRectSprite, &gDstRectSprite);
        SDL_RenderPresent(gMainRenderer);
        SDL_Delay(100);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                    gDstRectSprite.y -= 20;
                    break;
                case SDLK_a:
                    gDstRectSprite.x -= 32;
                    break;
                case SDLK_s:
                    gDstRectSprite.y += 20;
                    break;
                case SDLK_d:
                    gDstRectSprite.x += 32;
                    break;
                }
            }
            if (event.type == SDL_QUIT)
            {
                return close();
            }
        }
    }
    return 1;  // Should never reach here
}


//start up SDL and create window
bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return showError();

    if ((gWindow = SDL_CreateWindow(
         "An SDL2 window",                   // window title
         SDL_WINDOWPOS_UNDEFINED,            // initial x position
         SDL_WINDOWPOS_UNDEFINED,            // initial y position
         640,                                // width, in pixels
         400,                                // height, in pixels
         SDL_WINDOW_SHOWN                    // flags - see below
       )) == NULL) return showError();

    gMainRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    return true;
}


//loads media
bool loadMedia()
{
    gGear = IMG_Load("gear.png");
    if (gGear == NULL) return showError();

    gSprite = IMG_Load("ex_mob_member_idle.png");
    if (gSprite == NULL) return showError();

    gWoodTile = IMG_Load("wood_tile.png");
    if (gWoodTile == NULL) return showError();

    return true;
}


//frees media and shuts down SDL
int close()
{
    SDL_FreeSurface(gGear);
    gGear = NULL;
    SDL_FreeSurface(gWoodTile);
    gWoodTile = NULL;
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    SDL_DestroyRenderer(gMainRenderer);
    gMainRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
    return 0;
}


bool showError()
{
    printf("SDL Error: %s\n", SDL_GetError());
    return false;
}
