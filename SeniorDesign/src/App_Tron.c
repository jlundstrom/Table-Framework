#include "App_Tron.h"
#include "Draw.h"
#include "Noise.h"
#include "Input.h"

struct appData {
    int frame;
    int winner;
    int P1UP;
    int P2UP;
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
int collisionCheck(int xnext, int ynext);
void modeSetter(void);
void updatePlayerPos(int player);
void drawPlayers(void);
void rotateUp(int player, int LR);

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
    appTron_Data->P1UP = 0;
    appTron_Data->P2UP = 2;
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
        drawPlayers();

        //insert code for bluetooth
        //void rotateUp(int player, int LR) make sure to call this for inputs
        //L = 0         R = 1

        updatePlayerPos(1);
        updatePlayerPos(2);
        modeSetter();
    }
    if(appTron_Data->mode==1)
    {
        drawWinner(appTron_Data->winner);
    }
}

void drawPlayers(void) //call first
{
    setPixel(appTron_Data->point1.x,appTron_Data->point1.y,appTron_Data->P1);
    setPixel(appTron_Data->point2.x,appTron_Data->point2.y,appTron_Data->P2);
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
    if(winner==3)
    {
        Pixel pixel;
        pixel.R=255;
        pixel.G=0;
        pixel.B=0;
        char string[5]={'D','B','L','E',' '};
        char string2[5]={'D','E','A','T','H'};
        toString(string,0,pixel);
        toString(string2,1,pixel);
    }
}

void rotateUp(int player, int LR) //L = 0         R = 1
{
    if(player==1)
    {
        if(LR==0)
        {
            appTron_Data->P1UP--;
        }
        if(LR==1)
        {
            appTron_Data->P1UP++;
        }
        if(appTron_Data->P1UP>3)
        {
            appTron_Data->P1UP=0;
        }
        if(appTron_Data->P1UP<0)
        {
            appTron_Data->P1UP=3;
        }
    }
    if(player==2)
   {
        if(LR==0)
        {
            appTron_Data->P2UP--;
        }
        if(LR==1)
        {
            appTron_Data->P2UP++;
        }
        if(appTron_Data->P2UP>3)
        {
            appTron_Data->P2UP=0;
        }
        if(appTron_Data->P2UP<0)
        {
            appTron_Data->P2UP=3;
        }
   }
}

void modeSetter(void) //last call, sets next frame
{
    int hit1,hit2;
    hit1 = collisionCheck(appTron_Data->point1.x,appTron_Data->point1.y);
    hit2 = collisionCheck(appTron_Data->point2.x,appTron_Data->point2.y);
    if((hit1&&hit2)==1)
    {
        appTron_Data->mode = 1;
        appTron_Data->winner = 3;
        return;
    }
    if(hit1==1)
    {
        appTron_Data->mode = 1;
        appTron_Data->winner =2;
        return;
    }
    if(hit2==1)
    {
        appTron_Data->mode = 1;
        appTron_Data->winner = 1;
        return;
    }
    appTron_Data->mode = 0;
    return;
}


int collisionCheck(int xnext, int ynext) //collision check returns true if collision hit, check at end to process next frame
{
    if(inBounds(xnext,ynext)!=1)
    {
        return 1;
    }
    if(comparePixel(appTron_Data->P1,getPixel(xnext, ynext))==1)
    {
        return 1;
    }
    if(comparePixel(appTron_Data->P2,getPixel(xnext, ynext))==1)
    {
        return 1;
    }
    return 0;
}

void updatePlayerPos(int player) //updates players next position for next frame
{
    int xmove[4]={0,1,0,-1};
    int ymove[4]={1,0,-1,0};
    if(player==1)
    {
        appTron_Data->point1.x+=xmove[appTron_Data->P1UP];
        appTron_Data->point1.y+=ymove[appTron_Data->P1UP];
    }
    if(player==2)
   {
       appTron_Data->point2.x+=xmove[appTron_Data->P2UP];
       appTron_Data->point2.y+=ymove[appTron_Data->P2UP];
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
