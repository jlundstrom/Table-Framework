#ifdef CPU1
#include <string.h>
#include "input.h"
#include "F28x_Project.h"

// string-compatible helper functions
void flush(char buf[], Uint16 length);
void sciRead(char buf[], Uint16 length);
void sciWrite(char buf[]);

unsigned char Input_Status;
char          timeString[32] = "";

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

   // SCI-A receive pin
   GpioCtrlRegs.GPAGMUX1.bit.GPIO9 = 1; // Mux as SCI-A RX
   GpioCtrlRegs.GPAMUX1.bit.GPIO9  = 2; // Mux as SCI-A RX (cont.)
   GpioCtrlRegs.GPADIR.bit.GPIO9   = 0; // Set as input
   GpioCtrlRegs.GPAPUD.bit.GPIO9   = 0; // Enable pull-up (since input)
   GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 3; // Asynchronous (since input)

   // Status LED
   GpioCtrlRegs.GPCDIR.bit.GPIO70 = 1;
   GpioDataRegs.GPCDAT.bit.GPIO70 = 1;

   EDIS;

   // 1 stop bit,  no loopback,
   // no parity, 8 data bits, no control flow
   // async mode, idle-line protocol
   SciaRegs.SCICCR.all = 0x07;

   // Enable TX, RX, internal SCICLK
   // Disable RX ERR, SLEEP, TXWAKE
   SciaRegs.SCICTL1.all = 0x03;

   SciaRegs.SCICTL2.bit.TXINTENA   = 1;
   SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

   // 9600 baud, 25 MHz LSPCLK, 100 MHz SYSCLK
   SciaRegs.SCIHBAUD.all = 0x01;
   SciaRegs.SCILBAUD.all = 0x45;

   // Relinquish SCI from reset
   SciaRegs.SCICTL1.all = 0x23;

   sciWrite("\r\n\n\nSmart Table Startup\0");
}


// Check for input status updates and update
// Input_Status to represent current key presses
void Input_Poll(void)
{
   if (SciaRegs.SCIRXST.bit.RXRDY) // prevents from being locked in inf loop
   {
      char   rcvBuf [2]  = "";     // receive buffer
      Uint16 isLowercase = 0;

      sciRead(rcvBuf, 1);          // read the input
      sciWrite(rcvBuf);            // echo the input

      isLowercase = rcvBuf[0] & 0x20;
      rcvBuf[0]  |= 0x20;

      if (rcvBuf[0] == 't')
      {
         sciRead(timeString, 18);  // read and store the date and time
         GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
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
   }
}


void sciRead(char buf[], Uint16 length)
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


void sciWrite(char buf[])
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


// flush any buffer if needed
void flush(char buf[], Uint16 length)
{
   strncpy(buf, "", length);
}


#endif
