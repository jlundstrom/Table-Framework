#include "App.h"

unsigned char _AppStorage[2048];
void*         AppStorage;
App           apps[APP_COUNT];
App           *currentApp;
App           homeApp;
