#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__
#include "typeDefine.h"

typedef struct {
    uint32   resistor1000;  //k
    uint16   temp;          //c
}ts_resistorTab;

typedef struct {
    uint8  pinAd;
    uint8  pinOut;
    uint8  pinOutAct;
    uint16 max;
    uint8  min;
    float  pidRang;
    float  kp;
    float  ki;
    float  kd;
    const ts_resistorTab *tempTab;
    uint16 pullUp1000;
    uint16 tabSize;
}ts_temperature;


//====================================
// code:    46 
// RO:      0
// RW:      50
// ZI:      64
//====================================
class c_temp {
public:
    c_temp(ts_temperature *);
    void    setTarTemp(int tempT)   {tarTemp = tempT;   }
    float   getTemperature   ()     {return temperature;}
    int     getTarTemperature()     {return tarTemp;    }
    uint16  getOut()                {return outValue;   }
    float   getPidI()               {return iValue;     }
    bool    isHeat()                {return tarTemp > temperature;}
    void    outManage  ();
    float   sampleTemp ();
    void    setOut(uint32 comp);
    void    setDefalutI (float defI){iValue = defI;}
    uint16  pidAutoTune (float tempT, int ncycles);
    int     tarTemp;
    float   temperature;
    uint16  outMax;
    uint16  outMin;
private:
    uint16  outValue;
    uint16  runFlag;
    bool    AutoTurningFlag;
    //== pid
    uint16  pid();
    uint8   pidReset;
    float   pValue;
    float   iValue;
    float   dValue;
    float   pidOut;
    float   dTemp_1;
    //==
public:
    ts_temperature *tempDev;
};
extern c_temp tempHotBed;
extern c_temp tempHotEnd1;
extern c_temp tempHotEnd2;
extern c_temp tempHotBox;
#endif
