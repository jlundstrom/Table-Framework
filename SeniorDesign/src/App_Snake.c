#include "App_Snake.h"
#include "Draw.h"
#include "Input.h"
#include "Random.h"

#define DIRECTION          0xF
#define DIRECTION_UP       0x01
#define DIRECTION_LEFT     0x02
#define DIRECTION_DOWN     0x04
#define DIRECTION_RIGHT    0x08
#define SEGMENT_ACTIVE     0x10
#define GAME_OVER          0x80

struct appData
{
   int           headX;
   int           headY;
   int           foodX;
   int           foodY;
   int           tailX;
   int           tailY;
   int           headIdx;
   int           length;
   char          frame;
   unsigned char Direction;
   unsigned char snake[WIDTH * HEIGHT];
}
typedef   appData;
appData *Snake_Data;

void App_Snake_Init(void);
void App_Snake_Deinit(void);
void App_Snake_Place_Food(void);

void Demo_Snake_Init(void)
{
}


void Demo_Snake_Tick(void)
{
	Pixel pixel;
	pixel.R = 0;
	pixel.G = 0;
	pixel.B = 0;
	drawBackground(pixel);
	char string[5] = { 'S', 'N', 'A', 'K', 'E' };
	pixel.R = 200;
	pixel.G = 200;
	pixel.B = 100;
	toString(string, 0, pixel);
}


void Demo_Snake_Deinit(void)
{
}


void App_Snake_Init(void)
{
   Snake_Data          = AppStorage;
   Snake_Data->headX   = getRandomLow() % WIDTH;
   Snake_Data->headY   = getRandomLow() % HEIGHT;
   Snake_Data->headIdx = 0;
   Snake_Data->tailX   = Snake_Data->headX;
   Snake_Data->tailY   = Snake_Data->headY;
   Snake_Data->length  = 1;
   Snake_Data->frame   = 0;

   Snake_Data->snake[0]  = 0;
   Snake_Data->Direction = Snake_Data->snake[0];
   setPixel(Snake_Data->headX, Snake_Data->headY, PIXEL_CYAN);
   App_Snake_Place_Food();

   Input_Tap &= ~(UP_INPUT | DOWN_INPUT | LEFT_INPUT | RIGHT_INPUT | A_INPUT);
}


void App_Snake_Remove_Tail()
{
   unsigned char x, y;
   int           idx;

   x   = Snake_Data->tailX;
   y   = Snake_Data->tailY;
   idx = Snake_Data->headIdx - Snake_Data->length + 1;

   if (idx < 0)
   {
      idx += WIDTH * HEIGHT;
   }

   setPixel(x, y, PIXEL_BLACK);

   switch (Snake_Data->snake[idx] & ~SEGMENT_ACTIVE)
   {
   case DIRECTION_UP:
      y--;
      break;

   case DIRECTION_DOWN:
      y++;
      break;

   case DIRECTION_LEFT:
      x--;
      break;

   case DIRECTION_RIGHT:
      x++;
      break;

   default:
      break;
   }
   Snake_Data->tailX      = x;
   Snake_Data->tailY      = y;
   Snake_Data->snake[idx] = 0;
}


void App_Snake_Place_Food()
{
   Pixel tmp;

   while (1)
   {
      Snake_Data->foodX = getRandomLow() % WIDTH;
      Snake_Data->foodY = getRandomLow() % HEIGHT;
      tmp = getPixel(Snake_Data->foodX, Snake_Data->foodY);
      if (comparePixel(tmp, PIXEL_BLACK))
      {
         break;
      }
   }
   setPixel(Snake_Data->foodX, Snake_Data->foodY, PIXEL_GREEN);
}


void App_Snake_Game_Over_Tick()
{
   if (Snake_Data->frame % 4 == 3)
   {
      setPixel(getRandomLow() % WIDTH, getRandomLow() % HEIGHT, PIXEL_RED);
      if (Input_Tap)
      {
         clearDisplay();
         App_Snake_Deinit();
         App_Snake_Init();
      }
   }
}


void App_Snake_Tick(void)
{
   Pixel         tmp;
   unsigned char dirTemp;

   if (Snake_Data->Direction & GAME_OVER)
   {
      App_Snake_Game_Over_Tick();
   }
   else if (Snake_Data->frame == 5)
   {
      Snake_Data->frame = 0;

      if (Input_Tap)
      {
         if (Input_Tap & UP_INPUT && (Snake_Data->Direction != DIRECTION_DOWN))
         {
            Snake_Data->Direction &= !DIRECTION;
            Snake_Data->Direction |= DIRECTION_UP;
         }
         else if (Input_Tap & DOWN_INPUT && (Snake_Data->Direction != DIRECTION_UP))
         {
            Snake_Data->Direction &= !DIRECTION;
            Snake_Data->Direction |= DIRECTION_DOWN;
         }
         else if (Input_Tap & LEFT_INPUT && (Snake_Data->Direction != DIRECTION_RIGHT))
         {
            Snake_Data->Direction &= !DIRECTION;
            Snake_Data->Direction |= DIRECTION_LEFT;
         }
         else if (Input_Tap & RIGHT_INPUT && (Snake_Data->Direction != DIRECTION_LEFT))
         {
            Snake_Data->Direction &= !DIRECTION;
            Snake_Data->Direction |= DIRECTION_RIGHT;
         }

         if (Input_Tap & A_INPUT)
         {
            dirTemp = Snake_Data->Direction & DIRECTION;
            Snake_Data->Direction &= ~DIRECTION;
            dirTemp = dirTemp << 1;
            if (!(dirTemp & DIRECTION))
            {
               dirTemp = DIRECTION_UP;
            }
            Snake_Data->Direction |= dirTemp;
         }
         if (Input_Tap & B_INPUT)
         {
            dirTemp = Snake_Data->Direction & DIRECTION;
            Snake_Data->Direction &= ~DIRECTION;
            dirTemp = dirTemp >> 1;
            if (!dirTemp)
            {
               dirTemp = DIRECTION_RIGHT;
            }
            Snake_Data->Direction |= dirTemp;
         }

         Input_Tap &= ~(UP_INPUT | DOWN_INPUT | LEFT_INPUT | RIGHT_INPUT | A_INPUT | B_INPUT);
         Snake_Data->snake[Snake_Data->headIdx] = Snake_Data->Direction & DIRECTION;
      }

      if ((Snake_Data->Direction & DIRECTION) == 0x00)
      {
         return;
      }

      if ((Snake_Data->Direction & SEGMENT_ACTIVE) || (Snake_Data->length < 3))
      {
         Snake_Data->Direction ^= SEGMENT_ACTIVE;
         Snake_Data->length++;
      }
      else
      {
         App_Snake_Remove_Tail();
      }

      /*if (Snake_Data->headX < 0 || Snake_Data->headX > WIDTH) {
       *      Snake_Data->Direction |= SEGMENT_ACTIVE;
       *      return;
       * }
       *
       * if (Snake_Data->headY < 0 || Snake_Data->headY > HEIGHT) {
       *      Snake_Data->Direction |= SEGMENT_ACTIVE;
       *      return;
       * }*/

      switch (Snake_Data->Direction & ~SEGMENT_ACTIVE)
      {
      case DIRECTION_UP:
         Snake_Data->headY--;
         break;

      case DIRECTION_DOWN:
         Snake_Data->headY++;
         break;

      case DIRECTION_LEFT:
         Snake_Data->headX--;
         break;

      case DIRECTION_RIGHT:
         Snake_Data->headX++;
         break;

      default:
         break;
      }
      tmp = getPixel(Snake_Data->headX, Snake_Data->headY);
      if ((Snake_Data->foodX == Snake_Data->headX) && (Snake_Data->foodY == Snake_Data->headY))
      {
         Snake_Data->Direction |= SEGMENT_ACTIVE;
         App_Snake_Place_Food();
      }
      else if (tmp.R || tmp.G || tmp.B || (Snake_Data->headX < 0) ||
               (Snake_Data->headX >= WIDTH) || (Snake_Data->headY < 0) || (Snake_Data->headY >= HEIGHT))
      {
         Snake_Data->Direction = GAME_OVER;
      }
      setPixel(Snake_Data->headX, Snake_Data->headY, PIXEL_CYAN);
      Snake_Data->headIdx = (Snake_Data->headIdx + 1) % (WIDTH * HEIGHT);
      Snake_Data->snake[Snake_Data->headIdx] = Snake_Data->Direction & DIRECTION;
   }
   Snake_Data->frame++;
}


void App_Snake_Deinit(void)
{
   int i;

   for (i = 0; i < sizeof(appData); i++)
   {
       _AppStorage[i] = 0;
   }

   Snake_Data = 0;
}


void App_Snake_New(App *app)
{
   app->Demo_Init   = &Demo_Snake_Init;
   app->Demo_Tick   = &Demo_Snake_Tick;
   app->Demo_Deinit = &Demo_Snake_Deinit;
   app->App_Init    = &App_Snake_Init;
   app->App_Tick    = &App_Snake_Tick;
   app->App_Deinit  = &App_Snake_Deinit;
}
