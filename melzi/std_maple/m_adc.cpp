//===============================================
#include "m_include.h"
#include "m_adc.h"
//===============================================
adc_dev adc1 = {.regs = (ADC_TypeDef *)ADC1_BASE, .clk_id = RCC_ADC1 };
adc_dev adc2 = {.regs = (ADC_TypeDef *)ADC1_BASE, .clk_id = RCC_ADC1 };
//
//===============================================
// 起动 ADC
//===============================================
void c_adc::init(const adc_dev *dev) {
    //
    //==================================================
    adc_device = (adc_dev *)dev;
    //
    //==================================================
    //== DMA
    rcc.powerOn(RCC_DMA1);
    DMA1_Channel1->CPAR  = (uint32_t)ADC1 + 0x4c;
    DMA1_Channel1->CMAR  = (uint32_t)adOriginal;
    DMA1_Channel1->CNDTR = sizeof(adData)/4;
    uint32 CCR1 = 0;
    CCR1 &= ~DMA_CCR1_DIR;      // P->A
    CCR1 &= ~DMA_CCR1_PINC;     // !P++
    CCR1 |=  DMA_CCR1_MINC;     // A++
    CCR1 |=  DMA_CCR1_PSIZE_1;  // 32bits
    CCR1 |=  DMA_CCR1_MSIZE_1;  // 32bits
    CCR1 |=  DMA_CCR1_CIRC;     // loop
    CCR1 |=  DMA_CCR1_TCIE;     // 完成传输
    CCR1 &= ~DMA_CCR1_MEM2MEM;  // !A->A
    DMA1_Channel1->CCR = CCR1;
    nvic.irqEnable(DMA1_Channel1_IRQn);
    //
    //==================================================
    // ADC
    rcc.set_prescaler(RCC_PRESCALER_ADC, RCC_PCLK2_Div8);   //== 时钟设定9M ADC 最大为 12MHZ
    rcc.powerOn     (dev->clk_id);                          //== RCC 时钟开启
    //
    uint32 CR = dev->regs->CR1;
    CR |= ADC_CR1_SCAN;                                     //== 扫描方式
    dev->regs->CR1 = CR;
    //
    CR  = dev->regs->CR2;                             
    CR &= ~ADC_CR2_EXTSEL;
    CR |= ADC_EXT_EV_SWSTART;                               //== 软件启动
    CR |= ADC_CR2_EXTTRIG;                                  //== 外部触发
    CR |= ADC_CR2_DMA;                                      //== DMA 模式
    dev->regs->CR2 = CR;
    // 
    enable(dev);                                            //== 启用ADC
    calibrate(dev);                                         //== ADC 校准
    set_sample_rate(dev, ADC_SMPR_71_5);                    //== 通道采样
}
//
//===============================================
// adc 开启
//===============================================
inline void c_adc::enable(const adc_dev *dev) {
    dev->regs->CR2 |= ADC_CR2_ADON;
}
//
//===============================================
// adc 自校
//===============================================
void c_adc::calibrate(const adc_dev *dev) {
    __io uint32 *rstcal_bit = bb_perip(&(dev->regs->CR2), 3);
    __io uint32 *cal_bit = bb_perip(&(dev->regs->CR2), 2);

    *rstcal_bit = 1;
     while (*rstcal_bit);
    *cal_bit = 1;
    while (*cal_bit);
}
//
//===============================================
// 选择采样时间
//===============================================
void c_adc::set_sample_rate(const adc_dev *dev, adc_smp_rate smp_rate) {
    uint32 adc_smpr1_val = 0, adc_smpr2_val = 0;
    int i;

    for (i = 0; i < 10; i++) {
        if (i < 8) {
            adc_smpr1_val |= smp_rate << (i * 3);
        }
        adc_smpr2_val |= smp_rate << (i * 3);
    }
    dev->regs->SMPR1 = adc_smpr1_val;
    dev->regs->SMPR2 = adc_smpr2_val;
}
//
//===============================================
// adc 起动
//===============================================
void c_adc::start(void) {
    DMA1_Channel1->CCR    |= DMA_CCR1_EN;
    adc_device->regs->CR2 |= ADC_CR2_SWSTART;
}
//
//===============================================
// adc 通道初始化
//===============================================
void c_adc::initCh(uint8 pin, adc_factor factor) {
    for (int i=0; i<17; i++) {
        if (adCh[i] != 0) continue;
        //
        //================================
        //== ad 通道设定
        pinCh[PIN_MAP[pin].adc_channel] = i;
        adCh[i] = PIN_MAP[pin].adc_channel;
				switch(factor) {
					case  ADC_FACTOR_2:  pinFactor[i] = 1;  pinFactorR[i] = 1;	break;
					case  ADC_FACTOR_4:  pinFactor[i] = 3;  pinFactorR[i] = 2;	break;
					case  ADC_FACTOR_8:  pinFactor[i] = 7;  pinFactorR[i] = 3;	break;
					case  ADC_FACTOR_16: pinFactor[i] = 15; pinFactorR[i] = 4;	break;
					case  ADC_FACTOR_32: pinFactor[i] = 31; pinFactorR[i] = 5;	break;
					default: pinFactor[i] = 1;  pinFactorR[i] = 1;	break;
				}
        //
        //================================
        //== ad 通道序列设定
        volatile uint32 *SQR  = &adc_device->regs->SQR3;
        volatile uint32  SQRT;
        SQR  -= i/6;
        SQRT  = *SQR;
        i = i%6;
        SQRT &= ~(0x1f<<(i*5));
        SQRT |= PIN_MAP[pin].adc_channel<<(i*5);
        *SQR = SQRT;
        //
        //================================
        //== ad 转换数量设定
        SQRT = adc_device->regs->SQR1;
        SQRT&= ~(0xff<<20);
        SQRT|= i<<20;
        adc_device->regs->SQR1 = SQRT;
        DMA1_Channel1->CNDTR = i+1;
        channelCnt           = i+1;
        break;
    }
}
//
//===============================================
// adc 引脚读取
//===============================================
uint16 c_adc::analogRead(uint8 pin) {
    return adData[pinCh[PIN_MAP[pin].adc_channel]];
}
//
//===============================================
// adc 循环读引脚读取
//===============================================
uint16  c_adc::loopGetData(uint8 pin) {
		while (!(DMA1->ISR && DMA1_IT_TC1));
	  __irq_dma1_channel1();
	  return adData[pinCh[PIN_MAP[pin].adc_channel]];
}
//
//===============================================
#ifdef __cplusplus
extern "C" {
#endif
void __irq_dma1_channel1(void) {
    uint32 j;
    for (uint8 i=0; i<adc.channelCnt; i++) {
        j = (uint32)adc.adData[i] * adc.pinFactor[i] + adc.adOriginal[i] + adc.remain[i];
        adc.remain[i] = j % (adc.pinFactor[i] + 1);
        adc.adData[i] = j>>adc.pinFactorR[i];
    }
    adc.adc_device->regs->CR2 |= ADC_CR2_SWSTART;
    DMA1->IFCR = DMA1_IT_GL1 | DMA1_IT_TC1 | DMA1_IT_HT1;
}    
#ifdef __cplusplus
}
#endif
//
//===============================================
c_adc adc(&adc1);

