//================================================================================
#include "m_include.h"
#ifdef USB_SERIAL_USE
//================================================================================
/* USB 标准设备描述符 */
//================================================================================
#define USB_VCOM_ENDPOING_NUM 0x04
const DEVICE Device_Table_UsbVcom = {
    .Total_Endpoint      = USB_VCOM_ENDPOING_NUM,
    .Total_Configuration = 1
};
#define LEAFLABS_ID_VENDOR  0x1EAF
#define MAPLE_ID_PRODUCT    0x0004
#define USB_CDCACM_DECLARE_DEV_DESC(vid, pid) {                         \
      .bLength            = sizeof(usb_descriptor_device),              \
      .bDescriptorType    = USB_DESCRIPTOR_TYPE_DEVICE,                 \
      .bcdUSBL            = 0x00,                                       \
      .bcdUSBH            = 0x02,                                       \
      .bDeviceClass       = USB_DEVICE_CLASS_CDC,                       \
      .bDeviceSubClass    = USB_DEVICE_SUBCLASS_CDC,                    \
      .bDeviceProtocol    = 0x00,                                       \
      .bMaxPacketSize0    = 0x40,                                       \
      .idVendorL          = (uint8)vid,                                 \
      .idVendorH          = vid/0x100,                                  \
      .idProductL         = (uint8)pid,                                 \
      .idProductH         = pid/0x100,                                  \
      .bcdDeviceL         = 0x00,                                       \
      .bcdDeviceH         = 0x02,                                       \
      .iManufacturer      = 0x01,                                       \
      .iProduct           = 0x02,                                       \
      .iSerialNumber      = 0x00,                                       \
      .bNumConfigurations = 0x01,                                       \
 }
static const usb_descriptor_device deviceList_UsbVcom =
    USB_CDCACM_DECLARE_DEV_DESC(LEAFLABS_ID_VENDOR, MAPLE_ID_PRODUCT);
//================================================================================
// 配置表
static const usb_descriptor_config usbVcomDescriptor_Config = {
    .Config_Header = {
        .bLength              = sizeof(usb_descriptor_config_header),
        .bDescriptorType      = USB_DESCRIPTOR_TYPE_CONFIGURATION,
        .wTotalLengthL        = sizeof(usb_descriptor_config),
        .wTotalLengthH        = sizeof(usb_descriptor_config)/0x100,
        .bNumInterfaces       = 0x02,
        .bConfigurationValue  = 0x01,
        .iConfiguration       = 0x00,
        .bmAttributes         = (USB_CONFIG_ATTR_BUSPOWERED |USB_CONFIG_ATTR_SELF_POWERED),
        .bMaxPower            = MAX_POWER,
    },
    .CCI_Interface = {
        .bLength            = sizeof(usb_descriptor_interface),
        .bDescriptorType    = USB_DESCRIPTOR_TYPE_INTERFACE,
        .bInterfaceNumber   = 0x00,
        .bAlternateSetting  = 0x00,
        .bNumEndpoints      = 0x01,
        .bInterfaceClass    = USB_INTERFACE_CLASS_CDC,
        .bInterfaceSubClass = USB_INTERFACE_SUBCLASS_CDC_ACM,
        .bInterfaceProtocol = 0x01, /* Common AT Commands */
        .iInterface         = 0x00,
    },
    .CDC_Functional_IntHeader = {
        .bLength         = CDC_FUNCTIONAL_DESCRIPTOR_SIZE(2),
        .bDescriptorType = 0x24,
        .SubType         = 0x00,
        .Data            = {0x01, 0x10},
    },
    .CDC_Functional_CallManagement = {
        .bLength         = CDC_FUNCTIONAL_DESCRIPTOR_SIZE(2),
        .bDescriptorType = 0x24,
        .SubType         = 0x01,
        .Data            = {0x03, 0x01},
    },
    .CDC_Functional_ACM = {
        .bLength         = CDC_FUNCTIONAL_DESCRIPTOR_SIZE(1),
        .bDescriptorType = 0x24,
        .SubType         = 0x02,
        .Data            = {0x06},
    },
    .CDC_Functional_Union = {
        .bLength         = CDC_FUNCTIONAL_DESCRIPTOR_SIZE(2),
        .bDescriptorType = 0x24,
        .SubType         = 0x06,
        .Data            = {0x00, 0x01},
    },
    .ManagementEndpoint = {
        .bLength          = sizeof(usb_descriptor_endpoint),
        .bDescriptorType  = USB_DESCRIPTOR_TYPE_ENDPOINT,
        .bEndpointAddress = (DESCRIPTOR_ENDPOINT_IN_USB_VCOM | MANAGEMENT_ENDP_USB_VCOM),
        .bmAttributes     = USB_EP_TYPE_INTERRUPT,
        .wMaxPacketSizeL  = MANAGEMENT_EPSIZE_USB_VCOM,
        .wMaxPacketSizeH  = MANAGEMENT_EPSIZE_USB_VCOM/0x100,
        .bInterval        = 0xFF,
    },
    .DCI_Interface = {
        .bLength            = sizeof(usb_descriptor_interface),
        .bDescriptorType    = USB_DESCRIPTOR_TYPE_INTERFACE,
        .bInterfaceNumber   = 0x01,
        .bAlternateSetting  = 0x00,
        .bNumEndpoints      = 0x02,
        .bInterfaceClass    = USB_INTERFACE_CLASS_DIC,
        .bInterfaceSubClass = 0x00, /* None */
        .bInterfaceProtocol = 0x00, /* None */
        .iInterface         = 0x00,
    },
    .DataOutEndpoint = {
        .bLength          = sizeof(usb_descriptor_endpoint),
        .bDescriptorType  = USB_DESCRIPTOR_TYPE_ENDPOINT,
        .bEndpointAddress = (DESCRIPTOR_ENDPOINT_OUT_USB_VCOM | RX_ENDP_USB_VCOM),
        .bmAttributes     = USB_EP_TYPE_BULK,
        .wMaxPacketSizeL  = RX_EPSIZE_USB_VCOM,
        .wMaxPacketSizeH  = RX_EPSIZE_USB_VCOM/0x100,
        .bInterval        = 0x00,
    },
    .DataInEndpoint = {
        .bLength          = sizeof(usb_descriptor_endpoint),
        .bDescriptorType  = USB_DESCRIPTOR_TYPE_ENDPOINT,
        .bEndpointAddress = (DESCRIPTOR_ENDPOINT_IN_USB_VCOM | TX_ENDP_USB_VCOM),
        .bmAttributes     = USB_EP_TYPE_BULK,
        .wMaxPacketSizeL  = TX_EPSIZE_USB_VCOM,
        .wMaxPacketSizeH  = TX_EPSIZE_USB_VCOM/0x100,
        .bInterval        = 0x00,
    },
};
//================================================================================
// 字符描述符
static const USB_DESCRIPTOR_SRTING(2) usbVcomDescriptor_LangID = {
    .bLength         = USB_DESCRIPTOR_STRING_LEN(1),
    .bDescriptorType = USB_DESCRIPTOR_TYPE_STRING,
    .bString         = {0x09, 0x04},
};
static const USB_DESCRIPTOR_SRTING(16) usbVcomDescriptor_iManufacturer = {
    .bLength = USB_DESCRIPTOR_STRING_LEN(8),
    .bDescriptorType = USB_DESCRIPTOR_TYPE_STRING,
    .bString = {'L',0,'e',0,'a',0,'f',0,'L',0,'a',0,'b',0,'s',0},
};
static const USB_DESCRIPTOR_SRTING(18) usbVcomDescriptor_iProduct = {
    .bLength         = USB_DESCRIPTOR_STRING_LEN(9),
    .bDescriptorType = USB_DESCRIPTOR_TYPE_STRING,
    .bString         = {'M',0,'a',0,'p',0,'l',0,'e',0,' ',0,'0',0,'0',0,'1',0},
};
//================================================================================
// 描述符传输结构
static ONE_DESCRIPTOR usb_Vcom_Device_Descriptor = {   
    .Descriptor      = (uint8*)&deviceList_UsbVcom,
    .Descriptor_Size = sizeof(usb_descriptor_device)
};
static ONE_DESCRIPTOR usb_Vcom_Config_Descriptor = {
    .Descriptor      = (uint8*)&usbVcomDescriptor_Config,
    .Descriptor_Size = sizeof(usb_descriptor_config)
};
static ONE_DESCRIPTOR usb_Vcom_String_Descriptor[USB_DESCRIPTOR_STRING_N] = {
    {(uint8*)&usbVcomDescriptor_LangID,       USB_DESCRIPTOR_STRING_LEN(1)},
    {(uint8*)&usbVcomDescriptor_iManufacturer,USB_DESCRIPTOR_STRING_LEN(8)},
    {(uint8*)&usbVcomDescriptor_iProduct,     USB_DESCRIPTOR_STRING_LEN(5)}
};
//================================================================================
// 函数实现表
void InitUsbVcom ();
void ResetUsbVcom();
const DEVICE_PROP Device_Property_UsbVcom = {   
    .Init                        = InitUsbVcom,
    .Reset                       = ResetUsbVcom,
    .Process_Status_IN           = NOP_Process,
    .Process_Status_OUT          = NOP_Process,
    .Class_Data_Setup            = c_usb::Class_Data_Setup,
    .Class_NoData_Setup          = c_usb::Class_NoData_Setup,
    .Class_Get_Interface_Setting = c_usb::Class_Get_Interface_Setting,
    .GetDeviceDescriptor         = c_usb::GetDeviceDescriptor,
    .GetConfigDescriptor         = c_usb::GetConfigDescriptor,
    .GetStringDescriptor         = c_usb::GetStringDescriptor,
    .RxEP_buffer                 = NULL,
    .MaxPacketSize               = USB_SERIAL_DATA_SIZE
};
//================================
const USER_STANDARD_REQUESTS User_Standard_Requests_UsbVcom = {
    .User_GetConfiguration  = NOP_Process,
    .User_SetConfiguration  = c_usb::User_SetConfiguration,
    .User_GetInterface      = NOP_Process,
    .User_SetInterface      = NOP_Process,
    .User_GetStatus         = NOP_Process,
    .User_ClearFeature      = NOP_Process,
    .User_SetEndPointFeature= NOP_Process,
    .User_SetDeviceFeature  = NOP_Process,
    .User_SetDeviceAddress  = c_usb::User_SetDeviceAddress,
};
//================================
// 回调函数
void EP1_IN_Callback_UsbVcom ();
void EP3_OUT_Callback_UsbVcom();
void RESET_UsbVcom  ();
void SOF_UsbVcom    ();
const pEpInt_IN_Fxn pEpInt_IN_UsbVcom = {
    .In0 = EP1_IN_Callback_UsbVcom,
    .In1 = NOP_Process,
    .In2 = NOP_Process,
    .In3 = NOP_Process,
    .In4 = NOP_Process,
    .In5 = NOP_Process,
    .In6 = NOP_Process,
};
const pEpInt_OUT_Fxn pEpInt_OUT_UsbVcom = {
    .Out0 = NOP_Process,
    .Out1 = NOP_Process,
    .Out2 = EP3_OUT_Callback_UsbVcom,
    .Out3 = NOP_Process,
    .Out4 = NOP_Process,
    .Out5 = NOP_Process,
    .Out6 = NOP_Process,
};
const usbCallbackFxn usbCallbackFxn_UsbVcom = {   
    .sof    = SOF_UsbVcom,
    .ctr    = NOP_Process,
    .reset  = RESET_UsbVcom,
    .dovr   = NOP_Process,
    .err    = NOP_Process,
    .wkup   = NOP_Process,
    .esof   = NOP_Process,
    .susp   = NOP_Process,
};

LINE_CODING_USB_VCOM LinecodingUsbVcom = {
    115200, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* no. of bits 8*/
};
//================================================================================
// 设备总表
usblib_dev  usbSerialDev = {
    .timeOut                    = 50,
    .SuspendEnable              = true,
    .pEpInt_IN                  = (pEpInt_IN_Fxn  *)                &pEpInt_IN_UsbVcom,             
    .pEpInt_OUT                 = (pEpInt_OUT_Fxn *)                &pEpInt_OUT_UsbVcom,          
    .state                      = USB_UNCONNECTED,    
    .prevState                  = USB_UNCONNECTED,    
    .Device_Table               = (DEVICE *)                        &Device_Table_UsbVcom,    
    .User_Standard_Requests     = (USER_STANDARD_REQUESTS *)        &User_Standard_Requests_UsbVcom,
    .Device_Property            = (DEVICE_PROP*)                    &Device_Property_UsbVcom,
    .callBack                   = (usbCallbackFxn*)                 &usbCallbackFxn_UsbVcom,
    .deviceList                 = (usb_descriptor_device *)         &deviceList_UsbVcom,
    .ConfigList                 = (usb_descriptor_config *)         &usbVcomDescriptor_Config,
    .String_LangID              = (usb_descriptor_string *)&usbVcomDescriptor_LangID,
    .String_iManufacturer       = (usb_descriptor_string *)&usbVcomDescriptor_iManufacturer,
    .String_iProduct            = (usb_descriptor_string *)&usbVcomDescriptor_iProduct,
    .Device_Descriptor          = &usb_Vcom_Device_Descriptor,
    .Config_Descriptor          = &usb_Vcom_Config_Descriptor,
    .String_Descriptor[0]       = &usb_Vcom_String_Descriptor[0],
    .String_Descriptor[1]       = &usb_Vcom_String_Descriptor[1],
    .String_Descriptor[2]       = &usb_Vcom_String_Descriptor[2],
    .Linecoding                 = (uint8 *)&LinecodingUsbVcom,
    .LinecodingSize             = sizeof(LinecodingUsbVcom),
    .clk_id= RCC_USB
};
//================================================================================
// 实现函数
//================================================================================
// 端口初始化
void serialEpInit()
{  
    /* Initialize Endpoint 0 */
    SetEPType       (CTRL_ENDP_USB_VCOM, EP_CONTROL);
    SetEPTxStatus   (CTRL_ENDP_USB_VCOM, EP_TX_STALL);
    SetEPRxAddr     (CTRL_ENDP_USB_VCOM, CTRL_RX_ADDR_USB_VCOM);
    SetEPTxAddr     (CTRL_ENDP_USB_VCOM, CTRL_TX_ADDR_USB_VCOM);
    Clear_Status_Out(CTRL_ENDP_USB_VCOM);
    SetEPRxCount    (CTRL_ENDP_USB_VCOM, Device_Property.MaxPacketSize);
    SetEPRxStatus   (CTRL_ENDP_USB_VCOM, EP_RX_VALID);

    /* Initialize Endpoint 2 */
    SetEPType       (MANAGEMENT_ENDP_USB_VCOM, EP_INTERRUPT);
    SetEPTxAddr     (MANAGEMENT_ENDP_USB_VCOM, MANAGEMENT_ADDR_USB_VCOM);
    SetEPTxStatus   (MANAGEMENT_ENDP_USB_VCOM, EP_TX_NAK);
    SetEPRxStatus   (MANAGEMENT_ENDP_USB_VCOM, EP_RX_DIS);

    /* Initialize Endpoint 3 */
    SetEPType       (RX_ENDP_USB_VCOM, EP_BULK);
    SetEPRxAddr     (RX_ENDP_USB_VCOM, RX_ADDR_USB_VCOM);
    SetEPRxCount    (RX_ENDP_USB_VCOM, USB_SERIAL_DATA_SIZE);
    SetEPRxStatus   (RX_ENDP_USB_VCOM, EP_RX_VALID);
    
    /* Initialize Endpoint 1 */
    SetEPType       (TX_ENDP_USB_VCOM, EP_BULK);
    SetEPTxAddr     (TX_ENDP_USB_VCOM, TX_ADDR_USB_VCOM);
    SetEPTxStatus   (TX_ENDP_USB_VCOM, EP_TX_NAK);
    SetEPRxStatus   (TX_ENDP_USB_VCOM, EP_RX_DIS);
} 
//================================
usbSerial::usbSerial() {
    usbSending =0;
}
//================================

void EP1_IN_Callback_UsbVcom (void) {
    if (usbSerial1.usbSending) {
        usbSerial1.Handle_USBAsynchXfer();
    }
}
//================================
// usb 数据接收到 rxBuf
void EP3_OUT_Callback_UsbVcom(void) {
    static uint8 bufRemain = 0, bufIndex;
    //
    //===========================================
    //== 上次没有存储完成数据继续加载
    while (bufRemain) {
        if (!rb_safe_insert(&usbSerial1.rxRingbuf, usbSerial1.usbRxBuf[bufIndex++]))
            break;
        bufRemain--;
    }
    bufRemain = 0;
    //
    //===========================================
    //== 读取数据
    int length = USB_SIL_Read(EP3_OUT, usbSerial1.usbRxBuf);
    if (!length) 
        return; 
    //
    //===========================================
    //== 加载数据
    for (int i=0; i<length; i++) {
        if (!rb_safe_insert(&usbSerial1.rxRingbuf, usbSerial1.usbRxBuf[i])) {
            bufIndex  = i;
            bufRemain = length - i;
            break;
        }
    }
    if (*usbSerial1.semRxReady)
        isr_sem_send(usbSerial1.semRxReady);
    SetEPRxValid(RX_ENDP_USB_VCOM);
}
void usb_set_ep_tx_stat(uint8 ep, uint32 status) {
    uint32 epr = USB_BASE->ep[ep];
    epr &= ~(EPRX_STAT | EP_DTOG_RX | EP_DTOG_TX);
    epr |= EP_CTR_RX |EP_CTR_TX;
    epr ^= status;
    USB_BASE->ep[ep] = epr;
}


//================================
// 数据发送 usb 缓存区
void usbSerial::Handle_USBAsynchXfer (void) {
    int length = rb_full_count(&txRingbuf);
    if (length==0) {
        usbSending = 0;
        return;
    }
    if (length>USB_SERIAL_DATA_SIZE)
        length=USB_SERIAL_DATA_SIZE;
    
    for (int i=0, j; i<length; i++) {
        j=rb_safe_remove(&txRingbuf);
        if (j==-1) {
            length=i;
            break;
        }
        usbTxBuf[i] =j;
    }
    UserToPMABufferCopy(usbTxBuf, TX_ADDR_USB_VCOM, length);
    SetEPTxCount(TX_ENDP_USB_VCOM, length);
    SetEPTxValid(TX_ENDP_USB_VCOM);
    usbSending = 1;
}

//================================
//
void RESET_UsbVcom(void) {
    usbSerial1.usbSending = false;
    rb_reset(&usbSerial1.rxRingbuf);
    rb_reset(&usbSerial1.txRingbuf);
}

//================================
void SOF_UsbVcom(void) {
    static uint32_t FrameCount = 0;
  
    if(usb.usb_device->state != USB_CONFIGURED) 
        return;
    if (FrameCount++ != USB_SERIAL_FRAME_INTERVAL)
        return;

    FrameCount = 0;
    if (!usbSerial1.usbSending)
        usbSerial1.Handle_USBAsynchXfer();
}
//================================================================================
// 起动
//================================================================================
void (usbSerial::*serial_pEpInt_IN)(void);
void usbSerial::setSem(void) {
    os_sem_init(semTxReady,0);
    os_sem_init(semRxReady,0);
}
void usbSerial::begin() {
    rb_init(&rxRingbuf, sizeof(rxBuf),rxBuf);
    rb_init(&txRingbuf, sizeof(txBuf),txBuf);

    usb.beging(&usbSerialDev);
}
void InitUsbVcom() {
    usb.InitPort(voidFunc);
}
void ResetUsbVcom() {
    usb.ResetPort(serialEpInit);
}
//================================================================================
// 判读数据量
//================================================================================
uint32 usbSerial::available(void) {
    return rb_full_count(&rxRingbuf);
}
//================================================================================
// 读取数据
//================================================================================
uint32 usbSerial::read(void *buf, uint32 len) {
    char *bufT = (char *)buf;
    int  i;
    
    for (i=0; i<len; i++) {
        *bufT = rb_safe_remove(&rxRingbuf);
        if ((int)*bufT++ == -1) 
            break;
    }
    return i;
}
//================================================================================
// 清空接收数据
//================================================================================
void usbSerial::flush() {
    rb_reset(&rxRingbuf);
}
//================================================================================
// 读取单个数据
//================================================================================
uint8  usbSerial::read(void) {
    return rb_safe_remove(&rxRingbuf);
}
//================================================================================
// 写单个字符
//================================================================================
void usbSerial::write(uint8 ch) {
    rb_safe_insert(&txRingbuf, ch);
}
//================================================================================
// 写字符串
//================================================================================
void usbSerial::write(const char *str) {   
    while (*str) {
        if (!rb_safe_insert(&txRingbuf, *str++))
            break;
    }  
}
//================================================================================
// 写定长数
//================================================================================
void usbSerial::write(const void* pI, uint32 length) {
    char *ch=(char *)pI;
    while (length--) {
        if (!rb_safe_insert(&txRingbuf, *ch++))
            break;
    }
}
usbSerial usbSerial1;
#endif
//================================







