/*
 * Parameter.h
 *
 *  Created on: 2021. 12. 22.
 *      Author: IPCL
 */

#include "StructDefine.h"

#ifndef PARAMETER_H_
#define PARAMETER_H_

//  Define following variables as "extern" in order to retain their value.
/*------------------------------------------------------------------------------
The variable for PFC
------------------------------------------------------------------------------*/
extern float L;
extern float Lest;
extern float Co;
extern float Cf;
extern float gc;
extern float KgfVgrid;
extern float KgfVoPFC;
extern float Ki;
extern float Km;

void ParameterSetting();

#endif
