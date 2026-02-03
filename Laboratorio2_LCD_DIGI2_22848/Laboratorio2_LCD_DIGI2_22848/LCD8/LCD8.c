/*
 * LCD8.c
 *
 * Created: 27/01/2026 15:36:35
 *  Author: rodri
 */ 
//Basado en la libreria vista en clase
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "LCD8.h"

void initLCD8bits(void){
	DDRC |= (1<<DDC3) | (1<<DDC4);
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	DDRB |= (1<<DDB0)|(1<<DDB1);
	
	_delay_ms(20);
	LCD_CMD(0x30);
	_delay_ms(5);
	LCD_CMD(0x30);
	_delay_ms(11);
	LCD_CMD(0x30);
	_delay_ms(11);
	LCD_CMD(0x38);
	_delay_ms(5);
	LCD_CMD(0x0C);
	_delay_ms(5);
	LCD_CMD(0x06);
	_delay_ms(5);
	LCD_CMD(0x01);
	} //Funcion para inicializar
	
void LCD_Port(char a){
	if (a & 1)
	PORTD |= (1<<PORTD2);
	else
	PORTD &= ~(1<<PORTD2);
	if (a & 2)
	PORTD |= (1<<PORTD3);
	else
	PORTD &= ~(1<<PORTD3);
	if (a & 4)
	PORTD |= (1<<PORTD4);
	else
	PORTD &= ~(1<<PORTD4);
	if (a & 8)
	PORTD |= (1<<PORTD5);
	else
	PORTD &= ~(1<<PORTD5);
	if (a & 16)
	PORTD |= (1<<PORTD6);
	else
	PORTD &= ~(1<<PORTD6);
	if (a & 32)
	PORTD |= (1<<PORTD7);
	else
	PORTD &= ~(1<<PORTD7);
	if (a & 64)
	PORTB |= (1<<PORTB0);
	else
	PORTB &= ~(1<<PORTB0);
	if (a & 128)
	PORTB |= (1<<PORTB1);
	else
	PORTB &= ~(1<<PORTB1);
	} // Funcion para colocar un valor

void LCD_CMD(char a){
	//
	PORTC &= ~(1<<PORTC3);
	LCD_Port(a);
	PORTC |= (1<<PORTC4);
	_delay_ms(4);
	PORTC &= ~(1<<PORTC4);
	} // Funcion para enviar un comando
void LCD_WC(char c){
	PORTC |= (1<<PORTC3);
	LCD_Port(c);
	PORTC |= (1<<PORTC4);
	_delay_ms(5);
	PORTC &= ~(1<<PORTC4);
	
	}// Función para escribir un caracter
void LCD_WS(char *a){
	
	int i;
	for (i = 0; a[i] != '\0'; i++)
	LCD_WC(a[i]);
	
	}// Funcion para enviar una cadena
void LCD_SR(void){
	
	} // Desplazamiento a la derecha
void LCD_SL(void){
	
	} // Desplazamiento del cursor
void LCD_SC(char fila, char columna)
{
	char address = 0x80;

	if (fila == 1)
	{
		address = 0x80 + (columna - 1);
	}
	else if (fila == 2)
	{
		address = 0xC0 + (columna - 1);
	}

	LCD_CMD(address);
}
