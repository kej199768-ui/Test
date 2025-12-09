/*
 * Task_Control.c
 *
 *  Created on: 2021. 12. 22.
 *      Author: IPCL
 */
#include "define.h"
#include "StructDefine.h"
#include "Parameter.h"
#include "Func.h"
#include "Sequence.h"
#include "ADC.h"
#include "Task_Control.h"
#include <math.h>

/******************************************************************************
 Precharge variable
 *****************************************************************************/
Uint16 giFlag_PrecharCpl;
Uint16 giFlag_PrecharFlt;
Uint16 giFlag_PrecharState;
Uint32 giPrecharCplCnt;
Uint32 giPrecharFltCnt;
#ifdef SIMUL
Uint32 giPrecharCplCntCal = 500;
Uint32 giPrecharFltCntCal = 500;
float gfPrecharCplTimeCal = 0.05;
float gfPrecharFltTimeCal = 0.05;
#else
Uint32 giPrecharCplCntCal = 5000;
Uint32 giPrecharFltCntCal = 5000;
float gfPrecharCplTimeCal = 0.5;
float gfPrecharFltTimeCal = 0.5;
#endif

/******************************************************************************
 * Precharge_100us function
 *****************************************************************************/
Uint16 giFlag_PFCRlyCpl;
Uint16 giFlag_PFCRlyState;
Uint16 giFlag_PFCRlyONGate;
Uint32 giPFCRlyCplCnt;
#ifdef SIMUL
Uint32 giPFCRlyCplCntCal = 500;
float gfPFCRlyCplTimeCal = 0.05;
#else
Uint32 giPFCRlyCplCntCal = 5000;
float gfPFCRlyCplTimeCal = 0.5;

#endif

/******************************************************************************
 * GridPartCalc_100us function
 *****************************************************************************/
dq gdqVgrid_dqs = dq_defaults;
filter2 gf2Vgrid_qs_APF = filter2_defaults;
dq gdqVgrid_dqe = dq_defaults;
dq gdqVgrid_dqe_LPF = dq_defaults;
filter2 gf2Vgrid_de_LPF = filter2_defaults;
filter2 gf2Vgrid_qe_LPF = filter2_defaults;

PI_con gPiVgrid_angle = PI_con_defaults;
#ifdef SIMUL
float gfWgrid = 377.;
float gfWgrid_LPF = 377.;
filter1 gf1Wgrid_LPF = filter1_defaults;
float gfTheta_Grid;
float gfVgrid_Mag = PI2 * 220.;
#else
float gfWgrid;
float gfWgrid_LPF;
filter1 gf1Wgrid_LPF = filter1_defaults;
float gfTheta_Grid;
float gfTheta_Grid_Comp;
float gfVgrid_Mag;
#endif

Uint16 giPartCalcCplCnt;
Uint16 giFlag_PartCalcCpl;
#ifdef SIMUL
Uint32 giPartCalcCplCntCal = 500;
#else
Uint32 giPartCalcCplCntCal = 5000;
#endif

float gfWgrid_PC;
float gfGridAngleKp;
float gfGridAngleKi;


 /******************************************************************************
 * SS variable
 *****************************************************************************/
float gfVoPFCrefSS;

Uint32 giSsCplCnt;
Uint16 giFlag_SsFlt;
Uint32 giSsFltCnt;
Uint16 giFlag_SsState;


float gfdelVoPFCrefCal;
float gfVoPFCrefCal = 400;

float  gfSsCplTimeCal = 0.5;
float  gfSsFltTimeCal = 0.5;
Uint32 giSsCplCntCal = 5000;
Uint32 giSsFltCntCal = 5000;

float  gfTssCal = 1;
float  gfFssCal = 2;      // 1/gfTssCal

float gfVotref;
float gfVotrefLPF;
filter1 gf1Votref_LPF = filter1_defaults;
float gfVotrefSS;
float gfdelVotref;

Uint16 giFlag_SsCpl;
Uint16 giFlag_NormalState;



/******************************************************************************
 * Precharge_100us function
 *****************************************************************************/
void Precharging_100us()
{
    float Tsamp_Prechar = Ts10k;

    if ((INT_MAIN_STATE == STAT_NORMAL_STATE) && (giFlag_PrecharCpl == FALSE))
    {
        giFlag_PrecharState = TRUE;
        if (gfVoPFC > 0.8 * SQRT2 * gfVgrid_RMS)
        {
            giPrecharCplCnt++;
            giPrecharFltCnt = 0;
        }
        else
        {
            giPrecharCplCnt = 0;
            giPrecharFltCnt++;
        }

        if (giPrecharCplCnt > giPrecharCplCntCal)
        {
            giPrecharCplCnt = 0;
            giFlag_PrecharCpl = TRUE;
            giFlag_PrecharState = FALSE;
        }

        if (giPrecharFltCnt > giPrecharFltCntCal)
        {
            giPrecharFltCnt = 0;
            if (giTEST_Mode == TRUE)
            {
                giFlag_PrecharFlt = FALSE;
            }
            else
            {
                giFlag_PrecharFlt = TRUE;
            }
        }
    }
    else if ((INT_MAIN_STATE == STAT_NORMAL_STATE) && (giFlag_PrecharCpl == TRUE))
    {
    }
    else
    {
        giSsCplCntCal = (Uint32)(gfPrecharCplTimeCal / Tsamp_Prechar);
        giSsFltCntCal = (Uint32)(gfPrecharFltTimeCal / Tsamp_Prechar);
        giFlag_NormalState = FALSE;
        giFlag_PrecharState = FALSE;
        giFlag_PrecharCpl = FALSE;
        giPrecharCplCnt = 0;
        giPrecharFltCnt = 0;
    }
}

/******************************************************************************
 * Precharge_100us function
 *****************************************************************************/
void PFCRly_100us()
{
    float Tsamp_PFCRly = Ts10k;

    if ((INT_MAIN_STATE == STAT_NORMAL_STATE)
            && (giFlag_PrecharCpl == TRUE)
            && (giFlag_PFCRlyCpl == FALSE)
            )
    {
        giFlag_PFCRlyState = TRUE;
        giFlag_PFCRlyONGate = HIGH;
        GpioDataRegs.GPASET.bit.GPIO6  = HIGH;
        giPFCRlyCplCnt++;

        if (giPFCRlyCplCnt > giPFCRlyCplCntCal)
        {
            giPFCRlyCplCnt = 0;
            giFlag_PFCRlyCpl = TRUE;
            giFlag_PFCRlyState = FALSE;
        }
    }
    else  if ((INT_MAIN_STATE == STAT_NORMAL_STATE)
            && (giFlag_PrecharCpl == TRUE)
            && (giFlag_PFCRlyCpl == TRUE)
            )
    {
        giPFCRlyCplCnt = 0;
        giFlag_PFCRlyCpl = TRUE;
        giFlag_PFCRlyState = FALSE;
        giFlag_PFCRlyONGate = HIGH;
        GpioDataRegs.GPASET.bit.GPIO6  = HIGH;
    }
    else
    {
        giPFCRlyCplCntCal = (Uint32)(gfPFCRlyCplTimeCal / Tsamp_PFCRly);
        giFlag_NormalState = FALSE;
        giFlag_PFCRlyState = FALSE;
        giFlag_PFCRlyCpl = FALSE;
        giFlag_PFCRlyONGate = LOW;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = HIGH;
        giPFCRlyCplCnt = 0;
    }
}

/******************************************************************************
 * GridPartCalc_100us function
 *****************************************************************************/
void GridPartCalc_100us()
{
    float Tsamp_gridpartcalc = Ts10k;       //100us task = 10kHz 동작
    float gffgrid_LPF;                      //계통 주파수 측정한 값 넣을 변수

    //Grid voltage All pass filter
    gffgrid_LPF = gfWgrid_LPF * 0.1591549430919;    //계통 주파수 구하는 수식인데
//        gffgrid_LPF = 60;
    if (gffgrid_LPF > 72) gffgrid_LPF = 72;         //초기 or 비정상 동작을 위한 limiter
    else if (gffgrid_LPF < 40) gffgrid_LPF = 40;    //40~72로 제한

    //  gdqVgrid_dqs.q = gfVgrid;
    gdqVgrid_dqs.q = gfVgrid;                       //실제 라인은 q축으로 사용. d축은 APS 통해 가공하며 위상이 실제 라인 q축보다 90도 앞선다.
    gdqVgrid_dqs.d = APF2(Tsamp_gridpartcalc, gffgrid_LPF, gdqVgrid_dqs.q, &gf2Vgrid_qs_APF); // APF2(double Tsamp, double fc, double in, filter2 *out)
//    gfVgrid_Mag = sqrt(pow(gdqVgrid_dqs.d, 2) + pow(gdqVgrid_dqs.q, 2));
    gfVgrid_Mag = gfVgrid_RMS * SQRT2;              //RMS 값을 사용하여 라인 전압 크기 구하기


    if ((giADCoffsetCplFlag == TRUE)                                    //ADC offset 계산 끝나고
            && (giADCStableFlag == TRUE)                                //ADC 안정상태도 들어오고
//            && ((INT_INHIBIT_STATE & STAT_VIN_UV) != STAT_VIN_UV)
            && (giVgridUVInhibitFlag == FALSE)                          //입력전압이 안정적으로 들어오는 상황이면,
            )
    {

        //고급전력전자공학 p.152~163

        //PI제어기 부분은 p.161 반드시 참고할 것
        gfWgrid_PC = 300.;                                              //PLL control? 48Hz 기준 각속도. 책 wn
        gfGridAngleKp = 2 * 0.707 * gfWgrid_PC / (gfVgrid_Mag);         //
        gfGridAngleKi = gfWgrid_PC * gfWgrid_PC / (gfVgrid_Mag);

        gPiVgrid_angle.Kp = gfGridAngleKp;
        gPiVgrid_angle.Ki = gfGridAngleKi;
        gPiVgrid_angle.Ka = 1.0 / gPiVgrid_angle.Kp;

        //Grid voltage PLL
        gPiVgrid_angle.Ref = 0.;
//        gPiVgrid_angle.Fdb = gdqVgrid_dqe_LPF.d;
        gPiVgrid_angle.Fdb = gdqVgrid_dqe.d;

        PI_Control_calc(&gPiVgrid_angle);

        gfWgrid = gPiVgrid_angle.out + 350.; //377

        gfWgrid_LPF = LPF1(Tsamp_gridpartcalc, 20.0, gfWgrid, &gf1Wgrid_LPF);

        gfTheta_Grid += gfWgrid * Tsamp_gridpartcalc;

        gfTheta_Grid_Comp = gfTheta_Grid + 2* gfWgrid * Tsamp_gridpartcalc;


        if (gfTheta_Grid > PI)  gfTheta_Grid -= PI2;        //PI2 6.283185307???
        if (gfTheta_Grid < -PI)  gfTheta_Grid += PI2;

        gdqVgrid_dqe = park_calc(&gdqVgrid_dqs, gfTheta_Grid);

        gdqVgrid_dqe_LPF.d=LPF2(Tsamp_gridpartcalc, 100. , 0.707, gdqVgrid_dqe.d, &gf2Vgrid_de_LPF);
        gdqVgrid_dqe_LPF.q=LPF2(Tsamp_gridpartcalc, 100. , 0.707, gdqVgrid_dqe.q, &gf2Vgrid_qe_LPF);


        if ((gdqVgrid_dqe_LPF.q >= 0.9 * gfVgrid_Mag) && (gdqVgrid_dqe_LPF.d <= 30) && (giFlag_PartCalcCpl == FALSE))
        {
            giPartCalcCplCnt++;
            if (giPartCalcCplCnt > giPartCalcCplCntCal)
            {
                giFlag_PartCalcCpl = TRUE;
            }
        }
        else if ((gdqVgrid_dqe_LPF.q >= 0.9 * gfVgrid_Mag) && (gdqVgrid_dqe_LPF.d <= 30) && (giFlag_PartCalcCpl == TRUE))
        {
            giFlag_PartCalcCpl = TRUE;
            giPartCalcCplCnt = 0;
        }
        else
        {
            giFlag_PartCalcCpl = FALSE;
            giPartCalcCplCnt = 0;
        }
    }
    else
    {
        GridPartCalcGainInit();
    }
}

void GridPartCalcGainInit()
{
    float Tsamp_gridpartcalc = Ts10k;

    // PFC angle detection
    /*
        if(fabs(Vgrid_dqe_LPF.d) > 50) Wc_GSC_PC=10000.;
        else Wc_GSC_PC =300.;
    */
    gfWgrid = 350.;
    gfWgrid_LPF = 350.;
    gfWgrid_PC = 300.;
    gfGridAngleKp = 2 * 0.707 * gfWgrid_PC / (gfVgrid_Mag);
    gfGridAngleKi = gfWgrid_PC * gfWgrid_PC / (gfVgrid_Mag);

    gPiVgrid_angle.Kp = gfGridAngleKp;
    gPiVgrid_angle.Ki = gfGridAngleKi;
    gPiVgrid_angle.Ka = 1 / gPiVgrid_angle.Kp;
    gPiVgrid_angle.Integ = 0.;
    gPiVgrid_angle.outtemp = 0.;
    //  gPiVgrid_angle.Alpha = 1;
    gPiVgrid_angle.OutMax = 100;        //377 * 1.2;
    gPiVgrid_angle.OutMin = -100;       // -377 * 1.2;
    gPiVgrid_angle.Tsamp = Tsamp_gridpartcalc;
}

/******************************************************************************
 * SoftStart_100us function
 *****************************************************************************/
void SoftStart_100us()
{
    float Tsamp_Ss = Ts10k;

    if ((INT_MAIN_STATE == STAT_NORMAL_STATE) && (giFlag_PFCRlyCpl == TRUE) && (giFlag_SsCpl == FALSE))
    {
        giFlag_SsState = TRUE;
        if (gfVoPFCrefSS < gfVoPFCrefCal - gfdelVoPFCrefCal)
        {
            gfVoPFCrefSS += gfdelVoPFCrefCal;
        }
        else if (gfVoPFCrefSS > gfVoPFCrefCal + gfdelVoPFCrefCal)
        {
            gfVoPFCrefSS -= gfdelVoPFCrefCal;
        }
        else
        {
            gfVoPFCrefSS = gfVoPFCrefCal;

            //            if (gfVzig > 0.95 * gfVoPFCrefCal)
            if (gfVoPFC_LPF100 > 0.9 * gfVoPFCrefCal)
            {
                giSsCplCnt++;
                giSsFltCnt = 0;
            }
            else
            {
                giSsCplCnt = 0;
                giSsFltCnt++;
            }

            if (giSsCplCnt > giSsCplCntCal)
            {
                giSsCplCnt = 0;
                giFlag_SsCpl = 1;
                giFlag_NormalState = TRUE;
                giFlag_SsState = FALSE;
            }

            if (giSsFltCnt > giSsFltCntCal)
            {
                giSsFltCnt = 0;
                if (giTEST_Mode == FALSE)
                {
                    giFlag_SsFlt = 1;
                }
                else
                {
                    giFlag_NormalState = TRUE;
                    giFlag_SsState = FALSE;
                }
            }

        }
    }
    else if ((INT_MAIN_STATE == STAT_NORMAL_STATE) && (giFlag_PFCRlyCpl == TRUE) && (giFlag_SsCpl == TRUE))
    {
        giFlag_NormalState = TRUE;
        giFlag_SsState = FALSE;
        if (gfVoPFCrefSS < gfVoPFCrefCal - gfdelVoPFCrefCal)
        {
            gfVoPFCrefSS += gfdelVoPFCrefCal;
        }
        else if (gfVoPFCrefSS > gfVoPFCrefCal + gfdelVoPFCrefCal)
        {
            gfVoPFCrefSS -= gfdelVoPFCrefCal;
        }
        else
        {
            gfVoPFCrefSS = gfVoPFCrefCal;
        }
    }
    else
    {
        gfdelVoPFCrefCal = gfVoPFCrefCal * Tsamp_Ss / gfTssCal;           //gfVoPFCrefCal * Tsamp_Ss /Tss; //Tss = 50ms;
        giSsCplCntCal = (Uint16)(gfSsCplTimeCal / Tsamp_Ss);
        giSsFltCntCal = (Uint16)(gfSsFltTimeCal / Tsamp_Ss);
        giFlag_NormalState = FALSE;
        giFlag_SsState = FALSE;
        giFlag_SsCpl = FALSE;
        giFlag_SsFlt = FALSE;
        gfVoPFCrefSS = gfVoPFC;
        giSsCplCnt = 0;
        giSsFltCnt = 0;
    }
}






