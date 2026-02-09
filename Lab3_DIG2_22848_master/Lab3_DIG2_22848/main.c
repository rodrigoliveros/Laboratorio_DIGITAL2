/*
 * Lab3_DIG2_22848.c
 *
 * Created: 3/02/2026 16:38:28
 * Author : rodri
 */ 
// MAIN MASTER
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>


#include "SPI/SPI.h"


uint8_t contador = 0;

void refreshPORT(uint8_t valor);

//USARt
void USART_Init(unsigned int ubrr);
void USART_Transmit(char data);
uint8_t USART_Receive(void);


int main(void)
{
	cli();
	DDRD = 0xFF;
	DDRC = 0XFF;
	//slaveselect	
	DDRB |= (1<<DDB5)|(1<<DDB3)|(1<<DDB2); //MOSI,SLK, ss
	DDRB &= ~(1<<DDB4); //MISO
	spiInit(SPIM_OSC128,SPI_DORD_MSB,SPI_CLOCK_IDLE_LOW,SPI_CLOCK_FIRST_EDGE);// Debe de estar igual del lado del esclavo
	PORTB |= (1<<PB2); //(empezamos en 1 para que no seleccione al dispositivo esclavo)
	USART_Init(16);
	sei();
	
    while (1) 
    {
		
		//Recibir dato desde PC
		contador = USART_Receive();   // 0–255

		//Mostrar en LEDs 
		refreshPORT(contador);

		//Enviar dato
		PORTB &= ~(1<<PB2);           // SS = 0
		SPDR = contador;
		while(!(SPSR & (1<<SPIF)));
		PORTB |= (1<<PB2);            // SS = 1
		_delay_ms(250);
    }
}

// Funciones
void refreshPORT(uint8_t valor){ //leds
	//Inicializar
	if(valor & 0b10000000){
		PORTD |= (1<<PORTD7);
	}else{
		PORTD &= ~(1<<PORTD7);
	}
	if(valor & 0b01000000){
		PORTD |= (1<<PORTD6);
	}else{
		PORTD &= ~(1<<PORTD6);
	}
	if(valor & 0b00100000){
		PORTD |= (1<<PORTD5);
	}else{
		PORTD &= ~(1<<PORTD5);
	}
	if(valor & 0b00010000){
		PORTD |= (1<<PORTD4);
	}else{
		PORTD &= ~(1<<PORTD4);
	}
	if(valor & 0b00001000){
		PORTD |= (1<<PORTD3);
	}else{
		PORTD &= ~(1<<PORTD3);
	}
	if(valor & 0b00000100){
		PORTD |= (1<<PORTD2);
	}else{
		PORTD &= ~(1<<PORTD2);
	}
	if(valor & 0b00000010){
		PORTC |= (1<<PORTC1);
	}else{
		PORTC &= ~(1<<PORTC1);
	}
	if(valor & 0b00000001){
		PORTC |= (1<<PORTC0);
	}else{
		PORTC &= ~(1<<PORTC0);
	}
}
void USART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;

	UCSR0B = (1<<RXEN0)|(1<<TXEN0);   // RX y TX
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); // 8N1
}

void USART_Transmit(char data)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

uint8_t USART_Receive(void)
{
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}