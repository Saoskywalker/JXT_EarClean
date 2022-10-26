#ifndef _ADC_PORT_H
#define _ADC_PORT_H

#include "types_base.h"

//ADC vref define
#define MTF_ADC_VREF_VDD 4  /*Vref = Vdd*/
#define MTF_ADC_VREF_1P2V ADC_VREF_1P2V /*Vref =1.2v*/
#define MTF_ADC_VREF_2V ADC_VREF_2V   /*Vref =2.0v*/
#define MTF_ADC_VREF_2P4V ADC_VREF_2P4V /*Vref =2.4v*/
#define MTF_ADC_VREF_3V ADC_VREF_3V   /*Vref =3v*/

//ADC channel define
#define MTF_ADC_CH4 ADC_CH_4
#define MTF_ADC_CH5 ADC_CH_5
#define MTF_ADC_CH22 ADC_CH_22

uint8_t MM_adc1_init(void);
uint8_t MM_adc1_exit(void);
void MM_adc1_start(void);
void MM_adc1_suspend(void);
void MM_adc1_set_ref(uint8_t ref);
#define MM_adc1_set_channel(x) ADC_EnableChannel(x)
#define MM_adc1_convert_start() ADC_GO()
#define MM_adc1_get_state() ADC_IS_BUSY
#define MM_adc1_get_result() ADC_GetADCResult()

#endif
