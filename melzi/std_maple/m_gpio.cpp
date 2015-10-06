//===============================================
#include "m_include.h"
#include "m_gpio.h"
//===============================================
gpio_dev gpioa = {.regs = (GPIO_TypeDef  *)GPIOA_BASE, .clk_id = RCC_GPIOA, .exti_port = EXTI_PA,};
gpio_dev gpiob = {.regs = (GPIO_TypeDef  *)GPIOB_BASE, .clk_id = RCC_GPIOB, .exti_port = EXTI_PB,};
gpio_dev gpioc = {.regs = (GPIO_TypeDef  *)GPIOC_BASE, .clk_id = RCC_GPIOC, .exti_port = EXTI_PC,};
gpio_dev gpiod = {.regs = (GPIO_TypeDef  *)GPIOD_BASE, .clk_id = RCC_GPIOD, .exti_port = EXTI_PD,};
c_gpio gpio(&gpioa);
//=======================================
//== 
//=======================================
c_gpio::c_gpio(gpio_dev *) {
    // 新建class无意义
}

//=======================================
//== 读取数据 =
//=======================================
inline uint32 c_gpio::gpio_read_bit(gpio_dev *dev, uint8 pin) {
    return dev->regs->IDR & 1<<pin;
}

//=======================================
//== 写入数据 =
//=======================================
inline void     c_gpio::gpio_write_bit(gpio_dev *dev, uint8 pin, uint8 val) {
    (val != LOW) ? (dev->regs->BSRR = 1<<pin) : (dev->regs->BRR = 1<<pin);
}

//=======================================
//== 翻转数据 =
//=======================================
inline void     c_gpio::gpio_toggle_bit(gpio_dev *dev, uint8 pin) {
    dev->regs->ODR = dev->regs->ODR ^ (1U << pin);
}

//=======================================
//== 根据map表操作 读
//=======================================
boolean c_gpio::digitalRead(uint8 pin) {
    return gpio_read_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit) ?
        HIGH : LOW;
}

//=======================================
//== 根据map 表操作 写
//=======================================
void c_gpio::digitalWrite(uint8 pin, uint8 val) {
    gpio_write_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit, val);
}

//=======================================
//== 根据map 表操作 翻转
//=======================================
void c_gpio::toggle(uint8 pin) {
    gpio_toggle_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit);
}
//=======================================
//== 设定引脚
//=======================================
void c_gpio::gpio_set_mode(gpio_dev *dev, uint8 pin, gpio_pin_mode mode) {
    GPIO_TypeDef *regs = dev->regs;
    __io uint32 *cr = &regs->CRL + (pin >> 3);
    uint32 shift = (pin & 0x7) * 4;
    uint32 tmp = *cr;

    tmp &= ~(0xF << shift);
    tmp |= (mode == GPIO_INPUT_PU ? GPIO_INPUT_PD : mode) << shift;
    *cr = tmp;

    if (mode == GPIO_INPUT_PD) {
        regs->ODR &= ~(1U << pin);
    } else if (mode == GPIO_INPUT_PU) {
        regs->ODR |= (1U << pin);
    }
}
//=======================================
//== pwm 引脚初始化
//=======================================
void c_gpio::setPwmFormat (uint8 pin, uint16 Period, uint8 active) {
    Timer.setPeriod  (PIN_MAP[pin].timer_device, Period);
    Timer.setOcActive(PIN_MAP[pin].timer_device, PIN_MAP[pin].timer_channel, active);
}

//=======================================
//== pwm 读取周期值
//=======================================
uint16 c_gpio::getPwmPeriod (uint8 pin) {
    return Timer.getOverflow (PIN_MAP[pin].timer_device);
}

//=======================================
//== pwm 设定定时值
//=======================================
void c_gpio::setPwmDuty (uint8 pin, uint16 duty  ) {
    Timer.setCompare(PIN_MAP[pin].timer_device, PIN_MAP[pin].timer_channel, duty); 
}

//=======================================
//== 根据map 表操作 引脚模式
//=======================================
void c_gpio::pinMode(uint8 pin, WiringPinMode mode) {
    BOOL pwm = false;
    gpio_pin_mode    outputMode;
    
    rcc.powerOn(PIN_MAP[pin].gpio_device->clk_id);
    if (pin >= BOARD_NR_GPIO_PINS)
        return;
    switch(mode) {
    case OUTPUT:                outputMode = GPIO_OUTPUT_PP;           break;
    case OUTPUT_OPEN_DRAIN:     outputMode = GPIO_OUTPUT_OD;           break;
    case OUTPUT_AF_OD:          outputMode = GPIO_AF_OUTPUT_OD;        break; 
    case OUTPUT_AF_PP:          outputMode = GPIO_AF_OUTPUT_PP;        break;        
    case INPUT:                 
    case INPUT_FLOATING:        outputMode = GPIO_INPUT_FLOATING;      break;
    case INPUT_ANALOG:          outputMode = GPIO_INPUT_ANALOG;        break;
    case INPUT_PULLUP:          outputMode = GPIO_INPUT_PU;            break;
    case INPUT_PULLDOWN:        outputMode = GPIO_INPUT_PD;            break;
    case PWM:                   outputMode = GPIO_AF_OUTPUT_PP;        pwm = true;      break;
    case PWM_OPEN_DRAIN:        outputMode = GPIO_AF_OUTPUT_OD;        pwm = true;      break;
    default:
        return;
    }                    
    gpio_set_mode(PIN_MAP[pin].gpio_device,PIN_MAP[pin].gpio_bit,outputMode);  
    
    if (PIN_MAP[pin].timer_device != NULL) {
        Timer.setPinMode(PIN_MAP[pin].timer_device,  PIN_MAP[pin].timer_channel,
                         pwm ? TIMER_PWM : TIMER_DISABLED);
    }
}
//=======================================
#define BUTTON_DEBOUNCE_DELAY 1
uint8 c_gpio::isButtonPressed(uint8 pin, uint32 pressedLevel) {
    if (digitalRead(pin) == pressedLevel) {
        os_dly_wait(BUTTON_DEBOUNCE_DELAY);
        while (digitalRead(pin) == pressedLevel)
            ;
        return true;
    }
    return false;
}

//=======================================
uint8 c_gpio::waitForButtonPress(uint8 pin, uint32 pressedLevel, uint32 timeout) {
    uint32 start = os_time_get();
    uint32 time;
    if (timeout == 0) {
        while (!isButtonPressed(pin, pressedLevel))
            ;
        return true;
    }
    do {
        time = os_time_get();
        if ((os_time_get()-time)>timeout) {
            return false;
        }
    } while (!isButtonPressed(pin, pressedLevel));
    return true;
}

//=======================================
