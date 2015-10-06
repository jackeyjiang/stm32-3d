/*======================================================================  
maker  :jiaxing.shen
date   :2014.12.10
email  :55954781@qq.com
======================================================================*/
#ifndef __M_EEP_H__
#define __M_EEP_H__
//======================================================================
#include "typeDefine.h"
#include "stdint.h"
//======================================================================
// Flash Keys
#define RDPRT_KEY       0x5AA5
#define FLASH_KEY1      0x45670123
#define FLASH_KEY2      0xCDEF89AB
//
// Flash Control Register definitions
#define FLASH_PG        0x00000001
#define FLASH_PER       0x00000002
#define FLASH_MER       0x00000004
#define FLASH_OPTPG     0x00000010
#define FLASH_OPTER     0x00000020
#define FLASH_STRT      0x00000040
#define FLASH_LOCK      0x00000080
#define FLASH_OPTWRE    0x00000100
//
// Flash Status Register definitions
#define FLASH_BSY       0x00000001
#define FLASH_PGERR     0x00000004
#define FLASH_WRPRTERR  0x00000010
#define FLASH_EOP       0x00000020
//
// FLASH BANK size
#define BANK1_SIZE      0x00080000      // Bank1 Size = 512kB
//======================================================================
class c_eep {
public:
	void wirte (uint8 *source, uint32 tarAddr, uint16 len);
private:
    int ProgramPage (unsigned long adr, unsigned long sz, unsigned char *buf);
    int EraseSector (unsigned long adr);
    int Init        ();
    int UnInit      ();
};
extern c_eep   eep;
//======================================================================
#endif 
//======================================================================

