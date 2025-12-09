/*
 * Task.c
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
#include "Task.h"
#include <math.h>

__interrupt void Task_100us(void)
{
    GpioDataRegs.GPASET.bit.GPIO25  = 1;   // Enable
    EINT;

    ADC_Offset_Calc_100us();
    ADC_LPF_RMS_Calc_100us();
    GridPartCalc_100us();
    ChkMainState();
    Precharging_100us();
    PFCRly_100us();
    SoftStart_100us();
    SPIDAC_100us(); //ADC.c에 작성 (가장 아래)

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
    GpioDataRegs.GPACLEAR.bit.GPIO25  = 1;   // Enable
}



