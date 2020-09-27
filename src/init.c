#include "init.h"

int init(SDL_Window** window, SDL_Surface** screen_surface) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("Err: %s", SDL_GetError());
  }

  *window = SDL_CreateWindow("Pyatnashki", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 600, 600,
                            SDL_WINDOW_ALLOW_HIGHDPI);

  if (NULL == *window) {
    return 1;
  }

  *screen_surface = SDL_GetWindowSurface(*window);
  SDL_FillRect(*screen_surface, NULL,
               SDL_MapRGB((*screen_surface)->format, 0, 0, 0));

  return 0;
}

