//===============================================
#ifndef __STD_ADC_H__
#define __STD_ADC_H__
#include "stm32f10x.h"
#include "m_rcc.h"
//===============================================
typedef enum adc_extsel_event {
    ADC_EXT_EV_TIM1_CC1         = 0x00000, /**< ADC1, ADC2: Timer 1 CC1 event */
    ADC_EXT_EV_TIM1_CC2         = 0x20000, /**< ADC1, ADC2: Timer 1 CC2 event */
    ADC_EXT_EV_TIM2_CC2         = 0x60000, /**< ADC1, ADC2: Timer 2 CC2 event */
    ADC_EXT_EV_TIM3_TRGO        = 0x80000, /**< ADC1, ADC2: Timer 3 TRGO event */
    ADC_EXT_EV_TIM4_CC4         = 0xA0000, /**< ADC1, ADC2: Timer 4 CC4 event */
    ADC_EXT_EV_EXTI11           = 0xC0000, /**< ADC1, ADC2: EXTI11 event */
    /* Common: */
    ADC_EXT_EV_TIM1_CC3         = 0x40000, /**< ADC1, ADC2, ADC3: Timer 1 CC3 event */
    ADC_EXT_EV_SWSTART          = 0xE0000, /**< ADC1, ADC2, ADC3: Software start */
    /* HD only: */
    ADC_EXT_EV_TIM3_CC1         = 0x00000, 
    ADC_EXT_EV_TIM2_CC3         = 0x20000, 
    ADC_EXT_EV_TIM8_CC1         = 0x60000, 
    ADC_EXT_EV_ADC3_TIM8_TRGO   = 0x80000, 
    ADC_EXT_EV_TIM5_CC1         = 0xA0000, 
    ADC_EXT_EV_ADC12_TIM8_TRGO  = 0xC0000,
    ADC_EXT_EV_TIM5_CC3         = 0xC0000, 
} adc_extsel_event;
//
typedef enum adc_smp_rate {
    ADC_SMPR_1_5,               /**< 1.5 ADC cycles */
    ADC_SMPR_7_5,               /**< 7.5 ADC cycles */
    ADC_SMPR_13_5,              /**< 13.5 ADC cycles */
    ADC_SMPR_28_5,              /**< 28.5 ADC cycles */
    ADC_SMPR_41_5,              /**< 41.5 ADC cycles */
    ADC_SMPR_55_5,              /**< 55.5 ADC cycles */
    ADC_SMPR_71_5,              /**< 71.5 ADC cycles */
    ADC_SMPR_239_5,             /**< 239.5 ADC cycles */
} adc_smp_rate;
//
typedef struct adc_dev {
    ADC_TypeDef     *regs;      /**< Register map */
    rcc_clk_id      clk_id;     /**< RCC clock information */
} adc_dev;
typedef enum adc_factor {
    ADC_FACTOR_2,               
    ADC_FACTOR_4, 
    ADC_FACTOR_8, 
    ADC_FACTOR_16,
    ADC_FACTOR_32,
} adc_factor;
//
class c_adc {
public:
    c_adc  (adc_dev *dev){}
    uint16  analogRead (uint8 pin);
    uint16  loopGetData(uint8 pin);
    void    init    (const adc_dev *dev);
    void    start   ();
    void    initCh   (uint8 pin, adc_factor factor);
    uint16  adData    [17];  // 数据值
    uint32  adOriginal[17];  // 原始数据
    uint8	pinFactor [17];	 // 滤波系数
    uint8	pinFactorR[17];	 // 滤波移位值
    uint8   remain[17];      // 余数
    uint8   channelCnt;
    adc_dev *adc_device;
private:
    void enable          (const adc_dev *dev);
    void calibrate       (const adc_dev *dev);
    void set_sample_rate (const adc_dev *dev, adc_smp_rate smp_rate);
    uint8  adCh  [17];              // 通道值
    uint8  pinCh [17];              // pin 通道表值
};
//
extern adc_dev  adc1;
extern adc_dev  adc2;
extern c_adc    adc;
//===============================================
#ifdef __cplusplus
extern "C" {
#endif
extern void __irq_dma1_channel1(void);   
#ifdef __cplusplus
}
#endif
//===============================================
#endif

