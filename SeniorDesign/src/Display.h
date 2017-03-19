#ifndef __DISPLAY__
#define __DISPLAY__

// Current FPS of display
extern char FPS;
// Flag to signify a frame has been drawn
extern unsigned char DRAWN;

// Functions to initialize the display and draw current frame
extern void Display_init(void);
extern void Draw(void);
#endif
