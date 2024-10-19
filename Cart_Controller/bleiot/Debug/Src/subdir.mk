################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/drv_i2c.c \
../Src/drv_uart.c \
../Src/hci_tl_interface.c \
../Src/hts221.c \
../Src/lps22hb.c \
../Src/lps25hb.c \
../Src/lsm6ds0.c \
../Src/main.c \
../Src/sensor_service.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/stm32f4xx_nucleo.c \
../Src/stm32f4xx_nucleo_bus.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/drv_i2c.o \
./Src/drv_uart.o \
./Src/hci_tl_interface.o \
./Src/hts221.o \
./Src/lps22hb.o \
./Src/lps25hb.o \
./Src/lsm6ds0.o \
./Src/main.o \
./Src/sensor_service.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/stm32f4xx_nucleo.o \
./Src/stm32f4xx_nucleo_bus.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/drv_i2c.d \
./Src/drv_uart.d \
./Src/hci_tl_interface.d \
./Src/hts221.d \
./Src/lps22hb.d \
./Src/lps25hb.d \
./Src/lsm6ds0.d \
./Src/main.d \
./Src/sensor_service.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/stm32f4xx_nucleo.d \
./Src/stm32f4xx_nucleo_bus.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F411RETx -DNUCLEO_F411RE -DDEBUG -DSTM32F411xE -DUSE_HAL_DRIVER -c -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/HAL_Driver/Inc/Legacy" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/TimerServer/STM32xx_HAL_TimerServer_Drivers/inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/BlueNRG-MS/profiles/Peripheral/Inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/TimerServer/inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/BlueNRG-MS/utils" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Drivers/CMSIS/Include" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/BlueNRG-MS/STM32L4xx_HAL_BlueNRG_Drivers/inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/LowPowerManager/Inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Middlewares/ST/BlueNRG-MS/includes" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/Utilities/STM32F4xx-Nucleo" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/inc" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/CMSIS/device" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/CMSIS/core" -I"/home/kerhoas/WORKSPACE_WEB2/BLEIOT_/WORKSPACE_F411_BLEIOT_STM32CUBEIDE/bleiot/HAL_Driver/Inc" -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/drv_i2c.d ./Src/drv_i2c.o ./Src/drv_uart.d ./Src/drv_uart.o ./Src/hci_tl_interface.d ./Src/hci_tl_interface.o ./Src/hts221.d ./Src/hts221.o ./Src/lps22hb.d ./Src/lps22hb.o ./Src/lps25hb.d ./Src/lps25hb.o ./Src/lsm6ds0.d ./Src/lsm6ds0.o ./Src/main.d ./Src/main.o ./Src/sensor_service.d ./Src/sensor_service.o ./Src/stm32f4xx_hal_msp.d ./Src/stm32f4xx_hal_msp.o ./Src/stm32f4xx_it.d ./Src/stm32f4xx_it.o ./Src/stm32f4xx_nucleo.d ./Src/stm32f4xx_nucleo.o ./Src/stm32f4xx_nucleo_bus.d ./Src/stm32f4xx_nucleo_bus.o ./Src/system_stm32f4xx.d ./Src/system_stm32f4xx.o

.PHONY: clean-Src

