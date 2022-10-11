#include "display_define.h"
#include "EarClean_global.h"

/******************************************************************************
 *         数码管显示数据定义(LED显示编码，用于查表)
 *******************************************************************************/
IN_ROM uint8_t BCD_tab[] = {
    (DATA_0), /*0*/
    (DATA_1), /*1*/
    (DATA_2), /*2*/
    (DATA_3), /*3*/
    (DATA_4), /*4*/
    (DATA_5), /*5*/
    (DATA_6), /*6*/
    (DATA_7), /*7*/
    (DATA_8), /*8*/
    (DATA_9), /*9*/
};

/*************************************************
 // 函数名称    : dig1_2_dsp
 // 功能描述    : 显示
 // 入口参数    : 无
 // 出口参数    : 无
***************************************************/
void dig1_2_dsp(uint8_t dis)
{
  dig2_num = BCD_tab[dis % 10];
  dig1_num = BCD_tab[dis / 10];
}

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
 * 显示放电剩余电量
*************************************************/
static void dis_residue_battery(uint8_t state)
{
  static uint8_t _dis_cnt = 0, _dis_flash_500ms = 0, _cnt_flash = 0, temp_edge = 0;

  if (state == 0) //关闭功能
  {
    _dis_cnt = 0;
    _dis_flash_500ms = 0;
    _cnt_flash = 0;
    temp_edge = 0;
    return;
  }

  if (++_dis_cnt >= 50)
  {
    _dis_cnt = 0;
    _dis_flash_500ms = !_dis_flash_500ms;
  }

  if (_dis_flash_500ms)
  {
    //显示放电剩余电量
    if (EarClean_battery_level <= BATTERY_LV0)
    {
      pulse_locate;
    }
    else if (EarClean_battery_level <= BATTERY_LV1)
    {
      high_locate;
      pulse_locate;
    }
    else if (EarClean_battery_level <= BATTERY_LV2)
    {
      medium_locate;
      high_locate;
      pulse_locate;
    }
    else if (EarClean_battery_level <= BATTERY_FULL)
    {
      low_locate;
      medium_locate;
      high_locate;
      pulse_locate;
    }
    temp_edge = 1;
  }
  else
  {
    if (temp_edge)
    {
      temp_edge = 0;
      if (++_cnt_flash >= 3)
      {
        _cnt_flash = 0;
        EarClean_flag.disp_battery_level = 0;
      }
    }
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
  static uint8_t _dis_charge_cnt = 0;
  static uint8_t _dis_charge_500ms = 0, _dis_500ms_cnt = 0, _dis_500ms = 0;

  if (++_dis_500ms_cnt >= 50)
  {
    _dis_500ms_cnt = 0;
    _dis_500ms = !_dis_500ms;
  }

  if(EarClean_flag.sys_ready==0)
  {
    Led_dis_All(); //上电准备时全显
    return;
  }

  Led_Clear_All(); //清除所有显示数据

  if (EarClean_flag.usb_insert)
  {
      if (EarClean_flag.charge_full)
      {
        low_locate;
        medium_locate;
        high_locate;
        pulse_locate;
      }
      else
      {
        //显示充电电量
        if (++_dis_charge_500ms>=50)
        {
          _dis_charge_500ms = 0;
          
          if (++_dis_charge_cnt >= 5)
          {
            if (EarClean_battery_level <= BATTERY_LV0)
            {
              _dis_charge_cnt = 0;
            }
            else if (EarClean_battery_level <= BATTERY_LV1)
            {
              _dis_charge_cnt = 1;
            }
            else if (EarClean_battery_level <= BATTERY_LV2)
            {
              _dis_charge_cnt = 2;
            }
            else if (EarClean_battery_level <= BATTERY_FULL)
            {
              _dis_charge_cnt = 3;
            }
          }
        }
        if (_dis_charge_cnt == 1)
        {
          pulse_locate;
        }
        else if (_dis_charge_cnt == 2)
        {
          high_locate;
          pulse_locate;
        }
        else if (_dis_charge_cnt == 3)
        {
          medium_locate;
          high_locate;
          pulse_locate;
        }
        else if (_dis_charge_cnt == 4)
        {
          low_locate;
          medium_locate;
          high_locate;
          pulse_locate;
        }
      }
  }
  else
  {
    _dis_charge_cnt = 0;
    _dis_charge_500ms = 0;

    if (EarClean_flag.work)
    {
      if (EarClean_flag.temp_unit_C) //显示温度
      {
        if (water_temp.C_value <= 99 && water_temp.C_value >= 0)
        {
          dig1_2_dsp(water_temp.C_value);
        }
        else
        {
          dig1_num = DATA_neg;
          dig2_num = DATA_neg;
        }
        dig3_num = DATA_C;
      }
      else
      {
        if (water_temp.value <= 99 && water_temp.value >= 0)
        {
          dig1_2_dsp(water_temp.value);
        }
        else
        {
          dig1_num = DATA_neg;
          dig2_num = DATA_neg;
        }
        dig3_num = DATA_F;
      }

      dis_residue_battery(EarClean_flag.disp_battery_level);
      if(!EarClean_flag.disp_battery_level)
      {
        if (EarClean_battery_level <= BATTERY_LV0 && !_dis_500ms) //低电量闪烁
        {
        }
        else
        {
          if (EarClean_mode == MODE_A)
            low_locate;
          else if (EarClean_mode == MODE_B)
            medium_locate;
          else if (EarClean_mode == MODE_C)
            high_locate;
          else
            pulse_locate;
        }
      }
    }
    else
    {
      dis_residue_battery(EarClean_flag.disp_battery_level);
      if(!EarClean_flag.disp_battery_level)
      {
        EarClean_flag.sleep = 1; //进入睡眠命令统一由此发出, 由sleep运行event_handle退出
      }
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
