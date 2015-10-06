#ifndef _WIRISH_PRINT_H_
#define _WIRISH_PRINT_H_
//===============================================
#include "typeDefine.h"
class Print {
public:
    virtual void write(uint8 ch) = 0;
    virtual void write(const char *str);
    virtual void write(const void *buf, uint32 len);
		int  vprintf( const char* format, ...);
    void print(char);
    void print(const char[]);
    void print(uint8, te_base=e_DEC);
    void print(int, te_base=e_DEC);
    void print(unsigned int, te_base=e_DEC);
    void print(long, te_base=e_DEC);
    void print(unsigned long, te_base=e_DEC);
    void print(long long, te_base=e_DEC);
    void print(unsigned long long, te_base=e_DEC);
    void print(double, int=2);
    void println(void);
    void println(char);
    void println(const char[]);
    void println(uint8, te_base=e_DEC);
    void println(int, te_base=e_DEC);
    void println(unsigned int, te_base=e_DEC);
    void println(long, te_base=e_DEC);
    void println(unsigned long, te_base=e_DEC);
    void println(long long, te_base=e_DEC);
    void println(unsigned long long, te_base=e_DEC);
    void println(double, int=2);
private:
		char *itoa(int   num, char *str, int radix);
		char *ftoa(float num, char *str, uint8 integer, uint8 decimal);
    void printNumber(unsigned long long, uint8);
    void printFloat(double, uint8);
};

#endif
