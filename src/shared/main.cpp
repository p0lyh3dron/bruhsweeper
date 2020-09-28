#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "SDL.h"


int main(int argc, char* argv[])
{
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow(
        "bruhsweeper",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (window == NULL)
    {
        printf("Could not create window: \n");
        return 1;
    }

    // enter main loop (SDL_PollEvent())
    SDL_Event e;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

