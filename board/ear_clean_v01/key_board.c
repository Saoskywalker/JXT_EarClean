#include "key_board.h"
#include "gpio_board.h"
#include "adc_board.h"
#include "app_global.h"

uint16_t key_input_res = 0;

#define KEY_PREVENT_SHAKE_TIME 100 //按键消抖时间20ms
void key_input_check_timer(void)   //定期运行输入检查
{
    static uint8_t i = 0, j = 0, IC4056_state = 0, IC4056_state_old = 0;
    static uint16_t k = 0, u = 0;

    if (app_flag.sleep)
    {
        if (KEY_ADC_PIN() == 0) //按下
        {
            if (++j >= KEY_PREVENT_SHAKE_TIME)
            {
                j = KEY_PREVENT_SHAKE_TIME;
                key_input_res |= bit1;
            }
        }
        else //弹起
        {
            j = 0;
            key_input_res &= ~bit1;
        }
    }
    else
    {
        if (ADC_KEY_VALUE() >= 2048 - 100 && ADC_KEY_VALUE() <= 2048 + 100) //按下
        {
            if (++i >= KEY_PREVENT_SHAKE_TIME)
            {
                i = KEY_PREVENT_SHAKE_TIME;
                key_input_res |= bit0;
            }
        }
        else //弹起
        {
            i = 0;
            key_input_res &= ~bit0;
        }

        if (ADC_KEY_VALUE() >= 0 && ADC_KEY_VALUE() <= 200) //按下
        {
            if (++j >= KEY_PREVENT_SHAKE_TIME)
            {
                j = KEY_PREVENT_SHAKE_TIME;
                key_input_res |= bit1;
            }
        }
        else //弹起
        {
            j = 0;
            key_input_res &= ~bit1;
        }
    }

    if (SW_G_PIN())
    {
        if (++u >= 5000) // 1s
        {
            u = 5000;
            key_input_res |= bit4;
        }
    }
    else
    {
        if (u > 0)
            u--;
        else
            key_input_res &= ~bit4;
    }

    /********
        4054/4056充电指示: MCU IO均设为输入上拉
        断开充电器: CHRG=1, STD=1;
        充电中: CHRG=0, STD=1;
        充满状态:CHRG=1, STD=0;
        改变PROG引脚电阻可改变充电电流
     * **********/
    if (IC4056_CHRG_PIN() == 1 && IC4056_STDBY_PIN() == 0)
        IC4056_state = 2;
    else if (IC4056_CHRG_PIN() == 0 && IC4056_STDBY_PIN() == 1)
        IC4056_state = 1;
    else
        IC4056_state = 0;

    if (IC4056_state == IC4056_state_old)
    {
        k++;
        if (k >= 2000) // 400ms
        {
            k = 2000;
            if (IC4056_state == 2)
            {
                key_input_res |= bit2; // usb插入
                key_input_res |= bit3; //充满
            }
            else if (IC4056_state == 1)
            {
                key_input_res |= bit2;  // usb插入
                key_input_res &= ~bit3; //没充满
            }
            else
            {
                key_input_res &= ~bit2; // usb断开
                key_input_res &= ~bit3; //没充满电
            }
        }
    }
    else
    {
        k = 0;
        IC4056_state_old = IC4056_state;
    }
}
