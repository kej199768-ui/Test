/*
 * DPP_Define.h
 *
 *  Created on: 2020. 11. 16.
 *      Author: poweryhs
 */
#include "F28x_project.h"
#include "string.h"
#include <stdlib.h>

#ifndef DEFINE_H_
#define DEFINE_H_

//#define SIMUL

#define TBPRD_DB            20 //40  // 200MHz ==> 5*10^-9 ==> 40*5*10^-9 ==> 200*10^-9
#define NcountTs_UPDOWN     2000

#define Fs                  50000.  //100000.
#define Ts                  1/50000.  //1/100000.
#define Fs10                10.
#define Fs100               100.
#define Fs1k                1000.
#define Fs10k               10000.
#define Fs100k              100000.
#define Ts10                0.1.
#define Ts100               0.01
#define Ts1k                0.001
#define Ts10k               0.0001
#define Ts100k              0.00001

#define INV3                1/3.
#define SQRT2               1.414214
#define SQRT3               1.732051
#define INVSqrt2            1/sqrt(2.0)
#define INVSqrt3            1/sqrt(3.0)

#define HalfPI              1.570796327
#define PI                  3.141592654
#define PI2                 6.283185307
#define RmstoAVG            0.9003165946415         //2*1.414214/3.141592654
#define AVGtoRMS            1.1107203909733

#define YES                 1
#define NO                  0
#define HIGH                1
#define LOW                 0
#define TRUE                1
#define FALSE               0
#define ON                  1
#define OFF                 0

typedef unsigned char       Uint8;
typedef signed char         int8;
//typedef int                 int16;
//typedef long                int32;
//typedef unsigned int        Uint16;
//typedef unsigned long       Uint32;

#define BIT0_MASK   (0x00000001U)
#define BIT1_MASK   (0x00000002U)
#define BIT2_MASK   (0x00000004U)
#define BIT3_MASK   (0x00000008U)
#define BIT4_MASK   (0x00000010U)
#define BIT5_MASK   (0x00000020U)
#define BIT6_MASK   (0x00000040U)
#define BIT7_MASK   (0x00000080U)
#define BIT8_MASK   (0x00000100U)
#define BIT9_MASK   (0x00000200U)
#define BIT10_MASK  (0x00000400U)
#define BIT11_MASK  (0x00000800U)
#define BIT12_MASK  (0x00001000U)
#define BIT13_MASK  (0x00002000U)
#define BIT14_MASK  (0x00004000U)
#define BIT15_MASK  (0x00008000U)
#define BIT16_MASK  (0x00010000U)
#define BIT17_MASK  (0x00020000U)
#define BIT18_MASK  (0x00040000U)
#define BIT19_MASK  (0x00080000U)
#define BIT20_MASK  (0x00100000U)
#define BIT21_MASK  (0x00200000U)
#define BIT22_MASK  (0x00400000U)
#define BIT23_MASK  (0x00800000U)
#define BIT24_MASK  (0x01000000U)
#define BIT25_MASK  (0x02000000U)
#define BIT26_MASK  (0x04000000U)
#define BIT27_MASK  (0x08000000U)
#define BIT28_MASK  (0x10000000U)
#define BIT29_MASK  (0x20000000U)
#define BIT30_MASK  (0x40000000U)
#define BIT31_MASK  (0x80000000U)

#endif
