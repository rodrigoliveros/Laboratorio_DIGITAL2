/*
 * SPI.h
 *
 * Created: 3/02/2026 16:50:52
 *  Author: rodri
 */ 

#include <avr/io.h>
#ifndef SPI_H_
#define SPI_H_
  typedef enum {
	  //Configuracion de SPI
	  SPIM_OSC2 = 0b01010000,
	  SPIM_OSC4 = 0b01010001,
	  SPIM_OSC8 = 0b01010010,
	  SPIM_OSC16 = 0b01010011,
	  SPIM_OSC32 = 0b01010100,
	  SPIM_OSC64 = 0b01010101,
	  SPIM_OSC128 = 0b01010110,
	  SPI_SLAVE_SS = 0b01000000
	  
  }SPI_type;

  typedef enum {
	  //division SPI
	  SPI_OSC2 = 0b01010000,
	  SPI_OSC4 = 0b01010001,
	  SPI_OSC8 = 0b01010010,
	  SPI_OSC16 = 0b01010011,
	  SPI_OSC32 = 0b01010100,
	  SPI_OSC64 = 0b01010101,
	  SPI_OSC128 = 0b01010110
	  
  }SPI_OSCd;

  typedef enum {
	  SPI_DORD_MSB = 0b00000000,
	  SPI_DORD_LSB = 0b00100000
  }order;

  typedef enum {
	  SPI_CLOCK_IDLE_HIGH = 0b00001000,
	  SPI_CLOCK_IDLE_LOW = 0b00000000
  }clockpola;
  
  typedef enum {
	  SPI_CLOCK_FIRST_EDGE = 0b00000000,
	  SPI_CLOCK_LAST_EDGE = 0b00000100
  }clokpha;
  
 void spiInit(SPI_type,order,clockpola,clokpha);
 uint8_t spiRead(void);




#endif /* SPI_H_ */