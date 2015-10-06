#ifndef __SYS_CONF_H__
#define __SYS_CONF_H__
//============================================================================
#define __USE_C99_MATH
extern void memCopy(char *t, char *s, int length);
extern char taskRunEnable(void);
//============================================================================
#define DEBUG_AUTO_LEAVER 1
extern char debugOut;
#define  _sq(x)  ((x)*(x))
#define  _abs(x) ((x)>0?(x):-(x))  
#define  boundary(in, low, high) ((in<low) ? (low) : ((in>high) ? (high) : (in)))
#define  max(a, b) ((a>b)?(a):(b))
#define  min(a, b) ((a<b)?(a):(b))
#define  _map(value, fromStart, fromEnd, toStart, toEnd) ((value - fromStart) * (toEnd - toStart) / (fromEnd - fromStart) + toStart)
#define  PI         3.141592653589793238462643
#define  SIN_60     0.8660254037844386
#define  COS_60     0.5
//============================================================================
#include "RTL.h"
#include "typeDefine.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "math.h"
#include "limits.h"
//============================================================================
extern uint32 sysTimer;
//============================================================================
// 位操作地址
#define BB_SRAM_REF      0x20000000
#define BB_SRAM_BASE     0x22000000
#define BB_PERI_REF      0x40000000
#define BB_PERI_BASE     0x42000000
extern volatile uint32* bb_sramp (volatile void *address, uint32 bit);
extern uint8 bb_sram_get_bit     (volatile void *address, uint32 bit); 
extern void bb_sram_set_bit      (volatile void *address, uint32 bit, uint8 val);
extern volatile uint32* bb_perip (volatile void *address, uint32 bit);
extern uint8 bb_peri_get_bit     (volatile void *address, uint32 bit);
extern void bb_peri_set_bit      (volatile void *address, uint32 bit, uint8 val);
extern volatile uint32* __bb_addr(volatile void *address, uint32 bit, uint32 bb_base, uint32 bb_ref);
//============================================================================
// DMA1 使用
// #define DMA1_Channel1 DMA_ADC1
// #define DMA1_Channel2 DMA_SPI1_RX
// #define DMA1_Channel3 DMA_SPI1_TX
// #define DMA1_Channel4 DMA_USART1_TX
// #define DMA1_Channel5 DMA_USART1_RX
// #define DMA1_Channel6 DMA_USART2_RX
// #define DMA1_Channel7 DMA_USART2_TX
//============================================================================
// SD 卡使用
//============================================================================
// SERIAL 使用
#define SERIAL1_USE         TRUE
#define SERIAL1_RX_LENGTH   100
#define SERIAL1_TX_LENGTH   100

#define SERIAL2_USE         FALSE
#define SERIAL2_RX_LENGTH   100
#define SERIAL2_TX_LENGTH   100
//============================================================================
// USB SERIAL 使用
#define USB_SERIAL_USE
#define USB_DISCONNECT_ACTIVE               HIGH
#define USB_DISCONNECT_IDLE                 LOW
#define USB_DISCONNECT_PIN                  44
#define USB_SERIAL_RX_LENGTH                128
#define USB_SERIAL_TX_LENGTH                200
//**************************************************************************//
// 工程使用
//**************************************************************************//
//
//**************************************************************************//
// DO 输出
//**************************************************************************//
#define PIN_DO1     29
#define PIN_DO2     46
//
//**************************************************************************//
// SERVO
//**************************************************************************//
#define PIN_SERVO1  31
#define PIN_SERVO2  32
#define PIN_SERVO3  30
//
//**************************************************************************//
// AI 输出
//**************************************************************************//
#define PIN_AI1     15
#define PIN_AI2     16
#define PIN_AI3     17
#define PIN_AI4     18
//
//**************************************************************************//
// 步进电机
//**************************************************************************//
#define MOTO_IDLE_TIME  3      // (minutes)电机等待没有命令则休眠电机，省点电啦，绿色环保
enum AxisEnum {X_AXIS, Y_AXIS, Z_AXIS, E1_AXIS, MAX_AXIS};
// 步进电机引脚定义
#define PIN_X_DIR       5       // 方向引脚硬件定义
#define PIN_X_STEP      24      // 步进引脚硬件定义     TIME4 
#define PIN_X_ENABLE    22      // 使能引脚硬件定义
#define PIN_X_MAX       38      // 最大限位开关引脚硬件定义
#define PIN_X_MIN       37      // 最小限位开关引脚硬件定义
//
#define PIN_Y_DIR       9       // 方向引脚硬件定义     TIME1  
#define PIN_Y_STEP      2
#define PIN_Y_ENABLE    22
#define PIN_Y_MAX       36
#define PIN_Y_MIN       35
//
#define PIN_Z_DIR       14      // 方向引脚硬件定义     TIME1  
#define PIN_Z_STEP      3
#define PIN_Z_ENABLE    22
#define PIN_Z_MAX       20
#define PIN_Z_MIN       30
//
#define PIN_E1_DIR      21      // 方向引脚硬件定义     TIME1   
#define PIN_E1_STEP     1       // 
#define PIN_E1_ENABLE   22      
#define PIN_E1_MAX      -1
#define PIN_E1_MIN      -1
//
#define PIN_E2_DIR      23      // 方向引脚硬件定义     TIME1  
#define PIN_E2_STEP     0
#define PIN_E2_ENABLE   22
#define PIN_E2_MAX      -1
#define PIN_E2_MIN      -1
//
//========================================
// 引脚有效电平设定
#define PIN_X_DIR_P     LOW            // 方向加 电平。 调试方向反可以 设定 HIGH
#define PIN_Y_DIR_P     LOW            // 方向加 电平。 调试方向反可以 设定 HIGH
#define PIN_Z_DIR_P     LOW            // 方向加 电平。 调试方向反可以 设定 HIGH
#define PIN_E1_DIR_P    LOW            // 方向加 电平。 调试方向反可以 设定 HIGH
#define PIN_E2_DIR_P    LOW            // 方向加 电平。 调试方向反可以 设定 HIGH
//
#define PIN_X_STEP_A    HIGH            // 步进驱动有效电平  查硬件资料
#define PIN_Y_STEP_A    HIGH            // 步进驱动有效电平  查硬件资料
#define PIN_Z_STEP_A    HIGH            // 步进驱动有效电平  查硬件资料
#define PIN_E1_STEP_A   HIGH            // 步进驱动有效电平  查硬件资料
#define PIN_E2_STEP_A   HIGH            // 步进驱动有效电平  查硬件资料
//
#define PIN_X_ENABLE_A  LOW             // 步进允许电平  查硬件资料
#define PIN_Y_ENABLE_A  LOW             // 步进允许电平  查硬件资料
#define PIN_Z_ENABLE_A  LOW             // 步进允许电平  查硬件资料
#define PIN_E1_ENABLE_A LOW             // 步进允许电平  查硬件资料
#define PIN_E2_ENABLE_A LOW             // 步进允许电平  查硬件资料
//
#define PIN_X_MAX_A     HIGH            // 最大限位开关触发电平 查硬件资料
#define PIN_Y_MAX_A     HIGH            // 最大限位开关触发电平 查硬件资料
#define PIN_Z_MAX_A     HIGH            // 最大限位开关触发电平 查硬件资料
#define PIN_E1_MAX_A    HIGH            // 最大限位开关触发电平 查硬件资料
#define PIN_E2_MAX_A    HIGH            // 最大限位开关触发电平 查硬件资料
//
#define PIN_X_MIN_A     LOW             // 最小限位开关触发电平 查硬件资料
#define PIN_Y_MIN_A     LOW             // 最小限位开关触发电平 查硬件资料
#define PIN_Z_MIN_A     LOW             // 最小限位开关触发电平 查硬件资料
#define PIN_E1_MIN_A    LOW             // 最小限位开关触发电平 查硬件资料
#define PIN_E2_MIN_A    LOW             // 最小限位开关触发电平 查硬件资料
//
//========================================
// 电机参数设定
#define PIN_X_STEPS_MM      100     // (16(16micStps) * (360/1.8(1.8ang))) / (16(teeth)*2(belt))
#define PIN_Y_STEPS_MM      100     // (16(16micStps) * (360/1.8(1.8ang))) / (16(teeth)*2(belt))
#define PIN_Z_STEPS_MM      100     // (16(16micStps) * (360/1.8(1.8ang))) / (16(teeth)*2(belt))
#define PIN_E1_STEPS_MM     100     // (16(16micStps) * (360/1.8(1.8ang))) / (3.1415(PI) * 6.4(pulley_diameter))
#define PIN_E2_STEPS_MM     100     // (16(16micStps) * (360/1.8(1.8ang))) / (3.1415(PI) * 6.4(pulley_diameter))
//
#define PIN_X_MAX_SPEED     100     // mm/sec
#define PIN_Y_MAX_SPEED     100     // mm/sec
#define PIN_Z_MAX_SPEED     100     // mm/sec
#define PIN_E1_MAX_SPEED    50      // mm/sec
#define PIN_E2_MAX_SPEED    50      // mm/sec
//
#define PIN_X_MAX_ACC_SPEED  (PIN_X_MAX_SPEED/0.05)    // mm/sec^2 (speed)/(t sec)
#define PIN_Y_MAX_ACC_SPEED  (PIN_Y_MAX_SPEED/0.05)    // mm/sec^2 (speed)/(t sec)
#define PIN_Z_MAX_ACC_SPEED  (PIN_Z_MAX_SPEED/0.05)    // mm/sec^2 (speed)/(t sec)
#define PIN_E1_MAX_ACC_SPEED (PIN_E1_MAX_SPEED/0.1)    // mm/sec^2 (speed)/(t sec)
#define PIN_E2_MAX_ACC_SPEED (PIN_E2_MAX_SPEED/0.1)    // mm/sec^2 (speed)/(t sec)
#define PIN_A_RETRACT        3000
//
//**************************************************************************//
// 打印机机械参数
//**************************************************************************//
#define MAX_POS_X   70          // 最大坐标
#define MAX_POS_Y   70
#define MAX_POS_Z   250
#define LASER_X_OFFSET  -50     // 激光头偏移
#define LASER_Y_OFFSET  -50     // 激光头偏移
//
#define MIN_POS_X   -70         // 最小坐标
#define MIN_POS_Y   -70
//
#define DEFAULT_ACCELERATION        2000        // 默认加速度 mm/s^2
//
#define DEFAULT_XYJERK      10.0    // mm/sec       // 连接速度
#define DEFAULT_ZJERK       10.0    // mm/sec
#define DEFAULT_EYJERK      2       // mm/sec
#define MINIMUM_SPEED       0.05    // mm/sec       // 结束时的速度  
//
// DELTA 机型参数
#define DELTA_SEGMENTS_MM           1           // 每mm分片数
#define DELTA_DIAGONAL_ROD          324         // 斜棒的球心球心间距
#define DELTA_RADIUS                136         // 半径
//
#define DELTA_X_P_ADJUST            (1.0)       // X+输出 1，实际测量输出 1.1 修正（1.1 测量值）
#define DELTA_X_N_ADJUST            (1.0)       // X-输出 1，实际测量输出 1.1 修正（1.1 测量值）
#define DELTA_Y_P_ADJUST            (1.0)       // X+输出 1，实际测量输出 1.1 修正（1.1 测量值）
#define DELTA_Y_N_ADJUST            (1.0)       // X-输出 1，实际测量输出 1.1 修正（1.1 测量值）
//
//**************************************************************************//
// 加热控制
//**************************************************************************//
enum enum_heat {
    e_bed_heat_index,
    e_end1_heat_index,
    e_end2_heat_index,
    e_box_heat_index,
};
#define PID_DT                  50     // 调整时间ms
#define PID_FUNCTION_RANGE      10
#define PID_POWER_PROTECT       70      // 最大输出功率
#define AD_OVER_SAMPLE_NUM      16
//
//========================================
// 加热床温度控制
#define PIN_BED_HEATER_AD      PIN_AI1      // 温度传感器端口
#define PIN_BED_HEATER_OUT     6            // 加热控制输出端口  6
#define PIN_BED_OUT_ACTIVE     LOW          // 引脚输出有效
#define MAX_BED_HEATER         150          // 最大温度值
#define MIN_BED_EXTRUDE        99           // 挤出机动作热头最低温度
#define MIN_BED_HEATER         5            // 最低温度值
#define KP_BED_HEATER          21658.72     // P 系数
#define KI_BED_HEATER          1517.25      // I 系数
#define KD_BED_HEATER          27826.05     // D 系数
#define SENSER_BED_HEATER      GT104_2      // 传感器类型
#define PULLUP_BED_HEATER      1.0          // 上拉电阻 1K
//
//========================================
// 加热头1温度控制
#define PIN_END1_HEATER_AD     PIN_AI2      // 温度传感器端口
#define PIN_END1_HEATER_OUT    27           // 加热控制输出端口 27
#define PIN_END1_OUT_ACTIVE    LOW          // 引脚输出有效
#define MAX_END1_HEATER        250          // 最大温度值
#define MIN_END_EXTRUDE        170          // 挤出机动作热头最低温度
#define MIN_END1_HEATER        5            // 最低温度值
#define KP_END1_HEATER         4363.8659    // P 系数
#define KI_END1_HEATER         161.0284     // I 系数
#define KD_END1_HEATER         10643.4691   // D 系数
#define SENSER_END1_HEATER     GT104_2      // 传感器类型
#define PULLUP_END1_HEATER     1.0          // 上拉电阻 1K
//
//========================================
// 加热头2温度控制
#define PIN_END2_HEATER_AD     PIN_AI3      // 温度传感器端口
#define PIN_END2_HEATER_OUT    28           // 加热控制输出端口
#define PIN_END2_OUT_ACTIVE    HIGH         // 引脚输出有效
#define MAX_END2_HEATER        250          // 最大温度值
#define MIN_END2_EXTRUDE       170          // 挤出机动作热头最低温度
#define MIN_END2_HEATER        5            // 最低温度值
#define KP_END2_HEATER         4363.8659    // P 系数
#define KI_END2_HEATER         161.0284     // I 系数
#define KD_END2_HEATER         10643.4691   // D 系数
#define SENSER_END2_HEATER     GT104_2      // 传感器类型
#define PULLUP_END2_HEATER     1.0          // 上拉电阻 1K
//
//========================================
// 温度等待稳定
#define TEMP_RESIDENCY_TIME     10          // M109 等待温度条件持续时间
#define TEMP_RESIDENCY_T_WIN    1           // 温度计时触发温度 目标减 
#define TEMP_RESIDENCY_WIN      3           // 温度条件范围
//
//**************************************************************************//
// 风扇控制
//**************************************************************************//
#define FAN_END1_START          80         // 80度降温风扇开启
#define PIN_END1_FAN            PIN_DO1
#define PIN_END1_FAN_ACTIVE     HIGH
#define FAN_END2_START          80         // 80度降温风扇开启
#define PIN_END2_FAN            PIN_DO2
#define PIN_END2_FAN_ACTIVE     HIGH
//
//**************************************************************************//
// MELZI V2.0 LCD
//**************************************************************************//
#define LANGUAGE_CHOICE         1
#define LCD_WIDTH               20
#define LCD_HEIGH               5
//
#define LCD_PIN_CLK             34      
#define LCD_SPI_DATA            19     
#define LCD_PIN_CS              43
#define LCD_ENCODE1             25
#define LCD_ENCODE2             26
#define LCD_ENCODENT            41
#define LCD_ENCODENT_ACT        HIGH
#define LCD_BUZZER_PIN          42
#define LCD_RESET_PIN           4
//
//**************************************************************************//
// 自动调平
//**************************************************************************//
#define AUTO_LEAVER_PIN                 PIN_AI4     // 自动调平检测引脚
#define AUTO_LEAVER_MIN_SENSITIVITY     50          // 自动调平检测最小 AD 变化
#define AUTO_LEAVER_DETECT_H            3           // 自动调平探测 提升高度
//
//== 串口使用 ==============
#define serialCommu             usbSerial1
#define serialDebug             serial1
#define testPin                 PIN_SERVO1
#define testDac                 DAC_CHANNEL_2
//============================================================================
extern void mainLoopTask(void);
//============================================================================
//
//============================================================================
#endif



