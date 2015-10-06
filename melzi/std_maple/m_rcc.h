//===============================================
#ifndef __STD_RCC__
#define __STD_RCC__
//===============================================
#define APB1    RCC_APB1
#define APB2    RCC_APB2
#define AHB     RCC_AHB

typedef enum rcc_clk_domain {
    RCC_APB1,
    RCC_APB2,
    RCC_AHB
} rcc_clk_domain;

struct rcc_dev_info {
    rcc_clk_domain clk_domain;
    uint8         line_num;
};
//===============================================
// 时钟 ID
//===============================================
typedef enum rcc_clk_id {
    RCC_ADC1,
    RCC_ADC2,
    RCC_ADC3,
    RCC_AFIO,
    RCC_BKP,
    RCC_CRC,
    RCC_DAC,
    RCC_DMA1,
    RCC_DMA2,
    RCC_FLITF,
    RCC_FSMC,
    RCC_GPIOA,
    RCC_GPIOB,
    RCC_GPIOC,
    RCC_GPIOD,
    RCC_GPIOE,
    RCC_GPIOF,
    RCC_GPIOG,
    RCC_I2C1,
    RCC_I2C2,
    RCC_PWR,
    RCC_SDIO,
    RCC_SPI1,
    RCC_SPI2,
    RCC_SPI3,
    RCC_SRAM,
    RCC_TIMER1,
    RCC_TIMER2,
    RCC_TIMER3,
    RCC_TIMER4,
    RCC_TIMER5,
    RCC_TIMER6,
    RCC_TIMER7,
    RCC_TIMER8,
    RCC_TIMER9,
    RCC_TIMER10,
    RCC_TIMER11,
    RCC_TIMER12,
    RCC_TIMER13,
    RCC_TIMER14,
    RCC_USART1,
    RCC_USART2,
    RCC_USART3,
    RCC_UART4,
    RCC_UART5,
    RCC_USB,
} rcc_clk_id;

/**
 * @brief STM32F1 Prescaler identifiers
 * @see rcc_set_prescaler()
 */
typedef enum rcc_prescaler {
    RCC_PRESCALER_AHB,
    RCC_PRESCALER_APB1,
    RCC_PRESCALER_APB2,
    RCC_PRESCALER_USB,
    RCC_PRESCALER_ADC
} rcc_prescaler;

class c_rcc {
    public:
        c_rcc          (int);
        void powerOn   (rcc_clk_id id);
        void powerOff  (rcc_clk_id id);
        void powerReset(rcc_clk_id id);
        void set_prescaler(rcc_prescaler prescaler, uint32 divider);
        inline void do_set_prescaler(const uint32 *masks, rcc_prescaler prescaler,uint32 divider);
        void begin(void) {}
};

extern c_rcc rcc;
#endif
