/*
 * DPP_Interrupt.c
 *
 *  Created on: 2020. 11. 16.
 *      Author: poweryhs
 */
#include "Define.h"
#include "ISR.h"
#include "Func.h"
#include "Task_Control.h"
#include "ADC.h"
#include "Sequence.h"
#include <math.h>


INTERNAL_STATE INT_MAIN_STATE;
MODE_STATE INT_MODE_STATE;

Uint16 INT_FLT_STATE = 0x0000;
Uint16 INT_FLTSUB_STATE = 0x0000;
Uint16 INT_INHIBIT_STATE = 0x0000;
Uint16 INT_NORMAL_STATE = 0x0000;
Uint16 INT_SUB_STATE = 0x0000;
Uint16 giFlag_Run = 0;
Uint16 giTEST_Mode = 0;
Uint16 giModeState = 0;
Uint16 giFlag_FltClr = 0;

float gfVCBOVFlt = 20.0;
float gfVCBUVFlt = 10.0;
float gfiLPFCOCFlt = 20.0;
float gfOutCurrOCFlt = 20.0;
float gfVgridOVFlt = 264.0*SQRT2*1.2;
float gfVgridUVFlt = 85.0*0.8;
float gfVoPFCOVFlt = 800.0 * 1.2;
float gfVoPFCUVFlt = 85.0 * SQRT2 * 0.8;
float gfTempFlt = 90.0;
float gfVgridUVInhibit = 85.0 * 0.8;
float gfVoPFCUVInhibit = 85.0* SQRT2 * 0.8;
Uint16 giVgridUVInhibitFlag = 0;

void ChkMainState()
{
    if (ChkInhibitState() != 0x0000)
    {
        INT_MAIN_STATE = STAT_INHIBIT_STATE;
        INT_NORMAL_STATE = 0x00;
    }
    else if (ChkFltState() != 0x0000)
    {
        INT_MAIN_STATE = STAT_FAULT_STATE;
        INT_NORMAL_STATE = 0x00;
    }
    else
    {
        ChkNormalState();
        INT_MAIN_STATE = STAT_NORMAL_STATE;
    }

    if(giFlag_FltClr == 1)
    {
        giFlag_FltClr = 0;
        INT_FLT_STATE = 0x0000;
        INT_FLTSUB_STATE = 0x0000;
    }
}


Uint16 ChkFltState()
{
#if 0
    if (gfVCB_LPF > gfVCBOVFlt)
    {
        INT_FLT_STATE |= STAT_VCB_FLT;
        INT_FLTSUB_STATE |= STAT_VCB_OV_FLT;
    }
    else if (gfVCB_LPF < gfVCBUVFlt)
    {
        INT_FLT_STATE |= STAT_VCB_FLT;
        INT_FLTSUB_STATE |= STAT_VCB_UV_FLT;
    }

#endif
    if (gfVgrid > gfVgridOVFlt)
    {
        INT_FLTSUB_STATE |= STAT_GRIDOV_FLT;
    }

#if 0
    if ((gfVgrid  < gfVgridUVFlt) && ((INT_MAIN_STATE & STAT_NORMAL_STATE) == STAT_NORMAL_STATE))
    {
        INT_FLTSUB_STATE |= STAT_GRIDUV_FLT;
    }
#endif

    if (fabs(gfiLphaseA) > gfiLPFCOCFlt)
    {
        INT_FLTSUB_STATE |= STAT_PFCPHASEAOC_FLT;
    }
    if (fabs(gfiLphaseB) > gfiLPFCOCFlt)
    {
        INT_FLTSUB_STATE |= STAT_PFCPHASEBOC_FLT;
    }
    if (gfVoPFC > gfVoPFCOVFlt)
    {
        INT_FLTSUB_STATE |= STAT_PFCOUTOV_FLT;
    }

#if 0
    if ((gfVoPFC < gfVoPFCUVFlt) && ((INT_MAIN_STATE & STAT_NORMAL_STATE) == STAT_NORMAL_STATE))
    {
        INT_FLTSUB_STATE |= STAT_PFCOUTUV_FLT;
    }
    if (gfTemp > gfTempFlt)
    {
        INT_FLTSUB_STATE |= STAT_TEMP_FLT;
    }
#endif
    if (giFlag_SsFlt == TRUE)
    {
        INT_FLTSUB_STATE |= STAT_SoftStart_FLT;
    }

    if ((INT_FLTSUB_STATE != 0x0000))
    {
        INT_FLT_STATE = STAT_PFC_FLT;
    }

    INT_SUB_STATE = INT_FLT_STATE;
    return INT_SUB_STATE;
}


Uint16 ChkFltSubState()
{
    return INT_FLTSUB_STATE;
}


Uint16 ChkInhibitState()
{
    INT_INHIBIT_STATE = 0x00;

    //  if( giInhibit != FALSE )
#ifdef SIMUL
#else
    if (giFlag_Run == FALSE)
    {
        INT_INHIBIT_STATE |= STAT_INHIBIT;
    }

#endif

//    if (giTEST_Mode == FALSE)
//    {
        if (gfVgrid_RMS < gfVgridUVInhibit)
        {
            giVgridUVInhibitFlag = TRUE;
        }
        else
        {
            giVgridUVInhibitFlag = FALSE;
        }

        if (giVgridUVInhibitFlag == TRUE)
        {
            INT_INHIBIT_STATE |= STAT_VIN_UV;
        }

#if 0
            if (gfVo[i] < gfVoPFCUVInhibit)
            {
                INT_INHIBIT_STATE |= STAT_VOUT_UV;
                break;
            }
#endif
//    }

    if (giADCoffsetCplFlag == FALSE)
    {
        INT_INHIBIT_STATE |= STAT_ADC_OFFSET_CHEKK;
    }

    if (giADCStableFlag == FALSE)
    {
        INT_INHIBIT_STATE |= STAT_ADC_STABILITY_CHECK;
    }

    if (giFlag_PartCalcCpl == FALSE)
    {
        INT_INHIBIT_STATE |= STAT_GRIDPLL_CHECK;
    }

    INT_SUB_STATE = INT_INHIBIT_STATE;
    return INT_SUB_STATE;
}


void ChkNormalState()
{
    INT_NORMAL_STATE = 0x00;

    if (giFlag_PrecharState == TRUE)
    {
        INT_NORMAL_STATE |= STAT_PRECHARGE;
    }

    if (giFlag_PFCRlyState == ON)
    {
        INT_NORMAL_STATE |= STAT_PFCRLY;
    }

    if (giFlag_PFCRlyCpl == ON)
    {
        INT_NORMAL_STATE |= STAT_PFCRLYON;
    }

    if (giFlag_SsState == TRUE)
    {
        INT_NORMAL_STATE |= STAT_PFCSOFTSTART;
    }

    if (giFlag_NormalState == TRUE)
    {
        INT_NORMAL_STATE |= STAT_PFCNORMAL;
    }

    INT_SUB_STATE = INT_NORMAL_STATE;
}

Uint16 ChkRlyState()
{
    return 0;
}

