//=================================================================
#include "m_include.h"
#include "temperature.h"
//=================================================================
// http://shop.arcol.hu/static/datasheets/thermistors.pdf
// 104GT-2 RESISTOR TAB
const ts_resistorTab GT104_2[] = {
    {.resistor1000 =      2, .temp = 500},
    {.resistor1000 =     80, .temp = 300},
    {.resistor1000 =     93, .temp = 290},
    {.resistor1000 =    108, .temp = 280},
    {.resistor1000 =    126, .temp = 270},
    {.resistor1000 =    148, .temp = 260},
    {.resistor1000 =    174, .temp = 250},
    {.resistor1000 =    207, .temp = 240},
    {.resistor1000 =    247, .temp = 230},
    {.resistor1000 =    297, .temp = 220},
    {.resistor1000 =    360, .temp = 210},
    {.resistor1000 =    439, .temp = 200},
    {.resistor1000 =    541, .temp = 190},
    {.resistor1000 =    671, .temp = 180},
    {.resistor1000 =    841, .temp = 170},
    {.resistor1000 =   1064, .temp = 160},
    {.resistor1000 =   1360, .temp = 150},
    {.resistor1000 =   1758, .temp = 140},
    {.resistor1000 =   2298, .temp = 130}, 
    {.resistor1000 =   3043, .temp = 120}, 
    {.resistor1000 =   4082, .temp = 110}, 
    {.resistor1000 =   5556, .temp = 100}, 
    {.resistor1000 =   7686, .temp = 90}, 
    {.resistor1000 =  10800, .temp = 80}, 
    {.resistor1000 =  15440, .temp = 70}, 
    {.resistor1000 =  22510, .temp = 60}, 
    {.resistor1000 =  33490, .temp = 50}, 
    {.resistor1000 =  50960, .temp = 40}, 
    {.resistor1000 =  79360, .temp = 30}, 
    {.resistor1000 = 126800, .temp = 20}, 
    {.resistor1000 = 208600, .temp = 10}, 
    {.resistor1000 = 353700, .temp = 0}, 
};
//
//====================================
// 热床 定义
ts_temperature temperatureBed = {
    .pinAd      = PIN_BED_HEATER_AD,
    .pinOut     = PIN_BED_HEATER_OUT,
    .pinOutAct  = PIN_BED_OUT_ACTIVE,
    .max        = MAX_BED_HEATER,
    .min        = MIN_BED_HEATER,
    .pidRang    = PID_FUNCTION_RANGE,
    .kp         = EEP.data.Temp[e_bed_heat_index].kp,
    .ki         = EEP.data.Temp[e_bed_heat_index].ki * PID_DT / 1000,
    .kd         = EEP.data.Temp[e_bed_heat_index].kd * 1000 / PID_DT,
    .tempTab    = SENSER_BED_HEATER,
    .pullUp1000 = PULLUP_BED_HEATER * 1000,
    .tabSize    = sizeof(SENSER_BED_HEATER)/sizeof(ts_resistorTab),  // 电阻表长度
};
c_temp tempHotBed(&temperatureBed);
//
//====================================
// 热头1 定义
ts_temperature temperatureEnd1 = {
    .pinAd      = PIN_END1_HEATER_AD,
    .pinOut     = PIN_END1_HEATER_OUT,
    .pinOutAct  = PIN_END1_OUT_ACTIVE,
    .max        = MAX_END1_HEATER,
    .min        = MIN_END1_HEATER,
    .pidRang    = PID_FUNCTION_RANGE,
    .kp         = EEP.data.Temp[e_end1_heat_index].kp,
    .ki         = EEP.data.Temp[e_end1_heat_index].ki * PID_DT / 1000,
    .kd         = EEP.data.Temp[e_end1_heat_index].kd * 1000 / PID_DT,
    .tempTab    = SENSER_END1_HEATER,
    .pullUp1000 = PULLUP_END1_HEATER * 1000,
    .tabSize    = sizeof(SENSER_END1_HEATER)/sizeof(ts_resistorTab),  // 电阻表长度
};
c_temp tempHotEnd1(&temperatureEnd1);
//
//====================================
// 热头2 定义
ts_temperature temperatureEnd2 = {
    .pinAd      = PIN_END2_HEATER_AD,
    .pinOut     = PIN_END2_HEATER_OUT,
    .pinOutAct  = PIN_END2_OUT_ACTIVE,
    .max        = MAX_END2_HEATER,
    .min        = MIN_END2_HEATER,
    .pidRang    = PID_FUNCTION_RANGE,
    .kp         = EEP.data.Temp[e_end2_heat_index].kp,
    .ki         = EEP.data.Temp[e_end2_heat_index].ki * PID_DT / 1000,
    .kd         = EEP.data.Temp[e_end2_heat_index].kd * 1000 / PID_DT,
    .tempTab    = SENSER_END2_HEATER,
    .pullUp1000 = PULLUP_END2_HEATER * 1000,
    .tabSize    = sizeof(SENSER_END2_HEATER)/sizeof(ts_resistorTab),  // 电阻表长度
};
c_temp tempHotEnd2(&temperatureEnd2);
//====================================
// 构造函数
//====================================
c_temp::c_temp(ts_temperature *devIn) {
    tempDev = devIn;
    //1.== AD 采样引脚 == 
    gpio.pinMode(tempDev->pinAd, INPUT_ANALOG);
    
    //2.== 输出引脚 设定
    setOut(0);
    
    //2.== PWM 周期设定 10ms
    gpio.setPwmFormat(tempDev->pinOut, 10, tempDev->pinOutAct);
    outMax = gpio.getPwmPeriod(tempDev->pinOut);
    outMin = 0;
    
    runFlag = false;
}
//
//====================================
// 获得温度数据
//====================================
float c_temp::sampleTemp() {
    uint32 ad = 0, resistor1000;
    float tempT = 0;
    int   i;
    //---------------------------------------
    //1. -- 采样AD 值
    ad = adc.analogRead(tempDev->pinAd);
    if (ad == 0xfff) {
        temperature = 0.0;
        return 0.0;
    }
    
    //---------------------------------------
    //2. -- 通过AD 值和 上拉电阻，计算当前电阻值
    // ad = resistor * 0xfff(bit12)/ (resistor + pullup) =>
    // resistor = pullup*ad / (0xfff-ad)
    resistor1000 = ad * tempDev->pullUp1000/(0xfff-ad);
    //---------------------------------------
    //3. -- 查询电阻表 得到温度值  
    for (i = 1; i<tempDev->tabSize; i++) {
         if (resistor1000 < tempDev->tempTab[i].resistor1000) {
             tempT = (float)tempDev->tempTab[i-1].temp -
                     (float)(resistor1000-tempDev->tempTab[i-1].resistor1000) *     \
                     (tempDev->tempTab[i-1].temp - tempDev->tempTab[i].temp) /      \
                     (tempDev->tempTab[i].resistor1000 - tempDev->tempTab[i-1].resistor1000);
             break;
         }
     }
    //---------------------------------------
    // 输出温度值
    if ((i==resistor1000>tempDev->tabSize) || (i==1))
        tempT = 0.0;    // 断线或者温度过低
    temperature = tempT;
    return tempT;
}

//====================================
// pid 自动整定
// http://brettbeauregard.com/blog/2012/01/arduino-pid-autotune-library/
//====================================
uint16 c_temp::pidAutoTune(float setPoint, int ncycles) {
    AutoTurningFlag = true;
    
    float max = 0, min = 10000;
    uint32 t1 = os_time_get(), t2 = os_time_get(), printTime = os_time_get();
    int32  bias, d , t_hight = 0, t_low = 0;
    boolean heating = true;
    int16  cycles = 0;
    
    serialCommu.println("PID Autotune start");
    setOut(outMax);
    bias = d = outMax/2;
    for (;;) {
        os_dly_wait(10);
        
        sampleTemp();
        max = max(temperature, max);
        min = min(temperature, min);
        if (heating == true && temperature > setPoint && (os_time_get() - t2 > 5000)) {
            heating = false;
            t1 = os_time_get();
            t_hight = t1 - t2;
            setOut(bias - d);
            max = temperature;
        }
        
        if (heating == false && temperature < setPoint && (os_time_get() - t1 > 5000)) {
            heating = true;
            t2 = os_time_get();
            t_low = t2 - t1;
            if (cycles > 0) {
                bias += (d * (t_hight - t_low))/(t_hight+t_low);
                bias  = boundary(bias, outMin, outMax);
                (bias > outMax/2) ? (d = outMax - bias -1) : (d = bias);
                serialCommu.print(" bias: ");  serialCommu.print(bias);
                serialCommu.print(" d: ");     serialCommu.print(d);
                serialCommu.print(" max: ");   serialCommu.print(max);
                serialCommu.print(" min: ");   serialCommu.println(min);
            }
            if (cycles > 2) {
                float Ku = (4.0 * d)/(3.14159 * (max-min));
                float Tu = ((float)(t_low+t_hight)/1000.0);
                serialCommu.print(" Ku: ");   serialCommu.print  (Ku);
                serialCommu.print(" Tu: ");   serialCommu.println(Tu);
                serialCommu.println("Classic PID ---");
                serialCommu.print(" Kp: ");   serialCommu.print  (Ku * 0.6);
                serialCommu.print(" Ki: ");   serialCommu.print  (Ku * 0.6 * 1.2 / Tu);
                serialCommu.print(" Kd: ");   serialCommu.println(Ku * 0.6 * Tu  * 0.075);
            }
            setOut(bias + d);
            min = temperature;
            cycles ++;
        }
        //== 回显 ==
        if ((os_time_get() - printTime) > 2000) {
            printTime = os_time_get();
            serialCommu.print(" T:");    serialCommu.print  (tempHotEnd1.getTemperature(),    1);
            serialCommu.print(" /"   );  serialCommu.print  (tempHotEnd1.getTarTemperature(), 1);
            serialCommu.print(" B:");    serialCommu.print  (tempHotBed.getTemperature(),     1);
            serialCommu.print(" /"   );  serialCommu.print  (tempHotBed.getTarTemperature(),  1);
            serialCommu.print(" @:"   );  serialCommu.print (tempHotEnd1.getOut());
            serialCommu.print(" B@:"   );  serialCommu.println(tempHotBed.getOut() );
        }
        
        //== 过温 ======
        if (temperature > (setPoint + 20.0)) {
            serialCommu.println(" PID Autotune failed! Temperature too hight ");
            AutoTurningFlag = false;
            return false;
        }
        
        //== 到达次数 ==
        if (ncycles < cycles) {
            serialCommu.println(" PID Autotune finished! Put the last Kp, Ki, and Kd into Configuration.h ");
            AutoTurningFlag = false;
            return true;
        }
    }
}
//====================================
// pid 控制
//====================================
uint16 c_temp::pid() {
    float   err = (float)tarTemp - temperature;
    
    if (err > tempDev->pidRang) {
        pidReset = true;
        return 0xffff;
    }
    if (err < -tempDev->pidRang) {
        pidReset = true;
        return 0;
    }
    if (pidReset) {
        pidReset   = false;
        dTemp_1    = temperature;
        iValue     = 0; 
    }
    pValue  = tempDev->kp * err;
    iValue += tempDev->ki * err;
    iValue  = boundary(iValue, 0, outMax);
    dValue  = tempDev->kd * 0.05*(temperature-dTemp_1)+dValue*0.95;
    dTemp_1 = temperature;
    pidOut = boundary(pValue+iValue-dValue, 0, outMax);
    return (uint16)pidOut;
}

//====================================
// 输出
//====================================
void c_temp::setOut(uint32 outT) {
    outValue = _map(outT, outMin, outMax, 0, 127);
    //1. == 关闭输出
    if (outT <= outMin)  {
        gpio.digitalWrite(tempDev->pinOut, (tempDev->pinOutAct == HIGH) ? (LOW) : (HIGH));
        gpio.pinMode(tempDev->pinOut, OUTPUT);
        runFlag = false; 
        return;
    }
    //2. == 开启输出
    if (runFlag == false) {
        gpio.pinMode(tempDev->pinOut, PWM);
        runFlag = true;
    }
    //3. == com 置位
    gpio.setPwmDuty(tempDev->pinOut, boundary(outT, outMin, outMax));
}

//====================================
// ad 值转换 温度值
//====================================
void c_temp::outManage() {
    if (AutoTurningFlag == true)
        return;
    //---------------------------------
    //1. 采样温度
    sampleTemp();
    
    //---------------------------------
    //2. 温度异常
    if ((temperature < tempDev->min) || (temperature > tempDev->max)) {
        setOut(0);
        return;
    }
    //---------------------------------
    //3. pid 计算输出
    setOut(pid());

}
//=================================================================


