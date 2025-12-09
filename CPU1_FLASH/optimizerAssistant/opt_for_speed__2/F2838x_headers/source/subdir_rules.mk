################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
F2838x_headers/source/%.obj: ../F2838x_headers/source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-c2000_20.8.0.STS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --opt_for_speed=2 --fp_mode=relaxed --include_path="C:/ti/Workspace/211228_interleaved_totempole_PFC_opti" --include_path="C:/ti/C2000Ware_3_04_00_00_Software/device_support/f2838x/common/include" --include_path="C:/ti/C2000Ware_3_04_00_00_Software/device_support/f2838x/headers/include" --include_path="C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-c2000_20.8.0.STS/include" --advice:performance=all --define=DEBUG --define=CPU1 --define=_FLASH --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="F2838x_headers/source/$(basename $(<F)).d_raw" --obj_directory="F2838x_headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


