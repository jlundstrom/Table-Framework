#include "App_Tetris.h"
#include "Draw.h"
#include "Input.h"
#include "Random.h"

#define SPAWN_NEW_BLOCK    0x01
#define PLACE_BLOCK        0x02
#define BOARD_WIDTH        9
#define BOARD_HEIGHT       16
#define MAX_BLOCKSIZE      4 * 4

struct block
{
   char          x;
   char          y;
   unsigned char width;
   unsigned char height;
   Pixel         color;
   unsigned char pixels[MAX_BLOCKSIZE];
}
typedef   Block;

struct appData
{
   unsigned char  top;
   unsigned char  left;
   unsigned short rotation;
   char           frame;
   unsigned char  state;
   Pixel          BG;
   Block          block;
   unsigned char  board[BOARD_WIDTH * BOARD_HEIGHT];
}
typedef   appData;
appData *Tetris_Data;


void App_Tetris_Init(void);
void App_Tetris_Deinit(void);
void Tetris_GenerateBlock(appData *);

void Demo_Tetris_Init(void)
{
   App_Tetris_Init();
}


void Demo_Tetris_Tick(void)
{
}


void Demo_Tetris_Deinit(void)
{
   App_Tetris_Deinit();
}


void App_Tetris_Init(void)
{
   Tetris_Data           = &AppStorage;
   Tetris_Data->top      = 0;
   Tetris_Data->left     = 7;
   Tetris_Data->rotation = 0;
   Tetris_Data->frame    = 0;
   Tetris_Data->BG       = PIXEL_WHITE;

   Tetris_GenerateBlock(Tetris_Data);

   drawRect(Tetris_Data->left, Tetris_Data->top, Tetris_Data->left + BOARD_WIDTH, Tetris_Data->top + BOARD_HEIGHT, Tetris_Data->BG);
}


void Tetris_GenerateBlock(appData *data)
{
   int block = getRandom() % 7, i;

   for (i = 0; i < MAX_BLOCKSIZE; i++)
   {
      Tetris_Data->block.pixels[i] = 0;
   }
   switch (block)
   {
   case 0:
      Tetris_Data->block.color     = PIXEL_CYAN;
      Tetris_Data->block.width     = 4;
      Tetris_Data->block.height    = 1;
      Tetris_Data->block.pixels[0] = 1;
      Tetris_Data->block.pixels[1] = 1;
      Tetris_Data->block.pixels[2] = 1;
      Tetris_Data->block.pixels[3] = 1;
      break;

   case 1:
      Tetris_Data->block.color     = PIXEL_BLUE;
      Tetris_Data->block.width     = 3;
      Tetris_Data->block.height    = 2;
      Tetris_Data->block.pixels[0] = 1;
      Tetris_Data->block.pixels[1] = 1;
      Tetris_Data->block.pixels[2] = 1;
      Tetris_Data->block.pixels[6] = 1;
      break;

   case 2:
      Tetris_Data->block.color     = PIXEL_ORANGE;
      Tetris_Data->block.width     = 3;
      Tetris_Data->block.height    = 2;
      Tetris_Data->block.pixels[0] = 1;
      Tetris_Data->block.pixels[1] = 1;
      Tetris_Data->block.pixels[2] = 1;
      Tetris_Data->block.pixels[4] = 1;
      break;

   case 3:
      Tetris_Data->block.color     = PIXEL_YELLOW;
      Tetris_Data->block.width     = 2;
      Tetris_Data->block.height    = 2;
      Tetris_Data->block.pixels[0] = 1;
      Tetris_Data->block.pixels[1] = 1;
      Tetris_Data->block.pixels[4] = 1;
      Tetris_Data->block.pixels[5] = 1;
      break;

   case 4:
      Tetris_Data->block.color     = PIXEL_GREEN;
      Tetris_Data->block.width     = 3;
      Tetris_Data->block.height    = 2;
      Tetris_Data->block.pixels[1] = 1;
      Tetris_Data->block.pixels[2] = 1;
      Tetris_Data->block.pixels[4] = 1;
      Tetris_Data->block.pixels[5] = 1;
      break;

   case 5:
      Tetris_Data->block.color     = PIXEL_PURPLE;
      Tetris_Data->block.width     = 3;
      Tetris_Data->block.height    = 2;
      Tetris_Data->block.pixels[0] = 1;
      Tetris_Data->block.pixels[1] = 1;
      Tetris_Data->block.pixels[2] = 1;
      Tetris_Data->block.pixels[5] = 1;
      break;

   case 6:
      Tetris_Data->block.color     = PIXEL_RED;
      Tetris_Data->block.width     = 3;
      Tetris_Data->block.height    = 2;
      Tetris_Data->block.pixels[0] = 1;
      Tetris_Data->block.pixels[1] = 1;
      Tetris_Data->block.pixels[5] = 1;
      Tetris_Data->block.pixels[6] = 1;
      break;
   }

   Tetris_Data->block.y = 0;
   Tetris_Data->block.x = (BOARD_WIDTH / 2) - (Tetris_Data->block.width / 2);
}


int Tetris_GetPixelX(appData *data, char x)
{
   return data->left + x;
}


int Tetris_GetPixelY(appData *data, char y)
{
   return data->top + y;
}


unsigned char Tetris_GetCell(appData *data, char x, char y)
{
   return data->board[x + (y * BOARD_WIDTH)];
}


unsigned char Tetris_SetCell(appData *data, char x, char y, unsigned char val)
{
   return data->board[x + (y * BOARD_WIDTH)] = val;
}


unsigned char Tetris_RotateLeft(appData *data)
{
   int           x, y;
   unsigned char tmp[MAX_BLOCKSIZE];

   for (x = 0; x < data->block.width; x++)
   {
      for (y = 0; y < data->block.height; y++)
      {
         tmp[data->block.height - y - 1 + (x * 4)] = data->block.pixels[x + (y * 4)];
      }
   }
   for (x = 0; x < MAX_BLOCKSIZE; x++)
   {
      data->block.pixels[x] = tmp[x];
   }
   x = data->block.width;
   data->block.width  = data->block.height;
   data->block.height = x;
}


unsigned char Tetris_RotateRight(appData *data)
{
   int           x, y;
   unsigned char tmp[MAX_BLOCKSIZE];

   for (x = 0; x < data->block.width; x++)
   {
      for (y = 0; y < data->block.height; y++)
      {
         tmp[y + ((data->block.width - x - 1) * 4)] = data->block.pixels[x + (y * 4)];
      }
   }
   for (x = 0; x < MAX_BLOCKSIZE; x++)
   {
      data->block.pixels[x] = tmp[x];
   }
   x = data->block.width;
   data->block.width  = data->block.height;
   data->block.height = x;
}


int Tetris_CheckMove(appData *data, char xOffset, char yOffset)
{
   int x, y;

   // Left right and bottom bound checks
   if ((data->block.x + xOffset) < 0)
   {
      return 0;
   }
   if ((data->block.x + data->block.width + xOffset) > BOARD_WIDTH)
   {
      return 0;
   }
   if ((data->block.y + data->block.height + yOffset) > BOARD_HEIGHT)
   {
      return 0;
   }

   data->block.x += xOffset;
   data->block.y += yOffset;
   for (x = 0; x < data->block.width; x++)
   {
      for (y = 0; y < data->block.height; y++)
      {
         if (data->block.pixels[x + (y * 4)] && Tetris_GetCell(data, data->block.x + x, data->block.y + y))
         {
            data->block.x -= xOffset;
            data->block.y -= yOffset;
            return 0;
         }
      }
   }

   return 1;
}


void Tetris_RemoveRow(appData *data, char row)
{
   int x, y;

   for (y = row; y > 0; y--)
   {
      for (x = 0; x < BOARD_WIDTH; x++)
      {
         Tetris_SetCell(data, x, y, Tetris_GetCell(data, x, y - 1));
         setPixel(Tetris_GetPixelX(data, x), Tetris_GetPixelY(data, y),
                  getPixel(Tetris_GetPixelX(data, x), Tetris_GetPixelY(data, y - 1)));
      }
   }

   for (x = 0; x < BOARD_WIDTH; x++)
   {
      Tetris_SetCell(data, x, 0, 0);
      setPixel(Tetris_GetPixelX(data, x), Tetris_GetPixelY(data, 0), data->BG);
   }
}


void Tetris_Drop(appData *data, int drop)
{
   int x, y;

   for (x = 0; x < data->block.width; x++)
   {
      for (y = 0; y < data->block.height; y++)
      {
         if (data->block.pixels[x + (y * 4)])
         {
            setPixel(Tetris_GetPixelX(data, data->block.x + x), Tetris_GetPixelY(data, data->block.y + y), Tetris_Data->BG);
         }
      }
   }

   if ((Input_Tap & RIGHT_INPUT))
   {
      Tetris_CheckMove(data, 1, 0);
   }
   else if ((Input_Tap & LEFT_INPUT))
   {
      Tetris_CheckMove(data, -1, 0);
   }
   if (Input_Tap & A_INPUT)
   {
      Tetris_RotateRight(data);
      if (!Tetris_CheckMove(data, 0, 0))
      {
         Tetris_RotateLeft(data);
      }
   }
   else if (Input_Tap & B_INPUT)
   {
      Tetris_RotateLeft(data);
      if (!Tetris_CheckMove(data, 0, 0))
      {
         Tetris_RotateRight(data);
      }
   }

   if ((drop > 0) && !Tetris_CheckMove(data, 0, drop))
   {
      data->state |= SPAWN_NEW_BLOCK | PLACE_BLOCK;
   }

   Input_Tap &= ~(RIGHT_INPUT | LEFT_INPUT | A_INPUT | B_INPUT);

   for (x = 0; x < data->block.width; x++)
   {
      for (y = 0; y < data->block.height; y++)
      {
         if (data->block.pixels[x + (y * 4)])
         {
            setPixel(Tetris_GetPixelX(data, data->block.x + x), Tetris_GetPixelY(data, data->block.y + y), data->block.color);
            if (data->state & PLACE_BLOCK)
            {
               Tetris_SetCell(data, data->block.x + x, data->block.y + y, 1);
            }
         }
      }
   }

   if (data->state & PLACE_BLOCK)
   {
      for (y = data->block.height - 1; y >= 0; y--)
      {
         for (x = 0; x < BOARD_WIDTH; x++)
         {
            if (!Tetris_GetCell(data, x, data->block.y + y))
            {
               break;
            }
            if (x == BOARD_WIDTH - 1)
            {
               Tetris_RemoveRow(data, y + data->block.y);
               data->block.y++;
            }
         }
      }
      data->state &= ~PLACE_BLOCK;
   }
   if (data->state & SPAWN_NEW_BLOCK)
   {
      Tetris_GenerateBlock(data);
      data->state &= ~SPAWN_NEW_BLOCK;
   }
}


void App_Tetris_Tick(void)
{
   int frameAt = 15;

   if (Input_Status & DOWN_INPUT)
   {
      frameAt = 3;
   }

   if (Tetris_Data->frame >= frameAt)
   {
      Tetris_Drop(Tetris_Data, 1);
      Tetris_Data->frame = 0;
   }
   else if (Tetris_Data->frame % 3)
   {
      Tetris_Drop(Tetris_Data, 0);
   }

   Tetris_Data->frame += 1;
}


void App_Tetris_Deinit(void)
{
   int i;

   for (i = 0; i < sizeof(appData); i++)
   {
      AppStorage[i] = 0;
   }

   Tetris_Data = 0;
}


void App_Tetris_New(App *app)
{
   app->Demo_Init   = &Demo_Tetris_Init;
   app->Demo_Tick   = &Demo_Tetris_Tick;
   app->Demo_Deinit = &Demo_Tetris_Deinit;
   app->App_Init    = &App_Tetris_Init;
   app->App_Tick    = &App_Tetris_Tick;
   app->App_Deinit  = &App_Tetris_Deinit;
}
