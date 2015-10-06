#include "project.h"
U32 mainLoopStk[100];


__task void mainLoopTsk(void) {
while (1)
{
    m_gpio.digitalWrite(0,LOW);
    serial1.print("hello world\r\n");
    m_gpio.digitalWrite(0,HIGH);
    while (serial1.available()) 
        serial2.print(serial1.read());
}
}

__task void initTsk(void) {
    serial1.begin(9600);
    serial2.begin(9600);
    os_tsk_create_user(mainLoopTsk,0,mainLoopStk,sizeof(mainLoopStk));
    os_tsk_delete_self();
}

int main()
{
    os_sys_init(initTsk);
    while (1) {
        serial1.print("hello world");
    }
}