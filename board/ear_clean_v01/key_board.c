#include "key_board.h"
#include "gpio_board.h"

uint16_t key_input_res = 0;

#define KEY_PREVENT_SHAKE_TIME 50 //按键消抖时间10ms
void key_input_check_timer(void) //定期运行输入检查
{
    static uint8_t i = 0, j = 0, l = 0, charge_full = 0;
    static uint16_t k = 0, pulse_cnt = 0, cnt_1s = 0;

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
        if (++k >= 2500) //500ms
        {
            k = 2500;
            key_input_res |= bit2;
        }
    }
    else // usb拔掉
    {
        k = 0;
    }

    /********
     *  SM5308充电指示1灯模式:
        充电状态=LED1间断方波;
        充满状态=LED1一直方波;
     * **********/
    if(CHARGE_CHECK())
    {
        l = 1;
    }
    else
    {
        if (l)
            pulse_cnt++;
        l = 0;
    }
    if (++cnt_1s>=5000)
    {
        cnt_1s = 0;
        if (pulse_cnt >= 400) //1秒内出现大量的方波为电池充满状态
            charge_full = 1;
        else
            charge_full = 0;
        pulse_cnt = 0;
    }
    if(charge_full)
        key_input_res |= bit3;
}
