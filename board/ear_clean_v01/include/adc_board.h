#ifndef _ADC_BOARD_H
#define _ADC_BOARD_H

#include "types_base.h"
#include "adc_port.h"

//ADC channel define
#define MTF_ADC_BATTERY MTF_ADC_CH5
#define MTF_ADC_MOTOR_CURRENT MTF_ADC_CH4
#define MTF_ADC_KEY MTF_ADC_CH22

#define ADC_CHANNEL_TOTAL 3 //ADC需扫描通道数
extern uint16_t _adc_value[ADC_CHANNEL_TOTAL];
#define ADC_BATTERY_VALUE() _adc_value[0]
#define ADC_MOTOR_CURRENT_VALUE() _adc_value[1]
#define ADC_KEY_VALUE() _adc_value[2]

void adc_run(void);

#endif
