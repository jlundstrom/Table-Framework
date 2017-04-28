#include "App_Cloud.h"
#include "Draw.h"
#include "Noise.h"
#include "Input.h"
//this is literally just the noise.h cloud function, user defined, also ignore the defines
#define LEFT_INPUT     0x04
#define RIGHT_INPUT    0x08

#define DIRECTION          0x0F
#define DIRECTION_UP       2
#define DIRECTION_LEFT     3
#define DIRECTION_DOWN     0
#define DIRECTION_RIGHT    1

struct appData
{
   int           frame;
   int           base;
   int           size;
   int           hue;
   unsigned char flag;

}

typedef   appData;
appData *appCloud_Data;
void Demo_Cloud_Init(void);
void Demo_Cloud_Tick(void);
void Demo_Cloud_Deinit(void);
void App_Cloud_Init(void);
void App_Cloud_Tick(void);
void App_Cloud_Deinit(void);
void App_Cloud_New(App *app);
void errorCheck();

void Demo_Cloud_Init(void)
{
   appCloud_Data        = AppStorage;
   appCloud_Data->frame = 0;
   appCloud_Data->flag  = 0;
}


void Demo_Cloud_Tick(void)
{
   Pixel pixel;
   pixel.R = 0;
   pixel.G = 0;
   pixel.B = 0;
   drawBackground(pixel);
   char string[5]  = { 'C', 'L', 'O', 'U', 'D' };
   char string2[5] = { 'D', 'S', 'P', 'L', 'Y' };
   pixel.R = 200;
   pixel.G = 50;
   pixel.B = 255;
   toString(string, 0, pixel);
   toString(string2, 1, pixel);
}


void Demo_Cloud_Deinit(void)
{
   appCloud_Data->frame = 0;
   appCloud_Data        = 0;
}


void App_Cloud_Init(void)
{
   appCloud_Data              = AppStorage;
   appCloud_Data->frame       = 0;
   appCloud_Data->flag        = 0;
   appCloud_Data->hue       = 0;
   appCloud_Data->base        = 5;
   appCloud_Data->size        = 3;


}


void App_Cloud_Tick(void)
{
    generateNoise();
    if (Input_Tap)
          {
              if (Input_Tap & UP_INPUT)
               {
                  appCloud_Data->base+=5;
               }
               else if (Input_Tap & DOWN_INPUT)
               {
                   appCloud_Data->base-=5;
               }
               else if (Input_Tap & LEFT_INPUT)
               {
                   appCloud_Data->hue-=5;
               }
               else if (Input_Tap & RIGHT_INPUT)
               {
                   appCloud_Data->hue+=5;
               }
             if (Input_Tap & B_INPUT)
             {
                 appCloud_Data->size--;
             }
             if (Input_Tap & A_INPUT)
             {
                 appCloud_Data->size++;
             }
          }
          if (User2_Input_Tap)
          {
              if (User2_Input_Tap & UP_INPUT)
               {
                  appCloud_Data->base+=5;
               }
               else if (User2_Input_Tap & DOWN_INPUT)
               {
                   appCloud_Data->base-=5;
               }
               else if (User2_Input_Tap & LEFT_INPUT)
               {
                   appCloud_Data->hue-=5;
               }
               else if (User2_Input_Tap & RIGHT_INPUT)
               {
                   appCloud_Data->hue+=5;
               }
             if (User2_Input_Tap & B_INPUT)
             {
                 appCloud_Data->size--;
             }
             if (User2_Input_Tap & A_INPUT)
             {
                 appCloud_Data->size++;
             }
          }
          Input_Tap &= ~(LEFT_INPUT | RIGHT_INPUT | UP_INPUT | DOWN_INPUT | A_INPUT | B_INPUT);
          User2_Input_Tap &= ~(LEFT_INPUT | RIGHT_INPUT | UP_INPUT | DOWN_INPUT | A_INPUT | B_INPUT);
          errorCheck();
          drawCloudColorRotate(appCloud_Data->hue,appCloud_Data->size,appCloud_Data->base);
}


void App_Cloud_Deinit(void)
{
    int i;

    for (i = 0; i < sizeof(appData); i++)
    {
        _AppStorage[i] = 0;
    }

    appCloud_Data = 0;
}


void App_Cloud_New(App *app)
{
   app->Demo_Init   = &Demo_Cloud_Init;
   app->Demo_Tick   = &Demo_Cloud_Tick;
   app->Demo_Deinit = &Demo_Cloud_Deinit;
   app->App_Init    = &App_Cloud_Init;
   app->App_Tick    = &App_Cloud_Tick;
   app->App_Deinit  = &App_Cloud_Deinit;
}

void errorCheck()
{
    if(appCloud_Data->base>512)
    {
        appCloud_Data->base=0;
    }
    if(appCloud_Data->base<0)
    {
        appCloud_Data->base=0;
    }
    if(appCloud_Data->hue>360)
    {
        appCloud_Data->hue=0;
    }
    if(appCloud_Data->hue<0)
    {
        appCloud_Data->hue=360;
    }
    if(appCloud_Data->size>512)
    {
        appCloud_Data->size=0;
    }
    if(appCloud_Data->size<0)
    {
        appCloud_Data->size=0;
    }
}
