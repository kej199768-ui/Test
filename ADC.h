/*
 * ADC.h
 *
 *  Created on: 2020. 11. 16.
 *      Author: poweryhs
 */
#include "StructDefine.h"

#ifndef ADC_H_
#define ADC_H_


 /******************************************************************************
  * ADC ¼¾½Ì º¯¼ö
  *****************************************************************************/
extern float ADCRESULT0;
extern float ADCRESULT1;
extern float ADCRESULT2;
extern float ADCRESULT3;

extern float gfVgrid;
extern float gfVgrid_fabs;
extern float gfVgrid1;
extern float gfVgrid_LPF10;
extern float gfVgrid_LPF100;
extern float gfVgrid_LPF1K;
extern float gfVgrid_Offset;
extern float gfVgrid_Offset1;
extern float gfVgrid_Offset_LPF10;
extern float gfVgrid_Offset_Cal;

extern float gfVgrid_RMS;

extern float gfVoPFC;//// ÃÊ±â ½Ã¹Ä·¹ÀÌ¼Ç ¹®Á¦
extern float gfVoPFC1;
extern float gfVoPFC_LPF10;
extern float gfVoPFC_LPF100;
extern float gfVoPFC_LPF1K;
extern float gfVoPFC_Offset; //// ÃÊ±â ½Ã¹Ä·¹ÀÌ¼Ç ¹®Á¦
extern float gfVoPFC_Offset1;
extern float gfVoPFC_Offset_LPF10;
extern float gfVoPFC_Offset_Cal;

extern float gfiLphaseA;
extern float gfiLphaseA1;
extern float gfiLphaseA_LPF10;
extern float gfiLphaseA_LPF100;
extern float gfiLphaseA_LPF1K;
extern float gfiLphaseA_Offset;
extern float gfiLphaseA_Offset1;
extern float gfiLphaseA_Offset_LPF10;
extern float gfiLphaseA_Offset_Cal;

extern float gfiLphaseB;
extern float gfiLphaseB1;
extern float gfiLphaseB_LPF10;
extern float gfiLphaseB_LPF100;
extern float gfiLphaseB_LPF1K;
extern float gfiLphaseB_Offset;
extern float gfiLphaseB_Offset1;
extern float gfiLphaseB_Offset_LPF10;
extern float gfiLphaseB_Offset_Cal;

/******************************************************************************
 * ADC Offset º¯¼ö  ¹×  ¾ÈÁ¤È­ º¯¼ö
 *****************************************************************************/
extern Uint32 AdcOffset_CalcCnt_Max;
extern Uint16 AdcOffset_CalcCnt;
extern Uint16 giADCoffsetCplFlag;

extern Uint32 AdcStable_Cnt_Max;
extern Uint16 AdcStable_Cnt;
extern Uint16 giADCStableFlag;


/******************************************************************************
 * SPI DAC 변수
 *****************************************************************************/
extern Uint16 giSPIdata[3];
extern Uint16 giSPIdataindex;

extern Uint16 giSPIdatamode;

/******************************************************************************
 * ADC ÇÔ¼ö ¿øÇü ¼±¾ð
 *****************************************************************************/
void ADC_Calc(Uint16 iPhase);
void ADC_LPF_RMS_Calc_100us();
void ADC_Offset_Calc_100us();
void InitFilterVar_100us();
void SPIDAC_100us(void);

#endif
