################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pwmLedBlinker.c 

OBJS += \
./pwmLedBlinker.o 

C_DEPS += \
./pwmLedBlinker.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: RISC-V GCC/Newlib C Compiler'
	/home/fabiop/RISCV/FreedomStudio/bin/riscv64-unknown-elf-gcc -mabi=ilp32 -g3 -gdwarf-2 -march=rv32imac -DUSE_PLIC -DUSE_M_TIME -I"/home/fabiop/Development/RISCV/pwmLedBlinker/bsp/env/freedom-e300-hifive1" -I"/home/fabiop/Development/RISCV/pwmLedBlinker/bsp/env" -I"/home/fabiop/Development/RISCV/pwmLedBlinker/bsp/include" -I"/home/fabiop/Development/RISCV/pwmLedBlinker/bsp/drivers" -O3 -ffunction-sections -fdata-sections -Wall -c -fno-builtin-printf -include sys/cdefs.h -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


