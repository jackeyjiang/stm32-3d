//===============================================
#include "m_include.h"
//===============================================
// 位操作
//===============================================
inline volatile uint32* bb_sramp(volatile void *address, uint32 bit) {
    return __bb_addr(address, bit, BB_SRAM_BASE, BB_SRAM_REF);
}
inline uint8 bb_sram_get_bit(volatile void *address, uint32 bit) {
    return *bb_sramp(address, bit);
}
inline void bb_sram_set_bit(volatile void *address, uint32 bit, uint8 val) {
    *bb_sramp(address, bit) = val;
}
volatile uint32* bb_perip(volatile void *address, uint32 bit) {
    return __bb_addr(address, bit, BB_PERI_BASE, BB_PERI_REF);
}
inline uint8 bb_peri_get_bit(volatile void *address, uint32 bit) {
    return *bb_perip(address, bit);
}
inline void bb_peri_set_bit(volatile void *address, uint32 bit, uint8 val) {
    *bb_perip(address, bit) = val;
}
inline volatile uint32* __bb_addr(volatile void *address, uint32 bit, uint32 bb_base, uint32 bb_ref) {                                                                                
    return (volatile uint32*)(bb_base + ((uint32)address - bb_ref) * 32 + bit * 4);
}
//===============================================
//
//===============================================
void voidFunc(void){}   
void memCopy(char *t, char *s, int length) {
    while (length--)
        *t++ = *s++;
}

uint32 sysTimer = 0;
//===============================================
