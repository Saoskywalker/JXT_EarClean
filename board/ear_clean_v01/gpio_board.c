#include "gpio_board.h"

void main_IO_init(void)
{
    #ifndef DEBUG
    //DSCK/led-g
    GPIO_SET_MUX_MODE(P21CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_1); //设置为输出(默认推挽)
	P21 = 0;

    //DSDA/prog
    GPIO_SET_MUX_MODE(P35CFG, GPIO_MUX_GPIO); //设置为普通IO
	CHRG_CURRENT_SET_LOW();
    #endif

    //motor-pwm(正常工作时配置为PWM输出, 睡眠为普通IO, 软件操作)
    GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_GPIO);
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_3);
	P03 = 0;	

    //5V-EN
    GPIO_SET_MUX_MODE(P02CFG, GPIO_MUX_GPIO);
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_2);
	P02 = 1; //开启升压

    //led-pwm(正常工作时配置为PWM输出, 睡眠为普通IO, 软件操作)
    GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_GPIO);
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_1);
	P01 = 0;

    //led-r
    GPIO_SET_MUX_MODE(P22CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_2); //设置为输出(默认推挽)
	P22 = 0;

    //led-com
    GPIO_SET_MUX_MODE(P23CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_3); //设置为输出(默认推挽)
	P23 = 0;

    //SW-G
    GPIO_SET_MUX_MODE(P24CFG, GPIO_MUX_GPIO); //设置为普通IO
    GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_4); //设置为输入(默认高阻)
    GPIO_ENABLE_UP(P2UP, GPIO_PIN_4); //开上拉电阻

    //led-b
    GPIO_SET_MUX_MODE(P26CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_6); //设置为输出(默认推挽)
	P26 = 0;

    //adc-key(正常设为ad按键, 睡眠时设为普通IO输入用于唤醒)
    GPIO_SET_MUX_MODE(P30CFG, GPIO_MUX_GPIO); //设置为普通IO
    GPIO_ENABLE_INPUT(P3TRIS, GPIO_PIN_0); //设置为输入(默认高阻)
    // GPIO_ENABLE_UP(P3UP, GPIO_PIN_0); //开上拉电阻

    //stdby
    GPIO_SET_MUX_MODE(P31CFG, GPIO_MUX_GPIO); //设置为普通IO
    GPIO_ENABLE_INPUT(P3TRIS, GPIO_PIN_1); //设置为输入(默认高阻)
    GPIO_ENABLE_UP(P3UP, GPIO_PIN_1); //开上拉电阻

    //CHG
    GPIO_SET_MUX_MODE(P32CFG, GPIO_MUX_GPIO); //设置为普通IO
    GPIO_ENABLE_INPUT(P3TRIS, GPIO_PIN_2); //设置为输入(默认高阻)
    GPIO_ENABLE_UP(P3UP, GPIO_PIN_2); //开上拉电阻

    /*
    (2)设置外部中断
    */
    GPIO_SET_INT_MODE(P30EICFG, GPIO_INT_BOTH_EDGE); //设置为双沿中断模式
    GPIO_EnableInt(GPIO3, GPIO_PIN_0_MSK);        //开启P30中断

    GPIO_SET_INT_MODE(P31EICFG, GPIO_INT_BOTH_EDGE); //设置为双沿中断模式
    GPIO_EnableInt(GPIO3, GPIO_PIN_1_MSK);        //开启P31中断

    GPIO_SET_INT_MODE(P32EICFG, GPIO_INT_BOTH_EDGE); //设置为双沿中断模式
    GPIO_EnableInt(GPIO3, GPIO_PIN_2_MSK);        //开启P32中断

    /*
    (3)设置PORT3外部中断中断优先级
    */
    IRQ_SET_PRIORITY(IRQ_P3, IRQ_PRIORITY_LOW);
}

//睡眠前设置gpio
void main_IO_exit(void)
{
 MOTOR_PIN(0);
 EN_5V_PIN(0);

 LED_PWM_PIN(0);

#ifndef DEBUG
 LED_G_PIN(0);
 LED_R_PIN(0);
 CHARGE_PROG_PIN(0);
#endif

 LED_COM_PIN(0);
 LED_B_PIN(0);
}
