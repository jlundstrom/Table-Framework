#include "App_Conway.h"
#include "Draw.h"
#include "Input.h"
#include "Random.h"

#define STATE_BUILDING 0x01
#define STATE_RUNNING 0x02

struct appData
{
   int           frame;
   unsigned char *active;
   unsigned char *temp;
   unsigned char cells1[WIDTH * HEIGHT];
   unsigned char cells2[WIDTH * HEIGHT];
   unsigned char generation;
   unsigned char state;
   int x;
   int y;
}
typedef   appData;
appData *Conway_Data;

void App_Conway_Deinit(void);
void setCell(unsigned char *table, int x, int y, unsigned char val);
unsigned char getCell(unsigned char *table, int x, int y);

Pixel WinColor;

void setCell(unsigned char *table, int x, int y, unsigned char val)
{
   if (x < 0)
   {
      x += WIDTH;
   }
   if (x >= WIDTH)
   {
      x -= WIDTH;
   }
   if (y < 0)
   {
      y += HEIGHT;
   }
   if (y >= HEIGHT)
   {
      y -= HEIGHT;
   }
   if ((x < 0) || (y < 0) || (x >= WIDTH) || (y >= HEIGHT))
   {
      return;
   }

   table[x + y * WIDTH] = val;
   if (val)
   {
      setPixel(x, y, WinColor);
   }
   else
   {
      setPixel(x, y, PIXEL_BLACK);
   }
}


unsigned char getCell(unsigned char *table, int x, int y)
{
   // Screen wraps for checks, so adjust accordingly
   if (x < 0)
   {
      x += WIDTH;
   }
   if (x >= WIDTH)
   {
      x -= WIDTH;
   }
   if (y < 0)
   {
      y += HEIGHT;
   }
   if (y >= HEIGHT)
   {
      y -= HEIGHT;
   }
   if ((x < 0) || (y < 0) || (x >= WIDTH) || (y >= HEIGHT))
   {
      return 0;
   }

   return table[x + y * WIDTH];
}


unsigned char getNeighbours(unsigned char *table, int x, int y)
{
   return getCell(table, x - 1, y) +
          getCell(table, x - 1, y - 1) +
          getCell(table, x, y - 1) +
          getCell(table, x + 1, y - 1) +
          getCell(table, x + 1, y) +
          getCell(table, x + 1, y + 1) +
          getCell(table, x, y + 1) +
          getCell(table, x - 1, y + 1);
}


void Demo_Conway_Init(void)
{
	int rand = getRandom() % 4, x, y;

	Conway_Data = AppStorage;
	App_Conway_Deinit();      // Clean Struct
	Conway_Data = AppStorage;
	Conway_Data->frame = 0;
	Conway_Data->generation = 0;
	Conway_Data->active = Conway_Data->cells1;
	Conway_Data->temp = Conway_Data->cells2;
	Conway_Data->state = STATE_RUNNING;
	WinColor = getRandomPixel();

	Pixel pixel;
	pixel.R = 0;
	pixel.G = 0;
	pixel.B = 0;
	drawBackground(pixel);
	//CONWY
	//LIFE
	char string[5] = { 'C', 'O', 'N', 'W', 'Y' };
	char string2[5] = { 'L', 'I', 'F', 'E', ' ' };
	pixel.R = 200;
	pixel.G = 200;
	pixel.B = 100;
	toString(string, 0, pixel);
	toString(string2, 1, pixel);
	for (x = 0; x < WIDTH; x++)
	{
		for (y = 0; y < HEIGHT; y++)
		{
			pixel = getPixel(x, y);
			if (pixel.R > 0 || pixel.G > 0 || pixel.B > 0)
			{
				setCell(Conway_Data->active, x, y, 1);
			}
			else
			{
				setCell(Conway_Data->active, x, y, 0);
			}
		}
	}
}


void Demo_Conway_Tick(void)
{
   if (Conway_Data->frame != 20)
   {
      Conway_Data->frame++;
      return;
   }
   WinColor           = getRandomPixel();
   Conway_Data->frame = 0;
   int           x, y, neighbors;
   unsigned char *temp;

   for (x = 1; x < WIDTH; x++)
   {
      for (y = 0; y < HEIGHT; y++)
      {
         neighbors = getNeighbours(Conway_Data->active, x, y);
         if (getCell(Conway_Data->active, x, y))
         {
            if (neighbors < 2)
            {
               setCell(Conway_Data->temp, x, y, 0);
            }
            else if (neighbors < 4)
            {
               setCell(Conway_Data->temp, x, y, 1);
            }
            else
            {
               setCell(Conway_Data->temp, x, y, 0);
            }
         }
         else if (neighbors == 3)
         {
            setCell(Conway_Data->temp, x, y, 1);
         }
         else
         {
            setCell(Conway_Data->temp, x, y, 0);
         }
      }
   }
   temp = Conway_Data->active;
   Conway_Data->active = Conway_Data->temp;
   Conway_Data->temp   = temp;
}


void Demo_Conway_Deinit(void)
{
   App_Conway_Deinit();
}


void App_Conway_Init(void)
{
	int rand = getRandom() % 4, x = getRandom() % WIDTH, y = getRandom() % HEIGHT;

	Conway_Data = AppStorage;
	App_Conway_Deinit();      // Clean Struct
	Conway_Data = AppStorage;
	Conway_Data->frame = 0;
	Conway_Data->generation = 0;
	Conway_Data->active = Conway_Data->cells1;
	Conway_Data->temp = Conway_Data->cells2;
	Conway_Data->state = STATE_BUILDING;
	WinColor = getRandomPixel();

	if (rand == 0)
	{
		setCell(Conway_Data->active, x, y, 1);
		setCell(Conway_Data->active, x + 2, y, 1);
		setCell(Conway_Data->active, x + 4, y, 1);
		setCell(Conway_Data->active, x, y + 1, 1);
		setCell(Conway_Data->active, x + 4, y + 1, 1);
		setCell(Conway_Data->active, x, y + 2, 1);
		setCell(Conway_Data->active, x + 4, y + 2, 1);
		setCell(Conway_Data->active, x, y + 3, 1);
		setCell(Conway_Data->active, x + 4, y + 3, 1);
		setCell(Conway_Data->active, x, y + 4, 1);
		setCell(Conway_Data->active, x + 2, y + 4, 1);
		setCell(Conway_Data->active, x + 4, y + 4, 1);
	}
	else if (rand == 1)
	{
		setCell(Conway_Data->active, x + 1, y, 1);
		setCell(Conway_Data->active, x, y + 1, 1);
		setCell(Conway_Data->active, x + 1, y + 1, 1);
		setCell(Conway_Data->active, x + 2, y + 1, 1);
		setCell(Conway_Data->active, x, y + 2, 1);
		setCell(Conway_Data->active, x + 2, y + 2, 1);
		setCell(Conway_Data->active, x + 1, y + 3, 1);
	}
	else if (rand == 2)
	{
		setCell(Conway_Data->active, x++, y, 1);
		setCell(Conway_Data->active, x++, y, 1);
		setCell(Conway_Data->active, x++, y, 1);
		setCell(Conway_Data->active, x++, y, 1);
		setCell(Conway_Data->active, x++, y, 1);
		setCell(Conway_Data->active, x++, y, 1);
		setCell(Conway_Data->active, x++, y, 1);
		setCell(Conway_Data->active, x++, y, 1);
		setCell(Conway_Data->active, x++, y, 1);
		setCell(Conway_Data->active, x++, y, 1);
	}
	else
	{
		setCell(Conway_Data->active, x + 1, y, 1);
		setCell(Conway_Data->active, x + 2, y + 1, 1);
		setCell(Conway_Data->active, x + 2, y + 2, 1);
		setCell(Conway_Data->active, x + 1, y + 2, 1);
		setCell(Conway_Data->active, x, y + 2, 1);
	}
}


void App_Conway_Tick(void)
{
   if (Conway_Data->frame != 4)
   {
      Conway_Data->frame++;
      return;
   }
   Conway_Data->frame = 0;
   int           x, y, neighbors;
   unsigned char *temp;

   if ((Input_Tap & B_INPUT))
   {
	   if (Conway_Data->state & STATE_BUILDING)
	   {
		   Conway_Data->state = STATE_RUNNING;
	   }
	   else
	   {
		   Conway_Data->state = STATE_BUILDING;
	   }

   }

   if (Conway_Data->state & STATE_BUILDING) {
	   if (getCell(Conway_Data->active, Conway_Data->x, Conway_Data->y))
	   {
		   setPixel(Conway_Data->x, Conway_Data->y, WinColor);
	   }
	   else {
		   setPixel(Conway_Data->x, Conway_Data->y, PIXEL_BLACK);
	   }
	   if (Input_Status & UP_INPUT)
	   {
		   Conway_Data->y--;
	   }
	   if (Input_Status & DOWN_INPUT)
	   {
		   Conway_Data->y++;
	   }
	   if (Input_Status & LEFT_INPUT)
	   {
		   Conway_Data->x--;
	   }
	   if (Input_Status & RIGHT_INPUT)
	   {
		   Conway_Data->x++;
	   }

	   if (Conway_Data->x < 0)
	   {
		   Conway_Data->x = WIDTH - 1;
	   }

	   if (Conway_Data->y < 0)
	   {
		   Conway_Data->y = HEIGHT - 1;
	   }
	   setPixel(Conway_Data->x, Conway_Data->y, PIXEL_WHITE);
	   if ((Input_Tap & A_INPUT))
	   {
		   if (getCell(Conway_Data->active, Conway_Data->x, Conway_Data->y))
		   {
			   setCell(Conway_Data->active, Conway_Data->x, Conway_Data->y, 0);
		   }
		   else {
			   setCell(Conway_Data->active, Conway_Data->x, Conway_Data->y, 1);
		   }
		   
	   }
   }else if (Conway_Data->state & STATE_RUNNING)
   {
	   WinColor = getRandomPixel();
		for (x = 0; x < WIDTH; x++)
		{
			for (y = 0; y < HEIGHT; y++)
			{
				neighbors = getNeighbours(Conway_Data->active, x, y);
				if (getCell(Conway_Data->active, x, y))
				{
				if (neighbors < 2)
				{
					setCell(Conway_Data->temp, x, y, 0);
				}
				else if (neighbors < 4)
				{
					setCell(Conway_Data->temp, x, y, 1);
				}
				else
				{
					setCell(Conway_Data->temp, x, y, 0);
				}
				}
				else if (neighbors == 3)
				{
				setCell(Conway_Data->temp, x, y, 1);
				}
				else
				{
				setCell(Conway_Data->temp, x, y, 0);
				}
			}
		}
		temp = Conway_Data->active;
		Conway_Data->active = Conway_Data->temp;
		Conway_Data->temp   = temp;
   }

   Input_Tap &= ~(UP_INPUT | DOWN_INPUT | LEFT_INPUT | RIGHT_INPUT | A_INPUT | B_INPUT);
}


void App_Conway_Deinit(void)
{
   int i;

   for (i = 0; i < sizeof(appData); i++)
   {
       _AppStorage[i] = 0;
   }

   Conway_Data = 0;
}


void App_Conway_New(App *app)
{
   app->Demo_Init   = &Demo_Conway_Init;
   app->Demo_Tick   = &Demo_Conway_Tick;
   app->Demo_Deinit = &Demo_Conway_Deinit;
   app->App_Init    = &App_Conway_Init;
   app->App_Tick    = &App_Conway_Tick;
   app->App_Deinit  = &App_Conway_Deinit;
}
