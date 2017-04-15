#ifndef __APP__
#define __APP__

// Count of applicaions in menu
#define APP_COUNT 8

// Structs for critical application functions and
typedef void voidFunc(void);
struct App {
	voidFunc* Demo_Init;
	voidFunc* Demo_Tick;
	voidFunc* Demo_Deinit;
	voidFunc* App_Init;
	voidFunc* App_Tick;
	voidFunc* App_Deinit;
}typedef App;

// Shared data for applications
extern unsigned char AppStorage[];

// Array of applications for menu
extern App apps[];
// Currently loaded applications
extern App* currentApp;
// Home/Menu application
extern App homeApp;
#endif
