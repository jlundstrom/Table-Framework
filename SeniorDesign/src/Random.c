#include "Random.h"
#include <stdlib.h>

void getRandomSeeder();
#define MULT 31821  // only X-X-Even-2-1 allowed
#define INC 13849

unsigned int SEED = 241;
unsigned int current =0;


unsigned int getRandom() {
    current=SEED * MULT + INC % 65536;   //0-2^16 can be adjusted for wider range
    SEED = current;
    getRandomSeeder();
    return current;
}

void getRandomSeeder() {
    SEED = rand();
}
void updateSEED(unsigned int s){ //re-seed with only 1-64k
    SEED = s;
}

unsigned char getRandomLow(){  //0-2^8
    return (unsigned char)(getRandom() & 0x00FF);
}

unsigned int getRandomLowExtend(){ //0-2^9
    unsigned int i= getRandomLow();
    if(i<256){
        return(i);
    }
    else{
        return(i*2);
    }
}


Pixel getRandomPixel() {
	Pixel p;
	p.R = rand();
	p.G = rand();
	p.B = rand();
	return p;
}

