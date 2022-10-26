#include "envent_define.h"
#include "key_board.h"
#include "app_global.h"
#include "gpio_board.h"

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

    if ((key & bit0) && !(key_old & bit0)) //单击模式键
        sys_envent |= LED_MODE_KEY;

    if ((key & bit1) && !(key_old & bit1)) //单击电源键
        sys_envent |= POWER_KEY;

    if ((key & bit2)) //插入充电线
        sys_envent |= USB_INSERT;
    else
        sys_envent |= USB_NO_INSERT;

    if ((key & bit3)) //充满电
        sys_envent |= CHANGE_FULL;

    if ((key & bit4)) //倾倒
        sys_envent |= DROP_EVENT;
    else
        sys_envent |= NO_DROP_EVENT;

    if (key & bit0) //长按模式键
    {
        if (++mode_key_long_count >= 200) // 2s
        {
            mode_key_long_count = 0;
            // sys_envent |= CHANGE_TEMP_UNIT;
        }
    }
    else
    {
        mode_key_long_count = 0;
    }

    if (key & bit1) //电源键长按
    {
        if (++power_key_long_count >= 200) // 2s
        {
            power_key_long_count = 0;
            // sys_envent |= POWER_KEY;
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

    if (app_flag.sys_ready==0)
        return;

    while (temp)
    {   
        switch (sys_envent & temp) //注意事件顺序
        {
        case LED_MODE_KEY:
            if(app_flag.work)
            {
                if (++light_mode > LED_MODE_C)
                    light_mode = LED_MODE_A;
            }
            break;
        case POWER_KEY:
            // if (app_flag.usb_insert == 0)
            {
                app_flag.drop_error = 0;
                app_flag.sleep = 0;
                app_flag.disp_battery_level = 1;
                if (app_flag.work)
                {
                    if (++app_work_mode > MODE_C)
                    {
                        app_work_mode = MODE_A;
                        app_flag.work = 0;
                    }
                }
                else
                {
                    if (app_battery_level > BATTERY_LOSE)
                    {
                        app_flag.work = 1;
                    }
                }
            }
            break;
        case USB_INSERT:
            app_flag.sleep = 0;
            app_flag.usb_insert = 1;
            // app_flag.work = 0;
            break;
        case USB_NO_INSERT:
            app_flag.usb_insert = 0;
            app_flag.charge_full = 0;
            break;
        case DIS_BATTERY:
            app_flag.sleep = 0;
            app_flag.disp_battery_level = 1;
            break;
        case CHANGE_TEMP_UNIT:
            app_flag.temp_unit_C = !app_flag.temp_unit_C;
            break;
        case CHANGE_FULL:
            app_flag.charge_full = 1;
            break;
        case DROP_EVENT:
            app_flag.drop_error = 1;
            app_flag.work = 0; //倾倒停止工作
            break;
        case NO_DROP_EVENT:
            app_flag.drop_error = 0;
            break;
        default:
            break;
        }
        temp <<= 1;
    }
    sys_envent = 0;

    //error handle
    if(app_flag.current_error) //电流错误
        app_flag.work = 0;
    if (app_battery_level <= BATTERY_LOSE) //电池耗尽停止工作
        app_flag.work = 0;  

    if(app_flag.work)
        CHRG_CURRENT_SET_LOW();
    else
        CHRG_CURRENT_SET_HIGH();
}
