#include "App_Shooter.h"
#include "Draw.h"
#include "Noise.h"
#include "Input.h"

struct appData
{
   int           frame;
   int           frame2;
   unsigned char flag;
   unsigned char fadeoutFlag;
}

typedef   appData;
appData *appShoot_Data;
void Demo_Shoot_Init(void);
void Demo_Shoot_Tick(void);
void Demo_Shoot_Deinit(void);
void App_Shoot_Init(void);
void App_Shoot_Tick(void);
void App_Shoot_Deinit(void);
void App_Shoot_New(App *app);
void leftRotatebyOne(int arr[], int n);
int colors[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

void Demo_Shoot_Init(void)
{
   appShoot_Data        = &AppStorage;
   appShoot_Data->frame = 0;
   appShoot_Data->flag  = 0;
}


void Demo_Shoot_Tick(void)
{
    int i,k;
    Pixel pixel;
    for(k=1;k<3;k++)
    {
        for (i=0;i<16;i++)
        {
            switch(colors[i])
            {
            case 1:
                pixel.R=0;
                pixel.G=0;
                pixel.B=0;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 2:
                pixel.R=255;
                pixel.G=255;
                pixel.B=255;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 3:
                pixel.R=255;
                pixel.G=0;
                pixel.B=0;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 4:
                pixel.R=0;
                pixel.G=255;
                pixel.B=0;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 5:
                pixel.R=0;
                pixel.G=0;
                pixel.B=255;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 6:
                pixel.R=255;
                pixel.G=255;
                pixel.B=0;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 7:
                pixel.R=0;
                pixel.G=255;
                pixel.B=255;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 8:
                pixel.R=255;
                pixel.G=0;
                pixel.B=255;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 9:
                pixel.R=192;
                pixel.G=192;
                pixel.B=192;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 10:
                pixel.R=128;
                pixel.G=128;
                pixel.B=128;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 11:
                pixel.R=128;
                pixel.G=0;
                pixel.B=0;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 12:
                pixel.R=128;
                pixel.G=128;
                pixel.B=0;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 13:
                pixel.R=0;
                pixel.G=128;
                pixel.B=0;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 14:
                pixel.R=128;
                pixel.G=0;
                pixel.B=128;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 15:
                pixel.R=0;
                pixel.G=128;
                pixel.B=128;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            case 16:
                pixel.R=0;
                pixel.G=0;
                pixel.B=128;
                drawLine(i*k,0, i*k, 15,pixel);
                break;
            default:
                break;
            }
        }
    }
   leftRotatebyOne(colors, 16);
    char string[5]  = { 'S', 'H', 'O', 'O', 'T' };
    char string2[5] = { 'I', 'N', 'V', 'D', 'E' };
    pixel.R = 0;
    pixel.G = 0;
    pixel.B = 0;
    toStringInvert(string, 0, pixel);
    toStringInvert(string2, 1, pixel);
}


void Demo_Shoot_Deinit(void)
{
   appShoot_Data->frame = 0;
   appShoot_Data        = 0;
}


void App_Shoot_Init(void)
{

}


void App_Shoot_Tick(void) {


}


void App_Shoot_Deinit(void)
{
   int i;

   for (i = 0; i < sizeof(appData); i++)
   {
      AppStorage[i] = 0;
   }

   appShoot_Data = 0;
}


void App_Shoot_New(App *app)
{
   app->Demo_Init   = &Demo_Shoot_Init;
   app->Demo_Tick   = &Demo_Shoot_Tick;
   app->Demo_Deinit = &Demo_Shoot_Deinit;
   app->App_Init    = &App_Shoot_Init;
   app->App_Tick    = &App_Shoot_Tick;
   app->App_Deinit  = &App_Shoot_Deinit;
}

void leftRotatebyOne(int arr[], int n)
{
  int i, temp;
  temp = arr[0];
  for (i = 0; i < n-1; i++)
     arr[i] = arr[i+1];
  arr[i] = temp;
}
