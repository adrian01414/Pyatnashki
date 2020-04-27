#include <stdio.h>
#include <time.h>
#include <SDL.h>

#define WIDTH 600
#define HEIGHT 600

int getRand(int min, int max) {
    return rand() % (max - min) + min;
}

/*void cDisplay(int* obj) {
    for (int i = 0; i < 16; i++) {
        printf("%2d", obj[i]);
        if (i % 3 == 0) printf("\n");
    }
}

void getNumber(int* obj) {
    int arr[17];
    for (int i = 1; i <= 16; i++) {
        arr[i] = 1;
    }
    int temp = 0;
    for (int i = 0; i < 16; i++) {
        arr[i] = getRand(1, 16);

    }

}*/

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Err: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("Pyatnashki", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
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