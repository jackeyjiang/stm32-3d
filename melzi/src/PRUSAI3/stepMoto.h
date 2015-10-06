//=================================================================
#ifndef __STEP_MOTO_H__
#define __STEP_MOTO_H__
#include "typeDefine.h"
#include "m_ringBuffer.h"
#include "m_timer.h"
#include "sysConf.h"
//=================================================================
#define STEP_RUN_BUF_CUN    20      // block 缓存个数
#define STEP_TIMER          timer2
#define STEP_CHANNEL        1
//=================================================================
// 步进电机定义结构
//=================================================================
typedef struct {
    int8  step;
    int8  dir;
    int8  enable;
    int8  max;
    int8  min;
}ts_pin_step_moto;
//
typedef struct {
    uint16 maxSpeed;    //   mm/sec
    float  maxAcc;      //   steps/sec^2
    float  steps2mm;    //   steps/ mm
}ts_para_step_moto;
//
//====================================
// 单个执行块
typedef enum {
    direction_positive = 1,
    direction_negative =-1,
}te_direction;
//
typedef struct {
    //== 中断需要使用
    int32           tarSteps;           // 需要执行完成步数
    int8            direction;          // 方向
}ts_stepAxisRun;
//
typedef struct {
    int32   stepEventCun;           // 最大steps
    bool    busy;                   // 中断执行中
    bool    norminal_length;        // 正常长度标记
    bool    recalculate;            // 重新计算梯形
    bool    entrylockFlag;          // 锁定标记
    //
    //===========
    float   millimeters;            // 行程mm 数
    float   norminal_speed;         // 正常速度 mm/s
    int32   norminal_rate;          // 正常速率 steps/s
    float   acceleration;           // 加速度   mm    /s^2
    int32   accelerRate;            // 加速率   steps /s^2
    //
    //===========
    uint8   fanSpeed;               // 风机速度
    //
    //===========
    // 梯形加减速
    float   maxEntrySpeed;          // 最大进入速度
    float   entrySpeed;             // 进入速度
    int32   accelerate_until;       // 梯形加速结束脉冲数 steps
    int32   decelerate_after;       // 梯形开始减速脉冲数 steps
    int32   accelerate_begin_rate;  // 加速开始速度 steps/s
    int32   decelerate_end_rate;    // 减速结束速度
    //
    //===========
    // 各轴运行变量
    ts_stepAxisRun   axis[MAX_AXIS];
}ts_stepBlockRun;
//
//=================================================================
// 步进控制类结构
//=================================================================
typedef struct {
    ts_pin_step_moto   pinTab  [MAX_AXIS];   // 引脚定义
    ts_pin_step_moto   pinAct  [MAX_AXIS];   // 引脚有效
    ts_para_step_moto  pinPara [MAX_AXIS];   // 引脚参数
    int32              posSteps[MAX_AXIS];   // 记录的脉冲数
    int32              tarSteps[MAX_AXIS];   // 临时变量，减少任务 栈空间 
    int32              realSteps[MAX_AXIS];  // 实际输出脉冲数
    //
    uint16       limitFlag;                  // 检测到限位
    bool         maxLimitFlag[MAX_AXIS];     // 高限位
    bool         minLimitFlag[MAX_AXIS];     // 低限位
    //
    uint8   fanSpeed;            // 风机速度
    //
    uint8   dropSegments;        // 小于此值不执行
    int32   minTravelSpeed;      // 移动最低速度           
    int32   mininumSpeed;        // 最低速度
    uint32  minSegmentTick;      // 最小时间块
    //
    //-------------
    // 运行
    uint8   runningFlag;         // 运行标记
}ts_step_moto;
//
//=================================================================
// 步进电机单个block结构
//=================================================================
class c_stepMoto {
public:
//---------------------------------
//  接口函数
    void  move    (float *tarT, float setSpeedT);
    void  trigger ();                              // 触发脉冲
    void  initMbx ();                              // 邮箱初始化
//---------------------------------
//  总行程计算脉冲
	int32   SavePosSteps[MAX_AXIS];
    int32   SaveStepEventCun;
    int32   calculateStepsGet () {return SaveStepEventCun; }
//---------------------------------
    void  setPosSteps(float *tarT);
    void  setPosSteps(uint8  axis, float tarT) {dev->posSteps[axis] = dev->pinPara[axis].steps2mm * tarT;   }   // 设定位置
    float getPosSteps(uint8  axis)             {return dev->posSteps[axis] / dev->pinPara[axis].steps2mm;   }   // 得到位置
    void  setPos2Real();            // 复位使用
    void  setReal2Pos();            // 消除限位开关的影响
    float getRealZmm ();
    float getPosZmm  ();
    void  clearLimitF();
    bool  getMaxLimitF (bool xCheck, bool yCheck, bool zCheck); 
    void  waitFinish ();
    int32 rate_acc_2_Steps  (uint32 initRate, uint32 tarRate,   float acc);
    int32 steps_acc_2_rate  (uint32 initRate, uint32 steps,     float acc);
    float dis_acc_2_speed   (float  speed_v0, float  millimeter,float acc);
    uint32 motoIdleTimer;
//
//---------------------------------
public:
    c_stepMoto(ts_step_moto *);
//
//---------------------------------
//  isr 使用
    void pauseTimer ();
    void resumeTimer();
    void setCompare     (uint16 value);
    void pauseInterrupt ();
    void resumeInterrupt(); 
//
//---------------------------------
//  变量
    ts_step_moto      *dev;
    ring_buffer        rb;
    boolean            waitMutStep;
private:
//
//---------------------------------
//  set block
    int32  calculateTrapezoid(ts_stepBlockRun *block, float entfactor, float extfactor);
    void  recalculate_trapezoids();
    void  planner_reverse_pass();
    void  planner_forward_pass();
    bool  planner_pass_kernel(ts_stepBlockRun *pre, ts_stepBlockRun *cur, ts_stepBlockRun *next);

    inline int32 intersection_steps(uint32 initRate, uint32 tarRate, float acc, uint32 eventCun);
    inline void  triggerStepBlock();
    boolean      trigerFlag;
//
//---------------------------------
};
extern c_stepMoto stepMoto;
//
//=================================================================
#endif  //__STEP_MOTO_H__
//=================================================================
