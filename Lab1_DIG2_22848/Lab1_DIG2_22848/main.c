#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "TIMER0/TIMER0.h"
#include "BUTTON/BUTTON.h"
#include "DISPLAY7/DISPLAY7.h"
// ---------------- MÁQUINA DE ESTADOS ----------------
typedef enum {
	ESTADO_ESPERA,
	ESTADO_CUENTA_REGRESIVA,
	ESTADO_CARRERA
} estado_t;
estado_t estado = ESTADO_ESPERA;
// ---------------- VARIABLES ----------------
uint8_t cuenta = 5; // Muestra en display
uint32_t tiempo_anterior = 0;
boton_t boton_inicio;
boton_t boton_j1;
boton_t boton_j2;
uint8_t contador_j1 = 0; // Conteo J1
uint8_t contador_j2= 0; // Conteo J2

const uint8_t patron_leds[4] = {
	0b0001, // 1
	0b0010, // 2
	0b0100, // 3
	0b1000 // 4
};

uint32_t tiempo_mux = 0;
uint8_t jugador_activo = 0; // 0 = J1, 1 = J2
// ---------------- MAIN ----------------
void salidas_init(void){
	// ---------- CONFIGURACIÓN DE SALIDAS PARA LEDs ----------
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3); // Datos LEDs
	DDRB |= (1 << PB4); // Transistor J1
	DDRC |= (1 << PC0); // Transistor J2


	// Apagar todo al inicio
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3) | (1 << PB4));
	PORTC &= ~(1 << PC0);
}
void multiplexar_leds(void)
{
	if ((tiempo_ms - tiempo_mux) >= 1) {
		tiempo_mux = tiempo_ms;

		// 1. Apagar ambos jugadores
		PORTB &= ~(1 << PB4);
		PORTC &= ~(1 << PC0);

		// 2. Limpiar datos
		PORTB &= 0xF0;

		// 3. Cargar datos del jugador correspondiente
		if (jugador_activo == 0) {
			PORTB |= patron_leds[contador_j1];
			PORTB |= (1 << PB4);   // habilitar J1
			jugador_activo = 1;
			} else {
			PORTB |= patron_leds[contador_j2];
			PORTC |= (1 << PC0);   // habilitar J2
			jugador_activo = 0;
		}
	}
}
int main(void)
{
	cli();
	salidas_init();
	display_init();
	timer0_init();
	boton_init(&boton_inicio, PC1);
	boton_init(&boton_j1, PC2); // J1
	boton_init(&boton_j2, PC3); // J2
	contador_j1 = 0;
	contador_j2 = 0;
	display_mostrar(0);
	sei();
	while (1)
	{
		multiplexar_leds();
		switch (estado) {
			
			case ESTADO_ESPERA:
			if (boton_actualizar(&boton_inicio)) {
				cuenta = 5;
				display_mostrar(cuenta);
				tiempo_anterior = tiempo_ms;
				estado = ESTADO_CUENTA_REGRESIVA;
			}
			break;
			
			case ESTADO_CUENTA_REGRESIVA:
			if ((tiempo_ms - tiempo_anterior) >= 1000) {
				tiempo_anterior = tiempo_ms;
				if (cuenta > 0) {
					cuenta--;
					display_mostrar(cuenta);
					} else {
					estado = ESTADO_CARRERA;
				}
			}
			break;
			
			case ESTADO_CARRERA:

			if (boton_actualizar(&boton_j1)) {
				if (contador_j1 < 3) {
					contador_j1++;
				}
			}

			if (boton_actualizar(&boton_j2)) {
				if (contador_j2 < 3) {
					contador_j2++;
				}
			}
			
			// META
			if (contador_j1 == 3 || contador_j2 == 3) {
				contador_j1 = 0;
				contador_j2 = 0;
				estado = ESTADO_ESPERA;
			}

			break;
		}
	}
}