//===============================================
#include "m_include.h"
#include "m_timer.h"
//===========================================================================================
timer_dev timer1 = {.regs = (timer_reg_map*)TIM1_BASE, .clk_id = RCC_TIMER1, .type = TIMER_GENERAL, 0};
timer_dev timer2 = {.regs = (timer_reg_map*)TIM2_BASE, .clk_id = RCC_TIMER2, .type = TIMER_GENERAL, 0};
timer_dev timer3 = {.regs = (timer_reg_map*)TIM3_BASE, .clk_id = RCC_TIMER3, .type = TIMER_GENERAL, 0};
timer_dev timer4 = {.regs = (timer_reg_map*)TIM4_BASE, .clk_id = RCC_TIMER4, .type = TIMER_GENERAL, 0};
timer_dev timer8 = {.regs = (timer_reg_map*)TIM8_BASE, .clk_id = RCC_TIMER8, .type = TIMER_GENERAL, 0};
c_timer Timer((timer_dev *)0);
timer_dev *TIMER1 = &timer1;
timer_dev *TIMER2 = &timer2;
timer_dev *TIMER3 = &timer3;
timer_dev *TIMER4 = &timer4;
timer_dev *TIMER8 = &timer8;
//===============================================
// 实例化
//===============================================
c_timer::c_timer(timer_dev *dev) {
}

//===============================================
// 时钟开启
//===============================================
void c_timer::init(timer_dev *dev) {
    const uint16 full_overflow = 0xFFFF;
    const uint16 half_duty     = 0x8FFF;

    //===================================
    // 1.定时器 初始化
    //===================================
    rcc.powerOn(dev->clk_id);
    pause(dev);
    dev->regs->CR1.bits.ARPE  = 1;
    dev->regs->PSC            = 1;
    dev->regs->SR.all         = 0;
    dev->regs->DIER.all       = 0;
    dev->regs->DIER.bits.UIE  = 0;
    setOverflow(dev,full_overflow);
    for (uint8 channel = 1; channel <= 4; channel++) {
        setCompare(dev, channel, half_duty);
        setOcModle(dev, channel, TIMER_OC_MODE_PWM_1, 0);
    } 
    dev->regs->EGR.bits.UG    = 1;
    resume(dev);
}

//===============================================
//
//===============================================
void c_timer::setPinMode(timer_dev *dev, uint8 channel, timer_mode mode) {
   if (dev->type == TIMER_BASIC)
        return;
    switch (mode) {
    case TIMER_DISABLED:
        disableChannel(dev, channel);
        break;
    case TIMER_PWM:
        disableChannel(dev, channel);
        setOcModle    (dev, channel, TIMER_OC_MODE_PWM_1, 0);
        if (dev != TIMER1) {        //??
            setOcEnable   (dev, channel);
        }
        break;
    case TIMER_OUTPUT_COMPARE:
//         output_compare_mode(dev, channel);
        break;
    }
}

//===============================================
// 关闭通道
//===============================================
void c_timer::disableChannel(timer_dev *dev, int channel) {
    detachInterrupt(dev, channel);
    dev->regs->CCER.all &= ~(1<<((channel-1)*4));
}

//===============================================
// 比较输出开启
//===============================================
void c_timer::setOcEnable(timer_dev *dev, uint8 channel) {
    *bb_perip(&(dev->regs->CCER.all), 4 * (channel - 1)) = 1;
}

//===============================================
// 比较输出极性
//===============================================
void c_timer::setOcActive(timer_dev *dev, uint8 channel, uint8 active) {
    *bb_perip(&(dev->regs->CCER.all), 4 * (channel - 1) + 1) = active ? (0) : (1);
}

//===============================================
// 比较输出模式
//===============================================
void c_timer::setOcModle(timer_dev *dev, uint8 channel, timer_oc_mode mode, uint8 flags) {
    __io uint32 *ccmr = &dev->regs->CCMR1.all + (((channel - 1) >> 1) & 1);
    uint8 shift = 8 * (1 - (channel & 1));
    uint32 tmp = *ccmr;
    tmp &= ~(0xFF << shift);
    tmp |= (mode | flags) << shift;
    *ccmr = tmp;
} 

//===============================================
// 设定周期，根据周期计算分频
//===============================================
uint16 c_timer::setPeriod(timer_dev *dev, uint32 microseconds) {
        // Not the best way to handle this edge case?
    if (!microseconds) {
        setPrescaleFactor(dev, 1);
        setOverflow      (dev, 1);
        return dev->regs->ARR;
    }
    uint32 period_cyc = microseconds * CYCLES_PER_MICROSECOND;
    uint16 prescaler  = (uint16)(period_cyc / 0xffff + 1);
    uint16 overflow   = (uint16)((period_cyc + (prescaler / 2)) / prescaler);
    setPrescaleFactor(dev, prescaler);
    setOverflow      (dev, overflow );
    return overflow;
}

//===============================================
// 暂停中断函数
//===============================================
void c_timer::pauseInterrupt(timer_dev *dev, int channel) {
    dev->regs->DIER.all &= ~(1<<channel);
}

//===============================================
// 回复中断函数
//===============================================
void c_timer::resumeInterrupt(timer_dev *dev, int channel) {
    dev->regs->SR.all   &= ~(1<<channel);
    dev->regs->DIER.all |=   1<<channel;
}

//===============================================
// 设定通道回调函数
//===============================================
void c_timer::attachInterrupt(timer_dev *dev, int channel, voidFuncPtr handler) {
    dev->handlers[channel-1] = handler;
    dev->regs->DIER.all |= 1<<channel;
    if      (dev->clk_id == RCC_TIMER1)    nvic.irqEnable(TIM1_CC_IRQn);
    else if (dev->clk_id == RCC_TIMER2)    nvic.irqEnable(TIM2_IRQn);
    else if (dev->clk_id == RCC_TIMER3)    nvic.irqEnable(TIM3_IRQn);
    else if (dev->clk_id == RCC_TIMER4)    nvic.irqEnable(TIM4_IRQn);
}

//===============================================
// 取消通道回调函数
//===============================================
void c_timer::detachInterrupt(timer_dev *dev, int channel) {
    dev->regs->DIER.all &= ~(1<<channel);
    dev->handlers[channel-1] = NULL;
}

//===============================================
// 中断函数
//===============================================
#ifdef __cplusplus
extern "C" {
#endif
#define handle_irq(dier_sr, irq_mask, handlers, iid, handled_irq) do {    \
            if ((dier_sr) & (irq_mask)) {                                     \
                void (*__handler)() = (handlers)[iid];                     \
                if (__handler) {__handler();}                              \
                handled_irq |= irq_mask;                                      \
            }  } while (0)                                                    
    
static void dispatch_adv_cc(timer_dev *dev) {
    timer_reg_map *regs = dev->regs;
    uint32 dsr = regs->DIER.all & regs->SR.all;
    void (**hs)() = dev->handlers;
    uint32 handled = 0;
    
    handle_irq(dsr, TIM_SR_CC4IF, hs, 4, handled);
    handle_irq(dsr, TIM_SR_CC3IF, hs, 2, handled);
    handle_irq(dsr, TIM_SR_CC2IF, hs, 1, handled);
    handle_irq(dsr, TIM_SR_CC1IF, hs, 0, handled);

    regs->SR.all &= ~handled;
}

static void dispatch_general(timer_dev *dev) {
    timer_reg_map *regs = dev->regs;
    uint32 dsr = regs->DIER.all & regs->SR.all;
    void (**hs)() = dev->handlers;
    uint32 handled = 0;

    handle_irq(dsr, TIM_SR_COMIF, hs, 5, handled);
    handle_irq(dsr, TIM_SR_CC4IF, hs, 3, handled);
    handle_irq(dsr, TIM_SR_CC3IF, hs, 2, handled);
    handle_irq(dsr, TIM_SR_CC2IF, hs, 1, handled);
    handle_irq(dsr, TIM_SR_CC1IF, hs, 0, handled);
    handle_irq(dsr, TIM_SR_UIF,   hs, 4, handled);

    regs->SR.all &= ~handled;
}
void __irq_tim1_cc(void) {
    dispatch_adv_cc(TIMER1);
}
void __irq_tim2(void) {
    dispatch_general(TIMER2);
}
void __irq_tim3(void) {
    dispatch_general(TIMER3);
}
void __irq_tim4(void) {
    dispatch_general(TIMER4);
}    
void __irq_tim8(void) {
    dispatch_general(TIMER8);
} 
#ifdef __cplusplus
}
#endif

//===========================================================================================


