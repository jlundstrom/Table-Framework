#include "App_Clock.h"
#include "Draw.h"
#include "Noise.h"
#include "Input.h"
#include <string.h>

struct appData
{
   int           frame;
   unsigned char flag;
   unsigned char fadeoutFlag;
}
typedef   appData;
char string[5];
char string2[5];

appData *appClock_Data;
void Demo_Clock_Init(void);
void Demo_Clock_Tick(void);
void Demo_Clock_Deinit(void);
void App_Clock_Init(void);
void App_Clock_Tick(void);
void App_Clock_Deinit(void);
void App_Clock_New(App *app);

void Demo_Clock_Init(void)
{
   appClock_Data        = &AppStorage;
   appClock_Data->frame = 0;
   appClock_Data->flag  = 0;
}


void Demo_Clock_Tick(void)
{
   Pixel pixel;

   pixel.R = 0;
   pixel.G = 0;
   pixel.B = 0;
   drawBackground(pixel);
   strncpy(string, time, 5);
   strncpy(string2, date, 5);
   pixel.R = 255;
   pixel.G = 0;
   pixel.B = 0;
   toString(string, 0, pixel);
   toString(string2, 1, pixel);
}


void Demo_Clock_Deinit(void)
{
   appClock_Data->frame = 0;
   appClock_Data        = 0;
}


void App_Clock_Init(void)
{
   appClock_Data              = &AppStorage;
   appClock_Data->frame       = 240;
   appClock_Data->flag        = 0;
   appClock_Data->fadeoutFlag = 250;

}


void App_Clock_Tick(void)
{

}


void App_Clock_Deinit(void)
{
   int i;

   for (i = 0; i < sizeof(appData); i++)
   {
      AppStorage[i] = 0;
   }

   appClock_Data = 0;
}


void App_Clock_New(App *app)
{
   app->Demo_Init   = &Demo_Clock_Init;
   app->Demo_Tick   = &Demo_Clock_Tick;
   app->Demo_Deinit = &Demo_Clock_Deinit;
   app->App_Init    = &App_Clock_Init;
   app->App_Tick    = &App_Clock_Tick;
   app->App_Deinit  = &App_Clock_Deinit;
}
