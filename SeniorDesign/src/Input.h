#ifndef __INPUT__
#define __INPUT__

// Bits representing each key
#define P1_UP_INPUT 0x02
#define P1_DOWN_INPUT 0x04
#define P1_LEFT_INPUT 0x06
#define P1_RIGHT_INPUT 0x08
#define P1_A_INPUT 0x20
#define P1_B_INPUT 0x40
#define P1_START_INPUT 0x60
#define P1_SELECT_INPUT 0x80

#define P2_UP_INPUT 0x03
#define P2_DOWN_INPUT 0x05
#define P2_LEFT_INPUT 0x07
#define P2_RIGHT_INPUT 0x09
#define P2_A_INPUT 0x30
#define P2_B_INPUT 0x50
#define P2_START_INPUT 0x70
#define P2_SELECT_INPUT 0x90

// Char representing current keypresses
// e.g. UP_INPUT | A_INPUT == 0x01 | 0x10 == 0x11 == 0001 0001
// Checking e.g. Input_Status & UP_INPUT == 0x11 & 0x01 = 1
// Not Pressed e.g. Input_Status & DOWN_INPUT == 0x11 & 0x02 = 0
extern unsigned char Input_Status;

// prototypes for input init and polling functions
extern void Input_init(void);
extern void Input_Poll(void);
#endif
