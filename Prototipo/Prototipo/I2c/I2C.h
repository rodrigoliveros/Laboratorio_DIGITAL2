/*
 * I2C.h
 *
 * Created: 9/02/2026 23:28:21
 *  Author: Barbaritos
 */ 
#ifndef I2C_H_
#define I2C_H_

#ifndef	F_CPU
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
//Maestro
void initmaster(unsigned long SCL_Clock, uint8_t Prescaler); //Función para inicializar el master
uint8_t masterstart(void);
uint8_t masterrepeatedstart(void);
void masterstop(void);
uint8_t masterwrite(uint8_t dato);
uint8_t masterread(uint8_t *buffer, uint8_t ack);

//esclavo
void initslave(uint8_t SlaveAddress);

#endif /* I2C_H_ */