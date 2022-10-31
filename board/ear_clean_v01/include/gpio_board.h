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
#define KEY_ADC_PIN()  P30

//input
#define SW_G_PIN() P24
#define IC4056_CHRG_PIN() P31
#define IC4056_STDBY_PIN() P32

//output
#define MOTOR_PIN(x) P03 = x
#define EN_5V_PIN(x) P02 = x

#define LED_PWM_PIN(x) P01 = x

#define LED_G_PIN(x) P21 = x
#define LED_R_PIN(x) P22 = x
#define CHARGE_PROG_PIN(x) P35 = x

#define LED_COM_PIN(x) P23 = x
#define LED_B_PIN(x) P26 = x

#define LED_1TO4_ALL_OFF() {GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_1); LED_G_PIN(0); GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_2); LED_R_PIN(0); GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_3); LED_COM_PIN(0); GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_6); LED_B_PIN(0);}
#define LED_1TO4_ALL_SLEEP() {GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_1); LED_G_PIN(0); GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_2); LED_R_PIN(0); GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_3); LED_COM_PIN(0); GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_6); LED_B_PIN(0);}

#define LED1_ON() {GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_6); LED_B_PIN(1); GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_3); LED_COM_PIN(0);}
#define LED2_ON() {GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_6); LED_B_PIN(1); GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_2); LED_COM_PIN(0);}
#define LED3_ON() {GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_6); LED_B_PIN(1); GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_1); LED_G_PIN(0);}
#define LED4_R_ON() {GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_3); LED_COM_PIN(1); GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_6); LED_B_PIN(0);}
#define LED4_G_ON() {GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_3); LED_COM_PIN(1); GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_1); LED_G_PIN(0);}
#define LED4_B_ON() {GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_3); LED_COM_PIN(1); GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_2); LED_R_PIN(0);}

// #define COMDIG4_PIN(x) P23 = x
// #define SEG_A_PIN(x) P22 = x
// #define COMDIG1_PIN(x) P17 = x
// #define SEG_B_PIN(x) P16 = x
// #define SEG_C_PIN(x) P15 = x
// #define SEG_D_PIN(x) P14 = x
// #define COMDIG2_PIN(x) P13 = x
// #define SEG_E_PIN(x) P00 = x
// #define SEG_F_PIN(x) P01 = x
// #define SEG_G_PIN(x) P02 = x
// #define COMDIG3_PIN(x) P03 = x

#define CHRG_CURRENT_SET_HIGH() GPIO_ENABLE_OUTPUT(P3TRIS, GPIO_PIN_5); CHARGE_PROG_PIN(0) //输出为低, 以减少编程电阻
#define CHRG_CURRENT_SET_LOW() GPIO_ENABLE_INPUT(P3TRIS, GPIO_PIN_5) //设为输入, 以加大编程电阻

void main_IO_init(void);
void main_IO_exit(void);
///////////////////////////////

#define TEST_TOGGLE_PIN() P22 = ~P22 //测试引脚, 翻转
#define TEST_PIN(x) P22 = x //测试引脚

void gpio_test(void);

#ifdef __cplusplus
}
#endif

#endif
