/*
 * Task_Control.h
 *
 *  Created on: 2021. 12. 22.
 *      Author: IPCL
 */

#include "StructDefine.h"


#ifndef TASK_CONTROL_H_
#define TASK_CONTROL_H_

/******************************************************************************
 Precharge variable
 *****************************************************************************/
extern Uint32 giPrecharCplCnt;
extern Uint16 giFlag_PrecharCpl;
extern Uint16 giFlag_PrecharState;

/******************************************************************************
 * Precharge_100us function
 *****************************************************************************/
extern Uint32 giPFCRlyCplCnt;
extern Uint16 giFlag_PFCRlyCpl;
extern Uint16 giFlag_PFCRlyState;
extern Uint16 giFlag_PFCRlyONGate;

/******************************************************************************
 * GridPartCalc_100us function
 *****************************************************************************/
extern dq gdqVgrid_dqs;
extern filter2 gf2Vgrid_qs_APF;
extern dq gdqVgrid_dqe;

extern PI_con gPiVgrid_angle;
extern float gfWgrid;
extern float gfWgrid_LPF;
extern filter1 gf1Wgrid_LPF;
extern float gfTheta_Grid;
extern float gfTheta_Grid_Comp;
extern float gfVgrid_Mag;

extern Uint16 giPartCalcCplCnt;
extern Uint16 giFlag_PartCalcCpl;
extern Uint32 giPartCalcCplCntCal;

extern float gfWgrid_PC;
extern float gfGridAngleKp;
extern float gfGridAngleKi;

/******************************************************************************
 * SS variable
 *****************************************************************************/
extern float gfVoPFCrefCal;

extern Uint16 giFlag_SsFlt;
extern Uint16 giFlag_SsState;
extern Uint16 giFlag_SsCpl;
extern Uint16 giFlag_NormalState;

extern float gfVoPFCrefSS;

/******************************************************************************
 * Control function
 *****************************************************************************/
void Precharging_100us(void);
void PFCRly_100us(void);
void GridPartCalc_100us(void);
void SoftStart_100us(void);

/******************************************************************************
 * Init function
 *****************************************************************************/
void GridPartCalcGainInit(void);


#endif
