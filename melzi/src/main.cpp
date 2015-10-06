/*=============================================================================================
\mainpage Repetier-Firmware for Arduino based RepRaps
<CENTER>Copyright &copy; 2011-2013 by repetier
</CENTER>

\section Intro Introduction


\section GCodes Implemented GCodes

 look here for descriptions of gcodes: http://linuxcnc.org/handbook/gcode/g-code.html
 and http://objects.reprap.org/wiki/Mendel_User_Manual:_RepRapGCodes

Implemented Codes

- G0  -> G1
- G1  - Coordinated Movement X Y Z E
- G4  - Dwell S<seconds> or P<milliseconds>
- G20 - Units for G0/G1 are inches.
- G21 - Units for G0/G1 are mm.
- G28 - Home all axis or named axis.
- G29 S<0..2> - Z-Probe at the 3 defined probe points. S = 1 measure avg. zHeight, S = 2 store avg zHeight
- G30 P<0..3> - Single z-probe at current position P = 1 first measurement, P = 2 Last measurement P = 0 or 3 first and last measurement
- G31 - Write signal of probe sensor
- G32 S<0..2> P<0..1> - Autolevel print bed. S = 1 measure zLength, S = 2 Measue and store new zLength
- G90 - Use absolute coordinates
- G91 - Use relative coordinates
- G92 - Set current position to cordinates given
- G131 - set extruder offset position to 0 - needed for calibration with G132
- G132 - calibrate endstop positions. Call this, after calling G131 and after centering the extruder holder.

RepRap M Codes

- M104 - Set extruder target temp
- M105 - Read current temp
- M106 - Fan on
- M107 - Fan off
- M109 - Wait for extruder current temp to reach target temp.
- M114 - Display current position

Custom M Codes

- M20  - List SD card
- M21  - Init SD card
- M22  - Release SD card
- M23  - Select SD file (M23 filename.g)
- M24  - Start/resume SD print
- M25  - Pause SD print
- M26  - Set SD position in bytes (M26 S12345)
- M27  - Report SD print status
- M28  - Start SD write (M28 filename.g)
- M29  - Stop SD write
- M30 <filename> - Delete file on sd card
- M32 <dirname> create subdirectory
- M42 P<pin number> S<value 0..255> - Change output of pin P to S. Does not work on most important pins.
- M80  - Turn on power supply
- M81  - Turn off power supply
- M82  - Set E codes absolute (default)
- M83  - Set E codes relative while in Absolute Coordinates (G90) mode
- M84  - Disable steppers until next move,
        or use S<seconds> to specify an inactivity timeout, after which the steppers will be disabled.  S0 to disable the timeout.
- M85  - Set inactivity shutdown timer with parameter S<seconds>. To disable set zero (default)
- M92  - Set axisStepsPerMM - same syntax as G92
- M104 S<temp> T<extruder> P1 F1 - Set temperature without wait. P1 = wait for moves to finish, F1 = beep when temp. reached first time
- M105 X0 - Get temperatures. If X0 is added, the raw analog values are also written.
- M112 - Emergency kill
- M115- Capabilities string
- M116 - Wait for all temperatures in a +/- 1 degree range
- M117 <message> - Write message in status row on lcd
- M119 - Report endstop status
- M140 S<temp> F1 - Set bed target temp, F1 makes a beep when temperature is reached the first time
- M190 - Wait for bed current temp to reach target temp.
- M201 - Set max acceleration in units/s^2 for print moves (M201 X1000 Y1000)
- M202 - Set max acceleration in units/s^2 for travel moves (M202 X1000 Y1000)
- M203 - Set temperture monitor to Sx
- M204 - Set PID parameter X => Kp Y => Ki Z => Kd S<extruder> Default is current extruder. NUM_EXTRUDER=Heated bed
- M205 - Output EEPROM settings
- M206 - Set EEPROM value
- M207 X<XY jerk> Z<Z Jerk> E<ExtruderJerk> - Changes current jerk values, but do not store them in eeprom.
- M220 S<Feedrate multiplier in percent> - Increase/decrease given feedrate
- M221 S<Extrusion flow multiplier in percent> - Increase/decrease given flow rate
- M231 S<OPS_MODE> X<Min_Distance> Y<Retract> Z<Backlash> F<ReatrctMove> - Set OPS parameter
- M232 - Read and reset max. advance values
- M233 X<AdvanceK> Y<AdvanceL> - Set temporary advance K-value to X and linear term advanceL to Y
- M251 Measure Z steps from homing stop (Delta printers). S0 - Reset, S1 - Print, S2 - Store to Z length (also EEPROM if enabled)
- M280 S<mode> - Set ditto printing mode. mode: 0 = off, 1 = on
- M300 S<Frequency> P<DurationMillis> play frequency
- M303 P<extruder/bed> S<printTemerature> X0 - Autodetect pid values. Use P<NUM_EXTRUDER> for heated bed. X0 saves result in EEPROM.
- M320 - Activate autolevel
- M321 - Deactivate autolevel
- M322 - Reset autolevel matrix
- M340 P<servoId> S<pulseInUS> : servoID = 0..3, Servos are controlled by a pulse with normally between 500 and 2500 with 1500ms in center position. 0 turns servo off.
- M350 S<mstepsAll> X<mstepsX> Y<mstepsY> Z<mstepsZ> E<mstepsE0> P<mstespE1> : Set microstepping on RAMBO board
- M400 - Wait until move buffers empty.
- M401 - Store x, y and z position.
- M402 - Go to stored position. If X, Y or Z is specified, only these coordinates are used. F changes feedrate fo rthat move.
- M500 Store settings to EEPROM
- M501 Load settings from EEPROM
- M502 Reset settings to the one in configuration.h. Does not store values in EEPROM!
- M908 P<address> S<value> : Set stepper current for digipot (RAMBO board)
==============================================================================================*/
#include "m_include.h"
//----------------------------------------------------
// 任务堆栈
__align(8)uint16  main_loop_stk     [0x200];
__align(8)uint16  lcdStk            [0x200];
__align(8)uint16  sdReaderStk       [0x200];
__align(8)uint16  commuStk          [0x200];
__align(8)uint16  gcodeStk          [0x200];
bool mainTaskRunEnable = false;
char debugOut = DEBUG_AUTO_LEAVER;
//
//===============================================================
// 协调同步启动
//===============================================================
char taskRunEnable(void) {
    if (!commu.taskRunEnable    )    return false;
    if (!lcd.taskRunEnable      )    return false;
    if (!sdReader.taskRunEnable )    return false;
    if (!mainTaskRunEnable      )    return false;
    if (!gcode.taskRunEnable    )    return false;
    return true;
}
//
//===============================================================
// 主循环任务
//===============================================================
__task void mainLoopTask(void) {
    static uint32 buzzerTimer;
    static uint32 tempTimer;
    static uint32 enterTimer;
    static bool   enterTriFlag;
    static bool   laserTriFlag;
    
    gpio.pinMode(PIN_END1_FAN, OUTPUT);
    gpio.pinMode(PIN_END2_FAN, OUTPUT);
    mainTaskRunEnable = true;
    while (taskRunEnable() == false) os_dly_wait(1);
while (1) {
    //
    //===========================================================   
    // 激光控制
    if (lcd.laserModle == false) {
        if (laserTriFlag == true) {
            stepMoto.dev->fanSpeed = 0;
            laserTriFlag = false;
        }
    } else {
        if (laserTriFlag == false) {
            gcode.G28();
            laserTriFlag = true;
            gcode.moveAbs (0, 0, para.printer.laserFocus, 0, para.motion.maxSpeed[X_AXIS]/2);
            for (int i=0; i<MAX_AXIS; i++) {
                gcode.targetPos[i] = gcode.currentPos[i];
            }
        }
    }
    //
    //===========================================================   
    // 温度控制
    if ((os_time_get() - tempTimer) > PID_DT) {
        tempHotBed .outManage ();
        tempHotEnd1.outManage ();
        if (lcd.laserModle == false) {
            tempHotEnd2.outManage ();
        }
        tempTimer = os_time_get();
    }
    //
    //===========================================================   
    // 电机空闲待机 
    if ((os_time_get() - stepMoto.motoIdleTimer > (uint32)(MOTO_IDLE_TIME*60000)) && 
        (stepMoto.dev->runningFlag == false)){
        stepMoto.motoIdleTimer = os_time_get();
        gcode.M84();
        gcode.printStartTime = 0;
    } 
    //
    //===========================================================   
    //== 蜂鸣器
    if (lcd.buzzerFlag) {
        if ((os_time_get() - buzzerTimer) > 50) {
            (lcd.buzzerFlag) ? (lcd.buzzerFlag--) : (lcd.buzzerFlag = 0);
            buzzerTimer = os_time_get();
        }
        gpio.digitalWrite(LCD_BUZZER_PIN, HIGH);
    } else {
        buzzerTimer = os_time_get();
        gpio.digitalWrite(LCD_BUZZER_PIN, LOW);
    }
    //
    //===========================================================   
    //== enter 按键
    if (gpio.digitalRead(LCD_ENCODENT) == HIGH) {
        if (((os_time_get() - enterTimer) > 100) && (enterTriFlag == false)){
            lcd.encoderEnt = true;
            lcd.buzzerFlag = 2;
            enterTriFlag   = true;
            os_sem_send(&lcd.sem_lcd);
        }
    } else {
        enterTimer   = os_time_get();
        enterTriFlag = false;
    }
    //
    //===========================================================   
    //== reset 按键
    static uint32 resetTimer = 0;
    static bool   pauseTriFlag = false;
    static bool   resetTriFlag = false;
    if (gpio.digitalRead(LCD_RESET_PIN) == LOW) {
        if (((os_time_get() - resetTimer) > 200) && (pauseTriFlag == false)){
            pauseTriFlag   = lcd.pauseFlag = true;
            lcd.buzzerFlag = 4;
        }
        if (((os_time_get() - resetTimer) > 5000) && (resetTriFlag == false)){
            resetTriFlag   = lcd.resetFlag = true;
            lcd.buzzerFlag = 10;
            gcode.stop();
        }
    } else {
        resetTimer   = os_time_get();
        pauseTriFlag = resetTriFlag = false;
    }
    //
    //===========================================================   
    //
    os_dly_wait(20);    
}
}
//
//===============================================================
// Idle 默认任务做为最低级服务程序
/* The idle demon is a system task, running when no other task is ready */
/* to run. The 'os_xxx' function calls are not allowed from this task.  */
//===============================================================
#ifdef __cplusplus
extern "C" {
#endif
__task void os_idle_demon (void) {
for (;;) {
    //
    //===========================================================
    //== 各个任务内存消耗 0%-100%
    int i;
    for (i=2; main_loop_stk[i]==0; i++);
    lcd.sysStatus.mainLoopStkP = (sizeof(main_loop_stk) - i*2)*100 / sizeof(main_loop_stk);
    for (i=2; sdReaderStk[i]==0; i++);
    lcd.sysStatus.sdReaderStkP = (sizeof(sdReaderStk) - i*2)*100   / sizeof(sdReaderStk);
    for (i=2; commuStk[i]==0; i++);
    lcd.sysStatus.commuStkP    = (sizeof(commuStk) - i*2)*100      / sizeof(commuStk);
    for (i=2; gcodeStk[i]==0; i++);
    lcd.sysStatus.gcodeStkP    = (sizeof(gcodeStk) - i*2)*100      / sizeof(gcodeStk);  
    for (i=2; lcdStk[i]==0; i++);
    lcd.sysStatus.lcdStkP      = (sizeof(lcdStk) - i*2)*100        / sizeof(lcdStk);
    //
    //===========================================================   
    //== 加热头风扇控制 温度高于起动是起动风机
    if ((tempHotEnd1.getTemperature() > FAN_END1_START) || lcd.laserModle) {
        gpio.digitalWrite(PIN_END1_FAN, (PIN_END1_FAN_ACTIVE == HIGH) ? (HIGH) : (LOW));
    } else {                                               
        gpio.digitalWrite(PIN_END1_FAN, (PIN_END1_FAN_ACTIVE == HIGH) ? (LOW) : (HIGH));
    }
    //
    //===========================================================   
    //== 物料冷却风扇
    if ((stepMoto.dev->fanSpeed) && (lcd.laserModle == false)) {
        gpio.digitalWrite(PIN_DO2, HIGH);
    } else {
        gpio.digitalWrite(PIN_DO2, LOW);
    }  
    //
    //===========================
    // 系统时钟
    sysTimer = os_time_get();
}
}
void os_tmr_call (U16 info) {
}
#ifdef __cplusplus
}
#endif
//
//===============================================================
// 操作系统启动初始化
// os_idle_demon 高一级别任务
//===============================================================
__task void init_task(void) {
//
//--------------------------------------
//  测试引脚
    gpio.pinMode(testPin, OUTPUT);
//     dac.init    (testDac);
//
//--------------------------------------
//  usb 标准任务，起动 setSem
    serialCommu.setSem();
    serialCommu.begin();
//
//--------------------------------------
//== sd 卡初始化起动
    sdReader.init();
//
//--------------------------------------
//== ADC 初始化
    adc.initCh(PIN_AI1, ADC_FACTOR_32);
    adc.initCh(PIN_AI2, ADC_FACTOR_32);
    adc.initCh(PIN_AI3, ADC_FACTOR_32);
    adc.initCh(AUTO_LEAVER_PIN, ADC_FACTOR_4);
    adc.start ();
//
//------------------------------------
//  建立任务 越前面优先级越低
    os_tsk_create_user(lcdTask,      2,    lcdStk,          sizeof(lcdStk)          );
    os_tsk_create_user(mainLoopTask, 3,    main_loop_stk,   sizeof(main_loop_stk)   );
    os_tsk_create_user(sdReaderTask, 4,    sdReaderStk,     sizeof(sdReaderStk)     );
    os_tsk_create_user(commuTsk,     5,    commuStk,        sizeof(commuStk)        );
    os_tsk_create_user(gcodeTsk,     6,    gcodeStk,        sizeof(gcodeStk)        );
    os_tsk_delete_self();
}
//
//===============================================================
// 主程序
//===============================================================ADC1
boolean EEp_init_flag = 1;
int main(void) {
//
//--------------------------------------
//-- 串口初始化  
    serialDebug.begin(115200);
//
//--------------------------------------
//-- EEprom 调取参数
     if (EEP.data.ver==0 || EEp_init_flag==0)  
			 eep.wirte((uint8 *)&EEP_DF, (uint32)&EEP, sizeof(para));
     memCopy((char *)&para, (char *)&EEP, sizeof(para));
//
//--------------------------------------
//== 操作系统启动
    os_sys_init(init_task);
//
//--------------------------------------
}
//===============================================================


