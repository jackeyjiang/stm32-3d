//============================================================================================
#ifndef __STD_TIMER_H__
#define __STD_TIMER_H__
//============================================================================================
#include "typeDefine.h"
#include "m_rcc.h"
//============================================================================================
typedef enum timer_mode {
    TIMER_DISABLED,
    TIMER_PWM,
    TIMER_OUTPUT_COMPARE,
} timer_mode;

typedef enum timer_type {
    TIMER_ADVANCED,             /**< Advanced type */
    TIMER_GENERAL,              /**< General purpose type */
    TIMER_BASIC,                /**< Basic type */
} timer_type;

typedef enum timer_oc_mode {
    TIMER_OC_MODE_FROZEN            = 0 << 4,
    TIMER_OC_MODE_ACTIVE_ON_MATCH   = 1 << 4,
    TIMER_OC_MODE_INACTIVE_ON_MATCH = 2 << 4,
    TIMER_OC_MODE_TOGGLE            = 3 << 4,
    TIMER_OC_MODE_FORCE_INACTIVE    = 4 << 4,
    TIMER_OC_MODE_FORCE_ACTIVE      = 5 << 4,
    TIMER_OC_MODE_PWM_1             = 6 << 4,
    TIMER_OC_MODE_PWM_2             = 7 << 4,
} timer_oc_mode;

//== CR1 =====================================================================================
typedef struct {
    uint16  CEN     :1; // bit 0
    uint16  UDIS    :1; // bit 1
    uint16  URS     :1; // bit 2
    uint16  OPM     :1; // bit 3
    uint16  DIR     :1; // bit 4
    uint16  CMS     :2; // bit 6-5
    uint16  ARPE    :1; // bit 7
    uint16  CKD     :2; // bit 9-8
    uint16  NoUse1  :6; 
    uint16  NoUse2  :16; 
}ts_timer_CR1_bits;
typedef union {
    ts_timer_CR1_bits   bits;
    uint32              all;
}tu_timer_CR1;

//== CR2 ========================================
typedef struct {
    uint16  CCPC    :1; // bit 0
    uint16  NoUse1  :1; // bit 1
    uint16  CCUS    :1; // bit 2
    uint16  CCDS    :1; // bit 3
    uint16  MMS     :3; // bit 6-4
    uint16  TI1S    :1; // bit 7
    uint16  OISO    :1; // bit 8
    uint16  OIS1N   :1; // bit 9
    uint16  OIS2    :1; // bit 10
    uint16  OIS2N   :1; // bit 11
    uint16  OIS3    :1; // bit 12
    uint16  OIS3N   :1; // bit 13
    uint16  OIS4    :1; // bit 14
    uint16  NoUse2  :1; // 
    uint16  NoUse3  :16;//
}ts_timer_CR2_bits;
typedef union {
    ts_timer_CR2_bits   bits;
    uint32              all;
}tu_timer_CR2;

//== SMCR =======================================
typedef struct {
    uint16  SMS     :3; // 2-0
    uint16  NoUse1  :1; // 3
    uint16  TS      :3; // 6-4
    uint16  MSM     :1; // 7
    uint16  ETF     :4; // 11-8
    uint16  ETPS    :2; // 13-12
    uint16  ECE     :1; // 14
    uint16  ETP     :1; // 15
    uint16  NoUse2  :16;
}ts_timer_SMCR_bits;
typedef union {
    ts_timer_SMCR_bits  bits;
    uint32              all;
}tu_timer_SMCR;

//== DIER =======================================
typedef struct {
    uint16  UIE     :1; // bit 0
    uint16  CC1IE   :1; // bit 1
    uint16  CC2IE   :1; // bit 2
    uint16  CC3IE   :1; // bit 3
    uint16  CC4IE   :1; // bit 4
    uint16  COMIE   :1; // bit 5
    uint16  TIE     :1; // bit 6
    uint16  BIE     :1; // bit 7
    uint16  UDE     :1; // bit 8
    uint16  CC1DE   :1; // bit 9
    uint16  CC2DE   :1; // bit 10
    uint16  CC3DE   :1; // bit 11
    uint16  CC4DE   :1; // bit 12
    uint16  COMDE   :1; // bit 13
    uint16  TDE     :1; // bit 14
    uint16  NoUse1  :1;
    uint16  NoUse2  :16;
}ts_timer_DIER_bits;
typedef union {
    ts_timer_DIER_bits  bits;
    uint32              all;
}tu_timer_DIER;

//== SR =======================================
typedef struct {
    uint16  UIF     :1; // bit 0
    uint16  CC1IF   :1; // bit 1
    uint16  CC2IF   :1; // bit 2
    uint16  CC3IF   :1; // bit 3
    uint16  CC4IF   :1; // bit 4
    uint16  COMIF   :1; // bit 5
    uint16  TIF     :1; // bit 6
    uint16  BIF     :1; // bit 7
    uint16  NoUse1  :1; // bit 8
    uint16  CC1DF   :1; // bit 9
    uint16  CC2DF   :1; // bit 10
    uint16  CC3DF   :1; // bit 11
    uint16  CC4DF   :1; // bit 12
    uint16  NoUse2  :3;
    uint16  NoUse3  :16;
}ts_timer_SR_bits;
typedef union {
    ts_timer_DIER_bits  bits;
    uint32              all;
}tu_timer_SR;

//== EGR =======================================
typedef struct {
    uint16  UG      :1; // bit 0
    uint16  CC1G    :1; // bit 1
    uint16  CC2G    :1; // bit 2
    uint16  CC3G    :1; // bit 3
    uint16  CC4G    :1; // bit 4
    uint16  NoUse1  :1; // bit 5
    uint16  TG      :1; // bit 6
    uint16  NoUse2  :9;
    uint16  NoUse3  :16;
}ts_timer_EGR_bits;
typedef union {
    ts_timer_EGR_bits   bits;
    uint32              all;
}tu_timer_EGR;

//== CCMR1 =====================================
typedef struct {
    uint16  CC1S    :2; // bit 1-0
    uint16  OC1FE   :1; // bit 2
    uint16  OC1PE   :1; // bit 3
    uint16  OC1M    :3; // bit 6-4
    uint16  OC1CE   :1; // bit 7
    uint16  CC2S    :2; // bit 9-8
    uint16  OC2FE   :1; // bit 10
    uint16  OC2PE   :1; // bit 11
    uint16  OC2M    :3; // bit 12-14
    uint16  OC2CE   :1; // bit 15
    uint16  NoUse   :16;
}ts_timer_CCMR1_bits;
typedef union {
    ts_timer_CCMR1_bits bits;
    uint32              all;
}tu_timer_CCMR1;

//== CCMR2 =====================================
typedef struct {
    uint16  CC3S    :2; // bit 1-0
    uint16  OC3FE   :1; // bit 2
    uint16  OC3PE   :1; // bit 3
    uint16  OC3M    :3; // bit 6-4
    uint16  OC3CE   :1; // bit 7
    uint16  CC4S    :2; // bit 9-8
    uint16  OC4FE   :1; // bit 10
    uint16  OC4PE   :1; // bit 11
    uint16  OC4M    :3; // bit 12-14
    uint16  OC4CE   :1; // bit 15
    uint16  NoUse   :16;
}ts_timer_CCMR2_bits;
typedef union {
    ts_timer_CCMR2_bits bits;
    uint32              all;
}tu_timer_CCMR2;

//== CCER =====================================
typedef struct {
    uint16  CC1E    :1; // bit 0
    uint16  CC1P    :1; // bit 1
    uint16  NoUse1  :2; // bit 3-2
    uint16  CC2E    :1; // bit 4
    uint16  CC2P    :1; // bit 5
    uint16  NoUse2  :2; // bit 7-6
    uint16  CC3E    :1; // bit 8
    uint16  CC3P    :1; // bit 9
    uint16  NoUse3  :2; // bit 11-10
    uint16  CC4E    :1; // bit 12
    uint16  CC4P    :1; // bit 13
    uint16  NoUse4  :2; // bit 15-14
    uint16  NoUse5  :16;
}ts_timer_CCER_bits;
typedef union {
    ts_timer_CCER_bits  bits;
    uint32              all;
}tu_timer_CCER;

//==========================================================================================
typedef struct timer_reg_map {
    __io tu_timer_CR1   CR1;            /**< Control register 1 */
    __io tu_timer_CR2   CR2;            /**< Control register 2 */
    __io tu_timer_SMCR  SMCR;           /**< Slave mode control register */
    __io tu_timer_DIER  DIER;           /**< DMA/interrupt enable register */
    __io tu_timer_SR    SR;             /**< Status register */
    __io tu_timer_EGR   EGR;            /**< Event generation register  */
    __io tu_timer_CCMR1 CCMR1;          /**< Capture/compare mode register 1 */
    __io tu_timer_CCMR2 CCMR2;          /**< Capture/compare mode register 2 */
    __io tu_timer_CCER  CCER;           /**< Capture/compare enable register */
    __io uint32 CNT;            /**< Counter */
    __io uint32 PSC;            /**< Prescaler */
    __io uint32 ARR;            /**< Auto-reload register */
    __io uint32 RCR;            /**< Repetition counter register */
    __io uint32 CCR1;           /**< Capture/compare register 1 */
    __io uint32 CCR2;           /**< Capture/compare register 2 */
    __io uint32 CCR3;           /**< Capture/compare register 3 */
    __io uint32 CCR4;           /**< Capture/compare register 4 */
    __io uint32 BDTR;           /**< Break and dead-time register */
    __io uint32 DCR;            /**< DMA control register */
    __io uint32 DMAR;           /**< DMA address for full transfer */
} timer_reg_map;
//==========================================================================================
typedef struct timer_dev {
    timer_reg_map  *regs;        
    rcc_clk_id      clk_id;      
    timer_type      type;        
    voidFuncPtr     handlers[6];
} timer_dev;
//==========================================================================================
class c_timer {
    
public:
    c_timer(timer_dev *);
    void    setPinMode(timer_dev *dev, uint8 channel, timer_mode mode);
    void    init(timer_dev *dev);
    void    pause  (timer_dev *dev)  {dev->regs->CR1.bits.CEN = 0;} // 停止
    void    resume (timer_dev *dev)  {dev->regs->CR1.bits.CEN = 1;} // 重启   
    void    pauseInterrupt (timer_dev *dev, int channel);           // 暂停中断函数
    void    resumeInterrupt(timer_dev *dev, int channel);           // 起动中断函数
    void    setPrescaleFactor(timer_dev *dev, uint32 factor) {// 设定分频值
                dev->regs->PSC = factor;
                dev->regs->EGR.bits.UG = 1;}
    void    setOverflow(timer_dev *dev, uint16 val) {dev->regs->ARR = val;     }          // 设定周期值溢出值
    uint16  getOverflow(timer_dev *dev)             {return dev->regs->ARR ;   }          // 读取周期值溢出值
    uint16  setPeriod(timer_dev *dev, uint32 microseconds);             // 设定周期，根据周期计算分频
    void    setOcActive(timer_dev *dev, uint8 channel, uint8 active);
    void    setCompare(timer_dev *dev, int channel, uint16 compare){    // 设定通道比较值
                __io uint32 *ccr = &dev->regs->CCR1 + (channel - 1);
                *ccr = compare;
            }  
    void    attachInterrupt(timer_dev *dev, int channel, voidFuncPtr handler);
    void    detachInterrupt(timer_dev *dev, int channel);   
    uint16  getCount(timer_dev *dev) { return dev->regs->CNT;    }                          // 得到计数值                  
private: 
    void    setCount(timer_dev *dev, uint16 val) { dev->regs->CNT = val;}                   // 设定计数值        
    void    setOcModle (timer_dev *dev, uint8 channel, timer_oc_mode mode, uint8 flags);
    void    setOcEnable(timer_dev *dev, uint8 channel   );     
    void    disableChannel (timer_dev *dev, int channel );
};

void timer_set_mode(timer_dev *dev, uint8 channel, timer_mode mode);

extern c_timer Timer;
extern timer_dev timer1;
extern timer_dev timer2;
extern timer_dev timer3;
extern timer_dev timer4;
extern timer_dev timer8;
#endif

