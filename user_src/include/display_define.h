#ifndef _DISPLAY_DEFINE_H
#define _DISPLAY_DEFINE_H

#include "display_board.h"

/*****************************
 * 应用对应的led显存功能定义
 * **************************/
#define LED_LIGHT_GRADUAL(x) LED_data_buf[1] = x

#define Dsp_RESlocate(X, N) (LED_data_buf[X] &= ~(N))
#define Dsp_locate(X, N) (LED_data_buf[X] |= (N))

#define led1_locate Dsp_locate(0, bit0)
#define led2_locate Dsp_locate(0, bit1)
#define led3_locate Dsp_locate(0, bit2)
#define red_locate Dsp_locate(0, bit3)
#define green_locate Dsp_locate(0, bit4)
#define blue_locate Dsp_locate(0, bit5)

/////////////////////////////////////

//==============================================================================
//      3) 函数声明(对外接口)
//==============================================================================
void Led_display(void);
void Disp_All(void);
void dig1_2_dsp(uint8_t _disp_data);

#endif
