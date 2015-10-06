/*****************************************************************************/
/*********************** Bulk-Only Transfer State machine ********************/
/*****************************************************************************/
#define BOT_IDLE                      0       /* Idle state */
#define BOT_DATA_OUT                  1       /* Data Out state */
#define BOT_DATA_IN                   2       /* Data In state */
#define BOT_DATA_IN_LAST              3       /* Last Data In Last */
#define BOT_CSW_Send                  4       /* Command Status Wrapper */
#define BOT_ERROR                     5       /* error state */

#define BOT_CBW_SIGNATURE             0x43425355
#define BOT_CSW_SIGNATURE             0x53425355
#define BOT_CBW_PACKET_LENGTH         31

#define CSW_DATA_LENGTH               0x000D

/* CSW Status Definitions */
#define CSW_CMD_PASSED                0x00
#define CSW_CMD_FAILED                0x01
#define CSW_PHASE_ERROR               0x02

#define SEND_CSW_DISABLE              0
#define SEND_CSW_ENABLE               1

#define DIR_IN                        0
#define DIR_OUT                       1
#define BOTH_DIR                      2


/* Bulk-only Command Block Wrapper */
typedef struct _Bulk_Only_CBW {
  uint32_t dSignature;
  uint32_t dTag;
  uint32_t dDataLength;
  uint8_t  bmFlags;
  uint8_t  bLUN;
  uint8_t  bCBLength;
  uint8_t  CB[16];
}Bulk_Only_CBW;
/* Bulk-only Command Status Wrapper */
typedef struct _Bulk_Only_CSW {
  uint32_t dSignature;
  uint32_t dTag;
  uint32_t dDataResidue;
  uint8_t  bStatus;
}Bulk_Only_CSW;
//==================================================================================
class c_massStorage {
public:
    c_massStorage(sd_dev *sdDev, usblib_dev  *usbDev);
    bool    begin();
    void    Mass_Storage_In (void);
    void    setSdDev (sd_dev      *sdDev )  {sd_device  = sdDev; }
    void    setUsbDev(usblib_dev  *usbDev)  {usb_device = usbDev;}
private:
    uint8_t     Bot_State;
    uint32_t    SCSI_LBA;
    uint32_t    SCSI_BlkLen;

    bool        status;
    c_sd        *pSd;
    c_usb       *pUsb;
    sd_dev      *sd_device;
    usblib_dev  *usb_device;
};
//=======================================================
// scsi 协议集
//=======================================================
class c_scsi {
    void    SCSI_Inquiry_Cmd        (uint8_t lun);
    void    Transfer_Data_Request   (uint8_t* Data_Pointer, uint16_t Data_Len);
    
    uint8_t         Page00_Inquiry_Data  [5 ];
    uint8_t         Standard_Inquiry_Data[36];
    uint8_t         STANDARD_INQUIRY_DATA_LEN;
    uint8_t         Bot_State;
    Bulk_Only_CBW   CBW;
    Bulk_Only_CSW   CSW;
};
