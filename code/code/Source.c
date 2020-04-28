#include <stdio.h>
#include <time.h>
#include <SDL.h>

#define WIDTH 600
#define HEIGHT 600

SDL_Window* window;
SDL_Renderer* renderer;


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int getRand(int min, int max) {
    return rand() % (max - min) + min;
}

void cDisplay(int obj[16]) {
    for (int i = 1; i < 17; i++) {
        if (obj[i-1] != 0) printf("%3d", obj[i - 1]);
        else printf("   ");
        if (i % 4 == 0) printf("\n");
    }
}

void getNumbers(int obj[16]) {
    int arr[17];
    for (int i = 1; i <= 16; i++) {
        arr[i] = 1;
    }
    for (int i = 0; i < 15; i++) {
        obj[i] = getRand(1, 15);
        if (arr[obj[i]] == 0) {
            do{
                if (obj[i] >= 2) obj[i]--;
                else obj[i] = 15;
            } while (arr[obj[i]] == 0);
        }
        arr[obj[i]] = 0;
    }
    obj[15] = 0;
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Err: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Pyatnashki", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    if (NULL == window) {
        printf("Err: %s", SDL_GetError());
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