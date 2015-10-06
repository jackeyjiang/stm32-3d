//===================================================================
//
//===================================================================
#ifndef __M_SPI_H__
#define __M_SPI_H__
#include "typeDefine.h"
#ifdef __cplusplus
extern "C" {
#endif
//===================================================================
extern void     spi1_init    (void);
extern void     spi1_sent    (uint8 outb);
extern void     spi1_sentBuf (uint8 *buf, uint32 sz);
extern void     spi1_recBuf  (uint8 *buf, uint32 sz);
//===================================================================
#ifdef __cplusplus
}
#endif
#endif //__M_SPI_H__
//===================================================================

