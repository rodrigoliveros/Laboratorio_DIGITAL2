/*
 * TIMER0.h
 *
 * Created: 20/01/2026 18:00:10
 *  Author: rodri
 */ 


#ifndef TIMER_0
#define TIMER_0
#include <stdint.h>

extern volatile uint32_t tiempo_ms;

void timer0_init(void);

#endif