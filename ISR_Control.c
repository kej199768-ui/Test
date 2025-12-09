/*
 * ISR_Control.c
 *
 *  Created on: 2021. 12. 22.
 *      Author: IPCL
 */


#include "StructDefine.h"
#include "Func.h"
#include "Sequence.h"
#include "ADC.h"
#include "Task_Control.h"
#include "ISR_Control.h"
#include "Task.h"
#include "ISR.h"
#include <math.h>



/******************************************************************************
 *Half Cycle Detection º¯¼ö
 *****************************************************************************/
Uint16 giflag_PosCycle;
Uint16 giflag_NegCycle;
Uint16 giFlag_HSSW_Deadzone;
Uint16 giFlag_LSSW_Deadzone;
Uint32 giPos_dead_cnt;
Uint32 giNeg_dead_cnt;
float gfHSSW_VmAL;
float gfHSSW_VmAH;
float gfHSSW_VmBL;
float gfHSSW_VmBH;
float gfLSSW_VmL;
float gfLSSW_VmH;
float Vm_dead;
Uint16 giHSSWDeadzoneCal = 10;
Uint16 giLSSWDeadzoneCal = 30;
float gfVgrid_CycleStartCal= 0;
float gfVgrid_CycleEndCal= 40;



/******************************************************************************
 *Voltage Control ISR º¯¼ö
 *****************************************************************************/
DPID_con gcVoPFC = DPID_con_defaults;
float gfPFC_CCM_FF;
float gfPFC_DCM_FF;
float gfPFC_FF;
float gfIPFCref;
float gfIPFCphaseref;

/******************************************************************************
 *Current Control ISR º¯¼ö
 *****************************************************************************/
DPID_con gcILPFC1 = DPID_con_defaults;
DPID_con gcILPFC2 = DPID_con_defaults;
Uint16 giFlag_IL1CtrlCpl;
Uint16 giFlag_IL2CtrlCpl;
Uint16 giFlag_IL1CtrlCpl_Delay;
Uint16 giFlag_IL2CtrlCpl_Delay;
Uint16 giFlag_LSSWCpl;
Uint16 giFlag_EPwm2TZCLR = 0;
Uint16 giFlag_EPwm3TZCLR = 0;
float gfKpc=1.0;
float gfEPWM2ACMP = 0.;
float gfEPWM2BCMP = 0.;
float gfEPWM3ACMP = 0.;
float gfEPWM3BCMP = 0.;
float gfDutydithering = 0.1;

/******************************************************************************
 *Half line cycle detection º¯¼ö
 *****************************************************************************/
void HalfCycleDetection()
{
    /*------------------------------------------------------------------------------
    Sofware for Half line cycle detection
    ------------------------------------------------------------------------------*/
    if ((gfVgrid > gfVgrid_CycleStartCal)
            && (gfVgrid_LPF100 < gfVgrid_CycleStartCal)
            && (giflag_PosCycle == FALSE)
 //           && ((gfTheta_Grid >= -HalfPI) || (gfTheta_Grid < HalfPI))
        )
    {
        giflag_PosCycle = TRUE;
        giflag_NegCycle = FALSE;
    }
    else if((gfVgrid < gfVgrid_CycleEndCal)
            && (gfVgrid_LPF100 > gfVgrid_CycleEndCal)
            && (giflag_PosCycle == TRUE)
//            && ((gfTheta_Grid_Comp >= HalfPI) || (gfTheta_Grid_Comp < -HalfPI))
        )
    {
        giflag_PosCycle = FALSE;
        giflag_NegCycle = FALSE;
    }


    if ((gfVgrid < -gfVgrid_CycleStartCal)
            && (gfVgrid_LPF100 > -gfVgrid_CycleStartCal)
            && (giflag_NegCycle == FALSE)
//            && ((gfTheta_Grid >= HalfPI) || (gfTheta_Grid < -HalfPI))
        )
    {
        giflag_PosCycle = FALSE;
        giflag_NegCycle = TRUE;
    }
    else if((gfVgrid > -gfVgrid_CycleEndCal)
            && (gfVgrid_LPF100 < -gfVgrid_CycleEndCal)
            && (giflag_NegCycle == TRUE)
//            && ((gfTheta_Grid_Comp >= -HalfPI) || (gfTheta_Grid_Comp < HalfPI))
        )
    {
        giflag_PosCycle = FALSE;
        giflag_NegCycle = FALSE;
    }


    if ((giflag_PosCycle == TRUE)
            && (giflag_NegCycle == FALSE)
            )
    {
        GpioDataRegs.GPASET.bit.GPIO27  = 1;   // Enable
        if (giPos_dead_cnt < giHSSWDeadzoneCal)
        {
            giFlag_HSSW_Deadzone = TRUE;
            giFlag_LSSW_Deadzone = TRUE;
            giPos_dead_cnt++;
        }
        else if ((giPos_dead_cnt >= giHSSWDeadzoneCal)
                && (giPos_dead_cnt < giLSSWDeadzoneCal)
                )
        {
            giFlag_HSSW_Deadzone = FALSE;
            giFlag_LSSW_Deadzone = TRUE;
            giPos_dead_cnt++;
        }
        else
        {
            giFlag_HSSW_Deadzone = FALSE;
            giFlag_LSSW_Deadzone = FALSE;
            giPos_dead_cnt = giLSSWDeadzoneCal;
        }
        giNeg_dead_cnt = 0;
    }
    else if  ((giflag_PosCycle == FALSE)
            && (giflag_NegCycle == TRUE)
            )
    {
        GpioDataRegs.GPASET.bit.GPIO27  = 1;   // Enable
        if (giNeg_dead_cnt < giHSSWDeadzoneCal)
        {
            giFlag_HSSW_Deadzone = TRUE;
            giFlag_LSSW_Deadzone = TRUE;
            giNeg_dead_cnt++;
        }
        else if ((giNeg_dead_cnt >= giHSSWDeadzoneCal)
                && (giNeg_dead_cnt < giLSSWDeadzoneCal)
                )
        {
            giFlag_HSSW_Deadzone = FALSE;
            giFlag_LSSW_Deadzone = TRUE;
            giNeg_dead_cnt++;
        }
        else
        {
            giFlag_HSSW_Deadzone = FALSE;
            giFlag_LSSW_Deadzone = FALSE;
            giNeg_dead_cnt = giLSSWDeadzoneCal;
        }
        giPos_dead_cnt = 0;
    }
    else
    {
        GpioDataRegs.GPACLEAR.bit.GPIO27  = 1;   // Enable
        giFlag_HSSW_Deadzone = TRUE;
        giFlag_LSSW_Deadzone = TRUE;
        giPos_dead_cnt = 0;
        giNeg_dead_cnt = 0;
    }

    if((INT_MAIN_STATE == STAT_NORMAL_STATE)
//            && ((INT_NORMAL_STATE & STAT_PFCRLYON) == STAT_PFCRLYON)
            && (giFlag_PFCRlyCpl == TRUE)
            && (giflag_PosCycle == TRUE)
            && (giflag_NegCycle == FALSE)
            && (giFlag_LSSW_Deadzone == FALSE)
         )
    {
        GpioDataRegs.GPACLEAR.bit.GPIO0  = 1;
        GpioDataRegs.GPASET.bit.GPIO1  = 1;
        giFlag_LSSWCpl = TRUE;
    }
    else if((INT_MAIN_STATE == STAT_NORMAL_STATE)
//            && ((INT_NORMAL_STATE & STAT_PFCRLYON) == STAT_PFCRLYON)
            && (giFlag_PFCRlyCpl == TRUE)
            && (giflag_PosCycle == FALSE)
            && (giflag_NegCycle == TRUE)
            && (giFlag_LSSW_Deadzone == FALSE)
         )
    {
        GpioDataRegs.GPASET.bit.GPIO0  = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1  = 1;
        giFlag_LSSWCpl = TRUE;
    }
    else
    {
        GpioDataRegs.GPACLEAR.bit.GPIO0  = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1  = 1;
        giFlag_LSSWCpl = FALSE;
    }

/*
    if (giFlag_HSSW_Deadzone == FALSE)
    {
        GpioDataRegs.GPASET.bit.GPIO27  = 1;
    }
    else
    {
        GpioDataRegs.GPACLEAR.bit.GPIO27  = 1;
    }
*/

}

/******************************************************************************
 *Ãâ·Â Àü¾Ð Á¦¾î±â
 *****************************************************************************/
void VoPFC_Ctrl()
{
    if ((INT_MAIN_STATE == STAT_NORMAL_STATE)
            && (giFlag_PFCRlyCpl == TRUE)
            )
    {
        //      Calculate the outer loop PI controller using Trapezoidal Rule
        gcVoPFC.Ref = gfVoPFCrefSS;
        gcVoPFC.Fdb = gfVoPFC;
        gcVoPFC.Kp = 0.00029085 * gfVoPFC; //Kp = 0.11634     //0.000083145 * gfVoPFC; //400VÃâ·Â Àü¾Ð¿¡¼­ ÀÌµæ 0.8865156
        //실시간으로 바뀐다.
        DPID_Control_calc(&gcVoPFC);

        //Calculate gfVoPFCltage reference
        gfIPFCref = (gcVoPFC.out) * gfVgrid / (gfVgrid_RMS * gfVgrid_RMS);
//        gfIPFCref = (gcVoPFC.out) * gfVgrid * 0.000082644628099174;
        gfIPFCphaseref = gfIPFCref * 0.5 ;
    }
    else
    {
        Init_VoPFC_cont();
    }
}


/******************************************************************************
 * Àü·ùÁ¦¾î±â Ãâ·Â Àü¾Ð Á¦¾î±â
 *****************************************************************************/
void ILPFC_Ctrl1()
{
    if ((INT_MAIN_STATE == STAT_NORMAL_STATE)
            && (giFlag_PFCRlyCpl == TRUE)
            && (giFlag_HSSW_Deadzone == FALSE)
            && (giflag_PosCycle == TRUE)
            && (giflag_NegCycle == FALSE)
            )
    {
        if(giFlag_LSSW_Deadzone == FALSE)
        {
            //GpioDataRegs.GPASET.bit.GPIO27  = 1;
            //GpioDataRegs.GPCSET.bit.GPIO64  = 1;
            gcILPFC1.Ref = gfIPFCphaseref;
            gcILPFC1.Fdb = gfiLphaseA;
            gcILPFC1.FF = 1.0 - (fabs(gfVgrid) / gfVoPFC);
            gcILPFC1.Kp = 4.7776 * gfKpc / gfVoPFC;//kp=0.011944      //2.6172 * gfKpc / gfVoPFC;  // kp = 0.006543 ;
                                 //15.2728 * gfKpc / gfVoPFC;  // kp = 0.038182     //7.6 * gfKpc / gfVoPFC; // kp = 0.040346

            DPID_Control_calc(&gcILPFC1);

            gfEPWM2ACMP = gcILPFC1.out * NcountTs_UPDOWN + TBPRD_DB;
            if(gfEPWM2ACMP >= NcountTs_UPDOWN) gfEPWM2ACMP = NcountTs_UPDOWN;
            gfEPWM2BCMP = gcILPFC1.out * NcountTs_UPDOWN;

            EPwm2Regs.CMPA.bit.CMPA = gfEPWM2ACMP;
            EPwm2Regs.CMPB.bit.CMPB = gfEPWM2BCMP;

        }
        else
        {
            Init_ILPFC1_cont();
            EPwm2Regs.CMPA.bit.CMPA = NcountTs_UPDOWN;
            EPwm2Regs.CMPB.bit.CMPB = gfDutydithering * NcountTs_UPDOWN;
        }

        giFlag_IL1CtrlCpl_Delay = giFlag_IL1CtrlCpl;
        giFlag_IL1CtrlCpl = TRUE;

        if((giFlag_IL1CtrlCpl_Delay == TRUE)
                && (giFlag_EPwm2TZCLR == FALSE)
                )
        {
            EALLOW;
            EPwm2Regs.TZCLR.bit.OST = TRUE;
            EDIS;
            giFlag_EPwm2TZCLR = TRUE;
        }
    }
    else if ((INT_MAIN_STATE == STAT_NORMAL_STATE)
            && (giFlag_PFCRlyCpl == TRUE)
            && (giFlag_HSSW_Deadzone == FALSE)
            && (giflag_PosCycle == FALSE)
            && (giflag_NegCycle == TRUE)
            )
    {
        if(giFlag_LSSW_Deadzone == FALSE)
        {
            gcILPFC1.Ref = -gfIPFCphaseref;
            gcILPFC1.Fdb = -gfiLphaseA;
            gcILPFC1.FF = 1.0 - (fabs(gfVgrid) / gfVoPFC);
            gcILPFC1.Kp = 4.7776 * gfKpc / gfVoPFC;//kp=0.011944      //2.6172 * gfKpc / gfVoPFC;  // kp = 0.006543 ;
                                        //15.2728 * gfKpc / gfVoPFC;  // kp = 0.038182     //7.6 * gfKpc / gfVoPFC; // kp = 0.040346

            DPID_Control_calc(&gcILPFC1);

            gfEPWM2ACMP = (1.0 - gcILPFC1.out) * NcountTs_UPDOWN;
            gfEPWM2BCMP = (1.0 - gcILPFC1.out) * NcountTs_UPDOWN - TBPRD_DB;
            if( gfEPWM2BCMP <= 0 ) gfEPWM2BCMP = 0;

            EPwm2Regs.CMPA.bit.CMPA = gfEPWM2ACMP;
            EPwm2Regs.CMPB.bit.CMPB = gfEPWM2BCMP;

        }
        else
        {
            Init_ILPFC1_cont();
            EPwm2Regs.CMPA.bit.CMPA = (1-gfDutydithering) * NcountTs_UPDOWN;
            EPwm2Regs.CMPB.bit.CMPB = 0;
        }

        giFlag_IL1CtrlCpl_Delay = giFlag_IL1CtrlCpl;
        giFlag_IL1CtrlCpl = TRUE;

        if((giFlag_IL1CtrlCpl_Delay == TRUE)
                && (giFlag_EPwm2TZCLR == FALSE)
                )
        {
            EALLOW;
            EPwm2Regs.TZCLR.bit.OST = TRUE;
            EDIS;
            giFlag_EPwm2TZCLR = TRUE;
        }
    }
    else
    {
//        GpioDataRegs.GPACLEAR.bit.GPIO27  = 1;
//        GpioDataRegs.GPCCLEAR.bit.GPIO64  = 1;
        Init_ILPFC1_cont();
        giFlag_IL1CtrlCpl_Delay = FALSE;
        giFlag_IL1CtrlCpl = FALSE;
        giFlag_EPwm2TZCLR = FALSE;
        gfEPWM2ACMP = 0;
        gfEPWM2ACMP = 0;
        EALLOW;
        EPwm2Regs.TZFRC.bit.OST = TRUE;
        EDIS;
    }



}

void ILPFC_Ctrl2()
{

    if ((INT_MAIN_STATE == STAT_NORMAL_STATE)
            && (giFlag_PFCRlyCpl == TRUE)
            && (giFlag_HSSW_Deadzone == FALSE)
            && (giflag_PosCycle == TRUE)
            && (giflag_NegCycle == FALSE)
            )
    {
        if(giFlag_LSSW_Deadzone == FALSE)
        {
            gcILPFC2.Ref = gfIPFCphaseref;
            gcILPFC2.Fdb = gfiLphaseB;
            gcILPFC2.FF = 1.0 - (fabs(gfVgrid) / gfVoPFC);
            gcILPFC2.Kp = 4.7776 * gfKpc / gfVoPFC;//kp=0.011944      //2.6172 * gfKpc / gfVoPFC;  // kp = 0.006543 ;
                                    //15.2728 * gfKpc / gfVoPFC;  // kp = 0.038182     //7.6 * gfKpc / gfVoPFC; // kp = 0.040346

            DPID_Control_calc(&gcILPFC2);

            gfEPWM3ACMP = gcILPFC2.out * NcountTs_UPDOWN + TBPRD_DB;
            if( gfEPWM3ACMP >= NcountTs_UPDOWN ) gfEPWM3ACMP = NcountTs_UPDOWN;
            gfEPWM3BCMP = gcILPFC2.out * NcountTs_UPDOWN;

            EPwm3Regs.CMPA.bit.CMPA = gfEPWM3ACMP;
            EPwm3Regs.CMPB.bit.CMPB = gfEPWM3BCMP;

        }
        else
        {
            Init_ILPFC2_cont();
            EPwm3Regs.CMPA.bit.CMPA = NcountTs_UPDOWN;
            EPwm3Regs.CMPB.bit.CMPB = gfDutydithering * NcountTs_UPDOWN;

        }
        giFlag_IL2CtrlCpl_Delay = giFlag_IL2CtrlCpl;
        giFlag_IL2CtrlCpl = TRUE;

        if((giFlag_IL2CtrlCpl_Delay == TRUE)
                && (giFlag_EPwm3TZCLR == FALSE)
                )
        {
            EALLOW;
            EPwm3Regs.TZCLR.bit.OST = TRUE;
            EDIS;
            giFlag_EPwm3TZCLR = TRUE;
        }

    }
    else if ((INT_MAIN_STATE == STAT_NORMAL_STATE)
//            && (STAT_PFCRLYON == (INT_NORMAL_STATE & STAT_PFCRLYON))
            && (giFlag_PFCRlyCpl == TRUE)
            && (giFlag_HSSW_Deadzone == FALSE)
            && (giflag_PosCycle == FALSE)
            && (giflag_NegCycle == TRUE)
            )
    {
        if(giFlag_LSSW_Deadzone == FALSE)
        {
            gcILPFC2.Ref = -gfIPFCphaseref;
            gcILPFC2.Fdb = -gfiLphaseB;
            gcILPFC2.FF = 1.0 - (fabs(gfVgrid) / gfVoPFC);
            gcILPFC2.Kp = 4.7776 * gfKpc / gfVoPFC;//kp=0.011944      //2.6172 * gfKpc / gfVoPFC;  // kp = 0.006543 ;
                                            //15.2728 * gfKpc / gfVoPFC;  // kp = 0.038182     //7.6 * gfKpc / gfVoPFC; // kp = 0.040346

            DPID_Control_calc(&gcILPFC2);

            gfEPWM3ACMP = (1.0 - gcILPFC2.out) * NcountTs_UPDOWN;
            gfEPWM3BCMP = (1.0 - gcILPFC2.out) * NcountTs_UPDOWN - TBPRD_DB;
            if( gfEPWM3BCMP <= 0 ) gfEPWM3BCMP = 0;

            EPwm3Regs.CMPA.bit.CMPA = gfEPWM3ACMP;
            EPwm3Regs.CMPB.bit.CMPB = gfEPWM3BCMP;
        }
        else
        {
            Init_ILPFC2_cont();
            EPwm3Regs.CMPA.bit.CMPA = (1-gfDutydithering) * NcountTs_UPDOWN;
            EPwm3Regs.CMPB.bit.CMPB = 0;
        }

        giFlag_IL2CtrlCpl_Delay = giFlag_IL2CtrlCpl;
        giFlag_IL2CtrlCpl = TRUE;

        if((giFlag_IL2CtrlCpl_Delay == TRUE)
                && (giFlag_EPwm3TZCLR == FALSE)
                )
        {
            EALLOW;
            EPwm3Regs.TZCLR.bit.OST = TRUE;
            EDIS;
            giFlag_EPwm3TZCLR = TRUE;
        }

    }
    else
    {
        Init_ILPFC2_cont();
        giFlag_IL2CtrlCpl_Delay = FALSE;
        giFlag_IL2CtrlCpl = FALSE;
        giFlag_EPwm3TZCLR = FALSE;
        EALLOW;
        EPwm3Regs.TZFRC.bit.OST = TRUE;
        EDIS;
    }

}

void Init_VoPFC_cont()
{
    float  Ts_VoPFC = Ts;

    gcVoPFC.OutMax = 3300 * 1.4;
    gcVoPFC.OutMin = -3300 * 1.4;
    gcVoPFC.Tsamp = Ts_VoPFC;
    gcVoPFC.Pole = 0.99501;//0.99877;
    gcVoPFC.Zero1 = 0.9995;//0.99952;
    gcVoPFC.Zero2 = 0;
    gcVoPFC.Kp = 0.11634;//0.033258;
    gcVoPFC.Ref = 0;
    gcVoPFC.Fdb = 0;
    gcVoPFC.FF = 0;
    gcVoPFC.Err = 0;
    gcVoPFC.Err1 = 0;
    gcVoPFC.Err2 = 0;
    gcVoPFC.outtemp = 0;
    gcVoPFC.outtemp1 = 0;
    gcVoPFC.outtemp2 = 0;

}
void Init_ILPFC1_cont()
{
    float  Ts_ILPFC = Ts;

    gcILPFC1.OutMax = 0.95;  //0.95
    gcILPFC1.OutMin = 0;
    gcILPFC1.Tsamp = Ts_ILPFC;

    gcILPFC1.Pole   = 0;//0.51206;//0.;
    gcILPFC1.Zero1  = 0.96715;//0.934;//0.976;
    gcILPFC1.Zero2  = 0;//0.934;//0.;
    gcILPFC1.Kp     = 0.011944;//0.006543;//0.038182;//0.019;

    gcILPFC1.Err = 0.;
    gcILPFC1.Err1 = 0.;
    gcILPFC1.Err2 = 0.;
    gcILPFC1.outtemp = 0.;
    gcILPFC1.outtemp1 = 0.;
    gcILPFC1.outtemp2 = 0.;
    gcILPFC1.out = 0.;
}
void Init_ILPFC2_cont()
{
    float  Ts_ILPFC = Ts;

    gcILPFC2.OutMax = 0.95;  //0.95
    gcILPFC2.OutMin = 0;
    gcILPFC2.Tsamp = Ts_ILPFC;

    gcILPFC2.Pole   = 0;//0.51206;//0.;
    gcILPFC2.Zero1  = 0.96715;//0.934;//0.976;
    gcILPFC2.Zero2  = 0;//0.934;//0.;
    gcILPFC2.Kp     = 0.011944;//0.006543;//0.038182;//0.019;

    gcILPFC2.Err = 0.;
    gcILPFC2.Err1 = 0.;
    gcILPFC2.Err2 = 0.;
    gcILPFC2.outtemp = 0.;
    gcILPFC2.outtemp1 = 0.;
    gcILPFC2.outtemp2 = 0.;
    gcILPFC2.out = 0.;
}


