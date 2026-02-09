/*
 * SPI.c
 *
 * Created: 3/02/2026 16:51:07
 *  Author: rodri
 */ 
#include <avr/io.h>
#include "SPI.h"

void spiInit(SPI_type sType, order sDataOrder, clockpola sclockpola, clokpha sclockpha ){
	// PD2 = SS
	// PB3 = MOSI
	// PB4 = MISO
	// PB5 = SCK
	
	if (sType & (1 << MSTR)){ // SI MSTR
		DDRB |= (1<<DDB3)|(1<<DDB5)|(1<<DDB2);//MOSI,SCK,NEGADO_sS
		DDRB &= ~(1<<DDB4); // MISO
		SPCR |= (1<<MSTR); //MASTER
		
		uint8_t temp = sType & 0b00000111; //switchcase frecuencia osc
		switch(temp){
			case 0: //div2 
			SPCR &= ~((1<<SPR1)|(1<<SPR0));
			SPSR |= (1<<SPI2X);
			break;
			case 1: //div4
			SPCR &= ~((1<<SPR1)|(1<<SPR0));
			SPSR &= ~(1<<SPI2X);
			break;
			
			case 2: //div8
			SPCR |= (1<<SPR0);
			SPCR &= ~(1<<SPR1);
			SPSR |= (1<<SPI2X);
			break;
			
			case 3: //div16
			SPCR |= (1<<SPR0);
			SPCR &= ~(1<<SPR1);
			SPSR &= ~(1<<SPI2X);
			break;
			case 4: //div32
			SPCR &= ~(1<<SPR0);
			SPCR |= (1<<SPR1);
			SPSR |=(1<<SPI2X);
			break;
			case 5: //div64
			SPCR &= ~(1<<SPR0);
			SPCR |= (1<<SPR1);
			SPSR &= ~(1<<SPI2X);
			break;
			
			case 6: //div128
			SPCR |= ((1<<SPR1)|(1<<SPR0));
			SPSR &= ~(1<<SPI2X);
			break;		
		}
	}
	else { //if slave
		DDRB |= (1<<DDB4); //MISO
		DDRB &= ~((1<<DDB3)|(1<<DDB5)|(1<<DDB2)); //MOSI,SCK,SS
		SPCR &= ~(1<<MSTR); //SLAVE
	}
	SPCR |= (1<<SPE)|sDataOrder|sclockpola|sclockpha ; //enable
}	

uint8_t spiRead(void) {
	while (!(SPSR & (1<<SPIF))); //wait for data complete
	return(SPDR); //read the received data from buffer
	}//Read the recieved data