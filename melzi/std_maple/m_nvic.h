#ifndef __M_NVIC_H__
#define __M_NVIC_H__

//=====================================================
#include "typeDefine.h"
#include "stm32f10x.h"
//=====================================================
typedef struct nvic_reg_map {
    __io uint32 ISER[8];      /**< Interrupt Set Enable Registers */
    uint32 RESERVED0[24];
    __io uint32 ICER[8];      /**< Interrupt Clear Enable Registers */
    uint32 RESERVED1[24];
    __io uint32 ISPR[8];      /**< Interrupt Set Pending Registers */
    uint32 RESERVED2[24];
    __io uint32 ICPR[8];      /**< Interrupt Clear Pending Registers */
    uint32 RESERVED3[24];
    __io uint32 IABR[8];      /**< Interrupt Active bit Registers */
    uint32 RESERVED4[56];
    __io uint8  IP[240];      /**< Interrupt Priority Registers */
    uint32 RESERVED5[644];
    __io uint32 STIR;         /**< Software Trigger Interrupt Registers */
} nvic_reg_map;

/** NVIC register map base pointer. */
#define _NVIC_BASE                       ((struct nvic_reg_map*)NVIC_BASE)
//
//=====================================================
typedef enum nvic_priority_Group {
	nvic_group0 = 0x700, /*!< 0 bits for pre-emption priority	4 bits for subpriority */            
	nvic_group1 = 0x600, /*!< 1 bits for pre-emption priority	3 bits for subpriority */                                                       
	nvic_group2 = 0x500, /*!< 2 bits for pre-emption priority	2 bits for subpriority */
	nvic_group3 = 0x400, /*!< 3 bits for pre-emption priority	1 bits for subpriority */                                              
	nvic_group4 = 0x300  /*!< 4 bits for pre-emption priority 0 bits for subpriority */
}nvic_priority_Group;                                        
//
//=====================================================
class c_nvic {
public:
    void globalEnable ();
    void globalDisable();
    void irqEnable (IRQn irq_num, uint8 mPriority, uint8 sPriority);
    void irqEnable (IRQn irq_num);
    void irqDisable(IRQn irq_num);
    void priorityGroup(nvic_priority_Group group);
};
//
//=====================================================
extern c_nvic nvic;
#endif //__M_NVIC_H__

