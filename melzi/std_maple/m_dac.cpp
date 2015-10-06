//===========================================================================
#include "m_include.h"
#include "m_dac.h"
//===========================================================================
c_dac dac;
//
//==================================================
//  DAC 通道初始化
//==================================================
void c_dac::init(uint8 channel) {
    if (channel>1) return;
    rcc.powerOn(RCC_DAC);
    
    uint32 temp1, temp2 = 0;
    temp1 = DAC->CR;
    temp1 &= ~(0xffff<<(channel*16));
    temp2 |= DAC_CR_BOFF1;              // 输出缓存禁能
    temp2 |= DAC_Trigger_Software;      // 软件触发方式 
    temp2 |= DAC_WaveGeneration_None;   // 叠加波形
    temp2 |= DAC_CR_EN1;                // 通道使能
    temp1 = temp1 | temp2<<(channel*16);
    DAC->CR = temp1;
}
//
//==================================================
//  DAC 通道输出
//==================================================
void c_dac::write(uint8 channel, uint16 data) {
    if (channel) {
        DAC->DHR12R2  = data;
        DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG2;
    } else {
        DAC->DHR12R1 = data;
        DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
    }
}
//===========================================================================
// end of m_dac_c
