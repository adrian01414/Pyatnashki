#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 600
#define HEIGHT 600
#define TRUE 1
#define FALSE 0

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Surface* area = NULL;
SDL_Surface* block = NULL;
SDL_Surface* title = NULL;
SDL_Surface* numbers[15];
SDL_Surface* areawin = NULL;

struct pyatna {
  int x;
  int y;
  int mas;
  int trueMas;
};

void swap(int *, int *);
int getRand(int, int);
void getNumbers(struct pyatna[16], int*, int*);
int init();
int load();
void quit();
void dsp(struct pyatna[16], SDL_Rect);

int main(int argc, char **args) {
  SDL_Rect rect;
  SDL_Rect rect2;
  SDL_Rect rect3;
  rect2.x = 60, rect2.y = 60;
  rect.x = 50, rect.y = 50;
  rect3.x = 0, rect3.y = 11;

  struct pyatna cells[16];
  for (int i = 0; i < 16; i += 4) {
    for (int j = 0; j < 4; j++) {
      cells[i + j].x = j;
      cells[i + j].y = i;
      cells[i + j].trueMas = i + j;
      cells[i + j].mas = cells[i + j].trueMas + 1;
    }
  }
  cells[15].mas = 0;
  if (init() == 1) {
    return 1;
  }

  if (load() == 1) {
    return 1;
  }
  SDL_BlitSurface(area, NULL, screen_surface, &rect);
  SDL_BlitSurface(title, NULL, screen_surface, &rect3);
  SDL_BlitSurface(block, NULL, screen_surface, &rect2);

  int ptrCell[2] = { 3, 12 };
  srand(time(0));
  getNumbers(cells, &ptrCell[0], &ptrCell[1]);
  dsp(cells, rect2);

  SDL_UpdateWindowSurface(window);

  SDL_Event windowEvent;
  int run = TRUE, win = FALSE, getRetry = FALSE, getUp = FALSE, getDown = FALSE,
      getRight = FALSE, getLeft = FALSE, getClick = FALSE;


  while (run == TRUE && win == FALSE) {
    while (SDL_PollEvent(&windowEvent) != 0) {
      if (windowEvent.key.keysym.sym == SDLK_x && windowEvent.type != SDL_MOUSEMOTION) {
        for (int i = 0; i < 16; i += 4) {
          for (int j = 0; j < 4; j++) {
            cells[i + j].mas = cells[i + j].trueMas + 1;
              if (j + i == 14) cells[i + j].mas = 0;
              if (j + i == 15) cells[i + j].mas = 15;
              ptrCell[0] = 2;
              ptrCell[1] = 12;
              dsp(cells, rect2);
          }
        }
      }

      if (windowEvent.key.keysym.sym == SDLK_r && windowEvent.type != SDL_MOUSEMOTION) {
        if (getRetry == TRUE) {
          getRetry = FALSE;
        } else {
          getNumbers(cells, &ptrCell[0], &ptrCell[1]);
          dsp(cells, rect2);
          getRetry = TRUE;
        }
      }

      if (windowEvent.type == SDL_QUIT)
        run = FALSE;
      if (windowEvent.key.keysym.sym == SDLK_ESCAPE && windowEvent.type != SDL_MOUSEMOTION)
        run = FALSE;
      if (windowEvent.key.keysym.sym == SDLK_UP) {
        if (getUp == TRUE) {
          getUp = FALSE;
        } else {
          if (ptrCell[1] == 0) {
            getUp = TRUE;
            continue;
          }
          swap(&cells[ptrCell[0] + ptrCell[1]].mas,
               &cells[ptrCell[0] + ptrCell[1] - 4].mas);
          ptrCell[1] -= 4;
          getUp = TRUE;
        }
      }
      if (windowEvent.key.keysym.sym == SDLK_DOWN) {
        if (getDown == TRUE) {
          getDown = FALSE;
        } else {
          if (ptrCell[1] == 12) {
            getDown = TRUE;
            continue;
          }
          swap(&cells[ptrCell[0] + ptrCell[1]].mas,
               &cells[ptrCell[0] + ptrCell[1] + 4].mas);
          ptrCell[1] += 4;
          getDown = TRUE;
        }
      }
      if (windowEvent.key.keysym.sym == SDLK_RIGHT) {
        if (getRight == TRUE) {
          getRight = FALSE;
        } else {
          if (ptrCell[0] == 3) {
            getRight = TRUE;
            continue;
          }
          swap(&cells[ptrCell[0] + ptrCell[1]].mas,
               &cells[ptrCell[0] + ptrCell[1] + 1].mas);
          ptrCell[0]++;
          getRight = TRUE;
        }
      }
      if (windowEvent.key.keysym.sym == SDLK_LEFT) {
        if (getLeft == TRUE) {
          getLeft = FALSE;
        } else {
          if (ptrCell[0] == 0) {
            getLeft = TRUE;
            continue;
          }
          swap(&cells[ptrCell[0] + ptrCell[1]].mas,
               &cells[ptrCell[0] + ptrCell[1] - 1].mas);
          ptrCell[0]--;
          getLeft = TRUE;
        }
      }

      if (windowEvent.button.button == 1) {
        if (getClick == TRUE) {
          getClick = FALSE;
        } else {
          if ((windowEvent.button.x < 61 || windowEvent.button.x > 539) ||
              windowEvent.button.y < 61 || windowEvent.button.y > 539) {
            getClick = TRUE;
            continue;
          } else {
            if ((ptrCell[0] == (windowEvent.button.x - 60) / 120 &&
              ptrCell[1] - 4 == ((windowEvent.button.y - 60) / 120) * 4) ||
              (ptrCell[0] == (windowEvent.button.x - 60) / 120 &&
                ptrCell[1] + 4 == ((windowEvent.button.y - 60) / 120) * 4) ||
              (ptrCell[0] - 1 == (windowEvent.button.x - 60) / 120 &&
                ptrCell[1] == ((windowEvent.button.y - 60) / 120) * 4) ||
              (ptrCell[0] + 1 == (windowEvent.button.x - 60) / 120 &&
                ptrCell[1] == ((windowEvent.button.y - 60) / 120) * 4)) {
              swap(&cells[ptrCell[0] + ptrCell[1]].mas,
                &cells[(windowEvent.button.x - 60) / 120 +
                ((windowEvent.button.y - 60) / 120) * 4]
                .mas);
              ptrCell[0] = (windowEvent.button.x - 60) / 120;
              ptrCell[1] = ((windowEvent.button.y - 60) / 120) * 4;
              getClick = TRUE;
            }
            else {
              getClick = TRUE;
              continue;
            }
          }
        }
      }

      dsp(cells, rect2);
      SDL_UpdateWindowSurface(window);
    }
    int game = TRUE;
    for (int i = 0; i < 16; i += 4) {
      for (int j = 0; j < 4; j++) {
        if (i + j < 15) {
          if (!(cells[i + j].mas == cells[i + j].trueMas + 1))
            game = FALSE;
        }else if(i + j == 15 && !(cells[i + j].mas == 0))
          game = FALSE;
      }
    }
    if (game == TRUE) {
      win = TRUE;
      run = FALSE;
      SDL_BlitSurface(areawin, NULL, screen_surface, &rect);
      SDL_UpdateWindowSurface(window);

    }
    
    while (run == FALSE && win == TRUE) {
      while (SDL_PollEvent(&windowEvent) != 0) {
        if (windowEvent.key.keysym.sym == SDLK_r && windowEvent.type != SDL_MOUSEMOTION) {
          if (getRetry == TRUE) {
            getRetry = FALSE;
          }
          else {
            getNumbers(cells, &ptrCell[0], &ptrCell[1]);
            dsp(cells, rect2);
            SDL_BlitSurface(area, NULL, screen_surface, &rect);
            getRetry = TRUE;
            win = FALSE;
            run = TRUE;
          }
        }
        
        if (windowEvent.type == SDL_QUIT) {
          run = FALSE;
          win = FALSE;
        }
        if (windowEvent.key.keysym.sym == SDLK_ESCAPE && windowEvent.type != SDL_MOUSEMOTION) {
          run = FALSE;
          win = FALSE;
        }
      }
    }
  }
  
  quit();
  return 0;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int getRand(int min, int max) { return rand() % (max - min) + min; }

void getNumbers(struct pyatna obj[16], int* x, int* y) {
    int zero[2];
    zero[0] = *x;
    zero[1] = *y;
    for (int i = 0; i < 1000; i++) {
        int randNum = getRand(1, 5);
        if (randNum == 1) {
            if (zero[1] == 0) {
                continue;
            }
            swap(&obj[zero[0] + zero[1]].mas,
                &obj[zero[0] + zero[1] - 4].mas);
            zero[1] -= 4;
        }
        if (randNum == 2) {
            if (zero[1] == 12) {
                continue;
            }
            swap(&obj[zero[0] + zero[1]].mas,
                &obj[zero[0] + zero[1] + 4].mas);
            zero[1] += 4;
        }
        if (randNum == 3) {
            if (zero[0] == 0) {
                continue;
            }
            swap(&obj[zero[0] + zero[1]].mas,
                &obj[zero[0] + zero[1] - 1].mas);
            zero[0] --;
        }
        if (randNum == 4) {
            if (zero[0] == 3) {
                continue;
            }
            swap(&obj[zero[0] + zero[1]].mas,
                &obj[zero[0] + zero[1] + 1].mas);
            zero[0] ++;
        }

    }
    *x = zero[0];
    *y = zero[1];
}

int init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("Err: %s", SDL_GetError());
  }

  window = SDL_CreateWindow("Pyatnashki", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                            SDL_WINDOW_ALLOW_HIGHDPI);

  if (NULL == window) {
    return 1;
  }

  screen_surface = SDL_GetWindowSurface(window);
  SDL_FillRect(screen_surface, NULL,
               SDL_MapRGB(screen_surface->format, 0, 0, 0));

  return 0;
}

int load() {
  area = SDL_LoadBMP("area.bmp");
  block = SDL_LoadBMP("block.bmp");
  title = SDL_LoadBMP("title.bmp");
  areawin = SDL_LoadBMP("areawin.bmp");
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
  if (area == NULL || block == NULL) {
    return 1;
  }
  return 0;
}

void quit() {
  SDL_FreeSurface(area);
  area = NULL;
  SDL_FreeSurface(block);
  block = NULL;
  SDL_FreeSurface(title);
  title = NULL;
  SDL_FreeSurface(areawin);
  areawin = NULL;
  for (int i = 0; i < 15; i++) {
    SDL_FreeSurface(numbers[i]);
    numbers[i] = NULL;
  }

  SDL_DestroyWindow(window);

  SDL_Quit();
}

void dsp(struct pyatna cells[16], SDL_Rect rect2) {
    for (int i = 0; i < 16; i += 4) {
        for (int j = 0; j < 4; j++) {
            SDL_BlitSurface(block, NULL, screen_surface, &rect2);
            rect2.x += 4;
            rect2.y += 4;
            SDL_BlitSurface(numbers[cells[i + j].mas - 1], NULL, screen_surface, &rect2);
            rect2.x += 116;
            rect2.y -= 4;
        }
        rect2.x = 60;
        rect2.y += 120;
    }

}

