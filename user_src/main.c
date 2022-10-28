#include "app_global.h"
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
#include "app_timer.h"
#include "ad_table.h"

app_flag_type app_flag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t light_mode = LED_MODE_A, app_work_mode = MODE_A;
uint8_t app_battery_level = BATTERY_FULL;

/*****************************
 * 电机控制输出
 * ********************************/
static void motor_function(void)
{
	static uint16_t pulse_count = 0;
	static uint8_t new_mode = 0;

	if (app_flag.work)
	{
		if(new_mode!=app_work_mode)
		{
			new_mode = app_work_mode;
			pulse_count = 0;
		}
		if (new_mode == MODE_A)
		{
			if(++pulse_count>=6500)
			{
				pulse_count = 0;
			}
			if (pulse_count>=500)
				PWM_MOTOR_SET_DUTY(PWM_DUTY_0);
			else
				PWM_MOTOR_SET_DUTY(PWM_DUTY_75);
		}
		else if (new_mode == MODE_B)
		{
			if(++pulse_count>=4500)
			{
				pulse_count = 0;
			}
			if (pulse_count>=500)
				PWM_MOTOR_SET_DUTY(PWM_DUTY_0);
			else
				PWM_MOTOR_SET_DUTY(PWM_DUTY_75);
		}
		else
		{
			if(++pulse_count>=2500)
			{
				pulse_count = 0;
			}
			if (pulse_count>=500)
				PWM_MOTOR_SET_DUTY(PWM_DUTY_0);
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
/* ADC_PARA water_temp = {25, 77, 2048, AD_NORMAL};
static void temp_deal(void)
{
	static uint8_t Temp_Err_Cont = 0;
	static uint16_t cnt_delay = 0;

	if (app_flag.sys_ready)
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
			app_flag.ntc_error = 1;
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
			app_flag.ntc_error = 1;
			water_temp.C_value = -128;
			water_temp.value = -128;
		}
	}
	else
	{
		Temp_Err_Cont = 0;
		water_temp.status = AD_NORMAL;
		app_flag.ntc_error = 0;

		//表从0C开始, 表为下拉电阻, 但实际电路为上拉电阻
		water_temp.C_value = (int8_t)ADC_lookup(4096-ADC_NTC_VALUE(), TempC_tab_10k_3435, sizeof(TempC_tab_10k_3435)/sizeof(uint16_t));
        water_temp.value = C_F((int8_t)water_temp.C_value);
	}
}
 */
static void battery_deal(void)
{
	// Vref=2.4, 分压为1/2, Vin = 2*AD*2.4/4096+0.5(四舍五入), AD = (Vin)*4096/4.8+0.5(四舍五入)

	if (app_flag.sys_ready == 0)// || app_flag.sleep_updata)
	{
		if (ADC_BATTERY_VALUE() >= 4000) //voltage over high
		{
			app_battery_level = BATTERY_HIGH;
		}
		else if (ADC_BATTERY_VALUE() >= 3328) // 3.9V
		{
			app_battery_level = BATTERY_FULL;
		}
		else if (ADC_BATTERY_VALUE() >= 3157) // 3.7V
		{
			app_battery_level = BATTERY_LV2;
		}
		else if (ADC_BATTERY_VALUE() >= 2987) // 3.5V
		{
			app_battery_level = BATTERY_LV1;
		}
		else if (ADC_BATTERY_VALUE() >= 2645) // 3.1V
		{
			app_battery_level = BATTERY_LV0;
		}
		else // 2.9V
		{
			app_battery_level = BATTERY_LOSE;
		}
		return;
	}
	
	if(app_flag.usb_insert)
	{
		//单向往上走
		if (ADC_BATTERY_VALUE() >= 4000) //voltage over high
		{
			app_battery_level = BATTERY_HIGH;
		}
		else if (ADC_BATTERY_VALUE() >= 3328) // 3.9V
		{
			app_battery_level = BATTERY_FULL;
		}
		else if (ADC_BATTERY_VALUE() >= 3157 && app_battery_level <= BATTERY_LV2) // 3.7V
		{
			app_battery_level = BATTERY_LV2;
		}
		else if (ADC_BATTERY_VALUE() >= 2987 && app_battery_level <= BATTERY_LV1) // 3.5V
		{
			app_battery_level = BATTERY_LV1;
		}
		else if (ADC_BATTERY_VALUE() >= 2645 && app_battery_level <= BATTERY_LV0) // 3.1V
		{
			app_battery_level = BATTERY_LV0;
		}
	}
	else
	{
		//单向往下走
		if (ADC_BATTERY_VALUE() >= 4000) //voltage over high
		{
			app_battery_level = BATTERY_HIGH;
		}
		else if (ADC_BATTERY_VALUE() >= 3328 && app_battery_level >= BATTERY_FULL) // 3.9V
		{
			app_battery_level = BATTERY_FULL;
		}
		else if (ADC_BATTERY_VALUE() >= 3157 && app_battery_level >= BATTERY_LV2) // 3.7V
		{
			app_battery_level = BATTERY_LV2;
		}
		else if (ADC_BATTERY_VALUE() >= 2987 && app_battery_level >= BATTERY_LV1) // 3.5V
		{
			app_battery_level = BATTERY_LV1;
		}
		else if (ADC_BATTERY_VALUE() >= 2645 && app_battery_level >= BATTERY_LV0) // 3.1V
		{
			app_battery_level = BATTERY_LV0;
		}
		else // 2.9V
		{
			app_battery_level = BATTERY_LOSE;
		}
	}
}

static void motor_current_deal(void)
{
	if (ADC_MOTOR_CURRENT_VALUE() >= 1024) //采样电阻0.5, AD = 4096/Vref*(0.5*Imax)
	{
		app_flag.current_error = 1;
	}
	else
	{
		app_flag.current_error = 0;
	}
}

static void sleep(void)
{
	uint16_t check_count = 0;
	
	if(app_flag.sleep)
	{
		Led_Display_exit();
		MM_adc1_suspend();
		PWM_SUSPEND();
		main_IO_exit();

		while (app_flag.sleep)
		{
			MTF_sys_stop(); //进入休眠模式
			check_count = 0;
			while (check_count < 300)
			{
				MTF_watch_dog_feed();
				app_flag.sleep_updata = 1;
				if (app_timer_flag._10ms)
				{
					app_timer_flag._10ms = 0;
					event_produce();
					event_handle();
					check_count++;
				}
				if (app_flag.sleep == 0)
					break;
			}
		}
		
		main_IO_init();
		PWM_START();
		MM_adc1_start();
		Led_Display_init();
	}
}

void main(void)
{
	uint8_t sys_read_delay = 0, sleep_updata_delay = 0;
	
	main_IO_init();
	PWM_INIT();
	MM_adc1_init();
	// UART_INIT();
	MTF_timer_init_handle();
	Led_Display_init();

	MTF_watch_dog_init();
	// printf("welcome.............\r\n");

	while (1)
	{
		MTF_watch_dog_feed();

		if (app_timer_flag._2ms)
		{
			app_timer_flag._2ms = 0;
			adc_run();
		}

		if (app_timer_flag._10ms)
		{
			app_timer_flag._10ms = 0;
			// temp_deal();
			battery_deal();
			// motor_current_deal();
			if (app_flag.sleep_updata == 0)
			{
				event_produce();
				event_handle();
				motor_function();
				Led_display();
			}
		}

		if (app_timer_flag._100ms)
		{
			app_timer_flag._100ms = 0;

			if(app_flag.sys_ready==0)
			{
				if(++sys_read_delay>=10) //上电等待系统稳定
				{
					sys_read_delay = 0;
					app_flag.sys_ready = 1;
					app_flag.disp_battery_level = 1;
					app_flag.sleep = 0;
					app_flag.work = 1; //上电工作
				}
			}

			if(app_flag.sleep_updata)
			{
				if(++sleep_updata_delay>=2)
				{
					sleep_updata_delay = 0;
					app_flag.sleep_updata = 0;
				}
			}
		}
		
		sleep();
	}
}
