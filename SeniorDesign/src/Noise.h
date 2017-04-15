#ifndef __NOISE__
#define __NOISE__

#define noiseWidth 32
#define noiseHeight 16


extern double noise[noiseHeight][noiseWidth]; //the noise array
extern void generateNoise(); //run first to fill array
extern double smoothNoise(double x, double y); //use for main noise gen
extern double turbulence(double x, double y, double size); //blob mode
extern void drawCloud(int RGB); //send a 1,2,3 command depending on color of clouds
extern void drawCloudColor(Pixel color); // draws a cloud with base pixel color
#endif
