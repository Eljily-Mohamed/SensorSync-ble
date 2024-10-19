#include "tcs34725.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"

tcs34725IntegrationTime_t _tcs34725IntegrationTime = TCS34725_INTEGRATIONTIME_700MS;
tcs34725Gain_t _tcs34725Gain = TCS34725_GAIN_1X;

void write8(uint8_t reg, uint8_t value) {
    uint8_t data[2];
    data[0] = TCS34725_COMMAND_BIT | reg;
    data[1] = value & 0xFF;

    if (i2c1_WriteBuffer(TCS34725_ADDRESS, data, sizeof(data)) != 0)
    {
        printf("\n\r Erreur lors de l'écriture dans I2C\n");
        return;
    }
}

uint8_t read8(uint8_t reg) {
    uint8_t value;

    uint8_t reg_data[1] = { TCS34725_COMMAND_BIT | reg };

    if (i2c1_WriteBuffer(TCS34725_ADDRESS, reg_data, 1) != 0) {
        printf("\n\rErreur lors de l'écriture dans le registre\n");
        return 0;
    }

    if (i2c1_ReadBuffer(TCS34725_ADDRESS, &value, 1)!=0) {
        printf("\n\rErreur lors de la lecture d'octets\n");
        return 0;
    }

    return value;
}

uint16_t read16(uint8_t reg) {
    uint16_t x;

    uint8_t reg_data[1] = { TCS34725_COMMAND_BIT | reg };
    if (i2c1_WriteBuffer(TCS34725_ADDRESS, reg_data, 1) != 0) {
        printf("\n\rErreur lors de l'écriture dans le registre\n");
        return 0;
    }

    uint8_t data[2];
    if (i2c1_ReadBuffer(TCS34725_ADDRESS, data, 2) != 0) {
        printf("\n\rErreur lors de la lecture d'octets\n");
        return 0;
    }

    x = data[1];
    x <<= 8;
    x |= data[0];

    return x;
}

void enable(void) {
    write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);

    HAL_Delay(1);

    write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
}

void setIntegrationTime(tcs34725IntegrationTime_t it) {
    write8(TCS34725_ATIME, it);
}

void setGain(tcs34725Gain_t gain) {
    write8(TCS34725_CONTROL, gain);
    _tcs34725Gain = gain;
}

void tcs34725_init(void) {
    i2c1_Init();
    uint8_t id = read8(TCS34725_ID);
    if ((id != 0x44) && (id != 0x10)) {
        printf("\n\rErreur: ID Incorrect\n");
        return;
    }

    tcs34725_config_t config = {
        .enable = TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN,
        .integration_time = TCS34725_INTEGRATIONTIME_700MS,
        .gain = TCS34725_GAIN_1X
    };

    write8(TCS34725_ENABLE, config.enable);
    write8(TCS34725_ATIME, config.integration_time);
    write8(TCS34725_CONTROL, config.gain);

    // delay_us(SAMPLING_PERIOD);

    //uart_puts(_USART2, "\n\rTCS34725 I2C Color Sensor bien initialisé\n");
    return;
}

void tcs34725_read_color(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear) {
    *clear = read16(TCS34725_CDATAL);
    *red = read16(TCS34725_RDATAL);
    *green = read16(TCS34725_GDATAL);
    *blue = read16(TCS34725_BDATAL);
    printf("READ DATA");

    uint8_t atime_reg = read8(TCS34725_ATIME);
    uint16_t integration_time = (256 - atime_reg) * 2.4;

    switch (integration_time) {
    		case 2: // 2.4 ms
            	HAL_Delay(2.4);
                break;
            case 24: // 24 ms
            	HAL_Delay(24);
                break;
            case 50: // 50 ms
            	HAL_Delay(50);
                break;
            case 101: // 101 ms
            	HAL_Delay(101);
                break;
            case 154: // 154 ms
            	HAL_Delay(154);
                break;
            case 700: // 700 ms
            	HAL_Delay(700);
                break;
            default:
                break;
    }
}

float calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b, float *x, float *y) {
    float X, Y, Z;
    float XYZ_sum;

    X = (-0.14282f * r + 1.54924f * g - 0.95641f * b);
	Y = (-0.32466f * r + 1.57837f * g - 0.73191f * b);
	Z = (-0.68202f * r + 0.77073f * g + 0.56332f * b);

    XYZ_sum = X + Y + Z;
    if (XYZ_sum != 0) {
        *x = X / XYZ_sum;
        *y = Y / XYZ_sum;
    } else {
        *x = 5000; // Valeur par défaut
        *y = 5000; // Valeur par défaut
    }

    float n = (*x - 0.3320f) / (0.1858f - *y);

    // Calculer cct
    float cct = ((437 * n * n * n) + (3601 * n * n) + (6861 * n) + 5517);
    return cct;
}

float calculateLux(uint16_t r, uint16_t g, uint16_t b) {
    float illuminance;

    illuminance = (-0.32466f * r) + (1.57837f * g) + (-0.73191f * b);

    return (uint16_t)illuminance;
}
