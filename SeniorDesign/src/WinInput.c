#ifdef WIN32
#include "input.h"
#include <windows.h>

unsigned char Input_Status;
unsigned char User2_Input_Status;

unsigned char Input_Tap;
unsigned char User2_Input_Tap;

unsigned char date[6];
unsigned char time[6];

// Get character status from Windows
int check_Char(char c)
{
   return (GetKeyState(c) >> 16) & 0x1;
}


void Input_init(void)
{
   Input_Status = 0;
}


// Check if user is pressing an input key
// If one is pressed set the bit high else low
void Input_Poll(void)
{
   unsigned char prev = Input_Status;

   if (check_Char('W'))
   {
      Input_Status |= UP_INPUT;
   }
   else
   {
      Input_Status &= ~UP_INPUT;
   }
   if (check_Char('S'))
   {
      Input_Status |= DOWN_INPUT;
   }
   else
   {
      Input_Status &= ~DOWN_INPUT;
   }
   if (check_Char('A'))
   {
      Input_Status |= LEFT_INPUT;
   }
   else
   {
      Input_Status &= ~LEFT_INPUT;
   }
   if (check_Char('D'))
   {
      Input_Status |= RIGHT_INPUT;
   }
   else
   {
      Input_Status &= ~RIGHT_INPUT;
   }
   if (check_Char('Q'))
   {
      Input_Status |= A_INPUT;
   }
   else
   {
      Input_Status &= ~A_INPUT;
   }
   if (check_Char('E'))
   {
      Input_Status |= B_INPUT;
   }
   else
   {
      Input_Status &= ~B_INPUT;
   }
   if (check_Char('H'))
   {
      Input_Status |= START_INPUT;
   }
   else
   {
      Input_Status &= ~START_INPUT;
   }
   if (check_Char('J'))
   {
      Input_Status |= SELECT_INPUT;
   }
   else
   {
      Input_Status &= ~SELECT_INPUT;
   }

   // Raise Tap for keys with a state change that ends with it being pressed
   Input_Tap |= (prev ^ Input_Status) & Input_Status;
}


#endif
