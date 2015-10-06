//========================================================
#ifndef __PROJECT_H__
#define __PROJECT_H__
//========================================================
#include <rtl.h>


//========================================================
//== 串口使用 ==============
#define serialGcode     serial1
#define serialDebug     serial2

//== 步进定时器使用 ========
#define stepTimer       Timer1

//== 步进电机加减速台阶数 ==
#define stepStepCnt             20
#define STEP_SLOW_DOWN_PERSON   50
//== MAX 200MM/S
#define STEP_MAX_SPEED          200



//== step box length
#define STEP_MBX_LENGTH         20

//========================================================

#endif

