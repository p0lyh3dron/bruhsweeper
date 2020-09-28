#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "SDL.h"

#include "../../inc/shared/minesweeper.h"

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
	    running = false;
        while (SDL_PollEvent(&e))
        {
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    MinesweeperGame m;
    game_init( &m, 10, 10, 10, NULL );
    game_printf( &m );
    game_delete( &m );
    
    return 0;
}

