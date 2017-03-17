#ifndef __DRAW__
#define __DRAW__

#ifdef DEBUG
#define WIDTH 32
#define HEIGHT 16
#else
#define WIDTH 32
#define HEIGHT 16
#endif // DEBUG

struct pixel {
    unsigned char G;
	unsigned char R;
	unsigned char B;
} typedef Pixel;

static Pixel PIXEL_BLACK = { 0, 0, 0 };
static Pixel PIXEL_CYAN = { 128, 0, 128 };
static Pixel PIXEL_RED = { 0, 128, 0 };
static Pixel PIXEL_GREEN = { 128, 0, 0 };
static Pixel PIXEL_WHITE = { 255, 255, 255 };


extern Pixel Pixels[];
extern Pixel getPixel(int x, int y);
extern void setPixel(int x, int y, Pixel pixel);
extern void drawRect(int x, int y, int w, int h, Pixel pixel);
extern void clearDisplay(void);
#endif
