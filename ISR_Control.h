/*
 * ISR_Control.h
 *
 *  Created on: 2021. 12. 22.
 *      Author: IPCL
 */

#include "StructDefine.h"


#ifndef ISR_CONTROL_H_
#define ISR_CONTROL_H_


/******************************************************************************
 *Half Cycle Detection 변수
 *****************************************************************************/
extern Uint16 giflag_PosCycle;
extern Uint16 giflag_NegCycle;
extern Uint16 giFlag_HSSW_Deadzone;
extern Uint16 giFlag_LSSW_Deadzone;
extern Uint32 giPos_dead_cnt;
extern Uint32 giNeg_dead_cnt;
extern float gfHSSW_VmAL;
extern float gfHSSW_VmAH;
extern float gfHSSW_VmBL;
extern float gfHSSW_VmBH;
extern float gfLSSW_VmL;
extern float gfLSSW_VmH;
extern float Vm_dead;
extern float gfVgrid_CycleStartCal;
extern float gfVgrid_CycleEndCal;

/******************************************************************************
 *Voltage Control ISR 변수
 *****************************************************************************/
extern DPID_con gcVoPFC;
extern float gfIPFCref;
extern float gfIPFCphaseref;

/******************************************************************************
 *Current Control ISR 변수
 *****************************************************************************/
extern DPID_con gcILPFC1;
extern DPID_con gcILPFC2;
extern float gfPFC_CCM_FF;
extern float gfPFC_DCM_FF;
extern float gfPFC_FF;
extern Uint16 giFlag_IL1CtrlCpl;
extern Uint16 giFlag_IL2CtrlCpl;
extern Uint16 giFlag_IL1CtrlCpl_Delay;
extern Uint16 giFlag_IL2CtrlCpl_Delay;
extern Uint16 giFlag_LSSWCpl;

/******************************************************************************
 *ISR 제어 함수
 *****************************************************************************/
void HalfCycleDetection(void);

void VoPFC_Ctrl(void);
void Init_VoPFC_cont(void);

void ILPFC_Ctrl1(void);
void ILPFC_Ctrl2(void);
void Init_ILPFC1_cont(void);
void Init_ILPFC2_cont(void);




#endif
