/*======================================================================  
maker  :jiaxing.shen
date   :2014.12.10
email  :55954781@qq.com
//
参数保存，非易失数据空间
======================================================================*/
#ifndef __EEPROM_H__
#define __EEPROM_H__
//======================================================================
#include "typedefine.h"
#include "Gcode.h"
//======================================================================
//---------------------------------------
// motion 参数数据结构
typedef struct {
    float   acceleration;
    int     jerk_xy;
    int     jerk_z;
    int     jerk_e;
    float   endSpeed;
    int     maxSpeed[MAX_AXIS];
    float   maxAcc[MAX_AXIS];
    float   retractAcc;
    int     E1Mutiply;              
}ts_para_motion;
//
//---------------------------------------
// 自动调平
typedef struct {
    float   adjust_xp;
    float   adjust_xn;
    float   adjust_yp;
    float   adjust_yn;
    float   autoLevXG29;            // 自动调平G29 得到的 X倾斜 修正系数
    float   autoLevYG29;            // 自动调平G29 得到的 Y倾斜 修正系数
    float   autoLevXManu;           // X倾斜 修正手动调节系数（值大，X+高度上升，    层厚变大）
    float   autoLevYManu;           // Y倾斜 修正手动调节系数（值大，Y+高度上升，    层厚变大）
    float   autoLevCeManu;          // 弯曲 修正手动调节系数 （值大，中心点高度上升，层厚变大）
    int     autoLevSentive;         // 敏感度
    int     autoLevBegin;           // 高度开启检测
}ts_para_adjust;
//
//---------------------------------------
// retract 回抽控制
typedef struct {
    bool    enable;
    float   length;
    float   lengthSwap;
    float   feedrate;
    float   zlift;
    float   recoveLength;
    float   recoveLengthSwap;
    float   recoveFeedrate;
}ts_para_retract;
//
//---------------------------------------
// printer  打印机参数
typedef struct {
    float   max_pos_x;
    float   min_pos_x;
    float   max_pos_y;
    float   min_pos_y;
    float   z_home;  
    int     laser_x_offset;
    int     laser_y_offset;
    float   laserFocus;
    int     laserDelay;
    float   deltaRadius;
    float   deltaDiagonalRad;
    float   steps_mm[MAX_AXIS];
    int     steps_pin[MAX_AXIS];
}ts_para_printer;
//
//---------------------------------------
// gcode 参数数据结构
typedef struct {
// 自动温度
    bool    autoTempEnable;     
    float   autoTempMin;
    float   autoTempMax;
    float   autoTempFactor;	
}ts_para_gcode;
//
//---------------------------------------
// temp 参数数据结构
typedef struct {
// pid 
    float   kp;
    float   ki;
    float   kd;	
    float   kc;	
// 自动温度
    bool    autoTempEnable;     
    float   autoTempMin;
    float   autoTempMax;
    float   autoTempFactor;	
}ts_para_temp;
//
//---------------------------------------
//  preheat 参数数据结构
typedef struct {
    int   fanSpeed;
    int   endTemp;
    int   bedTemp;	
}ts_para_preheat;
//
//---------------------------------------
//  温度输出PID 预设值
typedef struct {
    int   tar;
    float iValue;
}ts_para_DTempOut;
//
//---------------------------------------
// eeprom 存储数据结构
typedef struct {
	float ver;
	ts_para_gcode       Gcode;
    ts_para_temp        Temp[4];
    ts_para_DTempOut    DTempOut;
    ts_para_motion      motion;
    ts_para_printer     printer;
    ts_para_adjust      adjust;
    ts_para_retract     retract;
    ts_para_preheat     preHeatAbs;
    ts_para_preheat     preHeatPla;
}ts_eeprom;
//
//---------------------------------------
// 
typedef union {
    ts_eeprom    data; 
    uint32       buf[512];
}tu_para;
//
//---------------------------------------
//
extern const tu_para   EEP;
extern const ts_eeprom EEP_DF;
extern       ts_eeprom para;
//
//======================================================================
#endif
//======================================================================



