#include "timer_port.h"
#include "types_base.h"

//开启定时器
void MTF_timer_init_handle(void)
{
    //设置timer3
	/*
	(1)设置Timer的运行模式
	*/
	TMR_ConfigRunMode(TMR3, TMR_MODE_TIMING,TMR_TIM_AUTO_8BIT);	
	/*
	(2)设置Timer 运行时钟
	*/
	TMR_ConfigTimerClk(TMR3, TMR_CLK_DIV_4);						/*Fsys = 4Mhz，Ftimer = 1Mhz, Ttmr = 1us*/
	/*
	(3)设置Timer周期
	*/	
	TMR_ConfigTimerPeriod(TMR3, 256-200, 256-200); 				// 200*1us = 200us,递增计数, 8位自动重装模式下设置计算器和重装值
		
	/*
	(4)开启中断
	*/
	TMR_EnableOverflowInt(TMR3);

	/*
	(5)设置Timer中断优先级
	*/	
	IRQ_SET_PRIORITY(IRQ_TMR3,IRQ_PRIORITY_LOW);
	IRQ_ALL_ENABLE();	

	/*
	(6)开启Timer
	*/
	TMR_Start(TMR3);
}
