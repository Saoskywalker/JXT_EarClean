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
    static uint8_t long_count = 0;

    key = key_get_result();
    
    if (key & MODE_KEY)
        sys_envent |= MODE_KEY;
    if (key & POWER_KEY)
    {
        if (++long_count>=200) //2s
        {
            long_count = 0;
            sys_envent |= POWER_KEY;
        }
    }
    else
    {
        long_count = 0;
    }
}

//-----------------------------------------------------------
//	事件处理
//-----------------------------------------------------------
void event_handle(void)
{
    switch (sys_envent)
    {
    case MODE_KEY:
        if (++EarClean_mode>=4)
            EarClean_mode = 0;
        break;
    case POWER_KEY:
        EarClean_flag.work = !EarClean_flag.work;
        if (EarClean_flag.work)
            EarClean_flag.sleep = 0;
        else
            EarClean_flag.sleep = 1;
        break;
    default:
        break;
    }
    sys_envent = 0;
}
