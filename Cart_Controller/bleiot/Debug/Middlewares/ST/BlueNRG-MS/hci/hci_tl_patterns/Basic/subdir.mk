################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/hci_tl.c 

OBJS += \
./Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/hci_tl.o 

C_DEPS += \
./Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/hci_tl.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/%.o: ../Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/%.c Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F411RETx -DNUCLEO_F411RE -DDEBUG -DSTM32F411xE -DUSE_HAL_DRIVER -c -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/HAL_Driver/Inc/Legacy" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/TimerServer/STM32xx_HAL_TimerServer_Drivers/inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/TimerServer/inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/BlueNRG-MS/utils" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Drivers/CMSIS/Include" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/BlueNRG-MS/STM32L4xx_HAL_BlueNRG_Drivers/inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/LowPowerManager/Inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/BlueNRG-MS/includes" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Utilities/STM32F4xx-Nucleo" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/CMSIS/device" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/CMSIS/core" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/HAL_Driver/Inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-BlueNRG-2d-MS-2f-hci-2f-hci_tl_patterns-2f-Basic

clean-Middlewares-2f-ST-2f-BlueNRG-2d-MS-2f-hci-2f-hci_tl_patterns-2f-Basic:
	-$(RM) ./Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/hci_tl.d ./Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/hci_tl.o

.PHONY: clean-Middlewares-2f-ST-2f-BlueNRG-2d-MS-2f-hci-2f-hci_tl_patterns-2f-Basic

