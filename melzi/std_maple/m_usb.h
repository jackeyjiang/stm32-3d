//================================================
#ifndef __M_USB_H__
#define __M_USB_H__
//================================================
#ifdef __cplusplus
extern "C" {
#endif
#include "typeDefine.h"
//=======================================
//== 寄存器 ==
#define USB_NR_EP_REGS  8  
typedef struct usb_reg_map {
    __io uint32 ep[USB_NR_EP_REGS];
    int32 RESERVED[8];       
    __io uint32 cntr;
    __io uint32 istr;             
    __io uint32 fnr;               
    __io uint32 daddr;           
    __io uint32 btable;          
} usb_reg_map;
#define USB_BASE ((struct usb_reg_map*)0x40005C00)
//=======================================
/* SCSI Commands */
#define SCSI_FORMAT_UNIT                            0x04
#define SCSI_INQUIRY                                0x12
#define SCSI_MODE_SELECT6                           0x15
#define SCSI_MODE_SELECT10                          0x55
#define SCSI_MODE_SENSE6                            0x1A
#define SCSI_MODE_SENSE10                           0x5A
#define SCSI_ALLOW_MEDIUM_REMOVAL                   0x1E
#define SCSI_READ6                                  0x08
#define SCSI_READ10                                 0x28
#define SCSI_READ12                                 0xA8
#define SCSI_READ16                                 0x88

#define SCSI_READ_CAPACITY10                        0x25
#define SCSI_READ_CAPACITY16                        0x9E

#define SCSI_REQUEST_SENSE                          0x03
#define SCSI_START_STOP_UNIT                        0x1B
#define SCSI_TEST_UNIT_READY                        0x00
#define SCSI_WRITE6                                 0x0A
#define SCSI_WRITE10                                0x2A
#define SCSI_WRITE12                                0xAA
#define SCSI_WRITE16                                0x8A

#define SCSI_VERIFY10                               0x2F
#define SCSI_VERIFY12                               0xAF
#define SCSI_VERIFY16                               0x8F

#define SCSI_SEND_DIAGNOSTIC                        0x1D
#define SCSI_READ_FORMAT_CAPACITIES                 0x23
//=======================================

#define USB_DESCRIPTOR_TYPE_DEVICE        0x01
#define USB_DESCRIPTOR_TYPE_CONFIGURATION 0x02
#define USB_DESCRIPTOR_TYPE_STRING        0x03
#define USB_DESCRIPTOR_TYPE_INTERFACE     0x04
#define USB_DESCRIPTOR_TYPE_ENDPOINT      0x05

#define USB_DEVICE_CLASS_CDC              0x02
#define USB_DEVICE_SUBCLASS_CDC           0x00
#define USB_INTERFACE_CLASS_CDC           0x02
#define USB_INTERFACE_SUBCLASS_CDC_ACM    0x02
#define USB_INTERFACE_CLASS_DIC           0x0A

#define USB_CONFIG_ATTR_BUSPOWERED        0x80
#define USB_CONFIG_ATTR_SELF_POWERED      0xc0

#define USB_EP_TYPE_INTERRUPT             0x03
#define USB_EP_TYPE_BULK                  0x02
/* Descriptor structs and declaration helpers */
#define USB_DESCRIPTOR_STRING_LEN(x) (2 + (x << 1))
#define USB_DESCRIPTOR_STRING_N           0x03

#define SEND_ENCAPSULATED_COMMAND   0x00
#define GET_ENCAPSULATED_RESPONSE   0x01
#define SET_COMM_FEATURE            0x02
#define GET_COMM_FEATURE            0x03
#define CLEAR_COMM_FEATURE          0x04
#define SET_LINE_CODING             0x20
#define GET_LINE_CODING             0x21
#define SET_CONTROL_LINE_STATE      0x22
#define SEND_BREAK                  0x23

typedef enum usb_dev_state {
    USB_UNCONNECTED,
    USB_ATTACHED,
    USB_POWERED,
    USB_SUSPENDED,
    USB_ADDRESSED,
    USB_CONFIGURED
} usb_dev_state;

typedef enum _RESUME_STATE {
  RESUME_EXTERNAL,
  RESUME_INTERNAL,
  RESUME_LATER,
  RESUME_WAIT,
  RESUME_START,
  RESUME_ON,
  RESUME_OFF,
  RESUME_ESOF
} RESUME_STATE;

typedef struct usbCallbackFxn {
    voidFuncPtr     sof;
    voidFuncPtr     ctr;
    voidFuncPtr     reset;
    voidFuncPtr     dovr;
    voidFuncPtr     err;
    voidFuncPtr     wkup;
    voidFuncPtr     esof;
    voidFuncPtr     susp;
}usbCallbackFxn;

typedef struct pEpInt_IN_Fxn {
    voidFuncPtr     In0;
    voidFuncPtr     In1;
    voidFuncPtr     In2;
    voidFuncPtr     In3;
    voidFuncPtr     In4;
    voidFuncPtr     In5;
    voidFuncPtr     In6;
}pEpInt_IN_Fxn;

typedef struct pEpInt_OUT_Fxn {
    voidFuncPtr     Out0;
    voidFuncPtr     Out1;
    voidFuncPtr     Out2;
    voidFuncPtr     Out3;
    voidFuncPtr     Out4;
    voidFuncPtr     Out5;
    voidFuncPtr     Out6;
}pEpInt_OUT_Fxn;

typedef struct usb_descriptor_device {
    uint8  bLength;
    uint8  bDescriptorType;
    uint8  bcdUSBL;
    uint8  bcdUSBH;
    uint8  bDeviceClass;
    uint8  bDeviceSubClass;
    uint8  bDeviceProtocol;
    uint8  bMaxPacketSize0;
    uint8  idVendorL;
    uint8  idVendorH;
    uint8  idProductL;
    uint8  idProductH;
    uint8  bcdDeviceL;
    uint8  bcdDeviceH;
    uint8  iManufacturer;
    uint8  iProduct;
    uint8  iSerialNumber;
    uint8  bNumConfigurations;
} usb_descriptor_device;

typedef struct usb_descriptor_config_header {
    uint8  bLength;
    uint8  bDescriptorType;
    uint8  wTotalLengthL;
    uint8  wTotalLengthH;
    uint8  bNumInterfaces;
    uint8  bConfigurationValue;
    uint8  iConfiguration;
    uint8  bmAttributes;
    uint8  bMaxPower;
}usb_descriptor_config_header;

typedef struct usb_descriptor_interface {
    uint8 bLength;
    uint8 bDescriptorType;
    uint8 bInterfaceNumber;
    uint8 bAlternateSetting;
    uint8 bNumEndpoints;
    uint8 bInterfaceClass;
    uint8 bInterfaceSubClass;
    uint8 bInterfaceProtocol;
    uint8 iInterface;
}usb_descriptor_interface;

typedef struct usb_descriptor_endpoint {
    uint8  bLength;
    uint8  bDescriptorType;
    uint8  bEndpointAddress;
    uint8  bmAttributes;
    uint8  wMaxPacketSizeL;
    uint8  wMaxPacketSizeH;
    uint8  bInterval;
}usb_descriptor_endpoint;
  
#define CDC_FUNCTIONAL_DESCRIPTOR(DataSize)     \
  struct {                                      \
      uint8 bLength;                            \
      uint8 bDescriptorType;                    \
      uint8 SubType;                            \
      uint8 Data[DataSize];                     \
  }
  
#define USB_DESCRIPTOR_SRTING(DataSize)     \
  struct {                                  \
      uint8 bLength;                        \
      uint8 bDescriptorType;                \
      uint8 bString[DataSize];              \
  }

typedef struct usb_descriptor_string {
    uint8 bLength;
    uint8 bDescriptorType;
    uint8 bString[];
} usb_descriptor_string;

//== 功能描述表机构
#define CDC_FUNCTIONAL_DESCRIPTOR_SIZE(DataSize) (3 + DataSize)
#define CDC_FUNCTIONAL_DESCRIPTOR(DataSize)     \
  struct {                                      \
      uint8 bLength;                            \
      uint8 bDescriptorType;                    \
      uint8 SubType;                            \
      uint8 Data[DataSize];                     \
  }
//== 配置表结构  
typedef struct {
    usb_descriptor_config_header Config_Header;
    usb_descriptor_interface     CCI_Interface;
    CDC_FUNCTIONAL_DESCRIPTOR(2) CDC_Functional_IntHeader;
    CDC_FUNCTIONAL_DESCRIPTOR(2) CDC_Functional_CallManagement;
    CDC_FUNCTIONAL_DESCRIPTOR(1) CDC_Functional_ACM;
    CDC_FUNCTIONAL_DESCRIPTOR(2) CDC_Functional_Union;
    usb_descriptor_endpoint      ManagementEndpoint;
    usb_descriptor_interface     DCI_Interface;
    usb_descriptor_endpoint      DataOutEndpoint;
    usb_descriptor_endpoint      DataInEndpoint;
} usb_descriptor_config;
//================================================
// 设备描述总表
typedef struct usblib_dev {
    uint16                  timeOut;
    uint8                   SuspendEnable;
    pEpInt_IN_Fxn           *pEpInt_IN;
    pEpInt_OUT_Fxn          *pEpInt_OUT;
    usb_dev_state           state;
    usb_dev_state           prevState;
    DEVICE                 *Device_Table;
    USER_STANDARD_REQUESTS *User_Standard_Requests;
    DEVICE_PROP            *Device_Property;
    usbCallbackFxn         *callBack;
    usb_descriptor_device  *deviceList;
    usb_descriptor_config  *ConfigList;
    usb_descriptor_string  *String_LangID;
    usb_descriptor_string  *String_iManufacturer;
    usb_descriptor_string  *String_iProduct;
    ONE_DESCRIPTOR         *Device_Descriptor;
    ONE_DESCRIPTOR         *Config_Descriptor;
    ONE_DESCRIPTOR         *String_Descriptor[3];
    uint8 *                 Linecoding;
    uint8                   LinecodingSize;
    rcc_clk_id              clk_id;
} usblib_dev;
extern  void (*pEpInt_IN[7])   (void);
extern  void (*pEpInt_OUT[7])  (void);
extern  void (*pUsbCallBack[8])(void);
extern void usbPortStatusIn(void);
extern RESULT Class_Data_Setup(uint8_t RequestNo);
extern RESULT usbPortNoDataSetup(uint8_t RequestNo);
extern RESULT usbGetInterfaceSetting(uint8_t Interface, uint8_t AlternateSetting);
extern uint8_t *usbGetConfigDescriptor(uint16_t Length);
extern uint8_t *usbGetDeviceDescriptor(uint16_t Length);
extern uint8_t *usbGetStringDescriptor(uint16_t Length);
extern void usbSetConfig(); 
extern void usbSetAddress(); 
//================================================
class c_usb {
public:
    c_usb(usblib_dev *dev) {usb_device = dev;}
    void beging (usblib_dev *dev);
    void waitConnect();
        
    void USB_Istr (void);
    static void   User_SetDeviceAddress();
    static void   User_SetConfiguration();
    void   InitPort (voidFuncPtr fxn);
    static void   ResetPort(voidFuncPtr fxn);
    static void   Process_Status_IN (void);
    static RESULT Class_Data_Setup  (uint8_t RequestNo);
    static uint8_t *getSetLineCoding(uint16_t Length);
    static RESULT Class_NoData_Setup(uint8_t RequestNo);
    static RESULT Class_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
    static uint8_t *GetDeviceDescriptor(uint16_t Length);
    static uint8_t *GetConfigDescriptor(uint16_t Length);
    static uint8_t *GetStringDescriptor(uint16_t Length); 
    static usblib_dev  *usb_device;
private:
    static void PinSet (uint8_t NewState);
    static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);
    static void Get_SerialNum();
private:
    void Resume_Init();
    void Resume (RESUME_STATE eResumeSetVal);
    void Suspend(void);
    void Leave_LowPowerMode(void);
    void Enter_LowPowerMode (void);
    void PinInit();
    void NvicUsb(void);
};
extern c_usb usb;
#ifdef __cplusplus
}
#endif
//================================================
#endif
