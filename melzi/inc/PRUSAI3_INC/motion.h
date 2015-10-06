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
#
  Functions in this file are used to communicate using ascii or repetier protocol.
*/

#ifndef MOTION_H_INCLUDED
#define MOTION_H_INCLUDED
#include "wirish\wirish.h"
#include "Repetier.h"

/** Marks the first step of a new move */
#define FLAG_WARMUP 1
#define FLAG_NOMINAL 2
#define FLAG_DECELERATING 4
#define FLAG_ACCELERATION_ENABLED 8
#define FLAG_CHECK_ENDSTOPS 16
#define FLAG_SKIP_ACCELERATING 32
#define FLAG_SKIP_DEACCELERATING 64
#define FLAG_BLOCKED 128

/** Are the step parameter computed */
#define FLAG_JOIN_STEPPARAMS_COMPUTED 1
/** The right speed is fixed. Don't check this block or any block to the left. */
#define FLAG_JOIN_END_FIXED 2
/** The left speed is fixed. Don't check left block. */
#define FLAG_JOIN_START_FIXED 4
/** Start filament retraction at move start */
#define FLAG_JOIN_START_RETRACT 8
/** Wait for filament pushback, before ending move */
#define FLAG_JOIN_END_RETRACT 16
/** Disable retract for this line */
#define FLAG_JOIN_NO_RETRACT 32
/** Wait for the extruder to finish it's up movement */
#define FLAG_JOIN_WAIT_EXTRUDER_UP 64
/** Wait for the extruder to finish it's down movement */
#define FLAG_JOIN_WAIT_EXTRUDER_DOWN 128
// Printing related data
#if NONLINEAR_SYSTEM
// Allow the delta cache to store segments for every line in line cache. Beware this gets big ... fast.
// MAX_DELTA_SEGMENTS_PER_LINE *
#define DELTA_CACHE_SIZE (MAX_DELTA_SEGMENTS_PER_LINE * MOVE_CACHE_SIZE)

class PrintLine;
typedef struct
{
    uint8_t dir; 									///< Direction of delta movement.
    uint16_t deltaSteps[3];   				    ///< Number of steps in move.
    inline void checkEndstops(PrintLine *cur,bool checkall);
    inline void setXMoveFinished()
    {
        dir&=~16;
    }
    inline void setYMoveFinished()
    {
        dir&=~32;
    }
    inline void setZMoveFinished()
    {
        dir&=~64;
    }
    inline void setXYMoveFinished()
    {
        dir&=~48;
    }
    inline bool isXPositiveMove()
    {
        return (dir & 17)==17;
    }
    inline bool isXNegativeMove()
    {
        return (dir & 17)==16;
    }
    inline bool isYPositiveMove()
    {
        return (dir & 34)==34;
    }
    inline bool isYNegativeMove()
    {
        return (dir & 34)==32;
    }
    inline bool isZPositiveMove()
    {
        return (dir & 68)==68;
    }
    inline bool isZNegativeMove()
    {
        return (dir & 68)==64;
    }
    inline bool isEPositiveMove()
    {
        return (dir & 136)==136;
    }
    inline bool isENegativeMove()
    {
        return (dir & 136)==128;
    }
    inline bool isXMove()
    {
        return (dir & 16);
    }
    inline bool isYMove()
    {
        return (dir & 32);
    }
    inline bool isXOrYMove()
    {
        return dir & 48;
    }
    inline bool isZMove()
    {
        return (dir & 64);
    }
    inline bool isEMove()
    {
        return (dir & 128);
    }
    inline bool isEOnlyMove()
    {
        return (dir & 240)==128;
    }
    inline bool isNoMove()
    {
        return (dir & 240)==0;
    }
    inline bool isXYZMove()
    {
        return dir & 112;
    }
    inline bool isMoveOfAxis(uint8_t axis)
    {
        return (dir & (16<<axis));
    }
    inline void setMoveOfAxis(uint8_t axis)
    {
        dir |= 16<<axis;
    }
    inline void setPositiveDirectionForAxis(uint8_t axis)
    {
        dir |= 1<<axis;
    }
} DeltaSegment;
extern uint8_t lastMoveID;
#endif
class UIDisplay;
class PrintLine   // RAM usage: 24*4+15 = 113 Byte
{
    friend class UIDisplay;
public:
    static uint8_t linesPos;        // 执行数据下标
    static PrintLine lines[];
    static uint8_t linesWritePos;   // 写缓冲数据的下标
    uint8_t joinFlags;
    volatile uint8_t flags;
    uint8_t dir;                    ///< Direction of movement. 1 = X+, 2 = Y+, 4= Z+, values can be combined.
    uint8_t primaryAxis;
private:

    long timeInTicks;
    uint8_t halfStep;               ///< 4 = disabled, 1 = halfstep, 2 = fulstep

    long delta[4];                  ///< Steps we want to move.
    long error[4];                  ///< Error calculation for Bresenham algorithm
    float speedX;                   ///< Speed in x direction at fullInterval in mm/s
    float speedY;                   ///< Speed in y direction at fullInterval in mm/s
    float speedZ;                   ///< Speed in z direction at fullInterval in mm/s
    float speedE;                   ///< Speed in E direction at fullInterval in mm/s
    float fullSpeed;                ///< Desired speed mm/s
    float invFullSpeed;             ///< 1.0/fullSpeed for fatser computation
    float accelerationDistance2;    ///< Real 2.0*distanceüacceleration mm2/s2
    float maxJunctionSpeed;         ///< Max. junction speed between this and next segment
    float startSpeed;               ///< Staring speed in mm/s
    float endSpeed;                 ///< Exit speed in mm/s
    float minSpeed;
    float distance;
    ticks_t fullInterval;           ///< interval at full speed in ticks/step.
    unsigned int accelSteps;        ///< How much steps does it take, to reach the plateau.
    unsigned int decelSteps;        ///< How much steps does it take, to reach the end speed.
    unsigned long accelerationPrim; ///< Acceleration along primary axis
    unsigned long fAcceleration;    ///< accelerationPrim*262144/F_CPU
    speed_t vMax;                   ///< Maximum reached speed in steps/s.
    speed_t vStart;                 ///< Starting speed in steps/s.
    speed_t vEnd;                   ///< End speed in steps/s
public:
    long stepsRemaining;                ///< Remaining steps, until move is finished
    static PrintLine *cur;
    static volatile uint8_t linesCount; // Number of lines cached 0 = nothing to do
    inline bool areParameterUpToDate() {return joinFlags & FLAG_JOIN_STEPPARAMS_COMPUTED;  }
    inline void invalidateParameter() {       joinFlags &= ~FLAG_JOIN_STEPPARAMS_COMPUTED;}
    inline void setParameterUpToDate() {joinFlags |= FLAG_JOIN_STEPPARAMS_COMPUTED;}
    inline bool isStartSpeedFixed() {return joinFlags & FLAG_JOIN_START_FIXED;}
    inline void setStartSpeedFixed(bool newState) {
        joinFlags = (newState ? joinFlags | FLAG_JOIN_START_FIXED : joinFlags & ~FLAG_JOIN_START_FIXED);
    }
    inline void fixStartAndEndSpeed() {joinFlags |= FLAG_JOIN_END_FIXED | FLAG_JOIN_START_FIXED; }
    inline bool isEndSpeedFixed() {return joinFlags & FLAG_JOIN_END_FIXED; }
    inline void setEndSpeedFixed(bool newState) {
        joinFlags = (newState ? joinFlags | FLAG_JOIN_END_FIXED : joinFlags & ~FLAG_JOIN_END_FIXED);
    }
    inline bool isWarmUp() {return flags & FLAG_WARMUP; }
    inline uint8_t getWaitForXLinesFilled() {return primaryAxis; }
    inline void setWaitForXLinesFilled(uint8_t b) {primaryAxis = b;}
    inline bool isExtruderForwardMove() {return (dir & 136)==136; }
    inline void block() {flags |= FLAG_BLOCKED; }
    inline void unblock() {flags &= ~FLAG_BLOCKED;}
    inline bool isBlocked() {return flags & FLAG_BLOCKED;}
    inline bool isCheckEndstops()  {return flags & FLAG_CHECK_ENDSTOPS;}
    inline bool isNominalMove() {return flags & FLAG_NOMINAL;}
    inline bool setNominalMove() {flags |= FLAG_NOMINAL;}
    inline void checkEndstops()  {
//         if(isCheckEndstops()) {
//             if(isXNegativeMove() && Printer::isXMinEndstopHit()) setXMoveFinished();
//             if(isYNegativeMove() && Printer::isYMinEndstopHit()) setYMoveFinished();
//             if(isXPositiveMove() && Printer::isXMaxEndstopHit()) setXMoveFinished();
//             if(isYPositiveMove() && Printer::isYMaxEndstopHit()) setYMoveFinished();
//         }
//         // Test Z-Axis every step if necessary, otherwise it could easyly ruin your printer!
//         if(isZNegativeMove() && Printer::isZMinEndstopHit())
//             setZMoveFinished();
    }
    inline void setXMoveFinished()  {dir&=~16;}
    inline void setYMoveFinished()  {dir&=~32;}
    inline void setZMoveFinished()  {dir&=~64;}
    inline void setXYMoveFinished() {dir&=~48;}
    inline bool isXPositiveMove() {return (dir & 17)==17;}
    inline bool isXNegativeMove() {return (dir & 17)==16;}
    inline bool isYPositiveMove() {return (dir & 34)==34;}
    inline bool isYNegativeMove() {return (dir & 34)==32;}
    inline bool isZPositiveMove() {return (dir & 68)==68;}
    inline bool isZNegativeMove() {return (dir & 68)==64;}
    inline bool isEPositiveMove() {return (dir & 136)==136;}
    inline bool isENegativeMove() {return (dir & 136)==128;}
    inline bool isXMove() {return (dir & 16);}
    inline bool isYMove() {return (dir & 32);}
    inline bool isXOrYMove()  {return dir & 48;}
    inline bool isZMove() {return (dir & 64);}
    inline bool isEMove() {return (dir & 128); }
    inline bool isEOnlyMove() {return (dir & 240)==128;}
    inline bool isNoMove() {return (dir & 240)==0;}
    inline bool isXYZMove() {return dir & 112;}
    inline bool isMoveOfAxis(uint8_t axis) {return (dir & (16<<axis));}
    inline void setMoveOfAxis(uint8_t axis) {dir |= 16<<axis;}
    inline void setPositiveDirectionForAxis(uint8_t axis) {dir |= 1<<axis;}
    inline static void resetPathPlanner(){
        linesCount = 0;
        linesPos = linesWritePos;
    }
    inline void updateAdvanceSteps(unsigned int v,uint8_t max_loops,bool accelerate) {}
    inline bool moveDecelerating() {
        if(stepsRemaining <= decelSteps) {
            if (!(flags & FLAG_DECELERATING)) {
                Printer::timer = 0;
                flags |= FLAG_DECELERATING;
            }
            return true;
        }
        else return false;
    }
    inline bool moveAccelerating() {return Printer::stepNumber <= accelSteps; }
    inline bool isFullstepping() {return halfStep == 4; }
    inline bool startXStep() {digitalWrite(X_STEP_PIN,HIGH);}
    inline bool startYStep() {digitalWrite(Y_STEP_PIN,HIGH);}
    inline void startZStep() {digitalWrite(Z_STEP_PIN,HIGH);}
    void updateStepsParameter();
    inline float safeSpeed();
    void calculateMove(float axis_diff[],uint8_t pathOptimize);
    void logLine();
    inline long getWaitTicks()  {return timeInTicks; }
    inline void setWaitTicks(long wait) {timeInTicks = wait;}
    static inline bool hasLines() {return linesCount;}
    static inline void setCurrentLine() {
        cur = &lines[linesPos];
    }
    static inline void removeCurrentLineForbidInterrupt() {
        linesPos++;
        if(linesPos>=MOVE_CACHE_SIZE) linesPos=0;
        cur = NULL;
        HAL::forbidInterrupts();
        --linesCount;
    }
    static inline void pushLine() {
        linesWritePos++;
        if(linesWritePos>=MOVE_CACHE_SIZE) linesWritePos = 0;
//        BEGIN_INTERRUPT_PROTECTED
        linesCount++;
//        END_INTERRUPT_PROTECTED
    }
    static PrintLine *getNextWriteLine() {
        return &lines[linesWritePos];
    }
    static inline void computeMaxJunctionSpeed(PrintLine *previous,PrintLine *current);
    static uint16 bresenhamStep();
    static void waitForXFreeLines(uint8_t b=1);
    static inline void forwardPlanner(uint8_t p);
    static inline void backwardPlanner(uint8_t p,uint8_t last);
    static void updateTrapezoids();
    static uint8_t insertWaitMovesIfNeeded(uint8_t pathOptimize, uint8_t waitExtraLines);
    static void queueCartesianMove(uint8_t check_endstops,uint8_t pathOptimize);
    static void moveRelativeDistanceInSteps(long x,long y,long z,long e,float feedrate,bool waitEnd,bool check_endstop);
    static void arc(float *position, float *target, float *offset, float radius, uint8_t isclockwise);
    static inline void previousPlannerIndex(uint8_t &p) {p = (p ? p-1 : MOVE_CACHE_SIZE-1);}
    static inline void nextPlannerIndex(uint8_t& p) {p = (p==MOVE_CACHE_SIZE-1?0:p+1);}
};

//========================================================================
// 加速曲线表 + 值 1/1000 加速区间
// 减速曲线表 - 值 1/1000 减速区间
// 数值为 0-1000
//========================================================================
extern int accelerationTab[180];


#endif // MOTION_H_INCLUDED