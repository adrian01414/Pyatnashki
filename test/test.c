#include <SDL2/SDL.h>
#include "../src/swap.h"
#include "../src/init.h"
#include "../src/load.h"
#include "../src/getRand.h"
#include <stdlib.h>
#include "ctest.h"

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Surface* area = NULL;
SDL_Surface* block = NULL;
SDL_Surface* title = NULL;
SDL_Surface* numbers[15];
SDL_Surface* areawin = NULL;

CTEST(notSDL, test1_getRand) {
    int a = getRand(1, 5);
    if(a >= 1 && a <= 5) {
    	return ASSERT_EQUAL(1, 1);
    } else {
    	ASSERT_FAIL();
    }
}

CTEST(notSDL, test2_swap) {
	int a = 1, b = 2;
	swap(&a, &b);
	if(a == 2 && b == 1) {
		return ASSERT_EQUAL(1, 1);
	} else {
    		ASSERT_FAIL();
    	}
}

CTEST(SDL, test3_load) {
	int a = load(&area, &block, &title, numbers, &areawin);
	if(a == 0) {
		return ASSERT_EQUAL(1, 1);
	} else {
    		ASSERT_FAIL();
    	}
}

CTEST(SDL, test3_init) {
	int a = init(&window, &screen_surface);
	if(a == 0) {
		return ASSERT_EQUAL(1, 1);
	} else {
    		ASSERT_FAIL();
    	}
}
