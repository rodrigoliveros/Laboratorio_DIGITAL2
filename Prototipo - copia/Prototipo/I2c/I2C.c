/*
 * I2C.c
 *
 * Created: 9/02/2026 23:28:37
 *  Author: Barbaritos
 */ 
#include "I2C.h"

void initmaster(unsigned long SCL_Clock, uint8_t Prescaler)
{
	DDRC &= ~((1<<DDC4)|(1<<DDC5)); //SA y SCL
	//Seleccinoar el valor de los bits para el prescaler TWSR
	switch(Prescaler){
		case 1:
			TWSR &= ~((1<<TWPS1)|(1<<TWPS0));
			break;
		case 4:
			TWSR &= ~((1<<TWPS1));
			TWSR |= (1<<TWPS0);
			break;
		case 16:
			TWSR &= ~((1<<TWPS0));
			TWSR |= (1<<TWPS1);
			break;
		case 64:
			TWSR |= (1<<TWPS1)|(1<<TWPS0);
			break;
		default:
			TWSR &= ~((1<<TWPS1)|(1<<TWPS0));
			Prescaler = 1;
			break;
		
	}
	TWBR = (((F_CPU/SCL_Clock)-16)/(2*Prescaler)); // Calcular la velocidad
	TWCR |= (1<<TWEN); //Activar I2C
}

uint8_t masterstart()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //Master, limpiar bandera de int, iniciar start iniciar interface
	while (!(TWCR&(1<<TWINT)));//eSPERAMOS QUE SE ENCIENDA LA BANDERA
	return ((TWSR & 0xF8) == 0x08); //Nos quedamos con los bits de estado(¿qué paso?)
}

uint8_t masterrepeatedstart()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);//Master, limpiar bandera de int, iniciar start iniciar interface
	while (!(TWCR&(1<<TWINT)));//eSPERAMOS QUE SE ENCIENDA LA BANDERA
	return ((TWSR & 0xF8) == 0x10);  //Nos quedamos con los bits de estado(¿qué paso?)
}

void masterstop()
{
		TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO); // Inicia el envio de secuencia de parada
		while (TWCR	& (1<<TWSTO)); //esperamos a que se haga la secuencia de start
}

uint8_t masterwrite(uint8_t dato)
{
	uint8_t estado;
	
	TWDR = dato; //Dato que me estan enviando
	
	TWCR = (1<<TWEN)|(1<<TWINT); //Inicia la secuencia de envio
	
	while(!(TWCR & (1<< TWINT))); // esperamos bandera de interrupcion
	estado = TWSR & 0XF8; //SOlo nos quedamos con los bits de estado(vemos el estado)
	
	if (estado == 0x18 || estado == 0x28)
	{
		return 1;
	}else
	{
		return estado;
	}
}

uint8_t masterread(uint8_t *buffer, uint8_t ack)
{
	uint8_t estado;
	if (ack)
	{
		// ACK: se desea seguir leyendo.
		TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWEA); //LIMPIO INTERRUPT, I2C ENABLE, Envio de ack automatico
	} else{
		//Ultimo byte, NACK
		TWCR= (1<<TWINT)|(1<<TWEN); //LIMPIO INTERRUPT, I2C ENABLE, ya no envio ack
	}
	while (!(TWCR&(1<<TWINT))); //esperamos a que suceda la comunicaci n
	
	estado= TWSR & 0xF8; //vemos que estado viene.
	//vemos si viene con ACK o NACK
	if (ack && estado != 0x50) return 0; //Dato recibido, ACK, Si no es ninguno de estos 2 mandamos 0
	if (!ack && estado!= 0x58) return 0; //Dato recibido, NACK
	
	*buffer = TWDR; //Dato recibido a Buffer
	return 1; // s todo bien guardamos los datos y return 1
}



//Inicializar Esclavo

void initslave(uint8_t SlaveAddress)
{
	DDRC &= ~((1<<DDC4)|(1<<DDC5)); //Pines I2c como entradas
	TWAR = SlaveAddress <<1; //nombre o direccion sin general call
	//TWAR = (address <<1 |0x01); //se asigna la direccion que tendra y habilita llamada general
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN)|(1<<TWIE); //Habilitamos I2C,ACK automatico, ISR habilitadas
}