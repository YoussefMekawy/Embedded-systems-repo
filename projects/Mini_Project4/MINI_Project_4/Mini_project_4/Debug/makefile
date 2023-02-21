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
Mini_project_4.lss \

FLASH_IMAGE += \
Mini_project_4.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Mini_project_4.elf secondary-outputs

# Tool invocations
Mini_project_4.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Mini_project_4.map -mmcu=atmega32 -o "Mini_project_4.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Mini_project_4.lss: Mini_project_4.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Mini_project_4.elf  >"Mini_project_4.lss"
	@echo 'Finished building: $@'
	@echo ' '

Mini_project_4.hex: Mini_project_4.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Mini_project_4.elf  "Mini_project_4.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Mini_project_4.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Mini_project_4.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Mini_project_4.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
