/*
 * StructDefine.h
 *
 *  Created on: 2021. 4. 16.
 *      Author: poweryhs
 */

#include "Define.h"

#ifndef STRUCTDEFINE_H
#define STRUCTDEFINE_H


 /*-----------------------------------------------------------------------------
 Define the structure of the 3-phase variable
 -----------------------------------------------------------------------------*/
typedef struct {
    float  u;
    float  v;
    float  w;

}uvw;
#define uvw_defaults {0.,0.,0.}

/*-----------------------------------------------------------------------------
Define the structure of the Line to Line variable
-----------------------------------------------------------------------------*/
typedef struct {
    float uv;
    float vw;
    float wu;
}uvw_LL;

#define uvw_LL_defaults     {0.,0.,0.}

/*-----------------------------------------------------------------------------
Define the structure of the d-q variable
-----------------------------------------------------------------------------*/
//int와 같이 dq가 구조체를 선언
typedef struct {
    float  d;
    float  q;
}dq;

#define dq_defaults {0.,0.}


/*-----------------------------------------------------------------------------
Define the structure of the 1-order filter
-----------------------------------------------------------------------------*/
typedef struct{float input;
                float input_old1;
                float output;
                float output_old1;
            }filter1;

#define filter1_defaults {0.,0.,0.,0.}

/*-----------------------------------------------------------------------------
Define the structure of the 2-order filter
-----------------------------------------------------------------------------*/
typedef struct{float input;
                float input_old1;
                float input_old2;
                float output;
                float output_old1;
                float output_old2;
            }filter2;

#define filter2_defaults {0.,0.,0.,0.,0.,0.}

/*-----------------------------------------------------------------------------
Define the structure of the PI controller
-----------------------------------------------------------------------------*/
typedef struct { float  Ref;                // Input : Reference input
            float  Fdb;                 // Input : Feedback input
            float  Integ;
            float  Kp;                      // Parameter: Proportional gain
            float  Ki;                      // Parameter: Integral gain
            float  Ka;                      // Parameter: Anti-windup gain
            Uint16  Alpha;                  // Parameter: IP-PI control ratio
            float  Tsamp;                   // Parameter: Sampling time
            float  Err;                     // Variable: Error
            float  FF;                      // Variable: Feedforward term
            float  Fb;                      // Variable: Feedback term
            float  OutMax;                  // Variable: Output limit max
            float  OutMin;                  // Variable: Output limit min
            float  outtemp;
            float  out;                 // Variable: PI control out
                 }PI_con;

#define PI_con_defaults { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

/*-----------------------------------------------------------------------------
Define the structure of the PID controller
-----------------------------------------------------------------------------*/

typedef struct { float  Ref;                // Input : Reference input
        float  Fdb;                 // Input : Feedback input
        float  Integ;
        float  Diff;
        float  Kp;                      // Parameter: Proportional gain
        float  Ki;                      // Parameter: Integral gain
        float  Kd;                      // Parameter: DifferentagfiL gain
        float  Ka;                      // Parameter: Anti-windup gain
        Uint16  Alpha;                  // Parameter: IP-PI control ratio
        float  Tsamp;                   // Parameter: Sampling time
        float  Err;                     // Variable: Error
        float  Err1;                    // Variable: Error
        float  FF;                      // Variable: Feedforward term
        float  Fb;                      // Variable: Feedback term
        float  OutMax;                  // Variable: Output limit max
        float  OutMin;                  // Variable: Output limit min
        float  outtemp;
        float  out;                 // Variable: PI control out
         }PID_con;

#define PID_con_defaults { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}


/*-----------------------------------------------------------------------------
Define the structure of the DPID controller
-----------------------------------------------------------------------------*/

typedef struct {
        float  Ref;                     // Input : Reference input
        float  Fdb;                     // Input : Feedback input
        float  Kp;                      // Parameter: Proportional gain
        float  Zero1;                   // Parameter: Zero1
        float  Zero2;                   // Parameter: Zero2
        float  Pole;                    // Parameter: Pole1
        float  Tsamp;                   // Parameter: Sampling time
        float  Err;                     // Variable: Error
        float  Err1;                    // Variable: Error
        float  Err2;                    // Variable: Error
        float  FF;                      // Variable: Feedforward term
        float  OutMax;                  // Variable: Output limit max
        float  OutMin;                  // Variable: Output limit min
        float  outtemp;
        float  outtemp1;
        float  outtemp2;
        float  out;                 // Variable: PI control out
        }DPID_con;

#define DPID_con_defaults { 0.,}



/*-----------------------------------------------------------------------------
Define the structure of the PIR controller
-----------------------------------------------------------------------------*/
typedef struct { float  Ref;                // Input : Reference input
            float  Fdb;                 // Input : Feedback input
            float  Integ;
            float  Kp;                      // Parameter: Proportional gain
            float  Ki;                      // Parameter: Integral gain
            float   Res;                    // Parameter: Resonant filter
            float  Ka;                      // Parameter: Anti-windup gain
            Uint16  Alpha;                  // Parameter: IP-PI control ratio
            float  Tsamp;                   // Parameter: Sampling time
            float  Err;                 // Variable: Error
            float  FF;                      // Variable: Feedforward term
            float  Fb;                      // Variable: Feedback term
            float  OutMax;                  // Variable: Output limit max
            float  OutMin;                  // Variable: Output limit min
            float  outtemp;
            float  out;                 // Variable: PI control out
            filter2 Resfilter;
                 }PIR_con;

#define PIR_con_defaults { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,filter2_defaults}


/*-----------------------------------------------------------------------------
Define the structure of the 2P1Z controller Trapezoidal
-----------------------------------------------------------------------------*/

typedef struct {
        float  Ref;                     // Input : Reference input
        float  Fdb;                     // Input : Feedback input
        float  Kp;                      // Parameter: Proportional gain
        float  Wp;                      // Parameter: Pole1
        float  Wz;                      // Parameter: Zero1
        float  Ka;                      // Parameter: Anti-windup gain
        float  Tsamp;                   // Parameter: Sampling time
        float  Err;                     // Variable: Error
        float  Err1;                    // Variable: Error
        float  Err2;                    // Variable: Error
        float  FF;                      // Variable: Feedforward term
        float  Fb;                      // Variable: Feedback term
        float  OutMax;                  // Variable: Output limit max
        float  OutMin;                  // Variable: Output limit min
        float  outtemp;
        float  outtemp1;
        float  outtemp2;
        float  out;                 // Variable: PI control out
        }TPOZ_con;

#define TPOZ_con_defaults { 0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.}

/*-----------------------------------------------------------------------------
Define the structure of the 3P2Z controller Trapezoidal
-----------------------------------------------------------------------------*/

typedef struct {
        float  Ref;                 // Input : Reference input
        float  Fdb;                 // Input : Feedback input
        float  Kp;                  // Parameter: Proportional gain
        float  Wp1;                 // Parameter: Pole1
        float  Wz1;                 // Parameter: Zero1
        float  Wp2;                 // Parameter: Pole2
        float  Wz2;                 // Parameter: Zero2
        float  Ka;                  // Parameter: Anti-windup gain
        float  Tsamp;               // Parameter: Sampling time
        float  Err;                 // Variable: Error
        float  Err1;                // Variable: Error
        float  Err2;                // Variable: Error
        float  Err3;                // Variable: Error
        float  FF;                  // Variable: Feedforward term
        float  Fb;                  // Variable: Feedback term
        float  OutMax;              // Variable: Output limit max
        float  OutMin;              // Variable: Output limit min
        float  outtemp;
        float  outtemp1;
        float  outtemp2;
        float  outtemp3;
        float  out;                 // Variable: PI control out
         }TPTZ_con;

#define TPTZ_con_defaults { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

#endif





