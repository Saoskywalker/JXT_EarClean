#include "key_board.h"
#include "gpio_board.h"
#include "types_plus.h"

uint16_t key_input_res = 0;

#define KEY_PREVENT_SHAKE_TIME 10 //按键消抖时间
void key_input_check_timer(void) //定期运行输入检查
{
    static uint8_t i = 0, j = 0, k = 0;

    key_input_res = 0;
    
    if (KEY_1_PIN()) //弹起
    {
        i = 0;
    }
    else //按下
    {
        if (++i >= KEY_PREVENT_SHAKE_TIME)
        {
            i = KEY_PREVENT_SHAKE_TIME;
            key_input_res |= bit0;
        }
    }

    if (KEY_2_PIN()) //弹起
    {
        j = 0;
    }
    else //按下
    {
        if (++j >= KEY_PREVENT_SHAKE_TIME)
        {
            j = KEY_PREVENT_SHAKE_TIME;
            key_input_res |= bit1;
        }
    }

    if (USB_CHECK()) // usb插入
    {
        if (++k >= KEY_PREVENT_SHAKE_TIME)
        {
            k = KEY_PREVENT_SHAKE_TIME;
            key_input_res |= bit2;
        }
    }
    else // usb拔掉
    {
        k = 0;
    }

    /********
     *  SM5308充电指示1灯模式:
        充电状态=LED1输出方波;
        充满状态=LED1高电平;
     * **********/
    if(CHARGE_CHECK()) //隔一段时间无方波输出
    {
        
    }
}
