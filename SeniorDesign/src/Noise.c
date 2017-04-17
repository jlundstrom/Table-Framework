#include "Random.h"
#include "Draw.h"
#include "Noise.h"


double noise[noiseHeight][noiseWidth];

void generateNoise() //run first to populate
{
   int y;
   int x;

   for (y = 0; y < noiseHeight; y++)
   {
      for (x = 0; x < noiseWidth; x++)
      {
         noise[y][x] = (getRandom() % 32768) / 32768.0;
      }
   }
}


double smoothNoise(double x, double y)
{
   //get fractional part of x and y
   double fractX = x - (int)x;
   double fractY = y - (int)y;

   //wrap around
   int x1 = ((int)x + noiseWidth) % noiseWidth;
   int y1 = ((int)y + noiseHeight) % noiseHeight;

   //neighbor values
   int x2 = (x1 + noiseWidth - 1) % noiseWidth;
   int y2 = (y1 + noiseHeight - 1) % noiseHeight;

   //smooth the noise with bilinear interpolation
   double value = 0.0;

   value += fractX * fractY * noise[y1][x1];
   value += (1 - fractX) * fractY * noise[y1][x2];
   value += fractX * (1 - fractY) * noise[y2][x1];
   value += (1 - fractX) * (1 - fractY) * noise[y2][x2];

   return value;
}


double turbulence(double x, double y, double size) //size is zoom factor
{
   double value = 0.0, initialSize = size;

   while (size >= 1)
   {
      value += smoothNoise(x / size, y / size) * size;
      size  /= 3.0;
   }

   return(128.0 * value / initialSize);  //scaled for 0-255
}


void drawCloud(int RGB) // send 1,2,3 for which color to not hold constant
{
   if (!((RGB < 4) && (RGB > 0)))
   {
      return;
   }
   int   x;
   int   y;
   char  color;
   Pixel pixel;
   pixel.R = 0;
   pixel.G = 0;
   pixel.B = 0;
   for (x = 0; x < noiseWidth; x++)
   {
      for (y = 0; y < noiseHeight; y++)
      {
         color = 5 + (char)turbulence(x, y, 3);
         if (RGB == 1)
         {
            pixel.R = color;
            setPixel(x, y, pixel);
         }
         if (RGB == 2)
         {
            pixel.G = color;
            setPixel(x, y, pixel);
         }
         if (RGB == 3)
         {
            pixel.B = color;
            setPixel(x, y, pixel);
         }
      }
   }
}


void drawCloudColor(int hue)
{
   int   x;
   int   y;
   int   temp;
   Pixel pixel;

   for (x = 0; x < noiseWidth; x++)
   {
      for (y = 0; y < noiseHeight; y++)
      {
         temp  = 10 + turbulence(x, y, 3);
         pixel = HSV2RGB(hue, 255, temp);
         setPixel(x, y, pixel);
      }
   }
}

void drawCloudColorRotate(int hue, int size, int base)
{
   int   x;
   int   y;
   int   temp;
   Pixel pixel;

   for (x = 0; x < noiseWidth; x++)
   {
      for (y = 0; y < noiseHeight; y++)
      {
         temp  = base + turbulence(x, y, size);
         pixel = HSV2RGB(hue, 255, temp);
         setPixel(x, y, pixel);
      }
   }
}
