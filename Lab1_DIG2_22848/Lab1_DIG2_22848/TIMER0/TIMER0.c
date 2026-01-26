/*
 * TIMER0.c
 *
 * Created: 20/01/2026 18:00:58
 *  Author: rodri
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TIMER0.h"

volatile uint32_t tiempo_ms = 0;

void timer0_init(void)
{
	TCCR0A = (1 << WGM01); // Modo CTC
	TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler 64
	OCR0A = 249; // ~ 1 ms
	TIMSK0 = (1 << OCIE0A); // Habilitar interrupción
}
ISR(TIMER0_COMPA_vect)
{
	tiempo_ms++; // Aumentar cada 1 ms
}