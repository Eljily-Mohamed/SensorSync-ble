#PATH_TO_BIN = /local/sdk_elec/gcc-arm-none-eabi-5_2-2015q4/bin/


TARGET  = $(PATH_TO_BIN)arm-none-eabi-

CC      = $(TARGET)gcc
OBJCOPY = $(TARGET)objcopy
AS      = $(TARGET)gcc -x assembler-with-cpp -c
SIZE    = $(TARGET)size
OBJDUMP = $(TARGET)objdump

PROJECT_NAME = template

PROJECT_SRC = .
STM_SRC = _Libraries/STM32F4xx_HAL_Driver/Src/


vpath %.c $(PROJECT_SRC)
vpath %.c $(STM_SRC)

########################################################################

SRCS = Middlewares/ST/BlueNRG-MS/utils/ble_list.c
SRCS += Middlewares/ST/BlueNRG-MS/hci/hci_le.c
SRCS += Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/hci_tl.c
SRCS += Middlewares/ST/BlueNRG-MS/hci/controller/bluenrg_gap_aci.c
SRCS += Middlewares/ST/BlueNRG-MS/hci/controller/bluenrg_gatt_aci.c
SRCS += Middlewares/ST/BlueNRG-MS/hci/controller/bluenrg_hal_aci.c
SRCS += Middlewares/ST/BlueNRG-MS/hci/controller/bluenrg_l2cap_aci.c
SRCS += Middlewares/ST/BlueNRG-MS/hci/controller/bluenrg_updater_aci.c
SRCS += Middlewares/ST/BlueNRG-MS/hci/controller/bluenrg_utils_small.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
SRCS += Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
SRCS += Src/system_stm32f4xx.c
#SRCS += Src/app_x-cube-ble1.c
SRCS += Src/hci_tl_interface.c
SRCS += Src/main.c
SRCS += Src/sensor_service.c
SRCS += Src/stm32f4xx_hal_msp.c
SRCS += Src/stm32f4xx_it.c
SRCS += Src/stm32f4xx_nucleo.c
SRCS += Src/stm32f4xx_nucleo_bus.c
SRCS += SW4STM32/startup_stm32f411xe.s
SRCS += SW4STM32/syscalls.c

########################################################################

SRCS += Src/tcs34725.c
SRCS += Src/sht4x.c
SRCS += Src/drv_uart.c
SRCS += Src/drv_i2c.c

########################################################################

EXT_OBJ = $(EXT_SRCS:.c=.o)

INC_DIRS += Inc/
INC_DIRS += Middlewares/ST/BlueNRG-MS/includes/
# INC_DIRS += Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Template/
INC_DIRS += Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/
INC_DIRS += Middlewares/ST/BlueNRG-MS/utils/


INC_DIRS += Drivers/STM32F4xx_HAL_Driver/Inc/
INC_DIRS += Drivers/CMSIS/Device/ST/STM32F4xx/Include/
INC_DIRS += Drivers/CMSIS/Include/
INC_DIRS += Drivers/BSP/STM32F4xx-Nucleo/
INC_DIRS += Drivers/BSP/X-NUCLEO-IDB04A1
INC_DIRS += Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/includes
INC_DIRS += Middlewares/ST/STM32_BlueNRG/Interface
INC_DIRS += Drivers/BSP/X-NUCLEO-IDB0xA1
INC_DIRS += Drivers/BSP/X_NUCLEO_IKS01A1
INC_DIRS += Drivers/BSP/X_NUCLEO_IKS01A2
INC_DIRS += Drivers/BSP/Components/Common
INC_DIRS += Drivers/BSP/Components/hts221
INC_DIRS += Drivers/BSP/Components/lis3mdl
INC_DIRS += Drivers/BSP/Components/lps22hb
INC_DIRS += Drivers/BSP/Components/lps25hb
INC_DIRS += Drivers/BSP/Components/lsm303agr
INC_DIRS += Drivers/BSP/Components/lsm6ds0
INC_DIRS += Drivers/BSP/Components/lsm6ds3
INC_DIRS += Drivers/BSP/Components/lsm6dsl
INC_DIRS += Drivers/BSP/Components/lsm6dsm
INC_DIRS += Drivers/BSP/Components/stc3115
INC_DIRS += Drivers/BSP/X_NUCLEO_IKS01A1
INC_DIRS += Drivers/BSP/X_NUCLEO_IKS01A2


INCLUDE = $(addprefix -I,$(INC_DIRS))

DEFS = -DSTM32F411xE

CFLAGS  = -ggdb -O0 -fcommon

CFLAGS += -D ARM_MATH_CM4 -L 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -Wl,--gc-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -specs=nano.specs -fsingle-precision-constant

WFLAGS += -Wall -Wextra -Warray-bounds -Wno-unused-parameter

LFLAGS = -TDevice/gcc.ld -mfloat-abi=hard -lc -lgcc -lgcov -lm -Wl,-Map=$@.map



.PHONY: all
all: $(PROJECT_NAME)

.PHONY: $(PROJECT_NAME)
$(PROJECT_NAME): $(PROJECT_NAME).elf

$(PROJECT_NAME).elf: $(SRCS) $(EXT_OBJ)
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) $(WFLAGS) $(LFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJECT_NAME).elf   $(PROJECT_NAME).hex
	$(OBJCOPY) -O binary $(PROJECT_NAME).elf $(PROJECT_NAME).bin

%.o: %.c
	$(CC) -c -o $@ $(INCLUDE) $(DEFS) $(CFLAGS) $^

clean:
	rm -f *.o $(PROJECT_NAME).elf $(PROJECT_NAME).hex $(PROJECT_NAME).bin $(PROJECT_NAME).map

	
	
