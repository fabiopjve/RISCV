################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/drivers/plic/plic_driver.c 

OBJS += \
./bsp/drivers/plic/plic_driver.o 

C_DEPS += \
./bsp/drivers/plic/plic_driver.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/drivers/plic/%.o: ../bsp/drivers/plic/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DNO_INIT -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


