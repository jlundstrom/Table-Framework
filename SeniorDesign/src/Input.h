#ifndef __INPUT__
#define __INPUT__

// Bits representing each key
#define NORMAL_INPUT 0x3F
#define UP_INPUT 0x01
#define DOWN_INPUT 0x02
#define LEFT_INPUT 0x04
#define RIGHT_INPUT 0x08
#define A_INPUT 0x10
#define B_INPUT 0x20
#define START_INPUT 0x40
#define SELECT_INPUT 0x80

// Char representing current keypresses
// e.g. UP_INPUT | A_INPUT == 0x01 | 0x10 == 0x11 == 0001 0001
// Checking e.g. Input_Status & UP_INPUT == 0x11 & 0x01 = 1
// Not Pressed e.g. Input_Status & DOWN_INPUT == 0x11 & 0x02 = 0
extern unsigned char Input_Status;
extern unsigned char User2_Input_Status;

extern unsigned char Input_Tap;
extern unsigned char User2_Input_Tap;

extern char date[6];
extern char time[6];

// prototypes for input init and polling functions
extern void Input_init(void);
extern void Input_Poll(void);

// prototype for detecting long inputs
extern void Input_Draw_Tick(void);
extern int P1_Long_Hold(unsigned char, int);
extern int P2_Long_Hold(unsigned char, int);
#endif
