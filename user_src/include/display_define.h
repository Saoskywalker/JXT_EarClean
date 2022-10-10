#ifndef _DISPLAY_DEFINE_H
#define _DISPLAY_DEFINE_H

#include "display_board.h"

/*****************************
 * 应用对应的led显存功能定义
 * **************************/
#define dig1_num LED_data_buf[0]
#define dig2_num LED_data_buf[1]
#define dig3_num LED_data_buf[2]

#define Dsp_RESlocate(X, N) (LED_data_buf[X] &= ~(N))
#define Dsp_locate(X, N) (LED_data_buf[X] |= (N))

#define low_locate Dsp_locate(3, bit5)
#define medium_locate Dsp_locate(3, bit2)
#define high_locate Dsp_locate(3, bit1)
#define pulse_locate Dsp_locate(3, bit3)
/////////////////////////////////////

//==============================================================================
//      3) 函数声明(对外接口)
//==============================================================================
void Led_display(void);
void Disp_All(void);
void dig1_2_dsp(uint8_t _disp_data);

#endif
