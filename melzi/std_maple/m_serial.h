//=============================================================
#ifndef __STD_HARDWARESERIAL_H__
#define __STD_HARDWARESERIAL_H__
//=============================================================
#include "stm32f10x.h"
#include "m_rcc.h"
#include "m_Print.h"
#include "RTL.h"
//=============================================================
typedef struct usart_dev {
    USART_TypeDef           *reg;
    rcc_clk_id              clk_id;
    rcc_clk_id              clk_dma;
    IRQn                    txDmaIrq;
    DMA_Channel_TypeDef *   rxDma;
    DMA_Channel_TypeDef *   txDma;
    uint8                   rxPin;
    uint8                   txPin;
    char *                  rxBuf;
    char *                  txBuf;
    uint16                  rxSize;
    uint16                  txSize;
}usart_dev;

class serial : public Print {
public:
    serial(usart_dev* udev);
public:
    /* I/O */
    void    begin(uint32 baud);
    uint8   read(void);
    void    end(void);
    uint32  available(void);
    virtual void write(uint8  );
    virtual void write(uint8 *);
    void    waitTxFinish()   {txFinish=false; while(!txFinish) os_dly_wait(1);}
    using   Print::write;
    void    flush(void);
    void    rxIsr();
    void    txIsr();
private:
    void    dmaTxFxn(void);
    usart_dev *usart_device;
    uint16  txHead;
    uint16  txTail;
    uint16  rxPos;
    BOOL    txFinish;
    uint32  band;
};
//================================================================
#if SERIAL1_USE == TRUE
extern serial serial1;
#endif
#if SERIAL2_USE == TRUE
extern serial serial2;
#endif
#ifdef __cplusplus
extern "C" {
#endif
void __irq_dma1_channel4(void);
void __irq_dma1_channel7(void);
#ifdef __cplusplus
}
#endif
#endif

