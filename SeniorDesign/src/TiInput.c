#ifdef CPU1
#include <string.h>
#include "Input.h"
#include "F28x_Project.h"

// string-compatible helper functions
void sciaRead(char buf[], Uint16 length);
void sciaWrite(char buf[]);
void scibRead(char buf[], Uint16 length);
void scibWrite(char buf[]);

unsigned char Input_Status;
unsigned char User2_Input_Status;

unsigned char Input_Tap;
unsigned char User2_Input_Tap;

char date[6];
char time[6];

// Initialize input device
void Input_init(void)
{
   Input_Status = 0;

   EALLOW;

   // Set regs for proper pin behavior
   // SCI-A transmit pin
   GpioCtrlRegs.GPAGMUX1.bit.GPIO8 = 1; // Mux as SCI-A TX
   GpioCtrlRegs.GPAMUX1.bit.GPIO8  = 2; // Mux as SCI-A TX (cont.)
   GpioCtrlRegs.GPADIR.bit.GPIO8   = 1; // Set as output
   GpioCtrlRegs.GPAPUD.bit.GPIO8   = 1; // Disable pull-up (since output)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO8 = 0; // Synchronous (since output)

   // SCI-B transmit pin
   GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 0;
   GpioCtrlRegs.GPAMUX2.bit.GPIO18  = 2;
   GpioCtrlRegs.GPADIR.bit.GPIO18   = 1;
   GpioCtrlRegs.GPAPUD.bit.GPIO18   = 1;
   GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 0;

   // SCI-A receive pin
   GpioCtrlRegs.GPAGMUX1.bit.GPIO9 = 1; // Mux as SCI-A RX
   GpioCtrlRegs.GPAMUX1.bit.GPIO9  = 2; // Mux as SCI-A RX (cont.)
   GpioCtrlRegs.GPADIR.bit.GPIO9   = 0; // Set as input
   GpioCtrlRegs.GPAPUD.bit.GPIO9   = 0; // Enable pull-up (since input)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 3; // Asynchronous (since input)

   // SCI-B receive pin
   GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 0;
   GpioCtrlRegs.GPAMUX2.bit.GPIO19  = 2;
   GpioCtrlRegs.GPADIR.bit.GPIO19   = 0;
   GpioCtrlRegs.GPAPUD.bit.GPIO19   = 0;
   GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;

   // Status LED
   GpioCtrlRegs.GPCDIR.bit.GPIO70 = 1;
   GpioDataRegs.GPCDAT.bit.GPIO70 = 1;
   GpioCtrlRegs.GPCDIR.bit.GPIO69 = 1;
   GpioDataRegs.GPCDAT.bit.GPIO69 = 1;

   EDIS;

   // 1 stop bit,  no loopback,
   // no parity, 8 data bits, no control flow
   // async mode, idle-line protocol
   SciaRegs.SCICCR.all = 0x07;
   ScibRegs.SCICCR.all = 0x07;

   // Enable TX, RX, internal SCICLK
   // Disable RX ERR, SLEEP, TXWAKE
   SciaRegs.SCICTL1.all            = 0x03;
   ScibRegs.SCICTL1.all            = 0x03;
   SciaRegs.SCICTL2.bit.TXINTENA   = 1;
   SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
   ScibRegs.SCICTL2.bit.TXINTENA   = 1;
   ScibRegs.SCICTL2.bit.RXBKINTENA = 1;

   // 9600 baud, 25 MHz LSPCLK, 100 MHz SYSCLK
   SciaRegs.SCIHBAUD.all = 0x01;
   SciaRegs.SCILBAUD.all = 0x45;
   ScibRegs.SCIHBAUD.all = 0x01;
   ScibRegs.SCILBAUD.all = 0x45;

   // Relinquish SCI from reset
   SciaRegs.SCICTL1.all = 0x23;
   ScibRegs.SCICTL1.all = 0x23;

   sciaWrite("\r\nProgram Start -- Player 1 Channel\0");
   scibWrite("\r\nProgram Start -- Player 2 Channel\0");
}


// Check for input status updates and update
// Input_Status to represent current key presses
void Input_Poll(void)
{
   Uint16        isLowercase = 0;
   char          rcvBuf [2]  = ""; // receive buffer
   unsigned char prev;

   if (SciaRegs.SCIRXST.bit.RXRDY) // prevents from being locked in inf loop
   {
      sciaRead(rcvBuf, 1);         // read the input
      isLowercase = rcvBuf[0] & 0x20;
      rcvBuf[0]  |= 0x20;
      prev        = Input_Status;

      if (rcvBuf[0] == 'z')
      {
         // read and store the date and time
         sciaRead(date, 6);
         sciaRead(time, 6);
      }

      if (rcvBuf[0] == 'w')
      {
         if (!isLowercase)
         {
            Input_Status &= ~UP_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
         else
         {
            Input_Status |= UP_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
      }

      if (rcvBuf[0] == 's')
      {
         if (!isLowercase)
         {
            Input_Status &= ~DOWN_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
         else
         {
            Input_Status |= DOWN_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
      }

      if (rcvBuf[0] == 'a')
      {
         if (!isLowercase)
         {
            Input_Status &= ~LEFT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
         else
         {
            Input_Status |= LEFT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
      }

      if (rcvBuf[0] == 'd')
      {
         if (!isLowercase)
         {
            Input_Status &= ~RIGHT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
         else
         {
            Input_Status |= RIGHT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
      }

      if (rcvBuf[0] == 'q')
      {
         if (!isLowercase)
         {
            Input_Status &= ~A_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
         else
         {
            Input_Status |= A_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
      }

      if (rcvBuf[0] == 'e')
      {
         if (!isLowercase)
         {
            Input_Status &= ~B_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
         else
         {
            Input_Status |= B_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
      }

      if (rcvBuf[0] == 'h')
      {
         if (!isLowercase)
         {
            Input_Status &= ~START_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
         else
         {
            Input_Status |= START_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
      }

      if (rcvBuf[0] == 'j')
      {
         if (!isLowercase)
         {
            Input_Status &= ~SELECT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
         else
         {
            Input_Status |= SELECT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
      }

      // Raise Tap for keys with a state change that ends with it being pressed
      Input_Tap |= (prev ^ Input_Status) & Input_Status;
   }

   if (ScibRegs.SCIRXST.bit.RXRDY) // prevents from being locked in inf loop
   {
      scibRead(rcvBuf, 1);         // read the input
      isLowercase = rcvBuf[0] & 0x20;
      rcvBuf[0]  |= 0x20;
      prev        = User2_Input_Status;

      // read and store the date and time
      if (rcvBuf[0] == 'z')
      {
         // read and store the date and time
         scibRead(date, 6);
         scibRead(time, 6);
      }

      if (rcvBuf[0] == 'w')
      {
         if (!isLowercase)
         {
            User2_Input_Status &= ~UP_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
         else
         {
            User2_Input_Status |= UP_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
      }

      if (rcvBuf[0] == 's')
      {
         if (!isLowercase)
         {
            User2_Input_Status &= ~DOWN_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO70 = 1;
         }
         else
         {
            User2_Input_Status |= DOWN_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
      }

      if (rcvBuf[0] == 'a')
      {
         if (!isLowercase)
         {
            User2_Input_Status &= ~LEFT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
         else
         {
            User2_Input_Status |= LEFT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
      }

      if (rcvBuf[0] == 'd')
      {
         if (!isLowercase)
         {
            User2_Input_Status &= ~RIGHT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
         else
         {
            User2_Input_Status |= RIGHT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
      }

      if (rcvBuf[0] == 'q')
      {
         if (!isLowercase)
         {
            User2_Input_Status &= ~A_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
         else
         {
            User2_Input_Status |= A_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
      }

      if (rcvBuf[0] == 'e')
      {
         if (!isLowercase)
         {
            User2_Input_Status &= ~B_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
         else
         {
            User2_Input_Status |= B_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
      }

      if (rcvBuf[0] == 'h')
      {
         if (!isLowercase)
         {
            User2_Input_Status &= ~START_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
         else
         {
            User2_Input_Status |= START_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
      }

      if (rcvBuf[0] == 'j')
      {
         if (!isLowercase)
         {
            User2_Input_Status &= ~SELECT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
         else
         {
            User2_Input_Status |= SELECT_INPUT;
            GpioDataRegs.GPCTOGGLE.bit.GPIO69 = 1;
         }
      }

      // Raise Tap for keys with a state change that ends with it being pressed
      User2_Input_Tap |= (prev ^ User2_Input_Status) & User2_Input_Status;
   }
}


void sciaRead(char buf[], Uint16 length)
{
   Uint16 bytesRead   = 0;
   Uint16 bytesToRead = length;

   while (bytesRead < bytesToRead)
   {
      while (!SciaRegs.SCIRXST.bit.RXRDY)
      {
      }
      buf[bytesRead] = SciaRegs.SCIRXBUF.all;
      bytesRead++;
   }
}


void sciaWrite(char buf[])
{
   Uint16 bytesWritten = 0;
   Uint16 bytesToWrite = strlen(buf);

   while (bytesWritten < bytesToWrite)
   {
      while (!SciaRegs.SCICTL2.bit.TXRDY)
      {
      }
      SciaRegs.SCITXBUF.all = buf[bytesWritten];
      bytesWritten++;
   }
}


void scibRead(char buf[], Uint16 length)
{
   Uint16 bytesRead   = 0;
   Uint16 bytesToRead = length;

   while (bytesRead < bytesToRead)
   {
      while (!ScibRegs.SCIRXST.bit.RXRDY)
      {
      }
      buf[bytesRead] = ScibRegs.SCIRXBUF.all;
      bytesRead++;
   }
}


void scibWrite(char buf[])
{
   Uint16 bytesWritten = 0;
   Uint16 bytesToWrite = strlen(buf);

   while (bytesWritten < bytesToWrite)
   {
      while (!ScibRegs.SCICTL2.bit.TXRDY)
      {
      }
      ScibRegs.SCITXBUF.all = buf[bytesWritten];
      bytesWritten++;
   }
}


#endif
