//================================================================
#ifndef __STD_GPIO_H__
#define __STD_GPIO_H__
//================================================================
#include "stm32f10x.h"
#include "m_rcc.h"
#include "m_exti.h"
//================================================================
typedef enum WiringPinMode {
    OUTPUT, 
    OUTPUT_OPEN_DRAIN,
    OUTPUT_AF_OD,
    OUTPUT_AF_PP,
    INPUT, 
    INPUT_ANALOG, 
    INPUT_PULLUP,
    INPUT_PULLDOWN, 
    INPUT_FLOATING, 
    PWM, 
    PWM_OPEN_DRAIN, 
} WiringPinMode;

#define GPIO_CR_CNF                     (0x3 << 2)
#define GPIO_CR_CNF_INPUT_ANALOG        (0x0 << 2)
#define GPIO_CR_CNF_INPUT_FLOATING      (0x1 << 2)
#define GPIO_CR_CNF_INPUT_PU_PD         (0x2 << 2)
#define GPIO_CR_CNF_OUTPUT_PP           (0x0 << 2)
#define GPIO_CR_CNF_OUTPUT_OD           (0x1 << 2)
#define GPIO_CR_CNF_AF_OUTPUT_PP        (0x2 << 2)
#define GPIO_CR_CNF_AF_OUTPUT_OD        (0x3 << 2)
#define GPIO_CR_MODE                    0x3
#define GPIO_CR_MODE_INPUT              0x0
#define GPIO_CR_MODE_OUTPUT_10MHZ       0x1
#define GPIO_CR_MODE_OUTPUT_2MHZ        0x2
#define GPIO_CR_MODE_OUTPUT_50MHZ       0x3

typedef enum gpio_pin_mode {
    GPIO_OUTPUT_PP      = GPIO_CR_CNF_OUTPUT_PP | GPIO_CR_MODE_OUTPUT_50MHZ,        /** Output push-pull. */
    GPIO_OUTPUT_OD      = GPIO_CR_CNF_OUTPUT_OD | GPIO_CR_MODE_OUTPUT_50MHZ,        /** Output open-drain. */
    GPIO_AF_OUTPUT_PP   = GPIO_CR_CNF_AF_OUTPUT_PP | GPIO_CR_MODE_OUTPUT_50MHZ,     /** Alternate function output push-pull. */
    GPIO_AF_OUTPUT_OD   = GPIO_CR_CNF_AF_OUTPUT_OD | GPIO_CR_MODE_OUTPUT_50MHZ,     /** Alternate function output open drain. */
    GPIO_INPUT_ANALOG   = GPIO_CR_CNF_INPUT_ANALOG | GPIO_CR_MODE_INPUT,            /** Analog input. */
    GPIO_INPUT_FLOATING = GPIO_CR_CNF_INPUT_FLOATING | GPIO_CR_MODE_INPUT,          /** Input floating. */
    GPIO_INPUT_PD       = GPIO_CR_CNF_INPUT_PU_PD | GPIO_CR_MODE_INPUT,             /** Input pull-down. */
    GPIO_INPUT_PU,                                              
} gpio_pin_mode;

typedef struct gpio_dev {
    GPIO_TypeDef    *regs;       /**< Register map */
    rcc_clk_id      clk_id;      /**< RCC clock information */
    exti_cfg        exti_port;
} gpio_dev;
//================================================================
//
//================================================================
class c_gpio {
public:
    c_gpio  (gpio_dev *);
    void    pinMode             (uint8 pin, WiringPinMode mode);
    void    setPwmFormat        (uint8 pin, uint16 Period, uint8 active);
    void    setPwmDuty          (uint8 pin, uint16 duty  );
    uint16  getPwmPeriod        (uint8 pin);
    boolean digitalRead         (uint8 pin);
    void    digitalWrite        (uint8 pin, uint8 val);
    void    toggle              (uint8 pin);
    uint8   isButtonPressed     (uint8 pin, uint32 pressedLevel);
    uint8   waitForButtonPress  (uint8 pin, uint32 pressedLevel, uint32 timeout);
private:
    inline uint32   gpio_read_bit  (gpio_dev *dev, uint8 pin);
    inline void     gpio_write_bit (gpio_dev *dev, uint8 pin, uint8 val);
    inline void     gpio_toggle_bit(gpio_dev *dev, uint8 pin);
    inline void     gpio_set_mode  (gpio_dev *dev, uint8 pin, gpio_pin_mode mode);
};

extern c_gpio gpio;
extern gpio_dev gpioa;
extern gpio_dev gpiob;
extern gpio_dev gpioc;
extern gpio_dev gpiod;
//================================================================
#endif
//================================================================

