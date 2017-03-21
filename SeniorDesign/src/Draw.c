#include "Draw.h"
Pixel Pixels[WIDTH * HEIGHT];
int areaArray = WIDTH * HEIGHT;
// Pixels are stored to be optimal for sending to ws2812b leds from the microprocess

// Retrieve pixel, and return first pixel for invalid inputs
Pixel getPixel(int x, int y) {
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0) {
		return Pixels[0];
	}
	if(y % 2 == 0)
	{
	    return Pixels[y * WIDTH + WIDTH - x - 1];
	}
	return Pixels[y * WIDTH + x];
}

// Only update pixel if a valid position is given
void setPixel(int x, int y, Pixel pixel) {
	if (x > WIDTH) {
		return;
	}
	if (y > HEIGHT) {
		return;
	}
	if (x < 0) {
		return;
	}
	if (y < 0) {
		return;
	}
    if(y % 2 == 0)
    {
        Pixels[y * WIDTH + WIDTH - x - 1] = pixel;
    }
    else
    {
        Pixels[y * WIDTH + x] = pixel;
    }
}

void drawRect(int x, int y, int x2, int y2, Pixel pixel) {
	int y1;
	if (x2 > WIDTH) {
		x2 = WIDTH;
	}
	if (y2 > HEIGHT) {
		y2 = HEIGHT;
	}
	if (x < 0) {
		x = 0;
	}
	if (y < 0) {
		y = 0;
	}
	for (; x < x2; x++) {
		for (y1 = y; y1 < y2; y1++) {
			setPixel(x, y1, pixel);
		}
	}
}

void drawCircle(int x0, int y0, int radius, Pixel pixel)
{
    int i;
    int r2 = radius * radius;
    int area = r2 << 2;
    int rr = radius << 1;
    int tx = 0;
    int ty = 0;
    for(i = 0; i < area; i++)
    {
        tx = (i % rr) - radius;
        ty = (i / rr) - radius;

        if (tx * tx + ty * ty <= r2)
            setPixel(x0 + tx, y0 + ty, pixel);
    }
}

void fadeOut(int s)
{
    int i;
    for (i =0; i<(areaArray);i++)
        {
            if(Pixels[i].G>(0+s))
                {
                    Pixels[i].G= Pixels[i].G-s;
                }
            if(Pixels[i].R>(0+s))
                {
                        Pixels[i].R= Pixels[i].R-s;
                }
            if(Pixels[i].B>(0+s))
                {
                        Pixels[i].B= Pixels[i].B-s;
                }

        }
    return;
}

void fadeOutExclude(int s, Pixel pixel)  //if outside threshold sets pixel to the exclude pixel
{
    int i;
    for (i =0; i<(areaArray);i++)
        {
            if((Pixels[i].G!=pixel.G)&&(Pixels[i].G>(0+s)))
                {
                    Pixels[i].G= Pixels[i].G-s;
                }
            else
                {
                    Pixels[i].G= pixel.G;
                }
            if((Pixels[i].R!=pixel.R)&&(Pixels[i].R>(0+s)))
                {
                        Pixels[i].R= Pixels[i].R-s;
                }
            else
                {
                    Pixels[i].R= pixel.R;
                }
            if((Pixels[i].B!=pixel.B)&&(Pixels[i].B>(0+s)))
                {
                        Pixels[i].B= Pixels[i].B-s;
                }
            else
                {
                    Pixels[i].B= pixel.B;
                }

        }
    return;
}

void drawBackground(Pixel pixel) //this will overwrite everything so call early
{
    int i;
    for(i=0;i<areaArray;i++)
    {
        Pixels[i]=pixel;
    }
    return;
}

void clearDisplay(void) {
	Pixel blank = { 0,0,0 };
	drawRect(0, 0, WIDTH, HEIGHT, blank);
}
