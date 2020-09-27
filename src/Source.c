#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include "swap.h"
#include "init.h"
#include "load.h"
#include "getRand.h"

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


void getNumbers(struct pyatna[16], int*, int*);
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
  if (init(&window, &screen_surface) == 1) {
    return 1;
  }

  if (load(&area, &block, &title, numbers, &areawin) == 1) {
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

