#ifndef _PWM_PORT_H
#define _PWM_PORT_H

#include "types_base.h"

uint8_t MM_pwm_init(void);
uint8_t MM_pwm_exit(void);
void MM_pwm_start(void);
void MM_pwm_suspend(void);
void MM_pwm0_set_duty(uint16_t Duty);
void MM_pwm1_set_duty(uint16_t Duty);

#endif
