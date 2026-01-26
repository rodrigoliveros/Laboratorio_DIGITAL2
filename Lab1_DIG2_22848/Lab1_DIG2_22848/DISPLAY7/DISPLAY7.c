/*
 * DISPLAY7.c
 *
 * Created: 20/01/2026 17:18:57
 *  Author: rodri
 */ 
#include <avr/io.h>
#include "DISPLAY7.h"

static const uint8_t numeros[10] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111 // 9
};

void display_init(void){
	DDRD |= 0x7F; // PD0-PD6 SALIDA
	PORTD &= ~0x7F; // Comienza apagado
}

void display_mostrar(uint8_t numero)
{
	if (numero > 9) return;
	PORTD = (PORTD & 0x80) | numeros[numero];
}