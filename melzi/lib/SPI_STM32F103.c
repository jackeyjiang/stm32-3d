/*----------------------------------------------------------------------------
 *      RL-ARM - FlashFS
 *----------------------------------------------------------------------------
 *      Name:    SPI_STM32F103.c
 *      Purpose: Serial Peripheral Interface Driver for ST STM32F103
 *      Rev.:    V4.22
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <File_Config.h>
#include <stm32f10x.h>                              /* STM32F10x Definitions */
#include "m_spi.h"
/*----------------------------------------------------------------------------
  SPI Driver instance definition
   spi0_drv: First SPI driver
   spi1_drv: Second SPI driver
 *---------------------------------------------------------------------------*/

#define __DRV_ID  spi0_drv
#define __FPCLK   72000000

/* SPI Driver Interface functions */
static BOOL Init (void);
static BOOL UnInit (void);
static U8   Send (U8 outb);
static BOOL SendBuf (U8 *buf, U32 sz);
static BOOL RecBuf (U8 *buf, U32 sz);
static BOOL BusSpeed (U32 kbaud);
static BOOL SetSS (U32 ss);
static U32  CheckMedia (void);        /* Optional function for SD card check */

/* SPI Device Driver Control Block */
SPI_DRV __DRV_ID = {
  Init,
  UnInit,
  Send,
  SendBuf,
  RecBuf,
  BusSpeed,
  SetSS,
  CheckMedia                          /* Can be NULL if not existing         */
};

/* SPI_SR - bit definitions. */
#define RXNE    0x01
#define TXE     0x02
#define BSY     0x80
#define FPCLK   (__FPCLK/1000)

/*--------------------------- Init ------------------------------------------*/
static BOOL Init (void) {
    spi1_init();
    return (__TRUE);
}

/*--------------------------- UnInit ----------------------------------------*/

static BOOL UnInit (void) {
  /* Return SSP interface to default state. */ 

  GPIOA->BSRR =  0x00100000;

  GPIOA->CRL &= ~0xFFFF0000;
  GPIOA->CRL |=  0x44440000;

  SPI1->CR1  = 0x0000;
  SPI1->CR2  = 0x0000;

  return (__TRUE);
}


/*--------------------------- Send ------------------------------------------*/

static U8 Send (U8 outb) {
    spi1_sent(outb);
    return (SPI1->DR);
}


/*--------------------------- SendBuf ---------------------------------------*/

static BOOL SendBuf (U8 *buf, U32 sz) {
    uint32 i;

    for (i = 0; i < sz; i++) {
        SPI1->DR = buf[i];
//      #define TXE 0x02
        while (!(SPI1->SR & 0x02));
        SPI1->DR;
    }
//  #define BSY     0x80
//  #define RXNE    0x01
    while (SPI1->SR & (0x80 | 0x01)) {
        SPI1->DR;
    }
    //spi1_sentBuf(buf, sz);
    return (__TRUE);
}


/*--------------------------- RecBuf ----------------------------------------*/

static BOOL RecBuf (U8 *buf, U32 sz) {
  /* Receive SPI data to buffer. */
  U32 i;

  for (i = 0; i < sz; i++) {
    SPI1->DR = 0xFF;
    /* Wait if RNE cleared, Rx FIFO is empty. */
    while (!(SPI1->SR & RXNE));
    buf[i] = SPI1->DR;
  }
  return (__TRUE);
}


/*--------------------------- BusSpeed --------------------------------------*/

static BOOL BusSpeed (U32 kbaud) {
  /* Set an SPI clock to required baud rate. */
  U8 br;

  if      (kbaud >= FPCLK / 2)   br = 0;                       /* FPCLK/2    */
  else if (kbaud >= FPCLK / 4)   br = 1;                       /* FPCLK/4    */
  else if (kbaud >= FPCLK / 8)   br = 2;                       /* FPCLK/8    */
  else if (kbaud >= FPCLK / 16)  br = 3;                       /* FPCLK/16   */
  else if (kbaud >= FPCLK / 32)  br = 4;                       /* FPCLK/32   */
  else if (kbaud >= FPCLK / 64)  br = 5;                       /* FPCLK/64   */
  else if (kbaud >= FPCLK / 128) br = 6;                       /* FPCLK/128  */
  else                           br = 7;                       /* FPCLK/256  */

  SPI1->CR1 = (SPI1->CR1 & ~(7 << 3)) | (br << 3); 
  return (__TRUE);
}       
/*--------------------------- SetSS -----------------------------------------*/

static BOOL SetSS (U32 ss) {
    if (ss) {
        GPIOA->BSRR = 0x00000010;
    } else {
        GPIOA->BRR = 0x00000010;
    }
    return (__TRUE);
}

/*--------------------------- CheckMedia ------------------------------------*/

static U32 CheckMedia (void) {
    return M_INSERTED;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/


