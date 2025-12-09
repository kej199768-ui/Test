/*
 * ISR.c
 *
 *  Created on: 2021. 12. 22.
 *      Author: IPCL
 */

#include "Parameter.h"
#include "define.h"
#include "StructDefine.h"
#include "Func.h"
#include "Sequence.h"
#include "ADC.h"
#include "Task_Control.h"
#include "ISR_Control.h"
#include "Task.h"
#include "ISR.h"
#include <math.h>



__interrupt void adca1_isr()
{
    GpioDataRegs.GPASET.bit.GPIO24  = 1;   // Enable

    ADC_Calc(1);

    if ((INT_MAIN_STATE == STAT_NORMAL_STATE)
            && (ChkFltState() != 0x0000))
    {
        INT_MAIN_STATE = STAT_FAULT_STATE;
        EPwm2Regs.TZFRC.bit.OST = 1;
        EPwm3Regs.TZFRC.bit.OST = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO0  = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1  = 1;
        giFlag_LSSWCpl = FALSE;
    }

    HalfCycleDetection();
    ILPFC_Ctrl1();

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    //
    // Check if overflow has occurred
    //
    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    GpioDataRegs.GPACLEAR.bit.GPIO24  = 1;   // Enable
}

__interrupt void adca2_isr()
{
   GpioDataRegs.GPASET.bit.GPIO26  = 1;   // Enable

    ADC_Calc(2);

    if ((INT_MAIN_STATE == STAT_NORMAL_STATE)
            && (ChkFltState() != 0x0000))
    {
        INT_MAIN_STATE = STAT_FAULT_STATE;
        EPwm2Regs.TZFRC.bit.OST = 1;
        EPwm3Regs.TZFRC.bit.OST = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO0  = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1  = 1;
        giFlag_LSSWCpl = FALSE;
    }


    VoPFC_Ctrl();
    ILPFC_Ctrl2();


    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //clear INT2 overflow flag

    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT2)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT2 = 1; //clear INT2 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //clear INT2 flag
    }
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;

    GpioDataRegs.GPACLEAR.bit.GPIO26  = 1;   // Enable
}


