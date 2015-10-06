//==========================================================
#ifndef __M_VIRTUAL_COM_H__
#define __M_VIRTUAL_COM_H__
#include "typeDefine.h"
#include "usb_core.h"
//==========================================================
#define USB_SERIAL_DATA_SIZE        64
#define USB_SERIAL_EP_NUM           4
#define USB_SERIAL_CONFIG_NUM       1
#define USB_SERIAL_FRAME_INTERVAL   5
#define USB_SERIAL_BTABLE_ADDRESS   0

#define DESCRIPTOR_ENDPOINT_IN_USB_VCOM        0x80
#define DESCRIPTOR_ENDPOINT_OUT_USB_VCOM       0x00

#define MANAGEMENT_ENDP_USB_VCOM      2
#define MANAGEMENT_ADDR_USB_VCOM      0x100
#define MANAGEMENT_EPSIZE_USB_VCOM    0x40

#define CTRL_ENDP_USB_VCOM            0
#define CTRL_RX_ADDR_USB_VCOM         0x40
#define CTRL_TX_ADDR_USB_VCOM         0x80
#define CTRL_EPSIZE_USB_VCOM          0x40

#define TX_ENDP_USB_VCOM              1
#define TX_ADDR_USB_VCOM              0xC0
#define TX_EPSIZE_USB_VCOM            0x40

#define RX_ENDP_USB_VCOM              3
#define RX_ADDR_USB_VCOM              0x110
#define RX_EPSIZE_USB_VCOM            0x40
#define MAX_POWER (100 >> 1)

#ifndef USB_ISR_MSK
/* Handle CTRM, WKUPM, SUSPM, ERRM, SOFM, ESOFM, RESETM */
#define ISR_MSK_USB_VCOM 0xBF00
#endif

typedef struct {
  uint32 bitrate;
  uint8  format;
  uint8  paritytype;
  uint8  datatype;
}LINE_CODING_USB_VCOM;
//==========================================================
extern void (*serialEpInt_IN[7]) (void);
extern void (*serialEpInt_OUT[7])(void);
extern void (*serialCallBack[8]) (void);
extern const DEVICE_PROP            Usb_Serial_Property;
extern const USER_STANDARD_REQUESTS Usb_Serial_Request;

extern usblib_dev  usbSerialDev;
//==========================================================
class usbSerial : public Print {
public: 
//---------------------------------------
// !! 必须先调用 类才可以使用
    void begin (void);          // 在main中调用起动
    void setSem(void);          // 在任务初始化函数中调用
//
//---------------------------------------
// 接口函数
    void end  (void);                       // 停电啦
    void flush(void);                       // 数据清空
    uint32 available(void);

    uint32 read(void *buf, uint32 len);         // 读取数据
    uint8  read(void);                          // 读取数据
    virtual void write(uint8);                  // 写入数据
    virtual void write(const char *str);        // 写入数据
    virtual void write(const void*, uint32);    // 写入数据
//
//---------------------------------------
// 内部函数，不要操作
public:
    usbSerial();
    RESULT SerialDataSetup(uint8_t RequestNo);
    void Handle_USBAsynchXfer   (void);
    //=================================================
    //
public:
    OS_SEM          semTxReady;
    OS_SEM          semRxReady;
    uint8           usbSending;
    ring_buffer     rxRingbuf;
    ring_buffer     txRingbuf;
    uint8_t txBuf   [USB_SERIAL_TX_LENGTH];
    uint8_t rxBuf   [USB_SERIAL_RX_LENGTH];
    uint8_t usbRxBuf[USB_SERIAL_DATA_SIZE];
    uint8_t usbTxBuf[USB_SERIAL_DATA_SIZE];
};
extern usbSerial usbSerial1;
#endif

