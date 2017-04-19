#include "App_Tetris.h"
#include "Draw.h"
#include "Input.h"
#include "Random.h"

#define SPAWN_NEW_BLOCK    0x01
#define PLACE_BLOCK        0x02
#define GAME_OVER          0x03
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

struct playerData
{
   unsigned char  top;
   unsigned char  left;
   unsigned short rotation;
   char           frame;
   unsigned char  state;
   Pixel          BG;
   Block          block;
   Block          nextBlock;
   unsigned char  board[BOARD_WIDTH * BOARD_HEIGHT];
}
typedef   playerData;

struct appData
{
	playerData Player1;
	playerData Player2;
}
typedef   appData;
appData *Tetris_Data;


void App_Tetris_Init(void);
void App_Tetris_Deinit(void);
void Tetris_GenerateBlock(Block*);
void Tetris_GenerateBlocks(playerData *);
int Tetris_CheckMove(playerData*, char, char);

void Demo_Tetris_Init(void)
{
}


void Demo_Tetris_Tick(void)
{
	Pixel pixel;
	pixel.R = 0;
	pixel.G = 0;
	pixel.B = 0;
	drawBackground(pixel);
	char string[5] = { 'B', 'L', 'O', 'C', 'K' };
	char string2[5] = { 'D', 'R', 'O', 'P', ' ' };
	pixel.R = 200;
	pixel.G = 200;
	pixel.B = 100;
	toString(string, 0, pixel);
	toString(string2, 1, pixel);
}


void Demo_Tetris_Deinit(void)
{
}


void App_Tetris_Init(void)
{
   Tetris_Data           = AppStorage;
   Tetris_Data->Player1.top      = 0;
   Tetris_Data->Player1.left     = 1;
   Tetris_Data->Player1.rotation = 0;
   Tetris_Data->Player1.frame    = 0;
   Tetris_Data->Player1.state = 0;
   Tetris_Data->Player1.BG       = PIXEL_BLACK;
   Tetris_Data->Player2.top = 0;
   Tetris_Data->Player2.left = 17;
   Tetris_Data->Player2.rotation = 0;
   Tetris_Data->Player2.frame = 0;
   Tetris_Data->Player2.state = 0;
   Tetris_Data->Player2.BG = PIXEL_BLACK;

   Tetris_GenerateBlock(&Tetris_Data->Player1.nextBlock);
   Tetris_GenerateBlock(&Tetris_Data->Player2.nextBlock);

   Tetris_GenerateBlocks(&(Tetris_Data->Player1));
   Tetris_GenerateBlocks(&(Tetris_Data->Player2));
   
   drawRect(Tetris_Data->Player1.left - 1, Tetris_Data->Player1.top - 1, Tetris_Data->Player1.left + BOARD_WIDTH + 1, Tetris_Data->Player1.top + BOARD_HEIGHT + 1, PIXEL_WHITE);
   drawRect(Tetris_Data->Player2.left - 1, Tetris_Data->Player2.top - 1, Tetris_Data->Player2.left + BOARD_WIDTH + 1, Tetris_Data->Player2.top + BOARD_HEIGHT + 1, PIXEL_RED);
   drawRect(Tetris_Data->Player1.left, Tetris_Data->Player1.top, Tetris_Data->Player1.left + BOARD_WIDTH, Tetris_Data->Player1.top + BOARD_HEIGHT, Tetris_Data->Player1.BG);
   drawRect(Tetris_Data->Player2.left, Tetris_Data->Player2.top, Tetris_Data->Player2.left + BOARD_WIDTH, Tetris_Data->Player2.top + BOARD_HEIGHT, Tetris_Data->Player2.BG);
}

void Tetris_GenerateBlock(Block* blk)
{
	int block = getRandom() % 7, i;

	for (i = 0; i < MAX_BLOCKSIZE; i++)
	{
		blk->pixels[i] = 0;
	}
	switch (block)
	{
	case 0:
		blk->color = PIXEL_CYAN;
		blk->width = 4;
		blk->height = 1;
		blk->pixels[0] = 1;
		blk->pixels[1] = 1;
		blk->pixels[2] = 1;
		blk->pixels[3] = 1;
		break;

	case 1:
		blk->color = PIXEL_BLUE;
		blk->width = 3;
		blk->height = 2;
		blk->pixels[0] = 1;
		blk->pixels[1] = 1;
		blk->pixels[2] = 1;
		blk->pixels[6] = 1;
		break;

	case 2:
		blk->color = PIXEL_ORANGE;
		blk->width = 3;
		blk->height = 2;
		blk->pixels[0] = 1;
		blk->pixels[1] = 1;
		blk->pixels[2] = 1;
		blk->pixels[4] = 1;
		break;

	case 3:
		blk->color = PIXEL_YELLOW;
		blk->width = 2;
		blk->height = 2;
		blk->pixels[0] = 1;
		blk->pixels[1] = 1;
		blk->pixels[4] = 1;
		blk->pixels[5] = 1;
		break;

	case 4:
		blk->color = PIXEL_GREEN;
		blk->width = 3;
		blk->height = 2;
		blk->pixels[1] = 1;
		blk->pixels[2] = 1;
		blk->pixels[4] = 1;
		blk->pixels[5] = 1;
		break;

	case 5:
		blk->color = PIXEL_PURPLE;
		blk->width = 3;
		blk->height = 2;
		blk->pixels[0] = 1;
		blk->pixels[1] = 1;
		blk->pixels[2] = 1;
		blk->pixels[5] = 1;
		break;

	case 6:
		blk->color = PIXEL_RED;
		blk->width = 3;
		blk->height = 2;
		blk->pixels[0] = 1;
		blk->pixels[1] = 1;
		blk->pixels[5] = 1;
		blk->pixels[6] = 1;
		break;
	}

	blk->y = 0;
	blk->x = (BOARD_WIDTH / 2) - (blk->width / 2);
}

void Tetris_GenerateBlocks(playerData *data)
{
	int x, y;
	
	data->block = data->nextBlock;
	Tetris_GenerateBlock(&data->nextBlock);

	drawRect(Tetris_GetPixelX(data, BOARD_WIDTH + 1), Tetris_GetPixelY(data, 1), Tetris_GetPixelX(data, BOARD_WIDTH + 6), Tetris_GetPixelY(data, 5), PIXEL_BLACK);
	for (x = 0; x < data->nextBlock.width; x++)
	{
		for (y = 0; y < data->nextBlock.height; y++)
		{
			if (data->nextBlock.pixels[x + (y * 4)])
			{
				setPixel(Tetris_GetPixelX(data, BOARD_WIDTH + 2 + x), Tetris_GetPixelY(data, 1 + y), data->nextBlock.color);
			}
		}
	}

   if (!Tetris_CheckMove(data, 0, 0))
   {
	   data->state |= GAME_OVER;
   }
}


int Tetris_GetPixelX(playerData *data, char x)
{
   return data->left + x;
}


int Tetris_GetPixelY(playerData *data, char y)
{
   return data->top + y;
}


unsigned char Tetris_GetCell(playerData *data, char x, char y)
{
   return data->board[x + (y * BOARD_WIDTH)];
}


unsigned char Tetris_SetCell(playerData *data, char x, char y, unsigned char val)
{
   return data->board[x + (y * BOARD_WIDTH)] = val;
}


void Tetris_RotateLeft(playerData *data)
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


void Tetris_RotateRight(playerData *data)
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


int Tetris_CheckMove(playerData *data, char xOffset, char yOffset)
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


void Tetris_RemoveRow(playerData *data, char row)
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


void App_Tetris_GameOver_Tick(playerData *data, unsigned char input)
{
	int x, y;
	Pixel p;
	for (y = 0; y < BOARD_HEIGHT; y++)
	{
		for (x = 0; x < BOARD_WIDTH; x++)
		{
			p = getPixel(Tetris_GetPixelX(data, x), Tetris_GetPixelY(data, y));
			if (!(comparePixel(p, PIXEL_BLACK) || comparePixel(p, PIXEL_RED)))
			{
				setPixel(Tetris_GetPixelX(data, x), Tetris_GetPixelY(data, y), PIXEL_RED);
				return;
			}
		}
	}
	for (y = BOARD_HEIGHT - 1; y >= 0; y--)
	{
		for (x = 0; x < BOARD_WIDTH; x++)
		{
			p = getPixel(Tetris_GetPixelX(data, x), Tetris_GetPixelY(data, y));
			setPixel(Tetris_GetPixelX(data, x), Tetris_GetPixelY(data, y), PIXEL_BLACK);
			if (!comparePixel(p, PIXEL_BLACK) && y + 1 < BOARD_HEIGHT)
			{
				setPixel(Tetris_GetPixelX(data, x), Tetris_GetPixelY(data, y + 1), p);
				return;
			}
		}
	}

	if (input & A_INPUT)
	{
		data->frame = 0;
		data->state = 0;
		data->BG = PIXEL_BLACK;
		for (x = 0; x < BOARD_WIDTH * BOARD_HEIGHT; x++)
		{
			data->board[x] = 0;
		}

		Tetris_GenerateBlock(&data->nextBlock);

		Tetris_GenerateBlocks(data);
	}
}


void Tetris_Drop(playerData *data, int drop, unsigned char input)
{
   int x, y;

   if (data->state & GAME_OVER)
   {
	   App_Tetris_GameOver_Tick(data, input);
	   return;
   }

   for (x = 0; x < data->block.width; x++)
   {
      for (y = 0; y < data->block.height; y++)
      {
         if (data->block.pixels[x + (y * 4)])
         {
            setPixel(Tetris_GetPixelX(data, data->block.x + x), Tetris_GetPixelY(data, data->block.y + y), data->BG);
         }
      }
   }

   if ((input & RIGHT_INPUT))
   {
      Tetris_CheckMove(data, 1, 0);
   }
   else if ((input & LEFT_INPUT))
   {
      Tetris_CheckMove(data, -1, 0);
   }
   if (input & A_INPUT)
   {
      Tetris_RotateRight(data);
      if (!Tetris_CheckMove(data, 0, 0))
      {
         Tetris_RotateLeft(data);
      }
   }
   else if (input & B_INPUT)
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
      Tetris_GenerateBlocks(data);
      data->state &= ~SPAWN_NEW_BLOCK;
   }
}


void App_Tetris_Tick(void)
{
   int P1FrameAt = 15, P2FrameAt = 15;

   if (Input_Status & DOWN_INPUT)
   {
      P1FrameAt = 3;
   }

   if (Tetris_Data->Player1.frame >= P1FrameAt)
   {
      Tetris_Drop(&(Tetris_Data->Player1), 1, Input_Tap);
      Tetris_Data->Player1.frame = 0;
	  Input_Tap &= ~(RIGHT_INPUT | LEFT_INPUT | A_INPUT | B_INPUT);
   }
   else
   {
      Tetris_Drop(&(Tetris_Data->Player1), 0, Input_Tap);
	  Input_Tap &= ~(RIGHT_INPUT | LEFT_INPUT | A_INPUT | B_INPUT);
   }

   Tetris_Data->Player1.frame += 1;

   if (User2_Input_Status & DOWN_INPUT)
   {
	   P2FrameAt = 3;
   }

   if (Tetris_Data->Player2.frame >= P2FrameAt)
   {
	   Tetris_Drop(&(Tetris_Data->Player2), 1, User2_Input_Tap);
	   Tetris_Data->Player2.frame = 0;
	   User2_Input_Tap &= ~(RIGHT_INPUT | LEFT_INPUT | A_INPUT | B_INPUT);
   }
   else
   {
	   Tetris_Drop(&(Tetris_Data->Player2), 0, User2_Input_Tap);
	   User2_Input_Tap &= ~(RIGHT_INPUT | LEFT_INPUT | A_INPUT | B_INPUT);
   }

   Tetris_Data->Player2.frame += 1;
}


void App_Tetris_Deinit(void)
{
   int i;

   for (i = 0; i < sizeof(appData); i++)
   {
       _AppStorage[i] = 0;
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
