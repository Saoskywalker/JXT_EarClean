#ifndef _DELAY_H
#define _DELAY_H

#include <types_base.h>

void delay(volatile uint32_t ms);
void delay_us(volatile uint16_t us);
void delay_ms(volatile uint32_t ms);

#endif
