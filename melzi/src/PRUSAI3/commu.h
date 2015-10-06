//===========================================================
#ifndef __GET_repetier_H__
#define __GET_repetier_H__
//===========================================================
#include "m_ringBuffer.h"
#include "RTL.h"
//===========================================================
#define COMMU_BUFFER_SIZE       64       // 解析协议BUF
#define COMMU_CMD_CUN           100      // 命令缓存个数
extern OS_MBX  commuMbx;
//
//===========================================================
// 二进制协议头 位定义
//===========================================================
typedef struct {
    uint16 N_V2_I   :1;   //BIT 0
    uint16 M_V2_J   :1;   //BIT 1
    uint16 G_V2_R   :1;   //BIT 2
    uint16 X        :1;   //BIT 3
    uint16 Y        :1;   //BIT 4
    uint16 Z        :1;   //BIT 5
    uint16 E        :1;   //BIT 6
    uint16 Binary   :1;   //BIT 7
    uint16 F        :1;   //BIT 8
    uint16 T        :1;   //BIT 9
    uint16 S        :1;   //BIT 10
    uint16 P        :1;   //BIT 11
    uint16 V2       :1;   //BIT 12
    uint16 EXT      :1;   //BIT 13
    uint16 INT      :1;   //BIT 14
    uint16 TEXT     :1;   //BIT 15
}TS_BinaryBitfieldBits;
typedef union {
    TS_BinaryBitfieldBits   bits;
    uint16                  all;
}TU_BinaryBitfield;
//
//===========================================================
// 数据缓存结构
//===========================================================
typedef struct {
    TU_BinaryBitfield   params;
    uint16              params2;
    uint16  N; // Line number
    uint16  M;
    uint16  G;
    float   Axis[MAX_AXIS];
    float   F;
    uint8   T;
    long    S;
    long    P;
    float   I;
    float   J;
    float   R;
    float   C;
}ts_commu_buf;
//
//===========================================================
class c_commu {   // 52 uint8s per command needed
public:
//----------------------------------------------------
//  接口函数
    void  getGcodeLock(ts_commu_buf *);     // 带锁的gcode读取
//----------------------------------------------------
//  函数
    void   codeLoop();                      // 任务循环使用 自身task 使用
    c_commu(void);
    bool           parseAscii (char    *sbuf, ts_commu_buf *tbuf,  bool fromSerial);
    bool           parseBinary(uint8   *sbuf, ts_commu_buf *tbuf,  bool fromSerial);
    ts_commu_buf  *checkAndPushCommand  (ts_commu_buf *sbuf);
    ts_commu_buf  *pushCommand          (ts_commu_buf *sbuf);
    ts_commu_buf  *pMbx;
    ts_commu_buf  *getMbxBuf(void);         // 获得内存
    void           flushMbx (void);
    bool           taskRunEnable;
private:
//
//----------------------------------------------------
//  函数
    uint8  BinarySize (char *ptr);
    void   requestResend();
    inline float parseFloatValue(char *s, uint16 *params2);
    inline long  parseLongValue (char *s, uint16 *params2);
//
//----------------------------------------------------
//  变量
    int8   waitingForResend;                    ///< Waiting for line to be resend. -1 = no wait.
    uint8  RecivingCount;                       ///< Writing position in repetier_transbuffer.
    uint8  RecivingBuf[COMMU_BUFFER_SIZE];
    bool   wasLastRxAsBinary;                   /// 上次接收的是2进制
    bool   isRxAsBinary;                        /// 这次是按2进制发送
    bool   commentDetected;                     /// 如果检测到命令
    uint8  binaryRxSize;                        /// 需要接收的数据长度
    uint8  stepMbxRemain;                       /// 发送给step 邮箱的剩余个数
    uint16 lastLineNumber;                      /// 上次行数
    uint8  formatErrors;                        /// 格式错误
    char   *text;
};
//==============================================
extern class    c_commu     commu;
extern __task   void commuTsk();
#endif //__GET_repetier_H__

