#include "App_Tron.h"
#include "Draw.h"
#include "Noise.h"
#include "Input.h"

struct appData {
    int frame;
    int winner;
    unsigned char flag;
    unsigned char mode;
    Point point1;
    Point point2;
    Pixel P1;
    Pixel P2;
    Pixel background;

} typedef appData;
appData* appTron_Data;
void Demo_Tron_Init(void);
void Demo_Tron_Tick(void);
void Demo_Tron_Deinit(void);
void App_Tron_Init(void);
void App_Tron_Tick(void);
void App_Tron_Deinit(void);
void App_Tron_New(App* app);
void drawWinner(int winner);


void Demo_Tron_Init(void) {
    appTron_Data = &AppStorage;
    appTron_Data->frame = 0;
    appTron_Data->flag = 0;
}

void Demo_Tron_Tick(void) {
    Pixel pixel;
    generateNoise();
    pixel.R=0;
    pixel.G=0;
    pixel.B=0;
    drawBackground(pixel);
    pixel.R=100;
    pixel.G=255;
    pixel.B=255;
    drawLine(appTron_Data->frame*2,0,appTron_Data->frame*2,15,pixel);
    drawLine(0,appTron_Data->frame,31,appTron_Data->frame,pixel);
    char string[5]={'T','R','O','N',' '};
    char string2[5]={'2',' ','P','Y',' '};
    pixel.R=0;
    pixel.G=0;
    pixel.B=255;
    toString(string,0,pixel);
    toString(string2,1,pixel);
    appTron_Data->frame++;
    if(appTron_Data->frame>16)
    {
        appTron_Data->frame=0;
    }
}

void Demo_Tron_Deinit(void) {
    appTron_Data->frame = 0;
    appTron_Data = 0;
}

void App_Tron_Init(void) {
    appTron_Data = &AppStorage;
    Pixel pixel;
    pixel.R=0;
    pixel.G=0;
    pixel.B=0;
    appTron_Data->background = pixel;
    drawBackground(pixel);
    appTron_Data->frame = 0;
    appTron_Data->winner = 0;
    appTron_Data->flag = 0;
    appTron_Data->mode = 0;
    appTron_Data->point1.x = 1;
    appTron_Data->point2.x = 30;
    appTron_Data->point1.y = 1;
    appTron_Data->point2.y = 14;
    pixel.R=0;
    pixel.G=255;
    pixel.B=255;
    appTron_Data->P1=pixel;
    pixel.R=255;
    pixel.G=0;
    pixel.B=0;
    appTron_Data->P2=pixel;
}

void App_Tron_Tick(void) {
    if(appTron_Data->mode==0)
    {

    }
    if(appTron_Data->mode==1)
    {
        drawWinner(appTron_Data->winner);
    }
}

void drawWinner(int winner)
{
    if(winner==1)
    {
        fadeOutExclude(5,appTron_Data->P1);
    }
    if(winner==2)
    {
        fadeOutExclude(5,appTron_Data->P2);
    }
}


void App_Tron_Deinit(void) {
    int i;
    for (i = 0; i < sizeof(appData); i++) {
        AppStorage[i] = 0;
    }

    appTron_Data = 0;
}

void App_Tron_New(App* app) {
    app->Demo_Init = &Demo_Tron_Init;
    app->Demo_Tick = &Demo_Tron_Tick;
    app->Demo_Deinit = &Demo_Tron_Deinit;
    app->App_Init = &App_Tron_Init;
    app->App_Tick = &App_Tron_Tick;
    app->App_Deinit = &App_Tron_Deinit;
}
