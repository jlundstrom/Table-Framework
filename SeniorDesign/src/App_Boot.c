#include "App_Boot.h"
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
appData *appBoot_Data;
void Demo_Boot_Init(void);
void Demo_Boot_Tick(void);
void Demo_Boot_Deinit(void);
void App_Boot_Init(void);
void App_Boot_Tick(void);
void App_Boot_Deinit(void);
void App_Boot_New(App *app);

const uint16_t nihao[32] = { { 0b0000010000000010 }, { 0b0000100000001100 }, { 0b0001000000000000 }, { 0b0011111111101110 },
                          { 0b1100010000000001 }, { 0b0000100010000001 }, { 0b0001000100010001 }, { 0b1110011001001101 },
                          { 0b0010000000100001 }, { 0b0010111111000001 }, { 0b0010000000000001 }, { 0b0010010000000111 },
                          { 0b0010101000000000 }, { 0b0011000110001000 }, { 0b0000000000000110 }, { 0b0000000000000000 },
                          { 0b0000100000000010 }, { 0b0000100001000100 }, { 0b0000111110101000 }, { 0b1111100000010000 },
                          { 0b0000100001101000 }, { 0b0000111110000110 }, { 0b0000000000000000 }, { 0b0000000100000000 },
                          { 0b0100000100000010 }, { 0b0100000100000001 }, { 0b0100011111111110 }, { 0b0100100100000000 },
                          { 0b0101000100000000 }, { 0b0110000100000000 }, { 0b0000000100000000 }, { 0b0000000000000000 } };

Pixel pixelText;

void Demo_Boot_Init(void)
{
   appBoot_Data        = &AppStorage;
   appBoot_Data->frame = 0;
   appBoot_Data->flag  = 0;
}


void Demo_Boot_Tick(void)
{
   Pixel pixel;

   pixel.R = 0;
   pixel.G = 0;
   pixel.B = 0;
   drawBackground(pixel);
   char string[5]  = { 'B', 'O', 'O', 'T', ' ' };
   char string2[5] = { 'M', 'O', 'D', 'E', ' ' };
   pixel.R = 255;
   pixel.G = 0;
   pixel.B = 0;
   toString(string, 0, pixel);
   toString(string2, 1, pixel);
}


void Demo_Boot_Deinit(void)
{
   appBoot_Data->frame = 0;
   appBoot_Data        = 0;
}


void App_Boot_Init(void)
{
   appBoot_Data              = &AppStorage;
   appBoot_Data->frame       = 240;
   appBoot_Data->flag        = 0;
   appBoot_Data->frame2       = 0;
   appBoot_Data->fadeoutFlag = 250;
   pixelText.R = 255;
   pixelText.G = 0;
   pixelText.B = 0;
}


void App_Boot_Tick(void) {
    generateNoise();
    int i,j;
    uint16_t mask = 0x8000;
    if(appBoot_Data->fadeoutFlag>0)
    {
        if(appBoot_Data->frame2 % 2)
		{
			drawCloud(3);
		}
		appBoot_Data->frame2++;		
        for(i=31;i>=0;i--)
            {
            mask = 0x8000;
                for(j=0;j<16;j++)
                {
                    if(nihao[i] & mask)
                    {
                        setPixel(i,j,pixelText);
                    }
                    mask = mask >> 1;
                }
            }
        appBoot_Data->fadeoutFlag--;
        pixelText.R--;
    }
    else
    {
        if(appBoot_Data->frame>350)
            {
                appBoot_Data->flag=0;
            }
            if(appBoot_Data->frame<0)
            {
                appBoot_Data->flag=1;
            }
            if(appBoot_Data->flag==1)
            {
                appBoot_Data->frame++;
            }
      else
      {
         appBoot_Data->frame--;
      }
      drawCloudColor(appBoot_Data->frame);
   }
}


void App_Boot_Deinit(void)
{
   int i;

   for (i = 0; i < sizeof(appData); i++)
   {
      AppStorage[i] = 0;
   }

   appBoot_Data = 0;
}


void App_Boot_New(App *app)
{
   app->Demo_Init   = &Demo_Boot_Init;
   app->Demo_Tick   = &Demo_Boot_Tick;
   app->Demo_Deinit = &Demo_Boot_Deinit;
   app->App_Init    = &App_Boot_Init;
   app->App_Tick    = &App_Boot_Tick;
   app->App_Deinit  = &App_Boot_Deinit;
}
