//===============================================
#include "m_include.h"
#include "m_rcc.h"
//================================================================================
const struct rcc_dev_info rcc_dev_table[] = {
    [RCC_GPIOA]  = { .clk_domain = APB2, .line_num = 2 },
    [RCC_GPIOB]  = { .clk_domain = APB2, .line_num = 3 },
    [RCC_GPIOC]  = { .clk_domain = APB2, .line_num = 4 },
    [RCC_GPIOD]  = { .clk_domain = APB2, .line_num = 5 },
    [RCC_AFIO]   = { .clk_domain = APB2, .line_num = 0 },
    [RCC_ADC1]   = { .clk_domain = APB2, .line_num = 9 },
    [RCC_ADC2]   = { .clk_domain = APB2, .line_num = 10 },
    [RCC_ADC3]   = { .clk_domain = APB2, .line_num = 15 },
    [RCC_USART1] = { .clk_domain = APB2, .line_num = 14 },
    [RCC_USART2] = { .clk_domain = APB1, .line_num = 17 },
    [RCC_USART3] = { .clk_domain = APB1, .line_num = 18 },
    [RCC_TIMER1] = { .clk_domain = APB2, .line_num = 11 },
    [RCC_TIMER2] = { .clk_domain = APB1, .line_num = 0 },
    [RCC_TIMER3] = { .clk_domain = APB1, .line_num = 1 },
    [RCC_TIMER4] = { .clk_domain = APB1, .line_num = 2 },
    [RCC_SPI1]   = { .clk_domain = APB2, .line_num = 12 },
    [RCC_SPI2]   = { .clk_domain = APB1, .line_num = 14 },
    [RCC_DMA1]   = { .clk_domain = AHB,  .line_num = 0 },
    [RCC_PWR]    = { .clk_domain = APB1, .line_num = 28},
    [RCC_BKP]    = { .clk_domain = APB1, .line_num = 27},
    [RCC_I2C1]   = { .clk_domain = APB1, .line_num = 21 },
    [RCC_I2C2]   = { .clk_domain = APB1, .line_num = 22 },
    [RCC_CRC]    = { .clk_domain = AHB,  .line_num = 6},
    [RCC_FLITF]  = { .clk_domain = AHB,  .line_num = 4},
    [RCC_SRAM]   = { .clk_domain = AHB,  .line_num = 2},
    [RCC_USB]    = { .clk_domain = APB1, .line_num = 23},
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    [RCC_GPIOE]  = { .clk_domain = APB2, .line_num = 6 },
    [RCC_GPIOF]  = { .clk_domain = APB2, .line_num = 7 },
    [RCC_GPIOG]  = { .clk_domain = APB2, .line_num = 8 },
    [RCC_UART4]  = { .clk_domain = APB1, .line_num = 19 },
    [RCC_UART5]  = { .clk_domain = APB1, .line_num = 20 },
    [RCC_TIMER5] = { .clk_domain = APB1, .line_num = 3 },
    [RCC_TIMER6] = { .clk_domain = APB1, .line_num = 4 },
    [RCC_TIMER7] = { .clk_domain = APB1, .line_num = 5 },
    [RCC_TIMER8] = { .clk_domain = APB2, .line_num = 13 },
    [RCC_FSMC]   = { .clk_domain = AHB,  .line_num = 8 },
    [RCC_DAC]    = { .clk_domain = APB1, .line_num = 29 },
    [RCC_DMA2]   = { .clk_domain = AHB,  .line_num = 1 },
    [RCC_SDIO]   = { .clk_domain = AHB,  .line_num = 10 },
    [RCC_SPI3]   = { .clk_domain = APB1, .line_num = 15 },
#endif
#ifdef STM32_XL_DENSITY
    [RCC_TIMER9]  = { .clk_domain = APB2, .line_num = 19 },
    [RCC_TIMER10] = { .clk_domain = APB2, .line_num = 20 },
    [RCC_TIMER11] = { .clk_domain = APB2, .line_num = 21 },
    [RCC_TIMER12] = { .clk_domain = APB1, .line_num = 6 },
    [RCC_TIMER13] = { .clk_domain = APB1, .line_num = 7 },
    [RCC_TIMER14] = { .clk_domain = APB1, .line_num = 8 },
#endif
};
//================================================================
// 开启电源
//================================================================
void c_rcc::powerOn(rcc_clk_id id)
{
    if (rcc_dev_table[id].clk_domain==AHB) {
        RCC_AHBPeriphClockCmd(1u<<rcc_dev_table[id].line_num, ENABLE);
    } else if (rcc_dev_table[id].clk_domain==APB1) {
        RCC_APB1PeriphClockCmd(1u<<rcc_dev_table[id].line_num, ENABLE);
    } else if (rcc_dev_table[id].clk_domain==APB2) {
        RCC_APB2PeriphClockCmd(1u<<rcc_dev_table[id].line_num, ENABLE); 
    } 
}
//================================================================
// 关闭电源
//================================================================
void c_rcc::powerOff(rcc_clk_id id)
{
    if (rcc_dev_table[id].clk_domain==AHB) {
        RCC_AHBPeriphClockCmd(1u<<rcc_dev_table[id].line_num, DISABLE);
    } else if (rcc_dev_table[id].clk_domain==APB1) {
        RCC_APB1PeriphClockCmd(1u<<rcc_dev_table[id].line_num, DISABLE);
    } else if (rcc_dev_table[id].clk_domain==APB2) {
        RCC_APB2PeriphClockCmd(1u<<rcc_dev_table[id].line_num, DISABLE); 
    }
}
//================================================================
// 复位电源
//================================================================
void c_rcc::powerReset(rcc_clk_id id)
{
    if (rcc_dev_table[id].clk_domain==APB1) {
        RCC_APB1PeriphResetCmd(1u<<rcc_dev_table[id].line_num, ENABLE);
    } else if (rcc_dev_table[id].clk_domain==APB2) {
        RCC_APB2PeriphResetCmd(1u<<rcc_dev_table[id].line_num, ENABLE); 
    }
}
//================================================================
// 设定分频值
//================================================================
inline void c_rcc::do_set_prescaler(const uint32 *masks,
                                    rcc_prescaler prescaler,
                                    uint32 divider) {
    uint32 cfgr = RCC->CFGR;
    cfgr &= ~masks[prescaler];
    cfgr |= divider;
    RCC->CFGR = cfgr;
}
//================================================================
// 设定分频值
//================================================================
void c_rcc::set_prescaler(rcc_prescaler prescaler, uint32 divider) {
    static const uint32 masks[] = {
        [RCC_PRESCALER_AHB] = RCC_CFGR_HPRE,
        [RCC_PRESCALER_APB1] = RCC_CFGR_PPRE1,
        [RCC_PRESCALER_APB2] = RCC_CFGR_PPRE2,
        [RCC_PRESCALER_USB] = RCC_CFGR_USBPRE,
        [RCC_PRESCALER_ADC] = RCC_CFGR_ADCPRE,
    };
    do_set_prescaler(masks, prescaler, divider);
}
//================================================================
c_rcc ::c_rcc(int begin) {
}
c_rcc rcc(true);


