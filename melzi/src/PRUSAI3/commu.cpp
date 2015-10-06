//======================================================================
#include "m_include.h"
#include "commu.h"
#include "m_ringBuffer.h"
//======================================================================
os_mbx_declare (mbx_commu,COMMU_CMD_CUN);                            /* Declare an RTX mailbox   */
_declare_box   (box_commu,sizeof(ts_commu_buf),COMMU_CMD_CUN+4);     /* Dynamic memory pool      */
class c_commu   commu;
OS_MUT          mutPushCommand;
//
//===========================================================
//== G代码接收任务 ==
__task void commuTsk()   {
    //================================
    // pushCommand 资源锁
    os_mut_init(mutPushCommand);
    //================================
    //== 邮箱初始化
    _init_box  (box_commu, sizeof(box_commu),  sizeof(ts_commu_buf));        
    os_mbx_init(mbx_commu, sizeof(mbx_commu));
    //
    //================================
    //== 定义第一个邮箱
    commu.pMbx = (ts_commu_buf *)_alloc_box(box_commu);
    commu.taskRunEnable = true;
    //
    //================================
    //== 等待任务启动允许
    while (taskRunEnable() == false) os_dly_wait(1);
    //
    //================================
    //== 任务循环
    while (1) {
        commu.codeLoop();
}
}
//
//===========================================================
// 构造函数
//===========================================================
c_commu::c_commu(void) {
    this->waitingForResend = -1;
}
//
//===========================================================
// 解析 浮点数
//===========================================================
float c_commu::parseFloatValue(char *s, uint16 *params2) {
    char *endPtr;
    float f = (strtod(s, &endPtr));
    if(s == endPtr) *params2 |= 0x8000;
        return f;
}
//
//===========================================================
// 解析 长整型数
//===========================================================
long c_commu::parseLongValue(char *s, uint16 *params2) {
        char *endPtr;
        long l = (strtol(s, &endPtr, 10));
        if(s == endPtr) *params2 |= 0x8000;
        return l;
}
//==============================================================
// 根据位标示，解析所需要接收的字节长度
//==============================================================
uint8_t c_commu::BinarySize(char *ptr) {
    uint8_t s = 4; 
    TU_BinaryBitfield bitfield;
    bitfield.all = *(uint16_t*)ptr;
    if(bitfield.bits.N_V2_I) s+=2;
    if(bitfield.bits.X) s+=4;
    if(bitfield.bits.Y) s+=4;
    if(bitfield.bits.Z) s+=4;
    if(bitfield.bits.E) s+=4;
    if(bitfield.bits.F) s+=4;
    if(bitfield.bits.T) s+=1;
    if(bitfield.bits.S) s+=4;
    if(bitfield.bits.P) s+=4;
    if(bitfield.bits.V2) {  // Version 2 or later
        s+=2;               // for bitfield 2
        uint16_t bitfield2 = *(uint16_t*)(ptr+2);
        if(bitfield.bits.M_V2_J) s+=2;
        if(bitfield.bits.G_V2_R) s+=2;
        if(bitfield2 & 1) s+= 4;
        if(bitfield2 & 2) s+= 4;
        if(bitfield2 & 4) s+= 4;
        if(bitfield.bits.TEXT) s+=(80<((uint8_t)ptr[4]+1))? (80) : ((uint8_t)ptr[4]+1);
    } else {
        if(bitfield.bits.M_V2_J) s+=1;
        if(bitfield.bits.G_V2_R) s+=1;
        if(bitfield.bits.TEXT)   s+=16;
    }
    return s;
}
//
//=================================================================
// 二进制数据接收解析
//=================================================================
bool c_commu::parseBinary(uint8 *sbuf, ts_commu_buf *tbuf,  bool fromSerial) {
    unsigned int sum1=0,sum2=0; // for fletcher-16 checksum   
    uint8_t *p = sbuf;
    uint8_t len = binaryRxSize-2;
//
//----------------------------------------------
//  1. 判断校验和 
    while (len) {
        uint8_t tlen = len > 21 ? 21 : len;
        len -= tlen;
        do {
            sum1 += *p++;
            if(sum1>=255) sum1-=255;
            sum2 += sum1;
            if(sum2>=255) sum2-=255;
        } while (--tlen);
    }
    sum1 -= *p++;
    sum2 -= *p;
    if(sum1 | sum2) {
        serialCommu.println("Wrong checksum");
        return false;
    }
//
//----------------------------------------------
//  数据拆分解析
    p = sbuf;
    tbuf->params.all = *(unsigned int *)p;
    p+=2;
    uint8_t textlen=16;
    if(tbuf->params.bits.V2) {
        tbuf->params2 = *(unsigned int *)p;
        p+=2;
        if(tbuf->params.bits.TEXT) textlen = *p++;
    } else tbuf->params2 = 0;
    if(tbuf->params.bits.N_V2_I) {
        tbuf->N =*(uint16_t *)p;
        p+=2;
    }
    if(tbuf->params.bits.V2) {   // Read G,M as 16 bit value
        if(tbuf->params.bits.M_V2_J) {tbuf->M = *(uint16_t *)p;     p+=2;}
        if(tbuf->params.bits.G_V2_R) {tbuf->G = *(uint16_t *)p;     p+=2;}
    } else {
        if(tbuf->params.bits.M_V2_J) {tbuf->M = *p++;}
        if(tbuf->params.bits.G_V2_R) {tbuf->G = *p++;}
    }
    if(tbuf->params.bits.X)       {tbuf->Axis[X_AXIS]  = *(float *)p;   p+=4;}
    if(tbuf->params.bits.Y)       {tbuf->Axis[Y_AXIS]  = *(float *)p;   p+=4;}
    if(tbuf->params.bits.Z)       {tbuf->Axis[Z_AXIS]  = *(float *)p;   p+=4;}
    if(tbuf->params.bits.E)       {tbuf->Axis[E1_AXIS] = *(float *)p;   p+=4;}
    if(tbuf->params.bits.F)       {tbuf->F = *(float *)p;   p+=4;}
    if(tbuf->params.bits.T)       {tbuf->T = *p++;    }
    if(tbuf->params.bits.S)       {tbuf->S = *(int32_t*)p;  p+=4;}
    if(tbuf->params.bits.P)       {tbuf->P = *(int32_t*)p;  p+=4;}
    if(tbuf->params.bits.N_V2_I)  {tbuf->I = *(float *)p;   p+=4;}
    if(tbuf->params.bits.M_V2_J)  {tbuf->J = *(float *)p;   p+=4;}
    if(tbuf->params.bits.G_V2_R)  {tbuf->R = *(float *)p;   p+=4;}
    if(tbuf->params.bits.TEXT) {                  // set text pointer to string
        text = (char*)p;
        text[textlen] = 0;                      // Terminate string overwriting checksum
    }
    formatErrors = 0;
    return true;
//
//----------------------------------------------
}
//
//=================================================================
// ASCII 数据接收解析
// 返回 1 正常
//      0 错误
//=================================================================
bool   c_commu::parseAscii (char *sbuf, ts_commu_buf *tbuf,  bool fromSerial) {
    char *pos;
    
    tbuf->params.all = tbuf->params2 = 0;
    if((pos = strchr(sbuf,'N'))!=0)  {  // Line number detected
        tbuf->params.bits.N_V2_I=1;
        tbuf->N = parseLongValue(++pos, &tbuf->params2);
    }
    if((pos = strchr(sbuf,'M'))!=0) {   // M command
        tbuf->M = parseLongValue(++pos, &tbuf->params2) & 0xffff;
        tbuf->params.bits.M_V2_J=1;
        if(tbuf->M > 255) tbuf->params.bits.V2=1;
    }
    if(tbuf->params.bits.M_V2_J && (tbuf->M == 23 || tbuf->M == 28 || tbuf->M == 29 || tbuf->M == 30 || tbuf->M == 32 || tbuf->M == 117)) {
        // after M command we got a filename for sd card management
        char *sp = sbuf;
        while(*sp!='M') sp++; // Search M command
        while(*sp!=' ') sp++; // search next whitespace
        while(*sp==' ') sp++; // skip leading whitespaces
        text = sp;
        while(*sp) {
            if(tbuf->M != 117 && (*sp==' ' || *sp=='*')) break; // end of filename reached
            sp++;
        }
        *sp = 0; // Removes checksum, but we don't care. Could also be part of the string.
        tbuf->params.bits.TEXT = 1;
    } else {
        if((pos = strchr(sbuf,'G'))!=0) {   // G command
            tbuf->G = parseLongValue(++pos, &tbuf->params2) & 0xffff;
            tbuf->params.bits.G_V2_R=1;
            if(tbuf->G > 255) tbuf->params.bits.V2=1;
        }
        if((pos = strchr(sbuf,'X'))!=0) {
            tbuf->Axis[X_AXIS] = parseFloatValue(++pos, &tbuf->params2);
            tbuf->params.bits.X=1;
        }
        if((pos = strchr(sbuf,'Y'))!=0) {
            tbuf->Axis[Y_AXIS] = parseFloatValue(++pos, &tbuf->params2);
            tbuf->params.bits.Y=1;
        }
        if((pos = strchr(sbuf,'Z'))!=0) {
            tbuf->Axis[Z_AXIS] = parseFloatValue(++pos, &tbuf->params2);
            tbuf->params.bits.Z=1;
        }
        if((pos = strchr(sbuf,'E'))!=0) {
            tbuf->Axis[E1_AXIS] = parseFloatValue(++pos, &tbuf->params2);
            tbuf->params.bits.E=1;
        }
        if((pos = strchr(sbuf,'F'))!=0) {
            tbuf->F = parseFloatValue(++pos, &tbuf->params2);
            tbuf->params.bits.F=1;
        }
        if((pos = strchr(sbuf,'C'))!=0) {
            tbuf->C = parseFloatValue(++pos, &tbuf->params2);
            tbuf->params.bits.F=1;
        }
        if((pos = strchr(sbuf,'T'))!=0) {  // M command
            tbuf->T = parseLongValue(++pos, &tbuf->params2) & 0xff;
            tbuf->params.bits.T=1;
        }
        if((pos = strchr(sbuf,'S'))!=0) {  // M command
            tbuf->S = parseLongValue(++pos, &tbuf->params2);
            tbuf->params.bits.S=1;
        }
        if((pos = strchr(sbuf,'P'))!=0) {  // M command
            tbuf->P = parseLongValue(++pos, &tbuf->params2);
            tbuf->params.bits.P=1;
        }
        if((pos = strchr(sbuf,'I'))!=0) {
            tbuf->I = parseFloatValue(++pos, &tbuf->params2);
            tbuf->params2 |= 1;
            tbuf->params.bits.N_V2_I=1; // Needs V2 for saving
        }
        if((pos = strchr(sbuf,'J'))!=0) {
            tbuf->J = parseFloatValue(++pos, &tbuf->params2);
            tbuf->params2 |= 2;
            tbuf->params.bits.M_V2_J=1; // Needs V2 for saving
        }
        if((pos = strchr(sbuf,'R'))!=0) {
            tbuf->R = parseFloatValue(++pos, &tbuf->params2);
            tbuf->params2 |= 4;
            tbuf->params.bits.G_V2_R=1; // Needs V2 for saving
        }
    }
    if((pos = strchr(sbuf,'*'))!=0) {  // checksum
        uint8_t checksum_given = parseLongValue(pos+1, &tbuf->params2);
        uint8_t checksum = 0;
        while(sbuf!=pos) checksum ^= *sbuf++;
        if(checksum!=checksum_given) {
            serialCommu.println("Wrong checksum");
            return false; // mismatch
        }
    }
    if((tbuf->params2 & 0x8000) || (tbuf->params.all & 0x206)==0) {   // Must contain G, M or T command and parameter need to have variables!
        formatErrors++;
        serialCommu.println("Format error");
        if(formatErrors<3) return false;
    }
    else formatErrors = 0;
    return true;   
}
//==============================================================
// 判断解析到的数据是否要推入命令堆栈， 如果错误则请求重新发送
//==============================================================
ts_commu_buf * c_commu::checkAndPushCommand(ts_commu_buf *sbuf) {
    os_mut_wait(mutPushCommand, 0xffff);
    //== M 执行 =======
    if(sbuf->params.bits.M_V2_J) {
        switch (sbuf->M) {
            case 110:  {waitingForResend = -1;
                        lastLineNumber = sbuf->N;
                        serialCommu.println("ok");
                        os_mut_release(mutPushCommand);
                        return sbuf;
                       }
            case 17 :
            case 80 :      
            case 112:  {gcode.stop();
                        break;
                       }
            default:    break;
            }
    }
    //== N 行号 ========
    if((((lastLineNumber+1)&0xffff) != sbuf->N) && sbuf->params.bits.N_V2_I) {
        if(waitingForResend<0) {    // after a resend, we have to skip the garbage in buffers, no message for this
            serialCommu.print("Error:expected line ");
            serialCommu.println((uint16_t)lastLineNumber+1);
            serialCommu.print(" got ");
            serialCommu.println((uint16_t)sbuf->N);
            requestResend();        // Line missing, force resend
        } else {
            RecivingCount = 0;
            serialCommu.print("skip ");
            serialCommu.println((uint16_t)sbuf->N);
            serialCommu.println("ok");
        }
        waitingForResend = true;
    } else {
        waitingForResend = -1;
        sbuf = pushCommand(sbuf);
        wasLastRxAsBinary = isRxAsBinary;
    }
    os_mut_release(mutPushCommand);
    return sbuf;
}
//===========================================================
// 数据压入
//===========================================================
ts_commu_buf * c_commu::pushCommand(ts_commu_buf *sbuf) {
    //
    //-------------------------------------------
    //1. 带文本命令直接执行，减少内存使用
    uint8 done = false, answer = true;
    if (sbuf->params.bits.M_V2_J) {
        switch (sbuf->M) {
            case (105):     gcode.M105();       done = true;    break;
            case (23) :     gcode.M23(text);    done = true;    break;
            case (28) :     gcode.M28(text);    done = true;    break;
            case (29) :     gcode.M29();        done = true;    break;
            case (30) :     gcode.M30(text);    done = true;    break;
            case (80) :     gcode.M80();        done = true;    break;
        }
    }
    //
    //-------------------------------------------
    //2. SD 接收文件
    if (sdReader.saving && done==false) {
        sdReader.writeCmd((char *)RecivingBuf);
        done = true;
    } else if (sbuf->params.bits.M_V2_J && sbuf->M==109) {
        lastLineNumber = sbuf->N;
        answer = false;
    }
    //
    //-------------------------------------------
    //3. 回令
    if (sbuf->params.bits.N_V2_I && answer == true) {
        lastLineNumber = sbuf->N;
        serialCommu.print("ok ");
        serialCommu.println((uint16_t)sbuf->N);
    }
    //
    //-------------------------------------------
    //3. 发送邮箱
    if (done) {
        return sbuf;
    } else {
        os_mbx_send(mbx_commu, sbuf, 0xffff);
        return getMbxBuf();
    }
}
//===========================================================
// 获得Mbx内存
//===========================================================
ts_commu_buf * c_commu::getMbxBuf(void) {
    ts_commu_buf *o;
    o = (ts_commu_buf *)_calloc_box(box_commu);
    while (o == NULL) {
        o = (ts_commu_buf *)_calloc_box(box_commu);
        os_dly_wait(1);
    }
    return o;
}
//
//===============================================================
// 清空MBX
//===============================================================
void c_commu::flushMbx(void) {
    ts_commu_buf *pNull;
    while (os_mbx_wait(mbx_commu, (void **)&pNull, 5) != OS_R_TMO);
}
//
//===========================================================
// 数据推出
//===========================================================
void  c_commu::getGcodeLock(ts_commu_buf *loadBuf) {
    ts_commu_buf *rxMbx;
    
    os_mbx_wait(mbx_commu, (void **)&rxMbx, 0xffff);
    memCopy((char *)loadBuf, (char*)rxMbx, sizeof(ts_commu_buf));
    _free_box(box_commu, rxMbx);
}
//
//===========================================================
// 请求数据的重发
//===========================================================
void c_commu::requestResend(void) {
    RecivingCount=0;
    serialCommu.println();
    serialCommu.print("Resend:");
    serialCommu.println(lastLineNumber+1);
}

//===========================================================
// repetier 主循环，判断接收数据 打包发送 class step
//===========================================================
void c_commu::codeLoop(void)
{
    static uint32_t requestTimer = os_time_get();
    static uint32_t waitTimer = os_time_get();  
// 
//----------------------------------------------------
//1. 没有数据接收 
    if (os_sem_wait(serialCommu.semRxReady, 200) == OS_R_TMO) {
        if (waitingForResend>=0 || RecivingCount>0) {
            serialCommu.flush();
            requestResend();
        } else if ((os_time_get()-waitTimer)>10000) {
            waitTimer = os_time_get();
            if (stepMbxRemain==0) {
                serialCommu.flush();
//                 serialCommu.println("wait");
            }  
        }
        return;
    }
    requestTimer    = os_time_get();
    waitTimer       = os_time_get();
// 
//----------------------------------------------------
//2. 接收到数据
    while (RecivingCount<COMMU_BUFFER_SIZE && serialCommu.available()) {
        RecivingBuf[RecivingCount++] = serialCommu.read();
        if (RecivingCount==1) {
            if (!RecivingBuf[0]) {
                RecivingCount = 0;
                continue;
            }
            pMbx->params.all = RecivingBuf[0];
            isRxAsBinary     = pMbx->params.bits.Binary;
        }
        //== 2进制接收 =========
        if (isRxAsBinary) {
            if (RecivingCount < 2) {
                binaryRxSize = 0;
                continue;
            }
            if (RecivingCount==4 || RecivingCount==5) {
                binaryRxSize=BinarySize((char *)RecivingBuf);
            }
            if (RecivingCount==binaryRxSize) {
                if (parseBinary(RecivingBuf, pMbx, true)) pMbx = checkAndPushCommand(pMbx);
                else                                      requestResend();
                RecivingCount=0;
                continue;
            }
        //== ASCII 接收 =========
        } else {    // Ascii command
            char ch = RecivingBuf[RecivingCount-1];
            if(ch == 0 || ch == '\n' || ch == '\r' || (!commentDetected && ch == ':')) { // complete line read
                RecivingBuf[RecivingCount-1]=0;
                commentDetected = false;
                if(RecivingCount==1) {                  // empty line ignore
                    RecivingCount = 0;
                    continue;
                }
                if(parseAscii((char *)RecivingBuf, pMbx,true))   pMbx = checkAndPushCommand(pMbx);
                else                                             requestResend(); 
                RecivingCount = 0;
                continue;
            } else {
                if(ch == ';')       commentDetected = true;   // ignore new data until lineend
                if(commentDetected) RecivingCount--;
            }
        }
        if(RecivingCount == COMMU_BUFFER_SIZE) {
            requestResend();
            return;
        }  
    }
}
//===========================================================



