################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/drivers/fe300prci/fe300prci_driver.c 

OBJS += \
./bsp/drivers/fe300prci/fe300prci_driver.o 

C_DEPS += \
./bsp/drivers/fe300prci/fe300prci_driver.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/drivers/fe300prci/%.o: ../bsp/drivers/fe300prci/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -msmall-data-limit=8 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -DNO_INIT -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


