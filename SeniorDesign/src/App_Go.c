#include "App_Go.h"
#include "Draw.h"
#include "Input.h"
#include <string.h>

#define EMPTYCELL 0x0F
#define P1CELL 0x01
#define P2CELL 0x02
#define SELCELL 0x10

#define MAXBOARDSIDE 16
#define MAXBOARDSIZE MAXBOARDSIDE * MAXBOARDSIDE

typedef int Long_Hold(unsigned char, int);
struct playerData
{
	char x;
	char y;
	unsigned char selMask;
	int frame;
	unsigned char* tap;
	unsigned char* input;
	Long_Hold* long_Hold;
	Pixel color;
};

struct appData
{
	char x;
	char y;
	int frame;
	int size;
	struct playerData player1;
	struct playerData player2;
	struct playerData* currentPlayer;
	unsigned char board[MAXBOARDSIZE];
}
typedef appData;

appData *Go_Data;

void Demo_Go_Init(void);
void Demo_Go_Tick(void);
void Demo_Go_Deinit(void);
void App_Go_Init(void);
void App_Go_Tick(void);
void App_Go_Deinit(void);

void Draw_Board(void);

void Demo_Go_Init(void)
{
}


void Demo_Go_Tick(void)
{
	drawBackground(PIXEL_BLACK);
	char string[5] = { 'G', 'O', ' ', ' ', ' ' };
	toString(string, 0, PIXEL_LIGHT_GREEN);
}


void Demo_Go_Deinit(void)
{

}


void App_Go_Init(void)
{
	App_Go_Deinit();
	Go_Data = AppStorage;

	Go_Data->size = 13;
	Go_Data->x = (WIDTH / 2) - (Go_Data->size / 2) - (Go_Data->size % 2);
	Go_Data->y = (HEIGHT / 2) - (Go_Data->size / 2) - (Go_Data->size % 2);
	
	Go_Data->player1.color = PIXEL_RED;
	Go_Data->player1.tap = &Input_Tap;
	Go_Data->player1.input = &Input_Status;
	Go_Data->player1.long_Hold = &P1_Long_Hold;
	Go_Data->player1.selMask = P1CELL;
	Go_Data->player1.x = (Go_Data->size / 2);
	Go_Data->player1.y = (Go_Data->size / 2);
	Go_Data->player2.color = PIXEL_BLUE;
	Go_Data->player2.tap = &User2_Input_Tap;
	Go_Data->player2.input = &User2_Input_Status;
	Go_Data->player2.long_Hold = &P2_Long_Hold;
	Go_Data->player2.selMask = P2CELL;
	Go_Data->player2.x = (Go_Data->size / 2);
	Go_Data->player2.y = (Go_Data->size / 2);

	Go_Data->currentPlayer = &Go_Data->player1;
}

unsigned char Go_getCell(int x, int y)
{
	return Go_Data->board[x + (y*Go_Data->size)];
}

void Go_setCell(int x, int y, unsigned char val)
{
	Go_Data->board[x + (y*Go_Data->size)] = val;
}

Pixel Go_CellColor(int x, int y)
{
	unsigned char cellStatus = Go_getCell(x, y);
	if (cellStatus & SELCELL)
	{
		return PIXEL_PURPLE;
	}
	else if (cellStatus & P1CELL)
	{
		return Go_Data->player1.color;
	}
	else if (cellStatus & P2CELL)
	{
		return Go_Data->player2.color;
	}
	return PIXEL_BLACK;
}

void Draw_Board(void)
{
	int x, y;
	for (x = 0; x < Go_Data->size; x++)
	{
		for (y = 0; y < Go_Data->size; y++)
		{
			setPixel(Go_Data->x + x, Go_Data->y + y, Go_CellColor(x, y));
		}
	}
}

void Go_ProcessSelection(struct playerData* player)
{
	if (*player->tap & A_INPUT)
	{
		if (!(Go_getCell(player->x, player->y) & 0x0f))
		{
			Go_setCell(player->x, player->y, player->selMask);
			Go_Data->currentPlayer = ((player == &Go_Data->player1) ? &Go_Data->player2 : &Go_Data->player1);
		}
	}
}

void Go_ProcessMove(struct playerData* player)
{
	if (*player->tap & NORMAL_INPUT)
	{
		Go_setCell(player->x, player->y, Go_getCell(player->x, player->y) & ~SELCELL);
		if (*player->tap & UP_INPUT)
		{
			player->y--;
		}
		if (*player->tap & DOWN_INPUT)
		{
			player->y++;
		}
		if (*player->tap & LEFT_INPUT)
		{
			player->x--;
		}
		if (*player->tap & RIGHT_INPUT)
		{
			player->x++;
		}
		if (player->x < 0)
		{
			player->x = Go_Data->size - 1;
		}

		if (player->y < 0)
		{
			player->y = Go_Data->size - 1;
		}
		player->x = player->x % Go_Data->size;
		player->y = player->y % Go_Data->size;
		player->frame = 0;
		Go_setCell(player->x, player->y, Go_getCell(player->x, player->y) | SELCELL);
	}
	if (player->frame == 5)
	{
		if (*player->input)
		{
			Go_setCell(player->x, player->y, Go_getCell(player->x, player->y) & ~SELCELL);
			if (player->long_Hold(UP_INPUT, 8))
			{
				player->y--;
			}
			if (player->long_Hold(DOWN_INPUT, 8))
			{
				player->y++;
			}
			if (player->long_Hold(LEFT_INPUT, 8))
			{
				player->x--;
			}
			if (player->long_Hold(RIGHT_INPUT, 8))
			{
				player->x++;
			}
			if (player->x < 0)
			{
				player->x = Go_Data->size - 1;
			}

			if (player->y < 0)
			{
				player->y = Go_Data->size - 1;
			}
			player->x = player->x % Go_Data->size;
			player->y = player->y % Go_Data->size;
		}
		Go_setCell(player->x, player->y, Go_getCell(player->x, player->y) ^ SELCELL);
		player->frame = 0;
	}

	player->frame++;
}


void App_Go_Tick(void)
{
	int P1FrameAt = 15, P2FrameAt = 15;

	if (Input_Status & DOWN_INPUT)
	{
		P1FrameAt = 3;
	}

	drawEmptyRect(Go_Data->x - 2, Go_Data->y - 1, Go_Data->x + Go_Data->size + 1, Go_Data->y + Go_Data->size, Go_Data->currentPlayer->color);
	drawEmptyRect(Go_Data->x - 1, Go_Data->y - 1, Go_Data->x + Go_Data->size, Go_Data->y + Go_Data->size, PIXEL_BROWN);

	printTextOffset('1', 1, 5, Go_Data->player1.color);
	printTextOffset('2', 26, 5, Go_Data->player2.color);
	
	Go_ProcessMove(Go_Data->currentPlayer);
	Go_ProcessSelection(Go_Data->currentPlayer);
	Draw_Board();

	Input_Tap &= ~NORMAL_INPUT;
	User2_Input_Tap &= ~NORMAL_INPUT;
}


void App_Go_Deinit(void)
{
   int i;

   for (i = 0; i < sizeof(appData); i++)
   {
       _AppStorage[i] = 0;
   }

   Go_Data = 0;
}


void App_Go_New(App *app)
{
   app->Demo_Init   = &Demo_Go_Init;
   app->Demo_Tick   = &Demo_Go_Tick;
   app->Demo_Deinit = &Demo_Go_Deinit;
   app->App_Init    = &App_Go_Init;
   app->App_Tick    = &App_Go_Tick;
   app->App_Deinit  = &App_Go_Deinit;
}
