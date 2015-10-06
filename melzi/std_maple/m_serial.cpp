//================================================================
#include "m_include.h"
#include "m_serial.h"
/*================================================================
// 串口类
//===============================================================*/
serial::serial(usart_dev* dev)
{ 
    usart_device = dev;
    
    txHead = txTail = 0;
    //-----------------------------------
    //== 功能电源打开 ==
    rcc.powerOn(usart_device->clk_id);
    rcc.powerOn(usart_device->clk_dma);
    
    //-----------------------------------
    // 1. 引脚定义
    gpio.pinMode(dev->txPin, OUTPUT_AF_PP);  
    gpio.pinMode(dev->rxPin, INPUT_PULLUP);

    //-----------------------------------
    // 2. 定义发送中断事件
    nvic.irqEnable(dev->txDmaIrq);
    
    //-----------------------------------
    // 5. 定义接收DMA
    DMA_InitTypeDef      DMA_InitStructure;
    DMA_DeInit(dev->rxDma);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)dev->reg + 0x04;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)dev->rxBuf;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_BufferSize = dev->rxSize;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(dev->rxDma, &DMA_InitStructure);
    DMA_Cmd(dev->rxDma, ENABLE);
    USART_DMACmd(dev->reg, USART_DMAReq_Rx, ENABLE);
    rxPos = DMA_GetCurrDataCounter(dev->rxDma);

    //-----------------------------------
    // 6. 定义发送DMA
    DMA_DeInit(dev->txDma);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)dev->reg + 0x04;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(dev->txDma, &DMA_InitStructure);
    DMA_ITConfig(dev->txDma, DMA_IT_TC, ENABLE);
    dev->txDma->CNDTR = 0;
    USART_DMACmd(dev->reg, USART_DMAReq_Tx, ENABLE);
    USART_Cmd(dev->reg, ENABLE);
}

/*================================================================
// 起动串口
//===============================================================*/
void serial::begin(uint32 ibaud) {
    
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = ibaud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = DISABLE;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(usart_device->reg, &USART_InitStructure);
    band = ibaud;
}

/*================================================================
// 关闭串口
//===============================================================*/
void serial::end(void) {
    rcc.powerOff(usart_device->clk_id);
}

//=================================================================
// 判读是否有数据
//=================================================================
uint8 serial::read(void) {
    char ch = usart_device->rxBuf[usart_device->rxSize-rxPos];
    if (--rxPos == 0)
		rxPos=usart_device->rxSize;
    return ch;
}

//=================================================================
// 判读是否有数据
//=================================================================
uint32 serial::available(void) {
    if (usart_device->rxDma->CNDTR == rxPos)
        return 0;
    return usart_device->rxSize-rxPos;
}

//=================================================================
// DMA 写入数据
//=================================================================
void serial::dmaTxFxn(void) {
    usart_device->txDma->CMAR =  (uint32_t)&usart_device->txBuf[txTail];
    if (txHead > txTail) {
        usart_device->txDma->CNDTR = txHead-txTail;
        txTail=txHead;
    } else {
        usart_device->txDma->CNDTR = usart_device->txSize-txTail;
        txTail = 0;
    }
    DMA_Cmd(usart_device->txDma, ENABLE);
}
//=================================================================
// 写入字节数据
//=================================================================
void serial::write(uint8 *str) {
    while (*str) {
        write(*str++);
    }
}
//=================================================================
// 写入字节数据
//=================================================================
void serial::write(uint8 ch) {
    //-----------------------------------
    // 1. 数据放入txBuf
    usart_device->txBuf[txHead] = ch;
    //-----------------------------------
    // 2. Head + 1
    txHead = (txHead + 1) % usart_device->txSize;
    if (!(usart_device->txDma->CCR & 1)) {
        dmaTxFxn();
    }
}
//=================================================================
// 清空接收区域
//=================================================================
void serial::flush(void) {
    rxPos = usart_device->rxDma->CNDTR;
}
//=================================================================
//== 数据发送完成，允许下次发送
void serial::txIsr() {
    txFinish=false;
    DMA_Cmd(usart_device->txDma, DISABLE);
    if (txHead!=txTail) {
        dmaTxFxn();
    } else {
        txFinish=true;
    }
}
//=================================================================
// 实体定义
#if SERIAL1_USE == TRUE
    char serial1Rxbuf[SERIAL1_RX_LENGTH];
    char serial1Txbuf[SERIAL1_TX_LENGTH];
    usart_dev  usart1 = {.reg     = USART1, 
                         .clk_id  = RCC_USART1, 
                         .clk_dma = RCC_DMA1,
                         .txDmaIrq= DMA1_Channel4_IRQn,
                         .rxDma   = DMA1_Channel5,
                         .txDma   = DMA1_Channel4,
                         .rxPin   = BOARD_USART1_RX_PIN, 
                         .txPin   = BOARD_USART1_TX_PIN, 
                         .rxBuf   = serial1Rxbuf,
                         .txBuf   = serial1Txbuf,
                         .rxSize  = SERIAL1_RX_LENGTH,
                         .txSize  = SERIAL1_TX_LENGTH};
    serial  serial1(&usart1);
    #ifdef __cplusplus
    extern "C" {
    #endif
        void __irq_dma1_channel4(void) {
            DMA_ClearITPendingBit(DMA1_IT_TC4);
            serial1.txIsr();
        }
    #ifdef __cplusplus
    }
    #endif 
#endif
#if SERIAL2_USE == TRUE
    char serial2Rxbuf[SERIAL2_RX_LENGTH];
    char serial2Txbuf[SERIAL2_TX_LENGTH];
    usart_dev  usart2 = {.reg     = USART2, 
                         .clk_id  = RCC_USART2, 
                         .clk_dma = RCC_DMA1,
                         .txDmaIrq= DMA1_Channel7_IRQn,
                         .rxDma   = DMA1_Channel6,
                         .txDma   = DMA1_Channel7,
                         .rxPin   = BOARD_USART2_RX_PIN, 
                         .txPin   = BOARD_USART2_TX_PIN, 
                         .rxBuf   = serial2Rxbuf,
                         .txBuf   = serial2Txbuf,
                         .rxSize  = SERIAL2_RX_LENGTH,
                         .txSize  = SERIAL2_TX_LENGTH};
    serial  serial2(&usart2);
    #ifdef __cplusplus
    extern "C" {
    #endif                   
        void __irq_dma1_channel7(void) {
            DMA_ClearITPendingBit(DMA1_IT_TC7);
            serial2.txIsr();
        }
    #ifdef __cplusplus
    }
    #endif 
#endif
//=================================================================



