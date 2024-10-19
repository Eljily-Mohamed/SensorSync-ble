################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/subdir.mk
-include SW4STM32/.metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include SW4STM32/subdir.mk
-include Middlewares/ST/TimerServer/src/subdir.mk
-include Middlewares/ST/LowPowerManager/Src/subdir.mk
-include Middlewares/ST/BlueNRG-MS/utils/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Utils/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/time_server/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/time_client/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/proximity_reporter/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/proximity_monitor/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/hid_device/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/heart_rate/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/glucose_sensor/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/blood_pressure_sensor/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/ble_profile/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/alert_notification_server/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/alert_notification_client/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/Phone_Alert_Client/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/Health_Thermometer/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/Find_Me_Target/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Src/Find_Me_Locator/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Utils/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/time_server/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/time_client/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/proximity_reporter/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/proximity_monitor/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/phone_alert_status_server/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/hid_host/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/heart_rate_collector/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/health_thermometer_collector/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/glucose_collector/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/find_me_target/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/find_me_locator/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/blood_pressure_collector/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/ble_profile/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/alert_notification_server/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/Central/Src/alert_notification_client/subdir.mk
-include Middlewares/ST/BlueNRG-MS/profiles/ANCS/Src/subdir.mk
-include Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Template/subdir.mk
-include Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/subdir.mk
-include Middlewares/ST/BlueNRG-MS/hci/controller/subdir.mk
-include Middlewares/ST/BlueNRG-MS/hci/subdir.mk
-include Middlewares/ST/BlueNRG-MS/STM32L4xx_HAL_BlueNRG_Drivers/src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/Legacy/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/iar/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/arm/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/subdir.mk
-include Drivers/BSP/X-NUCLEO-IDB0xA1/subdir.mk
-include Drivers/BSP/STM32L4xx_Nucleo/subdir.mk
-include .metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := bleiot
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
bleiot.elf \

SIZE_OUTPUT += \
template.size.stdout \

OBJDUMP_LIST += \
bleiot.list \

OBJCOPY_BIN += \
bleiot.bin \


# All Target
all: main-build

# Main-build Target
main-build: bleiot.elf secondary-outputs

# Tool invocations
bleiot.elf: $(OBJS) $(USER_OBJS) /home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/LinkerScript.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "bleiot.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/LinkerScript.ld" --specs=nosys.specs -Wl,-Map="bleiot.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

template.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

bleiot.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "bleiot.list"
	@echo 'Finished building: $@'
	@echo ' '

bleiot.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "bleiot.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) bleiot.bin bleiot.elf bleiot.list template.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
