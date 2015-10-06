//=========================================================================
#ifndef __M_PINS_H__
#define __M_PINS_H__
//=========================================================================
/* 72 MHz -> 72 cycles per microsecond. */
#define CYCLES_PER_MICROSECOND  72000
/* Pin number for the built-in button. */
#define BOARD_BUTTON_PIN        38
/* Pin number for the built-in LED. */
#define BOARD_LED_PIN           13
/* Number of USARTs/UARTs whose pins are broken out to headers. */
#define BOARD_NR_USARTS         3
/* USART pin numbers. */
#define BOARD_USART1_TX_PIN     7
#define BOARD_USART1_RX_PIN     8
#define BOARD_USART2_TX_PIN     1
#define BOARD_USART2_RX_PIN     0
#define BOARD_USART3_TX_PIN     29
#define BOARD_USART3_RX_PIN     30
/* Number of SPI ports broken out to headers. */
#define BOARD_NR_SPI            2
/* SPI pin numbers. */
#define BOARD_SPI1_NSS_PIN      10
#define BOARD_SPI1_MOSI_PIN     11
#define BOARD_SPI1_MISO_PIN     12
#define BOARD_SPI1_SCK_PIN      13
#define BOARD_SPI2_NSS_PIN      31
#define BOARD_SPI2_MOSI_PIN     34
#define BOARD_SPI2_MISO_PIN     33
#define BOARD_SPI2_SCK_PIN      32
/* Total number of GPIO pins that are broken out to headers and
 * intended for use. This includes pins like the LED, button, and
 * debug port (JTAG/SWD) pins. */
#define BOARD_NR_GPIO_PINS      47
/* Number of pins capable of PWM output. */
#define BOARD_NR_PWM_PINS       15
/* Number of pins capable of ADC conversion. */
#define BOARD_NR_ADC_PINS       15
/* Number of pins already connected to external hardware.  For Maple,
 * these are just BOARD_LED_PIN, BOARD_BUTTON_PIN, and the debug port
 * pins (see below). */
#define BOARD_NR_USED_PINS       7
/* Debug port pins. */
#define BOARD_JTMS_SWDIO_PIN    39
#define BOARD_JTCK_SWCLK_PIN    40
#define BOARD_JTDI_PIN          41
#define BOARD_JTDO_PIN          42
#define BOARD_NJTRST_PIN        43
/* USB configuration.  BOARD_USB_DISC_DEV is the GPIO port containing
 * the USB_DISC pin, and BOARD_USB_DISC_BIT is that pin's bit. */
#define BOARD_USB_DISC_DEV      GPIOC
#define BOARD_USB_DISC_BIT      12
/* Pin aliases: these give the GPIO port/bit for each pin as an
 * enum. These are optional, but recommended. They make it easier to
 * write code using low-level GPIO functionality. */
enum {
    PA3, PA2, PA0, PA1, PB5, PB6, PA8, PA9, PA10, PB7, PA4, PA7, PA6, PA5, PB8,
    PC0, PC1, PC2, PC3, PC4, PC5, PC13, PC14, PC15, PB9, PD2, PC10, PB0, PB1,
    PB10, PB11, PB12, PB13, PB14, PB15, PC6, PC7, PC8, PC9, PA13, PA14, PA15,
    PB3, PB4
};
typedef struct stm32_pin_info {
    gpio_dev        *gpio_device;       /**< Maple pin's GPIO device */
    timer_dev       *timer_device;      /**< Pin's timer device, if any. */
    const adc_dev   *adc_device;        /**< ADC device, if any. */
    uint8           gpio_bit;           /**< Pin's GPIO port bit. */
    uint8           timer_channel;      /**< Timer channel, or 0 if none. */
    uint8           adc_channel;        /**< Pin ADC channel, or ADCx if none. */
} stm32_pin_info;
extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS];
/* Makes the PIN_MAP rows more human-readable. */
#define PMAP_ROW(gpio_dev, gpio_bit, timer_dev, timer_ch, adc_dev, adc_ch) \
    { gpio_dev, timer_dev, adc_dev, gpio_bit, timer_ch, adc_ch }
    
#endif

