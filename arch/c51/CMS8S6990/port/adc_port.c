#include "adc_port.h"

uint8_t MM_adc1_init(void)
{
    GPIO_SET_MUX_MODE(P32CFG, GPIO_P32_MUX_AN14); //配置为模拟IO
    GPIO_SET_MUX_MODE(P05CFG, GPIO_P05_MUX_AN5); //配置为模拟IO
    GPIO_SET_MUX_MODE(P04CFG, GPIO_P04_MUX_AN4); //配置为模拟IO

    //设置ADC的运行模式
    ADC_ConfigRunMode(ADC_CLK_DIV_64, ADC_RESULT_LEFT); //设置ADC时钟为系统时钟的64分频，ADC结果为左对齐

    //设置ADC转换通道
    ADC_EnableChannel(ADC_CH_14); //切换通道后建议500ns后开采样

    //设置参考电压
    ADC_DisableLDO();
    // ADC_EnableLDO(); //开启后只能使用MCU LDO参考电压, 关闭后使用VDD参考电压
    // ADC_ConfigADCVref(ADC_VREF_3V);		//ADC_VREF_1P2V, ADC_VREF_2V, ADC_VREF_2P4V, ADC_VREF_3V

    //设置ADC中断
    // ADC_EnableInt();
    // IRQ_SET_PRIORITY(IRQ_ADC,IRQ_PRIORITY_HIGH);
    // IRQ_ALL_ENABLE();

    //开启ADC
    ADC_Start();

    return 0;
}

uint8_t MM_adc1_exit(void)
{
    return 0;
}

void MM_adc1_start(void)
{
    //开启ADC模块
    ADC_Start();
}

void MM_adc1_suspend(void)
{
    //停止ADC模块
    ADC_Stop();
}

void MM_adc1_set_ref(uint8_t ref)
{
    //设置参考电压
    if (ref == MTF_ADC_VREF_VDD)
    {
        ADC_DisableLDO();
    }
    else
    {
        //设置ADC LDO
        ADC_EnableLDO();        //开启后只能使用MCU LDO参考电压, 关闭后使用VDD参考电压
        ADC_ConfigADCVref(ref); // ADC_VREF_1P2V, ADC_VREF_2V, ADC_VREF_2P4V, ADC_VREF_3V
    }
}
