#ifndef __DRAW__
#define __DRAW__

// Dimensions of Display
#define WIDTH 32
#define HEIGHT 16

struct pixel {
    unsigned char G;
	unsigned char R;
	unsigned char B;
} typedef Pixel;

// Common colors
static Pixel PIXEL_BLACK = { 0, 0, 0 };
static Pixel PIXEL_CYAN = { 128, 0, 128 };
static Pixel PIXEL_RED = { 0, 128, 0 };
static Pixel PIXEL_GREEN = { 128, 0, 0 };
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
extern void fadeOut(int s);
// fades all pixels with speed s
extern void fadeOutExclude(int s, Pixel pixel);
// fades pixels with speed s, if below threshold ref pixel, sets to ref pixel
extern void drawBackground(Pixel pixel);
//this will overwrite everything so call early, forceful overwrite all pixels with ref
extern void clearDisplay(void);
#endif
