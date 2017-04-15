#ifdef CPU1
#include "F28x_Project.h"
#include "F2837xD_GlobalPrototypes.h"
#include "Display.h"
#include "Draw.h"

#ifndef __cplusplus
#ifdef __TI_COMPILER_VERSION__
#if __TI_COMPILER_VERSION__ >= 15009000
#pragma CODE_SECTION(epwm1_isr, ".TI.ramfunc");
#else
#pragma CODE_SECTION(epwm1_isr, "ramfuncs");
#endif
#endif
#endif
//
// Defines
//
#define DATAPERIOD       29
#define RESETPERIOD      61000
#define ONEDUTY          24
#define ZERODUTY         9
#define RESETDUTY        0
#define EPWM_CMP_UP      1
#define EPWM_CMP_DOWN    0
//
// Globals
//
typedef struct
{
   volatile struct EPWM_REGS *EPwmRegHandle;
   Uint16                    EPwm_CMPA_Direction;
   Uint16                    EPwm_CMPB_Direction;
   Uint16                    EPwmTimerIntCount;
   Uint16                    EPwmMaxCMPA;
   Uint16                    EPwmMinCMPA;
   Uint16                    EPwmMaxCMPB;
   Uint16                    EPwmMinCMPB;
} EPWM_INFO;

EPWM_INFO     epwm1_info;
unsigned char PauseMul   = 5;
unsigned char *rawPixels = (unsigned char *)Pixels;
unsigned char *endPixel  = (unsigned char *)&Pixels[WIDTH * HEIGHT];
unsigned char mask       = 0x80;
unsigned char DRAWN      = 0;

//
//  Function Prototypes
//
void InitEPwm1();
__interrupt void epwm1_isr(void);

void Display_init()
{
   InitSysCtrl();
   CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;   //misc init

   EALLOW;                             //This turns on GPIO80 to EPWM output
   GpioCtrlRegs.GPAPUD.bit.GPIO0  = 1; // Disable pull-up on GPIO0 (EPWM1A)
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1; // Configure GPIO0 as EPWM1A
   EDIS;

   DINT;

   //
   // Disable Interrupts at the CPU level:
   //
   DINT;

   //
   // Initialize the PIE control registers to their default state.
   // The default state is all PIE interrupts disabled and flags
   // are cleared.
   // This function is found in the F2837xD_PieCtrl.c file.
   //
   InitPieCtrl();

   IER = 0x0000;
   IFR = 0x0000;

   InitPieVectTable();
#ifdef _FLASH
   memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif

   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.EPWM1_INT = &epwm1_isr;
   EDIS;

   EALLOW;
   CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
   EDIS;

   InitEPwm1();  //need this to startup base level settings
   EPwm1Regs.TBPRD         = RESETPERIOD;
   EPwm1Regs.CMPA.bit.CMPA = RESETDUTY;


   EALLOW;
   CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
   EDIS;

   IER |= M_INT3;

   PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM
}


__attribute__((ramfunc))
__interrupt void epwm1_isr(void)
{
   //
   // Update the CMPA and CMPB values
   //
   //update_compare(&epwm1_info);

   if (rawPixels >= endPixel)
   {
      EPwm1Regs.TBPRD         = RESETPERIOD;
      EPwm1Regs.CMPA.bit.CMPA = RESETDUTY;
      if (PauseMul-- == 0)
      {
         rawPixels = (unsigned char *)&Pixels[0];
         DRAWN     = 1;
         PauseMul  = 5;
      }
   }
   else if (*rawPixels & mask)
   {
      EPwm1Regs.TBPRD         = DATAPERIOD;
      EPwm1Regs.CMPA.bit.CMPA = ONEDUTY;

      mask = mask >> 1;
   }
   else
   {
      EPwm1Regs.TBPRD         = DATAPERIOD;
      EPwm1Regs.CMPA.bit.CMPA = ZERODUTY;

      mask = mask >> 1;
   }

   if (!mask)
   {
      mask = 0x80;
      rawPixels++;
   }

   //
   // Clear INT flag for this timer
   //
   EPwm1Regs.ETCLR.bit.INT = 1;

   //
   // Acknowledge this interrupt to receive more interrupts from group 3
   //
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}


void Draw(void)
{
}


void InitEPwm1()
{
   //
   // Setup TBCLK
   //
   EPwm1Regs.TBCTL.bit.CTRMODE   = TB_COUNT_UP; // Count up
   EPwm1Regs.TBCTL.bit.PHSEN     = TB_DISABLE;  // Disable phase loading
   EPwm1Regs.TBPHS.bit.TBPHS     = 0x0000;      // Phase is 0
   EPwm1Regs.TBCTR               = 0x0000;      // Clear counter
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0x001;       // Clock ratio to SYSCLKOUT   2
   EPwm1Regs.TBCTL.bit.CLKDIV    = 0x000;       // 1
   //
   // Setup shadow register load on ZERO
   //
   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   //
   // Set actions
   //
   EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM1A on Zero
   EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM1A on event A,
                                                 // up count
   //
   // Interrupt where we will change the Compare Values
   //
   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTEN  = 1;               // Enable INT
   EPwm1Regs.ETPS.bit.INTPRD  = ET_1ST;          // Generate INT on xth event

   //
   // Information this example uses to keep track
   // of the direction the CMPA/CMPB values are
   // moving, the min and max allowed values and
   // a pointer to the correct ePWM registers
   //
   epwm1_info.EPwm_CMPA_Direction = EPWM_CMP_UP; // Start by increasing
                                                 // CMPA
   epwm1_info.EPwmTimerIntCount = 0;             // Zero the interrupt counter
   epwm1_info.EPwmRegHandle     = &EPwm1Regs;    // Set the pointer to the
                                                 // ePWM module
}


#endif
