#ifndef __APP__
#define __APP__
#define APP_COUNT 2
typedef void voidFunc(void);

struct App {
	voidFunc* Demo_Init;
	voidFunc* Demo_Tick;
	voidFunc* Demo_Deinit;
	voidFunc* App_Init;
	voidFunc* App_Tick;
	voidFunc* App_Deinit;
}typedef App;

extern char AppStorage[];

extern App apps[];
extern App* currentApp;
extern App homeApp;
#endif
