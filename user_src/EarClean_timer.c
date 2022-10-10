#include "EarClean_timer.h"
#include "types_plus.h"
#include "gpio_board.h"
#include "display_define.h"
#include "key_board.h"

timer_flag_type EarClean_timer_flag = {0, 0, 0, 0, 0, 0, 0, 0};

void EarClean_timer(void)
{
    static uint8_t count_2ms = 0, count_10ms = 0, count_100ms = 0;

    // 200us int
    EarClean_timer_flag._200us = 1;
    // TEST_TOGGLE_PIN();

    key_input_check_timer();

    if (++count_2ms >= 10)
    {
        count_2ms = 0;
        EarClean_timer_flag._2ms = 1;
        Led_Scan();
        if (++count_10ms >= 5)
        {
            count_10ms = 0;
            EarClean_timer_flag._10ms = 1;

            if(++count_100ms>=10)
            {
                count_100ms = 0;
                EarClean_timer_flag._100ms = 1;
            }
        }
    }
}
