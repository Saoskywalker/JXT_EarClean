#include "EarClean_timer.h"
#include "types_plus.h"
#include "gpio_board.h"

timer_flag_type EarClean_timer_flag = {0, 0, 0, 0, 0, 0, 0, 0};

void EarClean_timer(void)
{
    static uint8_t count_2ms = 0, count_10ms = 0;

    // 100us int
    EarClean_timer_flag._100us = 1;
    TEST_TOGGLE_PIN();

    if (++count_2ms >= 20)
    {
        count_2ms = 0;
        EarClean_timer_flag._2ms = 1;

        if (++count_10ms >= 5)
        {
            count_10ms = 0;
            EarClean_timer_flag._10ms = 1;
        }
    }
}
