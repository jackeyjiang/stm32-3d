//======================================================================
#ifndef __LCD_H__
#define __LCD_H__
//======================================================================
#include "typeDefine.h"
#include "commu.h"
#include "RTL.h"
//======================================================================
#define ENCODER_PULSE1  0
#define ENCODER_PULSE2  1
#define ENCODER_ENTER   2
//
//=================================================================================================
// 建立一个页面
// START_MENU
//
// MENU_ITEM
// .
// .
// .
//
// END_MENU
//=================================================================================================
// 窗口 开始
#define START_MENU() do {                                               \
    uint8 encoderT = encoderPos;                                        \
    if (encoderPos < 0) encoderPos = encoderT = 0;                      \
    if (encoderT < menuViewOffset) menuViewOffset = encoderT;           \
    lineNr = menuViewOffset;                                            \
    for (drawLineNr=0; drawLineNr<LCD_HEIGH; drawLineNr++, lineNr++) {  \
        menuItemNr = 0;
//=======================================================================
// 菜单控件
#define MENU_ITEM(type, label, args...) do {                            \
        if (menuItemNr == lineNr) {                                     \
            if (encoderPos == menuItemNr) {                             \
                drawmenu_##type##_selected(drawLineNr, label , ##args); \
            }else{                                                      \
                drawmenu_##type           (drawLineNr, label , ##args); \
            }                                                           \
            if (encoderEnt && (encoderPos == menuItemNr)) {             \
                menu_action_##type(args);                               \
                menu_action_feedBack();                                 \
                return;                                                 \
            }                                                           \
        }                                                               \
        menuItemNr++;                                                   \
        } while(0)
//=======================================================================
// 窗口 结束
#define END_MENU()                                                      \
        if (encoderPos >= menuItemNr)                                   \
            encoderPos = menuItemNr-1;                                  \
        if (encoderPos >= menuViewOffset + LCD_HEIGH) {                 \
            menuViewOffset = encoderPos - LCD_HEIGH + 1;                \
            lineNr         = menuViewOffset - 1;                        \
            drawLineNr     = -1;                                        \
        }                                                               \
    }} while(0)
//
//==================================================================================================
// 立即数据数据
// 旋钮开关 旋转，事件立即执行
//==================================================================================================
#define MENU_ITEM_IMMEDIATALY(type, label, args...) do {                \
        MENU_ITEM(immediataly_##type, label, label , ##args );          \
    } while(0)
#define menu_immediataly_type(_type, _name, _strFunc, scale)            \
void c_lcd::menu_immediataly_##_name() {                                \
        drawedit(editLabel,_strFunc(*((_type*)editValue)));             \
        if (encoderPos) {                                               \
            if (((float)encoderPos/scale + *((_type*)editValue)) > maxEditValue)        \
                *((_type*)editValue) = maxEditValue;                    \
            else if (((float)encoderPos/scale + *((_type*)editValue)) < minEditValue)   \
                *((_type*)editValue) = minEditValue;                    \
            else                                                        \
                *((_type*)editValue) += (float)encoderPos/scale;        \
            (this->*callbackFunc)();                                    \
            encoderPos = 0;                                             \
        }                                                               \
        if (encoderEnt) {                                               \
            currentMenu = prevMenu;                                     \
            encoderPos  = prevEncoderPos;                               \
            menu_action_feedBack();                                     \
        }}                                                              \
void c_lcd::menu_action_immediataly_ ## _name (const char* pstr, _type* ptr, _type minValue, _type maxValue, tdLcdFxn callback) { \
        prevMenu       = currentMenu;                                   \
        prevEncoderPos = encoderPos;                                    \
        currentMenu    = &c_lcd::menu_immediataly_##_name;              \
        editLabel = pstr;                                               \
        editValue = ptr;                                                \
        minEditValue = minValue;                                        \
        maxEditValue = maxValue;                                        \
        encoderPos   = 0;                                               \
        callbackFunc = callback;                                        \
    }
//
//=================================================================================================
// 编辑数据
// 和立即数据数据不同，在确认键按下数据才输入
//=================================================================================================
#define MENU_ITEM_EDIT(type, label, args...) do {                       \
        MENU_ITEM(edit_##type, label, label, ##args );                 \
    } while(0)       
#define menu_edit_type(_type, _name, _strFunc, scale)                   \
void c_lcd::menu_edit_##_name() {                                       \
        if ((int32_t)encoderPos < minEditValue)                         \
            encoderPos = minEditValue;                                  \
        if ((int32_t)encoderPos > maxEditValue)                         \
            encoderPos = maxEditValue;                                  \
        drawedit(editLabel,_strFunc(((_type)encoderPos) / scale));      \
        if (encoderEnt) {                                               \
            *((_type*)editValue) = ((_type)encoderPos) / scale;         \
            menu_action_feedBack();                                     \
            currentMenu = prevMenu;                                     \
            encoderPos  = prevEncoderPos;                               \
        }}                                                              \
void c_lcd::menu_action_edit_ ## _name(const char* pstr, _type* ptr, _type minValue, _type maxValue) { \
        prevMenu       = currentMenu;                                   \
        prevEncoderPos = encoderPos;                                    \
        currentMenu    = &c_lcd::menu_edit_##_name;                     \
        editLabel = pstr;                                               \
        editValue = ptr;                                                \
        minEditValue = minValue * scale;                                \
        maxEditValue = maxValue * scale;                                \
        encoderPos   = (*ptr) * scale;                                  \
        }                                                               
//
//=================================================================================================
// 标签数据
// 只显示，不操作 action 为空函数
//=================================================================================================
#define MENU_ITEM_LABEL(type, label, args...) do {                      \
        MENU_ITEM(label_##type, label, label, ##args );                 \
    } while(0)       
#define menu_label_type(_type, _name, _strFunc)                         \
void c_lcd::menu_action_label_##_name(const char* pstr, _type* ptr) {   \
        }                                                               
//
//=======================================================================
// 系统状态
//=======================================================================
typedef struct {
    int mainLoopStkP;
    int sdReaderStkP;
    int commuStkP;
    int gcodeStkP;
    int lcdStkP;
}ts_sysStatus;    
//
//======================================================================
// LCD 类
//======================================================================
class c_lcd {
public:
    void init_menu  (void);
    void update();
    ts_sysStatus    sysStatus;
    void encoderFxn (uint8);
    void getStatus  (void);
    OS_SEM  sem_lcd;
    bool    sem_lcd_flag;
    uint8   buzzerFlag;
    uint8   laserPowerOut;
    bool    encoderEnt;             // 确认键
    bool    resetFlag;
    bool    pauseFlag;
    bool    laserModle;
    int     autoTurnBed;
    int     autoTurnEnd;
//
//-- 活动标示
    uint32  liveTimer;
    bool    liveFlag;
    bool    taskRunEnable;
//
//-- GCODE 
    ts_commu_buf   *pLcdBuf;
    void function_storeEprom (void);
    void function_cooldown   (void);
private:

//-- 菜单函数
    void main_menu        (void);
    void tune_menu        (void);
    void printer_menu     (void);
    void adjust_menu      (void);
    void status_menu      (void);
    void prepare_menu     (void);
    void control_menu     (void);
    void move_menu        (void);
    void move_menu_load   (void);
    void temperature_menu (void);
    void motion_menu      (void);
    void retract_menu     (void);
    void preheatAbs_menu  (void);
    void preheatPla_menu  (void);
    void sys_status_menu  (void);
//-- 菜单回调函数
    void menu_action_feedBack   (void) { 
            encoderEnt = 0;
            os_sem_send(&sem_lcd);
         }
    //
    //== 菜单控件
    void menu_action_back       (void (c_lcd::*) (void));
    void menu_action_function   (void (c_lcd::*) (void));
    void menu_action_submenu    (void (c_lcd::*) (void));
    void menu_action_gcode      (const char *gcode);
   
    //
    float   minEditValue;
    float   maxEditValue;
    void   *editValue;
    const char  *editLabel;
    //
    //== 编辑数据
    void menu_edit_bool      ();
    void menu_edit_int3      ();
    void menu_edit_float3    ();
    void menu_edit_float32   ();
    void menu_edit_float5    ();
    void menu_edit_float51   ();
    void menu_edit_float52   ();
    void menu_edit_long5     ();
    void menu_action_edit_bool      (const char* pstr, bool* ptr);
    void menu_action_edit_int3      (const char* pstr, int* ptr, int minValue, int maxValue);
    void menu_action_edit_float3    (const char* pstr, float* ptr, float minValue, float maxValue);
    void menu_action_edit_float32   (const char* pstr, float* ptr, float minValue, float maxValue);
    void menu_action_edit_float5    (const char* pstr, float* ptr, float minValue, float maxValue);
    void menu_action_edit_float51   (const char* pstr, float* ptr, float minValue, float maxValue);
    void menu_action_edit_float52   (const char* pstr, float* ptr, float minValue, float maxValue);
    void menu_action_edit_long5     (const char* pstr, uint32* ptr, uint32 minValue, uint32 maxValue);
    //
    //== 立即数据
    void menu_immediataly_move01  ();
    void menu_immediataly_move1   ();
    void menu_immediataly_move10  ();
    void menu_action_immediataly_move01   (const char* pstr, float* ptr, float minValue, float maxValue, void (c_lcd::*) (void));
    void menu_action_immediataly_move1    (const char* pstr, float* ptr, float minValue, float maxValue, void (c_lcd::*) (void));
    void menu_action_immediataly_move10   (const char* pstr, float* ptr, float minValue, float maxValue, void (c_lcd::*) (void));
    //
    //== 标签数据
    void menu_label_int3();
    void menu_action_label_int3 (const char* pstr, int* ptr);
    void menu_label_int4();
    void menu_action_label_int4 (const char* pstr, int* ptr);
//-- 功能实现代码
    float xMove, yMove, zMove, e1Move, e2Move;
    void function_move           (void);
    void function_Focus          (void);
    void function_autoStartSd    (void);
    void function_setZzeroPos    (void);
    void function_reCalDelta     (void);
    void function_preheatAbs     (void);
    void function_preheatPla     (void);
    void function_loadEprom      (void);
    void function_reStoreFailsafe(void);   
    void function_pausePrint     (void);
    void function_resumePrint    (void);  
    void function_stopPrint      (void);  
    void function_cardMenu       (void);
    void function_initCard       (void);
    void function_openfile       (void);
    void function_autoTurn       (void);
    void (c_lcd::*currentMenu ) (void);
    void (c_lcd::*prevMenu    ) (void);
    void (c_lcd::*callbackFunc) (void);
    bool blink;
    char *ftostr3    (const float &x);
    char *itostr2    (const uint8 &x);
    char *ftostr31   (const float &x);   // 123.4
    char *ftostr31ns (const float &x);   // 123.4
    char *ftostr32   (const float &x);   // +1.23 格式化5位浮点
    char *itostr31   (const int &xx);    // +123.1  格式化4位整数
    char *itostr3    (const int &x);     // +123    格式化3位整数
    char *itostr3left(const int &xx);    // +123    格式化3位整数
    char *itostr4    (const int &xx);    // +1234   格式化4位整数
    char *ftostr5    (const float &x);   // +12345  格式化5位浮点
    char *ftostr51   (const float &x);   // +1234.5 格式化5位浮点
    char *ftostr52   (const float &x);   // +123.45 格式化5位浮点
    char conv[8];
    const char *statusMessage;
//
//-- 菜单
    int8    menuViewOffset;             // 菜单显示坐标
    int8    menuItemNr;
    int8    lineNr;
    int8    drawLineNr;
    void    drawedit                   (const char* pstr, char* value);
    void    drawmenu_generic           (uint8 row,    const char *pstr,  char pre_char, char post_char);
    void    drawmenu_edit_generic      (uint8 row,    const char* pstr,  char pre_char, char* data);
    void    drawmenu_edit_generic_P    (uint8 row,    const char* pstr,  char pre_char, const char* data);
//
//-- 旋转开关按键
    int16   encoderPos;             // encoderPosition
    int16   prevEncoderPos;         // 上级菜单Encoder
};

typedef void (c_lcd::*tdLcdFxn)(void);
extern __task void lcdTask(void);
//======================================================================
#ifdef __cplusplus
extern "C" {
#endif
extern void encoderPulse1Isr();
extern void encoderPulse2Isr();
extern void encoderEnterIsr ();
#ifdef __cplusplus
}
#endif
//======================================================================
extern c_lcd lcd;
//======================================================================
#endif  //__LCD_H__








