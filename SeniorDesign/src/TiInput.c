#ifdef CPU1
#include "input.h"

unsigned char Input_Status;

// Initialize input device
void Input_init(void) {
    Input_Status = 0;
}

// Check for input status updates and update
// Input_Status to represent current key presses.
void Input_Poll(void) {

}
#endif
