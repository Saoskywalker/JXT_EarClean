#ifndef _ADC_BOARD_H
#define _ADC_BOARD_H

#include "types_base.h"
#include "adc_port.h"

#define ADC_CHANNEL_TOTAL 3 //ADC需扫描通道数
extern uint16_t _adc_value[ADC_CHANNEL_TOTAL];
#define ADC_BATTERY_VALUE() _adc_value[0]
#define ADC_MOTOR_CURRENT_VALUE() _adc_value[1]
#define ADC_NTC_VALUE() _adc_value[2]

#define ADC_INIT() MM_adc1_init()
void adc_run(void);

#endif
