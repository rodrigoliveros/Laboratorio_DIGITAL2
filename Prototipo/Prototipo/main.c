/*
 * Prototipo.c
 *
 * Created: 10/02/2026 16:50:13
 * Author : rodri
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "I2c/I2C.h"

#define slave1 0x30
#define slave2 0x40

#define slave1R (0x30<<1)|0x01 //definicion de memoria cuando deseo leer
#define slave1W (0x30<<1) & 0b11111110 //definicion de memoria cuando deseo escribir

uint8_t direccion;
uint8_t temp;
uint8_t bufferI2C = 0;

void refreshPORT(uint8_t valor);
//MAIN master
int main(void)
{
	DDRD = 0xFF;
	DDRB |=(1<<DDB5);
	
	PORTB &= ~(1<<PORTB5);
	initmaster(100000,1);
	
    /* Replace with your application code */
    while (1)
	 
    {
		PORTB |=(1<<PORTB5);
		
		if (!masterstart()) return;
		
		if (!masterwrite(slave1W)){
			masterstop();
			return;
		}
		
		masterwrite('R');
		
		if (!masterrepeatedstart()){
			masterstop();
			return;
		}
		
		if (!masterwrite(slave1R)){
			masterstop();
			return;
		}
		
		masterread(&bufferI2C,0); //Nack
		//masterread(&bufferI2C1,1); //ack
		//masterread(&bufferI2C2,1); //ack
		//masterread(&bufferI2C3,0); //Nack
		
		masterstop();
		
		PORTB &=~(1<<PORTB5);
		
		refreshPORT(bufferI2C);
		_delay_ms(1000);
		
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