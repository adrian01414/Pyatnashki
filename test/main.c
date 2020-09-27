#include <SDL2/SDL.h>
#include "../src/swap.h"
#include "../src/init.h"
#include "../src/load.h"
#include "../src/getRand.h"

#define CTEST_MAIN
#define CTEST_SEGFAULT

#include "ctest.h"

int main(int argc, const char *argv[])
{
    int result = ctest_main(argc, argv);

    return result;
}
