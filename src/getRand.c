#include "getRand.h"

int getRand(int min, int max) { return rand() % (max - min) + min; }
