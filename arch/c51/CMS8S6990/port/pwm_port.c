#include "pwm_port.h"
#include "gpio_board.h"

uint8_t MM_pwm_init(void)
{
    //设置EPWM运行模式
    EPWM_ConfigRunMode(EPWM_WFG_INDEPENDENT | EPWM_OC_INDEPENDENT | EPWM_OCU_SYMMETRIC | EPWM_COUNT_DOWN); //独立模式+输出独立模式+对称计数模式+向下计数(边沿对齐)模式

    /*************PWM0***************/
    //设置EPWM运行时钟
    EPWM_ConfigChannelClk(EPWM0, EPWM_CLK_DIV_1); // Fsys/1

    //设置EPWM周期
    EPWM_ConfigChannelPeriod(EPWM0, 200); // 20KHz

    //占空比
    EPWM_ConfigChannelSymDuty(EPWM0, 0);

    //设置EPWM的加载方式为自动加载
    EPWM_EnableAutoLoadMode(EPWM_CH_0_MSK);

    //设置EPWM的输出极性
    EPWM_DisableReverseOutput(EPWM_CH_0_MSK); //关闭反向输出

    //设置EPWM输出
    EPWM_EnableOutput(EPWM_CH_0_MSK); //开启输出

    //设置EPWM死区
    // EPWM_DisableDeadZone(EPWM0);

    //设置EPWM中断
    // EPWM_EnableZeroInt(EPWM_CH_0_MSK);				//开启EPWM零点中断
    // EPWM_AllIntEnable();							//开启EPWM总中断
    // IRQ_SET_PRIORITY(IRQ_PWM,IRQ_PRIORITY_HIGH);
    // IRQ_ALL_ENABLE();								//开启总中断

    //设置EPWM输出IO复用
    GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_PG0);

    /*************PWM1***************/
    //设置EPWM运行时钟
    EPWM_ConfigChannelClk(EPWM1, EPWM_CLK_DIV_1); // Fsys/1

    //设置EPWM周期
    EPWM_ConfigChannelPeriod(EPWM1, 200); // 20KHz

    //占空比
    EPWM_ConfigChannelSymDuty(EPWM1, 0);

    //设置EPWM的加载方式为自动加载
    EPWM_EnableAutoLoadMode(EPWM_CH_1_MSK);

    //设置EPWM的输出极性
    EPWM_DisableReverseOutput(EPWM_CH_1_MSK); //关闭反向输出

    //设置EPWM输出
    EPWM_EnableOutput(EPWM_CH_1_MSK); //开启输出

    //设置EPWM输出IO复用
    GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_PG1);

    /***********************************************/
    //开启EPWM
    EPWM_Start(EPWM_CH_0_MSK | EPWM_CH_1_MSK);
		
	return 0;
}

uint8_t MM_pwm_exit(void)
{
	return 0;
}

void MM_pwm_start(void)
{
    EPWM_EnableOutput(EPWM_CH_0_MSK | EPWM_CH_1_MSK); //开启输出

    GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_PG0); //设置为PWM IO
    GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_PG1); //设置为PWM IO

    EPWM_Start(EPWM_CH_0_MSK | EPWM_CH_1_MSK); //开启计数
}

void MM_pwm_suspend(void)
{
    GPIO_SET_MUX_MODE(P03CFG, GPIO_MUX_GPIO); //设置为普通IO
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_3);
    MOTOR_PIN(0);
    GPIO_SET_MUX_MODE(P01CFG, GPIO_MUX_GPIO); //设置为普通IO
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_1);
    LED_PWM_PIN(0);
    
    EPWM_DisableOutput(EPWM_CH_0_MSK | EPWM_CH_1_MSK); //停止PWM输出
    EPWM_Stop(EPWM_CH_0_MSK | EPWM_CH_1_MSK); //停止PWM计数功能
}

/**********************************
 * period: PWM周期, 传入0XFFFF不改变状态
 * Duty: PWM占空比, 传入0XFFFF不改变状态
 * ******************************/
void MM_pwm0_set(uint16_t Period, uint16_t Duty)
{
    if ((PWMLOADEN & EPWM_CH_0_MSK) == 0)
    {
        if (Period != 0XFFFF)
        {
            PWMP0H = Period >> 8;
            PWMP0L = Period;
        }

        if (Duty != 0XFFFF)
        {
            PWMD0H = Duty >> 8;
            PWMD0L = Duty;
        }

        PWMLOADEN |= EPWM_CH_0_MSK; //通知PWM更新
    }
}

/**********************************
 * Duty: PWM占空比, 传入0XFFFF不改变状态
 * ******************************/
void MM_pwm0_set_duty(uint16_t Duty)
{
    if (Duty != 0XFFFF)
    {
        if ((PWMLOADEN & EPWM_CH_0_MSK) == 0)
        {
            PWMD0H = Duty >> 8;
            PWMD0L = Duty;
            PWMLOADEN |= EPWM_CH_0_MSK; //通知PWM更新
        }
    }
}

void MM_pwm1_set(uint16_t Period, uint16_t Duty)
{
    if ((PWMLOADEN & EPWM_CH_1_MSK) == 0)
    {
        if (Period != 0XFFFF)
        {
            PWMP1H = Period >> 8;
            PWMP1L = Period;
        }

        if (Duty != 0XFFFF)
        {
            PWMD1H = Duty >> 8;
            PWMD1L = Duty;
        }

        PWMLOADEN |= EPWM_CH_1_MSK; //通知PWM更新
    }
}

/**********************************
 * Duty: PWM占空比, 传入0XFFFF不改变状态
 * ******************************/
void MM_pwm1_set_duty(uint16_t Duty)
{
    if (Duty != 0XFFFF)
    {
        if ((PWMLOADEN & EPWM_CH_1_MSK) == 0)
        {
            PWMD1H = Duty >> 8;
            PWMD1L = Duty;
            PWMLOADEN |= EPWM_CH_1_MSK; //通知PWM更新
        }
    }
}

