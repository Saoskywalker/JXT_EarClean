#ifndef _APP_GLOBAL_H
#define _APP_GLOBAL_H

#include "types_base.h"

typedef struct
{
  uint8_t sleep : 1; //睡眠
  uint8_t sys_ready : 1; //系统准备完毕
  uint8_t work : 1; //工作
  uint8_t error : 1; //系统错误
  uint8_t sleep_updata : 1; //用于标记在唤醒后一段时间内, 进行一定的唤醒处理
  uint8_t nc1 : 1;
  uint8_t usb_insert : 1; //充电线插入
  uint8_t charge_full : 1; //充满电
  uint8_t drop_error : 1; //倾倒错误
  uint8_t current_error : 1; //电流AD错误
  uint8_t battery_error : 1; //电池AD错误
  uint8_t temp_unit_C : 1; //系统温度单位
  uint8_t disp_battery_level : 1; //显示电池电量
  uint8_t nc2 : 1;
  uint8_t nc3 : 1;
  uint8_t nc4 : 1;
} app_flag_type;

extern app_flag_type app_flag;

typedef enum
{
  AD_NORMAL = 0,
  AD_SHORT = 1,
  AD_CUT = 2
} AISTATUS;

typedef struct
{
  int8_t C_value;
  int8_t value;
  uint16_t AD_value;
  uint8_t status; // AISTATUS status;
} ADC_PARA;

extern ADC_PARA water_temp;

typedef enum
{
  LED_MODE_A = 0,
  LED_MODE_B,
  LED_MODE_C
};

typedef enum
{
  MODE_A = 0,
  MODE_B,
  MODE_C
};

typedef enum
{
  BATTERY_LOSE = 0,
  BATTERY_LV0,
  BATTERY_LV1,
  BATTERY_LV2,
  BATTERY_FULL,
  BATTERY_HIGH
};

extern uint8_t light_mode, app_work_mode;
extern uint8_t app_battery_level;

#endif
