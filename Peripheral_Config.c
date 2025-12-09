/*
 * Peripheral_Config.c
 *
 *  Created on: 2020. 11. 16.
 *      Author: poweryhs
 */

#include "f28x_project.h"
#include "Define.h"
#include "Peripheral_Config.h"
#include "ADC.h"
#include "ISR_Control.h"
#include "Task_Control.h"
#include "ISR.h"
#include "Task.h"



void InitGpioConfig()
{
    EALLOW;
    GpioCtrlRegs.GPACTRL.all = 0x00000000;
    GpioCtrlRegs.GPBCTRL.all = 0x00000000;
    GpioCtrlRegs.GPCCTRL.all = 0x00000000;
    GpioCtrlRegs.GPDCTRL.all = 0x00000000;
    EDIS;
}

void InitPWMEnaFltGpioConfig()
{
    EALLOW;
    //===========================================================================
    //PWM12 ENABLE 1, DC/DC1 and INV1
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO38  = 1;   // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 0;   // GPIO output
    GpioCtrlRegs.GPBDIR.bit.GPIO38  = 1;   // Output
    GpioDataRegs.GPBSET.bit.GPIO38  = 1;

    //===========================================================================
    //PWM34 ENABLE 2, DC/DC2 and INV2
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO39  = 1;   // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;   // GPIO output
    GpioCtrlRegs.GPBDIR.bit.GPIO39  = 1;   // Output
    GpioDataRegs.GPBSET.bit.GPIO39  = 1;

    //===========================================================================
    //PWM56 ENABLE 3, DC/DC3 and INV3
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO40  = 1;   // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;   // GPIO output
    GpioCtrlRegs.GPBDIR.bit.GPIO40  = 1;   // Output

    //===========================================================================
    //PWM78 ENABLE 4, DC/DC4
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO41  = 1;   // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;   // GPIO output
    GpioCtrlRegs.GPBDIR.bit.GPIO41  = 1;   // Output


    //===========================================================================
    //PWM FLT1
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO112  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX2.bit.GPIO112 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO112  = 0;   // Input
    //===========================================================================
    //PWM FLT2
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO113  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX2.bit.GPIO113 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO113  = 0;   // Input
    //===========================================================================
    //PWM FLT3
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO114  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX2.bit.GPIO114 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO114  = 0;   // Input
    //===========================================================================
    //PWM FLT4
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO114  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX2.bit.GPIO114 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO114  = 0;   // Input
    EDIS;
}

void InitGpioInOutConfig()
{
    EALLOW;
    //===========================================================================
    //Low speed High side switch GPIO
    //===========================================================================
    GpioCtrlRegs.GPAPUD.bit.GPIO0  = 1;   // Enable pullup
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;   // GPIO output
    GpioCtrlRegs.GPADIR.bit.GPIO0  = 1;   // Output
    //===========================================================================
    //Low speed Low side switch GPIO
    //===========================================================================
    GpioCtrlRegs.GPAPUD.bit.GPIO1  = 1;   // Enable pullup
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;   // GPIO output
    GpioCtrlRegs.GPADIR.bit.GPIO1  = 1;   // Output

    //===========================================================================
    //GPIO RLY ON
    //===========================================================================
    GpioCtrlRegs.GPAPUD.bit.GPIO6  = 1;   // Enable pullup
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;   // GPIO output
    GpioCtrlRegs.GPADIR.bit.GPIO6  = 1;   // Output
    //===========================================================================
    //GPIO PORT1 ENABLE
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO46  = 1;   // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 0;   // GPIO output
    GpioCtrlRegs.GPBDIR.bit.GPIO46  = 1;   // Output
    GpioDataRegs.GPBSET.bit.GPIO46  = 1;   // Enable
    //===========================================================================
    //GPIO24
    //===========================================================================
    GpioCtrlRegs.GPAPUD.bit.GPIO24  = 1;   // Enable pullup
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;   // GPIO output
    GpioCtrlRegs.GPADIR.bit.GPIO24  = 1;   // Output
    //===========================================================================
    //GPIO25
    //===========================================================================
    GpioCtrlRegs.GPAPUD.bit.GPIO25  = 1;   // Enable pullup
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;   // GPIO output
    GpioCtrlRegs.GPADIR.bit.GPIO25  = 1;   // Output
    //===========================================================================
    //GPIO26
    //===========================================================================
    GpioCtrlRegs.GPAPUD.bit.GPIO26  = 1;   // Enable pullup
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;   // GPIO output
    GpioCtrlRegs.GPADIR.bit.GPIO26  = 1;   // Output
    //===========================================================================
    //GPIO27
    //===========================================================================
    GpioCtrlRegs.GPAPUD.bit.GPIO27  = 1;   // Enable pullup
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;   // GPIO output
    GpioCtrlRegs.GPADIR.bit.GPIO27  = 1;   // Output
    //===========================================================================
    //GPIO64
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO64  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO64 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO64  = 1;   // Output
    //===========================================================================
    //GPIO65
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO65  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO65 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO65  = 1;   // Output
    //===========================================================================
    //GPIO66
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO66  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO66  = 1;   // Output
    //===========================================================================
    //GPIO67
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO67  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO67 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO67  = 1;   // Output

    //===========================================================================
    //GPIO PORT2 ENABLE
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO47  = 1;   // Enable pullup
    GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 0;   // GPIO output
    GpioCtrlRegs.GPBDIR.bit.GPIO47  = 1;   // Output
    //===========================================================================
    //GPIO68
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO68  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO68  = 1;   // Output
    //===========================================================================
    //GPIO69
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO69  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO69 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO69  = 1;   // Output
    //===========================================================================
    //GPIO70
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO70  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO70  = 1;   // Output
    //===========================================================================
    //GPIO71
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO71  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO71  = 1;   // Output
    //===========================================================================
    //GPIO73
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO73  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO73  = 1;   // Output
    //===========================================================================
    //GPIO74
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO74  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO74  = 1;   // Output
    //===========================================================================
    //GPIO75
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO75  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO75  = 1;   // Output
    //===========================================================================
    //GPIO76
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO76  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX1.bit.GPIO76 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO76  = 1;   // Output
    EDIS;
}

void InitADCFltGpioConfig()
{
    EALLOW;
    //===========================================================================
    //ADCA2,A3,A4,A5,B2,B3 High Flt ENABLE : GPIO82
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO82  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO82 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO82  = 1;   // Output
    //===========================================================================
    //ADCA2,A3,A4,A5,B2,B3 Low Flt ENABLE : GPIO86
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO86  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO86  = 1;   // Output


    //===========================================================================
    //ADCA2 High/Low Flt : GPIO89
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO89  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO89 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO89  = 0;   // Iuput
    //===========================================================================
    //ADCA3 High/Low Flt : GPIO90
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO90  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO90 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO90  = 0;   // Iuput
    //===========================================================================
    //ADCA4 High/Low Flt : GPIO91
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO91  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO91 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO91  = 0;   // Iuput
    //===========================================================================
    //ADCA5 High/Low Flt : GPIO92
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO92  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO92 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO92  = 0;   // Iuput
    //===========================================================================
    //ADCB2 High/Low Flt : GPIO93
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO93  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO93 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO93  = 0;   // Iuput
    //===========================================================================
    //ADCB3 High/Low Flt : GPIO94
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO94  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO94 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO94  = 0;   // Iuput


    //===========================================================================
    //ADCB4,B5,C2,C3,C4,C5 High Flt ENABLE : GPIO83
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO83  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO83 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO83  = 1;   // Output
    //===========================================================================
    //ADCB4,B5,C2,C3,C4,C5 Low Flt ENABLE : GPIO87
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO87  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO87  = 1;   // Output


    //===========================================================================
    //ADCB4 High/Low Flt : GPIO95
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO95  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO95 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO95  = 0;   // Iuput
    //===========================================================================
    //ADCB5 High/Low Flt : GPIO96
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO96  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO96 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO96  = 0;   // Iuput
    //===========================================================================
    //ADCC2 High/Low Flt : GPIO97
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO97  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO97 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO97  = 0;   // Iuput
    //===========================================================================
    //ADCC3 High/Low Flt : GPIO98
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO98  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO98 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO98  = 0;   // Iuput
    //===========================================================================
    //ADCC4 High/Low Flt : GPIO99
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO99  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO99 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO99  = 0;   // Iuput
    //===========================================================================
    //ADCC5 High/Low Flt : GPIO100
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO100  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO100 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO100  = 0;   // Iuput



    //===========================================================================
    //ADCD0,D1,D2,D3,14,15 High Flt ENABLE : GPIO85
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO85  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO85  = 1;   // Output
    //===========================================================================
    //ADCD0,D1,D2,D3,14,15 Low Flt ENABLE : GPIO88
    //===========================================================================
    GpioCtrlRegs.GPCPUD.bit.GPIO88  = 1;   // Enable pullup
    GpioCtrlRegs.GPCMUX2.bit.GPIO88 = 0;   // GPIO output
    GpioCtrlRegs.GPCDIR.bit.GPIO88  = 1;   // Output


    //===========================================================================
    //ADCD0 High/Low Flt : GPIO101
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO101  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO101 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO101  = 0;   // Iuput
    //===========================================================================
    //ADCD1 High/Low Flt : GPIO102
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO102  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO102 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO102  = 0;   // Iuput
    //===========================================================================
    //ADCD2 High/Low Flt : GPIO103
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO103  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO103 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO103  = 0;   // Iuput
    //===========================================================================
    //ADCD3 High/Low Flt : GPIO104
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO104  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO104 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO104  = 0;   // Iuput
    //===========================================================================
    //ADC14 High/Low Flt : GPIO105
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO105  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO105 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO105  = 0;   // Iuput
    //===========================================================================
    //ADC15 High/Low Flt : GPIO106
    //===========================================================================
    GpioCtrlRegs.GPDPUD.bit.GPIO106  = 1;   // Enable pullup
    GpioCtrlRegs.GPDMUX1.bit.GPIO106 = 0;   // GPIO output
    GpioCtrlRegs.GPDDIR.bit.GPIO106  = 0;   // Iuput
    EDIS;


}

void InitMcBspSPIConfig()
{
    EALLOW;

    //===========================================================================
    //MCBSP
    //===========================================================================
    GpioCtrlRegs.GPAPUD.bit.GPIO20  = 0;   // Enable pullup
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 2;   // MDXA

    GpioCtrlRegs.GPAPUD.bit.GPIO22  = 0;   // Enable pullup
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 2;   // MCLKXA
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 3;


    GpioCtrlRegs.GPAPUD.bit.GPIO23  = 0;   // Enable pullup
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 2;   // MFSXA
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 3;


    //===========================================================================
    //SPI
    //===========================================================================
    GpioCtrlRegs.GPBPUD.bit.GPIO54  = 1;   // Enable pullup
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1;   // SPIA_SIMO

    GpioCtrlRegs.GPBPUD.bit.GPIO56  = 1;   // Enable pullup
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1;   // SPIA_CLK
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3;

    GpioCtrlRegs.GPBPUD.bit.GPIO57  = 1;   // Enable pullup
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;   // SPIA_STEn인데 GPIO mode로 signal 한다.
    GpioCtrlRegs.GPBDIR.bit.GPIO57  = 1;   // output
    GpioDataRegs.GPBDAT.bit.GPIO57  = 1;   // initial disable to transmit data. (active low)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3;
    EDIS;
}



// Ç®±â
//
// InitEPwm1Example - Initialize EPWM1 configuration
//
#if 0
void EPwm1_Config()
{
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0x0;

    /**********************************************************************
    EPWM1 Config
    **********************************************************************/
//    EPwm1Regs.TZCLR.bit.OST = 0;
    EPwm1Regs.TZFRC.bit.OST = 1;
    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
    EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

    EPwm1Regs.TBPRD = NcountTs_UPDOWN;         // Set timer period
    EPwm1Regs.TBCTR = 0;                            // Clear counter
    EPwm1Regs.TBPHS.bit.TBPHS = 0;                  // Phase is 0

    // Setup TBCLK
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;      // Count up
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Enable phase loading
    EPwm1Regs.EPWMSYNCINSEL.all = 0x00;
    EPwm1Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    EPwm1Regs.CMPA.bit.CMPA = 0;

    // Set actions
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;

    // Active Low PWMs - Setup Deadband
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm1Regs.DBRED.bit.DBRED = TBPRD_DB;
    EPwm1Regs.DBFED.bit.DBFED = TBPRD_DB;

    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
    EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

    //ADC SOC Control Register
    EPwm1Regs.ETSEL.bit.SOCAEN       = 1;                    //Enable To Generate SOC Signal On A Group
    EPwm1Regs.ETSEL.bit.SOCASEL      = ET_CTR_ZERO;          //Set Time When SOC Is Generated,
                                                             //1: TBCTR=0, 2: TBCTR=TBPRD
                                                             //6: TBCTR=COMPB_Incrementing, 7: TBCTR=COMPB_Decrementing
    EPwm1Regs.ETPS.bit.SOCAPRD       = ET_1ST;               //Generate Pulse On 1st Event

    EDIS;

}
#endif

void EPwm2_Config()
{
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0x0;
    /**********************************************************************
    EPWM2 Config
    **********************************************************************/

    EPwm2Regs.TZFRC.bit.OST = 1;
    EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
    EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

    // Setup TBCLK
    EPwm2Regs.TBPRD = NcountTs_UPDOWN;         // Set timer period
    EPwm2Regs.TBCTR = 0;                            // Clear counter
    EPwm2Regs.TBPHS.bit.TBPHS = 0;                  // Phase is 0

    // Setup TBCLK
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;      // Count up
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Enable phase loading
    EPwm2Regs.EPWMSYNCINSEL.all = 0x00;
    EPwm2Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;

    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;


    // Set actions
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;            // Set PWM2A Phase 1 High speed High side switch
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;

    EPwm2Regs.AQCTLB.bit.CBD = AQ_SET;            // Set PWM2B Phase 1 High speed Low side switch
    EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    //ADC SOC Control Register
    EPwm2Regs.ETSEL.bit.SOCAEN       = 1;                    //Enable To Generate SOC Signal On A Group
    EPwm2Regs.ETSEL.bit.SOCASEL      = ET_CTR_ZERO;          //Set Time When SOC Is Generated,
                                                             //1: TBCTR=0, 2: TBCTR=TBPRD
                                                             //6: TBCTR=COMPB_Incrementing, 7: TBCTR=COMPB_Decrementing
    EPwm2Regs.ETPS.bit.SOCAPRD       = ET_1ST;               //Generate Pulse On 1st Event

    EDIS;

}

void EPwm3_Config()
{
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0x0;
    /**********************************************************************
    EPWM3 Config
    **********************************************************************/

    EPwm3Regs.TZFRC.bit.OST = 1;
    EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
    EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

    EPwm3Regs.TBPRD = NcountTs_UPDOWN;         // Set timer period
    EPwm3Regs.TBCTR = 0;                       // Clear counter
    EPwm3Regs.TBPHS.bit.TBPHS = NcountTs_UPDOWN;             // Phase is 0

    // Setup TBCLK
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;      // Count up
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;          // Enable phase loading
    EPwm3Regs.EPWMSYNCINSEL.bit.SEL = 0x02;
    EPwm3Regs.EPWMSYNCOUTEN.all = 0;
    EPwm3Regs.EPWMSYNCOUTEN.bit.ZEROEN = 0;

    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    // Set actions
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;            // Set PWM3A Phase 2 High speed High side switch
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;            // Set PWM3B Phase 2 High speed Low side switch
    EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;


    //ADC SOC Control Register
    EPwm3Regs.ETSEL.bit.SOCAEN       = 1;                    //Enable To Generate SOC Signal On A Group
    EPwm3Regs.ETSEL.bit.SOCASEL      = ET_CTR_ZERO;          //Set Time When SOC Is Generated,
                                                             //1: TBCTR=0, 2: TBCTR=TBPRD
                                                             //6: TBCTR=COMPB_Incrementing, 7: TBCTR=COMPB_Decrementing
    EPwm3Regs.ETPS.bit.SOCAPRD       = ET_1ST;               //Generate Pulse On 1st Event


    EDIS;
}


void Adc_Config()
{
    Uint16 acqps;

    EALLOW;

    //
    //write configurations
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcdRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //
    //Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    //power up the ADC
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //
    //delay for 1ms to allow ADC time to power up
    //
    DELAY_US(1000);


    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 14; //75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns
    }


    /**********************************************************************
     PFC phase1
    **********************************************************************/

    // IL1
    AdcaRegs.ADCSOC0CTL.bit.CHSEL   = 4;        //SOC0 will convert pin A4
    AdcaRegs.ADCSOC0CTL.bit.ACQPS   = acqps;    //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 7;        //trigger on ePWM2 SOCA

    // Vgrid
    AdcbRegs.ADCSOC0CTL.bit.CHSEL   = 5;        //SOC0 will convert pin B5
    AdcbRegs.ADCSOC0CTL.bit.ACQPS   = acqps;    //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 7;        //trigger on ePWM2 SOCA

    /**********************************************************************
      PFC phase2
    **********************************************************************/
    // IL2
    AdcaRegs.ADCSOC1CTL.bit.CHSEL   = 2;        //SOC0 will convert pin A2
    AdcaRegs.ADCSOC1CTL.bit.ACQPS   = acqps;    //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 9;        //trigger on ePWM3 SOCA

    // Vo_PFC
    AdcaRegs.ADCSOC2CTL.bit.CHSEL   = 5;        //SOC0 will convert pin A5
    AdcaRegs.ADCSOC2CTL.bit.ACQPS   = acqps;    //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 9;        //trigger on ePWM3 SOCA


    //ADC SOC control register (p509)
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;      //end of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;        //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      //make sure INT1 flag is cleared

    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 2;     //end of SOC2 will set INT2 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT2E = 1;        //enable INT2 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;      //make sure INT2 flag is cleared



    EDIS;
}


#if 0
void DAC_Config()
{
    EALLOW;

    //DAC PWM SYNC ¼³Á¤/ 0: PWMSYNC1 , 1:PWMSYNC2
    //EPWM1 syncsel --> PWMSYNC1
    DacaRegs.DACCTL.bit.SYNCSEL = 0;
    //DACVALA ·Îµå ÇÏ´Â Å¸ÀÌ¹Ö ¼³Á¤ / 0:Next sysclk , 1:Next PWMSync
    DacaRegs.DACCTL.bit.LOADMODE = 1;
    //DAC ·¹ÆÛ·±½º ¼³Á¤/ 0:VDAC/VSSA 1:ADC VREFHI/VREFLO
    DacaRegs.DACCTL.bit.DACREFSEL = 1;
    // DACA Ãâ·ÂÀ¸·Î ¼³Á¤ / 0:»ç¿ëx, 1:»ç¿ë
    DacaRegs.DACOUTEN.bit.DACOUTEN = 0;
    EDIS;

    //DAC Á¤»óÈ­¸¦ À§ÇÑ Áö¿¬½Ã°£
    DELAY_US(10);

}
#endif

#if 0
void CMPSS_Config()
{

    EALLOW;
    //ADCINA2=CMPIN1P, ADCINA3=CMPIN1N
    //CMPSS1 È°¼ºÈ­
    Cmpss1Regs.COMPCTL.bit.COMPDACE = 1;
    //CMPINxN ¼Ò½º ¼³Á¤, 0:³»ºÎ DAC, 1:ADCINA3
    Cmpss1Regs.COMPCTL.bit.COMPHSOURCE = NEGIN_DAC;
    //CMPSS ·¹ÆÛ·±½º Àü¾Ð ¼³Á¤, 0:VDDA, 1:VDAC
    Cmpss1Regs.COMPDACCTL.bit.SELREF = REFERENCE_VDDA;
    //³»ºÎ DAC ¼Ò½º ¼³Á¤, 0 : 12bit DAC, 1 : 16bit ramp generator
    Cmpss1Regs.COMPDACCTL.bit.DACSOURCE = 0; //DAC »ç¿ë
    //Cmpss1Regs.COMPDACCTL.bit.DACSOURCE = 1; //Ramp »ç¿ë

    //DACVALS ·Îµå ¸ðµå ¼³Á¤, 0:´ÙÀ½ Å¬·°, 1:´ÙÀ½ sync ½Ã±×³Î
    Cmpss1Regs.COMPDACCTL.bit.SWLOADSEL = 1;
/*
    //·¥ÇÁ ½ÃÀÛ ¼Ò½º ¼³Á¤, 0:PWMSYNC1, 1:PWMSYNC2 ... n-1:PWMSYNCn
    Cmpss1Regs.COMPDACCTL.bit.RAMPSOURCE = 1;
    //RAMPVALS ·Îµå ¸ðµå ¼³Á¤, 0:´ÙÀ½ Å¬·°, 1:´ÙÀ½ ramp generator
    Cmpss1Regs.COMPDACCTL.bit.RAMPLOADSEL = 1;
*/

    //
    //Set DAC to midpoint for arbitrary reference
    //
    Cmpss1Regs.DACHVALS.bit.DACVAL = 2048;

    Cmpss1Regs.CTRIPHFILCLKCTL.bit.CLKPRESCALE = 0;
    Cmpss1Regs.CTRIPHFILCTL.bit.SAMPWIN =10;
    Cmpss1Regs.CTRIPHFILCTL.bit.THRESH = 10;
    Cmpss1Regs.CTRIPHFILCTL.bit.FILINIT = 1;

    //³»ºÎ Æ®¸³ ½ÅÈ£ Ãú·Â ¼³Á¤, 0:async, 1:sync, 2:digital filter, 3:latch
    Cmpss1Regs.COMPCTL.bit.CTRIPHSEL=CTRIP_FILTER;
    //¿ÜºÎ Ãâ·Â ½ÅÈ£ Ãâ·Â ¼³Á¤, 0:async, 1:sync, 2:digital filter, 3:latch
    Cmpss1Regs.COMPCTL.bit.CTRIPOUTHSEL=CTRIP_FILTER;

    //EPwmXbarTrip4 MUX 0.0 ±â´É (CMPSS1.CTRIPH)À¸·Î ¼³Á¤
    EPwmXbarRegs.TRIP4MUX0TO15CFG.bit.MUX0 = 0;
    //EPwmXbarTrip4 MUX 0 ±â´É È°¼ºÈ­
    EPwmXbarRegs.TRIP4MUXENABLE.bit.MUX0 = 1;

    //OUTPUTXBAR8 MUX 0.0 ±â´É (CMPSS1.CTRIPOUTH)À¸·Î ¼³Á¤
    OutputXbarRegs.OUTPUT8MUX0TO15CFG.bit.MUX0 = 0;
    //OUTPUTXBAR8 MUX 0 ±â´É È°¼ºÈ­
    OutputXbarRegs.OUTPUT8MUXENABLE.bit.MUX0 =  1;

    EDIS;

    //CMPSS Á¤»óÈ­¸¦ À§ÇÑ Áö¿¬½Ã°£
    DELAY_US(10);


}
#endif


#if 0
void MCBSPDAC_Config()
{
    EALLOW;
   //McBSP
    McbspaRegs.SPCR2.all = 0x0000;
    McbspaRegs.SPCR1.all = 0x0000;
    McbspaRegs.PCR.all = 0x0F08;

    McbspaRegs.SPCR1.bit.CLKSTP = 2;
    McbspaRegs.MCR2.all = 0x0;
    McbspaRegs.XCR1.bit.XWDLEN1 = 2;
    McbspaRegs.RCR1.bit.RWDLEN1 = 2;
    McbspaRegs.XCR2.bit.XDATDLY = 1;
    McbspaRegs.RCR2.bit.RDATDLY = 1;
    McbspaRegs.MCR1.all = 0x0;

    McbspaRegs.SRGR2.all = 0x2000;
    McbspaRegs.SRGR2.bit.FPER = 0;
    McbspaRegs.SRGR1.bit.FWID = 15;
    McbspaRegs.SRGR1.bit.CLKGDV = 4;


    McbspaRegs.SPCR2.bit.GRST = 1;
    //delayloop();

    McbspaRegs.SPCR2.bit.XRST = 1;

    McbspaRegs.SPCR2.bit.FRST = 1;
    McbspaRegs.SPCR1.bit.RRST = 1;
    EDIS;
}

#endif


void SPIDAC_Config(void)
{

    //EALLOW; //사실 SPI는 EALLOW EDIS 필요없음. datasheet 참고.

    //초기화 동작
    SpiaRegs.SPICCR.bit.SPISWRESET = 0; //initialization. all flag clear. like EALLOW.

    //mode & function setting
    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;
    SpiaRegs.SPICCR.bit.HS_MODE = 0;
    SpiaRegs.SPICCR.bit.SPILBK = 0;

    //중요!!! 3선방식
    SpiaRegs.SPIPRI.bit.TRIWIRE = 1;

    //CLK
    SpiaRegs.SPICTL.bit.CLK_PHASE = 0;
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;
    SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = 3; // SPICLK = LSPCLK/(x).  해당 비트 : 0~3까지는 x=4. LSPCLK의 default는 50MHz. 최종 12.5MHz의 SPICLK를 설정.

    //ect
    SpiaRegs.SPICCR.bit.SPICHAR = 15; //16bit
    SpiaRegs.SPICTL.bit.SPIINTENA = 0;
    SpiaRegs.SPICTL.bit.TALK = 1;


    SpiaRegs.SPICCR.bit.SPISWRESET = 1; //ready to use SPI
    //EDIS;

}
