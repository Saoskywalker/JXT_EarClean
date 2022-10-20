#include "EarClean_global.h"
#include "types_plus.h"
#include "gpio_board.h"
#include "pwm_board.h"
#include "adc_board.h"
// #include "stdio.h"
#include "uart_board.h"
#include "timer_port.h"
#include "watch_dog_port.h"
#include "display_define.h"
#include "envent_define.h"
#include "EarClean_timer.h"
#include "ad_table.h"

EarClean_flag_type EarClean_flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t EarClean_mode = MODE_A;
uint8_t EarClean_battery_level = BATTERY_FULL;

static uint8_t sleep_updata = 0; //用于标记在唤醒后一段时间内, 进行一定的唤醒处理

/*****************************
 * 电机控制输出
 * ********************************/
static void motor_function(void)
{
	static uint8_t pulse_count = 0, new_mode = 0;

	if (EarClean_flag.work)
	{
		if (new_mode == MODE_A)
		{
			if(++pulse_count>=80)
			{
				pulse_count = 0;
				if(new_mode!=EarClean_mode)
				{
					new_mode = EarClean_mode;
					return;
				}
			}
			if (pulse_count>=40)
				PWM_MOTOR_SET_DUTY(PWM_DUTY_25);
			else
				PWM_MOTOR_SET_DUTY(PWM_DUTY_75);
		}
		else if (new_mode == MODE_B)
		{
			if(++pulse_count>=60)
			{
				pulse_count = 0;
				if(new_mode!=EarClean_mode)
				{
					new_mode = EarClean_mode;
					return;
				}
			}
			if (pulse_count>=30)
				PWM_MOTOR_SET_DUTY(PWM_DUTY_25);
			else
				PWM_MOTOR_SET_DUTY(PWM_DUTY_75);
		}
		else if (new_mode == MODE_C)
		{
			if(++pulse_count>=40)
			{
				pulse_count = 0;
				if(new_mode!=EarClean_mode)
				{
					new_mode = EarClean_mode;
					return;
				}
			}
			if (pulse_count>=20)
				PWM_MOTOR_SET_DUTY(PWM_DUTY_25);
			else
				PWM_MOTOR_SET_DUTY(PWM_DUTY_75);
		}
		else
		{
			if(++pulse_count>=20)
			{
				pulse_count = 0;
				if(new_mode!=EarClean_mode)
				{
					new_mode = EarClean_mode;
					return;
				}
			}
			if (pulse_count>=10)
				PWM_MOTOR_SET_DUTY(PWM_DUTY_25);
			else
				PWM_MOTOR_SET_DUTY(PWM_DUTY_75);
		}
	}
	else
	{
		PWM_MOTOR_SET_DUTY(PWM_DUTY_0);
		pulse_count = 0;
	}
}

/*************************************************
//名称        :	F_C
//功能        : F转换为C
//入口参数    :	无
//出口参数    :	无

原始公式 四舍五入
(X-32)*5/9+0.5
优化公式
((X-32)*10+9)/18
**************************************************/
static int8_t F_C(int8_t cfdata)
{
	int8_t a = 0;
	// if (cfdata > 32)
	{
		a = ((cfdata - 32) * 10 + 9) / 18;
	}
	// else
	// {
	// 	a = ((32 - cfdata) * 10 + 9) / 18;
	// }
	return a;
}

/*************************************************
//名称        :	C_F
//功能        : C转换为F
//入口参数    :	无
//出口参数    :	无
原公式为 四舍五入:  F=C*9/5+32+0.5
**************************************************/
static int8_t C_F(int8_t cfdata)
{
	int8_t a = 0;
	a = (cfdata * 18 + 5) / 10 + 32;
	return a;
}

/***************************************
 * 二分法查表
 * ************************************/
static uint16_t ADC_lookup(uint16_t value, uint16_t *ptr, uint16_t tab_leng)
{
	uint16_t low, high, mid, x, y;
	low = 0;
	mid = 0;
	high = tab_leng - 1;
	if (value <= *ptr)
		return low;
	if (value >= *(ptr + high))
		return high;
	//
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (*(ptr + mid) == value)
			return mid;
		else if (*(ptr + mid) > value)
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (value < *(ptr + mid))
	{
		x = *(ptr + mid) - value;
		y = value - *(ptr + mid - 1);
		if (x <= y)
			return mid;
		else
			return mid - 1;
	}
	else
	{
		x = *(ptr + mid + 1) - value;
		y = value - *(ptr + mid);
		if (x <= y)
			return mid + 1;
		else
			return mid;
	}
}

/*************************************************
 // 函数名称    : temp_deal
 // 功能描述    : 温度转换
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
ADC_PARA water_temp = {25, 77, 2048, AD_NORMAL};
static void temp_deal(void)
{
	static uint8_t Temp_Err_Cont = 0;
	static uint16_t cnt_delay = 0;

	if (EarClean_flag.sys_ready)
	{
		if (++cnt_delay < 50) //延迟更新温度 0.5s
			return;
		cnt_delay = 0;
	}

	if ((ADC_NTC_VALUE() > 4000))
	{
		if (++Temp_Err_Cont >= 2)
		{
			Temp_Err_Cont = 0;
			water_temp.status = AD_CUT;
			EarClean_flag.ntc_error = 1;
			water_temp.C_value = -128;
			water_temp.value = -128;
		}
	}
	else if ((ADC_NTC_VALUE() < 100))
	{
		if (++Temp_Err_Cont >= 2)
		{
			Temp_Err_Cont = 0;
			water_temp.status = AD_SHORT;
			EarClean_flag.ntc_error = 1;
			water_temp.C_value = -128;
			water_temp.value = -128;
		}
	}
	else
	{
		Temp_Err_Cont = 0;
		water_temp.status = AD_NORMAL;
		EarClean_flag.ntc_error = 0;

		//表从0C开始, 表为下拉电阻, 但实际电路为上拉电阻
		water_temp.C_value = (int8_t)ADC_lookup(4096-ADC_NTC_VALUE(), TempC_tab_10k_3435, sizeof(TempC_tab_10k_3435)/sizeof(uint16_t));
        water_temp.value = C_F((int8_t)water_temp.C_value);
	}
}

static void battery_deal(void)
{
	// Vref=3, 分压为1/2, Vin = 2*AD*3/4096+0.5(四舍五入), AD = (Vin)*4096/6+0.5(四舍五入)
	// Vin = ((ADC_BATTERY_VALUE()>>4)*300+256)/1280

	if (EarClean_flag.sys_ready == 0 || sleep_updata)
	{
		if (ADC_BATTERY_VALUE() >= 4000) //voltage over high
		{
			EarClean_battery_level = BATTERY_HIGH;
		}
		else if (ADC_BATTERY_VALUE() >= 2662) // 3.9V
		{
			EarClean_battery_level = BATTERY_FULL;
		}
		else if (ADC_BATTERY_VALUE() >= 2560) // 3.75V
		{
			EarClean_battery_level = BATTERY_LV2;
		}
		else if (ADC_BATTERY_VALUE() >= 2389) // 3.5V
		{
			EarClean_battery_level = BATTERY_LV1;
		}
		else if (ADC_BATTERY_VALUE() >= 2219) // 3.25V
		{
			EarClean_battery_level = BATTERY_LV0;
		}
		else // 2.9V
		{
			EarClean_battery_level = BATTERY_LOSE;
		}
		return;
	}
	
	if(EarClean_flag.usb_insert)
	{
		//单向往上走
		if (ADC_BATTERY_VALUE() >= 4000) //voltage over high
		{
			EarClean_battery_level = BATTERY_HIGH;
		}
		else if (ADC_BATTERY_VALUE() >= 2662) // 3.9V
		{
			EarClean_battery_level = BATTERY_FULL;
		}
		else if (ADC_BATTERY_VALUE() >= 2560 && EarClean_battery_level <= BATTERY_LV2) // 3.75V
		{
			EarClean_battery_level = BATTERY_LV2;
		}
		else if (ADC_BATTERY_VALUE() >= 2389 && EarClean_battery_level <= BATTERY_LV1) // 3.5V
		{
			EarClean_battery_level = BATTERY_LV1;
		}
		else if (ADC_BATTERY_VALUE() >= 2219 && EarClean_battery_level <= BATTERY_LV0) // 3.25V
		{
			EarClean_battery_level = BATTERY_LV0;
		}
	}
	else
	{
		//单向往下走
		if (ADC_BATTERY_VALUE() >= 4000) //voltage over high
		{
			EarClean_battery_level = BATTERY_HIGH;
		}
		else if (ADC_BATTERY_VALUE() >= 2662 && EarClean_battery_level >= BATTERY_FULL) // 3.9V
		{
			EarClean_battery_level = BATTERY_FULL;
		}
		else if (ADC_BATTERY_VALUE() >= 2560 && EarClean_battery_level >= BATTERY_LV2) // 3.75V
		{
			EarClean_battery_level = BATTERY_LV2;
		}
		else if (ADC_BATTERY_VALUE() >= 2389 && EarClean_battery_level >= BATTERY_LV1) // 3.5V
		{
			EarClean_battery_level = BATTERY_LV1;
		}
		else if (ADC_BATTERY_VALUE() >= 2219 && EarClean_battery_level >= BATTERY_LV0) // 3.25V
		{
			EarClean_battery_level = BATTERY_LV0;
		}
		else // 2.9V
		{
			EarClean_battery_level = BATTERY_LOSE;
		}
	}
}

static void motor_current_deal(void)
{
	if (ADC_MOTOR_CURRENT_VALUE() >= 1024) //采样电阻0.5, AD = 4096/Vref*(0.5*Imax)
	{
		EarClean_flag.current_error = 1;
	}
	else
	{
		EarClean_flag.current_error = 0;
	}
}

static void sleep(void)
{
	uint16_t check_count = 0;
	
	if(EarClean_flag.sleep)
	{
		MM_adc1_suspend();
		PWM_MOTOR_SUSPEND();
		main_IO_exit();

		while (EarClean_flag.sleep)
		{
			//注: 此IC进入休眠后LVR关闭
			SYS_EnterStop(); //进入休眠模式
			check_count = 0;
			while (check_count < 300)
			{
#ifndef DEBUG
				MTF_watch_dog_feed();
#endif
				sleep_updata = 1;
				if (EarClean_timer_flag._10ms)
				{
					EarClean_timer_flag._10ms = 0;
					event_produce();
					event_handle();
					check_count++;
				}
				if (EarClean_flag.sleep == 0)
					break;
			}
		}
		
		main_IO_init();
		PWM_MOTOR_START();
		MM_adc1_start();
	}
}

void main(void)
{
	uint8_t sys_read_delay = 0;
	
	main_IO_init();
	PWM_INIT();
	ADC_INIT();
	// UART_INIT();
	MTF_timer_init_handle();
#ifndef DEBUG
	MTF_watch_dog_init();
#endif
	SYS_EnableWakeUp();				//使能STOP唤醒功能
	// printf("welcome.............\r\n");

	while (1)
	{
#ifndef DEBUG
		MTF_watch_dog_feed();
#endif

		if (EarClean_timer_flag._2ms)
		{
			EarClean_timer_flag._2ms = 0;
			adc_run();
		}

		if (EarClean_timer_flag._10ms)
		{
			EarClean_timer_flag._10ms = 0;
			temp_deal();
			battery_deal();
			motor_current_deal();
			event_produce();
			event_handle();
			motor_function();
			Led_display();
		}

		if (EarClean_timer_flag._100ms)
		{
			EarClean_timer_flag._100ms = 0;

			if(EarClean_flag.sys_ready==0)
			{
				if(++sys_read_delay>=10) //上电等待系统稳定
				{
					sys_read_delay = 0;
					EarClean_flag.sys_ready = 1;
					EarClean_flag.sleep = 0;
					EarClean_flag.work = 1;
				}
			}
			sleep_updata = 0;
		}
		
		sleep();
	}
}
