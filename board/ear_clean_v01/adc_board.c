#include "adc_board.h"
// #include "stdio.h"

// #define MTF_ADC_debug(...) printf(__VA_ARGS__)
/* 
#define window_size 8
typedef struct
{
    unsigned char data_num;
    unsigned char data_full;
    uint16_t buffer[window_size];
} filter_type;
static filter_type battery_buf = {0, 0, 0, 0, 0, 0, 0}, current_buf = {0, 0, 0, 0, 0, 0, 0}, key_buf = {0, 0, 0, 0, 0, 0, 0};
uint16_t sliding_middle_filter(uint16_t value, filter_type *prt)
{
    uint16_t output = 0;
    unsigned char i;

    if (prt->data_full < window_size) //不满窗口，先填充
    {
        prt->buffer[prt->data_full] = value;
        prt->data_full++;
        output = value; //返回相同的值
    }
    else
    {
        prt->buffer[prt->data_num] = value;
        if (++(prt->data_num) >= window_size)
            prt->data_num = 0;

        for (i = 0; i < window_size; i++)
            output += prt->buffer[i];

        output = output>>3; //x/8
    }

    return output;
}
 */
uint16_t _adc_value[ADC_CHANNEL_TOTAL] = {2047, 2047, 2047};
void adc_run(void)
{
    
    static uint16_t adc_result = 20000;
    static uint8_t sample_count = 255, channel_count = 0, _reject_count = 0;

    if (sample_count >= 8)
    {
        sample_count = 0;                            //单通道采样次数
        _reject_count = 0;
        // _adc_value[channel_count] = adc_result >> 3; // adc_result/8, 注意复位的第一次值
        //因在51 MCU上 _adc_value[channel_count] 处理慢
        if (channel_count == 0)
            _adc_value[0] = adc_result >> 3;
        else if (channel_count == 1)
            _adc_value[1] = adc_result >> 3;
        else if (channel_count == 2)
            _adc_value[2] = adc_result >> 3;
        adc_result = 0;

        if (++channel_count >= ADC_CHANNEL_TOTAL)
        {
            channel_count = 0;
            // printf("ad: %d, %d, %d\r\n", _adc_value[0], _adc_value[1], _adc_value[2]);
        }

        //为保证结果准确度, 切换通道后建议500ns后开采样
        if (channel_count == 0)
        {
            MM_adc1_set_ref(MTF_ADC_VREF_2P4V);
            MM_adc1_set_channel(MTF_ADC_BATTERY);
        }
        else if (channel_count == 1)
        {
            MM_adc1_set_ref(MTF_ADC_VREF_2P4V);
            MM_adc1_set_channel(MTF_ADC_MOTOR_CURRENT);
        }
        else
        {
            MM_adc1_set_ref(MTF_ADC_VREF_VDD);
            MM_adc1_set_channel(MTF_ADC_KEY);
        }
    }
    else
    {
        if (++_reject_count >= 2)
        {
            // if (MM_adc1_get_state() == 0) //是否转换完成
            {
                adc_result += MM_adc1_get_result(); //获取AD值
                sample_count++;
            }
        }
        MM_adc1_convert_start(); //开启转换
    }
}
