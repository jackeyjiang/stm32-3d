//===========================================================================
#include "m_include.h"
//===========================================================================
#ifdef __cplusplus
extern "C" {
#endif
//===============================================
// 初始化 spi
//===============================================
bool spi1InitFlag = false;
void spi1_init(void) {
    if (spi1InitFlag) {
        return;
    }
    RCC->APB2ENR |=  0x00001005;
    GPIOA->BSRR   =  0x00000010;
    GPIOA->CRL   &= ~0xFFFF0000;
    GPIOA->CRL   |=  0xB8B30000;
    for (int i=10000; i != 0; i--);
    SPI1->CR1     =  0x037C;
    SPI1->CR2     =  0x0000;
    spi1InitFlag  =  true;
}
//
//===============================================
// 发送数据 spi
//===============================================
void spi1_sent(uint8 outb) {
    SPI1->DR = outb;	
//  while (!(SPI1->SR & RXNE));    
    while (!(SPI1->SR & 0x01));
}
//
//===============================================
// 发送内存 spi
//===============================================
void spi1_sentBuf(uint8 *buf, uint32 sz) {
    uint32 i;
    uint8  ch;

    for (i = 0; i < sz; i++) {
        SPI1->DR = buf[i];
//      #define TXE 0x02
        while (!(SPI1->SR & 0x02));
        ch = SPI1->DR;
    }
//  #define BSY     0x80
//  #define RXNE    0x01
    while (SPI1->SR & (0x80 | 0x01)) {
        ch = SPI1->DR;
    }
    sz = ch;
}
//
//===============================================
// 接收内存 spi
//===============================================
void spi1_recBuf(uint8 *buf, uint32 sz) {
    uint32 i;

    for (i = 0; i < sz; i++) {
        SPI1->DR = 0xFF;
//      #define RXNE    0x01
        while (!(SPI1->SR & 0x01));
        buf[i] = SPI1->DR;
    }
}
//
//===============================================
// 设定总线速度 spi
//===============================================
BOOL spi1_BusSpeed (uint32 kbaud) {
    uint8 br;

    if      (kbaud >= 72000 / 2)   br = 0;                       /* FPCLK/2    */
    else if (kbaud >= 72000 / 4)   br = 1;                       /* FPCLK/4    */
    else if (kbaud >= 72000 / 8)   br = 2;                       /* FPCLK/8    */
    else if (kbaud >= 72000 / 16)  br = 3;                       /* FPCLK/16   */
    else if (kbaud >= 72000 / 32)  br = 4;                       /* FPCLK/32   */
    else if (kbaud >= 72000 / 64)  br = 5;                       /* FPCLK/64   */
    else if (kbaud >= 72000 / 128) br = 6;                       /* FPCLK/128  */
    else                           br = 7;                       /* FPCLK/256  */

    SPI1->CR1 = (SPI1->CR1 & ~(7 << 3)) | (br << 3); 
    return (__TRUE);
} 
//===========================================================================
#ifdef __cplusplus
} 
#endif
//===========================================================================



