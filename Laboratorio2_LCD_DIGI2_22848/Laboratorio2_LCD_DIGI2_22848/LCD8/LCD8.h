/*
 * LCD8.h
 *
 * Created: 27/01/2026 15:36:01
 *  Author: rodri
 */ 


#ifndef LCD8_H_
#define LCD8_H_
//Basado en la libreria vista en clase
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void initLCD8bits(void); //Funcion para inicializar
void LCD_Port(char a); // Funcion para colocar un valor
void LCD_CMD(char a); // Funcion para enviar un comando
void LCD_WC(char c); // Función para escribir un caracter
void LCD_WS(char *a); // Funcion para enviar una cadena
void LCD_SR(void); // Desplazamiento a la derecha
void LCD_SL(void); // Desplazamiento del cursor
void LCD_SC(char c, char f); // Establecer el cursor





#endif /* LCD8_H_ */