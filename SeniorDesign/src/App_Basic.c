#include "App_Basic.h"
#include "Draw.h"
#include "Input.h"

struct appBasic_Data
{
   int x;
   int y;
   int frame;
   Pixel color;
   Pixel prevColor;
}
typedef   appBasic_Data;
appBasic_Data *Basic_Data;

void Demo_Init(void)
{
   Basic_Data        = AppStorage;
   Basic_Data->x     = 2;
   Basic_Data->y     = 0;
   Basic_Data->frame = 0;
   Basic_Data->color = PIXEL_CYAN;

}


void Demo_Tick(void)
{
   if (Basic_Data->frame == 1)
   {
      Basic_Data->frame = 0;
      setPixel(Basic_Data->x, Basic_Data->y, PIXEL_BLACK);
      Basic_Data->x++;
      if (Basic_Data->x == WIDTH)
      {
         Basic_Data->y++;
         Basic_Data->x = 2;
      }
      if (Basic_Data->y == HEIGHT)
      {
         Basic_Data->y = 0;
      }
      setPixel(Basic_Data->x, Basic_Data->y, PIXEL_CYAN);
   }
   Basic_Data->frame++;
}


void Demo_Deinit(void)
{
   Basic_Data->x     = 0;
   Basic_Data->y     = 0;
   Basic_Data->frame = 0;

   Basic_Data = 0;
}


void App_Init(void)
{
   Basic_Data        = AppStorage;
   Basic_Data->x     = 2;
   Basic_Data->y     = 0;
   Basic_Data->frame = 0;
   Basic_Data->color = PIXEL_CYAN;
}


void App_Tick(void)
{
   if (Basic_Data->frame == 4)
   {
      Basic_Data->frame = 0;
      if (Input_Status)
      {
		  if (!(Input_Status & A_INPUT))
		  {
			  setPixel(Basic_Data->x, Basic_Data->y, Basic_Data->prevColor);
		 }
         
         if (Input_Status & UP_INPUT)
         {
            Basic_Data->y--;
         }
         if (Input_Status & DOWN_INPUT)
         {
            Basic_Data->y++;
         }
         if (Input_Status & LEFT_INPUT)
         {
            Basic_Data->x--;
         }
         if (Input_Status & RIGHT_INPUT)
         {
            Basic_Data->x++;
         }
         if (Input_Tap & B_INPUT)
         {
			 if (comparePixel(Basic_Data->color, PIXEL_BLACK))
			 {
				 Basic_Data->color = PIXEL_CYAN;
			 }
			 else if (comparePixel(Basic_Data->color, PIXEL_CYAN))
			 {
				 Basic_Data->color = PIXEL_RED;
			 }
			 else if (comparePixel(Basic_Data->color, PIXEL_RED))
			 {
				 Basic_Data->color = PIXEL_GREEN;
			 }
			 else if (comparePixel(Basic_Data->color, PIXEL_GREEN))
			 {
				 Basic_Data->color = PIXEL_BLUE;
			 }
			 else if (comparePixel(Basic_Data->color, PIXEL_BLUE))
			 {
				 Basic_Data->color = PIXEL_YELLOW;
			 }
			 else if (comparePixel(Basic_Data->color, PIXEL_YELLOW))
			 {
				 Basic_Data->color = PIXEL_ORANGE;
			 }
			 else if (comparePixel(Basic_Data->color, PIXEL_ORANGE))
			 {
				 Basic_Data->color = PIXEL_PURPLE;
			 }
			 else if (comparePixel(Basic_Data->color, PIXEL_PURPLE))
			 {
				 Basic_Data->color = PIXEL_WHITE;
			 }
			 else if (comparePixel(Basic_Data->color, PIXEL_WHITE))
			 {
				 Basic_Data->color = PIXEL_BLACK;
			 }
         }

		 Input_Tap &= ~(UP_INPUT | DOWN_INPUT | LEFT_INPUT | RIGHT_INPUT | A_INPUT | B_INPUT);

         if (Basic_Data->x < 0)
         {
            Basic_Data->x = WIDTH - 1;
         }

         if (Basic_Data->y < 0)
         {
            Basic_Data->y = HEIGHT - 1;
         }
         Basic_Data->x = Basic_Data->x % WIDTH;
         Basic_Data->y = Basic_Data->y % HEIGHT;
		 Basic_Data->prevColor = getPixel(Basic_Data->x, Basic_Data->y);
         setPixel(Basic_Data->x, Basic_Data->y, Basic_Data->color);
      }
   }
   Basic_Data->frame++;
}


void App_Deinit(void)
{
   int i;

   for (i = 0; i < sizeof(appBasic_Data); i++)
   {
      _AppStorage[i] = 0;
   }

   Basic_Data = 0;
}


void App_Basic_New(App *app)
{
   app->Demo_Init   = &Demo_Init;
   app->Demo_Tick   = &Demo_Tick;
   app->Demo_Deinit = &Demo_Deinit;
   app->App_Init    = &App_Init;
   app->App_Tick    = &App_Tick;
   app->App_Deinit  = &App_Deinit;
}
