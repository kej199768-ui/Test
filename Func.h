/*
 * Func.h
 *
 *  Created on: 2021. 4. 16.
 *      Author: poweryhs
 */
#include "StructDefine.h"

#ifndef FUNC_H_
#define FUNC_H_

 //reference frame
extern uvw L2LtoPhase(uvw_LL* in);
extern dq park_calc(dq* in, double angle);
extern dq ipark_calc(dq* in, double angle);
extern dq clacke_calc(uvw* in);
extern uvw iclacke_calc(dq* in);
extern uvw SVPWM_calc(uvw* in);
extern uvw Positive_Seq(uvw* in, uvw* in_APF);
extern uvw Negative_Seq(uvw* in, uvw* in_APF);
extern uvw Zero_Seq(uvw* in, uvw* in_APF);

//PI control
extern void PI_Control_calc(PI_con *in);
extern void PID_Control_calc(PID_con *in);
extern void DPID_Control_calc(DPID_con *in);
extern void TPOZ_Control_calc(TPOZ_con *in);
extern void TPTZ_Control_calc(TPTZ_con *in);
extern void PIR_Control_calc(PIR_con *in, float Wres);


// 1-order digital filter
extern float LPF1(float Tsamp, float fc, float in, filter1 *out);
// 2-order digital filter
extern float LPF2(float Tsamp, float fc, float zeta, float in, filter2 *out);
extern float HPF2(float Tsamp, float fc, float zeta, float in, filter2 *out);
extern float BPF2(float Tsamp, float fc, float Band, float in, filter2 *out);
extern float BSF2(float Tsamp, float fc, float Band, float in, filter2 *out);
extern float SBPF2(float Tsamp, float fc, float zeta, float in, filter2 *out);
extern float APF2(float Tsamp, float fc,  float in, filter2 *out);
extern float RES(float Tsamp, float Ws, float Kr, float h, float in, filter2 *out);



/*------------------------------------------------------------------------------
Prototypes for the functions in Main sequence program
------------------------------------------------------------------------------*/
extern void ParameterSetting();

#endif
