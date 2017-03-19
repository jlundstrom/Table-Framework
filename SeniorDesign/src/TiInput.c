#ifdef CPU1
#include "input.h"
#include "F28x_Project.h"

//#define Launchpad

#ifdef Launchpad
    #define TX_GPIO_PIN 19
    #define TX_MUX 2
    #define RX_GPIO_PIN 18
    #define RX_MUX 2
    #define SCI_REG ScibRegs
    #define STATUS_LED 34
#else
    #define TX_GPIO_PIN 8
    #define TX_MUX 6
    #define RX_GPIO_PIN 9
    #define RX_MUX 6
    #define SCI_REG SciaRegs
    #define STATUS_LED 70
#endif

volatile struct SCI_REGS* SciRegs;
unsigned char Input_Status;

void scia_xmit(int a);
void scia_msg(char *msg);

// Initialize input device
void Input_init(void) {
    char *msg;
    Input_Status = 0;

    SciRegs = &SCI_REG;

    GPIO_SetupPinMux(TX_GPIO_PIN, GPIO_MUX_CPU1, TX_MUX);
    GPIO_SetupPinOptions(TX_GPIO_PIN, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(RX_GPIO_PIN, GPIO_MUX_CPU1, RX_MUX);
    GPIO_SetupPinOptions(RX_GPIO_PIN, GPIO_OUTPUT, GPIO_ASYNC);

    GPIO_SetupPinOptions(STATUS_LED, GPIO_OUTPUT, GPIO_ASYNC);

    // FIFO Init
    SciRegs->SCIFFTX.all = 0xE040;
    SciRegs->SCIFFRX.all = 0x2044;
    SciRegs->SCIFFCT.all = 0x0;

    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //
    SciRegs->SCICCR.all = 0x0007;   // 1 stop bit,  No loopback
                                    // No parity,8 char bits,
                                    // async mode, idle-line protocol
    SciRegs->SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK,
                                    // Disable RX ERR, SLEEP, TXWAKE
    SciRegs->SCICTL2.all = 0x0003;
    SciRegs->SCICTL2.bit.TXINTENA = 1;
    SciRegs->SCICTL2.bit.RXBKINTENA = 1;

    //
    // SCIA at 9600 baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B.
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x86.
    // @LSPCLK = 25 MHz (100 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x45.
    //
    SciRegs->SCIHBAUD.all = 0x0001;
    SciRegs->SCILBAUD.all = 0x0045;

    SciRegs->SCICTL1.all = 0x0023;  // Relinquish SCI from Reset

    msg = "\r\n\n\nSmart table Startup\0";
    scia_msg(msg);
}

// Check for input status updates and update
// Input_Status to represent current key presses.
void Input_Poll(void) {
    Uint16 ReceivedChar;
    Uint16 isLowercase;
    if(SciRegs->SCIFFRX.bit.RXFFST != 0)
    {
        ReceivedChar = SciRegs->SCIRXBUF.all;
        scia_xmit(ReceivedChar);
        isLowercase = ReceivedChar & 0x20;
        ReceivedChar |= 0x20; // Case to lowercase
        GPIO_WritePin(STATUS_LED, GPIO_ReadPin(STATUS_LED) ^ 0x01);

        if(ReceivedChar == 'w')
        {
            if(!isLowercase)
            {
                Input_Status &= ~UP_INPUT;
            }
            else
            {
                Input_Status |= UP_INPUT;
            }
        }

        if(ReceivedChar == 'a')
        {
            if(!isLowercase)
            {
                Input_Status &= ~LEFT_INPUT;
            }
            else
            {
                Input_Status |= LEFT_INPUT;
            }
        }
        if(ReceivedChar == 's')
        {
            if(!isLowercase)
            {
                Input_Status &= ~DOWN_INPUT;
            }
            else
            {
                Input_Status |= DOWN_INPUT;
            }
        }
        if(ReceivedChar == 'd')
        {
            if(!isLowercase)
            {
                Input_Status &= ~RIGHT_INPUT;
            }
            else
            {
                Input_Status |= RIGHT_INPUT;
            }
        }
        if(ReceivedChar == 'q')
        {
            if(!isLowercase)
            {
                Input_Status &= ~A_INPUT;
            }
            else
            {
                Input_Status |= A_INPUT;
            }
        }
        if(ReceivedChar == 'e')
        {
            if(!isLowercase)
            {
                Input_Status &= ~B_INPUT;
            }
            else
            {
                Input_Status |= B_INPUT;
            }
        }
        if(ReceivedChar == 'h')
        {
            if(!isLowercase)
            {
                Input_Status &= ~START_INPUT;
            }
            else
            {
                Input_Status |= START_INPUT;
            }
        }
        if(ReceivedChar == 'j')
        {
            if(!isLowercase)
            {
                Input_Status &= ~SELECT_INPUT;
            }
            else
            {
                Input_Status |= SELECT_INPUT;
            }
        }
    }
}

//
// scia_xmit - Transmit a character from the SCI
//
void scia_xmit(int a)
{
    while (SciRegs->SCIFFTX.bit.TXFFST != 0) {}
    SciRegs->SCITXBUF.all =a;
}

//
// scia_msg - Transmit message via SCIA
//
void scia_msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        scia_xmit(msg[i]);
        i++;
    }
}
#endif
