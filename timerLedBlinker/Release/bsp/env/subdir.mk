################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../bsp/env/entry.S \
../bsp/env/start.S 

OBJS += \
./bsp/env/entry.o \
./bsp/env/start.o 

S_UPPER_DEPS += \
./bsp/env/entry.d \
./bsp/env/start.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/env/%.o: ../bsp/env/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv64-unknown-elf-gcc -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


