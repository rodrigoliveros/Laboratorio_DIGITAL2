/*
 * Prototipo.c
 *
 * Created: 10/02/2026 16:50:13
 * Author : rodri
 */ 
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "I2c/I2C.h"

#define slaveAdress 0x30


//Variables
uint8_t buffer = 0;

uint8_t valueadc = 0x00;

volatile uint8_t adc_values[2];
volatile uint8_t adc_channel = 0; // 0 = ADC0, 1 = ADC1
volatile uint8_t adc0;
volatile uint8_t adc1;


void refreshPORT(uint8_t valor);

void SETUPADC(void);
void ADC_Select(uint8_t channel);

int main(void)
{
	//ADC
	cli();
	DDRD = 0xFF;
	DDRB |= (1<<DDB5);
	PORTB &= ~(1<<PORTB5);
	
	SETUPADC();
	initslave(slaveAdress);
	
	sei();
	
	while (1)
	{
		if(buffer == 'R'){
			PINB |=(1<<PINB5);
			buffer = 0;
		}
		ADCSRA |= (1<<ADSC); // primera lectura
		refreshPORT(adc0);
		_delay_ms(100);
		
	}
}

// Interrupciones
ISR(ADC_vect)
{
	static uint8_t canal = 0;

	if (canal == 0)
	{
		adc0 = ADCH;                 // ADC0, 8 bits
		ADMUX = (ADMUX & 0xF0) | 1;  // cambiar a ADC1
		canal = 1;
	}
	else
	{
		adc1 = ADCH;                 // ADC1, 8 bits
		ADMUX = (ADMUX & 0xF0) | 0;  // volver a ADC0
		canal = 0;
	}

	ADCSRA |= (1<<ADSC);             // nueva conversión
}

// Funciones

void refreshPORT(uint8_t valor){ //leds
	//Inicializar
	DDRD = 0xFF;
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
		PORTD |= (1<<PORTD1);
		}else{
		PORTD &= ~(1<<PORTD1);
	}
	if(valor & 0b00000001){
		PORTD |= (1<<PORTD0);
		}else{
		PORTD &= ~(1<<PORTD0);
	}
}

void ADC_Select(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
}

void SETUPADC(void)
{
	ADMUX = (1<<REFS0) | (1<<ADLAR);   // AVcc, 8 bits
	ADC_Select(0);              // Empezar en ADC0

	ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // Prescaler 128
}

ISR(TWI_vect){
	uint8_t estado = TWSR & 0xF8; // Nos quedamos unicamente con los bits mas significativos
	switch(estado){
		//Slave debe de recibir dato
		case 0x60: //SLA + W recibido
		case 0x70: //General call
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;
		case 0x80: //Dato recibido, ack enviado
		case 0x90: //Dato recibido General Call, ack enviado
			buffer = TWDR;
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;
		//Slave debe de transmitir datos
		case 0xA8: //SLA+R recibido
		case 0xB8: // dato transmitido, ack recibido
			TWDR = adc0; //dato a enviar
			//Como mandar 3 bites, teniendo una variable de indice
			//Entonces si es el indice 0 mandamos la primera variable
			// e incrementamos el indice
			// entonces en este case siempre revisamos en que indice estamos
			// dependiendo del indice mandamos algo u otro.
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;
		case 0xC0: //dato transimitido, NACK recibido
		case 0xC8: // ultimo dato transmitido
			
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA)|(1<<TWIE);
			break;
		case 0xA0: // stop o repeated start recibido como slave
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;
		default:
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);
			break;
	}
}

