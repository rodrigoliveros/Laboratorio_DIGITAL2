/*
 * BUTTON.h
 *
 * Created: 26/01/2026 13:03:24
 *  Author: rodri
 */ 
// Libreria creada con ayuda de ChatGPT con el fin de hacerla modular para cualquier pin del ArduinoNano
#ifndef BUTTON_H
#define BUTTON_H
#include <stdint.h>
typedef struct {
	uint8_t pin;
	uint8_t estado;
	uint32_t ultimo_tiempo;
} boton_t;

void boton_init(boton_t *b, uint8_t pin);

uint8_t boton_actualizar(boton_t *b);
#endif /* BUTTON_H_ */