/*
 * Proyecto_MASTER.c
 *
 * Created: 18/02/2026 18:32:09
 * Author : rodri
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdlib.h>

#include "I2C/I2C.h"
#include "BME280/bme280_mini.h"
#include "LCD8/LCD8.h"

#define SLAVE_SENSORS 0x30
#define SLAVE_ACTUATORS 0x40

#define AIR_THRESHOLD 100

uint8_t aire = 0;
uint8_t luz = 0;
int16_t temperatura = 0;

uint8_t dc = 0;
uint8_t stepper = 0;
uint8_t servo = 0;

uint8_t readSensorsSlave(void);
uint8_t sendActuatorsSlave(uint8_t dc, uint8_t stepper, uint8_t servo);
void processLogic(void);
void LCD_Update(void);

int main(void)
{
    initmaster(100000,1);
    initLCD8bits();
    BME280_Init();

    BME280_ReadTemperature();  // ignorar primera lectura
    _delay_ms(200);

    while (1)
    {
        int32_t temp_raw = BME280_ReadTemperature();
        temperatura = temp_raw / 100;

        if (temperatura < 20)
            continue;

        if (!readSensorsSlave())
            continue;

        processLogic();
        sendActuatorsSlave(dc, stepper, servo);

        LCD_Update();

        _delay_ms(1000);
    }
}

uint8_t readSensorsSlave(void)
{
    if (!masterstart())
        return 0;

    if (!masterwrite((SLAVE_SENSORS<<1) & 0xFE))
    {
        masterstop();
        return 0;
    }

    if (!masterrepeatedstart())
    {
        masterstop();
        return 0;
    }

    if (!masterwrite((SLAVE_SENSORS<<1) | 0x01))
    {
        masterstop();
        return 0;
    }

    if (!masterread(&aire,1))
    {
        masterstop();
        return 0;
    }

    if (!masterread(&luz,0))
    {
        masterstop();
        return 0;
    }

    masterstop();
    return 1;
}

void processLogic(void)
{
    bool aire_malo = (aire >= AIR_THRESHOLD);
    bool es_dia = (luz == 0);

    uint8_t nivel_temp;

    if (temperatura < 25)
        nivel_temp = 0;
    else if (temperatura < 30)
        nivel_temp = 1;
    else
        nivel_temp = 2;

    if (aire_malo)
    {
        dc = 0x01;
        servo = 0x02;
        stepper = 0x01;
        return;
    }

    if (es_dia)
    {
        stepper = 0x01;

        if (nivel_temp == 0) { servo = 0x00; dc = 0x00; }
        else if (nivel_temp == 1) { servo = 0x01; dc = 0x00; }
        else { servo = 0x02; dc = 0x01; }
    }
    else
    {
        stepper = 0;

        if (nivel_temp == 0) { servo = 0x00; dc = 0x00; }
        else if (nivel_temp == 1) { servo = 0x01; dc = 0x00; }
        else { servo = 0x02; dc = 0x01; }
    }
}

uint8_t sendActuatorsSlave(uint8_t dc_val, uint8_t stepper_val, uint8_t servo_val)
{
    if (!masterstart())
        return 0;

    if (!masterwrite((SLAVE_ACTUATORS<<1) & 0xFE))
    {
        masterstop();
        return 0;
    }

    if (!masterwrite(dc_val))
    {
        masterstop();
        return 0;
    }

    if (!masterwrite(stepper_val))
    {
        masterstop();
        return 0;
    }

    if (!masterwrite(servo_val))
    {
        masterstop();
        return 0;
    }

    masterstop();
    return 1;
}

void LCD_Update(void)
{
    char buffer[10];

    LCD_CMD(0x01);  // limpiar
    _delay_ms(2);

    // Línea 1
    LCD_SC(1,1);
    LCD_WS("T:");
    itoa(temperatura, buffer, 10);
    LCD_WS(buffer);
    LCD_WS("C ");

    LCD_WS("A:");
    itoa(aire, buffer, 10);
    LCD_WS(buffer);

    // Línea 2
    LCD_SC(2,1);

    if (luz == 0)
        LCD_WS("LUZ ");
    else
        LCD_WS("NO LUZ ");

    if (aire >= AIR_THRESHOLD)
        LCD_WS("MALO");
    else
        LCD_WS("BUENO");
}
