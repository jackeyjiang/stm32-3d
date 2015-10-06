/*======================================================================  
maker  :jiaxing.shen
date   :2014.12.10
email  :55954781@qq.com
======================================================================*/
#include "m_include.h"
#include "Eeprom.h"
//======================================================================
// EEPROM 存放地址 出厂默认数据地址
#define EEPROM_PAGE_SIZE		((uint16_t)0x800)
#define EEPROM_ADDR				(0x08000000 + (uint32_t)EEPROM_PAGE_SIZE * 127) 
#define EEPROM_DEFAULT_ADDR		(0x08000000 + (uint32_t)EEPROM_PAGE_SIZE * 126) 
//
//======================================================================
// 出厂设置参数
#define EEP_DEFAULT_VALUE {                                     \
	.ver = 1.0,                                                 \
    .DTempOut = {                                               \
        .tar = 0                                                \
    },                                                          \
    .motion = {                                                 \
        .acceleration = DEFAULT_ACCELERATION,                   \
        .jerk_xy      = DEFAULT_XYJERK,                         \
        .jerk_z       = DEFAULT_ZJERK,                          \
        .jerk_e       = DEFAULT_EYJERK,                         \
        .endSpeed     = MINIMUM_SPEED,                          \
        .E1Mutiply    = 100,                                    \
        .maxSpeed     = {                                       \
            PIN_X_MAX_SPEED,                                    \
            PIN_Y_MAX_SPEED,                                    \
            PIN_Z_MAX_SPEED,                                    \
            PIN_E1_MAX_SPEED,                                   \
        },                                                      \
        .maxAcc = {                                             \
            PIN_X_MAX_ACC_SPEED,                                \
            PIN_Y_MAX_ACC_SPEED,                                \
            PIN_Z_MAX_ACC_SPEED,                                \
            PIN_E1_MAX_ACC_SPEED,                               \
        },                                                      \
        .retractAcc = PIN_A_RETRACT,                            \
    },                                                          \
    .adjust = {                                                 \
        .adjust_xp = DELTA_X_P_ADJUST,                          \
        .adjust_xn = DELTA_X_N_ADJUST,                          \
        .adjust_yp = DELTA_Y_P_ADJUST,                          \
        .adjust_yn = DELTA_X_N_ADJUST,                          \
        .autoLevXG29   = 0,                                     \
        .autoLevYG29   = 0,                                     \
        .autoLevXManu  = 0,                                     \
        .autoLevYManu  = 0,                                     \
        .autoLevCeManu = 0,                                     \
        .autoLevSentive=AUTO_LEAVER_MIN_SENSITIVITY,            \
        .autoLevBegin  =50,                                     \
    },                                                          \
    .printer = {                                                \
        .max_pos_x = MAX_POS_X,                                 \
        .min_pos_x = MIN_POS_X,                                 \
        .max_pos_y = MAX_POS_Y,                                 \
        .min_pos_y = MIN_POS_Y,                                 \
        .z_home    = MAX_POS_Z,                                 \
        .laser_x_offset = LASER_X_OFFSET,                       \
        .laser_y_offset = LASER_Y_OFFSET,                       \
        .laserFocus = 20,                                       \
        .laserDelay = 250,                                      \
        .deltaRadius      = DELTA_RADIUS,                       \
        .deltaDiagonalRad = DELTA_DIAGONAL_ROD,                 \
        .steps_mm = {											\
						PIN_X_STEPS_MM,                         \
						PIN_Y_STEPS_MM,                         \
						PIN_Z_STEPS_MM,                         \
						PIN_E1_STEPS_MM,                        \
				},												\
        .steps_pin = {0, 1, 2, 3},                              \
    },                                                          \
    .preHeatAbs = {                                             \
        .fanSpeed = 255,                                        \
        .endTemp  = 110,                                        \
        .endTemp  = 220                                         \
    },                                                          \
    .preHeatPla = {                                             \
        .fanSpeed = 127,                                        \
        .endTemp  = 80,                                         \
        .endTemp  = 195                                         \
    },                                                          \
    .Temp[e_bed_heat_index] = {                                 \
        .kp = KP_BED_HEATER,                                    \
        .ki = KI_BED_HEATER,                                    \
        .kd = KD_BED_HEATER,                                    \
    },                                                          \
    .Temp[e_end1_heat_index] = {                                \
        .kp = KP_END1_HEATER,                                   \
        .ki = KI_END1_HEATER,                                   \
        .kd = KD_END1_HEATER,                                   \
    },                                                          \
    .Temp[e_end2_heat_index] = {                                \
        .kp = KP_END2_HEATER,                                   \
        .ki = KI_END2_HEATER,                                   \
        .kd = KD_END2_HEATER,                                   \
    },                                                          \
}
//
//======================================================================
//
const tu_para EEP       __attribute__ ((at(EEPROM_ADDR)));                              //2K   EEP ROM
const ts_eeprom EEP_DF  __attribute__ ((at(EEPROM_DEFAULT_ADDR))) = EEP_DEFAULT_VALUE;  //     EEP 出厂值
ts_eeprom para;                                                                         //     EEP 值
//
//======================================================================


