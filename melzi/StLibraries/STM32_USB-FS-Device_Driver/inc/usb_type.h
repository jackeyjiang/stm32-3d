/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : usb_type.h
* Author             : MCD Application Team
* Version            : V3.3.0
* Date               : 21-March-2011
* Description        : Type definitions used by the USB Library
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_TYPE_H
#define __USB_TYPE_H
#ifdef __cplusplus
 extern "C" {
#endif
//#include "m_usb.h"

#define IMR_MSK (CNTR_CTRM  | CNTR_SOFM  | CNTR_RESETM )

#ifndef NULL
#define NULL ((void *)0)
#endif
#define FALSE   0
#define TRUE    !FALSE

#ifdef __cplusplus
}
#endif
#endif /* __USB_TYPE_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
