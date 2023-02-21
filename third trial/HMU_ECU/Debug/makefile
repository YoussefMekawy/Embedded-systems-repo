################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
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
LSS += \
HMU_ECU.lss \

FLASH_IMAGE += \
HMU_ECU.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: HMU_ECU.elf secondary-outputs

# Tool invocations
HMU_ECU.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,HMU_ECU.map -mmcu=atmega32 -o "HMU_ECU.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

HMU_ECU.lss: HMU_ECU.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S HMU_ECU.elf  >"HMU_ECU.lss"
	@echo 'Finished building: $@'
	@echo ' '

HMU_ECU.hex: HMU_ECU.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex HMU_ECU.elf  "HMU_ECU.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: HMU_ECU.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 HMU_ECU.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) HMU_ECU.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
