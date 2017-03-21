#ifndef __RANDOM__
#define __RANDOM__
#include "Draw.h"

// Get a random integer
extern unsigned int getRandom();
// Get a random integer 0-2^8
extern unsigned int getRandomLow();
// Get a random integer 0-2^9
extern unsigned int getRandomLowExtend();
// Update SEED do not use 0
extern void updateSEED(unsigned int);
// Get a color with a random R, G, B value
extern Pixel getRandomPixel();
#endif
