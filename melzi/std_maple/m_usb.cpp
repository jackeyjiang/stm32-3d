//================================================================================
#include "m_include.h"
#ifdef USB_SERIAL_USE
//================================================================================
// 默认建立实体， 定义接口时再对指针赋值
__IO uint16_t           wIstr = 0;
void                    (*pEpInt_IN[7]) (void);
void                    (*pEpInt_OUT[7])(void);
DEVICE                  Device_Table;
DEVICE_PROP             Device_Property;
USER_STANDARD_REQUESTS  User_Standard_Requests;
//========================================
struct {
  __IO RESUME_STATE eState;
  __IO uint8_t      bESOFcnt;
}ResumeS;
//================================
// usb 起动
void c_usb::beging(usblib_dev *dev) {    
    usb_device = dev;
    //== 引脚初始化
    PinInit();
    //== 全局变量指定
    Device_Table            = *dev->Device_Table;
    Device_Property         = *dev->Device_Property;
    User_Standard_Requests  = *dev->User_Standard_Requests;
    memCopy((char *)pEpInt_IN,  (char *)dev->pEpInt_IN,   sizeof(pEpInt_IN) );
    memCopy((char *)pEpInt_OUT, (char *)dev->pEpInt_OUT,  sizeof(pEpInt_OUT));
    
    //== 引起枚举
    PinSet(USB_DISCONNECT_ACTIVE);
    
    //== 初始化 
    USB_Init();
}
//================================
// usb 时钟开启
void c_usb::NvicUsb(void) { 
    nvic.irqEnable(USB_LP_CAN1_RX0_IRQn);
}
//================================
void c_usb::PinInit() {
    gpio.pinMode(USB_DISCONNECT_PIN, OUTPUT);
}

//================================
// 线路引脚设定
void c_usb::PinSet (uint8_t NewState) {
    gpio.digitalWrite(USB_DISCONNECT_PIN, NewState ? HIGH : LOW);
}
//================================
void c_usb::Resume(RESUME_STATE eResumeSetVal)
{
    uint16_t wCNTR;
    if (eResumeSetVal != RESUME_ESOF)
        ResumeS.eState = eResumeSetVal;

    switch (ResumeS.eState) {
        case RESUME_EXTERNAL:
            Resume_Init();
            ResumeS.eState = RESUME_OFF;
            usb_device->state = usb_device->prevState;
            break;
        case RESUME_INTERNAL:
            Resume_Init();
            ResumeS.eState = RESUME_START;
            break;
        case RESUME_LATER:
            ResumeS.bESOFcnt = 2;
            ResumeS.eState = RESUME_WAIT;
            break;
        case RESUME_WAIT:
            ResumeS.bESOFcnt--;
            if (ResumeS.bESOFcnt == 0)
                ResumeS.eState = RESUME_START;
            break;
        case RESUME_START:
            wCNTR = _GetCNTR();
            wCNTR |= CNTR_RESUME;
            _SetCNTR(wCNTR);
            ResumeS.eState = RESUME_ON;
            ResumeS.bESOFcnt = 10;
            break;
        case RESUME_ON:
            ResumeS.bESOFcnt--;
            if (ResumeS.bESOFcnt == 0) {
                wCNTR = _GetCNTR();
                wCNTR &= (~CNTR_RESUME);
                _SetCNTR(wCNTR);
                usb_device->state = usb_device->prevState;
                ResumeS.eState = RESUME_OFF;
            }
            break;
        case RESUME_OFF:
        case RESUME_ESOF:
        default:
            ResumeS.eState = RESUME_OFF;
        break;
    }
}
//================================
void c_usb::Resume_Init(void) {
    uint16_t wCNTR;
    wCNTR = _GetCNTR();
    wCNTR &= (~CNTR_LPMODE);
    _SetCNTR(wCNTR);
    Leave_LowPowerMode();
    _SetCNTR(ISR_MSK_USB_VCOM);
}
//================================
void c_usb::Suspend(void) {
    uint16_t wCNTR;
    wCNTR = _GetCNTR();
    wCNTR |= CNTR_FSUSP;
    _SetCNTR(wCNTR);
    wCNTR = _GetCNTR();
    wCNTR |= CNTR_LPMODE;
    _SetCNTR(wCNTR);
    Enter_LowPowerMode();
}
//================================
void c_usb::Enter_LowPowerMode(void) {
    usb_device->prevState = usb_device->state;
    usb_device->state = USB_SUSPENDED;
}
//================================
void c_usb::Leave_LowPowerMode(void) {
    DEVICE_INFO *pInfo = &Device_Info;
    (pInfo->Current_Configuration != 0) ? (usb_device->state = USB_CONFIGURED):
                                          (usb_device->state = USB_ATTACHED  );
}


//================================
// Int 值转换 unicode
void c_usb::IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len) {
    uint8_t idx = 0;
  
    for( idx = 0 ; idx < len ; idx ++) {
        if( ((value >> 28)) < 0xA ) {
            pbuf[ 2* idx] = (value >> 28) + '0';
        } else {
          pbuf[2* idx] = (value >> 28) + 'A' - 10; 
        }
        value = value << 4;
        pbuf[ 2* idx + 1] = 0;
    }
}

//===========================
// 得到芯片序列号
void c_usb::Get_SerialNum()
{
//   uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

//   Device_Serial0 = *(__IO uint32_t*)(0x1FFFF7E8);
//   Device_Serial1 = *(__IO uint32_t*)(0x1FFFF7EC);
//   Device_Serial2 = *(__IO uint32_t*)(0x1FFFF7F0);
//   Device_Serial0 += Device_Serial2;
// //   if (Device_Serial0 != 0) {
// //       usb_device->
// //     IntToUnicode (Device_Serial0, &String[2] , 8);
// //     IntToUnicode (Device_Serial1, &String[18], 4);
// //   }
}

//================================
void c_usb::Process_Status_IN (void) {
//     if (usb_device->request == SET_LINE_CODING) 
//         usb_device->request = 0;
}

//================================
// DataSetup
uint8_t *c_usb::getSetLineCoding(uint16_t Length) {
    if (Length == 0) {
        pInformation->Ctrl_Info.Usb_wLength = usb_device->LinecodingSize;
        return NULL;
    }
    return usb_device->Linecoding;
}

//================================
// 端口起动
void c_usb::InitPort(voidFuncPtr fxn) {
    rcc.powerOn(usb_device->clk_id);
    Get_SerialNum();
    pInformation->Current_Configuration = 0;
    _SetCNTR(USB_CNTR_FRES);
    
    wInterrupt_Mask = 0;
    _SetCNTR(wInterrupt_Mask);
    
    _SetISTR(0);
    wInterrupt_Mask  = USB_CNTR_RESETM | USB_CNTR_SUSPM | USB_CNTR_WKUPM;
    _SetCNTR(wInterrupt_Mask);
    
    _SetISTR(0);
    wInterrupt_Mask = ISR_MSK_USB_VCOM;
    _SetCNTR(wInterrupt_Mask);
    
    NvicUsb();
    usb_device->state = USB_UNCONNECTED;
}

//================================
// 端口复位
void c_usb::ResetPort(voidFuncPtr fxn) {
    pInformation->Current_Configuration = 0;
    fxn();
    SetBTABLE(USB_SERIAL_BTABLE_ADDRESS);
    pInformation->Current_Feature = usb_device->ConfigList->Config_Header.bMaxPower;;
    pInformation->Current_Interface = 0;
    SetDeviceAddress(0);
    usb_device->state   = USB_ATTACHED;
    usb_device->callBack->reset();
}

//================================
// data setup
RESULT c_usb::Class_Data_Setup(uint8_t RequestNo) {
    uint8_t *(*CopyRoutine)(uint16_t) = NULL;

    if (Type_Recipient != (CLASS_REQUEST | INTERFACE_RECIPIENT)) 
        return USB_UNSUPPORT;
    
    if ((RequestNo == GET_LINE_CODING) || (RequestNo == SET_LINE_CODING))
        CopyRoutine = getSetLineCoding;
    
    else 
        return USB_UNSUPPORT;

    pInformation->Ctrl_Info.CopyData = CopyRoutine;
    pInformation->Ctrl_Info.Usb_wOffset = 0;
    (*CopyRoutine)(0);
    return USB_SUCCESS;
}

//================================
// no data setup
RESULT c_usb::Class_NoData_Setup(uint8_t RequestNo) {
    if (Type_Recipient != (CLASS_REQUEST | INTERFACE_RECIPIENT)) 
        return USB_UNSUPPORT;
    
    if (RequestNo == SET_COMM_FEATURE) 
        return USB_SUCCESS;
    
    if (RequestNo == SET_CONTROL_LINE_STATE) 
        return USB_SUCCESS;
    
    return USB_UNSUPPORT;
}

//================================
// 获得接口设定
RESULT c_usb::Class_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting) {
  if ((AlternateSetting > 0) || (Interface > 1))
    return USB_UNSUPPORT;
  
  return USB_SUCCESS;
}

//================================
// 描述表索引
uint8_t * c_usb::GetDeviceDescriptor(uint16_t Length) {
  return Standard_GetDescriptorData(Length, usb_device->Device_Descriptor);
}
uint8_t * c_usb::GetConfigDescriptor(uint16_t Length) {
  return Standard_GetDescriptorData(Length, usb_device->Config_Descriptor);
}

uint8_t * c_usb::GetStringDescriptor(uint16_t Length){
  uint8_t wValue0 = pInformation->USBwValue0;
    
  if (wValue0 >= USB_DESCRIPTOR_STRING_N)  
      return NULL;
  
  return Standard_GetDescriptorData(Length, usb_device->String_Descriptor[wValue0]);
}

//================================
// 端口设定
void c_usb::User_SetConfiguration() {
    if (pInformation->Current_Configuration != 0) 
        usb_device->state = USB_CONFIGURED;
}

//================================
// 设定地址
void c_usb::User_SetDeviceAddress (void) {
    usb_device->state = USB_ATTACHED;
}

//================================================================================================
// 中断处理函数
//================================================================================================
uint16  UsbIsrCount = 0;
void c_usb::USB_Istr(void) {
    wIstr = _GetISTR();

    
    
    
    //== 帧首 ==
    if (wIstr & ISTR_SOF & wInterrupt_Mask) {
        usb_device->callBack->sof();
        _SetISTR((uint16_t)CLR_SOF);
        if (!_GetISTR()) 
            return;
    }
    //== 一次正确的传输 ==
    if (wIstr & ISTR_CTR & wInterrupt_Mask) {
        CTR_LP();
        usb_device->callBack->ctr();
        if (!_GetISTR()) 
            return;
    }
    //== 复位请求 ==
    if (wIstr & ISTR_RESET & wInterrupt_Mask)  {
        Device_Property.Reset();
        usb_device->callBack->reset();
        _SetISTR((uint16_t)CLR_RESET);
        if (!_GetISTR()) 
            return;
    }
    //== 分组缓冲溢出 ==
    if (wIstr & ISTR_DOVR & wInterrupt_Mask) {
        _SetISTR((uint16_t)CLR_DOVR);
        usb_device->callBack->dovr();
        if (!_GetISTR()) 
            return;
    }
    //== 错误 ==
    if (wIstr & ISTR_ERR & wInterrupt_Mask) {
        usb_device->callBack->err();
        _SetISTR((uint16_t)CLR_ERR);
        if (!_GetISTR()) 
            return;
    }
    //== 唤醒中断 ==
    if (wIstr & ISTR_WKUP & wInterrupt_Mask) {
        Resume(RESUME_EXTERNAL);
        usb_device->callBack->wkup();
        _SetISTR((uint16_t)CLR_WKUP);
        if (!_GetISTR()) 
            return;
    }
    //== 挂起中断 ==
    if (wIstr & ISTR_SUSP & wInterrupt_Mask) {
        (usb_device->SuspendEnable)? (Suspend()):(Resume(RESUME_LATER));
        usb_device->callBack->susp();
        _SetISTR((uint16_t)CLR_SUSP);
        if (!_GetISTR()) 
            return;
    }
    //== 丢失帧首标示 ==
    if (wIstr & ISTR_ESOF & wInterrupt_Mask) {
        Resume(RESUME_ESOF);
        usb_device->callBack->esof();
        _SetISTR((uint16_t)CLR_ESOF);
        if (!_GetISTR()) 
            return;
    }
} /* USB_Istr */
//================================================================================================
// 中断向量
//================================================================================================
usblib_dev* c_usb::usb_device;
c_usb usb(&usbSerialDev);
#ifdef __cplusplus
extern "C" {
#endif
void __irq_usb_lp_can_rx0() {

    __disable_irq();
    usb.USB_Istr();
    __enable_irq();
}
#ifdef __cplusplus
}
#endif

#endif
//================================================================================================

