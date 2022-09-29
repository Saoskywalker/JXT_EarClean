#ifndef _EARCLEAN_GLOBAL_H
#define _EARCLEAN_GLOBAL_H

#include "types_base.h"

typedef struct
{
  uint8_t sleep : 1;
  uint8_t power_up : 1;
  uint8_t work : 1;
  uint8_t error : 1;
  uint8_t low_power : 1;
  uint8_t loss_power : 1;
  uint8_t charging : 1;
  uint8_t charge_full : 1;
} EarClean_flag_type;

extern EarClean_flag_type EarClean_flag;
extern uint8_t EarClean_mode;

#endif
