#include "load.h"

int load(SDL_Surface** area, SDL_Surface** block, SDL_Surface** title, SDL_Surface* numbers[15], SDL_Surface** areawin) {
  *area = SDL_LoadBMP("area.bmp");
  *block = SDL_LoadBMP("block.bmp");
  *title = SDL_LoadBMP("title.bmp");
  *areawin = SDL_LoadBMP("areawin.bmp");
  numbers[0] = SDL_LoadBMP("numbers/1.bmp");
  numbers[1] = SDL_LoadBMP("numbers/2.bmp");
  numbers[2] = SDL_LoadBMP("numbers/3.bmp");
  numbers[3] = SDL_LoadBMP("numbers/4.bmp");
  numbers[4] = SDL_LoadBMP("numbers/5.bmp");
  numbers[5] = SDL_LoadBMP("numbers/6.bmp");
  numbers[6] = SDL_LoadBMP("numbers/7.bmp");
  numbers[7] = SDL_LoadBMP("numbers/8.bmp");
  numbers[8] = SDL_LoadBMP("numbers/9.bmp");
  numbers[9] = SDL_LoadBMP("numbers/10.bmp");
  numbers[10] = SDL_LoadBMP("numbers/11.bmp");
  numbers[11] = SDL_LoadBMP("numbers/12.bmp");
  numbers[12] = SDL_LoadBMP("numbers/13.bmp");
  numbers[13] = SDL_LoadBMP("numbers/14.bmp");
  numbers[14] = SDL_LoadBMP("numbers/15.bmp");
  if (*area == NULL || *block == NULL) {
    return 1;
  }
  return 0;
}

