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
#include "src/App_Conway.h"
#include "src/App_Boot.h"
#include "src/App_Party.h"
#include "src/App_Tron.h"
#include "src/App_Shooter.h"
#include "src/App_Cloud.h"
#include "src/App_Clock.h"
#include "src/App_Tetris.h"

void main()
{
	App boot;
   // Initializes platform specifics components
   // Display_init should set system clocks if needed
   Display_init();
   Input_init();

   // Configures the primary app menu, builds the application structs and setsup the array
   App_Menu_New(&homeApp);
   App_Basic_New(&apps[0]);
   App_Snake_New(&apps[1]);
   App_Conway_New(&apps[2]);
   App_Tetris_New(&apps[3]);
   App_Party_New(&apps[4]);
   App_Tron_New(&apps[5]);
   App_Clock_New(&apps[6]);
   App_Shoot_New(&apps[7]);
   App_Cloud_New(&apps[8]);

   // Boot Animation
   App_Boot_New(&boot);
   boot.App_Init();
   while (!Input_Tap)
   {
	   if (DRAWN == 1)
	   {
		   boot.App_Tick();
		   DRAWN = 0;
	   }

	   // Trigger a frame redraw. Currently only used by WinDisplay
	   Draw();
	   // Check for new input
	   Input_Poll();
   }
   boot.App_Deinit();
   Input_Tap = 0;

   // Initialize the Menu
   currentApp = &homeApp;
   currentApp->App_Init();

   // Main application loop Quit if select is pressed
   // Quitting is currently used for Windows emulation
   while (1)
   {
      // Check if the start button is pressed to return to menu
      App_Menu_Poll();

      // Tick the application if a frame has been drawn
      // Clearing the flag if it's been used
      if (DRAWN == 1)
      {
         currentApp->App_Tick();
         DRAWN = 0;
      }

      // Trigger a frame redraw. Currently only used by WinDisplay
      Draw();
      // Check for new input
      Input_Poll();

#ifdef WIN32
      // Print frame status for windows
      if (DRAWN)
      {
         printf("Input: %02X ", Input_Status);
         printf("Tap: %02X ", Input_Tap);
         printf("FPS: %02d\r", FPS);
      }
#endif
   }
}
