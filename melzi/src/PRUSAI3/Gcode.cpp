//======================================================================
/*  
maker  ：jiaxing.shen
date   ：2014.12.10
email  ：55954781@qq.com
*/
//======================================================================
#include "m_include.h"
#include "Gcode.h"
//======================================================================
__task void gcodeTsk() {
    gcode.calculateDeltaPara();
    gcode.multiply = 100;
    //
    //================================
    //== 邮箱初始化
    stepMoto.initMbx();
    //
    //================================
    //== 
    gcode.setCurPos (0, 0, 0, 0);
    gcode.taskRunEnable = true;
    while (taskRunEnable() == false) os_dly_wait(1);
    while (1) {
        gcode.loop();
    }
}
//
//======================================================================
// 循环
//======================================================================
void c_gcode::loop() {
//----------------------------------------
// 得到 GCODE 
    commu.getGcodeLock(&buf);
//
//----------------------------------------
//  执行 G code
    if (buf.params.bits.G_V2_R) {
        switch (buf.G) {
            case 0  :
            case 1  :   G0_G1();    break;  // 线性运动
            case 2  :
            case 3  :   G2_G3();    break;  // G2 G3 圆形插补
            case 4  :   G4   ();    break;  // 等待一个设定时间
            case 28 :   G28  ();    break;  // 归原点
            case 29 :   G29  ();    break;  // 自动调平
            case 90 :   G90  ();    break;  // 绝对坐标模式
            case 91 :   G91  ();    break;  // 相对坐标模式
            case 92 :   G92  ();    break;  // 设定当前坐标
            default : break;
        }
    }
//
//----------------------------------------
//  执行 M code
    if (buf.params.bits.M_V2_J) {
        switch (buf.M) {
            case 0  :
            case 1  :   M0_M1();    break;  // 条件等待延时
            case  84:   M84();      break;  // 停止所有电机
            case  17:   M17();      break;  // 电机开启
            case 104:   M104();     break;  // 设定温度值
            case 140:   M140();     break;  // 设定温度值
            case 106:   M106();     break;  // 开启风扇
            case 107:   M107();     break;  // 关闭风扇
            case 109:   M109();     break;  // 等待温度到
            case 303:   M303();     break;  // 自整定PID 值
            // sd
            case 20:    M20();      break;  // 列出文件目录
            case 21:    M21();      break;  // 初始化SD卡
            case 22:    M22();      break;  // 拔出 SD卡
            case 24:    M24();      break;  // 启动 SD 卡打印
            case 25:    M25();      break;  // 停止 SD 卡打印
            case 27:    M27();      break;  // 报告 SD 打印状态
            default:                break;
        }
    }
}
//
//======================================================================
//  关闭风扇
//  生成：
//======================================================================
void c_gcode::M107 () {
    stepMoto.dev->fanSpeed = 0;
}
//
//======================================================================
//  开启风扇
//  生成：
//======================================================================
void c_gcode::M106 () {
    if (lcd.laserModle == true) {
        stepMoto.waitFinish();
        tempHotEnd2.setOut(tempHotEnd2.outMax);
        os_dly_wait(para.printer.laserDelay);
        stepMoto.dev->fanSpeed = 127;
    } else {
        stepMoto.dev->fanSpeed = buf.S;
    }
}
//
//======================================================================
//  条件等待延时
//  生成：
//======================================================================
void c_gcode::M0_M1() {
    uint32 delayCun = 0;
    //
    //----------------------------------------
    // 1. 设定定时时间
    if (buf.params.bits.P) {
        delayCun = buf.P;
    } else if (buf.params.bits.S) {
        delayCun = buf.S * 1000;
    }
    //
    //----------------------------------------
    // 2. 定时
    stepMoto.waitFinish();
    uint32 delayTime = os_time_get();
    G4Wait = true;
    if (delayCun == 0) {
        while (gpio.digitalRead(LCD_ENCODENT) != LCD_ENCODENT_ACT) 
            os_dly_wait(5);
    } else {
        while ((os_time_get() - delayTime) < delayCun)  {
            if (gpio.digitalRead(LCD_ENCODENT) == LCD_ENCODENT_ACT)
                break;
            os_dly_wait(5);
        }
    }
}
//
//======================================================================
//  电机开启
//  生成：
//======================================================================
void c_gcode::M17() {
    if (emergencyStop) return;
    for (int i=0; i<MAX_AXIS; i++) {
        gpio.digitalWrite(stepMoto.dev->pinTab[i].enable, stepMoto.dev->pinAct[i].enable);
    }
}
//
//======================================================================
//  应急停止
//  生成：
//======================================================================
void c_gcode::stop() {
    nvic.globalDisable();
    emergencyStop = true;
    M25();  // sd 卡停止打印
    for (int i=0; i<MAX_AXIS; i++) {
        gpio.digitalWrite(stepMoto.dev->pinTab[i].enable, !stepMoto.dev->pinAct[i].enable);
    }
    nvic.globalEnable();
}
//
//======================================================================
//  设定速度倍率
//  生成：
//======================================================================
void c_gcode::M220(void) {
    if (buf.params.bits.S) 
        multiply = buf.S;
}
//
//======================================================================
//  停止所有电机
//  生成：
//======================================================================
void c_gcode::M84(void) {
    stepMoto.waitFinish();
    for (int i=0; i<MAX_AXIS; i++) {
        gpio.digitalWrite(stepMoto.dev->pinTab[i].enable, (stepMoto.dev->pinAct[i].enable == HIGH) ? (LOW) : (HIGH));
    }
}
//
//======================================================================
//  启动 SD 卡打印
//  生成：
//======================================================================
void c_gcode::M24() {
    sdReader.setStartPrint(true);
    printStartTime = os_time_get();
}
//
//======================================================================
//  列出文件目录
//  生成：
//======================================================================
void c_gcode::M20() {
    serialCommu.println("Begin file list");
    sdReader.ls();
    serialCommu.println("End file list");
}
//
//======================================================================
//  设定当前坐标
//  生成：
//======================================================================
void c_gcode::G92() {
    if (!buf.params.bits.E) stepMoto.waitFinish();
    else                    {setCurrentPos(E1_AXIS, buf.Axis[E1_AXIS]); targetPos[E1_AXIS] = buf.Axis[E1_AXIS];}
    //
    if (buf.params.bits.X)  {setCurrentPos(X_AXIS,  buf.Axis[X_AXIS]);  targetPos[X_AXIS]  = buf.Axis[X_AXIS];}
    //
    if (buf.params.bits.Y)  {setCurrentPos(Y_AXIS,  buf.Axis[Y_AXIS]);  targetPos[Y_AXIS]  = buf.Axis[Y_AXIS];}
    //
    if (buf.params.bits.Z)  {setCurrentPos(Z_AXIS,  buf.Axis[Z_AXIS]);  targetPos[Z_AXIS]  = buf.Axis[Z_AXIS];}
}
//
//======================================================================
//  设定加热头温度
//  生成：
//======================================================================
void c_gcode::M109() {
    uint32  keepTime = os_time_get();
    boolean heatingFlag = tempHotEnd1.getTarTemperature() > tempHotEnd1.getTemperature();
    boolean trigFlag = 0;
    status = egcode_status_heat;
    M109Wait = true;
    tempHotEnd1.setTarTemp(buf.S);
    serialCommu.println("M109 waitting begin!");
    while (1) {
        //
        //-- 触发计时
        if (heatingFlag  && tempHotEnd1.getTemperature() > (tempHotEnd1.getTarTemperature() - TEMP_RESIDENCY_T_WIN)) { 
            trigFlag = true;
        } else if (!heatingFlag && tempHotEnd1.getTemperature() < (tempHotEnd1.getTarTemperature() + TEMP_RESIDENCY_T_WIN)) {
            trigFlag = true;
        }
        //
        //-- 计时
        if ((trigFlag == false) || abs(tempHotEnd1.getTarTemperature() - tempHotEnd1.getTemperature()) > TEMP_RESIDENCY_WIN){
            keepTime = os_time_get();
        } else if (os_time_get() - keepTime > TEMP_RESIDENCY_TIME*1000) {
            break;
        }
        //
        //-- M80 退出
        if (M109Wait == false) {
            break;
        }
        //-- print temp
        showTemperature();
        stepMoto.motoIdleTimer = os_time_get();
        os_dly_wait(10);
    }
    serialCommu.println("M109 waitting finish!");
    printStartTime = os_time_get();
    status = egcode_status_idle;

    serialCommu.print("ok ");
    serialCommu.println((uint16_t)buf.N);
}
//
//======================================================================
//  自整定PID 值
//  生成：
//======================================================================
void c_gcode::M303() {
    tempHotEnd1.pidAutoTune(buf.S, buf.C); 
}   
//
//======================================================================
//  显示温度值
//  生成：
//======================================================================
void c_gcode::showTemperature() {
    static uint32 showTime = os_time_get();
    if (os_time_get() - showTime < 900) return;
    showTime = os_time_get();
    serialCommu.print(" T:");      serialCommu.print  (tempHotEnd1.getTemperature(),    1);
    serialCommu.print(" /"   );    serialCommu.print  (tempHotEnd1.getTarTemperature(), 1);
    serialCommu.print(" B:");      serialCommu.print  (tempHotBed.getTemperature(),     1);
    serialCommu.print(" /"   );    serialCommu.print  (tempHotBed.getTarTemperature(),  1);
    serialCommu.print(" @:"   );   serialCommu.print (tempHotEnd1.getOut());
    serialCommu.print(" B@:"   );  serialCommu.println(tempHotBed.getOut() );
}
//
//======================================================================
//  设定当前坐标
//  生成：
//======================================================================
void c_gcode::setCurPos(float x, float y, float z, float e) {
    float deltaT[MAX_AXIS];
    currentPos[X_AXIS ] = targetPos[X_AXIS ] = x;
    currentPos[Y_AXIS ] = targetPos[Y_AXIS ] = y;
    currentPos[Z_AXIS ] = targetPos[Z_AXIS ] = z;
    currentPos[E1_AXIS] = targetPos[E1_AXIS] = e;
    calculateDelta(gcode.currentPos, deltaT);
    stepMoto.setPosSteps(deltaT); 
}
//
//======================================================================
//  自动调平探测
//  生成 检测到的由于探测开关引起的差值
//======================================================================
float c_gcode::G29_Detect(float x, float y, float rate) {
    float diff[3], sum = 0;
    stepMoto.waitFinish();
    stepMoto.clearLimitF();
    pressDetectFlag = false;
    moveAbs(x, y, AUTO_LEAVER_DETECT_H, 0, rate);
    stepMoto.waitFinish();
    // 三次探测平均值
    for (char i=0; i<3; i++) {
        if (G29Wait == false) return 0;
        //==============================
        //== 向下探测 15mm
        pressDetectFlag = true;
        moveAbs(x, y, -5, 0, 2);
        stepMoto.waitFinish();
        diff[i] = stepMoto.getPosZmm() - stepMoto.getRealZmm();
        stepMoto.clearLimitF();
        setCurPos(x, y, -5 - diff[i], 0);
        //==============================
        //== 向下探测 复位
        pressDetectFlag = false;
        moveAbs(x, y, -5 - diff[i] + 0.5, 0, rate);
        stepMoto.waitFinish();
        os_dly_wait(150);    // 等待 AD 稳定
    }
    sum  = max(diff[0], max(diff[1], diff[2]));
    sum += min(diff[0], min(diff[1], diff[2]));
    if (debugOut == DEBUG_AUTO_LEAVER) {
        serialDebug.vprintf("Detect1:%2.2f Detect2:%2.2f Detect3:%2.2f \r\n", diff[0], diff[1], diff[2]);
    }
    return (diff[0] + diff[1] + diff[2] - sum);
}
//
//======================================================================
//  调整 R 值，调整为线性
//  生成
//======================================================================
float c_gcode::G29_Liner (float x, float y, float rate, float *pN, float *pP) {
    float radius = para.printer.deltaRadius, adj=0, zero;
    float bestpN, bestpP, bestAdj, minDis = 10000;
    float dis1, dis2;
    //
    for (uint8 i=0; i<10; i++) {
        if (G29Wait == false)                                     return 0xffff;
        if ((zero  = G29_Detect (0,      0, rate))        == 0)   return 0xffff;
        if ((*pP   = G29_Detect(  x,     y, rate) - zero) == 0)   return 0xffff;
        if ((*pN   = G29_Detect(-(x), -(y), rate) - zero) == 0)   return 0xffff;
        if (abs(*pP + *pN) < minDis) {  // 记录最好
            bestpN  = *pP;   bestpP = *pN;
            minDis  = abs(*pP + *pN);
            bestAdj = adj;
            if (minDis < 0.05) break;
        }            
        //== 加1%探测值
        if (i==0)    { dis1 = *pP+*pN; adj  = 1.0;
        } else       { dis2 = *pP+*pN; adj = (abs(dis1)*adj/abs(dis1-dis2) + adj)/2;}
        (dis1 < 0.0) ? (adj = abs(adj)) : (adj = -abs(adj));
        para.printer.deltaRadius = radius + radius * adj/100;
        calculateDeltaPara();
    }
    para.printer.deltaRadius = radius;
    calculateDeltaPara();
    *pN = bestpN; *pN = bestpP;
    return  bestAdj;
}

//
//======================================================================
//  自动调平
//  生成：
//======================================================================
void c_gcode::G29 () {
    float feedrateT = 100;
    AutoLevEnable             = false;
    disAdjustEnable			  = false;
    para.adjust.autoLevCeManu = 0;
    para.adjust.autoLevYManu  = 0;
    para.adjust.autoLevXManu  = 0;
    G29Wait = true;
//
//-----------------------------------------
//  1. 归原点
    uint32	sum = 0;
    for (int i=0; i<100; i++) {	
        sum += adc.loopGetData(AUTO_LEAVER_PIN);
    }
    sensitivityNor = sum / 100;
    sensitivityMax = sensitivityNor + para.adjust.autoLevSentive;
    G28();
    moveAbs(0, 0, para.adjust.autoLevBegin, 0, feedrateT);
    stepMoto.waitFinish();
//
//-----------------------------------------
//  2. 探测当前打印机高度
    pressDetectFlag = true;
    moveAbs(0, 0, -50, 0, 2);
    stepMoto.waitFinish();
    setCurPos(0, 0, 0, 0);
//
//-----------------------------------------
//  2. 半径修正 修正打印平面 凹凸面
    float xP, xN, xAdj;
    float yP, yN, yAdj;
    xAdj = G29_Liner (para.printer.max_pos_x, 0, feedrateT, &xP, &xN);
    yAdj = G29_Liner (0, para.printer.max_pos_y, feedrateT, &yP, &yN);
    if (xAdj==0xffff || yAdj==0xffff) {
        pressDetectFlag = false;
        return;
    }
    para.printer.deltaRadius  += para.printer.deltaRadius * (xAdj+yAdj)/200;
    para.adjust.autoLevCeManu = 0;
    calculateDeltaPara();
//
//-----------------------------------------
//  3. 调平系数计算
    deltaPara.autoLevX = para.adjust.autoLevXG29 = (xP-xN)/para.printer.max_pos_x/2;
    deltaPara.autoLevY = para.adjust.autoLevYG29 = (yP-yN)/para.printer.max_pos_y/2;
//
//-----------------------------------------
//  4. Z自动
    moveAbs(0, 0, AUTO_LEAVER_DETECT_H, 0, feedrateT);
    G28();
    float HOME_Z = stepMoto.getPosZmm ();
    pressDetectFlag = false;
    moveAbs(0, 0, para.adjust.autoLevBegin, 0, feedrateT/2);
    stepMoto.waitFinish();
    pressDetectFlag = true;
    moveAbs(0, 0, -50, 0, 2);
    stepMoto.waitFinish();
    float ZERO_Z = stepMoto.getRealZmm();
    para.printer.z_home = HOME_Z-ZERO_Z-0.2;
    setCurPos(0, 0, 0, 0);
    stepMoto.clearLimitF();
    pressDetectFlag = false;
    moveAbs(0, 0, 10, 0, feedrateT/5);
//-----------------------------------------
// 5. 数据存储
    lcd.function_storeEprom();
    pressDetectFlag = false;
    AutoLevEnable   = true;
    disAdjustEnable = true;
}
//
//======================================================================
//  设定当前坐标
//  生成：
//======================================================================
void c_gcode::setCurrentPos(uint8 axis, float value) {
    currentPos[axis] = value;
    stepMoto.setPosSteps(axis, value);
}
//
//======================================================================
//  G2 G3 圆形插补
//  生成：
//======================================================================
void c_gcode::G2_G3() {
    float tarPosT[MAX_AXIS];
//---------------------------------------
//  1.坐标
    getCoordinates(tarPosT);
//
//----------------------------------------
//  2.参数赋值
    centerX = currentPos[X_AXIS] + buf.I;                   // 圆心X
    centerY = currentPos[Y_AXIS] + buf.J;                   // 圆心Y
    linearTravel  = tarPosT[Z_AXIS]  - currentPos[Z_AXIS];   
    extrudeTravel = tarPosT[E1_AXIS] - currentPos[E1_AXIS];
    rAxisX  = -buf.I;                       rAxisY  = -buf.J;
    rtAxisX =  tarPosT[X_AXIS] - centerX;   rtAxisY =  tarPosT[Y_AXIS] - centerY;
//
//----------------------------------------
//  3.圆弧夹角
    angular_travel = atan2(rAxisX*rtAxisY - rAxisY*rtAxisX, rAxisX*rtAxisX + rtAxisY*rtAxisY);
    if (angular_travel < 0) angular_travel += 2*PI;
    if (buf.G == 2)     // 顺逆时针
        angular_travel -= 2*PI;
//
//----------------------------------------
//  4.整圆
    if (currentPos[X_AXIS] == tarPosT[X_AXIS] && currentPos[Y_AXIS] == tarPosT[Y_AXIS] && angular_travel == 0) {
        angular_travel = 2*PI;
    }
//
//----------------------------------------
//  5.路径距离
    float millimeters = hypot(angular_travel * hypot(buf.I, buf.J), linearTravel);
    if (millimeters < 0.001) return;
    int segments = floor(millimeters / DELTA_SEGMENTS_MM);
    segments = max(segments, 1);
    angular_travel /= segments;
//
//----------------------------------------
//  6.分片
    float deltaT  [MAX_AXIS];
    float tarPosTT[MAX_AXIS];
    for (int i=0; i<segments; i++) {
        cosSegment = cos(i * angular_travel);
        sinSegment = sin(i * angular_travel);
        tarPosTT[X_AXIS] = centerX + sinSegment*buf.J - cosSegment*buf.I;
        tarPosTT[Y_AXIS] = centerY - sinSegment*buf.I - cosSegment*buf.J;
        tarPosTT[Z_AXIS]  += linearTravel /segments;
        tarPosTT[E1_AXIS] += extrudeTravel/segments;
        softLimit(tarPosT);
        calculateDelta(tarPosTT, deltaT);
		stepMoto.move (deltaT, feedrate);
    }
//
//----------------------------------------
//  7.current pos 更新
    setDest2current(tarPosT);
}
//
//======================================================================
//  G4 定时时间
//  生成：
//======================================================================
void c_gcode::G4() {
    uint32 delayCun = 0;
    //
    //----------------------------------------
    // 1. 设定定时时间
    if (buf.params.bits.P) {
        delayCun = buf.P;
        if (lcd.laserModle == true)
            delayCun *= 1000;
    } else if (buf.params.bits.S) {
        delayCun = buf.S * 1000;
    }
    //
    //----------------------------------------
    // 2. 定时
    stepMoto.waitFinish();
    uint32 delayTime = os_time_get();
    G4Wait = true;
    while ((os_time_get() - delayTime) <= delayCun) {
        if (G4Wait == false)
            break;
        os_dly_wait(5);
    }
}
//
//======================================================================
//  G28 回原点
//  生成：
//======================================================================
void c_gcode::G28() {
//-----------------------------------------
// 1. 保存环境
    feedrateSave = feedrate;
    float feedRateT = 3000;
    emergencyStop = false;
//
//-----------------------------------------
// 2. 快速回原点
    setCurPos(0, 0, 0, 0);
    if (stepMoto.getMaxLimitF(1, 1, 1) == false) {
        stepMoto.clearLimitF();
        moveAbs  (0, 0, 1.2 * para.printer.z_home, 0, feedRateT);
        stepMoto.waitFinish();
    }
    os_dly_wait(200);
//
//-----------------------------------------
// 3. 满速检测
    float stepCurPos[MAX_AXIS];
    for (int i=0; i<MAX_AXIS; i++) {
        stepCurPos[i] = stepMoto.getPosSteps(i);
    }
    homeAxis(X_AXIS, feedRateT/4, stepCurPos);
    os_dly_wait(200);
    homeAxis(Y_AXIS, feedRateT/4, stepCurPos);
    os_dly_wait(200);
    homeAxis(Z_AXIS, feedRateT/4, stepCurPos);
    os_dly_wait(200);
    stepMoto.clearLimitF();
//
//-----------------------------------------
// 4. 设定值
    setCurPos(0, 0, para.printer.z_home, 0);
    feedrate = feedrateSave;
}
//
//======================================================================
//  回原点
//  生成：
//======================================================================
uint8 c_gcode::homeAxis(uint8 axis, float feedrateT, float *stepPos) {
    stepMoto.clearLimitF();
//---------------------------------------
//  2.回退20mm
    stepPos[axis] = stepPos[axis] - 20;
    stepMoto.move (stepPos, feedrateT);
    stepPos[axis] = stepPos[axis];
    stepMoto.waitFinish();
    stepMoto.clearLimitF();
//
//---------------------------------------
//  3.慢速检测
    stepPos[axis] = stepPos[axis] + para.printer.z_home;
    stepMoto.move (stepPos, feedrateT/2);
    stepPos[axis] = stepPos[axis];
    stepMoto.waitFinish();
    stepMoto.clearLimitF();
    return 0;
}
//
//======================================================================
//  G0 G1 执行直线运动
//  生成：
//======================================================================
void c_gcode::G0_G1() {
//---------------------------------------
//  1.坐标
    getCoordinates(targetPos);
//---------------------------------------
//  2.运行
    moveAbs (targetPos[X_AXIS], targetPos[Y_AXIS], targetPos[Z_AXIS], targetPos[E1_AXIS], feedrate);
}
//
//======================================================================
//  目标坐标放入当前坐标
//  生成：
//======================================================================
void c_gcode::setDest2current(float *tarPosT) {
    for (int i=0; i<MAX_AXIS; i++) {
        currentPos[i] = tarPosT[i];
    }
}
//
//======================================================================
//  生成绝对坐标
//  生成：
//  destination
//  feedrate
//======================================================================
void c_gcode::softLimit(float *tarPosT) {
//-----------------------------------
// 绝对值限制
    tarPosT[X_AXIS] = boundary (tarPosT[X_AXIS], para.printer.min_pos_x, para.printer.max_pos_x);
    tarPosT[Y_AXIS] = boundary (tarPosT[Y_AXIS], para.printer.min_pos_y, para.printer.max_pos_y);
    tarPosT[Z_AXIS] = boundary (tarPosT[Z_AXIS], 0, para.printer.z_home);
//
//-----------------------------------
}
//
//======================================================================
//  生成绝对坐标
//  生成：
//  destination
//  feedrate
//======================================================================
void c_gcode::getCoordinates(float *tarT) {
//-----------------------------------
//1. 得到坐标值
    if (lcd.laserModle == true) {
        if (buf.params.bits.X)  tarT[X_AXIS]  = buf.Axis[X_AXIS] + para.printer.laser_x_offset;
        if (buf.params.bits.Y)  tarT[Y_AXIS]  = buf.Axis[Y_AXIS] + para.printer.laser_y_offset;
        if (buf.params.bits.Z)  tarT[Z_AXIS]  = buf.Axis[Z_AXIS] + currentPos[Z_AXIS] *relativeFlag;
    } else {
        if (buf.params.bits.X)  tarT[X_AXIS]  = buf.Axis[X_AXIS] + currentPos[X_AXIS] *relativeFlag;
        if (buf.params.bits.Y)  tarT[Y_AXIS]  = buf.Axis[Y_AXIS] + currentPos[Y_AXIS] *relativeFlag;
        if (buf.params.bits.Z)  tarT[Z_AXIS]  = buf.Axis[Z_AXIS] + currentPos[Z_AXIS] *relativeFlag;
        if (buf.params.bits.E)  tarT[E1_AXIS] = buf.Axis[E1_AXIS]+ currentPos[E1_AXIS]*relativeFlag;
    }
//
//-----------------------------------
//3. 得到给进速度
    if (buf.F) {
        feedrate = buf.F / 60;
    }
//
//-----------------------------------
}

//======================================================================
//  相对坐标移动
//  生成：
//======================================================================
void c_gcode::moveRelative (float x, float y, float z, float e, float rateT) {
    moveAbs(currentPos[X_AXIS] + x, currentPos[Y_AXIS ] + y, 
            currentPos[Z_AXIS] + z, currentPos[E1_AXIS] + e, rateT);
}
//======================================================================
//  绝对坐标移动
//  生成：
//======================================================================
void c_gcode::moveAbs (float x, float y, float z, float e, float speed_S) {
    static float tarPos     [MAX_AXIS];
    static float delta_mm   [MAX_AXIS];
    static float deltaT     [MAX_AXIS]; 
    static float tarPos_S   [MAX_AXIS];
//
//---------------------------------------
//  1.目标值缓存
    os_mut_wait(&mut_gcode, 0xffff);
    tarPos[X_AXIS] = x; tarPos[Y_AXIS] = y; tarPos[Z_AXIS] = z; tarPos[E1_AXIS] = e; 
//
//---------------------------------------
//  2.分片
    for (int i=0; i<MAX_AXIS; i++) {
        delta_mm[i] = tarPos[i] - currentPos[i];
    }
    float cartesian_mm = max(max(_abs(delta_mm[X_AXIS]), _abs(delta_mm[Y_AXIS])), _abs(delta_mm[Z_AXIS]));
    if (cartesian_mm < 0.00001) {
        cartesian_mm = _abs(delta_mm[E1_AXIS]);
    }
    if (cartesian_mm < 0.00001) {
        os_mut_release(&mut_gcode);
        return;
    }
    int steps = max(1, cartesian_mm/5);
//
//---------------------------------------
//  3.分片DELTA运动
    float  fraction;
    for (int s=1; s<=steps; s++) {
          fraction = (float)s/(float)steps;
        for (int i=0; i<MAX_AXIS; i++) 
            tarPos_S[i] = currentPos[i] + fraction*delta_mm[i];
        calculateDelta(tarPos_S, deltaT);
        stepMoto.move (deltaT, speed_S);
    }
//
//---------------------------------------
//  4.current pos 更新
    for (int i=0; i<MAX_AXIS; i++) {
        currentPos[i] = tarPos_S[i];
    }
    os_mut_release(&mut_gcode);
}
//
//======================================================================
//  卡尔迪坐标 变化成 Delta 坐标
//  生成：
//  delta[X Y Z]
//  delta^2 = diagonal^2 - R2^2;
//  R2^2    = (towerX-X)^2 + (towerY-Y)^2
//======================================================================
void c_gcode::calculateDelta(float *cartesianT, float *deltaT) {
//
//-----------------------------------
// E直接赋值
    deltaT[E1_AXIS] = cartesianT[E1_AXIS];
//
//-----------------------------------
// 距离线性调整
    float distanctAdjustX, distanctAdjustY; 
	  if (disAdjustEnable) {
			(cartesianT[X_AXIS] >= 0.0) ? (distanctAdjustX = cartesianT[X_AXIS] * para.adjust.adjust_xp) :
																		(distanctAdjustX = cartesianT[X_AXIS] * para.adjust.adjust_xn) ;
			(cartesianT[Y_AXIS] >= 0.0) ? (distanctAdjustY = cartesianT[Y_AXIS] * para.adjust.adjust_yp) :
																		(distanctAdjustY = cartesianT[Y_AXIS] * para.adjust.adjust_yn) ;
		} else {
			distanctAdjustX = cartesianT[X_AXIS];
			distanctAdjustY = cartesianT[Y_AXIS];
		}
//
//-----------------------------------
// 自动调平调整
    float distanctAdjustZ;
    if (AutoLevEnable) {
        distanctAdjustZ = distanctAdjustX*deltaPara.autoLevX + distanctAdjustY*deltaPara.autoLevY + cartesianT[Z_AXIS];
    } else {
        distanctAdjustZ = cartesianT[Z_AXIS];
    }
//
//-----------------------------------
// delta 坐标转换
    deltaT[X_AXIS] = sqrt(deltaPara.diagonalRod2 - _sq(deltaPara.tower1X-distanctAdjustX) - _sq(deltaPara.tower1Y-distanctAdjustY))                      
                     + distanctAdjustZ;
    deltaT[Y_AXIS] = sqrt(deltaPara.diagonalRod2 - _sq(deltaPara.tower2X-distanctAdjustX) - _sq(deltaPara.tower2Y-distanctAdjustY))
                     + distanctAdjustZ;
    deltaT[Z_AXIS] = sqrt(deltaPara.diagonalRod2 - _sq(deltaPara.tower3X-distanctAdjustX) - _sq(deltaPara.tower3Y-distanctAdjustY))       
                     + distanctAdjustZ;
}
//
//======================================================================
// Delta 参数预计算
// 生成
// deltaPara.diagonalRod2
// deltaPara.diagonalRod
// deltaPara.radius
// deltaPara.tower#n#X
// deltaPara.tower#n#Y
//======================================================================
void c_gcode::calculateDeltaPara() {
//
//------------------------------------------
// 计算内3角形两边长
    deltaPara.diagonalRod2 = _sq(para.printer.deltaDiagonalRad);
//
//------------------------------------------
// 计算内3角形两边长
    float rAdj = para.printer.deltaDiagonalRad - sqrt(deltaPara.diagonalRod2 - _sq(para.adjust.autoLevCeManu));
    if (para.adjust.autoLevCeManu >= 0) {
        deltaPara.deltaRadius = para.printer.deltaRadius - rAdj;
    } else {
        deltaPara.deltaRadius = para.printer.deltaRadius + rAdj;
    }
    deltaPara.tower1X   = - SIN_60 * deltaPara.deltaRadius;
    deltaPara.tower1Y   = - COS_60 * deltaPara.deltaRadius;
    deltaPara.tower2X   =   SIN_60 * deltaPara.deltaRadius;
    deltaPara.tower2Y   = - COS_60 * deltaPara.deltaRadius;
    deltaPara.tower3X   =   0;
    deltaPara.tower3Y   =   deltaPara.deltaRadius; 
//
//------------------------------------------
// 调平修正值
    gcode.deltaPara.autoLevX = para.adjust.autoLevXG29 + para.adjust.autoLevXManu / para.printer.max_pos_x / 10;
    gcode.deltaPara.autoLevY = para.adjust.autoLevYG29 + para.adjust.autoLevYManu / para.printer.max_pos_y / 10;
}
//
//======================================================================
// 构建函数
//======================================================================
c_gcode::c_gcode() {
//
//------------------------------------------
//2. 水平调节 默认参数
    AutoLevEnable 	= true;
		disAdjustEnable = true;
    
}
//======================================================================
c_gcode gcode;
//
//======================================================================
