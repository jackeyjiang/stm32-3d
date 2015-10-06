//=========================================================================
// 执行
//=========================================================================
#ifndef _STEP_H_
#define _STEP_H_


#define COORDINATE_MODE_ABSOLUTE    false       // 绝对坐标系
#define COORDINATE_MODE_RELATIVE    true        // 相对坐标系


class C_step {
public:
    C_step(void);
    uint8_t CoordinateMode;             // 相对坐标，绝对坐标
    uint8_t unitIsInches;               // 英制单位
    int feedrateMultiply;               //< 给进系数 (factor 1 = 100)
    
    long   destinationSteps[3];          // 目标脉冲数
    long   currentPositionSteps[3];      // 当前脉冲数
    float  currentPosition[3];           // 当前坐标
    float  lastCmdPos[3];                // 上次比对坐标
    float  coordinateOffset[3];          // 坐标偏置
    float  axisStepsPerMM[3];            // mm 脉冲数
    float  feedrate;                     // 给进速度 mm/s
    float  axisStepsMultiply[3];         // 相对主输出轴系数
    uint16 accUpStepCun;                 // 升速计数
    uint16 accDownStepCun;               // 降速计数
    
//     uint8_t Gcode2Destination(GCode *com);
private:
    uint8_t  pinNumber[4];      // 引脚
    uint32_t remainStep[4];     // 剩余脉冲数
    uint32_t activeStep[4];     // 当前块脉执行数
    uint16_t stepDuty[4];       // 每步脉冲定时值
    uint16_t stepDutyMin[4];    // 最低品台速度
public:
    inline bool    isRemainStep (uint8_t channel) {return remainStep[channel];            }
    inline void    setPinActive (uint8_t channel) {gpio.digitalWrite(pinNumber[channel],HIGH); remainStep[channel]--; activeStep[channel]++;}
    inline void    setPinIdle   (uint8_t channel) {gpio.digitalWrite(pinNumber[channel],LOW ); }
    inline uint16  getCompare   (uint8_t channel) {
//         uint32 accDuty = stepDutyMin[channel]-stepDuty[channel];
//         accDuty = stepDuty[channel]+accDuty*getAccPerson(channel)/1000;
//         return accDuty+stepTimer.getCount();
//         return stepDuty[channel] + stepTimer.getCount();
        return 0;
    }
    
    //== 触发主脉冲 ========
    void triggerStep  (uint8_t channel, uint32_t value) {
//         remainStep[channel] = value;
//         activeStep[channel] = 0;
//         timer_dev *dev = stepTimer.c_dev();
//         __io uint32 *ccr = &dev->regs.adv->CCR1 + channel;
//         *ccr = stepTimer.getCount()+1;
    }
    //== 获得加减速百分比 ====
    inline uint16 getAccPerson(uint8_t);
    
    //== 设定主轴定时器 ======
    inline void setMastAxitCopare(uint8_t channel) {
//         uint32 accDuty = stepDutyMin[channel]-stepDuty[channel];
//         accDuty = stepDuty[channel]+accDuty*getAccPerson(channel)/1000;
//         timer_dev *dev = stepTimer.c_dev();
//         __io uint32 *ccr = &dev->regs.adv->CCR1 + channel;
//         *ccr = stepTimer.getCount()+accDuty;
    }
};
//================================================
void stepC1Isr(void);
extern C_step step;
//================================================
typedef struct {
    unsigned int params;
    unsigned int params2;
    unsigned int N; // Line number
    unsigned int M;
    unsigned int G;
    long         S;
    long         P;
    uint8_t      T;
    char         text[20]; //text[17];
    uint32_t     X_F1000;
    uint32_t     Y_F1000;
    uint32_t     Z_F1000;
    uint32_t     E_F1000;
    uint32_t     F_F1000;
    uint32_t     I_F1000;
    uint32_t     J_F1000;
    uint32_t     R_F1000;
}TS_stepMbx;

//== 信号量 ==

__task void stepTask();


#endif

