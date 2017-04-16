#ifndef __DRAW__
#define __DRAW__
#include <stdint.h>
// Dimensions of Display
#define WIDTH 32
#define HEIGHT 16
#define areaArray (WIDTH * HEIGHT)

struct pixel {
    unsigned char G;
	unsigned char R;
	unsigned char B;
} typedef Pixel;

struct point {
    char x;
    char y;
} typedef Point;



// Common colors
static Pixel PIXEL_BLACK = { 0, 0, 0 };
static Pixel PIXEL_CYAN = { 128, 0, 128 };
static Pixel PIXEL_RED = { 0, 128, 0 };
static Pixel PIXEL_GREEN = { 128, 0, 0 };
static Pixel PIXEL_BLUE = { 0, 0, 128 };
static Pixel PIXEL_YELLOW = { 255, 255, 0 };
static Pixel PIXEL_ORANGE = { 165, 255, 0 };
static Pixel PIXEL_PURPLE = { 0, 255, 255 };
static Pixel PIXEL_WHITE = { 255, 255, 255 };

// Holds display data
extern Pixel Pixels[];

// Retrieve pixel of x and y position
extern Pixel getPixel(int x, int y);
// set color for pixel at x and y position
extern void setPixel(int x, int y, Pixel pixel);
// Draw a rectangle from x,y with a specified color, width and height
extern void drawRect(int x, int y, int w, int h, Pixel pixel);
// Draws a black rectangle to cover the entire display
extern void drawCircle(int x0, int y0, int radius, Pixel pixel);
// Draws a circle with radius R from centerpoint, filled
extern void drawCircleEmpty(int xc, int yc, int radius, Pixel pixel);
//draw a circle at point xc,yc with radius and set color
extern void fadeOut(int s);
// fades all pixels with speed s
extern void fadeOutTo(int s, Pixel pixel);
// fades pixels with speed s, if below threshold ref pixel, sets to ref pixel
extern void fadeOutExclude(int s, Pixel pixel);
// fades all pixels with speed s, excludes ref pixel
extern void drawBackground(Pixel pixel);
//this will overwrite everything so call early, forceful overwrite all pixels with ref
extern int comparePixel(Pixel pixel1, Pixel pixel2);
//return 0 if not equal, 1 for equal
extern void drawLine(int x1,int y1, int x2, int y2, Pixel pixel);
//draws a line between two points, generalized bresenham
extern void floodFill(int xo, int yo, Pixel fill, Pixel wall);
//floodfill algo, fill == fill color, wall==color marked as the barrier
extern void toString(char string[], int bottomtop, Pixel color);
//0 1 for bottom top len 4 max for the string
extern void printTextOffset(char text, int x, int y, Pixel color);
//prints from bottom left going up 7, right 5
extern void toStringInvert(char string[], int bottomtop, Pixel color);
//0 1 for bottom top len 4 max for the string, prints not the text, so background printer basically, super janky dont use
extern void printTextOffsetInvert(char text, int x, int y, Pixel color);
//prints from bottom left going up 7, right 5, prints not the text


extern void clearDisplay(void);
extern Pixel HSV2RGB(int H, int S, int V);
extern int inBounds(int x, int y);
//returns 1 if inside boundaries
//HSV/HSB to RGB
#endif
