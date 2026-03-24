/*
 * Laboratorio6_nano_228.c
 *
 * Created: 17/03/2026 15:49:48
 * Author : rodri
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>


volatile uint8_t ultimo_estado = 0xFF;
volatile uint8_t evento = 0;

void UART_init(void);
void UART_sendChar(char c);
void UART_sendNumber(uint8_t num);
void PCINT_init(void);

int main(void) {

	UART_init();
	PCINT_init();

	sei(); 

	while (1) {
		if (evento != 0) {
			UART_sendNumber(evento);
			evento = 0;
		}
	}
}

//Funciones
void PCINT_init() {
	
	//PB0–PB5 pullups
	DDRB &= ~0b00111111;
	PORTB |= 0b00111111;
	PCICR |= (1 << PCIE0); // habilitar interrupciones para puertob

	PCMSK0 |= (1 << PCINT0)|(1 << PCINT1)|(1 << PCINT2)|(1 << PCINT3)|(1 << PCINT4)|(1 << PCINT5);
}

//UART
void UART_init() {
	
	uint16_t ubrr = 16; //115200

	UCSR0A |= (1 << U2X0);  // Modo doble velocidad

	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;

	UCSR0B = (1 << TXEN0) | (1 << RXEN0); //Habilitar tx,rx
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //8 bits, no parity,stopbit
}

void UART_sendChar(char c) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void UART_sendNumber(uint8_t num) { //Convertir numero a ASCII
	UART_sendChar('0' + num); // simple (0–9);
}

//Interrupciones
ISR(PCINT0_vect) {
	uint8_t actual = PINB;
	uint8_t cambio = actual ^ ultimo_estado; //XOR para detectar que bit cambio

	for (uint8_t i = 0; i <= 5; i++) {
		if (cambio & (1 << i)) {
			// detectar flanco de bajada (botón presionado)
			if (!(actual & (1 << i))) {
				evento = i + 1; // botón 1–6
			}
		}
	}

	ultimo_estado = actual;
}

