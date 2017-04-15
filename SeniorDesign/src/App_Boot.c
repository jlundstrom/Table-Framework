#include "App_Boot.h"
#include "Draw.h"
#include "Noise.h"
#include "Input.h"

struct appData {
    int frame;
    unsigned char flag;
    unsigned char fadeoutFlag;
} typedef appData;
appData* appBoot_Data;
void Demo_Boot_Init(void);
void Demo_Boot_Tick(void);
void Demo_Boot_Deinit(void);
void App_Boot_Init(void);
void App_Boot_Tick(void);
void App_Boot_Deinit(void);
void App_Boot_New(App* app);

char    nihao[32][16] = { { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0 }, { 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 }, { 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 }, { 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0 }, { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
Pixel pixelText;

void Demo_Boot_Init(void) {
    appBoot_Data = &AppStorage;
    appBoot_Data->frame = 0;
    appBoot_Data->flag = 0;
}

void Demo_Boot_Tick(void) {
    Pixel pixel;
    pixel.R=0;
    pixel.G=0;
    pixel.B=0;
    drawBackground(pixel);
    char string[5]={'B','O','O','T',' '};
    char string2[5]={'M','O','D','E',' '};
    pixel.R=255;
    pixel.G=0;
    pixel.B=0;
    toString(string,0,pixel);
    toString(string2,1,pixel);
}

void Demo_Boot_Deinit(void) {
    appBoot_Data->frame = 0;
    appBoot_Data = 0;
}

void App_Boot_Init(void) {
    appBoot_Data = &AppStorage;
    appBoot_Data->frame = 240;
    appBoot_Data->flag = 0;
    appBoot_Data->fadeoutFlag = 250;
    pixelText.R=255;
    pixelText.G=0;
    pixelText.B=0;
}

void App_Boot_Tick(void) {
    generateNoise();
    int i,j;
    if(appBoot_Data->fadeoutFlag>0)
    {
        drawCloud(3);
        for(i=0;i<32;i++)
            {
                for(j=0;j<16;j++)
                {
                    if(nihao[i][j]==1)
                    {
                        setPixel(i,j,pixelText);
                    }
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

void App_Boot_Deinit(void) {
    int i;
    for (i = 0; i < sizeof(appData); i++) {
        AppStorage[i] = 0;
    }

    appBoot_Data = 0;
}

void App_Boot_New(App* app) {
    app->Demo_Init = &Demo_Boot_Init;
    app->Demo_Tick = &Demo_Boot_Tick;
    app->Demo_Deinit = &Demo_Boot_Deinit;
    app->App_Init = &App_Boot_Init;
    app->App_Tick = &App_Boot_Tick;
    app->App_Deinit = &App_Boot_Deinit;
}
