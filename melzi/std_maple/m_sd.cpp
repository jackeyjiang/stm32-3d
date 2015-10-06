//================================================================================
#include "m_include.h"
#include "m_sd.h"
#include "diskio.h"
//================================================================================
//========================================================
//========================================================
// sd 卡块读取                                          //
//========================================================
SD_Error c_sd::ReadBlock(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t BlockSize) {
    uint32_t i = 0;
    SD_Error rvalue = SD_RESPONSE_FAILURE;

    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_low);
    SendCmd(SD_CMD_READ_SINGLE_BLOCK, ReadAddr, 0xFF);
    if (!GetResponse(SD_RESPONSE_NO_ERROR)) {
        if (!GetResponse(SD_START_DATA_SINGLE_BLOCK_READ)) {
            for (i = 0; i < BlockSize; i++) {
                *pBuffer++ = ReadByte();
            }
            /*!< Get CRC bytes (not really needed by us, but required by SD) */
            ReadByte();
            ReadByte();
            rvalue = SD_RESPONSE_NO_ERROR;
        }
    }
    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_high);
    WriteByte(dummy);
    return rvalue;
}

//========================================================
// sd 多卡块读取                                        //
//========================================================
SD_Error c_sd::ReadMultiBlocks(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks) {
    uint32_t i = 0, Offset = 0;
    SD_Error rvalue = SD_RESPONSE_FAILURE;
  
    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_low);
    while (NumberOfBlocks--) {
        SendCmd (SD_CMD_READ_SINGLE_BLOCK, ReadAddr + Offset, 0xFF);
        if (GetResponse(SD_RESPONSE_NO_ERROR))
            return  SD_RESPONSE_FAILURE;
    
        if (!GetResponse(SD_START_DATA_SINGLE_BLOCK_READ)) {
            for (i = 0; i < BlockSize; i++)
                *pBuffer++ = ReadByte();
            Offset += 512;
            /*!< get CRC bytes (not really needed by us, but required by SD) */
            ReadByte();
            ReadByte();
            rvalue = SD_RESPONSE_NO_ERROR;
        } else {
            rvalue = SD_RESPONSE_FAILURE;
        }
    }
    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_high);
    WriteByte(dummy);
    return rvalue;
}

//========================================================
// sd 卡块写入                                          //
//========================================================
SD_Error c_sd::WriteBlock(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t BlockSize) {
    uint32_t i = 0;
    SD_Error rvalue = SD_RESPONSE_FAILURE;

    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_low);
    SendCmd(SD_CMD_WRITE_SINGLE_BLOCK, WriteAddr, 0xFF);
    if (!GetResponse(SD_RESPONSE_NO_ERROR)) {
        WriteByte(dummy);
        WriteByte(0xFE);
        for (i = 0; i < BlockSize; i++) {
            WriteByte(*pBuffer);
            pBuffer++;
        }
        /*!< Put CRC bytes (not really needed by us, but required by SD) */
        ReadByte();
        ReadByte();
        if (GetDataResponse() == SD_DATA_OK)
            rvalue = SD_RESPONSE_NO_ERROR;
    }
    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_high);
    WriteByte(dummy);
    return rvalue;
}

//========================================================
// sd 卡多块写入                                        //
//========================================================
SD_Error c_sd::WriteMultiBlocks(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks) {
    uint32_t i = 0, Offset = 0;
    SD_Error rvalue = SD_RESPONSE_FAILURE;

    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_low);
    while (NumberOfBlocks--){
        SendCmd(SD_CMD_WRITE_SINGLE_BLOCK, WriteAddr + Offset, 0xFF);
        if (GetResponse(SD_RESPONSE_NO_ERROR))
            return SD_RESPONSE_FAILURE;
        WriteByte(dummy);
        WriteByte(SD_START_DATA_SINGLE_BLOCK_WRITE);
        for (i = 0; i < BlockSize; i++) {
            WriteByte(*pBuffer);
            pBuffer++;
        }
        Offset += 512;
        ReadByte();
        ReadByte();
        (GetDataResponse() == SD_DATA_OK) ? (rvalue = SD_RESPONSE_NO_ERROR):
                                            (rvalue = SD_RESPONSE_FAILURE );
    }
    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_high);
    WriteByte(dummy);
    return rvalue;
}

//========================================================
// sd 数据响应                                          //
//========================================================
uint8_t c_sd::GetDataResponse(void) {
    uint32_t i = 0;
    uint8_t response, rvalue;

    while (i <= 64) {
        response = ReadByte();
        response &= 0x1F;
        switch (response)  {
        case SD_DATA_OK:    rvalue = SD_DATA_OK;
                            break;
        case SD_DATA_CRC_ERROR:
            return SD_DATA_CRC_ERROR;
        case SD_DATA_WRITE_ERROR:
            return SD_DATA_WRITE_ERROR;
        default:            rvalue = SD_DATA_OTHER_ERROR;
                            break;
        }
        if (rvalue == SD_DATA_OK)
            break;
        i++;
    }
    while (ReadByte() == 0);
    return response;
}

//========================================================
// 读取响应状态                                         //
//========================================================
SD_Error c_sd::GetResponse(uint8_t Response) {
    uint32_t Count = 0xFFF;

    while ((ReadByte() != Response) && Count)
        Count--;
    if (Count == 0) 
        return SD_RESPONSE_FAILURE;
    else
        return SD_RESPONSE_NO_ERROR;
}

//========================================================
// sd 进入 IDLE 状态
//========================================================
SD_Error c_sd::GoIdleState(void) {
    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_low);
    SendCmd(SD_CMD_GO_IDLE_STATE, 0, 0x95);
    if (GetResponse(SD_IN_IDLE_STATE))
        return SD_RESPONSE_FAILURE;
    do {
        gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_high);
        WriteByte(dummy);
        gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_low);
        SendCmd(SD_CMD_SEND_OP_COND, 0, 0xFF);
    } while (GetResponse(SD_RESPONSE_NO_ERROR));

    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_high);
    WriteByte(dummy);
    return SD_RESPONSE_NO_ERROR;
}

//========================================================
// 发送命令                                             //
//========================================================
void c_sd::SendCmd(uint8_t Cmd, uint32_t Arg, uint8_t Crc)
{
    uint32_t    i = 0x00;
    uint8_t     Frame[6];
    Frame[0] = (Cmd | 0x40);            /*!< Construct byte 1 */
    Frame[1] = (uint8_t)(Arg >> 24);    /*!< Construct byte 2 */
    Frame[2] = (uint8_t)(Arg >> 16);    /*!< Construct byte 3 */
    Frame[3] = (uint8_t)(Arg >> 8 );    /*!< Construct byte 4 */
    Frame[4] = (uint8_t)(Arg);          /*!< Construct byte 5 */
    Frame[5] = (Crc);                   /*!< Construct CRC: byte 6 */
    for (i = 0; i < 6; i++) 
        WriteByte(Frame[i]);         /*!< Send the Cmd bytes */
}

//========================================================
// 读取单字节数据
//========================================================
uint8_t c_sd::ReadByte(void) {
    uint8_t Data = 0;

    while (SPI_I2S_GetFlagStatus(sd_device->reg, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(sd_device->reg, dummy);
    while (SPI_I2S_GetFlagStatus(sd_device->reg, SPI_I2S_FLAG_RXNE) == RESET);
    Data = (uint8_t)SPI_I2S_ReceiveData(sd_device->reg);
    return Data;
}
//========================================================
// 写入单字节数据
//========================================================
uint8_t c_sd::WriteByte(uint8_t Data) {
    while(SPI_I2S_GetFlagStatus(sd_device->reg, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(sd_device->reg, Data);
    while(SPI_I2S_GetFlagStatus(sd_device->reg, SPI_I2S_FLAG_RXNE) == RESET);
    return (uint8_t)SPI_I2S_ReceiveData(sd_device->reg);
}

//========================================================
//
//========================================================
SD_Error c_sd::GetCardInfo() {
    SD_Error status = SD_RESPONSE_FAILURE;

    status = GetCSDRegister(&(cardinfo.SD_csd));
    status = GetCIDRegister(&(cardinfo.SD_cid));
    cardinfo.CardCapacity = (cardinfo.SD_csd.DeviceSize + 1) ;
    cardinfo.CardCapacity *= (1 << (cardinfo.SD_csd.DeviceSizeMul + 2));
    cardinfo.CardBlockSize = 1 << (cardinfo.SD_csd.RdBlockLen);
    cardinfo.CardCapacity *= cardinfo.CardBlockSize;

    return status;
}
//========================================================
//                                                      //
//========================================================
SD_Error c_sd::GetCSDRegister(SD_CSD* SD_csd) {
    uint32_t i = 0;
    SD_Error rvalue = SD_RESPONSE_FAILURE;
    uint8_t CSD_Tab[16];

    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_low);
    SendCmd(SD_CMD_SEND_CSD, 0, 0xFF);
    if (!GetResponse(SD_RESPONSE_NO_ERROR)) {
    if (!GetResponse(SD_START_DATA_SINGLE_BLOCK_READ))
        for (i = 0; i < 16; i++)
            CSD_Tab[i] = ReadByte();
        WriteByte(dummy);
        WriteByte(dummy);
        rvalue = SD_RESPONSE_NO_ERROR;
    }
    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_high);
    WriteByte(dummy);

    SD_csd->CSDStruct         = (CSD_Tab[0] & 0xC0) >> 6;
    SD_csd->SysSpecVersion    = (CSD_Tab[0] & 0x3C) >> 2;
    SD_csd->Reserved1         = CSD_Tab[0] & 0x03;
    SD_csd->TAAC    = CSD_Tab[1];
    SD_csd->NSAC    = CSD_Tab[2];
    SD_csd->MaxBusClkFrec   =  CSD_Tab[3];
    SD_csd->CardComdClasses =  CSD_Tab[4] << 4;
    SD_csd->CardComdClasses |= (CSD_Tab[5] & 0xF0) >> 4;
    SD_csd->RdBlockLen      =  CSD_Tab[5] & 0x0F;
    SD_csd->PartBlockRead   = (CSD_Tab[6] & 0x80) >> 7;
    SD_csd->WrBlockMisalign = (CSD_Tab[6] & 0x40) >> 6;
    SD_csd->RdBlockMisalign = (CSD_Tab[6] & 0x20) >> 5;
    SD_csd->DSRImpl         = (CSD_Tab[6] & 0x10) >> 4;
    SD_csd->Reserved2       = 0; /*!< Reserved */
    SD_csd->DeviceSize      = (CSD_Tab[6] & 0x03) << 10;
    SD_csd->DeviceSize      |= (CSD_Tab[7]) << 2;
    SD_csd->DeviceSize      |= (CSD_Tab[8] & 0xC0) >> 6;
    SD_csd->MaxRdCurrentVDDMin  = (CSD_Tab[8] & 0x38) >> 3;
    SD_csd->MaxRdCurrentVDDMax  = (CSD_Tab[8] & 0x07);
    SD_csd->MaxWrCurrentVDDMin  = (CSD_Tab[9] & 0xE0) >> 5;
    SD_csd->MaxWrCurrentVDDMax  = (CSD_Tab[9] & 0x1C) >> 2;
    SD_csd->DeviceSizeMul       = (CSD_Tab[9] & 0x03) << 1;
    SD_csd->DeviceSizeMul      |= (CSD_Tab[10] & 0x80) >> 7;
    SD_csd->EraseGrSize     = (CSD_Tab[10] & 0x40) >> 6;
    SD_csd->EraseGrMul      = (CSD_Tab[10] & 0x3F) << 1;
    SD_csd->EraseGrMul      |=(CSD_Tab[11] & 0x80) >> 7;
    SD_csd->WrProtectGrSize = (CSD_Tab[11] & 0x7F);
    SD_csd->WrProtectGrEnable = (CSD_Tab[12] & 0x80) >> 7;
    SD_csd->ManDeflECC      = (CSD_Tab[12] & 0x60) >> 5;
    SD_csd->WrSpeedFact     = (CSD_Tab[12] & 0x1C) >> 2;
    SD_csd->MaxWrBlockLen   = (CSD_Tab[12] & 0x03) << 2;
    SD_csd->MaxWrBlockLen |= (CSD_Tab[13] & 0xC0) >> 6;
    SD_csd->WriteBlockPaPartial = (CSD_Tab[13] & 0x20) >> 5;
    SD_csd->Reserved3           = 0;
    SD_csd->ContentProtectAppli = (CSD_Tab[13] & 0x01);
    SD_csd->FileFormatGrouop    = (CSD_Tab[14] & 0x80) >> 7;
    SD_csd->CopyFlag        = (CSD_Tab[14] & 0x40) >> 6;
    SD_csd->PermWrProtect   = (CSD_Tab[14] & 0x20) >> 5;
    SD_csd->TempWrProtect   = (CSD_Tab[14] & 0x10) >> 4;
    SD_csd->FileFormat      = (CSD_Tab[14] & 0x0C) >> 2;
    SD_csd->ECC             = (CSD_Tab[14] & 0x03);
    SD_csd->CSD_CRC     = (CSD_Tab[15] & 0xFE) >> 1;
    SD_csd->Reserved4   = 1;
    return rvalue;
}

//========================================================
// CID 读取 Card Identification Data
//========================================================
SD_Error c_sd::GetCIDRegister(SD_CID* SD_cid) {
    uint32_t i = 0;
    SD_Error rvalue = SD_RESPONSE_FAILURE;
    uint8_t CID_Tab[16];
    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_low);
    SendCmd(SD_CMD_SEND_CID, 0, 0xFF);
  
    if (!GetResponse(SD_RESPONSE_NO_ERROR)) {
        if (!GetResponse(SD_START_DATA_SINGLE_BLOCK_READ)) {
            for (i = 0; i < 16; i++)
                CID_Tab[i] = ReadByte();
        }
        /*!< Get CRC bytes (not really needed by us, but required by SD) */
        WriteByte(dummy);
        WriteByte(dummy);
        rvalue = SD_RESPONSE_NO_ERROR;
    }
    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_high);
    WriteByte(dummy);

    SD_cid->ManufacturerID = CID_Tab[0];
    SD_cid->OEM_AppliID  = CID_Tab[1] << 8;
    SD_cid->OEM_AppliID |= CID_Tab[2];
    SD_cid->ProdName1    = CID_Tab[3] << 24;
    SD_cid->ProdName1   |= CID_Tab[4] << 16;
    SD_cid->ProdName1   |= CID_Tab[5] << 8;
    SD_cid->ProdName1   |= CID_Tab[6];
    SD_cid->ProdName2    = CID_Tab[7];
    SD_cid->ProdRev      = CID_Tab[8];
    SD_cid->ProdSN       = CID_Tab[9] << 24;
    SD_cid->ProdSN      |= CID_Tab[10] << 16;
    SD_cid->ProdSN      |= CID_Tab[11] << 8;
    SD_cid->ProdSN      |= CID_Tab[12];
    SD_cid->Reserved1   |= (CID_Tab[13] & 0xF0) >> 4;
    SD_cid->ManufactDate = (CID_Tab[13] & 0x0F) << 8;
    SD_cid->ManufactDate|= CID_Tab[14];
    SD_cid->CID_CRC      = (CID_Tab[15] & 0xFE) >> 1;
    SD_cid->Reserved2    = 1;
    return rvalue;
}

//========================================================
// 低阶初始化                                           //
//========================================================
void c_sd::LowLevel_Init(void) {
    SPI_InitTypeDef   SPI_InitStructure;

    rcc.powerOn(PIN_MAP[sd_device->pin_clk ].gpio_device->clk_id);
    rcc.powerOn(PIN_MAP[sd_device->pin_cs  ].gpio_device->clk_id);
    rcc.powerOn(PIN_MAP[sd_device->pin_miso].gpio_device->clk_id);
    rcc.powerOn(PIN_MAP[sd_device->pin_mosi].gpio_device->clk_id);
    rcc.powerOn(sd_device->clk_id);
  
    gpio.pinMode(sd_device->pin_clk,  OUTPUT_AF_PP  );
    gpio.pinMode(sd_device->pin_mosi, OUTPUT_AF_PP  );
    gpio.pinMode(sd_device->pin_miso, INPUT_FLOATING);
    gpio.pinMode(sd_device->pin_cs,   OUTPUT        );

    /*!< SD_SPI Config */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL      = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA      = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial     = 7;
    SPI_Init(sd_device->reg, &SPI_InitStructure);
    SPI_Cmd(sd_device->reg, ENABLE); /*!< SD_SPI enable */
}

//========================================================
// sd 卡初始化                                          //
//========================================================
SD_Error c_sd::begin() {
    uint32_t i = 0;
    
    LowLevel_Init(); 
    gpio.digitalWrite(sd_device->pin_cs, sd_device->pin_cs_high);
    for (i = 0; i <= 9; i++) 
        WriteByte(dummy);
    return (GoIdleState());
}
//
//========================================================
// ff 接口函数   sd 卡初始化                            //
//========================================================
DSTATUS disk_initialize (BYTE pdrv) {
//
//==============================
// 支持单磁盘
    if (pdrv) {
        return STA_NOINIT;
    }
//
//==============================
// 初始化磁盘
    if (sd.begin() == SD_RESPONSE_NO_ERROR) {
        return RES_OK;
    } else {
        return STA_NOINIT;
    }
}
//
//========================================================
// ff 接口函数   sd 状态                                //
//========================================================
DSTATUS disk_status (BYTE pdrv) {
    if (pdrv) {
        return STA_NOINIT;
    }
    return RES_OK;
}
//
//========================================================
// ff 接口函数   读取扇区                               //
//========================================================
DRESULT disk_read (BYTE pdrv, BYTE *buff, DWORD sector, BYTE count) {
    if (pdrv || !count) {
        return RES_PARERR;
    }
    if (count == 1) {
        if (sd.ReadBlock(buff, sector, _MAX_SS) == SD_RESPONSE_NO_ERROR) 
            return RES_OK;
        else 
            return RES_ERROR;
    } else {
        if (sd.ReadMultiBlocks(buff, sector, _MAX_SS, count) == SD_RESPONSE_NO_ERROR) {
            return RES_OK;
        } else {
            return RES_ERROR;
        }
    }
}
//
//========================================================
// ff 接口函数   写入扇区                               //
//========================================================
DRESULT disk_write (BYTE pdrv, const BYTE *buff, DWORD sector, BYTE count) {
    if (pdrv || !count) {
        return RES_PARERR;
    }
    if (count == 1) {
        if (sd.WriteBlock((uint8_t *)buff, sector, _MAX_SS) == SD_RESPONSE_NO_ERROR) 
            return RES_OK;
        else 
            return RES_ERROR;
    } else {
        if (sd.WriteMultiBlocks((uint8_t *)buff, sector, _MAX_SS, count) == SD_RESPONSE_NO_ERROR) {
            return RES_OK;
        } else {
            return RES_ERROR;
        }
    }
}
//
//========================================================
// ff 接口函数   磁盘控制操作                           //
//========================================================
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void *buff){
    DRESULT res;
    if (pdrv) {
        return RES_PARERR;
    }
    switch (cmd) {
        case CTRL_SYNC: 
                res = RES_OK;
                break;
        case GET_SECTOR_COUNT:  {*(DWORD *)buff = sd.cardinfo.CardCapacity/sd.cardinfo.CardBlockSize;    
                                res = RES_OK; break;}
        case GET_SECTOR_SIZE:   {*(DWORD *)buff = _MAX_SS;                     res = RES_OK;   break;}
        case GET_BLOCK_SIZE:    {*(DWORD *)buff = sd.cardinfo.CardBlockSize;   res = RES_OK;   break;}
        default:                {res = RES_PARERR;}
    }
    return res;
}
//
//========================================================
// ff 接口函数   写入时间                               //
//========================================================
DWORD get_fattime (void) {
    return 0;
}
//================================================================================

