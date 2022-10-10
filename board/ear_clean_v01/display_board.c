#include "display_board.h"

/*************************************************
 // 函数名称    : uint8_t Led_Display_init(void)
 // 功能描述    : 开启LED显示
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
uint8_t Led_Display_init(void)
{
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
  COMDIG1_PIN_OFF;
  COMDIG2_PIN_OFF;
  COMDIG3_PIN_OFF;
  COMDIG4_PIN_OFF;
  return 0;
}

/*************************************************
 // 函数名称    : SEGNum_Scan
 // 功能描述    :
 // 入口参数    : uint8_t data    uint8_t com--8bit每段
 // 出口参数    : 无
***************************************************/
static void SEGNum_out(uint8_t _data_buf)
{
  if (_data_buf & bit0)
  {
    SEG_A_PIN_ON;
  }
  else
  {
    SEG_A_PIN_OFF;
  }

  if (_data_buf & bit1)
  {
    SEG_B_PIN_ON;
  }
  else
  {
    SEG_B_PIN_OFF;
  }

  if (_data_buf & bit2)
  {
    SEG_C_PIN_ON;
  }
  else
  {
    SEG_C_PIN_OFF;
  }

  if (_data_buf & bit3)
  {
    SEG_D_PIN_ON;
  }
  else
  {
    SEG_D_PIN_OFF;
  }

  if (_data_buf & bit4)
  {
    SEG_E_PIN_ON;
  }
  else
  {
    SEG_E_PIN_OFF;
  }

  if (_data_buf & bit5)
  {
    SEG_F_PIN_ON;
  }
  else
  {
    SEG_F_PIN_OFF;
  }

  if (_data_buf & bit6)
  {
    SEG_G_PIN_ON;
  }
  else
  {
    SEG_G_PIN_OFF;
  }

  if (_data_buf & bit7)
  {
    SEG_H_PIN_ON;
  }
  else
  {
    SEG_H_PIN_OFF;
  }
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
  for (i = 0; i < LED_COM_TOTAL; i++)
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
  for (i = 0; i < LED_COM_TOTAL; i++)
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
#define LED_SCAN_INTERVAL 2  //通道和显示更新间隔
#define LED_LIGHT_LEVEL 2 //亮度等级
uint8_t LED_data[LED_COM_TOTAL] = {0}; //数码管显示输出缓存
uint8_t LED_data_buf[LED_COM_TOTAL] = {0}; //LED显示data
void Led_Scan(void)
{
  static uint8_t led_scan_time = 0;        // LED扫描时间
  static uint8_t led_scan_position = 0;    // LED扫描位
  static uint8_t led_light_level_cnt = 0;

  if (++led_light_level_cnt >= LED_LIGHT_LEVEL)
  {
    //关COM口
    COMDIG1_PIN_OFF;
    COMDIG2_PIN_OFF;
    COMDIG3_PIN_OFF;
    COMDIG4_PIN_OFF;
  }
  
  if (++led_scan_time < LED_SCAN_INTERVAL)
  {
    return;
  }
  led_scan_time = 0;
  led_light_level_cnt = 0;

  if (led_scan_position == 0) // COM1
  {
    // LED_out(0X00);
    SEGNum_out(LED_data[led_scan_position]);
    COMDIG1_PIN_ON; //开COM口
  }
  else if (led_scan_position == 1) // COM2
  {
    SEGNum_out(LED_data[led_scan_position]);
    COMDIG2_PIN_ON; //开COM口
  }
  else if (led_scan_position == 2) // COM3
  {
    SEGNum_out(LED_data[led_scan_position]);
    COMDIG3_PIN_ON; //开COM口
  }
  else if (led_scan_position == 3) // COM4
  {
    // LED_out(LED_data[led_scan_position]);
    SEGNum_out(LED_data[led_scan_position]);
    COMDIG4_PIN_ON; //开COM口
  }

  if (++led_scan_position >= LED_COM_TOTAL)
  {
    led_scan_position = 0;
  }
}
