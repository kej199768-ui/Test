################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../F2838x_common/source/f2838x_codestartbranch.asm \
../F2838x_common/source/f2838x_dbgier.asm \
../F2838x_common/source/f2838x_dcsm_z1otp.asm \
../F2838x_common/source/f2838x_dcsm_z2otp.asm \
../F2838x_common/source/f2838x_usdelay.asm 

C_SRCS += \
../F2838x_common/source/f2838x_adc.c \
../F2838x_common/source/f2838x_cputimers.c \
../F2838x_common/source/f2838x_defaultisr.c \
../F2838x_common/source/f2838x_dma.c \
../F2838x_common/source/f2838x_ecap.c \
../F2838x_common/source/f2838x_emif.c \
../F2838x_common/source/f2838x_epwm.c \
../F2838x_common/source/f2838x_eqep.c \
../F2838x_common/source/f2838x_gpio.c \
../F2838x_common/source/f2838x_mcbsp.c \
../F2838x_common/source/f2838x_piectrl.c \
../F2838x_common/source/f2838x_pievect.c \
../F2838x_common/source/f2838x_sdfm_drivers.c \
../F2838x_common/source/f2838x_struct.c \
../F2838x_common/source/f2838x_sysctrl.c \
../F2838x_common/source/f2838x_tempsensorconv.c 

C_DEPS += \
./F2838x_common/source/f2838x_adc.d \
./F2838x_common/source/f2838x_cputimers.d \
./F2838x_common/source/f2838x_defaultisr.d \
./F2838x_common/source/f2838x_dma.d \
./F2838x_common/source/f2838x_ecap.d \
./F2838x_common/source/f2838x_emif.d \
./F2838x_common/source/f2838x_epwm.d \
./F2838x_common/source/f2838x_eqep.d \
./F2838x_common/source/f2838x_gpio.d \
./F2838x_common/source/f2838x_mcbsp.d \
./F2838x_common/source/f2838x_piectrl.d \
./F2838x_common/source/f2838x_pievect.d \
./F2838x_common/source/f2838x_sdfm_drivers.d \
./F2838x_common/source/f2838x_struct.d \
./F2838x_common/source/f2838x_sysctrl.d \
./F2838x_common/source/f2838x_tempsensorconv.d 

OBJS += \
./F2838x_common/source/f2838x_adc.obj \
./F2838x_common/source/f2838x_codestartbranch.obj \
./F2838x_common/source/f2838x_cputimers.obj \
./F2838x_common/source/f2838x_dbgier.obj \
./F2838x_common/source/f2838x_dcsm_z1otp.obj \
./F2838x_common/source/f2838x_dcsm_z2otp.obj \
./F2838x_common/source/f2838x_defaultisr.obj \
./F2838x_common/source/f2838x_dma.obj \
./F2838x_common/source/f2838x_ecap.obj \
./F2838x_common/source/f2838x_emif.obj \
./F2838x_common/source/f2838x_epwm.obj \
./F2838x_common/source/f2838x_eqep.obj \
./F2838x_common/source/f2838x_gpio.obj \
./F2838x_common/source/f2838x_mcbsp.obj \
./F2838x_common/source/f2838x_piectrl.obj \
./F2838x_common/source/f2838x_pievect.obj \
./F2838x_common/source/f2838x_sdfm_drivers.obj \
./F2838x_common/source/f2838x_struct.obj \
./F2838x_common/source/f2838x_sysctrl.obj \
./F2838x_common/source/f2838x_tempsensorconv.obj \
./F2838x_common/source/f2838x_usdelay.obj 

ASM_DEPS += \
./F2838x_common/source/f2838x_codestartbranch.d \
./F2838x_common/source/f2838x_dbgier.d \
./F2838x_common/source/f2838x_dcsm_z1otp.d \
./F2838x_common/source/f2838x_dcsm_z2otp.d \
./F2838x_common/source/f2838x_usdelay.d 

OBJS__QUOTED += \
"F2838x_common\source\f2838x_adc.obj" \
"F2838x_common\source\f2838x_codestartbranch.obj" \
"F2838x_common\source\f2838x_cputimers.obj" \
"F2838x_common\source\f2838x_dbgier.obj" \
"F2838x_common\source\f2838x_dcsm_z1otp.obj" \
"F2838x_common\source\f2838x_dcsm_z2otp.obj" \
"F2838x_common\source\f2838x_defaultisr.obj" \
"F2838x_common\source\f2838x_dma.obj" \
"F2838x_common\source\f2838x_ecap.obj" \
"F2838x_common\source\f2838x_emif.obj" \
"F2838x_common\source\f2838x_epwm.obj" \
"F2838x_common\source\f2838x_eqep.obj" \
"F2838x_common\source\f2838x_gpio.obj" \
"F2838x_common\source\f2838x_mcbsp.obj" \
"F2838x_common\source\f2838x_piectrl.obj" \
"F2838x_common\source\f2838x_pievect.obj" \
"F2838x_common\source\f2838x_sdfm_drivers.obj" \
"F2838x_common\source\f2838x_struct.obj" \
"F2838x_common\source\f2838x_sysctrl.obj" \
"F2838x_common\source\f2838x_tempsensorconv.obj" \
"F2838x_common\source\f2838x_usdelay.obj" 

C_DEPS__QUOTED += \
"F2838x_common\source\f2838x_adc.d" \
"F2838x_common\source\f2838x_cputimers.d" \
"F2838x_common\source\f2838x_defaultisr.d" \
"F2838x_common\source\f2838x_dma.d" \
"F2838x_common\source\f2838x_ecap.d" \
"F2838x_common\source\f2838x_emif.d" \
"F2838x_common\source\f2838x_epwm.d" \
"F2838x_common\source\f2838x_eqep.d" \
"F2838x_common\source\f2838x_gpio.d" \
"F2838x_common\source\f2838x_mcbsp.d" \
"F2838x_common\source\f2838x_piectrl.d" \
"F2838x_common\source\f2838x_pievect.d" \
"F2838x_common\source\f2838x_sdfm_drivers.d" \
"F2838x_common\source\f2838x_struct.d" \
"F2838x_common\source\f2838x_sysctrl.d" \
"F2838x_common\source\f2838x_tempsensorconv.d" 

ASM_DEPS__QUOTED += \
"F2838x_common\source\f2838x_codestartbranch.d" \
"F2838x_common\source\f2838x_dbgier.d" \
"F2838x_common\source\f2838x_dcsm_z1otp.d" \
"F2838x_common\source\f2838x_dcsm_z2otp.d" \
"F2838x_common\source\f2838x_usdelay.d" 

C_SRCS__QUOTED += \
"../F2838x_common/source/f2838x_adc.c" \
"../F2838x_common/source/f2838x_cputimers.c" \
"../F2838x_common/source/f2838x_defaultisr.c" \
"../F2838x_common/source/f2838x_dma.c" \
"../F2838x_common/source/f2838x_ecap.c" \
"../F2838x_common/source/f2838x_emif.c" \
"../F2838x_common/source/f2838x_epwm.c" \
"../F2838x_common/source/f2838x_eqep.c" \
"../F2838x_common/source/f2838x_gpio.c" \
"../F2838x_common/source/f2838x_mcbsp.c" \
"../F2838x_common/source/f2838x_piectrl.c" \
"../F2838x_common/source/f2838x_pievect.c" \
"../F2838x_common/source/f2838x_sdfm_drivers.c" \
"../F2838x_common/source/f2838x_struct.c" \
"../F2838x_common/source/f2838x_sysctrl.c" \
"../F2838x_common/source/f2838x_tempsensorconv.c" 

ASM_SRCS__QUOTED += \
"../F2838x_common/source/f2838x_codestartbranch.asm" \
"../F2838x_common/source/f2838x_dbgier.asm" \
"../F2838x_common/source/f2838x_dcsm_z1otp.asm" \
"../F2838x_common/source/f2838x_dcsm_z2otp.asm" \
"../F2838x_common/source/f2838x_usdelay.asm" 


