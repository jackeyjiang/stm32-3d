#include "m_include.h"
//=====================================================
// G 码转换驱动运动
//=====================================================
C_step step;
//=====================================================
C_step::C_step()
{
//     //====================================
//     //== 设定定时器时基为 1us 65.536ms 溢出
//     stepTimer.setOverflow(0xffff);
//     stepTimer.setPrescaleFactor(72);
//     stepTimer.attachCompare1Interrupt(stepC1Isr);
//     
//     for (int i=0; i<4; i++) {
//         remainStep[i]=false;
//         stepDuty[i]    = 200;
//         stepDutyMin[i] = 1000;
//     }
//     //====================================
//     // 升降品台个数
//     accUpStepCun = 300;                                             // 升速计数
//     accDownStepCun = STEP_SLOW_DOWN_PERSON*accUpStepCun / 100;      // 降速计数
}
//=====================================================



// uint8_t C_step::Gcode2Destination(GCode *com)
// {
// //     register long p;
// //     float x = com->X,y=com->Y,z=com->Z,e=com->E, f=com->F;
// //     
// //     //==================================================
// //     // 1: 公制英制转换, 判断      
// //     if (unitIsInches) {
// //         x *= 25.4;
// //         y *= 25.4;
// //         z *= 25.4;
// //         e *= 25.4;
// //         f *= 25.4;
// //     }       
// //         
// //     //==================================================
// //     // 2: 坐标纪录
// //     if(CoordinateMode == COORDINATE_MODE_ABSOLUTE) {
// //         if(com->hasX()) lastCmdPos[X_AXIS] = currentPosition[X_AXIS] = x - coordinateOffset[X_AXIS];
// //         if(com->hasY()) lastCmdPos[Y_AXIS] = currentPosition[Y_AXIS] = y - coordinateOffset[Y_AXIS];
// //         if(com->hasZ()) lastCmdPos[Z_AXIS] = currentPosition[Z_AXIS] = z - coordinateOffset[Z_AXIS];
// //     } else {
// //         if(com->hasX()) lastCmdPos[X_AXIS] = currentPosition[X_AXIS] += x;
// //         if(com->hasY()) lastCmdPos[Y_AXIS] = currentPosition[Y_AXIS] += y;
// //         if(com->hasZ()) lastCmdPos[Z_AXIS] = currentPosition[Z_AXIS] += z;
// //     }
// //     
// //     //==================================================
// //     // 3: 转换成目标脉冲数
// //     x=lastCmdPos[X_AXIS]; y=lastCmdPos[Y_AXIS]; z=lastCmdPos[Z_AXIS];
// //     destinationSteps[X_AXIS] = x*axisStepsPerMM[X_AXIS] + 0.5;
// //     destinationSteps[Y_AXIS] = y*axisStepsPerMM[Y_AXIS] + 0.5;
// //     destinationSteps[Z_AXIS] = z*axisStepsPerMM[Z_AXIS] + 0.5;
// //     
// //     //==================================================
// //     // 4: 给进速度 mm/min => mm/s 并做加减速系数计算
// //     if(com->hasF()) 
// //         feedrate = f*(float)feedrateMultiply*0.00016666666f;
// //     
// //     //==================================================
// //     // 5: 判断是否有运动
// //     if (com->hasNoXYZ())
// //         return 0;
// //     
// //     //==================================================
// //     // 6: 获得一条运动驱动缓存
// //     Printer::unsetAllSteppersDisabled();
// //     PrintLine::waitForXFreeLines(1);
// //     uint8_t newPath=PrintLine::insertWaitMovesIfNeeded(1, 0);
// //     PrintLine *pPline = PrintLine::getNextWriteLine();
// //     
// //     //==================================================
// //     // 7: 判断方向，计算差值脉冲数, 最大运动时间, 最大脉冲数
// //     long  delta[4], maxDelta=0;     //steps
// //     float maxTimer=0, tempTimer;
// //     
// //     if(ALWAYS_CHECK_ENDSTOPS)  pPline->flags = FLAG_CHECK_ENDSTOPS;
// //     else                       pPline->flags = 0;
// //     pPline->dir = 0;
// //     
// //     for(uint8_t axis=0; axis < 4; axis++) {
// //         if((delta[axis]=destinationSteps[axis]-currentPositionSteps[axis])>=0) {
// //             //= 设定方向
// //             pPline->setPositiveDirectionForAxis(axis);
// //         } else {
// //             //= 转换绝对值
// //             delta[axis] = -delta[axis];
// //         }
// //         
// //         //= 置位运行允许
// //         if (delta[axis]) pPline->setMoveOfAxis(axis);
// //         else             continue;
// //         
// //         //= 判断选择运行时间最长的作为主驱动轴，其他轴运动同步于主轴
// //         //= ticks / (mm/ticks) / (mm/s)
// //         tempTimer = (float)delta[axis]*Printer::invAxisStepsPerMM[axis]/Printer::maxFeedrate[axis];
// //         if (tempTimer > maxTimer) {
// //             maxTimer = tempTimer;
// //         }
// //         
// //         //= 判断最大脉冲数
// //         if (delta[axis] > maxDelta) {
// //             maxDelta = delta[axis];
// //         }
// //     }
// //     
// //     //==================================================
// //     // 根据最大时间最大脉冲数计算 每个驱动对应主驱动轴的系数
// //     for(uint8_t axis=0; axis<4; axis++) {
// //         if (delta[axis]) {
// //             axisStepsMultiply[axis] = (float)maxDelta/delta[axis];
// //         }
// //     }
// }
//=====================================================
// 定时器1 中断函数
//=====================================================
void stepC1Isr(void) {
//     //1. == 引脚不需要驱动 ==
//     if (!step.isRemainStep(0)) {
//         isr_sem_send (stepSemFinish);
//         stepTimer.pause();
//         return;
//     }
//     //2. == 驱动引脚 ==
//     step.setPinActive(0);
//     
//     //3. == 重载定时值 ==
//     if (!step.isRemainStep(0)) {
//         isr_sem_send (stepSemFinish);
//         stepTimer.pause();
//     } else {   
//         stepTimer.setCompare1(step.getCompare(0));
//     }
//     step.setPinIdle(0);
}
//=====================================================
// 判断当前状态是否在加减速状态
// 返回当前duty % ，分度 1/1000
// speed max = 0
// speed min = 1000;
//=====================================================
inline uint16 C_step::getAccPerson(uint8_t channel) 
{
    // 升速阶段
    if (activeStep[channel]<accUpStepCun) {
        uint32_t i=activeStep[channel];
        i = i*1000/accUpStepCun;
        return 1000-i;
    } else if (remainStep[channel]<accDownStepCun) {
        uint32_t i=remainStep[channel];
        i = i*1000/accDownStepCun;
        return 1000-i;
    } else {
        return 0;
    }
}
//=====================================================
// 步进驱动任务
// 检测邮箱，如果有数据则输出脉冲。
//=====================================================
float test_mm_Cmd[][4] = {
    {10,  30,   50,   0},
    {20,  50,   80,   0},
    {-20,  80,   120,   0},
    {-40,  120,   140,   0},
};
__task void stepTask()
{
    
while (1) {     

    

    stepMoto.gcode2Block(test_mm_Cmd[0], 150);
    stepMoto.gcode2Block(test_mm_Cmd[1], 150);
    stepMoto.gcode2Block(test_mm_Cmd[2], 150);
    stepMoto.gcode2Block(test_mm_Cmd[3], 150);
    os_dly_wait(3000);

    
//     //== 等待驱动命令邮箱 ==
//     os_mbx_wait(stepMbx, (void **)&pStepBox, 0xffff);
//     
// //     //== 执行操作 ==========
// //     os_sem_wait(stepSemFinish, 0);
// //      step.triggerStep(0, pStepBox->X_F1000);
// //     stepTimer.resume();
// //     //== 等待命令完成 ======
// //     os_sem_wait(stepSemFinish, 0xffff);
//     _free_box(stepPoolMbx, pStepBox);
}
}
//=====================================================

