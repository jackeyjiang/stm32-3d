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

    This firmware is a nearly complete rewrite of the sprinter firmware
    by kliment (https://github.com/kliment/Sprinter)
    which based on Tonokip RepRap firmware rewrite based off of Hydra-mmm firmware.

  Functions in this file are used to communicate using ascii or repetier protocol.
*/

#include "Repetier.h"
#include "string.h"

#ifndef FEATURE_CHECKSUM_FORCED
#define FEATURE_CHECKSUM_FORCED false
#endif

GCode    GCode::commandsBuffered[GCODE_BUFFER_SIZE]; ///< Buffer for received commands.
uint8_t  GCode::bufferReadIndex=0; ///< Read position in gcode_buffer.
uint8_t  GCode::bufferWriteIndex=0; ///< Write position in gcode_buffer.
uint8_t  GCode::commandReceiving[MAX_CMD_SIZE]; ///< Current received command.
uint8_t  GCode::commandsReceivingWritePosition=0; ///< Writing position in gcode_transbuffer.
uint8_t  GCode::sendAsBinary; ///< Flags the command as binary input.
uint8_t  GCode::wasLastCommandReceivedAsBinary=0; ///< Was the last successful command in binary mode?
uint8_t  GCode::commentDetected=false; ///< Flags true if we are reading the comment part of a command.
uint8_t  GCode::binaryCommandSize; ///< Expected size of the incoming binary command.
bool     GCode::waitUntilAllCommandsAreParsed=false; ///< Don't read until all commands are parsed. Needed if gcode_buffer is misused as storage for strings.
uint32_t GCode::lastLineNumber=0; ///< Last line number received.
uint32_t GCode::actLineNumber; ///< Line number of current command.
int8_t   GCode::waitingForResend=-1; ///< Waiting for line to be resend. -1 = no wait.
volatile uint8_t GCode::bufferLength=0; ///< Number of commands stored in gcode_buffer
millis_t GCode::timeOfLastDataPacket=0; ///< Time, when we got the last data packet. Used to detect missing uint8_ts.
uint8_t  GCode::formatErrors=0;

/** \page Repetier-protocol

\section Introduction

The repetier-protocol was developed, to overcome some shortcommings in the standard
RepRap communication method, while remaining backward compatible. To use the improved
features of this protocal, you need a host which speaks it. On Windows the recommended
host software is Repetier-Host. It is developed in parallel to this firmware and supports
all implemented features.

\subsection Improvements

- With higher speeds, the serial connection is more likely to produce communication failures.
  The standard method is to transfer a checksum at the end of the line. This checksum is the
  XORd value of all characters send. The value is limited to a range between 0 and 127. It can
  not detect two identical missing characters or a wrong order. Therefore the new protocol
  uses Fletchers checksum, which overcomes these shortcommings.
- The new protocol send data in binary format. This reduces the data size to less then 50% and
  it speeds up decoding the command. No slow conversion from string to floats are needed.

*/

/** \brief Computes size of binary data from bitfield.

In the repetier-protocol in binary mode, the first 2 uint8_ts define the
data. From this bitfield, this function computes the size of the command
including the 2 uint8_ts of the bitfield and the 2 uint8_ts for the checksum.


Gcode Letter to Bit and Datatype:

- N : Bit 0 : 16-Bit Integer
- M : Bit 1 :  8-Bit unsigned uint8_t
- G : Bit 2 :  8-Bit unsigned uint8_t
- X : Bit 3 :  32-Bit Float
- Y : Bit 4 :  32-Bit Float
- Z : Bit 5 :  32-Bit Float
- E : Bit 6 :  32-Bit Float
-  : Bit 7 :  always set to distinguish binary from ASCII line.
- F : Bit 8 :  32-Bit Float
- T : Bit 9 :  8 Bit Integer
- S : Bit 10 : 32 Bit Value
- P : Bit 11 : 32 Bit Integer
- V2 : Bit 12 : Version 2 command for additional commands/sizes
- Ext : Bit 13 : There are 2 more uint8_ts following with Bits, only for future versions
- Int :Bit 14 : Marks it as internal command,
- Text : Bit 15 : 16 Byte ASCII String terminated with 0
Second word if V2:
- I : Bit 0 : 32-Bit float
- J : Bit 1 : 32-Bit float
- R : Bit 2 : 32-Bit float
*/
//==============================================================
// 根据位标示，解析所需要接收的字节长度
//==============================================================
uint8_t GCode::computeBinarySize(char *ptr)  // unsigned int bitfield) {
{
    uint8_t s = 4; // include checksum and bitfield
    TU_BinaryBitfield bitfield;
    bitfield.all = *(uint16_t*)ptr;

    if(bitfield.bits.N_V2_I) s+=2;
    if(bitfield.bits.X) s+=4;
    if(bitfield.bits.Y) s+=4;
    if(bitfield.bits.Z) s+=4;
    if(bitfield.bits.E) s+=4;
    if(bitfield.bits.F) s+=4;
    if(bitfield.bits.T) s+=1;
    if(bitfield.bits.S) s+=4;
    if(bitfield.bits.P) s+=4;
    if(bitfield.bits.V2) {  // Version 2 or later
        s+=2;               // for bitfield 2
        uint16_t bitfield2 = *(uint16_t*)(ptr+2);
        if(bitfield.bits.M_V2_J) s+=2;
        if(bitfield.bits.G_V2_R) s+=2;
        if(bitfield2 & 1) s+= 4;
        if(bitfield2 & 2) s+= 4;
        if(bitfield2 & 4) s+= 4;
        if(bitfield.bits.TEXT) s+=RMath::min(80,(uint8_t)ptr[4]+1);
    } else {
        if(bitfield.bits.M_V2_J) s+=1;
        if(bitfield.bits.G_V2_R) s+=1;
        if(bitfield.bits.TEXT)   s+=16;
    }
    return s;
}
//==============================================================
// 回复响应接收状态
//==============================================================
void GCode::requestResend()
{
    Serial1.flush();
    commandsReceivingWritePosition=0;
    if(sendAsBinary)    waitingForResend = 30;
    else                waitingForResend = 14;
    Com::println();
    Com::printFLN(Com::tResend,(int)lastLineNumber+1);
    Com::printFLN(Com::tOk);
}
//==============================================================
// 判断解析到的数据是否要推入命令堆栈， 如果错误则请求重新发送
/**
  Check if result is plausible. If it is, an ok is send and the command is stored in queue.
  If not, a resend and ok is send.
*/
//==============================================================
void GCode::checkAndPushCommand()
{
    if(hasM()) {
        if(M==110) { // Reset line number
            lastLineNumber = actLineNumber;
            Com::printFLN(Com::tOk);
            waitingForResend = -1;
            return;
        }
        if(M==112) {   // Emergency kill - freeze printer
            Commands::emergencyStop();
        }
#ifdef DEBUG_COM_ERRORS
        if(M==666) {
            lastLineNumber++;
            return;
        }
#endif // DEBUG_COM_ERRORS
    }
    if(hasN()) {
        //== 行号没有累加 ，行号累计保持进程同步 ==
        if((((lastLineNumber+1) & 0xffff)!=(actLineNumber&0xffff))) {
            if(waitingForResend<0) {    // after a resend, we have to skip the garbage in buffers, no message for this
                if(Printer::debugErrors()) {
                    Com::printF(Com::tExpectedLine,(uint16_t)lastLineNumber+1);
                    Com::printFLN(Com::tGot,(uint16_t)actLineNumber);
                }
                requestResend();        // Line missing, force resend
            } else {
                --waitingForResend;
                commandsReceivingWritePosition = 0;
                Com::printFLN(Com::tSkip,(uint16_t)actLineNumber);
                Com::printFLN(Com::tOk);
            }
            return;
        }
        lastLineNumber = actLineNumber;
    }
    pushCommand();
#ifdef ACK_WITH_LINENUMBER
    Com::printFLN(Com::tOkSpace,(uint16_t)actLineNumber);
#else
    Com::printFLN(Com::tOk);
#endif
    wasLastCommandReceivedAsBinary = sendAsBinary;
    waitingForResend = -1; // everything is ok.
}
//==============================================================
// 使命令加入堆栈序列
//==============================================================
void GCode::pushCommand()
{
    bufferWriteIndex = (bufferWriteIndex+1) % GCODE_BUFFER_SIZE;
    bufferLength++;
#ifndef ECHO_ON_EXECUTE
    echoCommand();
#endif
}

//==============================================================
// 读取命令
/**
  Get the next buffered command. Returns 0 if no more commands are buffered. For each
  returned command, the gcode_command_finished() function must be called.
*/
//==============================================================
GCode *GCode::peekCurrentCommand()
{
    if(bufferLength==0) return NULL; // No more data
    return &commandsBuffered[bufferReadIndex];
}

//==============================================================
// 推出最后一条命令
/** \brief Removes the last returned command from cache. */
//==============================================================
void GCode::popCurrentCommand()
{
    if(!bufferLength) return; // Should not happen, but safety first
#ifdef ECHO_ON_EXECUTE
    echoCommand();
#endif
    if(++bufferReadIndex == GCODE_BUFFER_SIZE) bufferReadIndex = 0;
    bufferLength--;
}

//==============================================================
// 打印命令
//==============================================================
void GCode::echoCommand()
{
    if(Printer::debugEcho()) {
        Com::printF(Com::tEcho);
        printCommand();
    }
}

//==============================================================
// 调试打印出所有命令
//==============================================================
void GCode::debugCommandBuffer()
{
    Com::printF(PSTR("CommandBuffer"));
    for(int i=0; i<commandsReceivingWritePosition; i++)
        Com::printF(Com::tColon,(int)commandReceiving[i]);
    Com::println();
    Com::printFLN(PSTR("Binary:"),(int)sendAsBinary);
    if(!sendAsBinary) {
        Com::print((char*)commandReceiving);
        Com::println();
    }
}

/** \brief Execute commands in progmem stored string. Multiple commands are seperated by \n */
void GCode::executeFString(FSTRINGPARAM(cmd))
{
    char buf[80];
    uint8_t buflen;
    char c;
    GCode code;
    do
    {
        // Wait for a free place in command buffer
        // Scan next command from string
        uint8_t comment=0;
        buflen = 0;
        do
        {
            c = HAL::readFlashByte(cmd++);
            if(c == 0 || c == '\n') break;
            if(c == ';') comment = 1;
            if(comment) continue;
            buf[buflen++] = c;
        }
        while(buflen<79);
        if(buflen==0)   // empty line ignore
        {
            continue;
        }
        buf[buflen]=0;
        // Send command into command buffer
        if(code.parseAscii((char *)buf,false) && (code.params.all & 518))   // Success
        {
            Commands::executeGCode(&code);
            Printer::defaultLoopActions();
        }
    }
    while(c);
}
//=================================================================================== 
// 读取串口或者sd卡数据
/** \brief Read from serial console or sdcard.
This function is the main function to read the commands from serial console or from sdcard.
It must be called frequently to empty the incoming buffer.
*/
//=================================================================================== 
void GCode::readFromSerial()
{
    if(bufferLength>=GCODE_BUFFER_SIZE) return; // all buffers full
    if(waitUntilAllCommandsAreParsed && bufferLength) return;
    waitUntilAllCommandsAreParsed=false;
    millis_t time = millis();
    
    //== 数据为空 ======
    if(!Serial1.available()) {
        //== 数据为空 200ms 重发数据   
        if((waitingForResend>=0 || commandsReceivingWritePosition>0) && time-timeOfLastDataPacket>200) {
            requestResend(); // Something is wrong, a started line was not continued in the last second
            timeOfLastDataPacket = time;
        }
        //== 数据为空 1s 循环发送 wait
#ifdef WAITING_IDENTIFIER
        else if(bufferLength == 0 && time-timeOfLastDataPacket>1000) {  // Don't do it if buffer is not empty. It may be a slow executing command.
            Com::printFLN(Com::tWait); // Unblock communication in case the last ok was not received correct.
            timeOfLastDataPacket = time;
        }
#endif
    }
    
    //== 接收数据 ======
    while(Serial1.available() && commandsReceivingWritePosition < MAX_CMD_SIZE) {   // consume data until no data or buffer full
        timeOfLastDataPacket = time; //millis();
        commandReceiving[commandsReceivingWritePosition++] = Serial1.read();
        // first lets detect, if we got an old type ascii command
        if(commandsReceivingWritePosition==1) {
            //== 等待同步头
            if(waitingForResend>=0 && wasLastCommandReceivedAsBinary) {
                (!commandReceiving[0]) ? (waitingForResend--) : (waitingForResend = 30);
                continue;
            }
            //== 接收到错误0
            if(!commandReceiving[0]) {
                commandsReceivingWritePosition = 0;
                continue;
            }
            sendAsBinary = (commandReceiving[0] & 128)!=0;
        }
        if(sendAsBinary) {
            if(commandsReceivingWritePosition < 2 ) continue;
            //== 解析数据长度
            if(commandsReceivingWritePosition == 5 || commandsReceivingWritePosition == 4)
                binaryCommandSize = computeBinarySize((char*)commandReceiving);
            //== 接收完完整一帧数据
            if(commandsReceivingWritePosition == binaryCommandSize) {
                GCode *act = &commandsBuffered[bufferWriteIndex];
                if(act->parseBinary(commandReceiving,true)) act->checkAndPushCommand();
                else                                        requestResend();
                commandsReceivingWritePosition = 0;
                return;
            }
        } else {    // Ascii command
            char ch = commandReceiving[commandsReceivingWritePosition-1];
            if(ch == 0 || ch == '\n' || ch == '\r' || (!commentDetected && ch == ':')) { // complete line read
                //Com::printF(PSTR("Parse ascii"));Com::print((char*)commandReceiving);Com::println();
                commandReceiving[commandsReceivingWritePosition-1]=0;
                commentDetected = false;
                if(commandsReceivingWritePosition==1) {  // empty line ignore
                    commandsReceivingWritePosition = 0;
                    continue;
                }
                GCode *act = &commandsBuffered[bufferWriteIndex];
                if(act->parseAscii((char *)commandReceiving,true))   act->checkAndPushCommand();
                else                                                 requestResend(); 
                commandsReceivingWritePosition = 0;
                return;
            } else {
                if(ch == ';') commentDetected = true; // ignore new data until lineend
                if(commentDetected) commandsReceivingWritePosition--;
            }
        }
        if(commandsReceivingWritePosition == MAX_CMD_SIZE)
        {
            requestResend();
            return;
        }
    }
// #if SDSUPPORT
//     if(!sd.sdmode || commandsReceivingWritePosition!=0)   // not reading or incoming serial command
//         return;
//     while( sd.filesize > sd.sdpos && commandsReceivingWritePosition < MAX_CMD_SIZE)    // consume data until no data or buffer full
//     {
//         timeOfLastDataPacket = millis();
//         int n = sd.file.read();
//         if(n==-1)
//         {
//             Com::printFLN(Com::tSDReadError);
//             sd.sdmode = false;
//             UI_STATUS("SD Read Error");
//             break;
//         }
//         sd.sdpos++; // = file.curPosition();
//         commandReceiving[commandsReceivingWritePosition++] = (uint8_t)n;

//         // first lets detect, if we got an old type ascii command
//         if(commandsReceivingWritePosition==1)
//         {
//             sendAsBinary = (commandReceiving[0] & 128)!=0;
//         }
//         if(sendAsBinary)
//         {
//             if(commandsReceivingWritePosition < 2 ) continue;
//             if(commandsReceivingWritePosition == 4 || commandsReceivingWritePosition == 5)
//                 binaryCommandSize = computeBinarySize((char*)commandReceiving);
//             if(commandsReceivingWritePosition==binaryCommandSize)
//             {
//                 GCode *act = &commandsBuffered[bufferWriteIndex];
//                 if(act->parseBinary(commandReceiving,false))   // Success, silently ignore illegal commands
//                     pushCommand();
//                 commandsReceivingWritePosition = 0;
//                 return;
//             }
//         }
//         else
//         {
//             char ch = commandReceiving[commandsReceivingWritePosition-1];
//             bool returnChar = ch == '\n' || ch == '\r';
//             if(returnChar || sd.filesize == sd.sdpos || (!commentDetected && ch == ':') || commandsReceivingWritePosition >= (MAX_CMD_SIZE - 1) )  // complete line read
//             {
//                 if(returnChar || ch == ':')
//                     commandReceiving[commandsReceivingWritePosition-1]=0;
//                 else
//                     commandReceiving[commandsReceivingWritePosition]=0;
//                 commentDetected = false;
//                 if(commandsReceivingWritePosition==1)   // empty line ignore
//                 {
//                     commandsReceivingWritePosition = 0;
//                     continue;
//                 }
//                 GCode *act = &commandsBuffered[bufferWriteIndex];
//                 if(act->parseAscii((char *)commandReceiving,false))   // Success
//                     pushCommand();
//                 commandsReceivingWritePosition = 0;
//                 return;
//             }
//             else
//             {
//                 if(ch == ';') commentDetected = true; // ignore new data until lineend
//                 if(commentDetected) commandsReceivingWritePosition--;
//             }
//         }
//     }
//     sd.sdmode = false;
//     Com::printFLN(Com::tDonePrinting);
//     commandsReceivingWritePosition = 0;
//     commentDetected = false;
//     Printer::setMenuMode(MENU_MODE_SD_PRINTING,false);
// #endif
}

//=================================================================
// 转换一组二进制 GCODE 到结构缓存
//   Converts a binary uint8_tfield containing one GCode line into a GCode structure.
//   Returns true if checksum was correct.
//=================================================================
bool GCode::parseBinary(uint8_t *buffer,bool fromSerial)
{
    //== 和校验 ================================
    // first do fletcher-16 checksum tests see
    // http://en.wikipedia.org/wiki/Fletcher's_checksum
    unsigned int sum1=0,sum2=0; // for fletcher-16 checksum   
    uint8_t *p = buffer;
    uint8_t len = binaryCommandSize-2;
    while (len) {
        uint8_t tlen = len > 21 ? 21 : len;
        len -= tlen;
        do {
            sum1 += *p++;
            if(sum1>=255) sum1-=255;
            sum2 += sum1;
            if(sum2>=255) sum2-=255;
        } while (--tlen);
    }
    sum1 -= *p++;
    sum2 -= *p;
    if(sum1 | sum2) {
        if(Printer::debugErrors()) {
            Com::printErrorFLN(Com::tWrongChecksum);
        }
        return false;
    }
    //== 数据拆分解析 ============================
    p = buffer;
    params.all = *(unsigned int *)p;
    p+=2;
    uint8_t textlen=16;
    if(params.bits.V2) {
        params2 = *(unsigned int *)p;
        p+=2;
        if(params.bits.TEXT) textlen = *p++;
    } else params2 = 0;
    if(params.bits.N_V2_I) {
//88***88
//        actLineNumber=N=*(uint16_t *)p;
        actLineNumber++;
        p+=2;
    }
    if(params.bits.V2) {   // Read G,M as 16 bit value
        if(params.bits.M_V2_J) {M=*(uint16_t *)p;     p+=2;}
        if(params.bits.G_V2_R) {G=*(uint16_t *)p;     p+=2;}
    } else {
        if(params.bits.M_V2_J) {M=*p++;}
        if(params.bits.G_V2_R) {G=*p++;}
    }
    if(params.bits.X)    {X=*(float *)p;   p+=4;}
    if(params.bits.Y)    {Y=*(float *)p;   p+=4;}
    if(params.bits.Z)    {Z =*(float *)p;  p+=4;}
    if(params.bits.E)    {E=*(float *)p;   p+=4;}
    if(params.bits.F)    {F=*(float *)p;   p+=4;}
    if(params.bits.T)    {T=*p++;    }
    if(params.bits.S)    {S=*(int32_t*)p;  p+=4;}
    if(params.bits.P)    {P=*(int32_t*)p;  p+=4;}
    if(params.bits.N_V2_I) {I=*(float *)p; p+=4;}
    if(params.bits.M_V2_J) {J=*(float *)p; p+=4;}
    if(params.bits.G_V2_R) {R=*(float *)p; p+=4;}
    if(params.bits.TEXT) {                  // set text pointer to string
        text = (char*)p;
        text[textlen] = 0;                  // Terminate string overwriting checksum
        waitUntilAllCommandsAreParsed=true; // Don't destroy string until executed
    }
    formatErrors = 0;
    return true;
}
//=================================================================
// 转换一组ascii GCODE 到结构缓存
/**
  Converts a ascii GCode line into a GCode structure.
*/
//=================================================================
bool GCode::parseAscii(char *line,bool fromSerial)
{
    bool has_checksum = false;
    char *pos;
    params.all = 0;
    params2 = 0;
    if((pos = strchr(line,'N'))!=0)  {  // Line number detected
        actLineNumber = parseLongValue(++pos);
        params.bits.N_V2_I=1;
        N = actLineNumber & 0xffff;
    }
    if((pos = strchr(line,'M'))!=0) {   // M command
        M = parseLongValue(++pos) & 0xffff;
        params.bits.M_V2_J=1;
        if(M>255) params.bits.V2=1;
    }
    if(hasM() && (M == 23 || M == 28 || M == 29 || M == 30 || M == 32 || M == 117)) {
        // after M command we got a filename for sd card management
        char *sp = line;
        while(*sp!='M') sp++; // Search M command
        while(*sp!=' ') sp++; // search next whitespace
        while(*sp==' ') sp++; // skip leading whitespaces
        text = sp;
        while(*sp)
        {
            if(M != 117 && (*sp==' ' || *sp=='*')) break; // end of filename reached
            sp++;
        }
        *sp = 0; // Removes checksum, but we don't care. Could also be part of the string.
        waitUntilAllCommandsAreParsed = true; // don't risk string be deleted
        params.bits.TEXT = 1;
    } else {
        if((pos = strchr(line,'G'))!=0) {   // G command
            G = parseLongValue(++pos) & 0xffff;
            params.bits.G_V2_R=1;
            if(G>255) params.bits.V2=1;
        }
        if((pos = strchr(line,'X'))!=0) {
            X = parseFloatValue(++pos);
            params.bits.X=1;
        }
        if((pos = strchr(line,'Y'))!=0) {
            Y = parseFloatValue(++pos);
            params.bits.Y=1;
        }
        if((pos = strchr(line,'Z'))!=0) {
            Z = parseFloatValue(++pos);
            params.bits.Z=1;
        }
        if((pos = strchr(line,'E'))!=0) {
            E = parseFloatValue(++pos);
            params.bits.E=1;
        }
        if((pos = strchr(line,'F'))!=0) {
            F = parseFloatValue(++pos);
            params.bits.F=1;
        }
        if((pos = strchr(line,'T'))!=0) {  // M command
            T = parseLongValue(++pos) & 0xff;
            params.bits.T=1;
        }
        if((pos = strchr(line,'S'))!=0) {  // M command
            S = parseLongValue(++pos);
            params.bits.S=1;
        }
        if((pos = strchr(line,'P'))!=0) {  // M command
            P = parseLongValue(++pos);
            params.bits.P=1;
        }
        if((pos = strchr(line,'I'))!=0) {
            I = parseFloatValue(++pos);
            params2 |= 1;
            params.bits.N_V2_I=1; // Needs V2 for saving
        }
        if((pos = strchr(line,'J'))!=0) {
            J = parseFloatValue(++pos);
            params2 |= 2;
            params.bits.M_V2_J=1; // Needs V2 for saving
        }
        if((pos = strchr(line,'R'))!=0) {
            R = parseFloatValue(++pos);
            params2 |= 4;
            params.bits.G_V2_R=1; // Needs V2 for saving
        }
    }
    if((pos = strchr(line,'*'))!=0) {  // checksum
        uint8_t checksum_given = parseLongValue(pos+1);
        uint8_t checksum = 0;
        while(line!=pos) checksum ^= *line++;
#if FEATURE_CHECKSUM_FORCED
        Printer::flag0 |= PRINTER_FLAG0_FORCE_CHECKSUM;
#endif
        if(checksum!=checksum_given) {
            if(Printer::debugErrors()) {
                Com::printErrorFLN(Com::tWrongChecksum);
            }
            return false; // mismatch
        }
    }
#if FEATURE_CHECKSUM_FORCED
    else {
        if(!fromSerial) return true;
        if(hasM() && (M == 110 || hasString())) return true;
        if(Printer::debugErrors()) {
            Com::printErrorFLN(Com::tMissingChecksum);
        }
        return false;
    }
#endif
    if(hasFormatError() || (params.all & 518)==0) {   // Must contain G, M or T command and parameter need to have variables!
        formatErrors++;
        if(Printer::debugErrors())
            Com::printErrorFLN(Com::tFormatError);
        if(formatErrors<3) return false;
    }
    else formatErrors = 0;
    return true;
}
//=======================================================
// 打印命令信息
/** \brief Print command on serial console */
//======================================================
void GCode::printCommand()
{
    if(params.bits.M_V2_J) {
        Com::print('M');
        Com::print((int)M);
        Com::print(' ');
    }
    if(params.bits.G_V2_R) {
        Com::print('G');
        Com::print((int)G);
        Com::print(' ');
    }
    if(params.bits.T) {
        Com::print('T');
        Com::print((int)T);
        Com::print(' ');
    }
    if(params.bits.X)    {Com::printF(Com::tX,X);   }
    if(params.bits.Y)    {Com::printF(Com::tY,Y);   }
    if(params.bits.Z)    {Com::printF(Com::tZ,Z);   }
    if(params.bits.E)    {Com::printF(Com::tE,E,4); }
    if(params.bits.F)    {Com::printF(Com::tF,F);   }
    if(params.bits.S)    {Com::printF(Com::tS,S);   }
    if(params.bits.P)    {Com::printF(Com::tP,P);   }
    if(params.bits.N_V2_I)  {Com::printF(Com::tI,I);}
    if(params.bits.M_V2_J)  {Com::printF(Com::tJ,J);}
    if(params.bits.G_V2_R)  {Com::printF(Com::tR,R);}
    if(params.bits.TEXT)    {Com::print(text);      }
    Com::println();
}
