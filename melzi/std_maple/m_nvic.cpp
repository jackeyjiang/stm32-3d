//===============================================
#include "m_include.h"
#include "m_nvic.h"
//===============================================
// 全局中断开启
//===============================================
void c_nvic::globalEnable() {
    asm volatile("cpsie i");
}

//===============================================
// 全局中断关闭
//===============================================
void c_nvic::globalDisable() {
    asm volatile("cpsid i");
}

//===============================================
// 开启中断
//===============================================
void c_nvic::irqEnable(IRQn irq_num, uint8 mPriority, uint8 sPriority) {
		uint32 tmpPriority = 0, tmpPre = 0, tmpSub = 0;
	
    if (irq_num < 0) {
        return;
    }
		tmpPriority = (0x700-((SCB->AIRCR & (uint32)0x700)>>8));
		tmpPre = 4-tmpPriority;
		tmpSub = tmpSub>>tmpPriority;
		tmpPriority  = mPriority<<tmpPre;
		tmpPriority |= sPriority<<tmpSub;
		tmpPriority = tmpPriority<<4;
		NVIC->IP[irq_num] = tmpPriority;
    NVIC->ISER[((uint32_t)(irq_num) >> 5)] = (1 << ((uint32_t)(irq_num) & 0x1F));
}

//===============================================
// 开启中断
//===============================================
void c_nvic::irqEnable(IRQn irq_num) {
    if (irq_num < 0) {
        return;
    }
    NVIC->ISER[((uint32_t)(irq_num) >> 5)] = (1 << ((uint32_t)(irq_num) & 0x1F));
}

//===============================================
// 开启中断
//===============================================
void c_nvic::priorityGroup(nvic_priority_Group group) {
	SCB->AIRCR = 0x05FA0000 | group;
}
//
//===============================================
// 关闭中断
//===============================================
void c_nvic::irqDisable(IRQn irq_num) {
    if (irq_num < 0) {
        return;
    }
    NVIC->ICER[((uint32_t)(irq_num) >> 5)] = (1 << ((uint32_t)(irq_num) & 0x1F));
}

c_nvic nvic;
