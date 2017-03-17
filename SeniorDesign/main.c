#ifdef WIN32
    #include <stdio.h>
    //#include <windows.h>
    //#include <conio.h>
#endif
#ifdef CPU1
#include "F28x_Project.h"
#endif

#include "src/Display.h"
#include "src/Draw.h"
#include "src/Input.h"
#include "src/App.h"
#include "src/App_Basic.h"
#include "src/App_Snake.h"
#include "src/App_Menu.h"

int main() {
    Display_init();
    Input_init();

    App_Menu_New(&homeApp);
    App_Basic_New(&apps[0]);
    App_Snake_New(&apps[1]);

    currentApp = &homeApp;
    currentApp->App_Init();

    while (!(Input_Status & SELECT_INPUT)) {
        App_Menu_Poll();
        if(DRAWN == 1) {
            currentApp->App_Tick();
            DRAWN = 0;
        }
        Draw();
        Input_Poll();

#ifdef WIN32
        printf("Input: %02X\n", Input_Status);
        printf("FPS: %02d\n", FPS);
#endif
    }

    return 0;
}
