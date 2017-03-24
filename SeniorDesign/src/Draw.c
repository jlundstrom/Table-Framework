#include "Draw.h"
#include <math.h>
#include <stdint.h>
Pixel Pixels[WIDTH * HEIGHT];
int_fast8_t xMove[]={1,0,-1,0};
int_fast8_t yMove[]={0,1,0,-1};
uint_fast8_t refArray [WIDTH][HEIGHT];
Point stackMax[WIDTH*HEIGHT];

// Pixels are stored to be optimal for sending to ws2812b leds from the microprocess

//prototypes
Pixel getPixel(int x, int y);
void setPixel(int x, int y, Pixel pixel);
void drawRect(int x, int y, int x2, int y2, Pixel pixel) ;
void drawCircle(int x0, int y0, int radius, Pixel pixel);
void fadeOut(int s);
void fadeOutExclude(int s, Pixel pixel);
int comparePixel(Pixel pixel1, Pixel pixel2);
void drawBackground(Pixel pixel);
void drawLine(int x1,int y1, int x2, int y2, Pixel pixel);
void circlePlotPoint(int xc,int yc,int x,int y, Pixel pixel);
void drawCircleEmpty(int xc, int yc, int radius, Pixel pixel);
void clearDisplay(void);
void scanWall(Pixel pixel);
int inBounds(int x, int y);
int breakOut(Point point);
void floodFill(int xo, int yo, Pixel fill, Pixel wall);

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

int comparePixel(Pixel pixel1, Pixel pixel2) //return 0 if not equal, 1 for equal
{
    if((pixel1.R==pixel2.R)&&(pixel1.G==pixel2.G)&&(pixel1.B==pixel2.B))
    {
        return 1;
    }
    else
    {
        return 0;
    }
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

int sign(x)
{
if(x>0)
 return 1;
else if(x<0)
 return -1;
else
 return 0;
}

void drawLine(int x1,int y1, int x2, int y2, Pixel pixel)
{
    int x,y,dx,dy,swap,temp,s1,s2,p,i;

    x=x1;
    y=y1;
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    s1=sign(x2-x1);
    s2=sign(y2-y1);
    swap=0;
    setPixel(x1,y1,pixel);
    if(dy>dx)
        {
        temp=dx;
        dx=dy;
        dy=temp;
        swap=1;
        }
    p=2*dy-dx;
    for(i=0;i<dx;i++)
        {
        setPixel(x,y,pixel);
        while(p>=0)
        {
            p=p-2*dx;
            if(swap)
                x+=s1;
            else
                y+=s2;
        }
        p=p+2*dy;
        if(swap)
            y+=s2;
        else
            x+=s1;
 }
setPixel(x2,y2,pixel);
}

void drawCircleEmpty(int xc, int yc, int radius, Pixel pixel)
{
    int p,y,x;
    x=0;
    y=radius;
    p=3-2*radius;
    while(x<y)
    {
       x++;
       if(p<0) p+=4*x+6;
       else
       {
             y--;
             p+=4*(x-y)+10;
       }
       circlePlotPoint(xc,yc,x,y,pixel);
     }
}

void circlePlotPoint(int xc,int yc,int x,int y, Pixel pixel)
{
  setPixel(xc+x,yc+y,pixel);
  setPixel(xc-x,yc+y,pixel);
  setPixel(xc+x,yc-y,pixel);
  setPixel(xc-x,yc-y,pixel);
  setPixel(xc+y,yc+x,pixel);
  setPixel(xc-y,yc+x,pixel);
  setPixel(xc+y,yc-x,pixel);
  setPixel(xc-y,yc-x,pixel);
}

void clearDisplay(void) {
	Pixel blank = { 0,0,0 };
	drawRect(0, 0, WIDTH, HEIGHT, blank);
}

void scanWall(Pixel pixel) //sets ref array to 1 if wall
{
   int u,i;
   for(u=0;u<WIDTH;u++)
   {
       for(i=0;i<HEIGHT;i++)
       {
           if(comparePixel(pixel,getPixel(u,i))==1)
               {
                   refArray[u][i]=1;
               }
           else
               {
                   refArray[u][i]=0;
               }
       }
   }
}

int inBounds(int x, int y)
{
    if(x<WIDTH&&x>=0&&y<HEIGHT&&y>=0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void floodFill(int xo, int yo, Pixel fill, Pixel wall)
{
    int i,x,y,flag=0,pointer=0;
    x=xo;
    y=yo;
    scanWall(wall);
    refArray[x][y]=1;
    while(pointer <= 0)
    {
        flag=0;
        for(i=0;i<4;i++)
        {
            if(inBounds(xMove[i]+x,yMove[i]+y)==1)
            {
                if(refArray[xMove[i]+x][yMove[i]+y]==0)
                {
                    stackMax[pointer].x=xMove[i]+x;
                    stackMax[pointer].y=yMove[i]+y;
                    refArray[xMove[i]+x][yMove[i]+y]=1;
                    setPixel(xMove[i]+x,yMove[i]+y,fill);
                    pointer++;
                }
                else
                {
                    flag++;
                }
            }
            else
            {
                flag++;
            }
            if(flag==3)
            {
                pointer--;
            }
        }
        x=stackMax[pointer].x;
        y=stackMax[pointer].y;
    }
}
