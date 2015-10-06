//===============================================
#include "m_include.h"
//===============================================
extern timer_dev timer1;
extern timer_dev timer2;
extern timer_dev timer3;
extern timer_dev timer4;
extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {
    /* Top header */
    PMAP_ROW(&gpioa,   3, &timer2,  4, &adc1,        3), /* D0/PA3 */
    PMAP_ROW(&gpioa,   2, &timer2,  3, &adc1,        2), /* D1/PA2 */
    PMAP_ROW(&gpioa,   0, &timer2,  1, &adc1,        0), /* D2/PA0 */
    PMAP_ROW(&gpioa,   1, &timer2,  2, &adc1,        1), /* D3/PA1 */
    PMAP_ROW(&gpiob,   5,    NULL,  0,  NULL, ADC_NULL), /* D4/PB5 */
    PMAP_ROW(&gpiob,   6, &timer4,  1,  NULL, ADC_NULL), /* D5/PB6 */
    PMAP_ROW(&gpioa,   8, &timer1,  1,  NULL, ADC_NULL), /* D6/PA8 */
    PMAP_ROW(&gpioa,   9, &timer1,  2,  NULL, ADC_NULL), /* D7/PA9 */
    PMAP_ROW(&gpioa,  10, &timer1,  3,  NULL, ADC_NULL), /* D8/PA10 */
    PMAP_ROW(&gpiob,   7, &timer4,  2,  NULL, ADC_NULL), /* D9/PB7 */
    PMAP_ROW(&gpioa,   4,    NULL,  0, &adc1,        4), /* D10/PA4   SPI1_NSS */
    PMAP_ROW(&gpioa,   7, &timer3,  2, &adc1,        7), /* D11/PA7   SPI1_MOSI*/
    PMAP_ROW(&gpioa,   6, &timer3,  1, &adc1,        6), /* D12/PA6   SPI1_MISO*/
    PMAP_ROW(&gpioa,   5,    NULL,  0, &adc1,        5), /* D13/PA5   SPI1_SCK */
    PMAP_ROW(&gpiob,   8, &timer4,  3,  NULL, ADC_NULL), /* D14/PB8 */
    //
    /* Little header */
    PMAP_ROW(&gpioc,   0,    NULL,  0, &adc1,       10), /* D15/PC0 */
    PMAP_ROW(&gpioc,   1,    NULL,  0, &adc1,       11), /* D16/PC1 */
    PMAP_ROW(&gpioc,   2,    NULL,  0, &adc1,       12), /* D17/PC2 */
    PMAP_ROW(&gpioc,   3,    NULL,  0, &adc1,       13), /* D18/PC3 */
    PMAP_ROW(&gpioc,   4,    NULL,  0, &adc1,       14), /* D19/PC4 */
    PMAP_ROW(&gpioc,   5,    NULL,  0, &adc1,       15), /* D20/PC5 */
    //
    /* External header */
    PMAP_ROW(&gpioc,  13,    NULL,  0,  NULL, ADC_NULL), /* D21/PC13 */
    PMAP_ROW(&gpioc,  14,    NULL,  0,  NULL, ADC_NULL), /* D22/PC14 */
    PMAP_ROW(&gpioc,  15,    NULL,  0,  NULL, ADC_NULL), /* D23/PC15 */
    PMAP_ROW(&gpiob,   9, &timer4,  4,  NULL, ADC_NULL), /* D24/PB9 */
    PMAP_ROW(&gpiod,   2,    NULL,  0,  NULL, ADC_NULL), /* D25/PD2 */
    PMAP_ROW(&gpioc,  10,    NULL,  0,  NULL, ADC_NULL), /* D26/PC10 */
    PMAP_ROW(&gpiob,   0, &timer3,  3, &adc1,        8), /* D27/PB0 */
    PMAP_ROW(&gpiob,   1, &timer3,  4, &adc1,        9), /* D28/PB1 */
    PMAP_ROW(&gpiob,  10,    NULL,  0,  NULL, ADC_NULL), /* D29/PB10 */
    PMAP_ROW(&gpiob,  11,    NULL,  0,  NULL, ADC_NULL), /* D30/PB11 */
    PMAP_ROW(&gpiob,  12,    NULL,  0,  NULL, ADC_NULL), /* D31/PB12    SPI2_NSS */
    PMAP_ROW(&gpiob,  13,    NULL,  0,  NULL, ADC_NULL), /* D32/PB13    SPI2_SCK */
    PMAP_ROW(&gpiob,  14,    NULL,  0,  NULL, ADC_NULL), /* D33/PB14    SPI2_MISO*/
    PMAP_ROW(&gpiob,  15,    NULL,  0,  NULL, ADC_NULL), /* D34/PB15    SPI2_MOSI*/

    PMAP_ROW(&gpioc,   6,    NULL,  0,  NULL, ADC_NULL), /* D35/PC6 */
    PMAP_ROW(&gpioc,   7,    NULL,  0,  NULL, ADC_NULL), /* D36/PC7 */
    PMAP_ROW(&gpioc,   8,    NULL,  0,  NULL, ADC_NULL), /* D37/PC8 */
    PMAP_ROW(&gpioc,   9,    NULL,  0,  NULL, ADC_NULL), /* D38/PC9 (BUT) */
    //
    /* JTAG header */
    PMAP_ROW(&gpioa,  13,    NULL,  0,  NULL, ADC_NULL), /* D39/PA13 */
    PMAP_ROW(&gpioa,  14,    NULL,  0,  NULL, ADC_NULL), /* D40/PA14 */
    PMAP_ROW(&gpioa,  15,    NULL,  0,  NULL, ADC_NULL), /* D41/PA15 */
    PMAP_ROW(&gpiob,   3,    NULL,  0,  NULL, ADC_NULL), /* D42/PB3  */
    PMAP_ROW(&gpiob,   4,    NULL,  0,  NULL, ADC_NULL), /* D43/PB4  */
    //
    /* USB DISCONNECT */
    PMAP_ROW(&gpioc,   12,    NULL,  0,  NULL, ADC_NULL), /* D44/PB4  */
    PMAP_ROW(&gpioc,   11,    NULL,  0,  NULL, ADC_NULL), /* D45/PB4  */
    //
    /* NO CLASS */
    PMAP_ROW(&gpiob,   2,     NULL,  0,  NULL, ADC_NULL), /* D46/PB2 (boot 1) pull down */
};
