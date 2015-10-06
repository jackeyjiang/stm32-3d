//=================================================================
#include "m_include.h"
#include "stepMoto.h"
#include "math.h"
//=================================================================
// 引脚电平有效表
// 电机运行参数
//=================================================================
OS_SEM          sem_step;
ts_stepBlockRun block_buf[STEP_RUN_BUF_CUN];
int8            directionCnt[MAX_AXIS];
//
//== 捕捉高限位中断
void maxLimitIsr(int Ch) {
    lcd.buzzerFlag = 1;
    if (directionCnt[Ch] == 1) {
        stepMoto.dev->maxLimitFlag[Ch] = true; 
        stepMoto.dev->limitFlag = true;
        
    }
}
void max1LimitIsr() {maxLimitIsr(0);}   void max2LimitIsr() {maxLimitIsr(1);}
void max3LimitIsr() {maxLimitIsr(2);}   void max4LimitIsr() {maxLimitIsr(3);}   void max5LimitIsr() {maxLimitIsr(4);}
void (*pMaxLimitIsr[5]) (void) = {                                          \
    max1LimitIsr, max2LimitIsr, max3LimitIsr, max4LimitIsr, max5LimitIsr};  \
//
//== 捕捉低限位中断
void minLimitIsr(int Ch) {
    lcd.buzzerFlag = 1;
    if (directionCnt[Ch] == -1) {
        stepMoto.dev->minLimitFlag[Ch] = true; 
        stepMoto.dev->limitFlag = true;
    }
}
void min1LimitIsr() {minLimitIsr(0);}   void min2LimitIsr() {minLimitIsr(1);}
void min3LimitIsr() {minLimitIsr(2);}   void min4LimitIsr() {minLimitIsr(3);}   void min5LimitIsr() {minLimitIsr(4);}
void (*pMinLimitIsr[5]) (void) = {                                          \
    min1LimitIsr, min2LimitIsr, min3LimitIsr, min4LimitIsr, min5LimitIsr};  \
//
//===============================================================
void c_stepMoto::pauseTimer ()  {Timer.pause (&timer2); }
void c_stepMoto::resumeTimer()  {Timer.resume(&timer2); }
void stepIsr ();
//
//===============================================================
int8 pinTab[5][5] = {
    {PIN_X_STEP,  PIN_X_DIR,   },
    {PIN_Y_STEP,  PIN_Y_DIR,   },
    {PIN_Z_STEP,  PIN_Z_DIR,   },
    {PIN_E1_STEP, PIN_E1_DIR,  },
    {PIN_E2_STEP, PIN_E2_DIR,  },
};
ts_step_moto step_moto_3d = {
    .pinTab = {         // 功能引脚表
        {.step = pinTab[EEP.data.printer.steps_pin[0]][0],  .dir = pinTab[EEP.data.printer.steps_pin[0]][1], .enable = PIN_X_ENABLE,  .max = PIN_X_MAX,  .min = PIN_X_MIN },
        {.step = pinTab[EEP.data.printer.steps_pin[1]][0],  .dir = pinTab[EEP.data.printer.steps_pin[1]][1], .enable = PIN_Y_ENABLE,  .max = PIN_Y_MAX,  .min = PIN_Y_MIN },
        {.step = pinTab[EEP.data.printer.steps_pin[2]][0],  .dir = pinTab[EEP.data.printer.steps_pin[2]][1], .enable = PIN_Z_ENABLE,  .max = PIN_Z_MAX,  .min = PIN_Z_MIN },
        {.step = pinTab[EEP.data.printer.steps_pin[3]][0],  .dir = pinTab[EEP.data.printer.steps_pin[3]][1], .enable = PIN_E1_ENABLE, .max = PIN_E1_MAX, .min = PIN_E1_MIN},
        },
    .pinAct     = {     // 引脚电平有效表
        {.step = PIN_X_STEP_A,  .dir = PIN_X_DIR_P,  .enable= PIN_X_ENABLE_A,  .max = PIN_X_MAX_A,  .min= PIN_X_MIN_A },
        {.step = PIN_Y_STEP_A,  .dir = PIN_Y_DIR_P,  .enable= PIN_Y_ENABLE_A,  .max = PIN_Y_MAX_A,  .min= PIN_Y_MIN_A },
        {.step = PIN_Z_STEP_A,  .dir = PIN_Z_DIR_P,  .enable= PIN_Z_ENABLE_A,  .max = PIN_Z_MAX_A,  .min= PIN_Z_MIN_A },
        {.step = PIN_E1_STEP_A, .dir = PIN_E1_DIR_P, .enable= PIN_E1_ENABLE_A, .max = PIN_E1_MAX_A, .min= PIN_E1_MIN_A},
//      {.step = PIN_E2_STEP_A, .dir = PIN_E2_DIR_P, .enable= PIN_E2_ENABLE_A, .max = PIN_E2_MAX_A, .min= PIN_E2_MIN_A}
        },
    .pinPara    = {     // 电机运行参数
        {.maxSpeed = EEP.data.motion.maxSpeed[ X_AXIS], .maxAcc = EEP.data.motion.maxAcc[ X_AXIS] * EEP.data.printer.steps_mm[X_AXIS ],  .steps2mm = EEP.data.printer.steps_mm[X_AXIS ] },
        {.maxSpeed = EEP.data.motion.maxSpeed[ Y_AXIS], .maxAcc = EEP.data.motion.maxAcc[ Y_AXIS] * EEP.data.printer.steps_mm[Y_AXIS ],  .steps2mm = EEP.data.printer.steps_mm[Y_AXIS ] },
        {.maxSpeed = EEP.data.motion.maxSpeed[ Z_AXIS], .maxAcc = EEP.data.motion.maxAcc[ Z_AXIS] * EEP.data.printer.steps_mm[Z_AXIS ],  .steps2mm = EEP.data.printer.steps_mm[Z_AXIS ] },
        {.maxSpeed = EEP.data.motion.maxSpeed[E1_AXIS], .maxAcc = EEP.data.motion.maxAcc[E1_AXIS] * EEP.data.printer.steps_mm[E1_AXIS],  .steps2mm = EEP.data.printer.steps_mm[E1_AXIS] },
//      {.maxSpeed = PIN_E2_MAX_SPEED, .maxAcc = PIN_E2_MAX_ACC_SPEED* PIN_E2_STEPS_MM, .steps2mm = PIN_E2_STEPS_MM}
        },
};
c_stepMoto stepMoto(&step_moto_3d);
//
//===============================================================
// 初始化邮箱
//===============================================================
void c_stepMoto::initMbx() {
    rb_init(&rb, STEP_RUN_BUF_CUN, NULL);
    os_sem_init(sem_step, 0);
}
//
//===============================================================
// 构造函数
//=============================================================
c_stepMoto::c_stepMoto(ts_step_moto *devT) {
    dev = (ts_step_moto *)devT;
    for (int i=0; i<MAX_AXIS; i++) {
        //
        //===================================
        //1. 初始化引脚功能
        if (dev->pinTab[i].step    != -1) gpio.pinMode(dev->pinTab[i].step,    OUTPUT);
        if (dev->pinTab[i].dir     != -1) gpio.pinMode(dev->pinTab[i].dir,     OUTPUT);
        if (dev->pinTab[i].enable  != -1) gpio.pinMode(dev->pinTab[i].enable,  OUTPUT);
        //
        //===================================
        //2. 限位开关
        if (dev->pinTab[i].max != -1) {
            gpio.pinMode(dev->pinTab[i].max, INPUT_FLOATING);
            exti.begin(dev->pinTab[i].max, pMaxLimitIsr[i], (stepMoto.dev->pinAct[i].max) ? (EXTI_RISING) : (EXTI_FALLING));
        }
        if (dev->pinTab[i].min != -1) {
            gpio.pinMode(dev->pinTab[i].min, INPUT_FLOATING);
            exti.begin(dev->pinTab[i].min, pMinLimitIsr[i], (stepMoto.dev->pinAct[i].min) ? (EXTI_RISING) : (EXTI_FALLING));
        }
    }
    //
    //=======================================
    //3. 定时器
    Timer.setPrescaleFactor (&STEP_TIMER, CYCLES_PER_MICROSECOND/1000-1);
    Timer.setOverflow       (&STEP_TIMER, 0xffff);   
    Timer.pause             (&STEP_TIMER);
    Timer.attachInterrupt   (&STEP_TIMER, STEP_CHANNEL, stepIsr);
    Timer.pauseInterrupt    (&STEP_TIMER, STEP_CHANNEL);   
    //
    //=====================
    //8. 数据初始化
    dev->minTravelSpeed   = para.motion.jerk_xy;
    dev->mininumSpeed     = para.motion.jerk_e;          
    //
    //=====================
}
//===============================================================
// 单个block 运行，在中断中执行
//===============================================================
void stepIsr () {  
    static int32            axisCnt[MAX_AXIS];
    static int32            compValue;
    static float            accTime, decTime;
    static int32            stepRate;
    static int32            trigCun;
    static ts_stepBlockRun *block = NULL;
		static uint8						pressCnt  = 0;
		static uint8						pressWait = false;
    //
    //===============================
    // 1. step 引脚复位
    for (int i=0; i<MAX_AXIS; i++) {
        gpio.digitalWrite(stepMoto.dev->pinTab[i].step, !stepMoto.dev->pinAct[i].step);
    }
    //
    //===============================
    // 2. 获得内存
    if (block == NULL) {
        if (rb_is_empty(&stepMoto.rb)) {
            if (stepMoto.dev->runningFlag)
                stepMoto.dev->runningFlag--;
            stepMoto.setCompare(1000);
            return;
        }
        block = &block_buf[stepMoto.rb.head];
        stepRate = block->accelerate_begin_rate;
        block->busy = true;
        axisCnt[0] = -(block->stepEventCun>>1);
        trigCun = 0; accTime = 0; decTime = 0;
        //===============================
        //== 方向判断
        for (int i=0; i<MAX_AXIS; i++) {
            axisCnt[i] = axisCnt[0];
            if (block->axis[i].tarSteps == 0) {
                directionCnt[i] = 0; 
            } else if (block->axis[i].direction == direction_positive) {
                gpio.digitalWrite(stepMoto.dev->pinTab[i].dir,  stepMoto.dev->pinAct[i].dir);
                directionCnt[i] = 1;
            } else {
                gpio.digitalWrite(stepMoto.dev->pinTab[i].dir, !stepMoto.dev->pinAct[i].dir);
                directionCnt[i] = -1;
            }
        }
        if (block->fanSpeed) {
            (lcd.laserModle == true) ? (tempHotEnd2.setOut(tempHotEnd2.outMax)) : (gpio.digitalWrite(PIN_DO2, HIGH));
        } else {
            (lcd.laserModle == true) ? (tempHotEnd2.setOut(0)) : (gpio.digitalWrite(PIN_DO2, LOW));
        }
        //===============================
    }
    //
    //===============================
    // 3. G29 Z- Detect 托盘压力检测
    if (gcode.pressDetectFlag) {
			pressCnt++;
			if (pressCnt > 5) {
				pressCnt  = 0;
				pressWait = true;
				stepMoto.setCompare(50000);	// 等待 50ms
                return;
			}
			if (pressWait == true) {
					uint16 max = 0, min = 0xffff, ad;
					uint32 sum = 0;
					for (int i=0; i<34; i++) {
                        ad = adc.loopGetData(AUTO_LEAVER_PIN);
                        max  = max(max, ad);
                        min  = min(min, ad);
                        sum += ad;
					}
					ad = (sum - max - min)>>5;
					if ((ad > gcode.sensitivityMax)){
						stepMoto.dev->limitFlag = true;
                        lcd.buzzerFlag = 1;
					}
            }
            pressWait = false;
    }
    //
    //===============================
    // 3. 限位开关 或者 应急停
    if (stepMoto.dev->limitFlag || gcode.emergencyStop) {
        if (stepMoto.waitMutStep) {
            isr_sem_send(sem_step);
            stepMoto.waitMutStep = false;
        }
        rb_reset(&stepMoto.rb);
        block = NULL;
        stepMoto.setCompare(1000);
        return;
    }
    trigCun ++;
    //
    //===============================
    // 4. 加减速
    if (trigCun < block->accelerate_until) {
		stepRate  = accTime * block->accelerRate + block->accelerate_begin_rate;
        stepRate  = boundary(stepRate, block->accelerate_begin_rate, block->norminal_rate);
        compValue = 1000000 / stepRate;						// us = 1000000us / (steps/s);
				accTime += (float)compValue / 1000000;
    } else if (trigCun >= block->decelerate_after) {  
				compValue = stepRate - block->accelerRate * decTime;
        compValue = boundary(compValue, block->decelerate_end_rate, block->norminal_rate);
        compValue = 1000000 / compValue;
				decTime += (float)compValue / 1000000;
    } else {
        stepRate = block->norminal_rate;
				compValue = 1000000 / block->norminal_rate;
    }
    stepMoto.setCompare(compValue);
    //
    //===============================
    // 5. 脉冲输出
    for (int i=0; i<MAX_AXIS; i++) {
        axisCnt[i] += block->axis[i].tarSteps;
        if (axisCnt[i] > 0) {
            gpio.digitalWrite(stepMoto.dev->pinTab[i].step, stepMoto.dev->pinAct[i].step);
            axisCnt[i] -= block->stepEventCun;
            stepMoto.dev->realSteps[i] += directionCnt[i];
        }
    }
    //
    //===============================
    // 6. 完成输出
    if (trigCun >= block->stepEventCun) {
        if (stepMoto.waitMutStep) {
            isr_sem_send(sem_step);
            stepMoto.waitMutStep = false;
        }
        rb_removeIndex(&stepMoto.rb);
        block = NULL;
    }
}
//
//===============================================================
// 等待 完成
//===============================================================
void c_stepMoto::waitFinish() {
    while(dev->runningFlag) {
        os_dly_wait(5);
    }
}
//
//===============================================================
// 设定 POS STEPS
//===============================================================
void c_stepMoto::setPosSteps(float *tar) {
    for (int i=0; i<MAX_AXIS; i++) {
        dev->posSteps[i] = dev->realSteps[i] = dev->pinPara[i].steps2mm * tar[i];
    }
}
//
//===============================================================
// 复位 Real
//===============================================================
void c_stepMoto::setPos2Real() {
    for (int i=0; i<MAX_AXIS; i++) {
        dev->realSteps[i] = dev->posSteps[i];
    }
}
//
//===============================================================
// 消除限位开关差
//===============================================================
void c_stepMoto::setReal2Pos() {
    for (int i=0; i<MAX_AXIS; i++) {
        dev->posSteps[i] = dev->realSteps[i];
    }
}
//
//===============================================================
// 消除限位开关差
//===============================================================
float c_stepMoto::getRealZmm() {
    return (float)dev->realSteps[Z_AXIS]/dev->pinPara[Z_AXIS].steps2mm;
}
//
//===============================================================
// 消除限位开关差
//===============================================================
float c_stepMoto::getPosZmm() {
    return (float)dev->posSteps[Z_AXIS]/dev->pinPara[Z_AXIS].steps2mm;
}
//===============================================================
// 触发第一次BLOCK发送
//===============================================================
void c_stepMoto::triggerStepBlock() {
    dev->runningFlag = 10;
    if (trigerFlag == true) return;
    
    stepMoto.setCompare     (10);
    stepMoto.resumeInterrupt();
    stepMoto.resumeTimer    ();
    trigerFlag = true;
}
//
//===============================================================
// 清除限制标置
//===============================================================
void c_stepMoto::clearLimitF() {
    for (int i=0; i<MAX_AXIS; i++) {
        dev->maxLimitFlag[i] = false;
        dev->minLimitFlag[i] = false;
    }  
    dev->limitFlag = 0;
}
//
//===============================================================
// 获取限制标置
//===============================================================
bool c_stepMoto::getMaxLimitF(bool xCheck, bool yCheck, bool zCheck) {
    if (xCheck && (gpio.digitalRead(dev->pinTab[X_AXIS].max) == dev->pinAct[X_AXIS].max))
        return true;
    if (yCheck && (gpio.digitalRead(dev->pinTab[Y_AXIS].max) == dev->pinAct[Y_AXIS].max))
        return true;
    if (zCheck && (gpio.digitalRead(dev->pinTab[Z_AXIS].max) == dev->pinAct[Z_AXIS].max))
        return true;
    return false;
}
//
//===============================================================
// 设比较值
//===============================================================
void c_stepMoto::setCompare (uint16 value) {   
    Timer.setCompare(&STEP_TIMER, STEP_CHANNEL, Timer.getCount(&STEP_TIMER) + value);
}
//
//===============================================================
// 暂停通道中断
//===============================================================
void c_stepMoto::pauseInterrupt () {
    Timer.pauseInterrupt (&STEP_TIMER, STEP_CHANNEL);
}
//
//===============================================================
// 重启通道中断
//===============================================================
void c_stepMoto::resumeInterrupt () {
    Timer.resumeInterrupt (&STEP_TIMER, STEP_CHANNEL);
}
//
//===============================================================
// gcode 转到 block 准备执行
//===============================================================
void c_stepMoto::move (float *tarT, float speed_s) {
//
//------------------------------------------
//  1. 等待有buf可用
    if (rb_is_full(&rb)) {
        waitMutStep = true;
        os_sem_wait(sem_step, 0xffff);
    }
//
//------------------------------------------
//  2. 速度快速调节
    speed_s = speed_s*gcode.multiply / 100;
//
//------------------------------------------
//  3. == mm->steps mm值转换成steps
    for (uint8 i=0; i<MAX_AXIS; i++) {
        dev->tarSteps[i] = lround(tarT[i]*dev->pinPara[i].steps2mm);
    }
//
//------------------------------------------
//  4. == 挤出机 低温， 最大行程保护
    if (dev->tarSteps[E1_AXIS] != dev->posSteps[E1_AXIS]) {
        if (tempHotEnd1.getTemperature() < MIN_END_EXTRUDE) 
            dev->posSteps[E1_AXIS] = dev->tarSteps[E1_AXIS];
        if (_abs(dev->tarSteps[E1_AXIS] - dev->posSteps[E1_AXIS]) > para.printer.max_pos_x * dev->pinPara[E1_AXIS].steps2mm)
            dev->posSteps[E1_AXIS] = dev->tarSteps[E1_AXIS];
    }
//
//------------------------------------------
//  5. == block steps 计算要执行的 steps
    ts_stepBlockRun *block = &block_buf[rb.tail];
    block->busy = block->stepEventCun = 0;
    for (uint8 i=0; i<MAX_AXIS; i++) {
        block->axis[i].tarSteps  = _abs(dev->tarSteps[i] - dev->posSteps[i]);
        if (i==E1_AXIS) { 
            block->axis[i].tarSteps = block->axis[i].tarSteps * para.motion.E1Mutiply / 100;
        }
        if (block->axis[i].tarSteps > block->stepEventCun) {
            block->stepEventCun = block->axis[i].tarSteps;
        }
    }
    if (block->stepEventCun <= dev->dropSegments)   return;
//
//------------------------------------------
//  6. == 风机速度
    block->fanSpeed = dev->fanSpeed;
//    
//------------------------------------------
//  7. 各轴方向
    for (uint8 i=0; i<MAX_AXIS; i++) {
        (dev->tarSteps[i] >= dev->posSteps[i]) ? (block->axis[i].direction = direction_positive) :
                                                 (block->axis[i].direction = direction_negative) ; 
    }
//  
//------------------------------------------
//  8. 最低速度设定
    if (!gcode.pressDetectFlag) {
        if (lcd.laserModle) {
            if (block->fanSpeed == 0) {
               speed_s = para.motion.maxSpeed[X_AXIS]>>1; 
            }                
        } else {
            if (block->axis[E1_AXIS].tarSteps==0) speed_s = max(speed_s, dev->minTravelSpeed);
            else                                  speed_s = max(speed_s, dev->mininumSpeed  );
        }
    }
// 
//------------------------------------------
//  9. 计算行程，时间
    static float delta_mm[MAX_AXIS];
    for (uint8 i=0; i<MAX_AXIS; i++) 
        delta_mm[i] = (dev->tarSteps[i] - dev->posSteps[i]) / dev->pinPara[i].steps2mm;
    delta_mm[E1_AXIS] = delta_mm[E1_AXIS] * para.motion.E1Mutiply / 100;
    if (block->axis[X_AXIS].tarSteps <= dev->dropSegments && block->axis[Y_AXIS].tarSteps <= dev->dropSegments && block->axis[Z_AXIS].tarSteps <= dev->dropSegments) {
        block->millimeters = _abs(delta_mm[E1_AXIS]);
    } else {
        block->millimeters = max(max(_abs(delta_mm[X_AXIS]), _abs(delta_mm[Y_AXIS])), _abs(delta_mm[Z_AXIS]));
    }
    float inverse_millimeters = 1/block->millimeters;
    float inverse_second      = speed_s * inverse_millimeters;
    block->norminal_speed = block->millimeters  * inverse_second;
    block->norminal_rate  = block->stepEventCun * inverse_second;
// 
//------------------------------------------
//  10. 判断是否有轴超速
    static float axis_speed[MAX_AXIS];
    float        speed_factor = 1.0;
    for (uint8 i=0; i<MAX_AXIS; i++) {
        axis_speed[i] = delta_mm[i] * inverse_second;
        if (delta_mm[X_AXIS]==0 && delta_mm[Y_AXIS]==0 && delta_mm[Z_AXIS]==0)
            continue;
        if (_abs(axis_speed[i]) > dev->pinPara[i].maxSpeed)
            speed_factor = min(speed_factor, dev->pinPara[i].maxSpeed / _abs(axis_speed[i]));
    }
    if (speed_factor < 1.0) {
        for (uint8 i=0; i<MAX_AXIS; i++)    axis_speed[i] *= speed_factor;
        block->norminal_speed *= speed_factor;
        block->norminal_rate  *= speed_factor;
    }
// 
//------------------------------------------
//  11. 判断是否有加速度超限
    float steps_per_mm = block->stepEventCun/block->millimeters;
    int32 acceleration_st;
    acceleration_st = para.motion.acceleration * steps_per_mm;
    for (uint8 i=0; i<MAX_AXIS; i++) {
        if (delta_mm[X_AXIS]==0 && delta_mm[Y_AXIS]==0 && delta_mm[Z_AXIS]==0) {
            acceleration_st = min(acceleration_st, EEP.data.motion.retractAcc * EEP.data.printer.steps_mm[E1_AXIS]);
            continue;
        }
        if ((acceleration_st * block->axis[i].tarSteps / block->stepEventCun)> dev->pinPara[i].maxAcc)
            acceleration_st = min(acceleration_st, dev->pinPara[i].maxAcc);
    } 
    block->acceleration = acceleration_st / steps_per_mm;
    block->accelerRate  = acceleration_st;
// 
//------------------------------------------
//  12. 连接速度
    float vmax_juncton = para.motion.jerk_xy;
    float vmax_juncton_factor = 1.0;
    if (_abs(axis_speed[Z_AXIS]) > (para.motion.jerk_z / 2))
        vmax_juncton = min(vmax_juncton, para.motion.jerk_z / 2);
    if (_abs(axis_speed[E1_AXIS]) > (para.motion.jerk_e / 2))
        vmax_juncton = min(vmax_juncton, para.motion.jerk_e / 2);
    vmax_juncton = min(vmax_juncton, block->norminal_speed);
    float safe_speed = vmax_juncton;
    //
    static float pre_nominal_speed;
    static float pre_axis_speed[MAX_AXIS];
    if (!rb_is_empty(&rb)) {
        float jerk = sqrt(_sq(axis_speed[X_AXIS] - pre_axis_speed[X_AXIS]) + _sq(axis_speed[Y_AXIS] - pre_axis_speed[Y_AXIS]));
        vmax_juncton = block->norminal_speed;
        if (jerk > para.motion.jerk_xy) {
            vmax_juncton_factor = para.motion.jerk_xy / jerk;
        }
        if (_abs(axis_speed[Z_AXIS] - pre_axis_speed[Z_AXIS]) > para.motion.jerk_z) {
            vmax_juncton_factor = min(vmax_juncton_factor, para.motion.jerk_z / _abs(axis_speed[Z_AXIS] - pre_axis_speed[Z_AXIS]));
        }
        if (_abs(axis_speed[E1_AXIS] - pre_axis_speed[E1_AXIS]) > para.motion.jerk_e) {
            vmax_juncton_factor = min(vmax_juncton_factor, para.motion.jerk_e / _abs(axis_speed[E1_AXIS] - pre_axis_speed[E1_AXIS]));
        }
        vmax_juncton = min(pre_nominal_speed, vmax_juncton * vmax_juncton_factor);
    }
    block->maxEntrySpeed = vmax_juncton;
    float v_allowAble = dis_acc_2_speed(para.motion.endSpeed, block->millimeters, block->acceleration);
    block->entrySpeed = min(vmax_juncton, v_allowAble);
    //
    pre_nominal_speed = block->norminal_speed;
    memcpy(pre_axis_speed, axis_speed, sizeof(pre_axis_speed));
// 
//------------------------------------------
//  13. 置标志位
    block->norminal_length = (block->norminal_speed <= v_allowAble) ? (true) : (false);
    block->recalculate   = true;
    block->entrylockFlag = false;
// 
//------------------------------------------
//  14. 加减速梯形计算
    calculateTrapezoid(block, block->entrySpeed/block->norminal_speed, 
                              safe_speed/block->norminal_speed);  
// 
//------------------------------------------
//  15. 加入环形内存
    rb_insertIndex(&rb);
// 
//------------------------------------------
//  16. 重新计算加减速梯形
    planner_reverse_pass();
    planner_forward_pass();
    recalculate_trapezoids();
// 
//------------------------------------------
//  17. 触发脉冲
    trigger();
}
//
//===============================================================
// 重新计算加减速梯形
//===============================================================
void c_stepMoto::recalculate_trapezoids() {
    uint8 index = rb.head;
    ts_stepBlockRun *cur;
    ts_stepBlockRun *next = NULL;
    while (index != rb.tail) {
        cur = next;
        next = &block_buf[index];
        if (cur) {
             if (cur->recalculate || next->recalculate) {
                int32 final = calculateTrapezoid(cur, cur->entrySpeed/cur->norminal_speed, next->entrySpeed/cur->norminal_speed);
                final = final * cur->norminal_speed / cur->norminal_rate;
                if (final != next->entrySpeed) {
                    next->entrySpeed  = final;
                    next->recalculate = true;
                }
                cur->recalculate = false;
             }
        }
        index = rb_get_NextIndex(&rb, index);
    }
    if (next) {
        calculateTrapezoid(next, next->entrySpeed/next->norminal_speed, para.motion.endSpeed/next->norminal_speed);
        next->recalculate = false;
    }
}
//
//===============================================================
// 前个加速块加速距离不够，下一个块入口速度降为可以接应前个速度
// -->> check >>--
// pusu . . . ISR
// pre--cur--next
// 速度连接到下一个移动块
//===============================================================
void c_stepMoto::planner_forward_pass() {
    uint8 index = rb.head;
    ts_stepBlockRun *block[3] = {NULL, NULL, NULL};
    while (index != rb.tail) {
        block[0] = block[1];
        block[1] = block[2];
        block[2] = &block_buf[index];
        index = rb_get_NextIndex(&rb, index);
        if (block[0] == NULL) continue;
        planner_pass_kernel(block[0], block[1], block[2]);
}}
//===============================================================
// 反向检查 从最后推入堆的开始计算到输出执行中断
// --<< check <<--
// pusu . . . ISR
// pre--cur--next
// 速度连接到下一个移动块
//===============================================================
void c_stepMoto::planner_reverse_pass() {
    int8  index = rb.tail;  
    ts_stepBlockRun *block[3] = {NULL, NULL, NULL};
    while (index != rb.head) {
        index = rb_get_PreIndex(&rb, index);
        block[0] = block[1];
        block[1] = block[2];
        block[2] = &block_buf[index];
        if (block[0] == NULL) continue;
        if (!planner_pass_kernel(block[0], block[1], block[2])) {
            if (block[1]->entrySpeed != block[1]->maxEntrySpeed && !block[1]->entrylockFlag) {
                block[1]->entrySpeed  = block[1]->maxEntrySpeed;
                block[1]->recalculate = true;
            }
        }
    }
}
//
bool c_stepMoto::planner_pass_kernel(ts_stepBlockRun *pre, ts_stepBlockRun *cur, ts_stepBlockRun *next) {
    if (pre->entrySpeed < cur->maxEntrySpeed && !pre->norminal_length) {
        float entrySpeed = min(cur->maxEntrySpeed, dis_acc_2_speed(pre->entrySpeed, pre->millimeters, pre->acceleration));
        if (cur->entrySpeed != entrySpeed) {
            cur->entrySpeed  = entrySpeed;
            cur->recalculate = cur->entrylockFlag = true;
        }
        return true;
    }
    return false;
}
//
//===============================================================
// 触发起动
//===============================================================
void  c_stepMoto::trigger () {
    //
    //------------------------------------------
    //== 更新时间 
    motoIdleTimer = os_time_get();
    //
    //------------------------------------------
    if (!gcode.emergencyStop) {
        gcode.M17();
    }
    //
    //------------------------------------------
    //20. 启动block
    triggerStepBlock();
    //
    //------------------------------------------
    //19. 加载 position
    for (int i=0; i<MAX_AXIS; i++)  
        dev->posSteps[i] = dev->tarSteps[i];
}
//
//===============================================================
// 梯形加减速生成
// 生成:
//===============================================================
int32 c_stepMoto::calculateTrapezoid(ts_stepBlockRun *block, float entfactor, float extfactor) {
//---------------------------------------
//  1. 梯形波形成
    uint32 initial_rate = max(block->norminal_rate * entfactor, 120);
    uint32 final_rate   = max(block->norminal_rate * extfactor, 120);
    int32 acc_steps  = rate_acc_2_Steps(initial_rate, block->norminal_rate, block->accelerRate);
    int32 dec_steps  = rate_acc_2_Steps(final_rate,   block->norminal_rate, block->accelerRate);
    int32 normal_steps = block->stepEventCun - acc_steps - dec_steps;
//---------------------------------------
//  2. 脉冲个数不够，变化成只有加减速三角波
	if (normal_steps < 0){
        acc_steps = intersection_steps(initial_rate, final_rate, block->accelerRate, block->stepEventCun);
        acc_steps = boundary(acc_steps, 0, block->stepEventCun);
        normal_steps = 0;
    }
//
//---------------------------------------
//  3. 加载运行参数
    nvic.globalDisable();
    if (!block->busy) {
        block->accelerate_until     = acc_steps;
        block->decelerate_after     = acc_steps + normal_steps;
        block->accelerate_begin_rate= initial_rate;
        block->decelerate_end_rate  = final_rate;
    }
    nvic.globalEnable();
    return block->decelerate_end_rate;
//
//---------------------------------------
}
//
//===============================================================
// 到达不了最大速度 计算交叉 脉冲个数
// Xnormal        = (v2^2-v0^2)/2a  正常加速脉冲数
// Xintersections = 0.5*eventCun + 0.5Xnormal
//===============================================================
int32 c_stepMoto::intersection_steps(uint32 initRate, uint32 tarRate, float acc, uint32 eventCun){
    if (acc==0) return 0;
    
    return ((2.0*acc*eventCun + tarRate*tarRate - initRate*initRate)/(4.0*acc));
}
//
//===============================================================
// 通过 两点速度和加速度，计算脉冲步数
// x = (v2^2-v0^2)/2a
//===============================================================
int32 c_stepMoto::rate_acc_2_Steps(uint32 initRate, uint32 tarRate, float acc){
    if (acc == 0.0) return 0;
    //
    return (tarRate*tarRate - initRate*initRate)/(2*acc);
}
//
//===============================================================
// 通过 加速度，n 脉冲后的 速度
// x = (v2^2-v0^2)/2a
// v2 = sqrt(2a*x + v0^2)
//===============================================================
int32 c_stepMoto::steps_acc_2_rate(uint32 initRate, uint32 steps, float acc){
    if (acc == 0.0) return 0;
    return sqrt(2*acc*steps + initRate*initRate);
}
//
//===============================================================
// 通过 加速固定行程后得到的最大速度
// x = (v2^2-v0^2)/2a
// v2 = sqrt(2a*x + v0^2)
//===============================================================
float c_stepMoto::dis_acc_2_speed(float speed_v0, float millimeter, float acc){
    if (acc == 0.0) return 0;
    return sqrt(2*acc*millimeter + _sq(speed_v0));
}
//
//=========================================


