/*
 * Lab3_DIG2_22848.c
 *
 * Created: 3/02/2026 16:38:28
 * Author : rodri
 */ 
// MAIN SLAVE
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SPI/SPI.h"

//Variables

uint8_t valueadc = 0x00;
volatile uint8_t adc_values[2];
volatile uint8_t adc_channel = 0; // 0 = ADC0, 1 = ADC1
volatile uint8_t adc0;
volatile uint8_t adc1;


uint8_t valorSPI = 0; //Enviar


void refreshPORT(uint8_t valor);



int main(void)
{
	//ADC
	cli();
	
	//SPI
	
	DDRB &= ~((1<<DDB5)|(1<<DDB3)|(1<<DDB2)); //MOSI,SLK
	DDRB |= (1<<DDB4); //MISO
	
	DDRD |= 0xFF;
	
	spiInit(SPI_SLAVE_SS,SPI_DORD_MSB,SPI_CLOCK_IDLE_LOW,SPI_CLOCK_FIRST_EDGE);// Debe de estar igual del lado del esclavo
	SPCR |= (1<<SPIE);
	sei();
	
    while (1) 
    {
		refreshPORT(valorSPI);
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

ISR(SPI_STC_vect)
{
	valorSPI = SPDR;   // Leer dato enviado por el master
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





