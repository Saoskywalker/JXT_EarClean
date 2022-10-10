#ifndef _GPIO_BOARD_H
#define _GPIO_BOARD_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "types_base.h"

/****************************
应用定义接口
*****************************/
//io定义
//key
#define KEY_1_PIN()  P24
#define KEY_2_PIN() P25

#define USB_CHECK() P26
#define MOTOR_PIN(x) P30 = x
#define CHARGE_CHECK() P31

#define COMDIG4_PIN(x) P23 = x
#define SEG_A_PIN(x) P22 = x
#define COMDIG1_PIN(x) P17 = x
#define SEG_B_PIN(x) P16 = x
#define SEG_C_PIN(x) P15 = x
#define SEG_D_PIN(x) P14 = x
#define COMDIG2_PIN(x) P13 = x
#define SEG_E_PIN(x) P00 = x
#define SEG_F_PIN(x) P01 = x
#define SEG_G_PIN(x) P02 = x
#define COMDIG3_PIN(x) P03 = x

void main_IO_init(void);
void main_IO_exit(void);
///////////////////////////////

#define TEST_TOGGLE_PIN() P23 = ~P23 //测试引脚, 翻转
#define TEST_PIN(x) P23 = x //测试引脚

void gpio_test(void);

#ifdef __cplusplus
}
#endif

#endif
