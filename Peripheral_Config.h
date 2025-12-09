/*
 * DPP_Peripheral_Config.h
 *
 *  Created on: 2020. 11. 16.
 *      Author: poweryhs
 */


#ifndef LLC_PERIPHERAL_CONFIG_H_
#define LLC_PERIPHERAL_CONFIG_H_


extern Uint16 flagInit;
extern float countTs1;
extern float countTs2;
extern float countTask100us;

extern Uint16 HSSW_Phase1_gateH;
extern Uint16 HSSW_Phase1_gateL;
extern Uint16 HSSW_Phase2_gateH;
extern Uint16 HSSW_Phase2_gateL;
extern Uint16 LSSW_gateH;
extern Uint16 LSSW_gateL;
extern Uint16 RLY_gate;


//
// Function Peripheral Config
//
void InitGpioConfig(void);
void InitPWMEnaFltGpioConfig(void);
void InitGpioInOutConfig(void);
void InitMcBspSPIConfig();

void Epwm_gating(void);
void EPwm1_Config(void);
void EPwm2_Config(void);
void EPwm3_Config(void);
void Adc_Config(void);
void DAC_Config(void);
void CMPSS_Config(void);
void MCBSPDAC_Config(void);
void SPIDAC_Config(void);

#endif /* LLC_PERIPHERAL_CONFIG_H_ */
