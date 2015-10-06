/*
    This file is part of Repetier-Firmware.

    Repetier-Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Repetier-Firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Repetier-Firmware.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _GCODE_H
#define _GCODE_H
#include "wirish\wirish.h"
#include "Repetier.h"
#define MAX_CMD_SIZE 96
class SDCard;
//===========================================================
// 二进制协议头 位定义
//===========================================================
typedef struct {
    uint16 N_V2_I   :1;   //BIT 0
    uint16 M_V2_J   :1;   //BIT 1
    uint16 G_V2_R   :1;   //BIT 2
    uint16 X        :1;   //BIT 3
    uint16 Y        :1;   //BIT 4
    uint16 Z        :1;   //BIT 5
    uint16 E        :1;   //BIT 6
    uint16 none     :1;   //BIT 7
    uint16 F        :1;   //BIT 8
    uint16 T        :1;   //BIT 9
    uint16 S        :1;   //BIT 10
    uint16 P        :1;   //BIT 11
    uint16 V2       :1;   //BIT 12
    uint16 EXT      :1;   //BIT 13
    uint16 INT      :1;   //BIT 14
    uint16 TEXT     :1;   //BIT 15
}TS_BinaryBitfieldBits;
typedef union {
    TS_BinaryBitfieldBits   bits;
    uint16                  all;
}TU_BinaryBitfield;
//===========================================================
class GCode   // 52 uint8_ts per command needed
{
    TU_BinaryBitfield   params;
    unsigned int        params2;
public:
    unsigned int N; // Line number
    unsigned int M;
    unsigned int G;
    float X;
    float Y;
    float Z;
    float E;
    float F;
    uint8_t T;
    long S;
    long P;
    float I;
    float J;
    float R;
    char *text; //text[17];
    inline bool hasM()      { return params.bits.M_V2_J; }
    inline bool hasN()      { return params.bits.N_V2_I; }
    inline bool hasG()      { return params.bits.G_V2_R; }

    inline bool hasX()      { return params.bits.X;  }
    inline bool hasY()      { return params.bits.Y;  }
    inline bool hasZ()      { return params.bits.Z;  }
    inline bool hasNoXYZ()  { return !(params.bits.X || params.bits.Y || params.bits.Z); }
    inline bool hasE()      { return params.bits.E;  }
    inline bool hasF()      { return params.bits.F;  }
    inline bool hasT()      { return params.bits.T;  }
    inline bool hasS()      { return params.bits.S;  }
    inline bool hasP()      { return params.bits.P;  }
    inline bool isV2()      { return params.bits.V2; }
    inline bool hasString() { return params.bits.TEXT;   }
    inline bool hasI()      { return params.bits.N_V2_I; }
    inline bool hasJ()      { return params.bits.M_V2_J; }
    inline bool hasR()      { return params.bits.G_V2_R; } 
    inline long getS(long def)  {return (hasS() ? S : def);}
    inline long getP(long def)  {return (hasP() ? P : def);}
    inline void setFormatError() {params2 |= 32768;}
    inline bool hasFormatError() {return ((params2 & 32768)!=0);}
    void printCommand();
    bool parseBinary(uint8_t *buffer,bool fromSerial);
    bool parseAscii(char *line,bool fromSerial);
    void popCurrentCommand();
    void echoCommand();
    /** Get next command in command buffer. After the command is processed, call gcode_command_finished() */
    static GCode *peekCurrentCommand();
    /** Frees the cache used by the last command fetched. */
    static void readFromSerial();
    static void pushCommand();
    static void executeFString(FSTRINGPARAM(cmd));
    static uint8_t computeBinarySize(char *ptr);

    friend class SDCard;
    friend class UIDisplay;
private:
    void debugCommandBuffer();
    void checkAndPushCommand();
    static void requestResend();
    inline float parseFloatValue(char *s)
    {
        char *endPtr;
        float f = (strtod(s, &endPtr));
        if(s == endPtr) setFormatError();
        return f;
    }
    inline long parseLongValue(char *s)
    {
        char *endPtr;
        long l = (strtol(s, &endPtr, 10));
        if(s == endPtr) setFormatError();
        return l;
    }

    static GCode commandsBuffered[GCODE_BUFFER_SIZE]; ///< Buffer for received commands.
    static uint8_t bufferReadIndex; ///< Read position in gcode_buffer.
    static uint8_t bufferWriteIndex; ///< Write position in gcode_buffer.
    static uint8_t commandReceiving[MAX_CMD_SIZE]; ///< Current received command.
    static uint8_t commandsReceivingWritePosition; ///< Writing position in gcode_transbuffer.
    static uint8_t sendAsBinary; ///< Flags the command as binary input.
    static uint8_t wasLastCommandReceivedAsBinary; ///< Was the last successful command in binary mode?
    static uint8_t commentDetected; ///< Flags true if we are reading the comment part of a command.
    static uint8_t binaryCommandSize; ///< Expected size of the incoming binary command.
    static bool waitUntilAllCommandsAreParsed; ///< Don't read until all commands are parsed. Needed if gcode_buffer is misused as storage for strings.
    static uint32_t lastLineNumber; ///< Last line number received.
    static uint32_t actLineNumber; ///< Line number of current command.
    static int8_t waitingForResend; ///< Waiting for line to be resend. -1 = no wait.
    static volatile uint8_t bufferLength; ///< Number of commands stored in gcode_buffer
    static millis_t timeOfLastDataPacket; ///< Time, when we got the last data packet. Used to detect missing uint8_ts.
    static uint8_t formatErrors; ///< Number of sequential format errors
};


#endif

