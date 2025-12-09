//
// Included Files
//
#include "Define.h"
#include "Peripheral_Config.h"
#include "ISR.h"
#include "Task.h"
#include "ADC.h"
#include "Parameter.h"
#include "Func.h"
#include "Task_Control.h"

//
// Defines
//

//
// Globals
//

#ifdef _FLASH
#pragma CODE_SECTION(adca1_isr, ".TI.ramfunc");
#pragma CODE_SECTION(adca2_isr, ".TI.ramfunc");
#pragma CODE_SECTION(Task_100us, ".TI.ramfunc");
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
#endif


//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
   InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to its default state.
//
    InitGpioConfig();

//
// For this case just init GPIO pins for ePWM1, ePWM2, ePWM3
// These functions are in the F2837xD_EPwm.c file
//
//    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();


//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
    EALLOW; // This is needed to write to EALLOW protected registers
//  PieVectTable.EPWM1_INT = &epwm1_isr;
    PieVectTable.ADCA1_INT = &adca1_isr;    //function for ADCA interrupt 1
    PieVectTable.ADCA2_INT = &adca2_isr;
//    PieVectTable.TIMER0_INT = &Task_100us;  //function for TIMER0 interrupt
    PieVectTable.TIMER1_INT = &Task_100us;
    EDIS;   // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =0;
    EDIS;

    // 사용자 초기화
    InitGpioInOutConfig();
    InitPWMEnaFltGpioConfig();
    InitMcBspSPIConfig();
//    EPwm1_Config();
    EPwm2_Config();
    EPwm3_Config();

    Adc_Config();

    SPIDAC_Config();
    // 사용자 초기화 end

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =1;
    EDIS;

    //
    // Initialize the Device Peripheral. For this example, only initialize the
    // Cpu Timers.
    //
    InitCpuTimers();
    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 200MHz CPU Freq, 1 second Period (in uSeconds)
    //
//    ConfigCpuTimer(&CpuTimer0, 200, 100);
    ConfigCpuTimer(&CpuTimer1, 200, 100);
        //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in ConfigCpuTimer and InitCpuTimers, the below settings must also be
    // be updated.
    //
//    CpuTimer0Regs.TCR.all = 0x4000;
    CpuTimer1Regs.TCR.all = 0x4000;


//
// Step 5. User specific code, enable interrupts:
// Initialize counters:
//
    InitFilterVar_100us();
    ParameterSetting();


// Enable CPU INT3 which is connected to EPWM1-3 INT:
//
//    IER |= M_INT3;
    IER |= M_INT1;
    IER |= M_INT10;
    IER |= M_INT13;

//
// Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//
//    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;          //ADCA1INT
    PieCtrlRegs.PIEIER10.bit.INTx2 = 1;          //ADCB1INT
//    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;          //TINI0
//    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;          //TINI0
//
//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// Step 6. IDLE loop. Just sit and loop forever (optional):
//
    for(;;)
    {
        asm ("          NOP");
#if 0
        while(McbspaRegs.SPCR2.bit.XRDY != 1)
        {
            a = (Uint16)(AdcaResultRegs.ADCRESULT1);
            b = 0x8000 | (Uint16)((float)(a & 0xffff));
            McbspaRegs.DXR1.all = 0x8000 | a;
        }
#endif
    }
}


