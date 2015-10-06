#ifndef __IO_CONFIG_H__
#define __IO_CONFIG_H__

//== 串口使用 ==============
#define serialGcode     Serial1
#define serialDebug     Serial2

//== 步进定时器使用 ========
#define stepTimer       Timer1

//== 步进电机加减速台阶数 ==
#define stepStepCnt             20
#define STEP_SLOW_DOWN_PERSON   50
//== MAX 200MM/S
#define STEP_MAX_SPEED          200



//== step box length
#define STEP_MBX_LENGTH         20


#endif