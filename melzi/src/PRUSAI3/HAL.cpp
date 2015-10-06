#include "Repetier.h"
#include "libraries\Wire\utility\twi.h"
#include <avr/interrupt.h>

//extern "C" void __cxa_pure_virtual() { }

HAL::HAL()
{
    //ctor
}

HAL::~HAL()
{
    //dtor
}

uint16_t HAL::integerSqrt(long a)
{

    return 0;
}



const uint16_t fast_div_lut[17] PROGMEM = {0,
                                          };

const uint16_t slow_div_lut[257] PROGMEM = {0,0,0,0,0,0,0,0,
                                           };
/** \brief approximates division of F_CPU/divisor

In the stepper interrupt a division is needed, which is a slow operation.
The result is used for timer calculation where small errors are ok. This
function uses lookup tables to find a fast approximation of the result.

*/
long HAL::CPUDivU2(unsigned int divisor)
{
    return 0;
// #if CPU_ARCH==ARCH_AVR
//     long res;
//     unsigned short table;
//     if(divisor<8192)
//     {
//         if(divisor<512)
//         {
//             if(divisor<10) divisor = 10;
//             return Div4U2U(F_CPU,divisor); // These entries have overflows in lookuptable!
//         }
//         table = (unsigned short)&slow_div_lut[0];
//         __asm__ __volatile__( // needs 64 ticks neu 49 Ticks
//             "mov r18,%A1 \n\t"
//             "andi r18,31 \n\t"  // divisor & 31 in r18
//             "lsr %B1 \n\t" // divisor >> 4
//             "ror %A1 \n\t"
//             "lsr %B1 \n\t"
//             "ror %A1 \n\t"
//             "lsr %B1 \n\t"
//             "ror %A1 \n\t"
//             "lsr %B1 \n\t"
//             "ror %A1 \n\t"
//             "andi %A1,254 \n\t"
//             "add %A2,%A1 \n\t" // table+divisor>>3
//             "adc %B2,%B1 \n\t"
//             "lpm %A0,Z+ \n\t" // y0 in res
//             "lpm %B0,Z+ \n\t"  // %C0,%D0 are 0
//             "movw r4,%A0 \n\t" // y0 nach gain (r4-r5)
//             "lpm r0,Z+ \n\t" // gain = gain-y1
//             "sub r4,r0 \n\t"
//             "lpm r0,Z+ \n\t"
//             "sbc r5,r0 \n\t"
//             "mul r18,r4 \n\t" // gain*(divisor & 31)
//             "movw %A1,r0 \n\t" // divisor not needed any more, use for byte 0,1 of result
//             "mul r18,r5 \n\t"
//             "add %B1,r0 \n\t"
//             "mov %A2,r1 \n\t"
//             "lsl %A1 \n\t"
//             "rol %B1 \n\t"
//             "rol %A2 \n\t"
//             "lsl %A1 \n\t"
//             "rol %B1 \n\t"
//             "rol %A2 \n\t"
//             "lsl %A1 \n\t"
//             "rol %B1 \n\t"
//             "rol %A2 \n\t"
//             "sub %A0,%B1 \n\t"
//             "sbc %B0,%A2 \n\t"
//             "clr %C0 \n\t"
//             "clr %D0 \n\t"
//             "clr r1 \n\t"
//             : "=&r" (res),"=&d"(divisor),"=&z"(table) : "1"(divisor),"2"(table) : "r18","r4","r5");
//         return 0;
//         /*unsigned short adr0 = (unsigned short)&slow_div_lut+(divisor>>4)&1022;
//         long y0=	pgm_read_dword_near(adr0);
//         long gain = y0-pgm_read_dword_near(adr0+2);
//         return y0-((gain*(divisor & 31))>>5);*/
//     }
//     else
//     {
//         table = (unsigned short)&fast_div_lut[0];
//         __asm__ __volatile__( // needs 49 ticks
//             "movw r18,%A1 \n\t"
//             "andi r19,15 \n\t"  // divisor & 4095 in r18,r19
//             "lsr %B1 \n\t" // divisor >> 3, then %B1 is 2*(divisor >> 12)
//             "lsr %B1 \n\t"
//             "lsr %B1 \n\t"
//             "andi %B1,254 \n\t"
//             "add %A2,%B1 \n\t" // table+divisor>>11
//             "adc %B2,r1 \n\t" //
//             "lpm %A0,Z+ \n\t" // y0 in res
//             "lpm %B0,Z+ \n\t"
//             "movw r4,%A0 \n\t" // y0 to gain (r4-r5)
//             "lpm r0,Z+ \n\t" // gain = gain-y1
//             "sub r4,r0 \n\t"
//             "lpm r0,Z+ \n\t"
//             "sbc r5,r0 \n\t" // finished - result has max. 16 bit
//             "mul r18,r4 \n\t" // gain*(divisor & 4095)
//             "movw %A1,r0 \n\t" // divisor not needed any more, use for byte 0,1 of result
//             "mul r19,r5 \n\t"
//             "mov %A2,r0 \n\t" // %A2 = byte 3 of result
//             "mul r18,r5 \n\t"
//             "add %B1,r0 \n\t"
//             "adc %A2,r1 \n\t"
//             "mul r19,r4 \n\t"
//             "add %B1,r0 \n\t"
//             "adc %A2,r1 \n\t"
//             "andi %B1,240 \n\t" // >> 12
//             "swap %B1 \n\t"
//             "swap %A2 \r\n"
//             "mov %A1,%A2 \r\n"
//             "andi %A1,240 \r\n"
//             "or %B1,%A1 \r\n"
//             "andi %A2,15 \r\n"
//             "sub %A0,%B1 \n\t"
//             "sbc %B0,%A2 \n\t"
//             "clr %C0 \n\t"
//             "clr %D0 \n\t"
//             "clr r1 \n\t"
//             : "=&r" (res),"=&d"(divisor),"=&z"(table) : "1"(divisor),"2"(table) : "r18","r19","r4","r5");
//         return res;
//         /*
//         // The asm mimics the following code
//         unsigned short adr0 = (unsigned short)&fast_div_lut+(divisor>>11)&254;
//         unsigned short y0=	pgm_read_word_near(adr0);
//         unsigned short gain = y0-pgm_read_word_near(adr0+2);
//         return y0-(((long)gain*(divisor & 4095))>>12);*/
//     }
// #else
//     return F_CPU/divisor;
// #endif
}

void HAL::setupTimer()
{

//     PWM_TCCR = 0;  // Setup PWM interrupt
//     PWM_OCR = 64;
//     PWM_TIMSK |= (1<<PWM_OCIE);

//     TCCR1A = 0;  // Steup timer 1 interrupt to no prescale CTC mode
//     TCCR1C = 0;
//     TIMSK1 = 0;
//     TCCR1B =  (_BV(WGM12) | _BV(CS10)); // no prescaler == 0.0625 usec tick | 001 = clk/1
//     OCR1A=65500; //start off with a slow frequency.
//     TIMSK1 |= (1<<OCIE1A); // Enable interrupt
// #if FEATURE_SERVO
// #if SERVO0_PIN>-1
//     SET_OUTPUT(SERVO0_PIN);
//     digitalWrite(SERVO0_PIN,LOW);
// #endif
// #if SERVO1_PIN>-1
//     SET_OUTPUT(SERVO1_PIN);
//     digitalWrite(SERVO1_PIN,LOW);
// #endif
// #if SERVO2_PIN>-1
//     SET_OUTPUT(SERVO2_PIN);
//     digitalWrite(SERVO2_PIN,LOW);
// #endif
// #if SERVO3_PIN>-1
//     SET_OUTPUT(SERVO3_PIN);
//     digitalWrite(SERVO3_PIN,LOW);
// #endif
//     TCCR3A = 0;             // normal counting mode
//     TCCR3B = _BV(CS31);     // set prescaler of 8
//     TCNT3 = 0;              // clear the timer count
// #if defined(__AVR_ATmega128__)
//     TIFR |= _BV(OCF3A);     // clear any pending interrupts;
//     ETIMSK |= _BV(OCIE3A);  // enable the output compare interrupt
// #else
//     TIFR3 = _BV(OCF3A);     // clear any pending interrupts;
//     TIMSK3 =  _BV(OCIE3A) ; // enable the output compare interrupt
// #endif
// #endif
}

void HAL::showStartReason()
{
//     // Check startup - does nothing if bootloader sets MCUSR to 0
//     uint8_t mcu = MCUSR;
//     if(mcu & 1) Com::printInfoFLN(Com::tPowerUp);
//     if(mcu & 2) Com::printInfoFLN(Com::tExternalReset);
//     if(mcu & 4) Com::printInfoFLN(Com::tBrownOut);
//     if(mcu & 8) Com::printInfoFLN(Com::tWatchdog);
//     if(mcu & 32) Com::printInfoFLN(Com::tSoftwareReset);
//     MCUSR=0;
}
int HAL::getFreeRam()
{
//     int freeram = 0;
//     BEGIN_INTERRUPT_PROTECTED
//     uint8_t * heapptr, * stackptr;
//     heapptr = (uint8_t *)malloc(4);          // get heap pointer
//     free(heapptr);      // free up the memory again (sets heapptr to 0)
//     stackptr =  (uint8_t *)(SP);           // save value of stack pointer
//     freeram = (int)stackptr-(int)heapptr;
//     END_INTERRUPT_PROTECTED
//     return freeram;
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void HAL::resetHardware()
{
//     resetFunc();
}

void HAL::analogStart()
{
// #if ANALOG_INPUTS>0
//     ADMUX = ANALOG_REF; // refernce voltage
//     for(uint8_t i=0; i<ANALOG_INPUTS; i++)
//     {
//         osAnalogInputCounter[i] = 0;
//         osAnalogInputBuildup[i] = 0;
//         osAnalogInputValues[i] = 0;
//     }
//     ADCSRA = _BV(ADEN)|_BV(ADSC)|ANALOG_PRESCALER;
//     //ADCSRA |= _BV(ADSC);                  // start ADC-conversion
//     while (ADCSRA & _BV(ADSC) ) {} // wait for conversion
//     /* ADCW must be read once, otherwise the next result is wrong. */
//     uint dummyADCResult;
//     dummyADCResult = ADCW;
//     // Enable interrupt driven conversion loop
//     uint8_t channel = pgm_read_byte(&osAnalogInputChannels[osAnalogInputPos]);
// #if defined(ADCSRB) && defined(MUX5)
//     if(channel & 8)  // Reading channel 0-7 or 8-15?
//         ADCSRB |= _BV(MUX5);
//     else
//         ADCSRB &= ~_BV(MUX5);
// #endif
//     ADMUX = (ADMUX & ~(0x1F)) | (channel & 7);
//     ADCSRA |= _BV(ADSC); // start conversion without interrupt!
// #endif
}

/*************************************************************************
* Title:    I2C master library using hardware TWI interface
* Author:   Peter Fleury <pfleury@gmx.ch>  http://jump.to/fleury
* File:     $Id: twimaster.c,v 1.3 2005/07/02 11:14:21 Peter Exp $
* Software: AVR-GCC 3.4.3 / avr-libc 1.2.3
* Target:   any AVR device with hardware TWI
* Usage:    API compatible with I2C Software Library i2cmaster.h
**************************************************************************/


#include <avr/io.h>

/*************************************************************************
 Initialization of the I2C bus interface. Need to be called only once
*************************************************************************/
void HAL::i2cInit(unsigned long clockSpeedHz)
{
//     /* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
//     TWSR = 0;                         /* no prescaler */
//     TWBR = ((F_CPU/clockSpeedHz)-16)/2;  /* must be > 10 for stable operation */
}


/*************************************************************************
  Issues a start condition and sends address and transfer direction.
  return 0 = device accessible, 1= failed to access device
*************************************************************************/
unsigned char HAL::i2cStart(unsigned char address)
{
//     uint8_t   twst;

//     // send START condition
//     TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

//     // wait until transmission completed
//     while(!(TWCR & (1<<TWINT)));

//     // check value of TWI Status Register. Mask prescaler bits.
//     twst = TW_STATUS & 0xF8;
//     if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;

//     // send device address
//     TWDR = address;
//     TWCR = (1<<TWINT) | (1<<TWEN);

//     // wail until transmission completed and ACK/NACK has been received
//     while(!(TWCR & (1<<TWINT)));

//     // check value of TWI Status Register. Mask prescaler bits.
//     twst = TW_STATUS & 0xF8;
//     if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

    return 0;

}


/*************************************************************************
 Issues a start condition and sends address and transfer direction.
 If device is busy, use ack polling to wait until device is ready

 Input:   address and transfer direction of I2C device
*************************************************************************/
void HAL::i2cStartWait(unsigned char address)
{
//     uint8_t   twst;
//     while ( 1 )
//     {
//         // send START condition
//         TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

//         // wait until transmission completed
//         while(!(TWCR & (1<<TWINT)));

//         // check value of TWI Status Register. Mask prescaler bits.
//         twst = TW_STATUS & 0xF8;
//         if ( (twst != TW_START) && (twst != TW_REP_START)) continue;

//         // send device address
//         TWDR = address;
//         TWCR = (1<<TWINT) | (1<<TWEN);

//         // wail until transmission completed
//         while(!(TWCR & (1<<TWINT)));

//         // check value of TWI Status Register. Mask prescaler bits.
//         twst = TW_STATUS & 0xF8;
//         if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) )
//         {
//             /* device busy, send stop condition to terminate write operation */
//             TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

//             // wait until stop condition is executed and bus released
//             while(TWCR & (1<<TWSTO));

//             continue;
//         }
//         //if( twst != TW_MT_SLA_ACK) return 1;
//         break;
//     }

}


/*************************************************************************
 Terminates the data transfer and releases the I2C bus
*************************************************************************/
void HAL::i2cStop(void)
{
//     /* send stop condition */
//     TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
//     // wait until stop condition is executed and bus released
//     while(TWCR & (1<<TWSTO));
}


/*************************************************************************
  Send one byte to I2C device

  Input:    byte to be transfered
  Return:   0 write successful
            1 write failed
*************************************************************************/
unsigned char HAL::i2cWrite( unsigned char data )
{
//     uint8_t   twst;
//     // send data to the previously addressed device
//     TWDR = data;
//     TWCR = (1<<TWINT) | (1<<TWEN);
//     // wait until transmission completed
//     while(!(TWCR & (1<<TWINT)));
//     // check value of TWI Status Register. Mask prescaler bits
//     twst = TW_STATUS & 0xF8;
//     if( twst != TW_MT_DATA_ACK) return 1;
//     return 0;
}


/*************************************************************************
 Read one byte from the I2C device, request more data from device
 Return:  byte read from I2C device
*************************************************************************/
unsigned char HAL::i2cReadAck(void)
{
//     TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
//     while(!(TWCR & (1<<TWINT)));
//     return TWDR;
}

/*************************************************************************
 Read one byte from the I2C device, read is followed by a stop condition

 Return:  byte read from I2C device
*************************************************************************/
unsigned char HAL::i2cReadNak(void)
{
//     TWCR = (1<<TWINT) | (1<<TWEN);
//     while(!(TWCR & (1<<TWINT)));
//     return TWDR;
}

#if FEATURE_SERVO
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__) || defined(__AVR_ATmega128__) ||defined(__AVR_ATmega1281__)||defined(__AVR_ATmega2561__)
#define SERVO2500US F_CPU/3200
#define SERVO5000US F_CPU/1600
unsigned int HAL::servoTimings[4] = {0,0,0,0};
static uint8_t servoIndex = 0;
void HAL::servoMicroseconds(uint8_t servo,int ms)
{
//     if(ms<500) ms = 0;
//     if(ms>2500) ms = 2500;
//     servoTimings[servo] = (unsigned int)(((F_CPU/1000000)*(long)ms)>>3);
}
SIGNAL (TIMER3_COMPA_vect)
{
    switch(servoIndex)
    {
    case 0:
        TCNT3 = 0;
        if(HAL::servoTimings[0])
        {
#if SERVO0_PIN>-1
            digitalWrite(SERVO0_PIN,HIGH);
#endif
            OCR3A = HAL::servoTimings[0];
        }
        else OCR3A = SERVO2500US;
        break;
    case 1:
#if SERVO0_PIN>-1
        digitalWrite(SERVO0_PIN,LOW);
#endif
        OCR3A = SERVO5000US;
        break;
    case 2:
        TCNT3 = 0;
        if(HAL::servoTimings[1])
        {
#if SERVO1_PIN>-1
            digitalWrite(SERVO1_PIN,HIGH);
#endif
            OCR3A = HAL::servoTimings[1];
        }
        else OCR3A = SERVO2500US;
        break;
    case 3:
#if SERVO1_PIN>-1
        digitalWrite(SERVO1_PIN,LOW);
#endif
        OCR3A = SERVO5000US;
        break;
    case 4:
        TCNT3 = 0;
        if(HAL::servoTimings[2])
        {
#if SERVO2_PIN>-1
            digitalWrite(SERVO2_PIN,HIGH);
#endif
            OCR3A = HAL::servoTimings[2];
        }
        else OCR3A = SERVO2500US;
        break;
    case 5:
#if SERVO2_PIN>-1
        digitalWrite(SERVO2_PIN,LOW);
#endif
        OCR3A = SERVO5000US;
        break;
    case 6:
        TCNT3 = 0;
        if(HAL::servoTimings[3])
        {
#if SERVO3_PIN>-1
            digitalWrite(SERVO3_PIN,HIGH);
#endif
            OCR3A = HAL::servoTimings[3];
        }
        else OCR3A = SERVO2500US;
        break;
    case 7:
#if SERVO3_PIN>-1
        digitalWrite(SERVO3_PIN,LOW);
#endif
        OCR3A = SERVO5000US;
        break;
    }
    servoIndex++;
    if(servoIndex>7)
        servoIndex = 0;
}
#else
#error No servo support for your board, please diable FEATURE_SERVO
#endif
#endif

#define HEATER_PWM_SPEED 2 // How fast ist pwm signal 0 = 15.25Hz, 1 = 30.51Hz, 2 = 61.03Hz, 3 = 122.06Hz

#if !defined(HEATER_PWM_SPEED)
#define HEATER_PWM_SPEED 0
#endif
#if HEATER_PWM_SPEED<0
#define HEATER_PWM_SPEED 0
#endif
#if HEATER_PWM_SPEED>3
#define HEATER_PWM_SPEED 3
#endif

#if HEATER_PWM_SPEED == 0
#define HEATER_PWM_STEP 1
#define HEATER_PWM_MASK 255
#elif HEATER_PWM_SPEED == 1
#define HEATER_PWM_STEP 2
#define HEATER_PWM_MASK 254
#elif HEATER_PWM_SPEED == 2
#define HEATER_PWM_STEP 4
#define HEATER_PWM_MASK 252
#else
#define HEATER_PWM_STEP 4
#define HEATER_PWM_MASK 252
#endif

/**
This timer is called 3906 timer per second. It is used to update pwm values for heater and some other frequent jobs.
*/
ISR(PWM_TIMER_VECTOR)
{
//     static uint8_t pwm_count = 0;
//     static uint8_t pwm_count_heater = 0;
//     static uint8_t pwm_pos_set[NUM_EXTRUDER+3];
//     static uint8_t pwm_cooler_pos_set[NUM_EXTRUDER];
//     PWM_OCR += 64;
//     if(pwm_count_heater == 0)
//     {
// #if EXT0_HEATER_PIN>-1
//         if((pwm_pos_set[0] = (pwm_pos[0] & HEATER_PWM_MASK))>0) digitalWrite(EXT0_HEATER_PIN,1);
// #endif

// #if HEATED_BED_HEATER_PIN>-1 && HAVE_HEATED_BED
//         if((pwm_pos_set[NUM_EXTRUDER] = pwm_pos[NUM_EXTRUDER])>0) digitalWrite(HEATED_BED_HEATER_PIN,1);
// #endif
//     }
//     if(pwm_count==0)
//     {
// #if EXT0_HEATER_PIN>-1 && EXT0_EXTRUDER_COOLER_PIN>-1
//         if((pwm_cooler_pos_set[0] = extruder[0].coolerPWM)>0) digitalWrite(EXT0_EXTRUDER_COOLER_PIN,1);
// #endif
// #if defined(EXT1_HEATER_PIN) && EXT1_HEATER_PIN>-1 && NUM_EXTRUDER>1
// #if EXT1_EXTRUDER_COOLER_PIN>-1 && EXT1_EXTRUDER_COOLER_PIN!=EXT0_EXTRUDER_COOLER_PIN
//         if((pwm_cooler_pos_set[1] = extruder[1].coolerPWM)>0) digitalWrite(EXT1_EXTRUDER_COOLER_PIN,1);
// #endif
// #endif
// #if defined(EXT2_HEATER_PIN) && EXT2_HEATER_PIN>-1 && NUM_EXTRUDER>2
// #if EXT2_EXTRUDER_COOLER_PIN>-1
//         if((pwm_cooler_pos_set[2] = extruder[2].coolerPWM)>0) digitalWrite(EXT2_EXTRUDER_COOLER_PIN,1);
// #endif
// #endif
// #if defined(EXT3_HEATER_PIN) && EXT3_HEATER_PIN>-1 && NUM_EXTRUDER>3
// #if EXT3_EXTRUDER_COOLER_PIN>-1
//         if((pwm_cooler_pos_set[3] = extruder[3].coolerPWM)>0) digitalWrite(EXT3_EXTRUDER_COOLER_PIN,1);
// #endif
// #endif
// #if defined(EXT4_HEATER_PIN) && EXT4_HEATER_PIN>-1 && NUM_EXTRUDER>4
// #if EXT4_EXTRUDER_COOLER_PIN>-1
//         if((pwm_cooler_pos_set[4] = pwm_pos[4].coolerPWM)>0) digitalWrite(EXT4_EXTRUDER_COOLER_PIN,1);
// #endif
// #endif
// #if defined(EXT5_HEATER_PIN) && EXT5_HEATER_PIN>-1 && NUM_EXTRUDER>5
// #if EXT5_EXTRUDER_COOLER_PIN>-1
//         if((pwm_cooler_pos_set[5] = extruder[5].coolerPWM)>0) digitalWrite(EXT5_EXTRUDER_COOLER_PIN,1);
// #endif
// #endif
// #if FAN_BOARD_PIN>-1
//         if((pwm_pos_set[NUM_EXTRUDER+1] = pwm_pos[NUM_EXTRUDER+1])>0) digitalWrite(FAN_BOARD_PIN,1);
// #endif
// #if FAN_PIN>-1 && FEATURE_FAN_CONTROL
//         if((pwm_pos_set[NUM_EXTRUDER+2] = pwm_pos[NUM_EXTRUDER+2])>0) digitalWrite(FAN_PIN,1);
// #endif
//     }
// #if EXT0_HEATER_PIN>-1
//     if(pwm_pos_set[0] == pwm_count_heater && pwm_pos_set[0]!=HEATER_PWM_MASK) digitalWrite(EXT0_HEATER_PIN,0);
// #if EXT0_EXTRUDER_COOLER_PIN>-1
//     if(pwm_cooler_pos_set[0] == pwm_count && pwm_cooler_pos_set[0]!=255) digitalWrite(EXT0_EXTRUDER_COOLER_PIN,0);
// #endif
// #endif
// #if defined(EXT1_HEATER_PIN) && EXT1_HEATER_PIN>-1 && NUM_EXTRUDER>1
//     if(pwm_pos_set[1] == pwm_count_heater && pwm_pos_set[1]!=HEATER_PWM_MASK) digitalWrite(EXT1_HEATER_PIN,0);
// #if EXT1_EXTRUDER_COOLER_PIN>-1 && EXT1_EXTRUDER_COOLER_PIN!=EXT0_EXTRUDER_COOLER_PIN
//     if(pwm_cooler_pos_set[1] == pwm_count && pwm_cooler_pos_set[1]!=255) digitalWrite(EXT1_EXTRUDER_COOLER_PIN,0);
// #endif
// #endif
// #if defined(EXT2_HEATER_PIN) && EXT2_HEATER_PIN>-1 && NUM_EXTRUDER>2
//     if(pwm_pos_set[2] == pwm_count_heater && pwm_pos_set[2]!=HEATER_PWM_MASK) digitalWrite(EXT2_HEATER_PIN,0);
// #if EXT2_EXTRUDER_COOLER_PIN>-1
//     if(pwm_cooler_pos_set[2] == pwm_count && pwm_cooler_pos_set[2]!=255) digitalWrite(EXT2_EXTRUDER_COOLER_PIN,0);
// #endif
// #endif
// #if defined(EXT3_HEATER_PIN) && EXT3_HEATER_PIN>-1 && NUM_EXTRUDER>3
//     if(pwm_pos_set[3] == pwm_count_heater && pwm_pos_set[3]!=HEATER_PWM_MASK) digitalWrite(EXT3_HEATER_PIN,0);
// #if EXT3_EXTRUDER_COOLER_PIN>-1
//     if(pwm_cooler_pos_set[3] == pwm_count && pwm_cooler_pos_set[3]!=255) digitalWrite(EXT3_EXTRUDER_COOLER_PIN,0);
// #endif
// #endif
// #if defined(EXT4_HEATER_PIN) && EXT4_HEATER_PIN>-1 && NUM_EXTRUDER>4
//     if(pwm_pos_set[4] == pwm_count_heater && pwm_pos_set[4]!=HEATER_PWM_MASK) digitalWrite(EXT4_HEATER_PIN,0);
// #if EXT4_EXTRUDER_COOLER_PIN>-1
//     if(pwm_cooler_pos_set[4] == pwm_count && pwm_cooler_pos_set[4]!=255) digitalWrite(EXT4_EXTRUDER_COOLER_PIN,0);
// #endif
// #endif
// #if defined(EXT5_HEATER_PIN) && EXT5_HEATER_PIN>-1 && NUM_EXTRUDER>5
//     if(pwm_pos_set[5] == pwm_count_heater && pwm_pos_set[5]!=HEATER_PWM_MASK) digitalWrite(EXT5_HEATER_PIN,0);
// #if EXT5_EXTRUDER_COOLER_PIN>-1
//     if(pwm_cooler_pos_set[5] == pwm_count && pwm_cooler_pos_set[5]!=255) digitalWrite(EXT5_EXTRUDER_COOLER_PIN,0);
// #endif
// #endif
// #if FAN_BOARD_PIN>-1
//     if(pwm_pos_set[NUM_EXTRUDER+1] == pwm_count && pwm_pos_set[NUM_EXTRUDER+1]!=255) digitalWrite(FAN_BOARD_PIN,0);
// #endif
// #if FAN_PIN>-1 && FEATURE_FAN_CONTROL
//     if(pwm_pos_set[NUM_EXTRUDER+2] == pwm_count && pwm_pos_set[NUM_EXTRUDER+2]!=255) digitalWrite(FAN_PIN,0);
// #endif
// #if HEATED_BED_HEATER_PIN>-1 && HAVE_HEATED_BED
//     if(pwm_pos_set[NUM_EXTRUDER] == pwm_count_heater && pwm_pos_set[NUM_EXTRUDER]!=HEATER_PWM_MASK) digitalWrite(HEATED_BED_HEATER_PIN,0);
// #endif
//     HAL::allowInterrupts();
//     counterPeriodical++; // Appxoimate a 100ms timer
//     if(counterPeriodical>=(int)(F_CPU/40960))
//     {
//         counterPeriodical=0;
//         executePeriodical=1;
//     }
// // read analog values
// #if ANALOG_INPUTS>0
//     if((ADCSRA & _BV(ADSC))==0)   // Conversion finished?
//     {
//         osAnalogInputBuildup[osAnalogInputPos] += ADCW;
//         if(++osAnalogInputCounter[osAnalogInputPos]>=_BV(ANALOG_INPUT_SAMPLE))
//         {
// #if ANALOG_INPUT_BITS+ANALOG_INPUT_SAMPLE<12
//             osAnalogInputValues[osAnalogInputPos] =
//                 osAnalogInputBuildup[osAnalogInputPos] <<
//                 (12-ANALOG_INPUT_BITS-ANALOG_INPUT_SAMPLE);
// #endif
// #if ANALOG_INPUT_BITS+ANALOG_INPUT_SAMPLE>12
//             osAnalogInputValues[osAnalogInputPos] =
//                 osAnalogInputBuildup[osAnalogInputPos] >>
//                 (ANALOG_INPUT_BITS+ANALOG_INPUT_SAMPLE-12);
// #endif
// #if ANALOG_INPUT_BITS+ANALOG_INPUT_SAMPLE==12
//             osAnalogInputValues[osAnalogInputPos] =
//                 osAnalogInputBuildup[osAnalogInputPos];
// #endif
//             osAnalogInputBuildup[osAnalogInputPos] = 0;
//             osAnalogInputCounter[osAnalogInputPos] = 0;
//             // Start next conversion
//             if(++osAnalogInputPos>=ANALOG_INPUTS) osAnalogInputPos = 0;
//             uint8_t channel = pgm_read_byte(&osAnalogInputChannels[osAnalogInputPos]);
// #if defined(ADCSRB) && defined(MUX5)
//             if(channel & 8)  // Reading channel 0-7 or 8-15?
//                 ADCSRB |= _BV(MUX5);
//             else
//                 ADCSRB &= ~_BV(MUX5);
// #endif
//             ADMUX = (ADMUX & ~(0x1F)) | (channel & 7);
//         }
//         ADCSRA |= _BV(ADSC);  // start next conversion
//     }
// #endif

//     UI_FAST; // Short timed user interface action
//     pwm_count++;
//     pwm_count_heater += HEATER_PWM_STEP;
}

#ifndef EXTERNALSERIAL
// Implement serial communication for one stream only!
/*
  HardwareSerial.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 28 September 2010 by Mark Sproul

  Modified to use only 1 queue with fixed length by Repetier
*/

ring_buffer rx_buffer = { { 0 }, 0, 0};
ring_buffer_tx tx_buffer = { { 0 }, 0, 0};

inline void rf_store_char(unsigned char c, ring_buffer *buffer)
{
//     uint8_t i = (buffer->head + 1) & SERIAL_BUFFER_MASK;

//     // if we should be storing the received character into the location
//     // just before the tail (meaning that the head would advance to the
//     // current location of the tail), we're about to overflow the buffer
//     // and so we don't write the character or advance the head.
//     if (i != buffer->tail)
//     {
//         buffer->buffer[buffer->head] = c;
//         buffer->head = i;
//     }
}
// #if !defined(USART0_RX_vect) && defined(USART1_RX_vect)
// // do nothing - on the 32u4 the first USART is USART1
// #else
// void rfSerialEvent() __attribute__((weak));
// void rfSerialEvent() {}
// #define serialEvent_implemented
// #if defined(USART_RX_vect)
// SIGNAL(USART_RX_vect)
// #elif defined(USART0_RX_vect)
// SIGNAL(USART0_RX_vect)
// #else
// #if defined(SIG_USART0_RECV)
// SIGNAL(SIG_USART0_RECV)
// #elif defined(SIG_UART0_RECV)
// SIGNAL(SIG_UART0_RECV)
// #elif defined(SIG_UART_RECV)
// SIGNAL(SIG_UART_RECV)
// #else
// #error "Don't know what the Data Received vector is called for the first UART"
// #endif
// #endif
// {
// #if defined(UDR0)
//     unsigned char c  =  UDR0;
// #elif defined(UDR)
//     unsigned char c  =  UDR;
// // #else
// // #error UDR not defined
// #endif
//     rf_store_char(c, &rx_buffer);
// }
// #endif

// #if !defined(USART0_UDRE_vect) && defined(USART1_UDRE_vect)
// // do nothing - on the 32u4 the first USART is USART1
// #else
// #if !defined(UART0_UDRE_vect) && !defined(UART_UDRE_vect) && !defined(USART0_UDRE_vect) && !defined(USART_UDRE_vect)
// #error "Don't know what the Data Register Empty vector is called for the first UART"
// #else
// #if defined(UART0_UDRE_vect)
// ISR(UART0_UDRE_vect)
// #elif defined(UART_UDRE_vect)
// ISR(UART_UDRE_vect)
// #elif defined(USART0_UDRE_vect)
// ISR(USART0_UDRE_vect)
// #elif defined(USART_UDRE_vect)
// ISR(USART_UDRE_vect)
// #endif
// {
//     if (tx_buffer.head == tx_buffer.tail)
//     {
//         // Buffer empty, so disable interrupts
// #if defined(UCSR0B)
//         bit_clear(UCSR0B, UDRIE0);
// #else
//         bit_clear(UCSRB, UDRIE);
// #endif
//     }
//     else
//     {
//         // There is more data in the output buffer. Send the next byte
//         uint8_t c = tx_buffer.buffer[tx_buffer.tail];
//         tx_buffer.tail = (tx_buffer.tail + 1) & SERIAL_TX_BUFFER_MASK;

// #if defined(UDR0)
//         UDR0 = c;
// #elif defined(UDR)
//         UDR = c;
// #else
// #error UDR not defined
// #endif
//     }
// }
// #endif
// #endif

// Constructors ////////////////////////////////////////////////////////////////

RFHardwareSerial::RFHardwareSerial(ring_buffer *rx_buffer, ring_buffer_tx *tx_buffer,
                                   volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
                                   volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
                                   volatile uint8_t *udr,
                                   uint8_t rxen, uint8_t txen, uint8_t rxcie, uint8_t udrie, uint8_t u2x)
{
    _rx_buffer = rx_buffer;
    _tx_buffer = tx_buffer;
    _ubrrh = ubrrh;
    _ubrrl = ubrrl;
    _ucsra = ucsra;
    _ucsrb = ucsrb;
    _udr = udr;
    _rxen = rxen;
    _txen = txen;
    _rxcie = rxcie;
    _udrie = udrie;
    _u2x = u2x;
}

// Public Methods //////////////////////////////////////////////////////////////

void RFHardwareSerial::begin(unsigned long baud)
{
//     uint16_t baud_setting;
//     bool use_u2x = true;

// #if F_CPU == 16000000UL
//     // hardcoded exception for compatibility with the bootloader shipped
//     // with the Duemilanove and previous boards and the firmware on the 8U2
//     // on the Uno and Mega 2560.
//     if (baud == 57600)
//     {
//         use_u2x = false;
//     }
// #endif

// try_again:

//     if (use_u2x)
//     {
//         *_ucsra = 1 << _u2x;
//         baud_setting = (F_CPU / 4 / baud - 1) / 2;
//     }
//     else
//     {
//         *_ucsra = 0;
//         baud_setting = (F_CPU / 8 / baud - 1) / 2;
//     }

//     if ((baud_setting > 4095) && use_u2x)
//     {
//         use_u2x = false;
//         goto try_again;
//     }

//     // assign the baud_setting, a.k.a. ubbr (USART Baud Rate Register)
//     *_ubrrh = baud_setting >> 8;
//     *_ubrrl = baud_setting;

//     bit_set(*_ucsrb, _rxen);
//     bit_set(*_ucsrb, _txen);
//     bit_set(*_ucsrb, _rxcie);
//     bit_clear(*_ucsrb, _udrie);
}

void RFHardwareSerial::end()
{
//     // wait for transmission of outgoing data
//     while (_tx_buffer->head != _tx_buffer->tail)
//         ;

//     bit_clear(*_ucsrb, _rxen);
//     bit_clear(*_ucsrb, _txen);
//     bit_clear(*_ucsrb, _rxcie);
//     bit_clear(*_ucsrb, _udrie);

//     // clear a  ny received data
//     _rx_buffer->head = _rx_buffer->tail;
}

int RFHardwareSerial::available(void)
{
//     return (unsigned int)(SERIAL_BUFFER_SIZE + _rx_buffer->head - _rx_buffer->tail) & SERIAL_BUFFER_MASK;
}
int RFHardwareSerial::outputUnused(void)
{
//     return SERIAL_TX_BUFFER_SIZE-(unsigned int)((SERIAL_TX_BUFFER_SIZE + _tx_buffer->head - _tx_buffer->tail) & SERIAL_TX_BUFFER_MASK);
}

int RFHardwareSerial::peek(void)
{
//     if (_rx_buffer->head == _rx_buffer->tail)
//     {
//         return -1;
//     }
//     return _rx_buffer->buffer[_rx_buffer->tail];
}

int RFHardwareSerial::read(void)
{
//     // if the head isn't ahead of the tail, we don't have any characters
//     if (_rx_buffer->head == _rx_buffer->tail)
//     {
//         return -1;
//     }
//     unsigned char c = _rx_buffer->buffer[_rx_buffer->tail];
//     _rx_buffer->tail = (_rx_buffer->tail + 1) & SERIAL_BUFFER_MASK;
//     return c;
}

void RFHardwareSerial::flush()
{
//     while (_tx_buffer->head != _tx_buffer->tail)
//         ;
}
#ifdef COMPAT_PRE1
void
#else
size_t
#endif
RFHardwareSerial::write(uint8_t c)
{
//     uint8_t i = (_tx_buffer->head + 1) & SERIAL_TX_BUFFER_MASK;

//     // If the output buffer is full, there's nothing for it other than to
//     // wait for the interrupt handler to empty it a bit
//     while (i == _tx_buffer->tail)
//         ;

//     _tx_buffer->buffer[_tx_buffer->head] = c;
//     _tx_buffer->head = i;

//     bit_set(*_ucsrb, _udrie);
// #ifndef COMPAT_PRE1
//     return 1;
// #endif
}

// Preinstantiate Objects //////////////////////////////////////////////////////

// #if defined(UBRRH) && defined(UBRRL)
// RFHardwareSerial RFSerial(&rx_buffer, &tx_buffer, &UBRRH, &UBRRL, &UCSRA, &UCSRB, &UDR, RXEN, TXEN, RXCIE, UDRIE, U2X);
// #elif defined(UBRR0H) && defined(UBRR0L)
// RFHardwareSerial RFSerial(&rx_buffer, &tx_buffer, &UBRR0H, &UBRR0L, &UCSR0A, &UCSR0B, &UDR0, RXEN0, TXEN0, RXCIE0, UDRIE0, U2X0);
// #elif defined(USBCON)
// // do nothing - Serial object and buffers are initialized in CDC code
// #else
// #error no serial port defined  (port 0)
// #endif

#endif

