//================================================================================
#include "m_include.h"
#include <stdarg.h>
#include <stdio.h>
//================================================================================
#ifndef LLONG_MAX
/*
 * Note:
 *
 * At time of writing (12 April 2011), the limits.h that came with the
 * newlib we distributed didn't include LLONG_MAX.  Because we're
 * staying away from using templates (see /notes/coding_standard.rst,
 * "Language Features and Compiler Extensions"), this value was
 * copy-pasted from a println() of the value
 *
 *     std::numeric_limits<long long>::max().
 */
#define LLONG_MAX 9223372036854775807LL
#endif

/*
 * Public methods
 */
//
//================================================================================
/*
 * Conver int to string based on radix (usually 2, 8, 10, and 16)
*/
//================================================================================
char * Print::itoa(int num, char *str, int radix) {
    static char string[] = "0123456789abcdefghijklmnopqrstuvwxyz";
 
    char* ptr = str;
	  char  sig;
    int i;
    int j;
 
		if (num<0) {
			sig  = '-';
			num *= -1;
		}
	
    while (num) {
        *ptr++ = string[num % radix];
        num /= radix;
         if (num < radix)  {
            *ptr++ = string[num];
						if (sig == '-')
							*ptr++ = sig;
            *ptr = '\0';
            break;
        }
    }
 
    j = ptr - str - 1;
    for (i = 0; i < (ptr - str) / 2; i++) {
        int temp = str[i];
        str[i] = str[j];
        str[j--] = temp;
    }
 
    return str;
}
//
//================================================================================
/*
 * Conver float to string 
*/
//================================================================================
char *Print::ftoa(float num, char *str, uint8 integer, uint8 decimal) {
		// 默认 5.2
		long base = 1, xx;
		if (integer == 0) integer = 5;
		if (decimal == 0) decimal = 2;
		// decimal
		for (int i=0; i<decimal; i++) {
				num *= 10;
		}
		xx = num;
		// sig
		if (num < 0) {
				*str++ = '-';
				xx    *= -1;
		}
		//integer
		int byte = integer + decimal;
		for (int i=1; i<byte; i++) {
				base *= 10;
		}
		//
		for (int i=0; i<byte; i++) {
				if (i==integer) 
					*str++ = '.';
				*str++ = (xx/base) % 10 + '0';
				(base > 10) ? (base /= 10) : (base = 1);
		}
		*str = 0;
		return 0;
}
//================================================================================
/*
 * A simple printf function. Only support the following format:
 * Code Format
 * %c character
 * %d signed integers
 * %i signed integers
 * %s a string of characters
 * %o octal
 * %x unsigned hexadecimal
 */
int Print::vprintf( const char* format, ...) {
    va_list arg;
    int done = 0;
		uint8  decimal     = 0; 		// 小数位数
		uint8  integer     = 0;			// 整数位数
		bool   decimalFlag = false;	// 小数位置位
	  bool	 setType     = false;	// 整数位置位
 
    va_start (arg, format);
    //done = vfprintf (stdout, format, arg);
 
    while( *format != '\0') {
        if(*format == '%' || setType == true) {
						char store[20];
						char* str = store;
						format++;
						if (*format == '%') {
								write('%');		
						} else if (*format == 'c') {
								char c = (char)va_arg(arg, int);
								write(c);
						} else if (*format == 'd' || *format == 'i') {
								int i = va_arg(arg, int);
								itoa(i, store, 10);
								write(str);
						} else if (*format == 'o') {
								int i = va_arg(arg, int);
								itoa(i, store, 8);
								write(str);
						} else if (*format == 'x') {
								int i = va_arg(arg, int);
								itoa(i, store, 16);
								write(str);
						} else if (*format == 's') {
								char* str = va_arg(arg, char*);
								write(str);
						} else if (*format == 'f') {
								double i = va_arg(arg, double);
								ftoa(i, store, integer, decimal);
								write(str);
								setType = decimalFlag = integer = decimal = 0;
		// 显示数据位数设定
            } else if (*format >= '0' && *format <= '9') {
								if (decimalFlag == true) {
									decimal = decimal * 10 + *format-'0';
								} else {
									integer = integer * 10 + *format-'0';
								}
								setType     = true;
								continue;
						} else if (*format == '.'){
								setType     = true;
								decimalFlag = true;
								continue;
						} else {
								setType = decimalFlag = integer = decimal = 0;
								continue;
						}
            // Skip this one characters.
            format += 1;
        } else {
						write(*format++);
        }
    }
		va_end (arg);
		return done;
} 
//================================================================================


void Print::write(const char *str) {
    while (*str) {
        write(*str++);
    }
}

void Print::write(const void *buffer, uint32 size) {
    uint8 *ch = (uint8*)buffer;
    while (size--) {
        write(*ch++);
    }
}

void Print::print(uint8 b, te_base base) {
    print((uint64)b, base);
}

void Print::print(char c) {
    write(c);
}

void Print::print(const char str[]) {
    write(str);
}

void Print::print(int n, te_base base) {
    print((long long)n, base);
}

void Print::print(unsigned int n, te_base base) {
    print((unsigned long long)n, base);
}

void Print::print(long n, te_base base) {
    print((long long)n, base);
}

void Print::print(unsigned long n, te_base base) {
    print((unsigned long long)n, base);
}

void Print::print(long long n, te_base base) {
    if (base == e_BYTE) {
        write((uint8)n);
        return;
    }
    if (n < 0) {
        print('-');
        n = -n;
    }
    printNumber(n, base);
}

void Print::print(unsigned long long n, te_base base) {
    if (base == e_BYTE) {
        write((uint8)n);
    } else {
        printNumber(n, base);
    }
}

void Print::print(double n, int digits) {
    printFloat(n, digits);
}

void Print::println(void) {
    print('\r');
    print('\n');
}

void Print::println(char c) {
    print(c);
    println();
}

void Print::println(const char c[]) {
    print(c);
    println();
}

void Print::println(uint8 b, te_base base) {
    print(b, base);
    println();
}

void Print::println(int n, te_base base) {
    print(n, base);
    println();
}

void Print::println(unsigned int n, te_base base) {
    print(n, base);
    println();
}

void Print::println(long n, te_base base) {
    print((long long)n, base);
    println();
}

void Print::println(unsigned long n, te_base base) {
    print((unsigned long long)n, base);
    println();
}

void Print::println(long long n, te_base base) {
    print(n, base);
    println();
}

void Print::println(unsigned long long n, te_base base) {
    print(n, base);
    println();
}

void Print::println(double n, int digits) {
    print(n, digits);
    println();
}

/*
 * Private methods
 */

void Print::printNumber(unsigned long long n, uint8 base) {
    unsigned char buf[CHAR_BIT * sizeof(long long)+1];
    unsigned long i = 0;

    if (n == 0) {
        print('0');
        return;
    }

    while (n > 0) {
        buf[i++] = n % base;
        n /= base; 
    }

    for (; i > 0; i--) {
        print((char)(buf[i - 1] < 10 ?
                     '0' + buf[i - 1] :
                     'A' + buf[i - 1] - 10));
    }
}

/* According to snprintf(),
 *
 * nextafter((double)numeric_limits<long long>::max(), 0.0) ~= 9.22337e+18
 *
 * This slightly smaller value was picked semi-arbitrarily. */
#define LARGE_DOUBLE_TRESHOLD (9.1e18)

/* THIS FUNCTION SHOULDN'T BE USED IF YOU NEED ACCURATE RESULTS.
 *
 * This implementation is meant to be simple and not occupy too much
 * code size.  However, printing floating point values accurately is a
 * subtle task, best left to a well-tested library function.
 *
 * See Steele and White 2003 for more details:
 *
 * http://kurtstephens.com/files/p372-steele.pdf
 */
void Print::printFloat(double number, uint8 digits) {
    // Hackish fail-fast behavior for large-magnitude doubles
    if (abs(number) >= LARGE_DOUBLE_TRESHOLD) {
        if (number < 0.0) {
            print('-');
        }
        print("<large double>");
        return;
    }

    // Handle negative numbers
    if (number < 0.0) {
        print('-');
        number = -number;
    }

    // Simplistic rounding strategy so that e.g. print(1.999, 2)
    // prints as "2.00"
    double rounding = 0.5;
    for (uint8 i = 0; i < digits; i++) {
        rounding /= 10.0;
    }
    number += rounding;

    // Extract the integer part of the number and print it
    long long int_part = (long long)number;
    double remainder = number - int_part;
    print(int_part);

    // Print the decimal point, but only if there are digits beyond
    if (digits > 0) {
        print(".");
    }

    // Extract digits from the remainder one at a time
    while (digits-- > 0) {
        remainder *= 10.0;
        int to_print = (int)remainder;
        print(to_print);
        remainder -= to_print;
    }
}
