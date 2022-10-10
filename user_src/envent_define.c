#include "envent_define.h"
#include "key_board.h"
#include "EarClean_global.h"

uint16_t sys_envent = 0;

//-----------------------------------------------------------
//	事件产生
//-----------------------------------------------------------
void event_produce(void)
{
    uint16_t key = 0;
    static uint8_t power_key_long_count = 0, mode_key_long_count = 0;
    static uint16_t key_old = 0;

    key = key_get_result();

    if (!(key & bit1) && (key_old & bit1)) //单击模式键, 松开
        sys_envent |= MODE_KEY;

    if (!(key & bit0) && (key_old & bit0)) //单击电源键, 松开
        sys_envent |= DIS_BATTERY;

    if ((key & bit2)) //插入充电线
        sys_envent |= USB_INSERT;
    else
        sys_envent |= USB_NO_INSERT;

    if ((key & bit3)) //充满电
        sys_envent |= CHANGE_FULL;

    if (key & bit1) //长按模式键
    {
        if (++mode_key_long_count >= 200) // 2s
        {
            mode_key_long_count = 0;
            sys_envent |= CHANGE_TEMP_UNIT;
        }
    }
    else
    {
        mode_key_long_count = 0;
    }

    if (key & bit0) //电源键长按
    {
        if (++power_key_long_count >= 200) // 2s
        {
            power_key_long_count = 0;
            sys_envent |= POWER_KEY;
        }
    }
    else
    {
        power_key_long_count = 0;
    }

    key_old = key;
}

//-----------------------------------------------------------
//	事件处理
//-----------------------------------------------------------
void event_handle(void)
{
    uint16_t temp = 1;

    if (EarClean_flag.sys_ready==0)
        return;

    while (temp)
    {   
        switch (sys_envent & temp) //注意事件顺序
        {
        case MODE_KEY:
            if(EarClean_flag.work)
            {
                if (++EarClean_mode > MODE_D)
                    EarClean_mode = MODE_A;
            }
            break;
        case POWER_KEY:
            if (EarClean_flag.usb_insert == 0)
            {
                if (EarClean_flag.work)
                {
                    EarClean_flag.work = 0;
                }
                else
                {
                    if (EarClean_battery_level > BATTERY_LOSE)
                    {
                        EarClean_flag.work = 1;
                        EarClean_flag.sleep = 0;
                    }
                }
            }
            break;
        case USB_INSERT:
            EarClean_flag.sleep = 0;
            EarClean_flag.charge_full = 0;
            EarClean_flag.usb_insert = 1;
            EarClean_flag.work = 0;
            break;
        case USB_NO_INSERT:
            EarClean_flag.usb_insert = 0;
            break;
        case DIS_BATTERY:
            EarClean_flag.sleep = 0;
            EarClean_flag.disp_battery_level = 1;
            break;
        case CHANGE_TEMP_UNIT:
            EarClean_flag.temp_unit_C = !EarClean_flag.temp_unit_C;
            break;
        case CHANGE_FULL:
            EarClean_flag.charge_full = 1;
            break;
        default:
            break;
        }
        temp <<= 1;
    }
    sys_envent = 0;

    //error handle
    if(EarClean_flag.current_error) //电流错误
        EarClean_flag.work = 0;
    if (EarClean_battery_level <= BATTERY_LOSE) //电池耗尽停止工作
        EarClean_flag.work = 0;
}
