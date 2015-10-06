/*======================================================================  
maker  :jiaxing.shen
date   :2014.12.10
email  :55954781@qq.com
======================================================================*/
#include "m_include.h"
#include "m_eep.h"

//
//======================================================================
// 写入
//======================================================================
void c_eep::wirte(uint8 *source, uint32 tarAddr, uint16 len) {
//
//------------------------------------
// 0. 关闭系统中断
    nvic.globalDisable();
//
//------------------------------------
// 1. 开启内部高速时钟
    RCC->CR |= ((uint32_t)RCC_CR_HSION);
    while((RCC->CR & RCC_CR_HSIRDY) == 0);
//
//------------------------------------
// 2. 解锁
	Init();
//
//------------------------------------
// 3. 擦除并写入数据
    EraseSector(tarAddr);
    ProgramPage(tarAddr, len, source);
//
//------------------------------------
// 4. 锁定
	UnInit();
//
//------------------------------------
// 5. 关闭内部高速时钟
    RCC->CR &= ~((uint32_t)RCC_CR_HSION);
    while(RCC->CR & RCC_CR_HSIRDY);
//
//------------------------------------
// 6. 开启中断
    nvic.globalEnable();
}
//
//======================================================================
// 初始化EEP 功能
//======================================================================
/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */
int c_eep::Init () {
    // Unlock Flash    
    FLASH->KEYR  = FLASH_KEY1;
    FLASH->KEYR  = FLASH_KEY2;
    // Test if IWDG is running (IWDG in HW mode)
    if ((FLASH->OBR & 0x04) == 0x00) {              // Set IWDG time out to ~32.768 second
        IWDG->KR  = 0x5555;                         // Enable write access to IWDG_PR and IWDG_RLR     
        IWDG->PR  = 0x06;                           // Set prescaler to 256  
        IWDG->RLR = 4095;                           // Set reload value to 4095
    }
  return (0);
}
//
//======================================================================
// 结束解锁
//======================================================================
/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */
int c_eep::UnInit () {
  FLASH->CR  |=  FLASH_LOCK;
  return (0);
}
//
//======================================================================
// 扇区擦除
//======================================================================
/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */
int c_eep::EraseSector (unsigned long adr) {
    while (FLASH->SR  & FLASH_BSY) {
      IWDG->KR = 0xAAAA;                        // Reload IWDG
    }
    FLASH->CR  |=  FLASH_PER;                   // Page Erase Enabled 
    FLASH->AR   =  adr;                         // Page Address
    FLASH->CR  |=  FLASH_STRT;                  // Start Erase
    while (FLASH->SR  & FLASH_BSY) {
      IWDG->KR = 0xAAAA;                        // Reload IWDG
    }
    FLASH->CR  &= ~FLASH_PER;                   // Page Erase Disabled 
  return (0);                                   // Done
}
//
//======================================================================
// 页编程
//======================================================================
/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
*/
int c_eep::ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf) {
    sz = (sz + 1) & ~1;                             // Adjust size for Half Words
    while (sz) {
        FLASH->CR  |=  FLASH_PG;                    // Programming Enabled
        *(vu16 *)adr = *((unsigned short *)buf);    // Program Half Word
        while (FLASH->SR  & FLASH_BSY);
        FLASH->CR  &= ~FLASH_PG;                    // Programming Disabled
      // Check for Errors
      if (FLASH->SR  & (FLASH_PGERR | FLASH_WRPRTERR)) {
        FLASH->SR  |= FLASH_PGERR | FLASH_WRPRTERR;
        return (1);                                 // Failed
      }
      // Go to next Half Word
      adr += 2;
      buf += 2;
      sz  -= 2;
    }
  return (0);                                       // Done
}
//
//======================================================================
c_eep   eep;
//
//======================================================================





