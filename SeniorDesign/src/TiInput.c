#ifdef CPU1
#include "input.h"

 unsigned char Input_Status;
 char FPS;

int check_Char(char c) {
    return 0x00;
}

void Input_init(void) {
    Input_Status = 0;
}

void Input_Poll(void) {

}
#endif
