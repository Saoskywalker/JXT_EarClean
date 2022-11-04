#include "display_board.h"
#include "pwm_board.h"

static uint8_t dis_start = 0;

/*************************************************
 // 函数名称    : uint8_t Led_Display_init(void)
 // 功能描述    : 开启LED显示
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
uint8_t Led_Display_init(void)
{
  dis_start = 1;
  return 0;
}

/*************************************************
 // 函数名称    : uint8_t Led_Display_exit(void)
 // 功能描述    : 关闭LED显示
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
uint8_t Led_Display_exit(void)
{
  dis_start = 0;
  PWM_LED_SET_DUTY(0);
  LED_1TO4_ALL_SLEEP();
  return 0;
}

/*************************************************
 // 函数名称    : LED_out
 // 功能描述    :
 // 入口参数    : uint8_t data    uint8_t com--8bit每段
 // 出口参数    : 无
***************************************************/
/*
void LED_out(uint8_t _data_buf)
{
    if (_data_buf & bit0)
    {
        LED_1_ON;
    }
    else
    {
        LED_1_OFF;
    }

    if (_data_buf & bit1)
    {
        LED_2_ON;
    }
    else
    {
        LED_2_OFF;
    }

    if (_data_buf & bit2)
    {
        LED_3_ON;
    }
    else
    {
        LED_3_OFF;
    }

    if (_data_buf & bit3)
    {
        LED_4_ON;
    }
    else
    {
        LED_4_OFF;
    }

    if (_data_buf & bit4)
    {
        LED_5_ON;
    }
    else
    {
        LED_5_OFF;
    }

    if (_data_buf & bit5)
    {
        LED_6_ON;
    }
    else
    {
        LED_6_OFF;
    }

    if (_data_buf & bit6)
    {
        LED_7_ON;
    }
    else
    {
        LED_7_OFF;
    }

    if (_data_buf & bit7)
    {
        LED_8_ON;
    }
    else
    {
        LED_8_OFF;
    }
}
*/

/*************************************************
 // 函数名称    : Led_Dis_Update
 // 功能描述    : 显存更新到led
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
void Led_Dis_Update(void)
{
  uint8_t i = 0;
  for (i = 0; i < sizeof(LED_data); i++)
  {
    LED_data[i] = LED_data_buf[i];
  }
}

/*************************************************
 // 函数名称    : Led_Clear_All
 // 功能描述    : 清除所有显示
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
void Led_Clear_All(void)
{
  uint8_t i;
  for (i = 0; i < LED_DATA_SIZE; i++)
  {
    LED_data_buf[i] = 0;
  }
}

/*************************************************
 // 函数名称    : Led_dis_All
 // 功能描述    : 清除所有显示
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
void Led_dis_All(void)
{
  uint8_t i;
  for (i = 0; i < LED_DATA_SIZE; i++)
  {
    LED_data_buf[i] = 0XFF;
  }
}

/*************************************************
 // 函数名称    : Led_scan
 // 功能描述    : 此函数在prg_ms1()中执行
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
#define LED_SCAN_TOTAL 6 //通道数量
#define LED_SCAN_INTERVAL 1  //通道和显示更新间隔
#define LED_LIGHT_LEVEL 1 //亮度等级
uint8_t LED_data[LED_DATA_SIZE] = {0}; //数码管显示输出缓存
uint8_t LED_data_buf[LED_DATA_SIZE] = {0}; //LED显示data
void Led_Scan(void)
{
  static uint8_t led_scan_time = 0;        // LED扫描时间
  static uint8_t led_scan_position = 0;    // LED扫描位
  static uint8_t led_light_level_cnt = 0;

  if(!dis_start)
    return;

  PWM_LED_SET_DUTY((uint16_t)LED_data[1]<<1); //占空比转换 x*2

  if (++led_light_level_cnt >= LED_LIGHT_LEVEL)
  {
    //全关
    LED_1TO4_ALL_OFF();
  }
  
  if (++led_scan_time < LED_SCAN_INTERVAL)
  {
    return;
  }
  led_scan_time = 0;
  led_light_level_cnt = 0;

  if (led_scan_position == 0)
  {
    if (LED_data[0]&bit0)
    {
      LED1_ON();
    }
  }
  else if (led_scan_position == 1)
  {
    if (LED_data[0]&bit1)
    {
      LED2_ON();
    }
  }
  else if (led_scan_position == 2)
  {
    if (LED_data[0]&bit2)
    {
      LED3_ON();
    }
  }
  else if (led_scan_position == 3)
  {
    if (LED_data[0]&bit3)
    {
      LED4_R_ON();
    }
  }
  else if (led_scan_position == 4)
  {
    if (LED_data[0]&bit4)
    {
      LED4_G_ON();
    }
  }
  else if (led_scan_position == 5)
  {
    if (LED_data[0]&bit5)
    {
      LED4_B_ON();
    }
  }

  if (++led_scan_position >= LED_SCAN_TOTAL)
  {
    led_scan_position = 0;
  }
}
