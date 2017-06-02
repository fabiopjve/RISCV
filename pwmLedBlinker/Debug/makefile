################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include bsp/env/freedom-e300-hifive1/subdir.mk
-include bsp/env/subdir.mk
-include bsp/drivers/plic/subdir.mk
-include bsp/drivers/fe300prci/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_SIZE += \
pwmLedBlinker.siz \


# All Target
all: pwmLedBlinker.elf secondary-outputs

# Tool invocations
pwmLedBlinker.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: RISC-V GCC/Newlib C Linker'
	riscv64-unknown-elf-gcc -mabi=ilp32 -g3 -gdwarf-2 -march=rv32imac -T"../link.lds" -nostartfiles -Xlinker --gc-sections -L../ -Wl,-Map,pwmLedBlinker.map -Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=open -Wl,--wrap=lseek -Wl,--wrap=read -Wl,--wrap=write -Wl,--wrap=fstat -Wl,--wrap=stat -Wl,--wrap=close -Wl,--wrap=link -Wl,--wrap=unlink -Wl,--wrap=execve -Wl,--wrap=fork -Wl,--wrap=getpid -Wl,--wrap=kill -Wl,--wrap=wait -Wl,--wrap=isatty -Wl,--wrap=times -Wl,--wrap=sbrk -Wl,--wrap=_exit -L. -Wl,--start-group -Wl,--end-group -Wl,-gc-sections -o "pwmLedBlinker.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

pwmLedBlinker.siz: pwmLedBlinker.elf
	@echo 'Invoking: RISC-V GCC/Newlib Print Size'
	riscv64-unknown-elf-size --format=berkeley "pwmLedBlinker.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) pwmLedBlinker.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
