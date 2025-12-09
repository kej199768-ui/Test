/*
 * Parameter.c
 *
 *  Created on: 2021. 12. 22.
 *      Author: IPCL
 */
#include "Define.h"
#include "Parameter.h"
#include "Task_Control.h"
#include "ISR_Control.h"
#include <math.h>


//  Define following variables as "static" in order to retain their value.
/*------------------------------------------------------------------------------
The variable for PFC
-----------------------------------------------------------------------------*/
float L=0.;
float Lest=0.;
float Co=0.;
float Cf = 0.;
float gc=0.;
float KgfVgrid=0;
float KgfVoPFC=0;
float Ki=0;
float Km=0;


void ParameterSetting()
{
//  L=0.00173;
    L=0.000080;
    Co=0.00080;
    Cf = 0.000010;
    gfVoPFCrefCal=400;
    KgfVgrid=1;
    KgfVoPFC=1;

    Ki=1;
    Km=1;
    gc=Km*KgfVgrid/(KgfVgrid*KgfVgrid*Ki);   //gc=400


    Vm_dead=0.02; //50ns/2.5us(400kHz)

}





