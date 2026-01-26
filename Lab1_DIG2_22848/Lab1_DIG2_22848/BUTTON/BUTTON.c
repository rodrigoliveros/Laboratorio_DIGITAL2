/*
 * BUTTON.c
 *
 * Created: 26/01/2026 13:02:23
 *  Author: rodri
 */ 
// Libreria creada con ayuda de ChatGPT con el fin de hacerla modular para cualquier pin del ArduinoNano
#include <avr/io.h>
#include "BUTTON.h"
#include "C:\Users\rodri\Documents\Atmel Studio\7.0\Lab1_DIG2_22848\Lab1_DIG2_22848\TIMER0\TIMER0.h"

#define TIEMPO_REBOTE 30 
void boton_init(boton_t *b, uint8_t pin)
{
	b->pin = pin;  // Guardamos el pin
	b->estado = 1; // Estado HIGH
	b->ultimo_tiempo = 0;
	DDRC &= ~(1 << pin); // Entrada
	PORTC |= (1 << pin); // Pull-up
}
uint8_t boton_actualizar(boton_t *b)
{
	uint8_t lectura = (PINC & (1 << b->pin)) ? 1 : 0;
	
	if (lectura != b->estado) {
		if ((tiempo_ms - b->ultimo_tiempo) >= TIEMPO_REBOTE) {
			b->estado = lectura;
			b->ultimo_tiempo = tiempo_ms;
			if (lectura == 0) {
				return 1; // Evento: botón presionado
			}
		}
	}
	return 0;
}
