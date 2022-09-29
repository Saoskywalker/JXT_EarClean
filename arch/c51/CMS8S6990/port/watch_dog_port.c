#include "watch_dog_port.h"

void MTF_watch_dog_init(void)
{
	/*
	(1)喂狗，避免WDT时间太短，进入WDT复位
	*/
	WDT_ClearWDT();
	/*
	(2)开启WDT溢出时间
	*/
	WDT_ConfigOverflowTime(WDT_CLK_1048576);	// Fsys=4Mhz -> Twdt = 131072/4 = 32.768ms
	SYS_EnableWDTReset(); //开启WDT复位
	// SYS_DisableWDTReset();

	/*
	(3)设置WDT溢出中断
	*/
	// WDT_EnableOverflowInt();

	// IRQ_SET_PRIORITY(IRQ_WDT, IRQ_PRIORITY_HIGH);
	// IRQ_ALL_ENABLE();
	
	
}
