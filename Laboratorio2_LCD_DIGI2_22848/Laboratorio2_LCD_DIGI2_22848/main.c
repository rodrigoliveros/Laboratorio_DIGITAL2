/*
 * Laboratorio2_LCD_DIGI2_22848.c
 *
 * Created: 27/01/2026 15:35:22
 * Author : rodri
 */ 
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "LCD8/LCD8.h"

//Variables

uint8_t valueadc = 0x00;
volatile uint8_t adc_values[2];
volatile uint8_t adc_channel = 0; // 0 = ADC0, 1 = ADC1
volatile uint8_t adc8 = 0;     // POT1 (0–255)
volatile uint16_t adc10 = 0;   // POT2 (0–1023)
//ADC

void SETUPADC(void);
void ADC_Select(uint8_t channel);
void SETUPADC(void)
{
	ADMUX = (1<<REFS0) | (1<<ADLAR);   // AVcc, 8 bits
	ADC_Select(0);              // Empezar en ADC0

	ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // Prescaler 128
}



void ADC_Select(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
}
// Funcion realizada con ayuda de ChatGPT
float convertADC(uint8_t valueadc);
void enviarV(uint8_t adc);

float convertADC(uint8_t valueadc)
{
	return (valueadc * 5.0) / 255.0;
}



void enviarV(uint8_t adc)
{
	char buffer[8];
	float voltage;

	voltage = convertADC(adc);

	dtostrf(voltage, 4, 2, buffer);  // "5"

	LCD_WS(buffer);
	LCD_WS("V ");
}


 //Interrupcion ADC
 

ISR(ADC_vect)
{
	static uint8_t canal = 0;

	if (canal == 0)
	{
		adc8 = ADCH;          // 8 bits
		ADMUX &= ~(1<<MUX0);  // cambiar a ADC1
		ADMUX |= (1<<MUX0);
		ADMUX &= ~(1<<ADLAR); // 10 bits
		canal = 1;
	}
	else
	{
		uint8_t low = ADCL;
		uint8_t high = ADCH;
		adc10 = (high << 8) | low;

		ADMUX &= ~(1<<MUX0);  //  ADC0
		ADMUX |= (1<<ADLAR);  // 8 bits
		canal = 0;
	}

	ADCSRA |= (1<<ADSC);
}

int main(void)
{
	cli();
	SETUPADC();
	initLCD8bits();
	sei();

	ADCSRA |= (1<<ADSC); // primera lectura

	while (1)
	{
		LCD_SC(1,1);
		LCD_WS("P1: ");
		enviarV(adc8);

		char buffer[6];
		itoa(adc10, buffer, 10);

		LCD_SC(2,1);
		LCD_WS("P2: ");
		LCD_WS(buffer);

		_delay_ms(200);
	}
}


