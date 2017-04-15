#include "App_Boot.h"
#include "Draw.h"
#include "Noise.h"
#include "Input.h"

struct appBoot_Data {
    int frame;
} typedef appBoot_Data;
appBoot_Data* Boot_Data;

char    nihao[32][16] = { { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0 }, { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0 }, { 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 }, { 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 }, { 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0 }, { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }, { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, { 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

void Demo_Boot_Init(void) {
    Boot_Data = &AppStorage;
    Boot_Data->frame = 0;
}

void Demo_Boot_Tick(void) {
    Pixel pixel;
    char string[]={'H','I','Y','A','S'};
    pixel.R=255;
    pixel.G=0;
    pixel.B=0;
    toString(string,1,pixel);
}

void Demo_Boot_Deinit(void) {
    Boot_Data->frame = 0;
    Boot_Data = 0;
}

void App_Boot_Init(void) {
    Boot_Data = &AppStorage;
    Boot_Data->frame = 0;
}

void App_Boot_Tick(void) {
    generateNoise();
    drawCloud(3);
    int i,j;
    Pixel pixel;
    pixel.R=255;
    pixel.G=0;
    pixel.B=0;
    for(i=0;i<32;i++)
    {
        for(j=0;j<16;j++)
        {
            if(nihao[i][j]==1)
            {
                setPixel(i,j,pixel);
            }
        }
    }
    Boot_Data->frame++;
}

void App_Boot_Deinit(void) {
    int i;
    for (i = 0; i < sizeof(appBoot_Data); i++) {
        AppStorage[i] = 0;
    }

    Boot_Data = 0;
}

void App_Boot_New(App* app) {
    app->Demo_Init = &Demo_Boot_Init;
    app->Demo_Tick = &Demo_Boot_Tick;
    app->Demo_Deinit = &Demo_Boot_Deinit;
    app->App_Init = &App_Boot_Init;
    app->App_Tick = &App_Boot_Tick;
    app->App_Deinit = &App_Boot_Deinit;
}
