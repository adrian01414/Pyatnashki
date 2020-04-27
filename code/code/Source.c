#include <stdio.h>
#include <SDL.h>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Err: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Pyatnashki", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (NULL == window) {
        printf("Err: %s", SDL_GetError);
        return -1;
    }

    SDL_Event windowEvent;
    while (1) {
        if (SDL_PollEvent(&windowEvent)) {
            if (SDL_QUIT == windowEvent.type) break;
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}