#include "input.h"
int P1_COUNT[8];
int P2_COUNT[8];

void Input_Draw_Tick(void)
{
	unsigned int mask = 0x01;
	int i;
	for (i = 0; i < 8; i++)
	{
		if (Input_Status & mask)
		{
			P1_COUNT[i] ++;
		}
		else
		{
			P1_COUNT[i] = 0;
		}
		mask = mask << 1;
	}

	mask = 0x01;
	for (i = 0; i < 8; i++)
	{
		if (User2_Input_Status & mask)
		{
			P2_COUNT[i] ++;
		}
		else
		{
			P2_COUNT[i] = 0;
		}
		mask = mask << 1;
	}
}

int P1_Long_Hold(unsigned char userMask, int minFrame)
{
	unsigned int mask = 0x01;
	int i;
	for (i = 0; i < 8; i++)
	{
		if (userMask == mask)
		{
			return P1_COUNT[i] >= minFrame;
		}
		mask = mask << 1;
	}

	return 0;
}

int P2_Long_Hold(unsigned char userMask, int minFrame)
{
	unsigned int mask = 0x01;
	int i;
	for (i = 0; i < 8; i++)
	{
		if (userMask == mask)
		{
			return P2_COUNT[i] >= minFrame;
		}
		mask = mask << 1;
	}

	return 0;
}
