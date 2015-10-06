//====================================================================
#ifndef __SD_H__
#define __SD_H__
#include "stdio.h"
#include "typeDefine.h"
#include "commu.h"
//====================================================================
//
class c_sdReader {
public:
    void    init (void);  // 初始化， 调用任何程序前先调用
    void    uinit(void);  // 拔出 SD  卡
    void    ls(void);
    void    open         (const char*filename, const char* mode);
    void    close();
    void    write        (const char *fn);
    void    removeFile   (char *fn); 
    void    writeCmdEnd  ();
    void    writeCmd     (char *buf);
    void    sdPrint      (void);
    void    setStartPrint(bool status);
    uint8   getPercentDone();
    void    getStatus();
    void    setSaving    (bool status) {saving = status;}
    void    checkAutoStart(bool force);
public:
    bool    cardOk;
    int     cardErrCode;
    bool    printing;
    FILE   *pFile;
    FINFO   info;
    bool    fileOpen;
    bool    saving;
    uint32  sdPos;
    ts_commu_buf  *pSdBuf;
    bool    taskRunEnable;
private:
    uint8   getBuf[COMMU_BUFFER_SIZE];
};

extern c_sdReader  sdReader;
extern __task void sdReaderTask(void);
//====================================================================
#endif




