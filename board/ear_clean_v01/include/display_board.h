#ifndef _DISPLAY_BOARD_H
#define _DISPLAY_BOARD_H

#include "types_plus.h"
#include "gpio_board.h"

#define LED_DATA_SIZE 2 //显示内存大小, 以字节为单位

extern uint8_t LED_data[LED_DATA_SIZE]; //数码管显示输出缓存;
extern uint8_t LED_data_buf[LED_DATA_SIZE]; //LED显示data
void Led_Dis_Update(void);
void Led_Clear_All(void);
void Led_dis_All(void);
void Led_Scan(void);
uint8_t Led_Display_exit(void);
uint8_t Led_Display_init(void);

#endif
