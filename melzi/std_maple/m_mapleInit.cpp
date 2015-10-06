//===============================================
#include "m_include.h"
#include "m_mapleInit.h"
//===============================================


__attribute__((constructor)) void premain() {
    init();
}

void init(void) {
    //== 定时器初始化 =======
    Timer.init(&timer1);
    Timer.init(&timer2);
    Timer.init(&timer3);
    Timer.init(&timer4);
    Timer.init(&timer8);
    adc.init(&adc1);
}


