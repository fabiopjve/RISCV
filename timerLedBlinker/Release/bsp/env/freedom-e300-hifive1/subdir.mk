################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/env/freedom-e300-hifive1/init.c 

OBJS += \
./bsp/env/freedom-e300-hifive1/init.o 

C_DEPS += \
./bsp/env/freedom-e300-hifive1/init.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/env/freedom-e300-hifive1/%.o: ../bsp/env/freedom-e300-hifive1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DNO_INIT -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


