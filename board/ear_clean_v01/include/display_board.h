#ifndef _DISPLAY_BOARD_H
#define _DISPLAY_BOARD_H

#include "types_plus.h"
#include "gpio_board.h"

//==============================================================================
//      数码管定义
//==============================================================================
//数码管显示数据定义
#define BIT_A bit6 //          A
#define BIT_B bit7 //       -------
#define BIT_C bit0 //      |       |
#define BIT_D bit2 //    F |       |  B
#define BIT_E bit1 //       ---G---
#define BIT_F bit4 //      |       |  C
#define BIT_G bit5 //    E |       |
#define BIT_P bit3 //       ---D---   P
/******************************************************************************
 *         数码管显示代码定义
 *******************************************************************************/
#define DATA_0 BIT_A | BIT_B | BIT_C | BIT_D | BIT_E | BIT_F
#define DATA_1 BIT_B | BIT_C
#define DATA_2 BIT_A | BIT_B | BIT_D | BIT_E | BIT_G
#define DATA_3 BIT_A | BIT_B | BIT_C | BIT_D | BIT_G
#define DATA_4 BIT_B | BIT_C | BIT_F | BIT_G
#define DATA_5 BIT_A | BIT_C | BIT_D | BIT_F | BIT_G
#define DATA_6 BIT_A | BIT_C | BIT_D | BIT_E | BIT_F | BIT_G
#define DATA_7 BIT_A | BIT_B | BIT_C
#define DATA_8 BIT_A | BIT_B | BIT_C | BIT_D | BIT_E | BIT_F | BIT_G
#define DATA_9 BIT_A | BIT_B | BIT_C | BIT_D | BIT_F | BIT_G
#define DATA_A BIT_A | BIT_B | BIT_C | BIT_E | BIT_F | BIT_G
#define DATA_b BIT_C | BIT_D | BIT_E | BIT_F | BIT_G
#define DATA_C BIT_A | BIT_D | BIT_E | BIT_F
#define DATA_E BIT_A | BIT_D | BIT_E | BIT_F | BIT_G
#define DATA_F BIT_A | BIT_E | BIT_F | BIT_G
#define DATA_I BIT_E | BIT_F
#define DATA_i BIT_E
#define DATA_n BIT_A | BIT_B | BIT_C | BIT_E | BIT_F
#define DATA_o BIT_C | BIT_D | BIT_E | BIT_G
#define DATA_t BIT_D | BIT_E | BIT_F | BIT_G
#define DATA_e BIT_A | BIT_D | BIT_E | BIT_F | BIT_G
#define DATA_U BIT_B | BIT_C | BIT_D | BIT_E | BIT_F
#define DATA_P BIT_A | BIT_B | BIT_E | BIT_F | BIT_G
#define DATA_L BIT_D | BIT_E | BIT_F
#define DATA_H BIT_B | BIT_C | BIT_E | BIT_F | BIT_G
#define DATA_r BIT_E | BIT_G
#define DATA_neg BIT_G
#define DATA_M1 BIT_A | BIT_B | BIT_E | BIT_F
#define DATA_M2 BIT_A | BIT_B | BIT_C | BIT_F
#define DATA_NON 0
//------------------------

/****************************
应用定义接口
*****************************/
//数码管引脚
#define SEG_A_PIN_ON SEG_A_PIN(0)
#define SEG_A_PIN_OFF SEG_A_PIN(1)

#define SEG_B_PIN_ON SEG_B_PIN(0)
#define SEG_B_PIN_OFF SEG_B_PIN(1)

#define SEG_C_PIN_ON SEG_C_PIN(0)
#define SEG_C_PIN_OFF SEG_C_PIN(1)

#define SEG_D_PIN_ON SEG_D_PIN(0)
#define SEG_D_PIN_OFF SEG_D_PIN(1)

#define SEG_E_PIN_ON SEG_E_PIN(0)
#define SEG_E_PIN_OFF SEG_E_PIN(1)

#define SEG_F_PIN_ON SEG_F_PIN(0)
#define SEG_F_PIN_OFF SEG_F_PIN(1)

#define SEG_G_PIN_ON SEG_G_PIN(0)
#define SEG_G_PIN_OFF SEG_G_PIN(1)

#define SEG_H_PIN_ON
#define SEG_H_PIN_OFF

/*LED COM*/
#define COMDIG1_PIN_ON COMDIG1_PIN(1) // COM1
#define COMDIG1_PIN_OFF COMDIG1_PIN(0)

#define COMDIG2_PIN_ON COMDIG2_PIN(1) // COM2
#define COMDIG2_PIN_OFF COMDIG2_PIN(0)

#define COMDIG3_PIN_ON COMDIG3_PIN(1) // COM3
#define COMDIG3_PIN_OFF COMDIG3_PIN(0)

#define COMDIG4_PIN_ON COMDIG4_PIN(1) // COM4
#define COMDIG4_PIN_OFF COMDIG4_PIN(0)

//COM通道数量
#define LED_COM_TOTAL 4
////////////////////////////////////////

extern uint8_t LED_data[LED_COM_TOTAL]; //数码管显示输出缓存;
extern uint8_t LED_data_buf[LED_COM_TOTAL]; //LED显示data
void Led_Dis_Update(void);
void Led_Clear_All(void);
void Led_Scan(void);
uint8_t Led_Display_exit(void);
uint8_t Led_Display_init(void);

#endif
