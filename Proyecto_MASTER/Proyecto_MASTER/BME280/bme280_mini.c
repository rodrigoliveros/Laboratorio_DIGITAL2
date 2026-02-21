/*
 * bme280_mini.c
 *
 * Created: 19/02/2026 04:42:44
 *  Author: rodri*/

 #include "bme280_mini.h"
 #include "../I2C/I2C.h"

 static uint16_t dig_T1;
 static int16_t dig_T2;
 static int16_t dig_T3;

 static void BME280_ReadCalibration(void)
 {
	 uint8_t calib[6];

	 masterstart();
	 masterwrite(BME280_ADDR_W);
	 masterwrite(0x88);

	 masterrepeatedstart();
	 masterwrite(BME280_ADDR_R);

	 for (uint8_t i = 0; i < 6; i++)
	 masterread(&calib[i], (i < 5));

	 masterstop();

	 dig_T1 = (calib[1] << 8) | calib[0];
	 dig_T2 = (calib[3] << 8) | calib[2];
	 dig_T3 = (calib[5] << 8) | calib[4];
 }


 void BME280_Init(void)
 {
	 _delay_ms(100);

	 // Esperar fin de copia NVM
	 uint8_t status;
	 do {
		 masterstart();
		 masterwrite(BME280_ADDR_W);
		 masterwrite(0xF3);
		 masterrepeatedstart();
		 masterwrite(BME280_ADDR_R);
		 masterread(&status, 0);
		 masterstop();
	 } while (status & 0x01);

	 BME280_ReadCalibration();

	 // Modo NORMAL, temp oversampling x1
	 masterstart();
	 masterwrite(BME280_ADDR_W);
	 masterwrite(0xF4);
	 masterwrite(0x27);
	 masterstop();

	 _delay_ms(10);
 }


 int32_t BME280_ReadTemperature(void)
 {
	 uint8_t data[3];
	 int32_t adc_T;
	 int32_t var1, var2, t_fine, T;

	 masterstart();
	 masterwrite(BME280_ADDR_W);
	 masterwrite(0xFA);

	 masterrepeatedstart();
	 masterwrite(BME280_ADDR_R);

	 for (uint8_t i = 0; i < 3; i++)
	 masterread(&data[i], (i < 2));

	 masterstop();

	 adc_T = ((int32_t)data[0] << 12) |
	 ((int32_t)data[1] << 4)  |
	 ((int32_t)data[2] >> 4);

	 var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) *
	 ((int32_t)dig_T2)) >> 11;

	 var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) *
	 ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) *
	 ((int32_t)dig_T3)) >> 14;

	 t_fine = var1 + var2;

	 T = (t_fine * 5 + 128) >> 8;

	 return T;   // temperatura
	 
 }

