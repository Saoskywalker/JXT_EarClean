#ifndef _PWM_BOARD_H
#define _PWM_BOARD_H

#include "pwm_port.h"

#define PWM_DUTY_0 0
#define PWM_DUTY_25 50
#define PWM_DUTY_40 80
#define PWM_DUTY_50 100
#define PWM_DUTY_75 150
#define PWM_DUTY_100 200

#define PWM_INIT() MM_pwm_init()
#define PWM_START() MM_pwm_start()
#define PWM_SUSPEND() MM_pwm_suspend()
#define PWM_MOTOR_SET_DUTY(x) MM_pwm0_set_duty(x)
#define PWM_LED_SET_DUTY(x) MM_pwm1_set_duty(x)

#endif
