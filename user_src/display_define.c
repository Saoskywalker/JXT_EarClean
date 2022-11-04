#include "display_define.h"
#include "app_global.h"

/*************************************************
 // 函数名称    : board_test
 // 功能描述    : PCB工厂自检
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
void board_test(void)
{
}

/*************************************************
//名称        : Err_dsp
//功能        :
//入口参数    :	无
//出口参数    :	无
**************************************************/
void Err_dsp(void)
{
}

/*************************************************
 // 函数名称    : Disp_All
 // 功能描述    : 全显
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
void Disp_All(void)
{
}

/***********************************************
 * 显示电量
*************************************************/
static void dis_battery(void)
{
  if (app_battery_level <= BATTERY_LV0)
  {
    red_locate;
  }
  else if (app_battery_level <= BATTERY_LV1)
  {
    blue_locate;
  }
  else if (app_battery_level <= BATTERY_FULL)
  {
    green_locate;
  }
}

/*************************************************
 // 函数名称    : LedDsp_content
 // 功能描述    : 用户定义显示函数
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
static void LedDsp_content(void)
{
  static uint8_t _dis_charge_500ms = 0, _dis_charge_cnt = 0;
  static uint8_t _dis_500ms_cnt = 0, _dis_500ms = 0, _flash_cnt = 0, _dis_400ms_cnt = 0;

    if (app_battery_level <= BATTERY_LOSE)
    {
      _dis_500ms_cnt++;
      if (_dis_500ms_cnt >= 50)
      {
        _dis_500ms_cnt = 0;
        _dis_500ms ^= 0X01;
        _flash_cnt++;
      }
    }
    else
    {
      _dis_500ms_cnt = 0;
      _flash_cnt = 0;
      _dis_500ms = 0;
    }

  if(app_flag.sys_ready==0)
  {
    Led_dis_All(); //上电准备时全显
    return;
  }

  Led_Clear_All(); //清除所有显示数据

  if (app_flag.drop_error)
  {
    led1_locate;
    led2_locate;
    led3_locate;
    return;
  }

  if (app_flag.work)
  {
    if (app_work_mode == MODE_A)
    {
      led1_locate;
    }
    else if (app_work_mode == MODE_B)
    {
      led2_locate;
    }
    else
    {
      led3_locate;
    }

    //灯光模式显示
    if (light_mode == LED_MODE_A)
    {
      LED_LIGHT_GRADUAL(20);
    }
    else if (light_mode == LED_MODE_B)
    {
      LED_LIGHT_GRADUAL(60);
    }
    else if (light_mode == LED_MODE_C)
    {
      LED_LIGHT_GRADUAL(100);
    }
    else
    {
      LED_LIGHT_GRADUAL(0);
    }
  }

  if (app_flag.usb_insert) //整体策略上禁止充电时睡眠
  {
    _dis_400ms_cnt = 0;
    
    //充电时电量灯闪, 充满常亮
    if (app_flag.charge_full)
    {
      dis_battery();
    }
    else
    {
      _dis_charge_500ms++;
      if (_dis_charge_500ms >= 50)
      {
        _dis_charge_500ms = 0;
        _dis_charge_cnt = !_dis_charge_cnt;
      }
      if(_dis_charge_cnt)
        dis_battery();
    }
  }
  else
  {
    _dis_charge_cnt = 0;
    _dis_charge_500ms = 0;

    //放电电量指示
    if (app_battery_level <= BATTERY_LOSE)
    {
      if (_dis_500ms) //低电闪烁
      {
        red_locate;
      }
    }
    else
    {
      dis_battery();
    }

    if (!app_flag.work)
    {
      if (app_battery_level <= BATTERY_LOSE)
      {
        if (_flash_cnt >= 6) //低电睡眠策略, 闪3次后睡眠
        {
          app_flag.disp_battery_level = 0;
        }
        _dis_400ms_cnt = 0;
      }
      else
      {
        if (++_dis_400ms_cnt >= 40) //正常睡眠策略, 延时400ms
        {
          _dis_400ms_cnt = 0;
          app_flag.disp_battery_level = 0;
        }
      }
    }

    if (!app_flag.disp_battery_level)
    {
      Led_Clear_All(); 
      _dis_500ms_cnt = 0;
      _flash_cnt = 0;
      // _dis_400ms_cnt = 0;
      _dis_500ms = 0;
      app_flag.sleep = 1; //进入睡眠命令统一由此发出, 由sleep运行event_handle退出
    }
  }
}

/*************************************************
 // 函数名称    : Led_display
 // 功能描述    :
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
void Led_display(void)
{ 
  LedDsp_content();
  Led_Dis_Update();
}
