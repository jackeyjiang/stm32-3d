#ifndef __TYPE_DEFINE_
#define	__TYPE_DEFINE_

#define __io volatile

typedef   unsigned        char boolean;
typedef   unsigned          char uint8;
typedef   unsigned short     int uint16;
typedef   unsigned           int uint32;
typedef   unsigned       __int64 uint64;

typedef   signed          char int8;
typedef   signed short     int int16;
typedef   signed           int int32;
typedef   signed       __int64 int64;

typedef void (*voidFuncPtr)     (void);
typedef void (*voidFuncIntPtr)  (int);
extern  void voidFunc(void);
typedef void (*voidArgumentFuncPtr)(void *);

#ifndef NULL
#define NULL 0
#endif

#define ADC_NULL 0xFF

#ifndef HIGH
#define HIGH 0x1
#endif
#ifndef LOW
#define LOW  0x0
#endif

typedef enum {
    e_BYTE = 0,
    e_BIN  = 2,
    e_OCT  = 8,
    e_DEC  = 10,
    e_HEX  = 16
}te_base;

#define assert_param(expr) ((void)0)
#endif

