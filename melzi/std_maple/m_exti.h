//===============================================
#ifndef __M_EXIT_H__
#define __M_EXIT_H__
//===============================================
#include "typeDefine.h"
typedef enum exti_cfg {
    EXTI_PA,                    /**< Use PAx pin */
    EXTI_PB,                    /**< Use PBx pin */
    EXTI_PC,                    /**< Use PCx pin */
    EXTI_PD,                    /**< Use PDx pin */
    EXTI_PE,                    /**< Use PEx pin */
    EXTI_PF,                    /**< Use PFx pin */
    EXTI_PG,                    /**< Use PGx pin */
    EXTI_PH,                    /**< Use PHx pin */
    EXTI_PI,                    /**< Use PIx pin */
} exti_cfg;
//===============================================
// 中断电平选择
typedef enum exti_trigger_mode {
    EXTI_RISING,                /**< Trigger on the rising edge */
    EXTI_FALLING,               /**< Trigger on the falling edge */
    EXTI_RISING_FALLING         /**< Trigger on both the rising and falling edges */
} exti_trigger_mode;
//===============================================
// 类
class c_exti {
public:
    void  begin  (uint8 pin, voidFuncPtr handler, exti_trigger_mode mode);
    void  close  (uint8 pin);
    void  setMode(uint8 pin,exti_trigger_mode mode);
    void  pause  (uint8 pin);
    void  resume (uint8 pin);
};
extern c_exti exti;
#endif

