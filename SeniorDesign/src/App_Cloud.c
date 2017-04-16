#include "App_Cloud.h"
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
appData *appCloud_Data;
void Demo_Cloud_Init(void);
void Demo_Cloud_Tick(void);
void Demo_Cloud_Deinit(void);
void App_Cloud_Init(void);
void App_Cloud_Tick(void);
void App_Cloud_Deinit(void);
void App_Cloud_New(App *app);


void Demo_Cloud_Init(void)
{
   appCloud_Data        = &AppStorage;
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
   appCloud_Data              = &AppStorage;
   appCloud_Data->frame       = 240;
   appCloud_Data->flag        = 0;

}


void App_Cloud_Tick(void)
{

}


void App_Cloud_Deinit(void)
{

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
