#include "gpio_board.h"

void main_IO_init(void)
{
    #ifndef DEBUG
    //DSCK
    GPIO_SET_MUX_MODE(P21CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_1); //设置为输出(默认推挽)
	P21 = 0;

    //DSDA
    GPIO_SET_MUX_MODE(P35CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P3TRIS, GPIO_PIN_5); //设置为输出(默认推挽)
	P35 = 0;
    #endif

    //key1
    GPIO_SET_MUX_MODE(P24CFG, GPIO_MUX_GPIO); //设置为普通IO
    GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_4); //设置为输入
    GPIO_ENABLE_UP(P2UP, GPIO_PIN_4); //开上拉电阻

    //key2
    GPIO_SET_MUX_MODE(P25CFG, GPIO_MUX_GPIO); //设置为普通IO
    GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_5); //设置为输入(默认高阻)
    GPIO_ENABLE_UP(P2UP, GPIO_PIN_5);

    //vcc_ck
    GPIO_SET_MUX_MODE(P26CFG, GPIO_MUX_GPIO); //设置为普通IO
    GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_6); //设置为输入(默认高阻)
    GPIO_ENABLE_RD(P2RD, GPIO_PIN_6); //开下拉电阻

    //pwm(正常工作时配置为PWM输出, 睡眠为普通IO, 软件操作)
    GPIO_SET_MUX_MODE(P30CFG, GPIO_MUX_GPIO);
	GPIO_ENABLE_OUTPUT(P3TRIS, GPIO_PIN_0);
	P30 = 0;	

    //CHG
    GPIO_SET_MUX_MODE(P31CFG, GPIO_MUX_GPIO); //设置为普通IO
    GPIO_ENABLE_INPUT(P3TRIS, GPIO_PIN_1); //设置为输入(默认高阻)
    GPIO_ENABLE_UP(P3UP, GPIO_PIN_1); //开上拉电阻

    //COM4
    GPIO_SET_MUX_MODE(P23CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_3); //设置为输出(默认推挽)
	P23 = 0;

    //SEG6
    GPIO_SET_MUX_MODE(P22CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_2); //设置为输出(默认推挽)
	P22 = 0;

    //COM1
    GPIO_SET_MUX_MODE(P17CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_7); //设置为输出(默认推挽)
	P17 = 0;

    //SEG3
    GPIO_SET_MUX_MODE(P16CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_6); //设置为输出(默认推挽)
	P16 = 0;

    //SEG2
    GPIO_SET_MUX_MODE(P15CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_5); //设置为输出(默认推文)
	P15 = 0;

    //SEG4
    GPIO_SET_MUX_MODE(P14CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_4); //设置为输出(默认推文)
	P14 = 0;

    //COM2
    GPIO_SET_MUX_MODE(P13CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_3); //设置为输出(默认推文)
	P13 = 0;

    //SEG5
    GPIO_SET_MUX_MODE(P00CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_0); //设置为输出(默认推文)
	P00 = 0;

    //SEG1
    GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_1); //设置为输出(默认推文)
	P01 = 0;

    //SEG7
    GPIO_SET_MUX_MODE(P02CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_2); //设置为输出(默认推文)
	P02 = 0;

    //COM3
    GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_GPIO); //设置为普通IO
	GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_3); //设置为输出(默认推文)
	P03 = 0;

    /*
    (2)设置外部中断
    */
    GPIO_SET_INT_MODE(P24EICFG, GPIO_INT_RISING); //设置为上升沿中断模式
    GPIO_EnableInt(GPIO2, GPIO_PIN_4_MSK);        //开启P24中断

    GPIO_SET_INT_MODE(P25EICFG, GPIO_INT_RISING); //设置为上升沿中断模式
    GPIO_EnableInt(GPIO2, GPIO_PIN_5_MSK);        //开启P25中断

    GPIO_SET_INT_MODE(P26EICFG, GPIO_INT_RISING); //设置为上升沿中断模式
    GPIO_EnableInt(GPIO2, GPIO_PIN_6_MSK);        //开启P26中断

    /*
    (3)设置PORT2外部中断中断优先级
    */
    IRQ_SET_PRIORITY(IRQ_P2, IRQ_PRIORITY_LOW);
}

//睡眠前设置gpio
void main_IO_exit(void)
{
    MOTOR_PIN(0);
    COMDIG4_PIN(0);
    SEG_A_PIN(0);
    COMDIG1_PIN(0);
    SEG_B_PIN(0);
    SEG_C_PIN(0);
    SEG_D_PIN(0);
    COMDIG2_PIN(0);
    SEG_E_PIN(0);
    SEG_F_PIN(0);
    SEG_G_PIN(0);
    COMDIG3_PIN(0);
}
