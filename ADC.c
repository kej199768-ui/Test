/*
 * DPP_Interrupt.c
 * 
 * TEST1
 *
 * TEST!! TEST2
 *
 *  Created on: 2020. 11. 16.
 *      Author: poweryhs
 */
#include "f28x_project.h"
#include "Func.h"
#include "Define.h"
#include "ADC.h"
#include "Sequence.h"
#include "Task_Control.h"
#include "ISR_Control.h"
#include <math.h>


/******************************************************************************
 * ADC 센싱 변수
 *****************************************************************************/
float ADCRESULT0;
float ADCRESULT1;
float ADCRESULT2;
float ADCRESULT3;

float gfVgrid;
float gfVgrid1;
float gfVgrid_LPF10;
float gfVgrid_LPF100;
float gfVgrid_LPF1K;
float gfVgrid_Offset;
float gfVgrid_Offset1;
float gfVgrid_Offset_LPF10;

#ifdef SIMUL
float gfVgrid_Offset_Cal = 2047 * 0.1958485958486;;
#else
float gfVgrid_Offset_Cal;
#endif



#ifdef SIMUL
float gfVgrid_fabs;
float gfVgrid_fabs1;
float gfVgrid_fabs2;
float gfVgrid_fabs_LPF5 = 220.0;
float gfVgrid_fabs_LPF5_1 = 220.0;
float gfVgrid_fabs_LPF5_2 = 220.0;
float gfVgrid_RMS = 220.0;
#else
float gfVgrid_fabs;
float gfVgrid_fabs1;
float gfVgrid_fabs2;
float gfVgrid_fabs_LPF5;
float gfVgrid_fabs_LPF5_1;
float gfVgrid_fabs_LPF5_2;
float gfVgrid_RMS;
#endif

float gfVoPFC;//// 초기 시뮬레이션 문제
float gfVoPFC1;
float gfVoPFC_LPF10;
float gfVoPFC_LPF100;
float gfVoPFC_LPF1K;
float gfVoPFC_Offset; //// 초기 시뮬레이션 문제
float gfVoPFC_Offset1;
float gfVoPFC_Offset_LPF10;
#ifdef SIMUL
float gfVoPFC_Offset_Cal = 0.;
#else
float gfVoPFC_Offset_Cal;
#endif

float gfiLphaseA;
float gfiLphaseA1;
float gfiLphaseA_LPF10;
float gfiLphaseA_LPF100;
float gfiLphaseA_LPF1K;
float gfiLphaseA_Offset;
float gfiLphaseA_Offset1;
float gfiLphaseA_Offset_LPF10;
#ifdef SIMUL
float gfiLphaseA_Offset_Cal = 2047 * 0.01221001221;;
#else
float gfiLphaseA_Offset_Cal;
#endif

float gfiLphaseA_fabs;
float gfiLphaseA_fabs1;
float gfiLphaseA_fabs2;
float gfiLphaseA_fabs_LPF5;
float gfiLphaseA_fabs_LPF5_1;
float gfiLphaseA_fabs_LPF5_2;
float gfiLphaseA_RMS;

float gfiLphaseB;
float gfiLphaseB1;
float gfiLphaseB_LPF10;
float gfiLphaseB_LPF100;
float gfiLphaseB_LPF1K;
float gfiLphaseB_Offset;
float gfiLphaseB_Offset1;
float gfiLphaseB_Offset_LPF10;
#ifdef SIMUL
float gfiLphaseB_Offset_Cal = 2047 * 0.01221001221;;
#else
float gfiLphaseB_Offset_Cal;
#endif

float gfiLphaseB_fabs;
float gfiLphaseB_fabs1;
float gfiLphaseB_fabs2;
float gfiLphaseB_fabs_LPF5;
float gfiLphaseB_fabs_LPF5_1;
float gfiLphaseB_fabs_LPF5_2;
float gfiLphaseB_RMS;
/******************************************************************************
 * Filter 계수
 *****************************************************************************/
float gfTFilterSamp, gfFFilterSamp;
float WcLPF1_1K, WcLPF1_100, WcLPF1_50, WcLPF1_10, WcLPF1_5, WcLPF1_1, WcLPF1_0P1, WcLPF2_5;
float gfLPF1A1K, gfLPF1B1K, gfLPF1C1K;
float gfLPF1A100, gfLPF1B100, gfLPF1C100;
float gfLPF1A50, gfLPF1B50, gfLPF1C50;
float gfLPF1A10, gfLPF1B10, gfLPF1C10;
float gfLPF1A5, gfLPF1B5, gfLPF1C5;
float gfLPF1A1, gfLPF1B1, gfLPF1C1;
float gfLPF1A0P1, gfLPF1B0P1, gfLPF1C0P1;
float gfLPF2A5, gfLPF2B5, gfLPF2C5;


/******************************************************************************
 * ADC Offset 변수  및  안정화 변수
 *****************************************************************************/
Uint32 AdcOffset_CalcCnt_Max = Fs10k;
Uint16 AdcOffset_CalcCnt;
Uint16 giADCoffsetCplFlag;

Uint32 AdcStable_Cnt_Max = Fs10k;
Uint16 AdcStable_Cnt;
Uint16 giADCStableFlag;

float gfT_temp = 0.;



/******************************************************************************
 * SPI DAC 변수
 *****************************************************************************/
Uint16 giSPIdata[3] = {0, 0, 0};
Uint16 giSPIdataindex = 0;
Uint16 giSPIdatamode = 0;



/******************************************************************************
 * ADC 및 스케일보정 함수
 *****************************************************************************/

void ADC_Calc(Uint16 iPhase)
{
    /*
    //Current Sensing
    gfiLphaseA = (AdcaResultRegs.ADCRESULT0 * 0.0007326007326 - gfIin_OFFSET[0]) * 16.666667;
    gfiLphaseB = (AdcbResultRegs.ADCRESULT0 * 0.0007326007326 - gfIin_OFFSET[1]) * 16.666667;

    //Voltage Sensing
    gfVgrid = AdcaResultRegs.ADCRESULT1 * 0.0912087912088; //result/4095*3*249/2
    gfVoPFC = AdcbResultRegs.ADCRESULT1 * 0.0912087912088;
    */

    //Current Sensing
    switch (iPhase) {
        case 1:
            gfiLphaseA = AdcaResultRegs.ADCRESULT0  * 0.012625518 - gfiLphaseA_Offset_Cal;    ///result/4095*3*5/3*10
            gfVgrid = AdcbResultRegs.ADCRESULT0 * 0.1811243929*0.975 - gfVgrid_Offset_Cal; //result/4095*3*2/3*(220*4+2.2)/2.2  0.1958485958486   //220112수정직전 : 0.1911243929

            #if 0
            if (giTEST_Mode == FALSE)
            {
                gfVgrid = AdcbResultRegs.ADCRESULT0 * 0.1911243929 - gfVgrid_Offset_Cal; //result/4095*3*2/3*(220*4+2.2)/2.2  0.1958485958486
            }
            else
            {
                gfVgrid = 220*SQRT2*__sinpuf32(50*gfT_temp);
                gfT_temp += Ts100k;
                if (gfT_temp >= 1.0 ) gfT_temp = 0;
            }
#endif
            break;
        case 2:
            gfiLphaseB = AdcaResultRegs.ADCRESULT1 * 0.012625518 - gfiLphaseB_Offset_Cal;
            if (giTEST_Mode == FALSE)
            {
                gfVoPFC = AdcaResultRegs.ADCRESULT2 * 0.2500397301 - gfVoPFC_Offset_Cal; //result/4095*3*2/3*(390*8+6.2)/6.2  0.2462641301351
            }
            else
            {
                gfVoPFC = 220*SQRT2;
            }
            break;
        default:
            gfiLphaseA = AdcaResultRegs.ADCRESULT0  * 0.012625518 - gfiLphaseA_Offset_Cal;    ///result/4095*3*5/3*10   0.01221001221
            gfiLphaseB = AdcaResultRegs.ADCRESULT1 * 0.012625518 - gfiLphaseB_Offset_Cal;
            gfVgrid = AdcbResultRegs.ADCRESULT0 * 0.1811243929*0.975 - gfVgrid_Offset_Cal; //result/4095*3*2/3*(220*4+2.2)/2.2  0.1958485958486      //220112수정직전 : 0.1911243929
            gfVoPFC = AdcaResultRegs.ADCRESULT2 * 0.2500397301 - gfVoPFC_Offset_Cal; //result/4095*3*2/3*(390*8+6.2)/6.2  0.2462641301351
        break;
    }
    //Voltage Sensing
}

/******************************************************************************
 * LPF 및 RMS 연산 함수
 *****************************************************************************/
void ADC_LPF_RMS_Calc_100us()
{
    //LPF
//    gfiLphaseA_LPF10 = gfLPF1A10 * gfiLphaseA_LPF10 + gfLPF1B10 * gfiLphaseA + gfLPF1C10 * gfiLphaseA1;
//    gfiLphaseB_LPF10 = gfLPF1A10 * gfiLphaseB_LPF10 + gfLPF1B10 * gfiLphaseB + gfLPF1C10 * gfiLphaseB1;
    gfVgrid_LPF10 = gfLPF1A10 * gfVgrid_LPF10 + gfLPF1B10 * gfVgrid + gfLPF1C10 * gfVgrid1;
    gfVoPFC_LPF10 = gfLPF1A10 * gfVoPFC_LPF10 + gfLPF1B10 * gfVoPFC + gfLPF1C10 * gfVoPFC1;

//    gfiLphaseA_LPF100 = gfLPF1A100 * gfiLphaseA_LPF100 + gfLPF1B100 * gfiLphaseA + gfLPF1C100 * gfiLphaseA1;
//    gfiLphaseB_LPF100 = gfLPF1A100 * gfiLphaseB_LPF100 + gfLPF1B100 * gfiLphaseB + gfLPF1C100 * gfiLphaseB1;
    gfVgrid_LPF100 = gfLPF1A100 * gfVgrid_LPF100 + gfLPF1B100 * gfVgrid + gfLPF1C100 * gfVgrid1;
    gfVoPFC_LPF100 = gfLPF1A100 * gfVoPFC_LPF100 + gfLPF1B100 * gfVoPFC + gfLPF1C100 * gfVoPFC1;

    gfiLphaseA_LPF1K = gfLPF1A1K * gfiLphaseA_LPF1K + gfLPF1B1K * gfiLphaseA + gfLPF1C1K * gfiLphaseA1;
    gfiLphaseB_LPF1K = gfLPF1A1K * gfiLphaseB_LPF1K + gfLPF1B1K * gfiLphaseB + gfLPF1C1K * gfiLphaseB1;
    gfVgrid_LPF1K = gfLPF1A1K * gfVgrid_LPF1K + gfLPF1B1K * gfVgrid + gfLPF1C1K * gfVgrid1;
    gfVoPFC_LPF1K = gfLPF1A1K * gfVoPFC_LPF1K + gfLPF1B1K * gfVoPFC + gfLPF1C1K * gfVoPFC1;

    gfiLphaseA1 = gfiLphaseA;
    gfiLphaseB1 = gfiLphaseB;
    gfVgrid1 = gfVgrid;
    gfVoPFC1 = gfVoPFC;

    //RMS
    gfiLphaseA_fabs = fabs(gfiLphaseA);
    gfiLphaseB_fabs = fabs(gfiLphaseB);
    gfVgrid_fabs = fabs(gfVgrid);

    gfiLphaseA_fabs_LPF5 = gfLPF2A5 * gfiLphaseA_fabs_LPF5_1 + gfLPF2B5 * gfiLphaseA_fabs_LPF5_2 \
        + gfLPF2C5 * (gfiLphaseA_fabs + 2 * gfiLphaseA_fabs1 + gfiLphaseA_fabs2);

    gfiLphaseB_fabs_LPF5 = gfLPF2A5 * gfiLphaseB_fabs_LPF5_1 + gfLPF2B5 * gfiLphaseB_fabs_LPF5_2 \
        + gfLPF2C5 * (gfiLphaseB_fabs + 2 * gfiLphaseB_fabs1 + gfiLphaseB_fabs2);

    gfVgrid_fabs_LPF5 = gfLPF2A5 * gfVgrid_fabs_LPF5_1 + gfLPF2B5 * gfVgrid_fabs_LPF5_2 \
        + gfLPF2C5 * (gfVgrid_fabs + 2 * gfVgrid_fabs1 + gfVgrid_fabs2);

    gfiLphaseA_fabs_LPF5_2 = gfiLphaseA_fabs_LPF5_1;
    gfiLphaseB_fabs_LPF5_2 = gfiLphaseB_fabs_LPF5_1;
    gfVgrid_fabs_LPF5_2 = gfVgrid_fabs_LPF5_1;

    gfiLphaseA_fabs_LPF5_1 = gfiLphaseA_fabs_LPF5;
    gfiLphaseB_fabs_LPF5_1 = gfiLphaseB_fabs_LPF5;
    gfVgrid_fabs_LPF5_1 = gfVgrid_fabs_LPF5;

    gfiLphaseA_fabs2 = gfiLphaseA_fabs1;
    gfiLphaseB_fabs2 = gfiLphaseB_fabs1;
    gfVgrid_fabs2 = gfVgrid_fabs1;

    gfiLphaseA_fabs1 = gfiLphaseA_fabs;
    gfiLphaseB_fabs1 = gfiLphaseB_fabs;
    gfVgrid_fabs1 = gfVgrid_fabs;

    gfiLphaseA_RMS = AVGtoRMS * gfiLphaseA_fabs_LPF5;
    gfiLphaseB_RMS = AVGtoRMS * gfiLphaseB_fabs_LPF5;
    gfVgrid_RMS = AVGtoRMS * gfVgrid_fabs_LPF5;

#ifdef SIMUL
    if (giADCStableFlag == FALSE)
    {
        giADCStableFlag = TRUE;
    }
#else
    if ((AdcStable_Cnt < AdcStable_Cnt_Max) && (giADCoffsetCplFlag == TRUE))
    {
        giADCStableFlag = FALSE;
        AdcStable_Cnt++;
    }
    else if ((AdcStable_Cnt >= AdcStable_Cnt_Max) && (giADCoffsetCplFlag == TRUE))
    {
        giADCStableFlag = TRUE;
        AdcStable_Cnt = AdcStable_Cnt_Max;
    }
    else
    {
        giADCStableFlag = FALSE;
        AdcStable_Cnt = 0;
    }
#endif

}


/******************************************************************************
 * ADC offset 연산 함수
 *****************************************************************************/
void ADC_Offset_Calc_100us()
{
#ifdef SIMUL
    if (giADCoffsetCplFlag == FALSE)
    {
        giADCoffsetCplFlag = TRUE;
        gfiLphaseA_Offset_Cal = 2047 * 0.01221001221;
        gfiLphaseB_Offset_Cal = 2047 * 0.01221001221;
        gfVgrid_Offset_Cal = 2047 * 0.1958485958486;
    }

#else
    if (AdcOffset_CalcCnt < AdcOffset_CalcCnt_Max)
    {
        giADCoffsetCplFlag = FALSE;

        gfiLphaseA_Offset = AdcaResultRegs.ADCRESULT0  * 0.012625518;    ///result/4095*3*5/3*10  =  0.01221001221
        gfiLphaseB_Offset = AdcaResultRegs.ADCRESULT1 * 0.012625518;
        gfVgrid_Offset = AdcbResultRegs.ADCRESULT0 * 0.1811243929*0.975; //result/4095*3*2/3*(220*4+2.2)/2.2  =  0.1958485958486     //220112수정직전 : 0.1911243929
//        gfVoPFC_Offset = AdcaResultRegs.ADCRESULT2 * 0.2500397301; //result/4095*3*2/3*(390*8+6.2)/6.2  =  0.2462641301351

        gfiLphaseA_Offset_LPF10 = gfLPF1A10 * gfiLphaseA_Offset_LPF10   + gfLPF1B10 * gfiLphaseA_Offset + gfLPF1C10 * gfiLphaseA_Offset1;
        gfiLphaseB_Offset_LPF10 = gfLPF1A10 * gfiLphaseB_Offset_LPF10   + gfLPF1B10 * gfiLphaseB_Offset + gfLPF1C10 * gfiLphaseB_Offset1;
        gfVgrid_Offset_LPF10    = gfLPF1A10 * gfVgrid_Offset_LPF10      + gfLPF1B10 * gfVgrid_Offset    + gfLPF1C10 * gfVgrid_Offset1;
        gfVoPFC_Offset_LPF10    = gfLPF1A10 * gfVoPFC_Offset_LPF10      + gfLPF1B10 * gfVoPFC_Offset    + gfLPF1C10 * gfVoPFC_Offset1;

        gfiLphaseA_Offset1 = gfiLphaseA_Offset;
        gfiLphaseB_Offset1 = gfiLphaseB_Offset;
        gfVgrid_Offset1 = gfVgrid_Offset;
        gfVoPFC_Offset1 = gfVoPFC_Offset;

    }
    else if (AdcOffset_CalcCnt == AdcOffset_CalcCnt_Max)
    {
        giADCoffsetCplFlag = FALSE;
        gfiLphaseA_Offset_Cal = gfiLphaseA_Offset_LPF10;
        gfiLphaseB_Offset_Cal = gfiLphaseB_Offset_LPF10;
        gfVgrid_Offset_Cal = gfVgrid_Offset_LPF10;
 //       gfVoPFC_Offset_Cal = gfVoPFC_Offset_LPF10;
    }
    else
    {
        AdcOffset_CalcCnt = AdcOffset_CalcCnt_Max + 1;
        giADCoffsetCplFlag = TRUE;
    }
    AdcOffset_CalcCnt++;
#endif
}


/******************************************************************************
 * LPF 및 제어기 계수 연산
 *****************************************************************************/

void InitFilterVar_100us()
{
    float zeta = 0.707;

    gfFFilterSamp = Fs10k;
    gfTFilterSamp = Ts10k;

    WcLPF1_1K = PI2 * 1000.;
    WcLPF1_100 = PI2 * 100.;
    WcLPF1_50 = PI2 * 50.;
    WcLPF1_10 = PI2 * 10.;
    WcLPF1_5 = PI2 * 5.;
    WcLPF1_1 = PI2 * 1.;
    WcLPF1_0P1 = PI2 * 0.1;
    WcLPF2_5 = PI2 * 5.;

    gfLPF1A1K = (2.0 - gfTFilterSamp * WcLPF1_1K) / (2.0 + gfTFilterSamp * WcLPF1_1K);
    gfLPF1B1K = gfTFilterSamp * WcLPF1_1K / (2.0 + gfTFilterSamp * WcLPF1_1K);
    gfLPF1C1K = gfLPF1B1K;

    gfLPF1A100 = (2.0 - gfTFilterSamp * WcLPF1_100) / (2.0 + gfTFilterSamp * WcLPF1_100);
    gfLPF1B100 = gfTFilterSamp * WcLPF1_100 / (2.0 + gfTFilterSamp * WcLPF1_100);
    gfLPF1C100 = gfLPF1B100;

    gfLPF1A50 = (2.0 - gfTFilterSamp * WcLPF1_50) / (2.0 + gfTFilterSamp * WcLPF1_50);
    gfLPF1B50 = gfTFilterSamp * WcLPF1_50 / (2.0 + gfTFilterSamp * WcLPF1_50);
    gfLPF1C50 = gfLPF1B50;

    gfLPF1A10 = (2.0 - gfTFilterSamp * WcLPF1_10) / (2.0 + gfTFilterSamp * WcLPF1_10);
    gfLPF1B10 = gfTFilterSamp * WcLPF1_10 / (2.0 + gfTFilterSamp * WcLPF1_10);
    gfLPF1C10 = gfLPF1B10;

    gfLPF1A5 = (2.0 - gfTFilterSamp * WcLPF1_5) / (2.0 + gfTFilterSamp * WcLPF1_5);
    gfLPF1B5 = gfTFilterSamp * WcLPF1_5 / (2.0 + gfTFilterSamp * WcLPF1_5);
    gfLPF1C5 = gfLPF1B5;

    gfLPF1A1 = (2.0 - gfTFilterSamp * WcLPF1_1) / (2.0 + gfTFilterSamp * WcLPF1_1);
    gfLPF1B1 = gfTFilterSamp * WcLPF1_1 / (2.0 + gfTFilterSamp * WcLPF1_1);
    gfLPF1C1 = gfLPF1B1;

    gfLPF1A0P1 = (2.0 - gfTFilterSamp * WcLPF1_0P1) / (2.0 + gfTFilterSamp * WcLPF1_0P1);
    gfLPF1B0P1 = gfTFilterSamp * WcLPF1_0P1 / (2.0 + gfTFilterSamp * WcLPF1_0P1);
    gfLPF1C0P1 = gfLPF1B0P1;

    gfLPF2A5 = (8 - 2 * WcLPF2_5 * WcLPF2_5 * gfTFilterSamp * gfTFilterSamp )  // \ 코드 줄바꿈
        / (4 + 4 * zeta * WcLPF2_5 * gfTFilterSamp + WcLPF2_5 * WcLPF2_5 * gfTFilterSamp * gfTFilterSamp);
    gfLPF2B5 = (-4 + 4 * zeta * WcLPF2_5 * gfTFilterSamp - WcLPF2_5 * WcLPF2_5 * gfTFilterSamp * gfTFilterSamp) \
        / (4 + 4 * zeta * WcLPF2_5 * gfTFilterSamp + WcLPF2_5 * WcLPF2_5 * gfTFilterSamp * gfTFilterSamp);
    gfLPF2C5 = ( WcLPF2_5 * WcLPF2_5 * gfTFilterSamp * gfTFilterSamp) \
        / (4 + 4 * zeta * WcLPF2_5 * gfTFilterSamp + WcLPF2_5 * WcLPF2_5 * gfTFilterSamp * gfTFilterSamp);

}


/******************************************************************************
 * 최종 센싱 값 SPI DAC로 출력보내기
 *****************************************************************************/
void SPIDAC_100us(void)
{
    //1. adc 최종값을 DAC 레지스터 12bit로 변환
    //2. SPI DAC로 출력 보내기

    //DAC 소자에 총 16bit를 전송해야 하며
    //선행 4bit는 DAC소자의 출력 채널과 소자 기능을 설정하는 bit이고
    //후행 12bit는 ADC센싱 값이다.

    if (giSPIdatamode == 0)
    {
        giSPIdata[0] = 0x8000+((int)(fabs(gfVgrid)*4.09)+2048);         //Vgrid.      DAC 소자 a채널 출력(0x8000)
        giSPIdata[1] = 0x9000+((int)(gfiLphaseA*81.8)+2048);      //iLphaseA.   DAC 소자 b채널 출력(0x9000)
        giSPIdata[2] = 0xA000+((int)(gfIPFCphaseref*81.8)+2048);      //iLphaseB.   DAC 소자 c채널 출력(0xA000)
    }
    else if (giSPIdatamode == 1)
    {
        //원하는거 작성하기
        giSPIdata[0] = 0x8000+((int)(gfTheta_Grid*207.716)+2048); //Theta_grid. DAC 소자 a채널 출력(0x8000)//각도로 바꾸자
        giSPIdata[1] = 0x9000+((int)(gdqVgrid_dqe.d*4.09)+2048);  //d축 전압.      DAC 소자 b채널 출력(0x9000)
        giSPIdata[2] = 0xA000+((int)(gdqVgrid_dqe.q*4.09)+2048);  //q축 전압.      DAC 소자 c채널 출력(0xA000)
    }
    else if (giSPIdatamode == 2)
    {
        giSPIdata[0] = 0x8000+((int)(gcILPFC1.Err*81.8)+2048);      //A상 전류제어기 오차.  DAC 소자 a채널 출력(0x8000)
        giSPIdata[1] = 0x9000+((int)(gcILPFC1.FF*819));             //A상 Feedfoward.  DAC 소자 b채널 출력(0x9000)
        giSPIdata[2] = 0xA000+((int)(gcILPFC1.out*819));            //A상 Duty output. DAC 소자 c채널 출력(0xA000)
    }
    else if (giSPIdatamode == 3)
    {
        giSPIdata[0] = 0x8000+((int)(gcILPFC2.Err*81.8)+2048);      //B상 전류제어기 오차.  DAC 소자 a채널 출력(0x8000)
        giSPIdata[1] = 0x9000+((int)(gcILPFC2.FF*819));             //B상 Feedfoward.  DAC 소자 b채널 출력(0x9000)
        giSPIdata[2] = 0xA000+((int)(gcILPFC2.out*819));            //B상 Duty output. DAC 소자 c채널 출력(0xA000)
    }
    else if (giSPIdatamode == 4)
    {
        giSPIdata[0] = 0x8000+((int)(gcILPFC1.Fdb*81.8)+2048);      //B상 전류제어기 오차.  DAC 소자 a채널 출력(0x8000)
        giSPIdata[1] = 0x9000+((int)(gcILPFC1.outtemp*819));             //B상 Feedfoward.  DAC 소자 b채널 출력(0x9000)
        giSPIdata[2] = 0xA000+((int)(gcILPFC1.out*819));            //B상 Duty output. DAC 소자 c채널 출력(0xA000)
    }
    else if (giSPIdatamode == 5)
    {
        giSPIdata[0] = 0x8000+((int)(gcILPFC1.Err*81.8)+2048);      //B상 전류제어기 오차.  DAC 소자 a채널 출력(0x8000)
        giSPIdata[1] = 0x9000+((int)(gcILPFC1.FF*819));             //B상 Feedfoward.  DAC 소자 b채널 출력(0x9000)
        giSPIdata[2] = 0xA000+((int)(gcILPFC1.out*819));            //B상 Duty output. DAC 소자 c채널 출력(0xA000)
    }
    else if (giSPIdatamode == 6)
    {
        giSPIdata[0] = 0x8000+((int)(gfVoPFC*8.19));         //출력전압 센싱값.      DAC 소자 a채널 출력(0x8000) /400*4095/5*4
        giSPIdata[1] = 0x9000+((int)(gfVoPFC_LPF100*8.19));  //출력전압의 1st 100Hz LPF값 .   DAC 소자 b채널 출력(0x9000)
        giSPIdata[2] = 0xA000+((int)(gcILPFC1.FF*4095));     //전향보상 듀티.   DAC 소자 c채널 출력(0xA000)
    }
    else if (giSPIdatamode == 7)
    {
        giSPIdata[0] = 0x8000+((int)(gfVgrid*4.09)+2048);         //출력전압 센싱값.      DAC 소자 a채널 출력(0x8000) /400*4095/5*4
        giSPIdata[1] = 0x9000+((int)(gfVgrid_LPF100*4.09)+2048);  //출력전압의 1st 100Hz LPF값 .   DAC 소자 b채널 출력(0x9000)
        giSPIdata[2] = 0xA000+((int)(gfVgrid_CycleEndCal*4.09)+2048);     //전향보상 듀티.   DAC 소자 c채널 출력(0xA000)
//        giSPIdata[2] = 0xA000+((int)(giflag_PosCycle*2048));
    }

    else
    {
        giSPIdata[0] = 0x0000;
        giSPIdata[1] = 0x0000;
        giSPIdata[2] = 0x0000;
    }

    for (giSPIdataindex=0;giSPIdataindex<3;giSPIdataindex++)
    {
        SpiaRegs.SPITXBUF = giSPIdata[giSPIdataindex];
        GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;
        DELAY_US(1.5);                                   //1.5us 대기. 데이터를 제어보드 DAC 소자에 보내는데에 필요한 시간동안 잠시 기다린다(최소 요구시간 : 약 1.28us).
        GpioDataRegs.GPBSET.bit.GPIO57 = 1;
    }



}


