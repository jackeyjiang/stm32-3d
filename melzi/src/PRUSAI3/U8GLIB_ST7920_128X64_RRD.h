//=============================================================================
//
//=============================================================================
#ifndef     __U8GLIB_ST7920_128X64_RRD__
#define     __U8GLIB_ST7920_128X64_RRD__
//set optimization so ARDUINO optimizes this file
//#pragma GCC optimize (3)
#define ST7920_CLK_PIN  LCD_PIN_CLK
#define ST7920_DAT_PIN  LCD_SPI_DATA
#define ST7920_CS_PIN   LCD_PIN_CS
//#define PAGE_HEIGHT 8         //128 byte frambuffer
//#define PAGE_HEIGHT 16        //256 byte frambuffer
#define PAGE_HEIGHT 32          //512 byte framebuffer
#define WIDTH   128
#define HEIGHT  64
#include <U8glib.h>
//=====================================================
extern uint8_t      u8g_dev_rrd_st7920_128x64_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg);
extern u8g_dev_t    u8g_dev_st7920_128x64_rrd_sw_spi;
class U8GLIB_ST7920_128X64_RRD : public U8GLIB {
    public:
    U8GLIB_ST7920_128X64_RRD(uint8_t dummy) : U8GLIB(&u8g_dev_st7920_128x64_rrd_sw_spi) {}
};
extern U8GLIB_ST7920_128X64_RRD    u8g;
//=========================================================
//extern U8GLIB_ST7920_128X64_4X u8g;
extern void lcd_loop_fxn(void);
//=============================================================================
#endif  //__U8GLIB_ST7920_128X64_RRD__

