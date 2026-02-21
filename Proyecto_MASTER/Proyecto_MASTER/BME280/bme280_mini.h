/*
 * bme280_mini.h
 *
 * Created: 19/02/2026 04:42:23
 *  Author: rodri
 */ 


#ifndef BME280_MINI_H_
#define BME280_MINI_H_
#ifndef	F_CPU
#define F_CPU 16000000
#endif
#include <stdint.h>
#include <util/delay.h>

// Dirección I2C (0x76 o 0x77)
#define BME280_ADDR        0x76
#define BME280_ADDR_W      ((BME280_ADDR<<1) & 0xFE)
#define BME280_ADDR_R      ((BME280_ADDR<<1) | 0x01)

// Inicializa el sensor
void BME280_Init(void);

// Retorna temperatura en °C enteros
int32_t BME280_ReadTemperature(void);

#endif /* BME280_MINI_H_ */