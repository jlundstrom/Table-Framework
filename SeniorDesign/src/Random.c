#include "Random.h"
#include <stdlib.h>
unsigned int getRandom() {
	return rand();
}

Pixel getRandomPixel() {
	Pixel p;
	p.R = rand();
	p.G = rand();
	p.B = rand();
	return p;
}