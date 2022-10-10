#ifndef _EARCLEAN_GLOBAL_H
#define _EARCLEAN_GLOBAL_H

#include "types_base.h"

typedef struct
{
  uint8_t sleep : 1; //睡眠
  uint8_t sys_ready : 1; //系统准备完毕
  uint8_t work : 1; //工作
  uint8_t error : 1; //系统错误
  uint8_t nc0 : 1;
  uint8_t nc1 : 1;
  uint8_t usb_insert : 1; //充电线插入
  uint8_t charge_full : 1; //充满电
  uint8_t ntc_error : 1; //ntc AD错误
  uint8_t current_error : 1; //电流AD错误
  uint8_t battery_error : 1; //电池AD错误
  uint8_t temp_unit_C : 1; //系统温度单位
  uint8_t disp_battery_level : 1; //显示电池电量
  uint8_t nc2 : 1;
  uint8_t nc3 : 1;
  uint8_t nc4 : 1;
} EarClean_flag_type;

extern EarClean_flag_type EarClean_flag;

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
  MODE_A = 0,
  MODE_B,
  MODE_C,
  MODE_D
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

extern uint8_t EarClean_mode;
extern uint8_t EarClean_battery_level;

#endif
