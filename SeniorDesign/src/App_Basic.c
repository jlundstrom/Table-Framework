<<<<<<< Updated upstream
#include "App_Basic.h"
#include "Draw.h"
#include "Input.h"

struct appBasic_Data
{
   int x;
   int y;
   int frame;
}
typedef   appBasic_Data;
appBasic_Data *Basic_Data;

void Demo_Init(void)
{
   Basic_Data        = &AppStorage;
   Basic_Data->x     = 2;
   Basic_Data->y     = 0;
   Basic_Data->frame = 0;
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
   Basic_Data        = &AppStorage;
   Basic_Data->x     = 2;
   Basic_Data->y     = 0;
   Basic_Data->frame = 0;
}


void App_Tick(void)
{
   if (Basic_Data->frame == 4)
   {
      Basic_Data->frame = 0;
      if (Input_Status)
      {
         setPixel(Basic_Data->x, Basic_Data->y, PIXEL_BLACK);
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
         if (Input_Status & A_INPUT)
         {
         }
         if (Input_Status & B_INPUT)
         {
         }

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
         setPixel(Basic_Data->x, Basic_Data->y, PIXEL_CYAN);
      }
   }
   Basic_Data->frame++;
}


void App_Deinit(void)
{
   int i;

   for (i = 0; i < sizeof(appBasic_Data); i++)
   {
      AppStorage[i] = 0;
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
=======
#include "App_Basic.h"
#include "Draw.h"
#include "Input.h"

struct appBasic_Data {
	int x;
	int y;
	int frame;
} typedef appBasic_Data;
appBasic_Data* Basic_Data;

void Demo_Init(void) {
	Basic_Data = &AppStorage;
	Basic_Data->x = 2;
	Basic_Data->y = 0;
	Basic_Data->frame = 0;
}

void Demo_Tick(void) {
	if (Basic_Data->frame == 60) {
		Basic_Data->frame = 0;
		setPixel(Basic_Data->x, Basic_Data->y, PIXEL_BLACK);
		Basic_Data->x++;
		if (Basic_Data->x == WIDTH) {
			Basic_Data->y++;
			Basic_Data->x = 2;
		}
		if (Basic_Data->y == HEIGHT) {
			Basic_Data->y = 0;
		}
		setPixel(Basic_Data->x, Basic_Data->y, PIXEL_CYAN);
	}
	Basic_Data->frame++;
}

void Demo_Deinit(void) {
	Basic_Data->x = 0;
	Basic_Data->y = 0;
	Basic_Data->frame = 0;

	Basic_Data = 0;
}

void App_Init(void) {
	Basic_Data = &AppStorage;
	Basic_Data->x = 2;
	Basic_Data->y = 0;
	Basic_Data->frame = 0;
}

void App_Tick(void) {
	if (Basic_Data->frame == 4) {
		Basic_Data->frame = 0;
		if (Input_Status) {
			setPixel(Basic_Data->x, Basic_Data->y, PIXEL_BLACK);
			if (Input_Status & UP_INPUT) {
				Basic_Data->y--;
			}
			if (Input_Status & DOWN_INPUT) {
				Basic_Data->y++;
			}
			if (Input_Status & LEFT_INPUT) {
				Basic_Data->x--;
			}
			if (Input_Status & RIGHT_INPUT) {
				Basic_Data->x++;
			}
			if (Input_Status & A_INPUT) {
				
			}
			if (Input_Status & B_INPUT) {
				
			}

			if (Basic_Data->x < 0) {
				Basic_Data->x = WIDTH - 1;
			}

			if (Basic_Data->y < 0) {
				Basic_Data->y = HEIGHT - 1;
			}
			Basic_Data->x = Basic_Data->x % WIDTH;
			Basic_Data->y = Basic_Data->y % HEIGHT;
			setPixel(Basic_Data->x, Basic_Data->y, PIXEL_CYAN);
		}		
	}
	Basic_Data->frame++;
}

void App_Deinit(void) {
	int i;
	for (i = 0; i < sizeof(appBasic_Data); i++) {
		AppStorage[i] = 0;
	}

	Basic_Data = 0;
}

void App_Basic_New(App* app) {
	app->Demo_Init = &Demo_Init;
	app->Demo_Tick = &Demo_Tick;
	app->Demo_Deinit = &Demo_Deinit;
	app->App_Init = &App_Init;
	app->App_Tick = &App_Tick;
	app->App_Deinit = &App_Deinit;
}
>>>>>>> Stashed changes
