#include "EarClean_global.h"
#include "types_plus.h"
#include "gpio_board.h"
#include "pwm_board.h"
#include "adc_board.h"
#include "stdio.h"
#include "uart_board.h"
#include "timer_port.h"
#include "watch_dog_port.h"
#include "key_board.h"
#include "display_define.h"
#include "envent_define.h"
#include "EarClean_timer.h"
#include "ad_table.h"

EarClean_flag_type EarClean_flag = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t EarClean_mode = 0;

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
			SYS_EnterStop(); //进入休眠模式
			check_count = 0;
			while (check_count < 300)
			{
#ifndef DEBUG
				MTF_watch_dog_feed();
#endif
				if (EarClean_timer_flag._2ms)
				{
					EarClean_timer_flag._2ms = 0;
					key_input_check_timer();
				}
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

		MM_adc1_start();
		PWM_MOTOR_START();
	}
}

static void motor_function(void)
{
	if (EarClean_flag.work)
	{
		if (EarClean_mode == 0)
		{
			PWM_MOTOR_SET_DUTY(PWM_DUTY_25);
		}
		else if (EarClean_mode == 1)
		{
			PWM_MOTOR_SET_DUTY(PWM_DUTY_40);
		}
		else if (EarClean_mode == 2)
		{
			PWM_MOTOR_SET_DUTY(PWM_DUTY_50);
		}
		else
		{
			PWM_MOTOR_SET_DUTY(PWM_DUTY_75);
		}
	}
	else
	{
		PWM_MOTOR_SET_DUTY(PWM_DUTY_0);
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
static uint8_t F_C(uint8_t cfdata)
{
	uint8_t a = 0;
	if (cfdata > 32)
	{
		a = ((cfdata - 32) * 10 + 9) / 18;
	}
	else
	{
		a = ((32 - cfdata) * 10 + 9) / 18;
	}

	return a;
}

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
 // 功能描述    : 温度处理
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
typedef struct
{
  uint8_t C_value;
  uint8_t value;
  uint16_t AD_value;
  uint8_t status; // AISTATUS status;
} ADC_PARA;

static void temp_deal(void)
{
	uint8_t data_buf = 0;
	uint16_t AD_buf = 0;

	// AD_buf = ADC_NTC_VALUE >> 3;

	/* if ((AD_buf < 30) && (Power_Delay_Time == 0))
	{
		if (++Temp_coil_Err_cont >= 2)
		{
			Temp_coil_Err_cont = 0;
			Temp_coil.status = AI_CUT;
			Sys_Err.temp_coil_err = ENABLE;
			Temp_coil.value = 0;
		}
	}
	else if ((AD_buf > 500) && (Power_Delay_Time == 0))
	{
		if (++Temp_coil_Err_cont >= 2)
		{
			Temp_coil_Err_cont = 0;
			Temp_coil.status = AI_SHORT;
			Sys_Err.temp_coil_err = ENABLE;
			Temp_coil.value = 0;
		}
	}
	else
	{
		Temp_coil_Err_cont = 0;
		Temp_coil.status = AI_NORMAL;
		Sys_Err.temp_coil_err = DISABLE;

		Temp_coil.value = Temp_tab_10k_3450[data_buf - 48];
		Temp_coil.value = 5 + ADC_lookup(AD_buf, Temp_tab_10k_3450, 154); //表从5F开始
		//
		if (Temp_coil.value <= 32)
		{
			Temp_coil.C_value = 15 - F_C(Temp_coil.value);
		}
		else
		{
			Temp_coil.C_value = F_C(Temp_coil.value) + 15;
		}
	} */
	ADC_lookup(AD_buf, Temp_tab_10k_3450, 154);
}

void main(void)
{
	main_IO_init();
	PWM_INIT();
	ADC_INIT();
	UART_INIT();
	MTF_timer_init_handle();
#ifndef DEBUG
	MTF_watch_dog_init();
#endif
SYS_EnableWakeUp();				//使能STOP唤醒功能
	EarClean_flag.sleep = 0;
	EarClean_flag.work = 1;
printf("welcome.............\r\n");
	while (1)
	{
#ifndef DEBUG
		MTF_watch_dog_feed();
#endif

		if (EarClean_timer_flag._2ms)
		{
			EarClean_timer_flag._2ms = 0;
			adc_run();
			key_input_check_timer();
			Led_Scan();
		}

		if (EarClean_timer_flag._10ms)
		{
			EarClean_timer_flag._10ms = 0;
			event_produce();
			event_handle();
			Led_display();
			motor_function();
		}
		
		sleep();
	}
}
