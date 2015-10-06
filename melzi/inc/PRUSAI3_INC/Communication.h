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
*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "projectInclude.h"

extern const char *tDebug;
extern const char *tOk;
extern const char *tNewline;
extern const char *tNAN;
extern const char *tINF;
extern const char *tError;
extern const char *tInfo;
extern const char *tWarning;
extern const char *tWait;
extern const char *tResend;
extern const char *tEcho;
extern const char *tOkSpace;
extern const char *tWrongChecksum;
extern const char *tMissingChecksum;
extern const char *tBuffOverFlow;
extern const char *tFormatError;
extern const char *tDonePrinting;
extern const char *tX;
extern const char *tY;
extern const char *tZ;
extern const char *tE;
extern const char *tF;
extern const char *tS;
extern const char *tP;
extern const char *tI;
extern const char *tJ;
extern const char *tR;
extern const char *tSDReadError;
extern const char *tExpectedLine;
extern const char *tGot;
extern const char *tSkip;
extern const char *tBLK;
extern const char *tStart;
extern const char *tPowerUp;
extern const char *tExternalReset;
extern const char *tBrownOut;
extern const char *tWatchdog;
extern const char *tSoftwareReset;
extern const char *tUnknownCommand;
extern const char *tFreeRAM;
extern const char *tXColon;
extern const char *tSpaceXColon;
extern const char *tSpaceYColon;
extern const char *tSpaceZColon;
extern const char *tSpaceEColon;
extern const char *tTColon;
extern const char *tSpaceBColon;
extern const char *tSpaceAtColon;
extern const char *tSpaceT;
extern const char *tSpaceAt;
extern const char *tSpaceBAtColon;
extern const char *tSpaceRaw;
extern const char *tColon;
extern const char *tSlash;
extern const char *tSpeedMultiply;
extern const char *tFlowMultiply;
extern const char *tFanspeed;
extern const char *tPrintedFilament;
extern const char *tPrintingTime;
extern const char *tSpacem;
extern const char *tSpaceDaysSpace;
extern const char *tSpaceHoursSpace;
extern const char *tSpaceMin;
extern const char *tInvalidArc;
extern const char *tComma;
extern const char *tSpace;
extern const char *tYColon;
extern const char *tZColon;
extern const char *tE0Colon;
extern const char *tE1Colon;
extern const char *tMS1MS2Pins;
extern const char *tSetOutputSpace;
extern const char *tSpaceToSpace;
extern const char *tHSpace;
extern const char *tLSpace;
extern const char *tXMinColon;
extern const char *tXMaxColon;
extern const char *tYMinColon;
extern const char *tYMaxColon;
extern const char *tZMinColon;
extern const char *tZMaxColon;
extern const char *tJerkColon;
extern const char *tZJerkColon;
extern const char *tLinearStepsColon;
extern const char *tQuadraticStepsColon;
extern const char *tCommaSpeedEqual;
extern const char *tEEPROMUpdated;

extern const char *tLinearLColon;
extern const char *tQuadraticKColon;
#if DRIVE_SYSTEM==3
extern const char *tMeasurementReset;
extern const char *tMeasureDeltaSteps;
extern const char *tMeasureDelta;
extern const char *tMeasureOriginReset;
extern const char *tMeasurementAbortedOrigin";
extern const char *tInvalidDeltaCoordinate;
extern const char *tLevelingCalc;
extern const char *tTower1;
extern const char *tTower2;
extern const char *tTower3;
extern const char *tDeltaAlphaA;
extern const char *tDeltaAlphaB;
extern const char *tDeltaAlphaC;
extern const char *tDeltaRadiusCorrectionA;
extern const char *tDeltaRadiusCorrectionB;
extern const char *tDeltaRadiusCorrectionC;
extern const char *tDBGDeltaNoMoveinDSegment;
#endif // DRIVE_SYSTEM
#if DRIVE_SYSTEM==4
extern const char *tInvalidDeltaCoordinate;
extern const char *tDBGDeltaNoMoveinDSegment;
extern const char *tEPRDiagonalRodLength;
#endif // DRIVE_SYSTEM
#ifdef DEBUG_GENERIC
extern const char *tGenTemp;
#endif // DEBUG_GENERICextern const char *="";
extern const char *tTargetExtr;
extern const char *tTargetBedColon;
extern const char *tPIDAutotuneStart;
extern const char *tAPIDBias;
extern const char *tAPIDD;
extern const char *tAPIDMin;
extern const char *tAPIDMax;
extern const char *tAPIDKu;
extern const char *tAPIDTu;
extern const char *tAPIDClassic;
extern const char *tAPIDKp;
extern const char *tAPIDKi;
extern const char *tAPIDKd;
extern const char *tAPIDFailedHigh;
extern const char *tAPIDFailedTimeout;
extern const char *tAPIDFinished;
extern const char *tMTEMPColon;
extern const char *tHeatedBed;
extern const char *tExtruderSpace;
extern const char *tTempSensorDefect;
extern const char *tTempSensorWorking;
extern const char *tDryModeUntilRestart;
#ifdef DEBUG_QUEUE_MOVE
extern const char *tDBGId;
extern const char *tDBGVStartEnd;
extern const char *tDBAccelSteps;
extern const char *tDBGStartEndSpeed;
extern const char *tDBGFlags;
extern const char *tDBGJoinFlags;
extern const char *tDBGDelta;
extern const char *tDBGDir;
extern const char *tDBGFullSpeed;
extern const char *tDBGVMax;
extern const char *tDBGAcceleration;
extern const char *tDBGAccelerationPrim;
extern const char *tDBGRemainingSteps;
extern const char *tDBGAdvanceFull;
extern const char *tDBGAdvanceRate;
extern const char *tDBGLimitInterval;
extern const char *tDBGMoveDistance;
extern const char *tDBGCommandedFeedrate;
extern const char *tDBGConstFullSpeedMoveTime;
#endif // DEBUG_QUEUE_MOVEextern const char *="";
#ifdef DEBUG_DELTA_OVERFLOW
extern const char *tDBGDeltaOverflow;
#endif // DEBUG_DELTA_OVERFLOW
#ifdef DEBUG_SPLIT
extern const char *tDBGDeltaSeconds;
extern const char *tDBGDeltaZDelta;
extern const char *tDBGDeltaSegments;
extern const char *tDBGDeltaNumLines;
extern const char *tDBGDeltaSegmentsPerLine;
extern const char *tDBGDeltaMaxDS;
extern const char *tDBGDeltaStepsPerSegment;
extern const char *tDBGDeltaVirtualAxisSteps;
#endif
#ifdef DEBUG_STEPCOUNT
extern const char *tDBGMissedSteps;
#endif // DEBUG_STEPCOUNT
#if FEATURE_Z_PROBE
extern const char *tZProbe;
extern const char *tZProbeAverage;
extern const char *tZProbeZReset;
extern const char *tZProbeState;
extern const char *tZProbeStartScript,Z_PROBE_START_SCRIPT;
extern const char *tZProbeEndScript,Z_PROBE_FINISHED_SCRIPT;
extern const char *tHitZProbe;
extern const char *tAutolevelReset;
#endif
extern const char *tAutolevelEnabled;
extern const char *tAutolevelDisabled;
extern const char *tZProbeFailed;
extern const char *tZProbeMax;
extern const char *tZProbePrinterHeight;
//extern const char *="";
#if EEPROM_MODE==0
extern const char *tNoEEPROMSupport;
#else
#if FEATURE_Z_PROBE
extern const char *tZProbeHeight;
extern const char *tZProbeOffsetX;
extern const char *tZProbeOffsetY;
extern const char *tZProbeSpeed;
extern const char *tZProbeSpeedXY;
extern const char *tZProbeX1;
extern const char *tZProbeY1;
extern const char *tZProbeX2;
extern const char *tZProbeY2;
extern const char *tZProbeX3;
extern const char *tZProbeY3;
#endif
#if FEATURE_AUTOLEVEL
extern const char *tAutolevelActive;
#endif
extern const char *tConfigStoredEEPROM;
extern const char *tConfigLoadedEEPROM;
extern const char *tEPRConfigResetDefaults;
extern const char *tEPRProtocolChanged;
extern const char *tExtrDot;
extern const char *tEPR0;
extern const char *tEPR1;
extern const char *tEPR2;
extern const char *tEPR3;
extern const char *tEPRBaudrate;
extern const char *tEPRFilamentPrinted;
extern const char *tEPRPrinterActive;
extern const char *tEPRMaxInactiveTime;
extern const char *tEPRStopAfterInactivty;
extern const char *tEPRXHomePos;
extern const char *tEPRYHomePos;
extern const char *tEPRZHomePos;
extern const char *tEPRXMaxLength;
extern const char *tEPRYMaxLength;
extern const char *tEPRZMaxLength;
extern const char *tEPRXBacklash;
extern const char *tEPRYBacklash;
extern const char *tEPRZBacklash;
extern const char *tEPRMaxJerk;
#if DRIVE_SYSTEM==3
extern const char *tEPRZAcceleration;
extern const char *tEPRZTravelAcceleration;
extern const char *tEPRZStepsPerMM;
extern const char *tEPRZMaxFeedrate;
extern const char *tEPRZHomingFeedrate;

extern const char *tEPRDiagonalRodLength;
extern const char *tEPRHorizontalRadius;
extern const char *tEPRSegmentsPerSecondPrint;
extern const char *tEPRSegmentsPerSecondTravel;

extern const char *tEPRTowerXOffset;
extern const char *tEPRTowerYOffset;
extern const char *tEPRTowerZOffset;

#else
extern const char *tEPRMaxZJerk;
extern const char *tEPRXStepsPerMM;
extern const char *tEPRYStepsPerMM;
extern const char *tEPRZStepsPerMM;
extern const char *tEPRXMaxFeedrate;
extern const char *tEPRYMaxFeedrate;
extern const char *tEPRZMaxFeedrate;
extern const char *tEPRXHomingFeedrate;
extern const char *tEPRYHomingFeedrate;
extern const char *tEPRZHomingFeedrate;
extern const char *tEPRXAcceleration;
extern const char *tEPRYAcceleration;
extern const char *tEPRZAcceleration;
extern const char *tEPRXTravelAcceleration;
extern const char *tEPRYTravelAcceleration;
extern const char *tEPRZTravelAcceleration;
#endif
extern const char *tEPROPSMode;
extern const char *tEPROPSMoveAfter;
extern const char *tEPROPSMinDistance;
extern const char *tEPROPSRetractionLength;
extern const char *tEPROPSRetractionBacklash;
extern const char *tEPRBedHeatManager;
extern const char *tEPRBedPIDDriveMax;
extern const char *tEPRBedPIDDriveMin;
extern const char *tEPRBedPGain;
extern const char *tEPRBedIGain;
extern const char *tEPRBedDGain;
extern const char *tEPRBedPISMaxValue;
extern const char *tEPRStepsPerMM;
extern const char *tEPRMaxFeedrate;
extern const char *tEPRStartFeedrate;
extern const char *tEPRAcceleration;
extern const char *tEPRHeatManager;
extern const char *tEPRDriveMax;
extern const char *tEPRDriveMin;
extern const char *tEPRPGain;
extern const char *tEPRIGain;
extern const char *tEPRDGain;
extern const char *tEPRPIDMaxValue;
extern const char *tEPRXOffset;
extern const char *tEPRYOffset;
extern const char *tEPRStabilizeTime;
extern const char *tEPRRetractionWhenHeating;
extern const char *tEPRDistanceRetractHeating;
extern const char *tEPRExtruderCoolerSpeed;
extern const char *tEPRAdvanceK;
extern const char *tEPRAdvanceL;

#endif
#if SDSUPPORT
// extern const char *tSDRemoved,UI_TEXT_SD_REMOVED;
// extern const char *tSDInserted,UI_TEXT_SD_INSERTED;
extern const char *tSDInitFail;
extern const char *tErrorWritingToFile;
extern const char *tBeginFileList;
extern const char *tEndFileList;
extern const char *tFileOpened;
extern const char *tSpaceSizeColon;
extern const char *tFileSelected;
extern const char *tFileOpenFailed;
extern const char *tSDPrintingByte;
extern const char *tNotSDPrinting;
extern const char *tOpenFailedFile;
extern const char *tWritingToFile;
extern const char *tDoneSavingFile;
extern const char *tFileDeleted;
extern const char *tDeletionFailed;
extern const char *tDirectoryCreated;
extern const char *tCreationFailed;
extern const char *tSDErrorCode;
#endif

class Com
{
    public:
void printNumber(unsigned long n);
void printWarningF(const char *text);
void printInfoF(const char *(text));
void printErrorF(const char *(text));
void printWarningFLN(const char *(text));
void printInfoFLN(const char *(text));
void printErrorFLN(const char *(text));
void printFLN(const char *(text));
void printF(const char *(text));
void printF(const char *(text),int value);
void printF(const char *(text),const char *msg);
void printF(const char *(text),long value);
void printF(const char *(text),unsigned long value);
void printF(const char *(text),float value,uint8_t digits=2);
void printFLN(const char *(text),int value);
void printFLN(const char *(text),long value);
void printFLN(const char *(text),unsigned long value);
void printFLN(const char *(text),const char *msg);
void printFLN(const char *(text),float value,uint8_t digits=2);
void printArrayFLN(const char *(text),float *arr,uint8_t n=4,uint8_t digits=2);
void printArrayFLN(const char *(text),long *arr,uint8_t n=4);
void print(long value);
inline void print(unsigned long value) {printNumber(value);}
inline void print(int value) {print((long)value);}
void print(const char *text);
inline void print(char c) {  serialGcode.write(c);}
void printFloat(float number, uint8_t digits);
inline void println() {serialGcode.write('\r');serialGcode.write('\n');}
    protected:
    private:
};


extern Com mCom;
#endif // COMMUNICATION_H
