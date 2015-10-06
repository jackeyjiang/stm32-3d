/*======================================================================  
maker  :jiaxing.shen
date   :2014.12.10
email  :55954781@qq.com
======================================================================*/
#include "m_include.h"
#include "lcd.h"
#include "DOGMbitmaps.h"

#define LCD_CHAR_HEIGH  12
#define LCD_CHAR_WIDTH  6
/* Custom characters defined in font font_6x10_marlin.c */
extern  const u8g_fntpgm_uint8_t u8g_font_6x10_marlin[];
#define LCD_STR_BEDTEMP     "\xFE"
#define LCD_STR_DEGREE      "\xB0"
#define LCD_STR_THERMOMETER "\xFF"
#define LCD_STR_UPLEVEL     "\xFB"
#define LCD_STR_REFRESH     "\xF8"
#define LCD_STR_FOLDER      "\xF9"
#define LCD_STR_FEEDRATE    "\xFD"
#define LCD_STR_CLOCK       "\xFC"
#define LCD_STR_ARROW_RIGHT "\xFA"
//#define LCD_BLANK_SPACE   "01234567890123456789"
#define LCD_BLANK_SPACE     "                    "
//
//=================================================================================================
// 标签数据
// 只显示，不操作 action 为空函数
//=================================================================================================
menu_label_type(int, int3, itostr3)
menu_label_type(int, int4, itostr4)
#define drawmenu_label_int3_selected(row, pstr, pstr2, data)         drawmenu_edit_generic(row, pstr, '>', itostr3(*(data)))
#define drawmenu_label_int3(row, pstr, pstr2, data)                  drawmenu_edit_generic(row, pstr, ' ', itostr3(*(data)))
#define drawmenu_label_int4_selected(row, pstr, pstr2, data)         drawmenu_edit_generic(row, pstr, '>', itostr4(*(data)))
#define drawmenu_label_int4(row, pstr, pstr2, data)                  drawmenu_edit_generic(row, pstr, ' ', itostr4(*(data)))
//
//==================================================================================================
// 立即数据数据
// 旋钮开关 旋转，事件立即执行
//==================================================================================================
menu_immediataly_type(float,   move01,    ftostr51,     10 )
menu_immediataly_type(float,   move1,     ftostr51,     1  )
menu_immediataly_type(float,   move10,    ftostr51,     0.1)
#define drawmenu_immediataly_move01_selected(row, pstr, pstr2, data, minValue, maxValue, callback)         drawmenu_edit_generic(row, pstr, '>', itostr3(*(data)))
#define drawmenu_immediataly_move01(row, pstr, pstr2, data, minValue, maxValue, callback)                  drawmenu_edit_generic(row, pstr, ' ', itostr3(*(data)))
#define drawmenu_immediataly_move1_selected(row, pstr, pstr2, data, minValue, maxValue, callback)          drawmenu_edit_generic(row, pstr, '>', itostr3(*(data)))
#define drawmenu_immediataly_move1(row, pstr, pstr2, data, minValue, maxValue, callback)                   drawmenu_edit_generic(row, pstr, ' ', itostr3(*(data)))
#define drawmenu_immediataly_move10_selected(row, pstr, pstr2, data, minValue, maxValue, callback)         drawmenu_edit_generic(row, pstr, '>', itostr3(*(data)))
#define drawmenu_immediataly_move10(row, pstr, pstr2, data, minValue, maxValue, callback)                  drawmenu_edit_generic(row, pstr, ' ', itostr3(*(data)))
//
//=================================================================================================
// 编辑数据
// 和立即数据数据不同，在确认键按下数据才输入
//=================================================================================================
menu_edit_type(int,     int3,       itostr3,        1)
menu_edit_type(float,   float3,     ftostr3,        1)
menu_edit_type(float,   float32,    ftostr32,     100)
menu_edit_type(float,   float5,     ftostr5,     0.01)
menu_edit_type(float,   float51,    ftostr51,      10)
menu_edit_type(float,   float52,    ftostr52,     100)
menu_edit_type(uint32,  long5,      ftostr5,     0.01)
#define drawmenu_edit_int3_selected(row, pstr, pstr2, data, minValue, maxValue)         drawmenu_edit_generic(row, pstr, '>', itostr3(*(data)))
#define drawmenu_edit_int3(row, pstr, pstr2, data, minValue, maxValue)                  drawmenu_edit_generic(row, pstr, ' ', itostr3(*(data)))
#define drawmenu_edit_float3_selected(row, pstr, pstr2, data, minValue, maxValue)       drawmenu_edit_generic(row, pstr, '>', ftostr3(*(data)))
#define drawmenu_edit_float3(row, pstr, pstr2, data, minValue, maxValue)                drawmenu_edit_generic(row, pstr, ' ', ftostr3(*(data)))
#define drawmenu_edit_float32_selected(row, pstr, pstr2, data, minValue, maxValue)      drawmenu_edit_generic(row, pstr, '>', ftostr32(*(data)))
#define drawmenu_edit_float32(row, pstr, pstr2, data, minValue, maxValue)               drawmenu_edit_generic(row, pstr, ' ', ftostr32(*(data)))
#define drawmenu_edit_float5_selected(row, pstr, pstr2, data, minValue, maxValue)       drawmenu_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define drawmenu_edit_float5(row, pstr, pstr2, data, minValue, maxValue)                drawmenu_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define drawmenu_edit_float52_selected(row, pstr, pstr2, data, minValue, maxValue)      drawmenu_edit_generic(row, pstr, '>', ftostr52(*(data)))
#define drawmenu_edit_float52(row, pstr, pstr2, data, minValue, maxValue)               drawmenu_edit_generic(row, pstr, ' ', ftostr52(*(data)))
#define drawmenu_edit_float51_selected(row, pstr, pstr2, data, minValue, maxValue)      drawmenu_edit_generic(row, pstr, '>', ftostr51(*(data)))
#define drawmenu_edit_float51(row, pstr, pstr2, data, minValue, maxValue)               drawmenu_edit_generic(row, pstr, ' ', ftostr51(*(data)))
#define drawmenu_edit_long5_selected(row, pstr, pstr2, data, minValue, maxValue)        drawmenu_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define drawmenu_edit_long5(row, pstr, pstr2, data, minValue, maxValue)                 drawmenu_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define drawmenu_edit_bool_selected(row, pstr, pstr2, data)                             drawmenu_edit_generic_P(row, pstr, '>', (*(data))?(MSG_ON):(MSG_OFF))
#define drawmenu_edit_bool(row, pstr, pstr2, data)                                      drawmenu_edit_generic_P(row, pstr, ' ', (*(data))?(MSG_ON):(MSG_OFF))
//
//=======================================================================
// 菜单控件
//=======================================================================
#define drawmenu_back_selected(lineNr, lable, fxn)      drawmenu_generic(lineNr, lable, LCD_STR_UPLEVEL[0], LCD_STR_UPLEVEL[0]    )
#define drawmenu_back(lineNr, lable, fxn)               drawmenu_generic(lineNr, lable, ' ',                LCD_STR_UPLEVEL[0]    )
#define drawmenu_submenu_selected(lineNr, lable, fxn)   drawmenu_generic(lineNr, lable, '>',                LCD_STR_ARROW_RIGHT[0])
#define drawmenu_submenu(lineNr, lable, fxn)            drawmenu_generic(lineNr, lable, ' ',                LCD_STR_ARROW_RIGHT[0])
#define drawmenu_function_selected(lineNr, lable, fxn)  drawmenu_generic(lineNr, lable, '>', ' ')
#define drawmenu_function(lineNr, lable, fxn)           drawmenu_generic(lineNr, lable, ' ', ' ')
#define drawmenu_gcode_selected(lineNr, lable, fxn)     drawmenu_generic(lineNr, lable, '>', ' ')
#define drawmenu_gcode(lineNr, lable, fxn)              drawmenu_generic(lineNr, lable, ' ', ' ')
//======================================================================
// LCD 任务
//======================================================================
__task void lcdTask(void) {
    static uint8 sem_double_data;
    //===========================================
    //== lcd 信号触发刷屏
    os_sem_init(&lcd.sem_lcd, 0);
    //
    //===========================================
    //== 按键引脚
    exti.begin(LCD_ENCODE1,  encoderPulse1Isr, EXTI_RISING);
    exti.begin(LCD_ENCODE2,  encoderPulse2Isr, EXTI_RISING);
    gpio.pinMode(LCD_BUZZER_PIN, OUTPUT);
    //
    //================================
    //== 等待任务启动允许
    lcd.taskRunEnable = true;
    while (taskRunEnable() == false) os_dly_wait(1);
    lcd.pLcdBuf = commu.getMbxBuf();
    //
    //===========================================
    //== lcd 起动界面维持3S
    lcd.init_menu();
    os_dly_wait(3000);
while (1) {
    // lcd
    if (sem_double_data == 0) {
        if (os_sem_wait(&lcd.sem_lcd, 1000) != OS_R_TMO) {
            sem_double_data = 2;
        }
    }
    lcd.getStatus();
    lcd.update();
    if ((os_time_get() - lcd.liveTimer) > 1000) {
        lcd.liveTimer = os_time_get();
        (lcd.liveFlag) ? (lcd.liveFlag = false) : (lcd.liveFlag = true);
    }
    lcd.sem_lcd_flag = false;
		
    if (debugOut == DEBUG_AUTO_LEAVER) {
        serialDebug.print(adc.analogRead(AUTO_LEAVER_PIN));
        serialDebug.println();
    }
    (sem_double_data) ? (sem_double_data--) : (sem_double_data = 0);
}
}
//======================================================================
// 状态栏
//======================================================================
void c_lcd::getStatus() {
//                      "012345678901234567890"
    if (gcode.getStaus() == egcode_status_heat) {
        statusMessage = "002:Heating... ";
        return;
    }
    statusMessage = "Ready to Run !!! ";
}
//======================================================================
// 刷新界面
//======================================================================
void c_lcd::update() {
    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_6x10_marlin);
        u8g.setPrintPos(125, 0);
        (this->*currentMenu)();
    }while (u8g.nextPage());
}
//
//======================================================================
// 画调节框bool类型
//======================================================================
void c_lcd::drawmenu_edit_generic_P(uint8_t row, const char* pstr, char pre_char, const char* data) {    
    //
    //-- 填空
	u8g.setPrintPos(0, (row + 1) * LCD_CHAR_HEIGH);
    u8g.print(LCD_BLANK_SPACE); 
    //
    //-- 提示符填充
	u8g.setPrintPos(0 * LCD_CHAR_WIDTH, (row + 1) * LCD_CHAR_HEIGH);
    u8g.print(pre_char); 
    u8g.print(pstr); 
	u8g.print(": ");
    //
    //-- 数据
	u8g.print(data);
}
//
//======================================================================
// 画调节框
//======================================================================
void c_lcd::drawmenu_edit_generic(uint8_t row, const char* pstr, char pre_char, char* data) {
    //
    //-- 填空
	u8g.setPrintPos(0, (row + 1) * LCD_CHAR_HEIGH);
    u8g.print(LCD_BLANK_SPACE); 
    //
    //-- 提示符填充
	u8g.setPrintPos(0 * LCD_CHAR_WIDTH, (row + 1) * LCD_CHAR_HEIGH);
    u8g.print(pre_char); 
    u8g.print(pstr); 
	u8g.print(": ");
    //
    //-- 数据
	u8g.print(data);
}
//
//======================================================================
// 画菜单
//======================================================================
void c_lcd::drawmenu_generic (uint8 row, const char *pstr, char pre_char, char post_char) {
    //
    //-- 选择提示框
    if (pre_char=='>' || pre_char==LCD_STR_UPLEVEL[0]) {
        u8g.setColorIndex(1); //black on white
        u8g.drawBox(0, row * LCD_CHAR_HEIGH + 3, 128, LCD_CHAR_HEIGH);
        u8g.setColorIndex(0); //white on black
    } else {
        u8g.setColorIndex(1); //black on white
    }
    //
    //-- 字符编写
    u8g.setPrintPos (0, (row + 1)* LCD_CHAR_HEIGH);
    u8g.print(LCD_BLANK_SPACE);  
    u8g.setPrintPos (0, (row + 1)* LCD_CHAR_HEIGH);    
    (pre_char != '>') ? u8g.print(pre_char) : u8g.print(' ');
    u8g.print(pstr);  
    //
    //-- 结束符
    u8g.print(post_char);
    u8g.print(' ');
    u8g.setColorIndex(1);       //black on white
}
//
//======================================================================
// 编辑数据
//======================================================================
void c_lcd::drawedit(const char* pstr, char* value) {
	u8g.setPrintPos(0 , (u8g.getHeight() - 1 - LCD_CHAR_HEIGH) - (1 * LCD_CHAR_HEIGH) - 0);
	u8g.setFont(u8g_font_6x10_marlin);
    u8g.print(pstr); 
	u8g.print(": ");
	u8g.print(value);
}
//
//======================================================================
// 菜单返回
//======================================================================
void c_lcd::menu_action_back (tdLcdFxn fxn) {
    currentMenu = fxn;
    encoderPos  = 0;
}
//
//======================================================================
// 菜单进入子菜单
//======================================================================
void c_lcd::menu_action_submenu (tdLcdFxn fxn) {
    currentMenu = fxn;
    encoderPos  = 0;
}
//
//======================================================================
// 生成GCODE执行
//======================================================================
void c_lcd::menu_action_gcode (const char *gcode) {
    if (commu.parseAscii((char *)gcode, pLcdBuf,  false)) {
        pLcdBuf = commu.checkAndPushCommand(pLcdBuf);
    }
}
//
//======================================================================
// 执行功能代码
//======================================================================
void c_lcd::menu_action_function (tdLcdFxn fxn) {
    (this->*fxn)();
}
//
//======================================================================
// bool 执行
//======================================================================
void c_lcd::menu_action_edit_bool(const char *pstr, bool *ptr) {
    *ptr = !(*ptr);
}
//
//======================================================================
// 自动打印 SD 卡
//======================================================================
void c_lcd::function_autoStartSd () {
    sdReader.checkAutoStart(true);
}
//
//======================================================================
// 设定当前为所有机械0位
//======================================================================
void c_lcd::function_setZzeroPos () {
    para.printer.z_home -= gcode.getCurPos(Z_AXIS);
    gcode.setCurPos(0, 0, 0, 0);
}
//
//======================================================================
// PLA 预热
//======================================================================
void c_lcd::function_preheatPla () {
    tempHotBed.setTarTemp (para.preHeatPla.bedTemp);
    tempHotEnd1.setTarTemp(para.preHeatPla.endTemp);
    stepMoto.dev->fanSpeed = para.preHeatPla.fanSpeed;
}
//
//======================================================================
// ABS 预热
//======================================================================
void c_lcd::function_preheatAbs () {
    tempHotBed.setTarTemp (para.preHeatAbs.bedTemp);
    tempHotEnd1.setTarTemp(para.preHeatAbs.endTemp);
    stepMoto.dev->fanSpeed = para.preHeatAbs.fanSpeed;
}
//
//======================================================================
// 冷却
//======================================================================
void c_lcd::function_cooldown () {
    tempHotBed.setTarTemp (0);
    tempHotEnd1.setTarTemp(0);
    tempHotEnd2.setTarTemp(0);
    stepMoto.dev->fanSpeed = 0;
}
//
//======================================================================
// 存储数据到 EEPROM
//======================================================================
void c_lcd::function_storeEprom () {
    eep.wirte((uint8 *)&para, (uint32)&EEP, sizeof(para));
    gcode.calculateDeltaPara();
}
//
//======================================================================
// EEPROM数据读取使用
//======================================================================
void c_lcd::function_loadEprom () {
    memCopy((char *)&para, (char *)&EEP, sizeof(para));
    gcode.calculateDeltaPara();
}
//
//======================================================================
// 恢复出厂设置
//======================================================================
void c_lcd::function_reStoreFailsafe () {
    memCopy((char *)&para,    (char *)&EEP_DF,  sizeof(para));
    eep.wirte((uint8 *)&para, (uint32)&EEP,     sizeof(para));
    gcode.calculateDeltaPara();
}
//
//======================================================================
// 预处理界面
//======================================================================
int test ;
void c_lcd::prepare_menu(void) {
START_MENU();
    MENU_ITEM(back, MSG_MAIN, &c_lcd::main_menu);
	MENU_ITEM_EDIT(bool,    "Laser modle ",         &lcd.laserModle);
    MENU_ITEM_IMMEDIATALY(move01,    "Laser Focus ",&para.printer.laserFocus,   0, para.printer.z_home,  &c_lcd::function_Focus);
    MENU_ITEM_EDIT(int3,             "Laser delay ",&para.printer.laserDelay,  50,  1000);
    MENU_ITEM(function,     "Autostart",            &c_lcd::function_autoStartSd);
    MENU_ITEM(gcode,        "Disable steppers",     "M84 ");
    MENU_ITEM(gcode,        "Auto home (G28)",      "G28 ");
    MENU_ITEM(gcode,        "Auto Level(G29)",      "G29 ");
    MENU_ITEM(function,     "Set Z zero Pos",       &c_lcd::function_setZzeroPos);
    MENU_ITEM(function,     "Preheat PLA",          &c_lcd::function_preheatPla );
    MENU_ITEM(function,     "Preheat ABS",          &c_lcd::function_preheatAbs );
    MENU_ITEM(function,     "Cooldown",             &c_lcd::function_cooldown);
    MENU_ITEM(submenu,      "Move axis",            &c_lcd::move_menu_load);
END_MENU();
}
//
//======================================================================
// 移动控制界面
//======================================================================
void c_lcd::function_move(void) {
    gcode.moveAbs (xMove, yMove, zMove, e1Move, para.motion.maxSpeed[X_AXIS]/2);
    for (int i=0; i<MAX_AXIS; i++) {
        gcode.targetPos[i] = gcode.currentPos[i];
    }
}
//
//======================================================================
// 激光雕刻机焦点
//======================================================================
void c_lcd::function_Focus(void) {
    stepMoto.dev->fanSpeed = true;
    gcode.moveAbs (0, 0, para.printer.laserFocus, 0, para.motion.maxSpeed[X_AXIS]/2);
    for (int i=0; i<MAX_AXIS; i++) {
        gcode.targetPos[i] = gcode.currentPos[i];
    }
}
void c_lcd::move_menu_load(void) {
    xMove  = gcode.getCurPos(X_AXIS );
    yMove  = gcode.getCurPos(Y_AXIS );
    zMove  = gcode.getCurPos(Z_AXIS );
    e1Move = gcode.getCurPos(E1_AXIS);
    menu_action_submenu(&c_lcd::move_menu);
    menu_action_feedBack();
}
void c_lcd::move_menu(void) {
START_MENU();
    MENU_ITEM(back,     MSG_PREPARE,    &c_lcd::prepare_menu  );
    MENU_ITEM_IMMEDIATALY(move1 ,    "X Move   1mm",      &xMove,   para.printer.min_pos_x, para.printer.max_pos_x,   &c_lcd::function_move);
    MENU_ITEM_IMMEDIATALY(move1 ,    "Y Move   1mm",      &yMove,   para.printer.min_pos_y, para.printer.max_pos_y,   &c_lcd::function_move);
    MENU_ITEM_IMMEDIATALY(move01,    "Z Move 0.1mm",      &zMove,   0,                      para.printer.z_home,      &c_lcd::function_move);
    MENU_ITEM_IMMEDIATALY(move1 ,    " |Move   1mm",      &zMove,   0,                      para.printer.z_home,      &c_lcd::function_move);
    MENU_ITEM_IMMEDIATALY(move01,    "E1Move 0.1mm",      &e1Move,  -1000,       1000,      &c_lcd::function_move);
    MENU_ITEM_IMMEDIATALY(move1 ,    " |Move   1mm",      &e1Move,  -1000,       1000,      &c_lcd::function_move);
END_MENU();
}
//
//======================================================================
// 回抽控制
//======================================================================
void c_lcd::retract_menu() {
    START_MENU();
	MENU_ITEM(back, MSG_CONTROL, &c_lcd::control_menu);
	MENU_ITEM_EDIT(bool,    "AutoRetr. ",   &para.retract.enable);
	MENU_ITEM_EDIT(float52, "Retract mm",   &para.retract.length,           0, 100);
	MENU_ITEM_EDIT(float52, "Swap Re.mm",   &para.retract.lengthSwap,       0, 100);
	MENU_ITEM_EDIT(float3,  "Retract  V",   &para.retract.feedrate,         1, 999);
	MENU_ITEM_EDIT(float52, "Hop     mm",   &para.retract.zlift,            0, 999);
	MENU_ITEM_EDIT(float52, "UnRet  +mm",   &para.retract.recoveLength,     0, 100);
	MENU_ITEM_EDIT(float52, "S UnRet+mm",   &para.retract.recoveLengthSwap, 0, 100);
	MENU_ITEM_EDIT(float3,  "UnRet    V",   &para.retract.recoveFeedrate,   1, 999);
END_MENU();
}
//
//======================================================================
// ABS 预热设定
//======================================================================
void c_lcd::preheatAbs_menu() {	
START_MENU();
    MENU_ITEM(back, MSG_TEMPERATURE, &c_lcd::temperature_menu);
    MENU_ITEM_EDIT(int3, "Fan speed", &para.preHeatAbs.fanSpeed,    0,  255);
    MENU_ITEM_EDIT(int3, "Nozzle   ", &para.preHeatAbs.endTemp,     0,	MAX_END1_HEATER - 15);
    MENU_ITEM_EDIT(int3, "Bed      ", &para.preHeatAbs.bedTemp,     0,  MAX_BED_HEATER  - 15);
END_MENU();
}
//
//======================================================================
// PLA 预热设定
//======================================================================
void c_lcd::preheatPla_menu() {	
START_MENU();
    MENU_ITEM(back, MSG_TEMPERATURE, &c_lcd::temperature_menu);
    MENU_ITEM_EDIT(int3, "Fan speed", &para.preHeatPla.fanSpeed,    0,  255);
    MENU_ITEM_EDIT(int3, "Nozzle   ", &para.preHeatPla.endTemp,     0,	MAX_END1_HEATER - 15);
    MENU_ITEM_EDIT(int3, "Bed      ", &para.preHeatPla.bedTemp,     0,  MAX_BED_HEATER  - 15);
END_MENU();
}
//
//======================================================================
// 控制界面
//======================================================================
void c_lcd::control_menu(void) {
START_MENU();
    MENU_ITEM(back, MSG_MAIN, &c_lcd::main_menu);
    MENU_ITEM(submenu,    "Temperature",      &c_lcd::temperature_menu        );
    MENU_ITEM(submenu,    "Adjust",           &c_lcd::adjust_menu             );
    MENU_ITEM(submenu,    "Motion",           &c_lcd::motion_menu             );
    MENU_ITEM(submenu,    "Printer setting",  &c_lcd::printer_menu            );
    MENU_ITEM(submenu,    "Rectract",         &c_lcd::retract_menu            );
    MENU_ITEM(function,   "Store memory",     &c_lcd::function_storeEprom     );
    MENU_ITEM(function,   "Load memory",      &c_lcd::function_loadEprom      );
    MENU_ITEM(function,   "Restore failsafe", &c_lcd::function_reStoreFailsafe);
    
END_MENU();
}
//
//======================================================================
// 调整界面
//======================================================================
void c_lcd::tune_menu(void) {
START_MENU();
    MENU_ITEM(back, MSG_MAIN, &c_lcd::main_menu);
    MENU_ITEM_EDIT(int3,    "Speed      ",         &gcode.multiply,   			     0,     255               );
    MENU_ITEM_EDIT(int3,    "Nozzle1    ",         &tempHotEnd1.tarTemp,             0,     MAX_END1_HEATER-15);
    MENU_ITEM_EDIT(int3,    "Nozzle2    ",         &tempHotEnd2.tarTemp,             0,     MAX_END1_HEATER-15);
    MENU_ITEM_EDIT(int3,    "bed        ",         &tempHotBed.tarTemp,              0,     MAX_BED_HEATER -15);
    MENU_ITEM_EDIT(int3,    "Fan speed  ",         (int *)&stepMoto.dev->fanSpeed,   0,     255               );
    MENU_ITEM_EDIT(int3,    "E1 MUTIPLY ",  	   &para.motion.E1Mutiply,          10,     500               );
    //
END_MENU();
}
//
//======================================================================
// 系统状态界面
//======================================================================
void c_lcd::sys_status_menu(void) {
	int autoLevAd = adc.analogRead(AUTO_LEAVER_PIN);
START_MENU();
    MENU_ITEM(back, MSG_MAIN, &c_lcd::main_menu);
    MENU_ITEM_LABEL(int4, "AUTO LEV  AD." , &autoLevAd);
    MENU_ITEM_LABEL(int3, "Main loop stk" , &lcd.sysStatus.mainLoopStkP);
    MENU_ITEM_LABEL(int3, "Sd reader stk" , &lcd.sysStatus.sdReaderStkP);
    MENU_ITEM_LABEL(int3, "commu     stk" , &lcd.sysStatus.commuStkP);
    MENU_ITEM_LABEL(int3, "Gcode     stk" , &lcd.sysStatus.gcodeStkP);
    MENU_ITEM_LABEL(int3, "Lcd       stk" , &lcd.sysStatus.lcdStkP);
END_MENU();
}
//
//======================================================================
// sd卡控制
//======================================================================
void c_lcd::function_pausePrint() {
    sdReader.setStartPrint(false);
}
void c_lcd::function_resumePrint() {
    sdReader.setStartPrint(true);
}
void c_lcd::function_stopPrint() {
    sdReader.close();
}
void c_lcd::function_initCard() {
    sdReader.init();
}
void c_lcd::function_openfile() {
    sdReader.open((const char*)sdReader.info.name, "r");
    sdReader.setStartPrint(true);
}

void c_lcd::function_cardMenu() {
START_MENU();
    MENU_ITEM(back, MSG_MAIN, &c_lcd::main_menu);
    sdReader.info.fileID = 0;
    while(ffind("*.*",&sdReader.info)==0) {
        MENU_ITEM(function, (const char*)sdReader.info.name, &c_lcd::function_openfile);
    }
END_MENU();
}
//
//======================================================================
// 主菜单界面
//======================================================================
void c_lcd::main_menu(void) {
START_MENU();
    MENU_ITEM(back, MSG_WATCH, &c_lcd::status_menu);
    if (stepMoto.dev->runningFlag || sdReader.printing) MENU_ITEM(submenu, MSG_TUNE,    &c_lcd::tune_menu   ) ;
    else                                                MENU_ITEM(submenu, MSG_PREPARE, &c_lcd::prepare_menu) ;
    MENU_ITEM(submenu, MSG_CONTROL, &c_lcd::control_menu);   
    if (sdReader.cardOk) {
        if (sdReader.pFile) {
            if (sdReader.printing) MENU_ITEM(function, MSG_PAUSE_PRINT,  &c_lcd::function_pausePrint );
            else                   MENU_ITEM(function, MSG_RESUME_PRINT, &c_lcd::function_resumePrint);
            MENU_ITEM(function, MSG_STOP_PRINT, &c_lcd::function_stopPrint);
        } else {
            MENU_ITEM(submenu,  MSG_CARD_MENU,  &c_lcd::function_cardMenu);
            MENU_ITEM(function, MSG_CNG_SDCARD, &c_lcd::function_initCard);
        }
    } else {
        MENU_ITEM(function, MSG_NO_CARD,     &c_lcd::function_cardMenu);
        MENU_ITEM(function, MSG_INIT_SDCARD, &c_lcd::function_initCard);
    }
    MENU_ITEM(submenu, "sys status", &c_lcd::sys_status_menu);   
END_MENU();
}
//
//======================================================================
// 温度控制界面
//======================================================================
void c_lcd::function_autoTurn(void) {
    if (autoTurnBed) {
        tempHotBed.pidAutoTune(autoTurnBed,  10);
    } else if (autoTurnEnd){
        tempHotEnd1.pidAutoTune(autoTurnEnd, 10);
    }
    autoTurnBed = 0;
    autoTurnEnd = 0; 
}
void c_lcd::temperature_menu (void) {
    int none = 0;
START_MENU();
    MENU_ITEM(back, MSG_CONTROL, &c_lcd::control_menu);
    MENU_ITEM_EDIT(int3,    "Nozzle1",              (int*)&tempHotEnd1.tarTemp,      0,     MAX_END1_HEATER-15);
    MENU_ITEM_EDIT(int3,    "Nozzle2",              (int*)&tempHotEnd2.tarTemp,      0,     MAX_END2_HEATER-15);
    MENU_ITEM_EDIT(int3,    "Bed    ",              (int*)&tempHotBed.tarTemp,       0,     MAX_BED_HEATER -15);
    MENU_ITEM_EDIT(int3,    "Fan speed",            (int*)&stepMoto.dev->fanSpeed,   0,     255);
    MENU_ITEM(submenu,      "Preheat PLA conf",    &c_lcd::preheatPla_menu); 
    MENU_ITEM(submenu,      "Preheat ABS conf",    &c_lcd::preheatAbs_menu); 
    MENU_ITEM_LABEL(int3, "   --------------   " , &none);
    //
    //====== BED
    MENU_ITEM_EDIT(bool,    "BED Autotemp",    &para.Temp[e_bed_heat_index].autoTempEnable);
    MENU_ITEM_EDIT(float3,  "  | Min  ",        &para.Temp[e_bed_heat_index].autoTempMin,      0,  MAX_BED_HEATER -15);
    MENU_ITEM_EDIT(float3,  "  | Max  ",        &para.Temp[e_bed_heat_index].autoTempMax,      0,  MAX_BED_HEATER -15); 
    MENU_ITEM_EDIT(float32, "  | Fact ",        &para.Temp[e_bed_heat_index].autoTempFactor,   0,  1.0); 
    MENU_ITEM_EDIT(float51, "  | PID-P",        &para.Temp[e_bed_heat_index].kp,               0,  10000);
    MENU_ITEM_EDIT(float51, "  | PID-I",        &para.Temp[e_bed_heat_index].ki,               0,  10000);
    MENU_ITEM_EDIT(float51, "  | PID-D",        &para.Temp[e_bed_heat_index].kd,               0,  10000);
    MENU_ITEM_EDIT(int3,    "  | TUNE SET",     &autoTurnBed,  10, 150 );
    MENU_ITEM(function,     "  | AUTO TUNE",    &c_lcd::function_autoTurn );
    MENU_ITEM_LABEL(int3, "   --------------   " , &none);   
    //
    //====== END1
    MENU_ITEM_EDIT(bool,    "^END1 Autotemp",   &para.Temp[e_end1_heat_index].autoTempEnable);
    MENU_ITEM_EDIT(float3,  "  | Min  ",       &para.Temp[e_end1_heat_index].autoTempMin,      0,  MAX_END1_HEATER -15);
    MENU_ITEM_EDIT(float3,  "  | Max  ",       &para.Temp[e_end1_heat_index].autoTempMax,      0,  MAX_END1_HEATER -15); 
    MENU_ITEM_EDIT(float32, "  | Fact ",       &para.Temp[e_end1_heat_index].autoTempFactor,   0,  1.0); 
    MENU_ITEM_EDIT(float51, "  | PID-P",       &para.Temp[e_end1_heat_index].kp,               0.1,   10000);
    MENU_ITEM_EDIT(float51, "  | PID-I",       &para.Temp[e_end1_heat_index].ki,               0.1,   10000);
    MENU_ITEM_EDIT(float51, "  | PID-D",       &para.Temp[e_end1_heat_index].kd,               0.1,   10000);
    MENU_ITEM_EDIT(int3,    "  | TUNE SET",    &autoTurnEnd,  10, 250 );
    MENU_ITEM(function,     "  | AUTO TUNE",   &c_lcd::function_autoTurn );
    //====== END ======
    MENU_ITEM_LABEL(int3, "<--------END------->" , &none);
END_MENU();
}
//
//======================================================================
// 自动调平手动修正
//======================================================================
void c_lcd::function_reCalDelta() {
    gcode.calculateDeltaPara();
}
//
//======================================================================
// 调整控制界面
//======================================================================
void c_lcd::adjust_menu (void) {
    int none = 0;
START_MENU();
    MENU_ITEM(back, MSG_CONTROL, &c_lcd::control_menu);
    MENU_ITEM_IMMEDIATALY(move01,  "AutoLev X+T+",  &para.adjust.autoLevXManu, -5, 5, &c_lcd::function_reCalDelta);
    MENU_ITEM_IMMEDIATALY(move01,  "AutoLev Y+T+",  &para.adjust.autoLevYManu, -5, 5, &c_lcd::function_reCalDelta);
    MENU_ITEM_IMMEDIATALY(move01,  "AutoLev CeT+",  &para.adjust.autoLevCeManu,   -10,   10,   &c_lcd::function_reCalDelta);
    //                    "01234567890123456789"
    MENU_ITEM_LABEL(int3, "   --------------   " , &none);
    MENU_ITEM_EDIT(float32, "adjust XP(%)",   &para.adjust.adjust_xp, 0, 2);
    MENU_ITEM_EDIT(float32, "adjust XN(%)",   &para.adjust.adjust_xn, 0, 2);
    MENU_ITEM_EDIT(float32, "adjust YP(%)",   &para.adjust.adjust_yp, 0, 2);
    MENU_ITEM_EDIT(float32, "adjust YN(%)",   &para.adjust.adjust_yn, 0, 2);
    MENU_ITEM_LABEL(int3, "   --------------   " , &none);
    MENU_ITEM_EDIT(int3, "Lev sensitive",   &para.adjust.autoLevSentive, 1, 1000);
    MENU_ITEM_EDIT(int3, "Lev begin    ",   &para.adjust.autoLevBegin,   5, 100 );
    //                   "012345678901234567890"
    MENU_ITEM_LABEL(int3, "<--------END------->" , &none);
END_MENU();
}
//
//======================================================================
// 运动控制界面
//======================================================================
void c_lcd::motion_menu (void) {
    int none = 0;
START_MENU();
    MENU_ITEM(back, MSG_CONTROL, &c_lcd::control_menu);
    MENU_ITEM_EDIT(int3,   "jerk-Vxy mm/s",  &para.motion.jerk_xy,           1,      999);
    MENU_ITEM_EDIT(int3,   "jerk-Vz  mm/s",  &para.motion.jerk_z,            1,      999);
    MENU_ITEM_EDIT(int3,   "jerk-Ve  mm/s",  &para.motion.jerk_e,            1,      999);
    MENU_ITEM_EDIT(float32,"end-SPD mm/s",  &para.motion.endSpeed,          0,      5  );
    //                    "01234567890123456789"
    MENU_ITEM_LABEL(int3, "   --------------   " , &none);
    MENU_ITEM_EDIT(int3,   "E1 MUTIPLY  %",  &para.motion.E1Mutiply,        10,      500);
    //                    "01234567890123456789"
    MENU_ITEM_LABEL(int3, "   --------------   " , &none);
    MENU_ITEM_EDIT(int3,   "vmax x   mm/s",  &para.motion.maxSpeed[X_AXIS],  1,      999);
    MENU_ITEM_EDIT(int3,   "vmax y   mm/s",  &para.motion.maxSpeed[Y_AXIS],  1,      999);
    MENU_ITEM_EDIT(int3,   "vmax z   mm/s",  &para.motion.maxSpeed[Z_AXIS],  1,      999);
    MENU_ITEM_EDIT(int3,   "vmax e1  mm/s",  &para.motion.maxSpeed[E1_AXIS], 1,      999); 
    //                    "01234567890123456789"
    MENU_ITEM_LABEL(int3, "   --------------   " , &none);
    MENU_ITEM_EDIT(float5, "Accel mm/s^2",  &para.motion.acceleration,      500,    9999);
    MENU_ITEM_EDIT(float5, "AmaxX mm/s^2",  &para.motion.maxAcc[X_AXIS],    100,    9999);
    MENU_ITEM_EDIT(float5, "AmaxY mm/s^2",  &para.motion.maxAcc[Y_AXIS],    100,    9999);
    MENU_ITEM_EDIT(float5, "AmaxZ mm/s^2",  &para.motion.maxAcc[Z_AXIS],    100,    9999);
    MENU_ITEM_EDIT(float5, "AmaxE1mm/s^2",  &para.motion.maxAcc[E1_AXIS],   100,    9999);
    MENU_ITEM_EDIT(float5, "A retract   ",  &para.motion.retractAcc,        100,    9999);
    //                   "012345678901234567890"
    MENU_ITEM_LABEL(int3, "<--------END------->" , &none);
END_MENU();
}
//
//======================================================================
// 打印机界面
//======================================================================
void c_lcd::printer_menu (void) {
    int none = 0;
START_MENU();
    MENU_ITEM(back, MSG_CONTROL, &c_lcd::control_menu);
    MENU_ITEM_EDIT       (float51, "MAX POS X  ",    &para.printer.max_pos_x,        10, 1000);
    MENU_ITEM_EDIT       (float51, "MIN POS X  ",    &para.printer.min_pos_x,     -1000,  -10);
    MENU_ITEM_EDIT       (float51, "MAX POS Y  ",    &para.printer.max_pos_y,        10, 1000);
    MENU_ITEM_EDIT       (float51, "MIN POS Y  ",    &para.printer.min_pos_y,     -1000,  -10);
    MENU_ITEM_EDIT       (float32, "MAX POS Z  ",    &para.printer.z_home,           10, 1000);
    MENU_ITEM_EDIT       (int3,  "LASER X P  ",      &para.printer.laser_x_offset,-1000, 1000);
    MENU_ITEM_EDIT       (int3,  "LASER Y P  ",      &para.printer.laser_y_offset,-1000, 1000);
    //                    "01234567890123456789"
    MENU_ITEM_LABEL(int3, "   --------------   " , &none);
    MENU_ITEM_EDIT       (float32, "X STEPS/MM",    &para.printer.steps_mm[X_AXIS ], 10, 1000);
    MENU_ITEM_EDIT       (float32, "Y STEPS/MM",    &para.printer.steps_mm[Y_AXIS ], 10, 1000); 
    MENU_ITEM_EDIT       (float32, "Z STEPS/MM",    &para.printer.steps_mm[Z_AXIS ], 10, 1000);
    MENU_ITEM_EDIT       (float32, "E STEPS/MM",    &para.printer.steps_mm[E1_AXIS], 10, 1000); 
    MENU_ITEM_LABEL(int3, "   --------------   " , &none);
    MENU_ITEM_EDIT       (int3, "X CHANNEL",    &para.printer.steps_pin[0], 0, MAX_AXIS);
    MENU_ITEM_EDIT       (int3, "Y CHANNEL",    &para.printer.steps_pin[1], 0, MAX_AXIS); 
    MENU_ITEM_EDIT       (int3, "Z CHANNEL",    &para.printer.steps_pin[2], 0, MAX_AXIS);
    MENU_ITEM_EDIT       (int3, "E CHANNEL",    &para.printer.steps_pin[3], 0, MAX_AXIS); 
    //                    "01234567890123456789"
    MENU_ITEM_LABEL(int3, "   --------------   " , &none);
    MENU_ITEM_EDIT       (float32, "DIAGONAL LEN",   &para.printer.deltaDiagonalRad, 10, 1000);
    MENU_ITEM_EDIT       (float32, "DELTA RADIUS",   &para.printer.deltaRadius,      10, 1000);
    //                    "01234567890123456789"
    MENU_ITEM_LABEL(int3, "<--------END------->" , &none);
END_MENU();
}
//
//======================================================================
// 初始化页面
//======================================================================
void c_lcd::init_menu(void) {
    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_6x10_marlin);
        u8g.setColorIndex(1);
        u8g.drawBox(0, 0, u8g.getWidth(), u8g.getHeight());
        u8g.setColorIndex(1);
    }while(u8g.nextPage());
    
    u8g.firstPage();
    do {
        int y = 0;
        u8g.drawBitmap(0, 0, START_BMPBYTEWIDTH, START_BMPHEIGHT, start_bmp);
//      u8g.drawStr   (START_BMPWIDTH + 2, y = y +  0, "123456789A");  
        u8g.drawStr   (START_BMPWIDTH + 4, y = y + 10, "HARD WARE:");        
        u8g.drawStr   (START_BMPWIDTH + 4, y = y + 10, "15+ STM 3D");
        u8g.drawStr   (START_BMPWIDTH + 4, y = y + 10, "V2.0      ");
        u8g.drawStr   (START_BMPWIDTH + 4, y = y + 10, "FIRMWARE: ");
        u8g.drawStr   (START_BMPWIDTH + 4, y = y + 10, "V1.0      ");
        u8g.drawStr   (START_BMPWIDTH + 4, y = y + 10, "THK:MARLIN");
    }while(u8g.nextPage());
    currentMenu = &c_lcd::status_menu;
}
//======================================================================
// 状态显示界面
//======================================================================
void c_lcd::status_menu(void) {
    static bool multiplyInit = false;
    //
    //== 速度倍率
    if (multiplyInit == false) {
        encoderPos = gcode.multiply;
        multiplyInit = true;
    } else {
        encoderPos = boundary(encoderPos, 10, 999);
        gcode.multiply = encoderPos;
    }
    //
    //== 图形显示
    u8g.firstPage();
    do {
        u8g.setFont(u8g_font_6x10_marlin);
    //
    //== 图形显示
        u8g.setColorIndex(1);	        
        if (liveFlag && stepMoto.dev->fanSpeed) {
            u8g.drawBitmapP(9, 2, STATUS_SCREENBYTEWIDTH, STATUS_SCREENHEIGHT, status_screen0_bmp);
        } else {
            u8g.drawBitmapP(9, 2, STATUS_SCREENBYTEWIDTH, STATUS_SCREENHEIGHT, status_screen1_bmp);
        }
    //
    //== sd 卡槽显示
        u8g.drawBox(42, 42, 8, 7);
        u8g.drawBox(50, 44, 2, 5);
        u8g.drawFrame(42, 49, 10, 4);
        u8g.drawPixel(50, 43);
    //
    //== sd 进度条
        u8g.drawFrame(54, 49, 73, 4);
        if (sdReader.printing) {
            u8g.drawBox(55, 50, (unsigned int) ((71 * sdReader.getPercentDone()) / 100), 2);
        }
        u8g.setPrintPos(80, 47);
        if (gcode.printStartTime != 0) {
            uint32_t time = (os_time_get()-gcode.printStartTime) / 60000;
            u8g.print(itostr2(time / 60));
            u8g.print(':');
            u8g.print(itostr2(time % 60));
        } else {
            u8g.print("--:--");
        }
    //
    //== 挤出头1
        u8g.setPrintPos(6, 8);
        u8g.print(itostr3(int(tempHotEnd1.getTarTemperature() + 0.5)));
        u8g.print(" ");
        u8g.setPrintPos(6, 29);
        u8g.print(itostr3(int(tempHotEnd1.getTemperature() + 0.5)));
        u8g.print(" ");
        if (!tempHotEnd1.isHeat()) u8g.drawBox(13, 17, 2, 2);
        else {
            u8g.setColorIndex(0);	// white on black
            u8g.drawBox(13, 17, 2, 2);
            u8g.setColorIndex(1);	// black on white
        }
    //
    //== 挤出头2
        u8g.setPrintPos(31,8);
        u8g.print(itostr3(int(tempHotEnd2.getTarTemperature() + 0.5)));
        u8g.print(" ");
        u8g.setPrintPos(31,29);
        u8g.print(itostr3(int(tempHotEnd2.getTemperature() + 0.5)));
        u8g.print(" ");
        if (!tempHotEnd2.isHeat()) u8g.drawBox(38,17,2,2);
        else {
            u8g.setColorIndex(0);	// white on black
            u8g.drawBox(38,17,2,2);
            u8g.setColorIndex(1);   // black on white
        }
    //
    //== 挤出头3
        u8g.setPrintPos(55,29);
        u8g.print("---");
    //
    //== 热床
        u8g.setPrintPos(81, 8);
        u8g.print(itostr3(int(tempHotBed.getTarTemperature() + 0.5)));
        u8g.print(" ");
        u8g.setPrintPos(81, 29);
        u8g.print(itostr3(int(tempHotBed.getTemperature() + 0.5)));
        u8g.print(" ");
        if (!tempHotBed.isHeat())   u8g.drawBox(88, 18, 2, 2);
        else {
            u8g.setColorIndex(0);	// white on black
            u8g.drawBox(88, 18, 2, 2);
            u8g.setColorIndex(1);	// black on white
        }
    //
    //== 风机开度
        u8g.setPrintPos(104, 29);
        u8g.print(itostr3(int((stepMoto.dev->fanSpeed * 100) / 255)));
        u8g.print("%");
    //
    //== X Y Z 坐标
        u8g.drawBox(0, 30, 128, 9);
        u8g.setColorIndex(0);	// white on black
        u8g.setPrintPos(2, 38);
        u8g.print("X");
        u8g.drawPixel  ( 8, 33);
        u8g.drawPixel  ( 8, 35);
        u8g.setPrintPos(10, 38);
        u8g.print(ftostr31ns(gcode.getCurPos(X_AXIS)));
        u8g.setPrintPos(43, 38);
        u8g.print("Y");
        u8g.drawPixel  (49, 33);
        u8g.drawPixel  (49, 35);
        u8g.setPrintPos(51, 38);
        u8g.print(ftostr31ns(gcode.getCurPos(Y_AXIS)));
        u8g.setPrintPos(84, 38);
        u8g.print("Z");
        u8g.drawPixel  (90, 33);
        u8g.drawPixel  (90, 35);
        u8g.setPrintPos(92, 38);
        u8g.print(ftostr31ns(gcode.getCurPos(Z_AXIS)));
        u8g.setColorIndex(1);	// black on white
    //
    //== 给进速率
        u8g.setPrintPos(1, 49);
        u8g.print("Fd");
        u8g.drawPixel(13, 44);
        u8g.drawPixel(13, 46);
        u8g.setPrintPos(16, 49);
        u8g.print(ftostr3(gcode.multiply));
        u8g.print('%');
    //
    //== 状态栏
        u8g.setPrintPos(0, 61);
        u8g.print(statusMessage);
    //
    //== 活动标示
        if (liveFlag) {
            u8g.drawBox(1, 1, 2, 2);
        }
        
    }while(u8g.nextPage());
    //== 按键进入其他菜单
    if (encoderEnt) {
        menu_action_submenu(&c_lcd::main_menu);
        menu_action_feedBack();
        multiplyInit = false;
    }
}
//======================================================================
// 字符转换
//======================================================================
/********************************/
/** Float conversion utilities **/
/********************************/
//  convert float to string with +123.4 format
char conv[8];
char *c_lcd::ftostr3(const float &x) {
	return itostr3((int) x);
}
char *c_lcd::itostr2(const uint8_t &x) {
	//sprintf(conv,"%5.1f",x);
	int xx = x;
	conv[0] = (xx / 10) % 10 + '0';
	conv[1] = (xx) % 10 + '0';
	conv[2] = 0;
	return conv;
}
//  convert float to string with +123.4 format
char *c_lcd::ftostr31(const float &x) {
	int xx = x * 10;
	conv[0] = (xx >= 0) ? '+' : '-';
	xx = abs(xx);
	conv[1] = (xx / 1000) % 10 + '0';
	conv[2] = (xx / 100) % 10 + '0';
	conv[3] = (xx / 10) % 10 + '0';
	conv[4] = '.';
	conv[5] = (xx) % 10 + '0';
	conv[6] = 0;
	return conv;
}
//  convert float to string with 123.4 format
char *c_lcd::ftostr31ns(const float &x) {
	int xx = x * 10;
	//conv[0]=(xx>=0)?'+':'-';
	xx = abs(xx);
	conv[0] = (xx / 1000) % 10 + '0';
	conv[1] = (xx / 100) % 10 + '0';
	conv[2] = (xx / 10) % 10 + '0';
	conv[3] = '.';
	conv[4] = (xx) % 10 + '0';
	conv[5] = 0;
	return conv;
}
char *c_lcd::ftostr32(const float &x) {
	long xx = x * 100;
	if (xx >= 0)
		conv[0] = (xx / 10000) % 10 + '0';
	else
		conv[0] = '-';
	xx = abs(xx);
	conv[1] = (xx / 1000) % 10 + '0';
	conv[2] = (xx / 100) % 10 + '0';
	conv[3] = '.';
	conv[4] = (xx / 10) % 10 + '0';
	conv[5] = (xx) % 10 + '0';
	conv[6] = 0;
	return conv;
}
char *c_lcd::itostr31(const int &xx) {
	conv[0] = (xx >= 0) ? '+' : '-';
	conv[1] = (xx / 1000) % 10 + '0';
	conv[2] = (xx / 100) % 10 + '0';
	conv[3] = (xx / 10) % 10 + '0';
	conv[4] = '.';
	conv[5] = (xx) % 10 + '0';
	conv[6] = 0;
	return conv;
}
char *c_lcd::itostr3(const int &x) {
	int xx = x;
	if (xx < 0) {
		conv[0] = '-';
		xx = -xx;
	} else if (xx >= 100)
		conv[0] = (xx / 100) % 10 + '0';
	else
		conv[0] = ' ';
	if (xx >= 10)
		conv[1] = (xx / 10) % 10 + '0';
	else
		conv[1] = ' ';
	conv[2] = (xx) % 10 + '0';
	conv[3] = 0;
	return conv;
}

char *c_lcd::itostr3left(const int &xx) {
	if (xx >= 100) {
		conv[0] = (xx / 100) % 10 + '0';
		conv[1] = (xx / 10) % 10 + '0';
		conv[2] = (xx) % 10 + '0';
		conv[3] = 0;
	} else if (xx >= 10) {
		conv[0] = (xx / 10) % 10 + '0';
		conv[1] = (xx) % 10 + '0';
		conv[2] = 0;
	} else {
		conv[0] = (xx) % 10 + '0';
		conv[1] = 0;
	}
	return conv;
}

char *c_lcd::itostr4(const int &xx) {
	if (xx >= 1000)
		conv[0] = (xx / 1000) % 10 + '0';
	else
		conv[0] = ' ';
	if (xx >= 100)
		conv[1] = (xx / 100) % 10 + '0';
	else
		conv[1] = ' ';
	if (xx >= 10)
		conv[2] = (xx / 10) % 10 + '0';
	else
		conv[2] = ' ';
	conv[3] = (xx) % 10 + '0';
	conv[4] = 0;
	return conv;
}

//  convert float to string with 12345 format
char *c_lcd::ftostr5(const float &x) {
	long xx = abs(x);
	if (xx >= 10000)
		conv[0] = (xx / 10000) % 10 + '0';
	else
		conv[0] = ' ';
	if (xx >= 1000)
		conv[1] = (xx / 1000) % 10 + '0';
	else
		conv[1] = ' ';
	if (xx >= 100)
		conv[2] = (xx / 100) % 10 + '0';
	else
		conv[2] = ' ';
	if (xx >= 10)
		conv[3] = (xx / 10) % 10 + '0';
	else
		conv[3] = ' ';
	conv[4] = (xx) % 10 + '0';
	conv[5] = 0;
	return conv;
}
//  convert float to string with +1234.5 format
char *c_lcd::ftostr51(const float &x) {
	long xx = x * 10;
	conv[0] = (xx >= 0) ? '+' : '-';
	xx = abs(xx);
	conv[1] = (xx / 10000) % 10 + '0';
	conv[2] = (xx / 1000) % 10 + '0';
	conv[3] = (xx / 100) % 10 + '0';
	conv[4] = (xx / 10) % 10 + '0';
	conv[5] = '.';
	conv[6] = (xx) % 10 + '0';
	conv[7] = 0;
	return conv;
}
//  convert float to string with +123.45 format
char *c_lcd::ftostr52(const float &x) {
	long xx = x * 100;
	conv[0] = (xx >= 0) ? '+' : '-';
	xx = abs(xx);
	conv[1] = (xx / 10000) % 10 + '0';
	conv[2] = (xx / 1000) % 10 + '0';
	conv[3] = (xx / 100) % 10 + '0';
	conv[4] = '.';
	conv[5] = (xx / 10) % 10 + '0';
	conv[6] = (xx) % 10 + '0';
	conv[7] = 0;
	return conv;
}
//
//=================================================================================================
// 按键解码函数
//=================================================================================================
void c_lcd::encoderFxn(uint8 index) {
    static int8   enc1Mode = HIGH, enc2Mode = HIGH, cun = 0;
    static uint16 codeIndex  = 0;
    //=========================================
    //-- 旋转编码
    //-- 滤波消除跳动干扰
    uint8 code;
    if (index == ENCODER_PULSE1) {
        if (gpio.digitalRead(LCD_ENCODE2))  {exti.setMode(LCD_ENCODE2, EXTI_FALLING);    enc2Mode = LOW;  code = enc1Mode + 2;} 
        else                                {exti.setMode(LCD_ENCODE2, EXTI_RISING );    enc2Mode = HIGH; code = enc1Mode;    } 
        exti.pause  (LCD_ENCODE1);
        exti.resume (LCD_ENCODE2);
    } else {
        if (gpio.digitalRead(LCD_ENCODE1))  {exti.setMode(LCD_ENCODE1, EXTI_FALLING);    enc1Mode = LOW;   code = (enc2Mode<<1) + 1;} 
        else                                {exti.setMode(LCD_ENCODE1, EXTI_RISING );    enc1Mode = HIGH;  code = enc2Mode<<1;      } 
        exti.pause  (LCD_ENCODE2);
        exti.resume (LCD_ENCODE1);
    }
    //-- 采样两个停止位间代码序列
    codeIndex |= (code<<(cun*4));
    if (cun < 3) cun++;
    //-- 解码
    if (code == 0) {
        if      (codeIndex==0x0132 || codeIndex==0x0013) {encoderPos = boundary(encoderPos + 1, -30000, 30000); code = 0xaa;}
        else if (codeIndex==0x0231 || codeIndex==0x0023) {encoderPos = boundary(encoderPos - 1, -30000, 30000); code = 0xaa;}
        codeIndex = cun = 0;
        if (code == 0xaa) {
            if (lcd.sem_lcd_flag == false) {
                lcd.sem_lcd_flag = true;
                isr_sem_send(&lcd.sem_lcd);
            }
        }
    } 
}
//
//======================================================================
// 按键中断函数
//======================================================================
#ifdef __cplusplus
extern "C" {
#endif
void encoderPulse1Isr() {lcd.encoderFxn(ENCODER_PULSE1);}
void encoderPulse2Isr() {lcd.encoderFxn(ENCODER_PULSE2);}
#ifdef __cplusplus
}
#endif
//======================================================================
// STB Marlin
/*
  Fontname: u8g_font_6x10_marlin
  Copyright: Public domain terminal emulator font.  Share and enjoy.
  Capital A Height: 7, '1' Height: 7
  Calculated Max Values w= 6 h=10 x= 2 y= 7 dx= 6 dy= 0 ascent= 8 len=10
  Font Bounding box     w= 6 h= 9 x= 0 y=-2
  Calculated Min Values           x= 0 y=-2 dx= 0 dy= 0
  Pure Font   ascent = 7 descent=-2
  X Font      ascent = 7 descent=-2
  Max Font    ascent = 8 descent=-2
*/
const u8g_fntpgm_uint8_t u8g_font_6x10_marlin[2617] U8G_SECTION(".progmem.u8g_font_6x10_marlin") = {
//const u8g_fntpgm_uint8_t u8g_font_6x10_marlin[1] U8G_SECTION(".progmem.u8g_font_6x10_marlin") = {0
  0,6,9,0,254,7,1,153,3,43,32,255,254,8,254,7,
  254,0,0,0,6,0,0,1,7,7,6,2,0,128,128,128,
  128,128,0,128,3,3,3,6,1,4,160,160,160,5,7,7,
  6,0,0,80,80,248,80,248,80,80,5,7,7,6,0,0,
  32,112,160,112,40,112,32,5,7,7,6,0,0,72,168,80,
  32,80,168,144,5,7,7,6,0,0,64,160,160,64,168,144,
  104,1,3,3,6,2,4,128,128,128,3,7,7,6,1,0,
  32,64,128,128,128,64,32,3,7,7,6,1,0,128,64,32,
  32,32,64,128,5,5,5,6,0,1,136,80,248,80,136,5,
  5,5,6,0,1,32,32,248,32,32,3,3,3,6,1,255,
  96,64,128,5,1,1,6,0,3,248,3,3,3,6,1,255,
  64,224,64,5,7,7,6,0,0,8,8,16,32,64,128,128,
  5,7,7,6,0,0,32,80,136,136,136,80,32,5,7,7,
  6,0,0,32,96,160,32,32,32,248,5,7,7,6,0,0,
  112,136,8,48,64,128,248,5,7,7,6,0,0,248,8,16,
  48,8,136,112,5,7,7,6,0,0,16,48,80,144,248,16,
  16,5,7,7,6,0,0,248,128,176,200,8,136,112,5,7,
  7,6,0,0,48,64,128,176,200,136,112,5,7,7,6,0,
  0,248,8,16,16,32,64,64,5,7,7,6,0,0,112,136,
  136,112,136,136,112,5,7,7,6,0,0,112,136,152,104,8,
  16,96,3,7,7,6,1,255,64,224,64,0,64,224,64,3,
  7,7,6,1,255,64,224,64,0,96,64,128,4,7,7,6,
  1,0,16,32,64,128,64,32,16,5,3,3,6,0,2,248,
  0,248,4,7,7,6,1,0,128,64,32,16,32,64,128,5,
  7,7,6,0,0,112,136,16,32,32,0,32,5,7,7,6,
  0,0,112,136,152,168,176,128,112,5,7,7,6,0,0,32,
  80,136,136,248,136,136,5,7,7,6,0,0,240,72,72,112,
  72,72,240,5,7,7,6,0,0,112,136,128,128,128,136,112,
  5,7,7,6,0,0,240,72,72,72,72,72,240,5,7,7,
  6,0,0,248,128,128,240,128,128,248,5,7,7,6,0,0,
  248,128,128,240,128,128,128,5,7,7,6,0,0,112,136,128,
  128,152,136,112,5,7,7,6,0,0,136,136,136,248,136,136,
  136,3,7,7,6,1,0,224,64,64,64,64,64,224,5,7,
  7,6,0,0,56,16,16,16,16,144,96,5,7,7,6,0,
  0,136,144,160,192,160,144,136,5,7,7,6,0,0,128,128,
  128,128,128,128,248,5,7,7,6,0,0,136,136,216,168,136,
  136,136,5,7,7,6,0,0,136,136,200,168,152,136,136,5,
  7,7,6,0,0,112,136,136,136,136,136,112,5,7,7,6,
  0,0,240,136,136,240,128,128,128,5,8,8,6,0,255,112,
  136,136,136,136,168,112,8,5,7,7,6,0,0,240,136,136,
  240,160,144,136,5,7,7,6,0,0,112,136,128,112,8,136,
  112,5,7,7,6,0,0,248,32,32,32,32,32,32,5,7,
  7,6,0,0,136,136,136,136,136,136,112,5,7,7,6,0,
  0,136,136,136,80,80,80,32,5,7,7,6,0,0,136,136,
  136,168,168,216,136,5,7,7,6,0,0,136,136,80,32,80,
  136,136,5,7,7,6,0,0,136,136,80,32,32,32,32,5,
  7,7,6,0,0,248,8,16,32,64,128,248,3,7,7,6,
  1,0,224,128,128,128,128,128,224,5,7,7,6,0,0,128,
  128,64,32,16,8,8,3,7,7,6,1,0,224,32,32,32,
  32,32,224,5,3,3,6,0,4,32,80,136,5,1,1,6,
  0,255,248,2,2,2,6,2,6,128,64,5,5,5,6,0,
  0,112,8,120,136,120,5,7,7,6,0,0,128,128,176,200,
  136,200,176,5,5,5,6,0,0,112,136,128,136,112,5,7,
  7,6,0,0,8,8,104,152,136,152,104,5,5,5,6,0,
  0,112,136,248,128,112,5,7,7,6,0,0,48,72,64,240,
  64,64,64,5,7,7,6,0,254,120,136,136,120,8,136,112,
  5,7,7,6,0,0,128,128,176,200,136,136,136,3,7,7,
  6,1,0,64,0,192,64,64,64,224,4,9,9,6,1,254,
  16,0,48,16,16,16,144,144,96,5,7,7,6,0,0,128,
  128,136,144,224,144,136,3,7,7,6,1,0,192,64,64,64,
  64,64,224,5,5,5,6,0,0,208,168,168,168,136,5,5,
  5,6,0,0,176,200,136,136,136,5,5,5,6,0,0,112,
  136,136,136,112,5,7,7,6,0,254,176,200,136,200,176,128,
  128,5,7,7,6,0,254,104,152,136,152,104,8,8,5,5,
  5,6,0,0,176,200,128,128,128,5,5,5,6,0,0,112,
  128,112,8,240,5,7,7,6,0,0,64,64,240,64,64,72,
  48,5,5,5,6,0,0,136,136,136,152,104,5,5,5,6,
  0,0,136,136,80,80,32,5,5,5,6,0,0,136,136,168,
  168,80,5,5,5,6,0,0,136,80,32,80,136,5,7,7,
  6,0,254,136,136,152,104,8,136,112,5,5,5,6,0,0,
  248,16,32,64,248,4,7,7,6,1,0,48,64,32,192,32,
  64,48,1,7,7,6,2,0,128,128,128,128,128,128,128,4,
  7,7,6,1,0,192,32,64,48,64,32,192,5,3,3,6,
  0,4,72,168,144,0,0,0,1,0,0,0,0,0,1,0,
  0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
  1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,
  0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,
  0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
  1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,
  0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,
  0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
  1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,
  0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,
  0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
  1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,
  0,0,1,0,0,0,0,0,1,0,0,0,0,0,6,0,
  0,1,7,7,6,2,0,128,0,128,128,128,128,128,5,7,
  7,6,0,255,32,120,160,160,160,120,32,5,7,7,6,0,
  0,48,72,64,224,64,72,176,5,5,5,6,0,0,136,112,
  80,112,136,5,8,8,6,0,255,136,136,80,32,248,32,32,
  32,1,7,7,6,2,0,128,128,128,0,128,128,128,5,8,
  8,6,0,255,112,128,224,144,72,56,8,112,3,1,1,6,
  1,7,160,5,7,7,6,0,0,112,136,168,200,168,136,112,
  4,6,6,6,1,1,112,144,176,80,0,240,6,5,5,6,
  0,0,36,72,144,72,36,4,2,2,6,1,2,240,16,4,
  1,1,6,1,3,240,5,7,7,6,0,0,112,136,232,200,
  200,136,112,5,1,1,6,0,7,248,3,3,3,6,1,4,
  64,160,64,5,6,6,6,0,0,32,32,248,32,32,248,4,
  5,5,6,1,3,96,144,32,64,240,4,5,5,6,1,3,
  224,16,96,16,224,2,2,2,6,2,6,64,128,5,6,6,
  6,0,255,136,136,136,200,176,128,5,7,7,6,0,0,120,
  232,232,104,40,40,40,1,1,1,6,2,3,128,2,2,2,
  6,2,254,64,128,3,5,5,6,1,3,64,192,64,64,224,
  4,6,6,6,1,1,96,144,144,96,0,240,6,5,5,6,
  0,0,144,72,36,72,144,6,9,9,6,0,255,64,192,64,
  64,228,12,20,60,4,6,9,9,6,0,255,64,192,64,64,
  232,20,4,8,28,5,9,9,6,0,255,192,32,64,32,200,
  24,40,120,8,5,7,7,6,0,0,32,0,32,32,64,136,
  112,5,8,8,6,0,0,64,32,112,136,136,248,136,136,5,
  8,8,6,0,0,16,32,112,136,136,248,136,136,5,8,8,
  6,0,0,32,80,112,136,136,248,136,136,5,8,8,6,0,
  0,72,176,112,136,136,248,136,136,5,8,8,6,0,0,80,
  0,112,136,136,248,136,136,5,8,8,6,0,0,32,80,112,
  136,136,248,136,136,6,7,7,6,0,0,60,80,144,156,240,
  144,156,5,9,9,6,0,254,112,136,128,128,128,136,112,32,
  64,5,8,8,6,0,0,64,248,128,128,240,128,128,248,5,
  8,8,6,0,0,16,248,128,128,240,128,128,248,5,8,8,
  6,0,0,32,248,128,128,240,128,128,248,5,8,8,6,0,
  0,80,248,128,128,240,128,128,248,3,8,8,6,1,0,128,
  64,224,64,64,64,64,224,3,8,8,6,1,0,32,64,224,
  64,64,64,64,224,3,8,8,6,1,0,64,160,224,64,64,
  64,64,224,3,8,8,6,1,0,160,0,224,64,64,64,64,
  224,5,7,7,6,0,0,240,72,72,232,72,72,240,5,8,
  8,6,0,0,40,80,136,200,168,152,136,136,5,8,8,6,
  0,0,64,32,112,136,136,136,136,112,5,8,8,6,0,0,
  16,32,112,136,136,136,136,112,5,8,8,6,0,0,32,80,
  112,136,136,136,136,112,5,8,8,6,0,0,40,80,112,136,
  136,136,136,112,5,8,8,6,0,0,80,0,112,136,136,136,
  136,112,5,5,5,6,0,0,136,80,32,80,136,5,7,7,
  6,0,0,112,152,152,168,200,200,112,5,8,8,6,0,0,
  64,32,136,136,136,136,136,112,5,8,8,6,0,0,16,32,
  136,136,136,136,136,112,5,8,8,6,0,0,32,80,0,136,
  136,136,136,112,5,8,8,6,0,0,80,0,136,136,136,136,
  136,112,5,8,8,6,0,0,16,32,136,136,80,32,32,32,
  5,7,7,6,0,0,128,240,136,240,128,128,128,5,7,7,
  6,0,0,112,136,144,160,144,136,176,5,8,8,6,0,0,
  64,32,0,112,8,120,136,120,5,8,8,6,0,0,16,32,
  0,112,8,120,136,120,5,8,8,6,0,0,32,80,0,112,
  8,120,136,120,5,8,8,6,0,0,40,80,0,112,8,120,
  136,120,5,7,7,6,0,0,80,0,112,8,120,136,120,5,
  8,8,6,0,0,32,80,32,112,8,120,136,120,6,5,5,
  6,0,0,120,20,124,144,124,5,7,7,6,0,254,112,136,
  128,136,112,32,64,5,8,8,6,0,0,64,32,0,112,136,
  248,128,112,5,8,8,6,0,0,16,32,0,112,136,248,128,
  112,5,8,8,6,0,0,32,80,0,112,136,248,128,112,5,
  7,7,6,0,0,80,0,112,136,248,128,112,3,8,8,6,
  1,0,128,64,0,192,64,64,64,224,3,8,8,6,1,0,
  64,128,0,192,64,64,64,224,3,8,8,6,1,0,64,160,
  0,192,64,64,64,224,6,10,10,6,0,254,164,168,0,252,
  132,128,128,128,132,252,6,10,10,6,0,254,84,148,0,252,
  132,4,4,4,132,252,5,8,8,6,0,0,40,80,0,176,
  200,136,136,136,5,8,8,6,0,0,64,32,0,112,136,136,
  136,112,4,10,10,6,2,254,48,64,128,144,144,144,144,144,
  144,144,4,10,10,6,0,254,192,32,16,144,144,144,144,144,
  144,144,6,7,7,6,0,1,68,140,140,132,128,64,60,6,
  7,7,6,0,1,136,196,196,132,4,8,240,5,5,5,6,
  0,1,32,0,248,0,32,5,8,8,6,0,0,64,240,200,
  136,136,152,120,16,5,8,8,6,0,0,224,248,136,136,136,
  136,136,248,5,5,5,6,0,1,32,48,248,48,32,5,8,
  8,6,0,0,32,112,248,32,32,32,32,224,5,9,9,6,
  0,255,32,112,168,168,184,136,136,80,32,5,9,9,6,0,
  255,224,128,192,176,168,168,48,40,40,5,9,9,6,0,255,
  248,168,136,136,136,136,136,168,248,5,10,10,6,0,254,32,
  80,80,80,80,136,168,168,136,112
};
//======================================================================
c_lcd   lcd;
//======================================================================

