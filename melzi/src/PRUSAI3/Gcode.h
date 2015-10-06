//-------------------------------------------------------------------
//
//-------------------------------------------------------------------
#ifndef __GCODE_H__
#define __GCODE_H__
#include "typeDefine.h"
#include "sysConf.h"
#include "temperature.h"
#include "sysConf.h"
#include "commu.h"
#include "sdReader.h"
#include "m_usbSerial.h"
#include "m_Print.h"
#include "stepMoto.h"
typedef enum {
    egcode_status_idle = 0,
    egcode_status_powerOn,
    egcode_status_heat,
    egcode_status_run,
}te_gcode_status;
//-------------------------------------------------------------------
// delta 参数结构
typedef struct {
    float tower1X;
    float tower1Y;
    float tower2X;
    float tower2Y;
    float tower3X;
    float tower3Y;
    float diagonalRod2;
    float panRadius2;
    float deltaRadius;
    float second2segments;
    float autoLevX;
    float autoLevY;
}ts_delta_para;
//
//-------------------------------------------------------------------
//
class c_gcode {
public:
    c_gcode();
    OS_MUT  mut_gcode;
    void loop();
    void            setCurPos(float x, float y, float z, float e);          // 设定当前坐标
    void moveAbs      (float x, float y, float z, float e, float rateT);    // 绝对坐标运动
    void moveRelative (float x, float y, float z, float e, float rateT);    // 相对坐标运动
    float           getCurPos(uint8 axis)    {return currentPos[axis]; }
    te_gcode_status getStaus()               {return status;           }
    uint32    printStartTime;
    int       multiply;
    bool      emergencyStop;
    bool      taskRunEnable;
    void      calculateDeltaPara();
//--------------------------------------
// G29 传感器敏感程度检测
    bool    pressDetectFlag;    // 检测标志
    uint16  sensitivityMax;     // 震动环境下压力值最大值
    uint16  sensitivityNor;     // 正常压力值
//
//--------------------------------------
// G 代码
    void G0_G1();                                       //  G0 G1 执行直线运动
    void G2_G3();                                       //  G2 G3 圆形插补
    void G4   ();                                       //  G4 定时时间
    void G28  ();                                       //  G28 回原点
    void G29  ();                                       //  自动调平
    void G90  ()    {relativeFlag = false;}             //  绝对坐标模式
    void G91  ()    {relativeFlag = true; }             //  相对坐标模式
    void G92  ();                                       //  设定当前坐标
//
//--------------------------------------
// M 代码
    void M0_M1();                                       // 条件等待延时
    void M17  ();                                       // 电机开启
    void M20  ();                                       // SD卡 列出文件目录
    void M21  ()    {sdReader.init();               }   // SD卡 初始化
    void M22  ()    {sdReader.uinit();              }   // SD卡 拔出
    void M23  (char *text){sdReader.open(text, "r");}   // SD卡 选择文件打开
    void M24  ();                                       // SD卡 启动打印
    void M25  ()    {sdReader.setStartPrint(false); }   // SD卡 停止打印
    void M27  ()    {sdReader.getStatus();          }   // SD卡 打印状态
    void M28  (char *text){sdReader.write(text);    }   // SD卡 开始写文件
    void M29  ()    {sdReader.writeCmdEnd();        }   // SD卡 停止写文件
    void M30  (char *text){sdReader.removeFile(text);}  // SD卡 删除文件

    void M104 ()    {tempHotEnd1.setTarTemp(buf.S); }                   // 设定温度值
    void M140 ()    {tempHotBed .setTarTemp(buf.S); }                   // 设定温度值
    void M105 ()    {serialCommu.print("ok");   showTemperature();  }   // 回显示温度
    void M106 ();
    void M107 ();
    void M109 ();
    void M303 ();
    void M32  ();
    void M220 ();
    void M84  ();
    void M80  ()    {delectWait();}
    void stop ();
    void delectWait() {M109Wait = G4Wait = G29Wait = false;}
    ts_delta_para   deltaPara;
//
//--------------------------------------
// delta 机型
    float   currentPos   [MAX_AXIS];    // 当前坐标
    float   targetPos    [MAX_AXIS];    // 目标坐标
//
//--------------------------------------
// M 代码
private:
    float G29_Detect(float x, float y, float rate);
    float G29_Liner (float x, float y, float rate, float *pN, float *pP);
    void  showTemperature();
    void  calculateDelta(float *cartesian, float *delta);
    void  getCoordinates(float *);
    void  softLimit(float *);
    void  setDest2current(float *);
    uint8 homeAxis(uint8 axis, float feedrateT, float *stepPos);
    void  setCurrentPos(uint8 Axis, float value);
//
//--------------------------------------
// delta 机型
    float   feedrate;
    float   feedrateSave;
    te_gcode_status   status;
    bool    M109Wait;
    bool    G29Wait;
    bool    G4Wait;
//
//--------------------------------------
// 圆形规划
    float  centerX;
    float  centerY;
    float  linearTravel;    // 线性
    float  extrudeTravel;   // 挤出
    float  rAxisX;
    float  rAxisY;
    float  rtAxisX;
    float  rtAxisY;
    float  angular_travel;  // 角度
    float  cosSegment;
    float  sinSegment;
    bool   AutoLevEnable;
		bool   disAdjustEnable;
    ts_commu_buf    buf;
//
//--------------------------------------
// 
    bool    relativeFlag;   // 相对坐标系统
};
//
//-------------------------------------------------------------------
//
extern c_gcode gcode;
extern __task void gcodeTsk();

#ifdef __cplusplus
extern "C" {
#endif
    extern void AutoLeaverCheck(int value);
#ifdef __cplusplus
}
#endif

#endif //__GCODE_H__
//-------------------------------------------------------------------
