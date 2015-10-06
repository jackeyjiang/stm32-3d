//================================================================================
#include "m_include.h"
//================================================================================
//================================================================================
// 设备总表
usblib_dev  usbSdDev = {
    .timeOut                    = 50,
    .SuspendEnable              = true,
//     .pEpInt_IN                  = (pEpInt_IN_Fxn  *)                &pEpInt_IN_UsbVcom,             
//     .pEpInt_OUT                 = (pEpInt_OUT_Fxn *)                &pEpInt_OUT_UsbVcom,          
//     .state                      = USB_UNCONNECTED,    
//     .prevState                  = USB_UNCONNECTED,    
//     .Device_Table               = (DEVICE *)                        &Device_Table_UsbVcom,    
//     .User_Standard_Requests     = (USER_STANDARD_REQUESTS *)        &User_Standard_Requests_UsbVcom,
//     .Device_Property            = (DEVICE_PROP*)                    &Device_Property_UsbVcom,
//     .callBack                   = (usbCallbackFxn*)                 &usbCallbackFxn_UsbVcom,
//     .deviceList                 = (usb_descriptor_device *)         &deviceList_UsbVcom,
//     .ConfigList                 = (usb_descriptor_config *)         &usbVcomDescriptor_Config,
//     .String_LangID              = (usb_descriptor_string *)&usbVcomDescriptor_LangID,
//     .String_iManufacturer       = (usb_descriptor_string *)&usbVcomDescriptor_iManufacturer,
//     .String_iProduct            = (usb_descriptor_string *)&usbVcomDescriptor_iProduct,
//     .Device_Descriptor          = &usb_Vcom_Device_Descriptor,
//     .Config_Descriptor          = &usb_Vcom_Config_Descriptor,
//     .String_Descriptor[0]       = &usb_Vcom_String_Descriptor[0],
//     .String_Descriptor[1]       = &usb_Vcom_String_Descriptor[1],
//     .String_Descriptor[2]       = &usb_Vcom_String_Descriptor[2],
//     .Linecoding                 = (uint8 *)&LinecodingUsbVcom,
//     .LinecodingSize             = sizeof(LinecodingUsbVcom),
    .clk_id= RCC_USB
};
//================================================================================
// c_massStorage::c_massStorage(sd_dev *sdDev, usblib_dev  *usbDev) {
//     pSd  = new c_sd(sdDev);
//     if (pSd == NULL) {
//         status = false;
//         return;
//     }
//     pUsb = new c_usb(usbDev);
//     if (pUsb == NULL) {
//         status = false;
//         return;
//     }
//     sd_device  = sdDev;
//     usb_device = usbDev;
//     status = true;
// }

// bool c_massStorage::begin() {
//     if (status == false) 
//         return false;
//     
//     pSd->begin  (sd_device );
//     pUsb->beging(usb_device);
//     return true;
// }

// /*******************************************************************************
// * Function Name  : Mass_Storage_In
// * Description    : Mass Storage IN transfer.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void c_massStorage:: Mass_Storage_In (void)
// {
//   switch (Bot_State)
//   {
//     case BOT_CSW_Send:
//     case BOT_ERROR:
//       Bot_State = BOT_IDLE;
//       SetEPRxStatus(ENDP2, EP_RX_VALID);/* enable the Endpoint to receive the next cmd*/
//       break;
//     case BOT_DATA_IN:
//       switch (CBW.CB[0])
//       {
//         case SCSI_READ10:
//           SCSI_Read10_Cmd(CBW.bLUN , SCSI_LBA , SCSI_BlkLen);
//           break;
//       }
//       break;
//     case BOT_DATA_IN_LAST:
//       Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
//       SetEPRxStatus(ENDP2, EP_RX_VALID);
//       break;

//     default:
//       break;
//   }
// }
/*******************************************************************************
* Function Name  : Transfer_Data_Request
* Description    : Send the request response to the PC HOST.
* Input          : uint8_t* Data_Address : point to the data to transfer.
*                  uint16_t Data_Length : the number of Bytes to transfer.
* Output         : None.
* Return         : None.
*******************************************************************************/
void c_scsi::Transfer_Data_Request(uint8_t* Data_Pointer, uint16_t Data_Len) {
    USB_SIL_Write(EP1_IN, Data_Pointer, Data_Len);
    SetEPTxStatus(ENDP1, EP_TX_VALID);
    Bot_State           = BOT_DATA_IN_LAST;
    CSW.dDataResidue   -= Data_Len;
    CSW.bStatus         = CSW_CMD_PASSED;
}
/*******************************************************************************
* Function Name  : SCSI_Inquiry_Cmd
* Description    : SCSI Inquiry Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void c_scsi::SCSI_Inquiry_Cmd(uint8_t lun) {
    uint8_t* Inquiry_Data;
    uint16_t Inquiry_Data_Length;

    if (CBW.CB[1] & 0x01) {
        Inquiry_Data = Page00_Inquiry_Data;
        Inquiry_Data_Length = 5;
    } else {
        Inquiry_Data = Standard_Inquiry_Data;
        (CBW.CB[4] <= STANDARD_INQUIRY_DATA_LEN) ? (Inquiry_Data_Length = CBW.CB[4]) :
                                                   (Inquiry_Data_Length = STANDARD_INQUIRY_DATA_LEN);
    }
    Transfer_Data_Request(Inquiry_Data, Inquiry_Data_Length);
}

/*******************************************************************************
* Function Name  : SCSI_ReadFormatCapacity_Cmd
* Description    : SCSI ReadFormatCapacity Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
// void SCSI_ReadFormatCapacity_Cmd(uint8_t lun) {

//   if (MAL_GetStatus(lun) != 0 )
//   {
//     Set_Scsi_Sense_Data(CBW.bLUN, NOT_READY, MEDIUM_NOT_PRESENT);
//     Set_CSW (CSW_CMD_FAILED, SEND_CSW_ENABLE);
//     Bot_Abort(DIR_IN);
//     return;
//   }
//   ReadFormatCapacity_Data[4] = (uint8_t)(Mass_Block_Count[lun] >> 24);
//   ReadFormatCapacity_Data[5] = (uint8_t)(Mass_Block_Count[lun] >> 16);
//   ReadFormatCapacity_Data[6] = (uint8_t)(Mass_Block_Count[lun] >>  8);
//   ReadFormatCapacity_Data[7] = (uint8_t)(Mass_Block_Count[lun]);

//   ReadFormatCapacity_Data[9] = (uint8_t)(Mass_Block_Size[lun] >>  16);
//   ReadFormatCapacity_Data[10] = (uint8_t)(Mass_Block_Size[lun] >>  8);
//   ReadFormatCapacity_Data[11] = (uint8_t)(Mass_Block_Size[lun]);
//   Transfer_Data_Request(ReadFormatCapacity_Data, READ_FORMAT_CAPACITY_DATA_LEN);
// }

// /*******************************************************************************
// * Function Name  : SCSI_ReadCapacity10_Cmd
// * Description    : SCSI ReadCapacity10 Command routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_ReadCapacity10_Cmd(uint8_t lun)
// {

//   if (MAL_GetStatus(lun))
//   {
//     Set_Scsi_Sense_Data(CBW.bLUN, NOT_READY, MEDIUM_NOT_PRESENT);
//     Set_CSW (CSW_CMD_FAILED, SEND_CSW_ENABLE);
//     Bot_Abort(DIR_IN);
//     return;
//   }

//   ReadCapacity10_Data[0] = (uint8_t)((Mass_Block_Count[lun] - 1) >> 24);
//   ReadCapacity10_Data[1] = (uint8_t)((Mass_Block_Count[lun] - 1) >> 16);
//   ReadCapacity10_Data[2] = (uint8_t)((Mass_Block_Count[lun] - 1) >>  8);
//   ReadCapacity10_Data[3] = (uint8_t)(Mass_Block_Count[lun] - 1);

//   ReadCapacity10_Data[4] = (uint8_t)(Mass_Block_Size[lun] >>  24);
//   ReadCapacity10_Data[5] = (uint8_t)(Mass_Block_Size[lun] >>  16);
//   ReadCapacity10_Data[6] = (uint8_t)(Mass_Block_Size[lun] >>  8);
//   ReadCapacity10_Data[7] = (uint8_t)(Mass_Block_Size[lun]);
//   Transfer_Data_Request(ReadCapacity10_Data, READ_CAPACITY10_DATA_LEN);
// }

// /*******************************************************************************
// * Function Name  : SCSI_ModeSense6_Cmd
// * Description    : SCSI ModeSense6 Command routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_ModeSense6_Cmd (uint8_t lun)
// {
//   Transfer_Data_Request(Mode_Sense6_data, MODE_SENSE6_DATA_LEN);
// }

// /*******************************************************************************
// * Function Name  : SCSI_ModeSense10_Cmd
// * Description    : SCSI ModeSense10 Command routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_ModeSense10_Cmd (uint8_t lun)
// {
//   Transfer_Data_Request(Mode_Sense10_data, MODE_SENSE10_DATA_LEN);
// }

// /*******************************************************************************
// * Function Name  : SCSI_RequestSense_Cmd
// * Description    : SCSI RequestSense Command routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_RequestSense_Cmd (uint8_t lun)
// {
//   uint8_t Request_Sense_data_Length;

//   if (CBW.CB[4] <= REQUEST_SENSE_DATA_LEN)
//   {
//     Request_Sense_data_Length = CBW.CB[4];
//   }
//   else
//   {
//     Request_Sense_data_Length = REQUEST_SENSE_DATA_LEN;
//   }
//   Transfer_Data_Request(Scsi_Sense_Data, Request_Sense_data_Length);
// }

// /*******************************************************************************
// * Function Name  : Set_Scsi_Sense_Data
// * Description    : Set Scsi Sense Data routine.
// * Input          : uint8_t Sens_Key
//                    uint8_t Asc.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void Set_Scsi_Sense_Data(uint8_t lun, uint8_t Sens_Key, uint8_t Asc)
// {
//   Scsi_Sense_Data[2] = Sens_Key;
//   Scsi_Sense_Data[12] = Asc;
// }

// /*******************************************************************************
// * Function Name  : SCSI_Start_Stop_Unit_Cmd
// * Description    : SCSI Start_Stop_Unit Command routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_Start_Stop_Unit_Cmd(uint8_t lun)
// {
//   Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
// }

// /*******************************************************************************
// * Function Name  : SCSI_Read10_Cmd
// * Description    : SCSI Read10 Command routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_Read10_Cmd(uint8_t lun , uint32_t LBA , uint32_t BlockNbr)
// {

//   if (Bot_State == BOT_IDLE)
//   {
//     if (!(SCSI_Address_Management(CBW.bLUN, SCSI_READ10, LBA, BlockNbr)))/*address out of range*/
//     {
//       return;
//     }

//     if ((CBW.bmFlags & 0x80) != 0)
//     {
//       Bot_State = BOT_DATA_IN;
//       Read_Memory(lun, LBA , BlockNbr);
//     }
//     else
//     {
//       Bot_Abort(BOTH_DIR);
//       Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
//       Set_CSW (CSW_CMD_FAILED, SEND_CSW_ENABLE);
//     }
//     return;
//   }
//   else if (Bot_State == BOT_DATA_IN)
//   {
//     Read_Memory(lun , LBA , BlockNbr);
//   }
// }

// /*******************************************************************************
// * Function Name  : SCSI_Write10_Cmd
// * Description    : SCSI Write10 Command routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_Write10_Cmd(uint8_t lun , uint32_t LBA , uint32_t BlockNbr)
// {

//   if (Bot_State == BOT_IDLE)
//   {
//     if (!(SCSI_Address_Management(CBW.bLUN, SCSI_WRITE10 , LBA, BlockNbr)))/*address out of range*/
//     {
//       return;
//     }

//     if ((CBW.bmFlags & 0x80) == 0)
//     {
//       Bot_State = BOT_DATA_OUT;
//     #ifndef STM32F10X_CL
//       SetEPRxStatus(ENDP2, EP_RX_VALID);
//     #endif /* STM32F10X_CL */
//     }
//     else
//     {
//       Bot_Abort(DIR_IN);
//       Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
//       Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
//     }
//     return;
//   }
//   else if (Bot_State == BOT_DATA_OUT)
//   {
//     Write_Memory(lun , LBA , BlockNbr);
//   }
// }

// /*******************************************************************************
// * Function Name  : SCSI_Verify10_Cmd
// * Description    : SCSI Verify10 Command routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_Verify10_Cmd(uint8_t lun)
// {
//   if ((CBW.dDataLength == 0) && !(CBW.CB[1] & BLKVFY))/* BLKVFY not set*/
//   {
//     Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
//   }
//   else
//   {
//     Bot_Abort(BOTH_DIR);
//     Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
//     Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
//   }
// }
// /*******************************************************************************
// * Function Name  : SCSI_Valid_Cmd
// * Description    : Valid Commands routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_Valid_Cmd(uint8_t lun)
// {
//   if (CBW.dDataLength != 0)
//   {
//     Bot_Abort(BOTH_DIR);
//     Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
//     Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
//   }
//   else
//     Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
// }
// /*******************************************************************************
// * Function Name  : SCSI_Valid_Cmd
// * Description    : Valid Commands routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_TestUnitReady_Cmd(uint8_t lun)
// {
//   if (MAL_GetStatus(lun))
//   {
//     Set_Scsi_Sense_Data(CBW.bLUN, NOT_READY, MEDIUM_NOT_PRESENT);
//     Set_CSW (CSW_CMD_FAILED, SEND_CSW_ENABLE);
//     Bot_Abort(DIR_IN);
//     return;
//   }
//   else
//   {
//     Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
//   }
// }
// /*******************************************************************************
// * Function Name  : SCSI_Format_Cmd
// * Description    : Format Commands routine.
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_Format_Cmd(uint8_t lun)
// {
//   if (MAL_GetStatus(lun))
//   {
//     Set_Scsi_Sense_Data(CBW.bLUN, NOT_READY, MEDIUM_NOT_PRESENT);
//     Set_CSW (CSW_CMD_FAILED, SEND_CSW_ENABLE);
//     Bot_Abort(DIR_IN);
//     return;
//   }
// #ifdef USE_STM3210E_EVAL
//   else
//   {
//     NAND_Format();
//     Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
//   }
// #endif
// }
// /*******************************************************************************
// * Function Name  : SCSI_Invalid_Cmd
// * Description    : Invalid Commands routine
// * Input          : None.
// * Output         : None.
// * Return         : None.
// *******************************************************************************/
// void SCSI_Invalid_Cmd(uint8_t lun)
// {
//   if (CBW.dDataLength == 0)
//   {
//     Bot_Abort(DIR_IN);
//   }
//   else
//   {
//     if ((CBW.bmFlags & 0x80) != 0)
//     {
//       Bot_Abort(DIR_IN);
//     }
//     else
//     {
//       Bot_Abort(BOTH_DIR);
//     }
//   }
//   Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
//   Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
// }

// /*******************************************************************************
// * Function Name  : SCSI_Address_Management
// * Description    : Test the received address.
// * Input          : uint8_t Cmd : the command can be SCSI_READ10 or SCSI_WRITE10.
// * Output         : None.
// * Return         : Read\Write status (bool).
// *******************************************************************************/
// bool SCSI_Address_Management(uint8_t lun , uint8_t Cmd , uint32_t LBA , uint32_t BlockNbr)
// {

//   if ((LBA + BlockNbr) > Mass_Block_Count[lun] )
//   {
//     if (Cmd == SCSI_WRITE10)
//     {
//       Bot_Abort(BOTH_DIR);
//     }
//     Bot_Abort(DIR_IN);
//     Set_Scsi_Sense_Data(lun, ILLEGAL_REQUEST, ADDRESS_OUT_OF_RANGE);
//     Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
//     return (FALSE);
//   }


//   if (CBW.dDataLength != BlockNbr * Mass_Block_Size[lun])
//   {
//     if (Cmd == SCSI_WRITE10)
//     {
//       Bot_Abort(BOTH_DIR);
//     }
//     else
//     {
//       Bot_Abort(DIR_IN);
//     }
//     Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
//     Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
//     return (FALSE);
//   }
//   return (TRUE);
// }






