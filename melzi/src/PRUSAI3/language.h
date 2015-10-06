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
inline void print(char c) {  serialCommu.write(c);}
void printFloat(float number, uint8_t digits);
inline void println() {serialCommu.write('\r');serialCommu.write('\n');}
    protected:
    private:
};


extern Com mCom;



#define MSG_Enqueing "enqueing \""
#define MSG_POWERUP "PowerUp"
#define MSG_EXTERNAL_RESET " External Reset"
#define MSG_BROWNOUT_RESET " Brown out Reset"
#define MSG_WATCHDOG_RESET " Watchdog Reset"
#define MSG_SOFTWARE_RESET " Software Reset"
#define MSG_AUTHOR " | Author: "
#define MSG_CONFIGURATION_VER " Last Updated: "
#define MSG_FREE_MEMORY " Free Memory: "
#define MSG_PLANNER_BUFFER_BYTES "  PlannerBufferBytes: "
#define MSG_OK "ok"
#define MSG_FILE_SAVED "Done saving file."
#define MSG_ERR_LINE_NO "Line Number is not Last Line Number+1, Last Line: "
#define MSG_ERR_CHECKSUM_MISMATCH "checksum mismatch, Last Line: "
#define MSG_ERR_NO_CHECKSUM "No Checksum with line number, Last Line: "
#define MSG_ERR_NO_LINENUMBER_WITH_CHECKSUM "No Line Number with checksum, Last Line: "
#define MSG_FILE_PRINTED "Done printing file"
#define MSG_BEGIN_FILE_LIST "Begin file list"
#define MSG_END_FILE_LIST "End file list"
#define MSG_M104_INVALID_EXTRUDER "M104 Invalid extruder "
#define MSG_M105_INVALID_EXTRUDER "M105 Invalid extruder "
#define MSG_M200_INVALID_EXTRUDER "M200 Invalid extruder "
#define MSG_M218_INVALID_EXTRUDER "M218 Invalid extruder "
#define MSG_M221_INVALID_EXTRUDER "M221 Invalid extruder "
#define MSG_ERR_NO_THERMISTORS "No thermistors - no temperature"
#define MSG_M109_INVALID_EXTRUDER "M109 Invalid extruder "
#define MSG_HEATING "Heating..."
#define MSG_HEATING_COMPLETE "Heating done."
#define MSG_BED_HEATING "Bed Heating."
#define MSG_BED_DONE "Bed done."
#define MSG_M115_REPORT "FIRMWARE_NAME:Marlin V1; Sprinter/grbl mashup for gen6 FIRMWARE_URL:" FIRMWARE_URL " PROTOCOL_VERSION:" PROTOCOL_VERSION " MACHINE_TYPE:" MACHINE_NAME " EXTRUDER_COUNT:" STRINGIFY(EXTRUDERS) " UUID:" MACHINE_UUID "\n"
#define MSG_COUNT_X " Count X: "
#define MSG_ERR_KILLED "Printer halted. kill() called!"
#define MSG_ERR_STOPPED "Printer stopped due to errors. Fix the error and use M999 to restart. (Temperature is reset. Set it after restarting)"
#define MSG_RESEND "Resend: "
#define MSG_UNKNOWN_COMMAND "Unknown command: \""
#define MSG_ACTIVE_EXTRUDER "Active Extruder: "
#define MSG_INVALID_EXTRUDER "Invalid extruder"
#define MSG_X_MIN "x_min: "
#define MSG_X_MAX "x_max: "
#define MSG_Y_MIN "y_min: "
#define MSG_Y_MAX "y_max: "
#define MSG_Z_MIN "z_min: "
#define MSG_Z_MAX "z_max: "
#define MSG_M119_REPORT "Reporting endstop status"
#define MSG_ENDSTOP_HIT "TRIGGERED"
#define MSG_ENDSTOP_OPEN "open"
#define MSG_HOTEND_OFFSET "Hotend offsets:"

#define MSG_SD_CANT_OPEN_SUBDIR "Cannot open subdir"
#define MSG_SD_INIT_FAIL "SD init fail"
#define MSG_SD_VOL_INIT_FAIL "volume.init failed"
#define MSG_SD_OPENROOT_FAIL "openRoot failed"
#define MSG_SD_CARD_OK "SD card ok"
#define MSG_SD_WORKDIR_FAIL "workDir open failed"
#define MSG_SD_OPEN_FILE_FAIL "open failed, File: "
#define MSG_SD_FILE_OPENED "File opened: "
#define MSG_SD_SIZE " Size: "
#define MSG_SD_FILE_SELECTED "File selected"
#define MSG_SD_WRITE_TO_FILE "Writing to file: "
#define MSG_SD_PRINTING_BYTE "SD printing byte "
#define MSG_SD_NOT_PRINTING "Not SD printing"
#define MSG_SD_ERR_WRITE_TO_FILE "error writing to file"
#define MSG_SD_CANT_ENTER_SUBDIR "Cannot enter subdir: "

#define MSG_STEPPER_TOO_HIGH "Steprate too high: "
#define MSG_ENDSTOPS_HIT "endstops hit: "
#define MSG_ERR_COLD_EXTRUDE_STOP " cold extrusion prevented"
#define MSG_ERR_LONG_EXTRUDE_STOP " too long extrusion prevented"
#define MSG_BABYSTEPPING_X "Babystepping X"
#define MSG_BABYSTEPPING_Y "Babystepping Y"
#define MSG_BABYSTEPPING_Z "Babystepping Z"
#define MSG_SERIAL_ERROR_MENU_STRUCTURE "Error in menu structure"

#if LANGUAGE_CHOICE == 1

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " ready."
	#define MSG_SD_INSERTED "Card inserted"
	#define MSG_SD_REMOVED "Card removed"
	#define MSG_MAIN "Main"
	#define MSG_AUTOSTART "Autostart"
	#define MSG_DISABLE_STEPPERS "Disable steppers"
	#define MSG_AUTO_HOME "Auto home"
	#define MSG_SET_HOME_OFFSETS "Set home offsets"
	#define MSG_SET_ORIGIN "Set origin"
	#define MSG_PREHEAT_PLA "Preheat PLA"
	#define MSG_PREHEAT_PLA0 "Preheat PLA 1"
	#define MSG_PREHEAT_PLA1 "Preheat PLA 2"
	#define MSG_PREHEAT_PLA2 "Preheat PLA 3"
	#define MSG_PREHEAT_PLA012 "Preheat PLA All"
	#define MSG_PREHEAT_PLA_BEDONLY "Preheat PLA Bed"
	#define MSG_PREHEAT_PLA_SETTINGS "Preheat PLA conf"
	#define MSG_PREHEAT_ABS "Preheat ABS"
	#define MSG_PREHEAT_ABS0 "Preheat ABS 1"
	#define MSG_PREHEAT_ABS1 "Preheat ABS 2"
	#define MSG_PREHEAT_ABS2 "Preheat ABS 3"
	#define MSG_PREHEAT_ABS012 "Preheat ABS All"
	#define MSG_PREHEAT_ABS_BEDONLY "Preheat ABS Bed"
	#define MSG_PREHEAT_ABS_SETTINGS "Preheat ABS conf"
	#define MSG_COOLDOWN "Cooldown"
	#define MSG_SWITCH_PS_ON "Switch power on"
	#define MSG_SWITCH_PS_OFF "Switch power off"
	#define MSG_EXTRUDE "Extrude"
	#define MSG_RETRACT "Retract"
	#define MSG_MOVE_AXIS "Move axis"
	#define MSG_MOVE_X "Move X"
	#define MSG_MOVE_Y "Move Y"
	#define MSG_MOVE_Z "Move Z"
	#define MSG_MOVE_E "Extruder"
	#define MSG_MOVE_E1 "Extruder2"
	#define MSG_MOVE_E2 "Extruder3"
	#define MSG_MOVE_01MM "Move 0.1mm"
	#define MSG_MOVE_1MM "Move 1mm"
	#define MSG_MOVE_10MM "Move 10mm"
	#define MSG_SPEED "Speed"
	#define MSG_NOZZLE "Nozzle"
	#define MSG_NOZZLE1 "Nozzle2"
	#define MSG_NOZZLE2 "Nozzle3"
	#define MSG_BED "Bed"
	#define MSG_FAN_SPEED "Fan speed"
	#define MSG_FLOW "Flow"
	#define MSG_FLOW0 "Flow 0"
	#define MSG_FLOW1 "Flow 1"
	#define MSG_FLOW2 "Flow 2"
	#define MSG_CONTROL "Control"
	#define MSG_MIN " \002 Min"
	#define MSG_MAX " \002 Max"
	#define MSG_FACTOR " \002 Fact"
	#define MSG_AUTOTEMP "Autotemp"
	#define MSG_ON "On "
	#define MSG_OFF "Off"
	#define MSG_PID_P "PID-P"
	#define MSG_PID_I "PID-I"
	#define MSG_PID_D "PID-D"
	#define MSG_PID_C "PID-C"
	#define MSG_ACC  "Accel"
	#define MSG_VXY_JERK "Vxy-jerk"
	#define MSG_VZ_JERK "Vz-jerk"
	#define MSG_VE_JERK "Ve-jerk"
	#define MSG_VMAX "Vmax "
	#define MSG_X "x"
	#define MSG_Y "y"
	#define MSG_Z "z"
	#define MSG_E "e"
	#define MSG_VMIN "Vmin"
	#define MSG_VTRAV_MIN "VTrav min"
	#define MSG_AMAX "Amax "
	#define MSG_A_RETRACT "A-retract"
	#define MSG_XSTEPS "Xsteps/mm"
	#define MSG_YSTEPS "Ysteps/mm"
	#define MSG_ZSTEPS "Zsteps/mm"
	#define MSG_ESTEPS "Esteps/mm"
	#define MSG_RECTRACT "Rectract"
	#define MSG_TEMPERATURE "Temperature"
	#define MSG_MOTION "Motion"
	#define MSG_CONTRAST "LCD contrast"
	#define MSG_STORE_EPROM "Store memory"
	#define MSG_LOAD_EPROM "Load memory"
	#define MSG_RESTORE_FAILSAFE "Restore failsafe"
	#define MSG_REFRESH "Refresh"
	#define MSG_WATCH "Info screen"
	#define MSG_PREPARE "Prepare"
	#define MSG_TUNE "Tune"
	#define MSG_PAUSE_PRINT "Pause print"
	#define MSG_RESUME_PRINT "Resume print"
	#define MSG_STOP_PRINT "Stop print"
	#define MSG_CARD_MENU "Print from SD"
	#define MSG_NO_CARD "No SD card"
	#define MSG_DWELL "Sleep..."
	#define MSG_USERWAIT "Wait for user..."
	#define MSG_RESUMING "Resuming print"
	#define MSG_NO_MOVE "No move."
	#define MSG_KILLED "KILLED. "
	#define MSG_STOPPED "STOPPED. "
	#define MSG_CONTROL_RETRACT  "Retract mm"
	#define MSG_CONTROL_RETRACT_SWAP  "Swap Re.mm"
	#define MSG_CONTROL_RETRACTF "Retract  V"
	#define MSG_CONTROL_RETRACT_ZLIFT "Hop mm"
	#define MSG_CONTROL_RETRACT_RECOVER "UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "S UnRet+mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "UnRet  V"
	#define MSG_AUTORETRACT "AutoRetr."
	#define MSG_FILAMENTCHANGE "Change filament"
	#define MSG_INIT_SDCARD "Init. SD card"
	#define MSG_CNG_SDCARD "Change SD card"
	#define MSG_ZPROBE_OUT "Z probe out. bed"
	#define MSG_POSITION_UNKNOWN "Home X/Y before Z"
	#define MSG_ZPROBE_ZOFFSET "Z Offset"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Endstop abort"

#endif


#if LANGUAGE_CHOICE == 2

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " gotowy."
	#define MSG_SD_INSERTED "Karta wlozona"
	#define MSG_SD_REMOVED "Karta usunieta"
	#define MSG_MAIN "Menu glowne"
	#define MSG_AUTOSTART "Autostart"
	#define MSG_DISABLE_STEPPERS "Wylacz silniki"
	#define MSG_AUTO_HOME "Auto. poz. zerowa"
	#define MSG_SET_HOME_OFFSETS "Set home offsets"
	#define MSG_SET_ORIGIN "Ustaw punkt zero"
	#define MSG_PREHEAT_PLA "Rozgrzej PLA"
	#define MSG_PREHEAT_PLA0 "Rozgrzej PLA 1"
	#define MSG_PREHEAT_PLA1 "Rozgrzej PLA 2"
	#define MSG_PREHEAT_PLA2 "Rozgrzej PLA 3"
	#define MSG_PREHEAT_PLA012 "Roz. PLA Wszystko"
	#define MSG_PREHEAT_PLA_BEDONLY "Rozgrzej PLA Loze"
	#define MSG_PREHEAT_PLA_SETTINGS "Ustaw. rozg. PLA"
	#define MSG_PREHEAT_ABS "Rozgrzej ABS"
	#define MSG_PREHEAT_ABS0 "Rozgrzej ABS 1"
	#define MSG_PREHEAT_ABS1 "Rozgrzej ABS 2"
	#define MSG_PREHEAT_ABS2 "Rozgrzej ABS 3"
	#define MSG_PREHEAT_ABS012 "Roz. ABS Wszystko"
	#define MSG_PREHEAT_ABS_BEDONLY "Rozgrzej ABS Loze"
	#define MSG_PREHEAT_ABS_SETTINGS "Ustaw. rozg. ABS"
	#define MSG_COOLDOWN "Chlodzenie"
	#define MSG_SWITCH_PS_ON "Wlacz zasilacz"
	#define MSG_SWITCH_PS_OFF "Wylacz zasilacz"
	#define MSG_EXTRUDE "Ekstruzja"
	#define MSG_RETRACT "Cofanie"
	#define MSG_MOVE_AXIS "Ruch osi"
	#define MSG_MOVE_X "Przesun w X"
	#define MSG_MOVE_Y "Przesun w Y"
	#define MSG_MOVE_Z "Przesun w Z"
	#define MSG_MOVE_E "Ekstruzja (os E)"
	#define MSG_MOVE_E1 "Extruder2"
	#define MSG_MOVE_E2 "Extruder3"
	#define MSG_MOVE_01MM "Przesuwaj co .1mm"
	#define MSG_MOVE_1MM "Przesuwaj co 1mm"
	#define MSG_MOVE_10MM "Przesuwaj co 10mm"
	#define MSG_SPEED "Predkosc"
	#define MSG_NOZZLE "Dysza"
	#define MSG_NOZZLE1 "Dysza 2"
	#define MSG_NOZZLE2 "Dysza 3"
	#define MSG_BED "Loze"
	#define MSG_FAN_SPEED "Obroty wiatraka"
	#define MSG_FLOW "Przeplyw"
	#define MSG_FLOW0 "Przeplyw 0"
	#define MSG_FLOW1 "Przeplyw 1"
	#define MSG_FLOW2 "Przeplyw 2"
	#define MSG_CONTROL "Kontrola"
	#define MSG_MIN " \002 Min"
	#define MSG_MAX " \002 Max"
	#define MSG_FACTOR " \002 Mnoznik"
	#define MSG_AUTOTEMP "Auto. temperatura"
	#define MSG_ON "Wl. "
	#define MSG_OFF "Wyl."
	#define MSG_PID_P "PID-P"
	#define MSG_PID_I "PID-I"
	#define MSG_PID_D "PID-D"
	#define MSG_PID_C "PID-C"
	#define MSG_ACC  "Przyspieszenie"
	#define MSG_VXY_JERK "Zryw Vxy"
	#define MSG_VZ_JERK "Zryw Vz"
	#define MSG_VE_JERK "Zryw Ve"
	#define MSG_VMAX "Vmax"
	#define MSG_X "x"
	#define MSG_Y "y"
	#define MSG_Z "z"
	#define MSG_E "e"
	#define MSG_VMIN "Vmin"
	#define MSG_VTRAV_MIN "Vskok min"
	#define MSG_AMAX "Amax"
	#define MSG_A_RETRACT "A-wycofanie"
	#define MSG_XSTEPS "krokiX/mm"
	#define MSG_YSTEPS "krokiY/mm"
	#define MSG_ZSTEPS "krokiZ/mm"
	#define MSG_ESTEPS "krokiE/mm"
	#define MSG_RECTRACT "Wycofanie"
	#define MSG_TEMPERATURE "Temperatura"
	#define MSG_MOTION "Ruch"
	#define MSG_CONTRAST "Kontrast LCD"
	#define MSG_STORE_EPROM "Zapisz w pamieci"
	#define MSG_LOAD_EPROM "Wczytaj z pamieci"
	#define MSG_RESTORE_FAILSAFE "Ustaw. fabryczne"
	#define MSG_REFRESH "\004Odswiez"
	#define MSG_WATCH "Ekran glowny"
	#define MSG_PREPARE "Przygotuj"
	#define MSG_CONTROL "Ustawienia"
	#define MSG_TUNE "Strojenie"
	#define MSG_PAUSE_PRINT "Pauza"
	#define MSG_RESUME_PRINT "Wznowienie"
	#define MSG_STOP_PRINT "Stop"
	#define MSG_CARD_MENU "Menu karty SD"
	#define MSG_NO_CARD "Brak karty"
	#define MSG_DWELL "Uspij..."
	#define MSG_USERWAIT "Oczekiwanie..."
	#define MSG_RESUMING "Wznawianie druku"
	#define MSG_NO_MOVE "Brak ruchu"
	#define MSG_KILLED "Ubity. "
	#define MSG_STOPPED "Zatrzymany. "
	#define MSG_STEPPER_RELEASED "Zwolniony."
	#define MSG_CONTROL_RETRACT  "Wycofaj mm"
	#define MSG_CONTROL_RETRACT_SWAP  "Z Wycof. mm"
	#define MSG_CONTROL_RETRACTF "Wycofaj  V"
	#define MSG_CONTROL_RETRACT_ZLIFT "Skok Z mm:"
	#define MSG_CONTROL_RETRACT_RECOVER "Cof. wycof. +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Z Cof. wyc. +mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "Cof. wycof.  V"
	#define MSG_AUTORETRACT "Auto. wycofanie"
	#define MSG_FILAMENTCHANGE "Zmien filament"
	#define MSG_INIT_SDCARD "Inicjal. karty SD"
	#define MSG_CNG_SDCARD "Zmiana karty SD"
	#define MSG_ZPROBE_OUT "Sonda Z za lozem"
	#define MSG_POSITION_UNKNOWN "Wroc w XY przed Z"
	#define MSG_ZPROBE_ZOFFSET "Offset Z"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Blad wyl. kranc."
	#define MSG_CONTRAST "Kontrast"

#endif


#if LANGUAGE_CHOICE == 3

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " prete."
	#define MSG_SD_INSERTED "Carte inseree"
	#define MSG_SD_REMOVED "Carte retiree"
	#define MSG_MAIN "Menu principal"
	#define MSG_AUTOSTART "Demarrage auto"
	#define MSG_DISABLE_STEPPERS "Arreter moteurs"
	#define MSG_AUTO_HOME "Home auto."
	#define MSG_SET_HOME_OFFSETS "Set home offsets"
	#define MSG_SET_ORIGIN "Regler origine"
	#define MSG_PREHEAT_PLA " Prechauffage PLA"
	#define MSG_PREHEAT_PLA0 "Prechauff. PLA 1"
    #define MSG_PREHEAT_PLA1 "Prechauff. PLA 2"
	#define MSG_PREHEAT_PLA2 "Prechauff. PLA 3"
	#define MSG_PREHEAT_PLA012 "Prech. PLA Tout"
	#define MSG_PREHEAT_PLA_BEDONLY "Prech. PLA Plateau"
	#define MSG_PREHEAT_PLA_SETTINGS "Regl. prech. PLA"
	#define MSG_PREHEAT_ABS "Prechauffage ABS"
	#define MSG_PREHEAT_ABS0 "Prechauff. ABS 1"
	#define MSG_PREHEAT_ABS1 "Prechauff. ABS 2"
	#define MSG_PREHEAT_ABS2 "Prechauff. ABS 3"
	#define MSG_PREHEAT_ABS012 "Prech. ABS Tout"
	#define MSG_PREHEAT_ABS_BEDONLY "Prech. ABS Plateau"
	#define MSG_PREHEAT_ABS_SETTINGS "Regl. prech. ABS"
	#define MSG_COOLDOWN "Refroidir"
	#define MSG_SWITCH_PS_ON "Allumer alim."
	#define MSG_SWITCH_PS_OFF "Eteindre alim."
	#define MSG_EXTRUDE "Extrusion"
	#define MSG_RETRACT "Retraction"
	#define MSG_PREHEAT_PLA "Prechauffage PLA"
	#define MSG_PREHEAT_ABS "Prechauffage ABS"
	#define MSG_MOVE_AXIS "Deplacer un axe"
	#define MSG_MOVE_X "Move X"
	#define MSG_MOVE_Y "Move Y"
	#define MSG_MOVE_Z "Move Z"
	#define MSG_MOVE_E "Extruder"
	#define MSG_MOVE_E1 "Extruder2"
	#define MSG_MOVE_E2 "Extruder3"
	#define MSG_MOVE_01MM "Move 0.1mm"
	#define MSG_MOVE_1MM "Move 1mm"
	#define MSG_MOVE_10MM "Move 10mm"
	#define MSG_SPEED " Vitesse"
	#define MSG_NOZZLE "Buse"
	#define MSG_NOZZLE1 "Buse2"
	#define MSG_NOZZLE2 "Buse3"
	#define MSG_BED "Plateau"
	#define MSG_FAN_SPEED "Vite. ventilateur"
	#define MSG_FLOW "Flux"
	#define MSG_FLOW0 "Flux 0"
	#define MSG_FLOW1 "Flux 1"
	#define MSG_FLOW2 "Flux 2"
	#define MSG_CONTROL "Controler"
	#define MSG_MIN " \002 Min"
	#define MSG_MAX " \002 Max"
	#define MSG_FACTOR " \002 Facteur"
	#define MSG_AUTOTEMP "Temp. Auto."
	#define MSG_ON "Marche "
	#define MSG_OFF "Arret"
	#define MSG_PID_P "PID-P"
	#define MSG_PID_I "PID-I"
	#define MSG_PID_D "PID-D"
	#define MSG_PID_C "PID-C"
	#define MSG_ACC "Accel"
	#define MSG_VXY_JERK "Vxy-jerk"
	#define MSG_VZ_JERK "Vz-jerk"
	#define MSG_VE_JERK "Ve-jerk"
	#define MSG_VMAX "Vmax"
	#define MSG_X "x"
	#define MSG_Y "y"
	#define MSG_Z "z"
	#define MSG_E "e"
	#define MSG_VMIN "Vmin"
	#define MSG_VTRAV_MIN "Vdepl min"
	#define MSG_AMAX "Amax "
	#define MSG_A_RETRACT "A-retract"
	#define MSG_XSTEPS "Xpas/mm"
	#define MSG_YSTEPS "Ypas/mm"
	#define MSG_ZSTEPS "Zpas/mm"
	#define MSG_ESTEPS "Epas/mm"
	#define MSG_TEMPERATURE "Temperature"
	#define MSG_MOTION "Mouvement"
	#define MSG_CONTRAST "Contraste LCD"
	#define MSG_STORE_EPROM "Sauver config"
	#define MSG_LOAD_EPROM "Lire config"
	#define MSG_RESTORE_FAILSAFE "Restaurer defauts"
	#define MSG_REFRESH "Actualiser"
	#define MSG_WATCH "Surveiller"
	#define MSG_PREPARE "Preparer"
	#define MSG_TUNE "Regler"
	#define MSG_PAUSE_PRINT "Interrompre impr."
	#define MSG_RESUME_PRINT "Reprendre impr."
	#define MSG_STOP_PRINT "Arreter impr."
	#define MSG_CARD_MENU "Impr. depuis SD"
	#define MSG_NO_CARD "Pas de carte"
	#define MSG_DWELL "Repos..."
	#define MSG_USERWAIT "Atten. de l'util."
	#define MSG_RESUMING "Repri. de l'impr."
	#define MSG_NO_MOVE "Aucun mouvement."
	#define MSG_KILLED "MORT."
	#define MSG_STOPPED "STOPPE."
	#define MSG_STEPPER_RELEASED "RELACHE."
	#define MSG_CONTROL_RETRACT "Retraction mm"
	#define MSG_CONTROL_RETRACT_SWAP "Ech. Retr. mm"
	#define MSG_CONTROL_RETRACTF "Retraction V"
	#define MSG_CONTROL_RETRACT_ZLIFT "Hop mm"
	#define MSG_CONTROL_RETRACT_RECOVER "UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Ech. UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "UnRet V"
	#define MSG_AUTORETRACT "Retract. Auto."
	#define MSG_FILAMENTCHANGE "Changer filament"
	#define MSG_INIT_SDCARD "Init. la carte SD"
	#define MSG_CNG_SDCARD "Changer de carte"
	#define MSG_ZPROBE_OUT "Z sonde exte. lit"
	#define MSG_POSITION_UNKNOWN "Rev. dans XY av.Z"
	#define MSG_ZPROBE_ZOFFSET "Offset Z"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Butee abandon"
	#define MSG_CONTRAST "Contrast"

#endif


#if LANGUAGE_CHOICE == 4

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " Bereit."

	#define MSG_SD_INSERTED      "SDKarte erkannt"
	#define MSG_SD_REMOVED       "SDKarte entfernt"
	#define MSG_MAIN             "Hauptmenü"
	#define MSG_AUTOSTART        "Autostart"
	#define MSG_DISABLE_STEPPERS "Stepper abschalt."
	#define MSG_AUTO_HOME        "Auto Nullpunkt"
	#define MSG_SET_HOME_OFFSETS "Set home offsets"
	#define MSG_SET_ORIGIN       "Setze Nullpunkt"
	#define MSG_PREHEAT_PLA      "Vorwärmen PLA"
	#define MSG_PREHEAT_PLA0     "Vorwärmen PLA 1"
	#define MSG_PREHEAT_PLA1     "Vorwärmen PLA 2"
	#define MSG_PREHEAT_PLA2     "Vorwärmen PLA 3"
	#define MSG_PREHEAT_PLA012   "Vorw. PLA Alle"
	#define MSG_PREHEAT_PLA_BEDONLY "Vorw. PLA Bett"
	#define MSG_PREHEAT_PLA_SETTINGS "Vorwärm. PLA Ein."
	#define MSG_PREHEAT_ABS      "Vorwärmen ABS"
	#define MSG_PREHEAT_ABS0     "Vorwärmen ABS 1"
	#define MSG_PREHEAT_ABS1     "Vorwärmen ABS 2"
	#define MSG_PREHEAT_ABS2     "Vorwärmen ABS 3"
	#define MSG_PREHEAT_ABS012   "Vorw. ABS Alle"
	#define MSG_PREHEAT_ABS_BEDONLY "Vorw. ABS Bett"
	#define MSG_PREHEAT_ABS_SETTINGS "Vorwärm. ABS Ein."
	#define MSG_COOLDOWN         "Abkühlen"
	#define MSG_SWITCH_PS_ON     "Switch Power On"
	#define MSG_SWITCH_PS_OFF    "Switch Power Off"
	#define MSG_EXTRUDE          "Extrude"
	#define MSG_RETRACT          "Retract"
	#define MSG_MOVE_AXIS        "Achsen bewegen"
	#define MSG_MOVE_X           "X bewegen"
	#define MSG_MOVE_Y           "Y bewegen"
	#define MSG_MOVE_Z           "Z bewegen"
	#define MSG_MOVE_E           "Extruder"
	#define MSG_MOVE_E1 		 "Extruder2"
	#define MSG_MOVE_E2 		 "Extruder3"
	#define MSG_MOVE_01MM        "0.1mm bewegen"
	#define MSG_MOVE_1MM         "1mm bewegen"
	#define MSG_MOVE_10MM        "10mm bewegen"
	#define MSG_SPEED            "Geschw"
	#define MSG_NOZZLE           "Düse"
	#define MSG_NOZZLE1          "Düse2"
	#define MSG_NOZZLE2          "Düse3"
	#define MSG_BED              "Bett"
	#define MSG_FAN_SPEED        "Lüftergeschw."
	#define MSG_FLOW             "Fluss"
	#define MSG_FLOW0            "Fluss 0"
	#define MSG_FLOW1            "Fluss 1"
	#define MSG_FLOW2            "Fluss 2"
	#define MSG_CONTROL          "Einstellungen"
	#define MSG_MIN              "\002 Min"
	#define MSG_MAX              "\002 Max"
	#define MSG_FACTOR           "\002 Faktor"
	#define MSG_AUTOTEMP         "AutoTemp"
	#define MSG_ON               "Ein"
	#define MSG_OFF              "Aus"
	#define MSG_PID_P            "PID-P"
	#define MSG_PID_I            "PID-I"
	#define MSG_PID_D            "PID-D"
	#define MSG_PID_C            "PID-C"
	#define MSG_ACC              "Acc"
	#define MSG_VXY_JERK         "Vxy-jerk"
	#define MSG_VZ_JERK          "Vz-jerk"
	#define MSG_VE_JERK          "Ve-jerk"
	#define MSG_VMAX             "Vmax "
	#define MSG_X                "x"
	#define MSG_Y                "y"
	#define MSG_Z                "z"
	#define MSG_E                "e"
	#define MSG_VMIN             "Vmin"
	#define MSG_VTRAV_MIN        "VTrav min"
	#define MSG_AMAX             "Amax "
	#define MSG_A_RETRACT        "A-Retract"
	#define MSG_XSTEPS           "Xsteps/mm"
	#define MSG_YSTEPS           "Ysteps/mm"
	#define MSG_ZSTEPS           "Zsteps/mm"
	#define MSG_ESTEPS           "Esteps/mm"
	#define MSG_RECTRACT_WIDE    "Rectract"
	#define MSG_WATCH            "Beobachten"
	#define MSG_TEMPERATURE      "Temperatur"
	#define MSG_MOTION           "Bewegung"
	#define MSG_CONTRAST "LCD contrast"
	#define MSG_STORE_EPROM      "EPROM speichern"
	#define MSG_LOAD_EPROM       "EPROM laden"
	#define MSG_RESTORE_FAILSAFE "Standardkonfig."
	#define MSG_REFRESH          "Aktualisieren"
	#define MSG_PREPARE          "Vorbereitung"
	#define MSG_CONTROL          "Einstellungen"
	#define MSG_TUNE             "Justierung"
	#define MSG_PAUSE_PRINT      "Druck anhalten"
	#define MSG_RESUME_PRINT     "Druck fortsetz"
	#define MSG_STOP_PRINT       "Druck stoppen"
	#define MSG_CARD_MENU        "SDKarten Menü"
	#define MSG_NO_CARD          "Keine SDKarte"
	#define MSG_DWELL            "Warten..."
	#define MSG_USERWAIT         "Warte auf Nutzer"
	#define MSG_RESUMING         "Druck fortsetzung"
	#define MSG_NO_MOVE          "Kein Zug."
	#define MSG_KILLED           "KILLED"
	#define MSG_STOPPED          "GESTOPPT"
	#define MSG_STEPPER_RELEASED "Stepper frei"
	#define MSG_CONTROL_RETRACT  "Retract mm"
	#define MSG_CONTROL_RETRACT_SWAP  "Wechs. Retract mm"
	#define MSG_CONTROL_RETRACTF "Retract  V"
	#define MSG_CONTROL_RETRACT_ZLIFT "Hop mm"
	#define MSG_CONTROL_RETRACT_RECOVER "UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Wechs. UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "UnRet  V"
	#define MSG_AUTORETRACT      "AutoRetr."
	#define MSG_FILAMENTCHANGE "Filament wechseln"
	#define MSG_INIT_SDCARD "Init. SD-Card"
	#define MSG_CNG_SDCARD "Change SD-Card"
	#define MSG_ZPROBE_OUT "Z probe out. bed"
	#define MSG_POSITION_UNKNOWN "Home X/Y before Z"
	#define MSG_ZPROBE_ZOFFSET "Z Offset"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Endstop abort"
	#define MSG_CONTRAST "Contrast"

#endif


#if LANGUAGE_CHOICE == 5

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " lista."
	#define MSG_SD_INSERTED "Tarjeta colocada"
	#define MSG_SD_REMOVED "Tarjeta retirada"
	#define MSG_MAIN "Menu principal"
	#define MSG_AUTOSTART " Autostart"
	#define MSG_DISABLE_STEPPERS "Apagar motores"
	#define MSG_AUTO_HOME "Llevar al origen"
	#define MSG_SET_HOME_OFFSETS "Set home offsets"
	#define MSG_SET_ORIGIN "Establecer cero"
	#define MSG_PREHEAT_PLA "Precalentar PLA"
	#define MSG_PREHEAT_PLA0 "Precalentar PLA 1"
	#define MSG_PREHEAT_PLA1 "Precalentar PLA 2"
	#define MSG_PREHEAT_PLA2 "Precalentar PLA 3"
	#define MSG_PREHEAT_PLA012 "Precal. PLA Todo"
	#define MSG_PREHEAT_PLA_BEDONLY "Precal. PLA Base"
	#define MSG_PREHEAT_PLA_SETTINGS "Ajustar temp. PLA"
	#define MSG_PREHEAT_ABS "Precalentar ABS"
	#define MSG_PREHEAT_ABS0 "Precalentar ABS 1"
	#define MSG_PREHEAT_ABS1 "Precalentar ABS 2"
	#define MSG_PREHEAT_ABS2 "Precalentar ABS 3"
	#define MSG_PREHEAT_ABS012 "Precal. ABS Todo"
	#define MSG_PREHEAT_ABS_BEDONLY "Precal. ABS Base"
	#define MSG_PREHEAT_ABS_SETTINGS "Ajustar temp. ABS"
	#define MSG_COOLDOWN "Enfriar"
	#define MSG_SWITCH_PS_ON "Switch Power On"
	#define MSG_SWITCH_PS_OFF "Switch Power Off"
	#define MSG_EXTRUDE "Extruir"
	#define MSG_RETRACT "Retraer"
	#define MSG_MOVE_AXIS "Mover ejes"
	#define MSG_MOVE_X "Mover X"
	#define MSG_MOVE_Y "Mover Y"
	#define MSG_MOVE_Z "Mover Z"
	#define MSG_MOVE_E "Extrusor"
	#define MSG_MOVE_E1 "Extrusor2"
	#define MSG_MOVE_E2 "Extrusor3"
	#define MSG_MOVE_01MM "Mover 0.1mm"
	#define MSG_MOVE_1MM "Mover 1mm"
	#define MSG_MOVE_10MM "Mover 10mm"
	#define MSG_SPEED "Velocidad"
	#define MSG_NOZZLE "Nozzle"
	#define MSG_NOZZLE1 "Nozzle2"
	#define MSG_NOZZLE2 "Nozzle3"
	#define MSG_BED "Base"
	#define MSG_FAN_SPEED "Ventilador"
	#define MSG_FLOW "Flujo"
	#define MSG_FLOW0 "Flujo 0"
	#define MSG_FLOW1 "Flujo 1"
	#define MSG_FLOW2 "Flujo 2"
	#define MSG_CONTROL "Control"
	#define MSG_MIN "\002 Min"
	#define MSG_MAX "\002 Max"
	#define MSG_FACTOR "\002 Fact"
	#define MSG_AUTOTEMP "Autotemp"
	#define MSG_ON "On"
	#define MSG_OFF "Off"
	#define MSG_PID_P "PID-P"
	#define MSG_PID_I "PID-I"
	#define MSG_PID_D "PID-D"
	#define MSG_PID_C "PID-C"
	#define MSG_ACC  "Acel"
	#define MSG_VXY_JERK "Vxy-jerk"
	#define MSG_VZ_JERK "Vz-jerk"
	#define MSG_VE_JERK "Ve-jerk"
	#define MSG_VMAX "Vmax"
	#define MSG_X "x"
	#define MSG_Y "y"
	#define MSG_Z "z"
	#define MSG_E "e"
	#define MSG_VMIN "Vmin"
	#define MSG_VTRAV_MIN "VTrav min"
	#define MSG_AMAX "Amax"
	#define MSG_A_RETRACT "A-retrac."
	#define MSG_XSTEPS "X pasos/mm"
	#define MSG_YSTEPS "Y pasos/mm"
	#define MSG_ZSTEPS "Z pasos/mm"
	#define MSG_ESTEPS "E pasos/mm"
	#define MSG_RECTRACT "Retraer"
	#define MSG_TEMPERATURE "Temperatura"
	#define MSG_MOTION "Movimiento"
	#define MSG_STORE_EPROM "Guardar memoria"
	#define MSG_LOAD_EPROM "Cargar memoria"
	#define MSG_RESTORE_FAILSAFE "Rest. de emergen."
	#define MSG_REFRESH "Volver a cargar"
	#define MSG_WATCH "Monitorizar"
	#define MSG_PREPARE "Preparar"
	#define MSG_TUNE "Ajustar"
	#define MSG_PAUSE_PRINT "Pausar impresion"
	#define MSG_RESUME_PRINT "Reanudar impres."
	#define MSG_STOP_PRINT "Detener impresion"
	#define MSG_CARD_MENU "Menu de SD"
	#define MSG_NO_CARD "No hay tarjeta SD"
	#define MSG_DWELL "Reposo..."
	#define MSG_USERWAIT "Esperando ordenes"
	#define MSG_RESUMING "Resumiendo impre."
	#define MSG_NO_MOVE "Sin movimiento"
	#define MSG_KILLED "PARADA DE EMERG."
	#define MSG_STOPPED "PARADA"
	#define MSG_CONTROL_RETRACT  "Retraer mm"
	#define MSG_CONTROL_RETRACT_SWAP  "Interc. Retraer mm"
	#define MSG_CONTROL_RETRACTF "Retraer  V"
	#define MSG_CONTROL_RETRACT_ZLIFT "Levantar mm"
	#define MSG_CONTROL_RETRACT_RECOVER "DesRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Interc. DesRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "DesRet V"
	#define MSG_AUTORETRACT "AutoRetr."
	#define MSG_FILAMENTCHANGE "Cambiar filamento"
	#define MSG_INIT_SDCARD "Iniciando tarjeta"
	#define MSG_CNG_SDCARD "Cambiar tarjeta"
	#define MSG_RECTRACT_WIDE "Retraer"
	#define MSG_TEMPERATURE_WIDE "Temperatura"
	#define MSG_TEMPERATURE_RTN  "Temperatura"
	#define MSG_MAIN_WIDE "Menu principal"
	#define MSG_MOTION_WIDE "Movimiento"
	#define MSG_PREPARE_ALT "Preparar"
	#define MSG_CONTROL_ARROW "Control"
	#define MSG_RETRACT_ARROW "Retraer"
	#define MSG_STEPPER_RELEASED "Desacoplada."
	#define MSG_ZPROBE_OUT "Z probe out. bed"
	#define MSG_POSITION_UNKNOWN "Home X/Y before Z"
	#define MSG_ZPROBE_ZOFFSET "Z Offset"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Endstop abort"
	#define MSG_CONTRAST "Contrast"

#endif

#if LANGUAGE_CHOICE == 6


// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME			        "Готов."
	#define MSG_SD_INSERTED						"Карта вставлена"
	#define MSG_SD_REMOVED						"Карта извлечена"
	#define MSG_MAIN							"Меню \003"
	#define MSG_AUTOSTART						"Автостарт"
	#define MSG_DISABLE_STEPPERS 				"Выкл. двигатели"
	#define MSG_AUTO_HOME						"Парковка"
	#define MSG_SET_HOME_OFFSETS				"Set home offsets"
	#define MSG_SET_ORIGIN						"Запомнить ноль"
	#define MSG_PREHEAT_PLA 					"Преднагрев PLA"
	#define MSG_PREHEAT_PLA0					"Преднагрев PLA0"
	#define MSG_PREHEAT_PLA1					"Преднагрев PLA1"
	#define MSG_PREHEAT_PLA2					"Преднагрев PLA2"
	#define MSG_PREHEAT_PLA012 					"Преднаг. PLA все"
	#define MSG_PREHEAT_PLA_BEDONLY 			"Пред. PLA Кровать"
	#define MSG_PREHEAT_PLA_SETTINGS  			"Настройки PLA"
	#define MSG_PREHEAT_ABS						"Преднагрев ABS"
	#define MSG_PREHEAT_ABS0					"Преднагрев ABS0"
	#define MSG_PREHEAT_ABS1					"Преднагрев ABS1"
	#define MSG_PREHEAT_ABS2					"Преднагрев ABS2"
	#define MSG_PREHEAT_ABS012 					"Преднаг. ABS все "
	#define MSG_PREHEAT_ABS_BEDONLY 			"Пред. ABS Кровать"
	#define MSG_PREHEAT_ABS_SETTINGS  			"Настройки ABS"
	#define MSG_COOLDOWN						"Охлаждение"
	#define MSG_SWITCH_PS_ON					"Switch Power On"
	#define MSG_SWITCH_PS_OFF					"Switch Power Off"
	#define MSG_EXTRUDE							"Экструзия"
	#define MSG_RETRACT							"Откат"
	#define MSG_MOVE_AXIS  						"Движение по осям"
	#define MSG_MOVE_X                          "Move X"
	#define MSG_MOVE_Y                          "Move Y"
	#define MSG_MOVE_Z                          "Move Z"
	#define MSG_MOVE_E                          "Extruder"
	#define MSG_MOVE_E1 						"Extruder2"
	#define MSG_MOVE_E2 						"Extruder3"
	#define MSG_MOVE_01MM                       "Move 0.1mm"
	#define MSG_MOVE_1MM                        "Move 1mm"
	#define MSG_MOVE_10MM                       "Move 10mm"
	#define MSG_SPEED							"Скорость:"
	#define MSG_NOZZLE							"\002 Фильера:"
	#define MSG_NOZZLE1							"\002 Фильера2:"
	#define MSG_NOZZLE2							"\002 Фильера3:"
	#define MSG_BED								"\002 Кровать:"
	#define MSG_FAN_SPEED						"Куллер:"
	#define MSG_FLOW							"Поток:"
	#define MSG_FLOW0 " Поток0:"
	#define MSG_FLOW1 " Поток1:"
	#define MSG_FLOW2 " Поток2:"
	#define MSG_CONTROL							"Настройки \003"
	#define MSG_MIN								"\002 Минимум:"
	#define MSG_MAX								"\002 Максимум:"
	#define MSG_FACTOR							"\002 Фактор:"
	#define MSG_AUTOTEMP						"Autotemp:"
	#define MSG_ON								"Вкл. "
	#define MSG_OFF								"Выкл. "
	#define MSG_PID_P							"PID-P: "
	#define MSG_PID_I							"PID-I: "
	#define MSG_PID_D							"PID-D: "
	#define MSG_PID_C							"PID-C: "
	#define MSG_ACC								"Acc:"
	#define MSG_VXY_JERK						"Vxy-jerk: "
	#define MSG_VZ_JERK                         "Vz-jerk"
	#define MSG_VE_JERK                         "Ve-jerk"
	#define MSG_VMAX							"Vmax "
	#define MSG_X								"x:"
	#define MSG_Y								"y:"
	#define MSG_Z								"z:"
	#define MSG_E								"e:"
	#define MSG_VMIN							"Vmin:"
	#define MSG_VTRAV_MIN						"VTrav min:"
	#define MSG_AMAX							"Amax "
	#define MSG_A_RETRACT						"A-retract:"
	#define MSG_XSTEPS							"X шаг/mm:"
	#define MSG_YSTEPS							"Y шаг/mm:"
	#define MSG_ZSTEPS							"Z шаг/mm:"
	#define MSG_ESTEPS							"E шаг/mm:"
	#define MSG_RECTRACT    					"Откат подачи    \x7E"
	#define MSG_TEMPERATURE  					"Температура     \x7E"
	#define MSG_MOTION							"Скорости        \x7E"
	#define MSG_CONTRAST  						"LCD contrast"
	#define MSG_STORE_EPROM  					"Сохранить в EPROM"
	#define MSG_LOAD_EPROM  					"Загруз. из EPROM"
	#define MSG_RESTORE_FAILSAFE				"Сброс настроек"
	#define MSG_REFRESH							"\004Обновить"
	#define MSG_WATCH							"Обзор           \003"
	#define MSG_PREPARE							"Действия        \x7E"
	#define MSG_TUNE							"Настройки       \x7E"
	#define MSG_PAUSE_PRINT  					"Продолжить печать"
	#define MSG_RESUME_PRINT					"возобн. печать"
	#define MSG_STOP_PRINT 						"Остановить печать"
	#define MSG_CARD_MENU						"Меню карты      \x7E"
	#define MSG_NO_CARD							"Нет карты"
	#define MSG_DWELL							"Сон..."
	#define MSG_USERWAIT  						"Ожиданиие"
	#define MSG_RESUMING 						"Resuming print"
	#define MSG_NO_MOVE							"Нет движения."
	#define MSG_KILLED							"УБИТО."
	#define MSG_STOPPED							"ОСТАНОВЛЕНО."
	#define MSG_CONTROL_RETRACT					"Откат mm:"
	#define MSG_CONTROL_RETRACT_SWAP			"своп Откат mm:"
	#define MSG_CONTROL_RETRACTF				"Откат  V:"
	#define MSG_CONTROL_RETRACT_ZLIFT			"Прыжок mm:"
	#define MSG_CONTROL_RETRACT_RECOVER			"Возврат +mm:"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP	"своп Возврат +mm:"
	#define MSG_CONTROL_RETRACT_RECOVERF		"Возврат  V:"
	#define MSG_AUTORETRACT						"АвтоОткат:"
	#define MSG_FILAMENTCHANGE 					"Change filament"
	#define MSG_INIT_SDCARD 					"Init. SD-Card"
	#define MSG_CNG_SDCARD 						"Change SD-Card"
	#define MSG_ZPROBE_OUT 						"Z probe out. bed"
	#define MSG_POSITION_UNKNOWN 				"Home X/Y before Z"
	#define MSG_ZPROBE_ZOFFSET 					"Z Offset"
	#define MSG_BABYSTEP_X 						"Babystep X"
	#define MSG_BABYSTEP_Y 						"Babystep Y"
	#define MSG_BABYSTEP_Z 						"Babystep Z"
	#define MSG_ENDSTOP_ABORT 					"Endstop abort"
	#define MSG_CONTRAST 						"Contrast"

#endif


#if LANGUAGE_CHOICE == 7

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " pronto."
	#define MSG_SD_INSERTED          "SD Card inserita"
	#define MSG_SD_REMOVED           "SD Card rimossa"
	#define MSG_MAIN                 "Menu principale"
	#define MSG_AUTOSTART            "Autostart"
	#define MSG_DISABLE_STEPPERS     "Disabilita Motori"
	#define MSG_AUTO_HOME            "Auto Home"
	#define MSG_SET_HOME_OFFSETS     "Set home offsets"
	#define MSG_SET_ORIGIN           "Imposta Origine"
	#define MSG_PREHEAT_PLA          "Preriscalda PLA"
	#define MSG_PREHEAT_PLA0         "Preriscalda PLA 1"
	#define MSG_PREHEAT_PLA1         "Preriscalda PLA 2"
	#define MSG_PREHEAT_PLA2         "Preriscalda PLA 3"
	#define MSG_PREHEAT_PLA012       "Preris. PLA Tutto"
	#define MSG_PREHEAT_PLA_BEDONLY  "Preri. PLA Piatto"
	#define MSG_PREHEAT_PLA_SETTINGS "Preris. PLA Conf"
	#define MSG_PREHEAT_ABS          "Preriscalda ABS"
	#define MSG_PREHEAT_ABS0         "Preriscalda ABS 1"
	#define MSG_PREHEAT_ABS1         "Preriscalda ABS 2"
	#define MSG_PREHEAT_ABS2         "Preriscalda ABS 3"
	#define MSG_PREHEAT_ABS012       "Preris. ABS Tutto"
	#define MSG_PREHEAT_ABS_BEDONLY  "Preri. ABS Piatto"
	#define MSG_PREHEAT_ABS_SETTINGS "Preris. ABS Conf"
	#define MSG_COOLDOWN             "Raffredda"
	#define MSG_SWITCH_PS_ON         "Switch Power On"
	#define MSG_SWITCH_PS_OFF        "Switch Power Off"
	#define MSG_EXTRUDE              "Estrudi"
	#define MSG_RETRACT              "Ritrai"
	#define MSG_MOVE_AXIS            "Muovi Asse"
	#define MSG_MOVE_X               "Move X"
	#define MSG_MOVE_Y               "Move Y"
	#define MSG_MOVE_Z               "Move Z"
	#define MSG_MOVE_E               "Extruder"
	#define MSG_MOVE_E1 			 "Extruder2"
	#define MSG_MOVE_E2 			 "Extruder3"
	#define MSG_MOVE_01MM            "Move 0.1mm"
	#define MSG_MOVE_1MM             "Move 1mm"
	#define MSG_MOVE_10MM            "Move 10mm"
	#define MSG_SPEED                "Velcità"
	#define MSG_NOZZLE               "Ugello"
	#define MSG_NOZZLE1              "Ugello2"
	#define MSG_NOZZLE2              "Ugello3"
	#define MSG_BED                  "Piatto"
	#define MSG_FAN_SPEED            "Ventola"
	#define MSG_FLOW                 "Flusso"
	#define MSG_FLOW0                "Flusso 0"
	#define MSG_FLOW1                "Flusso 1"
	#define MSG_FLOW2                "Flusso 2"
	#define MSG_CONTROL              "Controllo"
	#define MSG_MIN                  " \002 Min:"
	#define MSG_MAX                  " \002 Max:"
	#define MSG_FACTOR               " \002 Fact:"
	#define MSG_AUTOTEMP             "Autotemp"
	#define MSG_ON                   "On "
	#define MSG_OFF                  "Off"
	#define MSG_PID_P                "PID-P"
	#define MSG_PID_I                "PID-I"
	#define MSG_PID_D                "PID-D"
	#define MSG_PID_C                "PID-C"
	#define MSG_ACC                  "Accel"
	#define MSG_VXY_JERK             "Vxy-jerk"
	#define MSG_VZ_JERK              "Vz-jerk"
	#define MSG_VE_JERK              "Ve-jerk"
	#define MSG_VMAX                 "Vmax"
	#define MSG_X                    "x"
	#define MSG_Y                    "y"
	#define MSG_Z                    "z"
	#define MSG_E                    "e"
	#define MSG_VMIN                 "Vmin"
	#define MSG_VTRAV_MIN            "VTrav min"
	#define MSG_AMAX                 "Amax"
	#define MSG_A_RETRACT            "A-retract"
	#define MSG_XSTEPS               "Xpassi/mm"
	#define MSG_YSTEPS               "Ypassi/mm"
	#define MSG_ZSTEPS               "Zpassi/mm"
	#define MSG_ESTEPS               "Epassi/mm"
	#define MSG_RECTRACT             "Ritrai"
	#define MSG_TEMPERATURE          "Temperatura"
	#define MSG_MOTION               "Movimento"
	#define MSG_CONTRAST "LCD contrast"
	#define MSG_STORE_EPROM          "Salva in EEPROM"
	#define MSG_LOAD_EPROM           "Carica da EEPROM"
	#define MSG_RESTORE_FAILSAFE     "Impostaz. default"
	#define MSG_REFRESH              "Aggiorna"
	#define MSG_WATCH                "Guarda"
	#define MSG_PREPARE              "Prepara"
	#define MSG_TUNE                 "Adatta"
	#define MSG_PAUSE_PRINT          "Pausa"
	#define MSG_RESUME_PRINT         "Riprendi Stampa"
	#define MSG_STOP_PRINT           "Arresta Stampa"
	#define MSG_CARD_MENU            "SD Card Menu"
	#define MSG_NO_CARD              "No SD Card"
	#define MSG_DWELL                "Sospensione..."
	#define MSG_USERWAIT             "Attendi Utente..."
	#define MSG_RESUMING             "Riprendi Stampa"
	#define MSG_NO_MOVE              "Nessun Movimento."
	#define MSG_KILLED               "UCCISO. "
	#define MSG_STOPPED              "ARRESTATO. "
	#define MSG_CONTROL_RETRACT      "Ritrai mm"
	#define MSG_CONTROL_RETRACT_SWAP "Scamb. Ritrai mm"
	#define MSG_CONTROL_RETRACTF     "Ritrai  V"
	#define MSG_CONTROL_RETRACT_ZLIFT "Salta mm"
	#define MSG_CONTROL_RETRACT_RECOVER "UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Scamb. UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "UnRet  V"
	#define MSG_AUTORETRACT          "AutoArretramento"
	#define MSG_FILAMENTCHANGE       "Cambia filamento"
	#define MSG_INIT_SDCARD          "Iniz. SD-Card"
	#define MSG_CNG_SDCARD           "Cambia SD-Card"
	#define MSG_ZPROBE_OUT "Z probe out. bed"
	#define MSG_POSITION_UNKNOWN "Home X/Y before Z"
	#define MSG_ZPROBE_ZOFFSET "Z Offset"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Endstop abort"
	#define MSG_CONTRAST "Contrast"

#endif


#if LANGUAGE_CHOICE == 8

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " pronto."
	#define MSG_SD_INSERTED "Cartao inserido"
	#define MSG_SD_REMOVED "Cartao removido"
	#define MSG_MAIN " Menu principal \003"
	#define MSG_AUTOSTART "Autostart"
	#define MSG_DISABLE_STEPPERS " Apagar motores"
	#define MSG_AUTO_HOME "Ir para origen"
	#define MSG_SET_HOME_OFFSETS "Set home offsets"
	#define MSG_SET_ORIGIN "Estabelecer orig."
	#define MSG_PREHEAT_PLA "Pre-aquecer PLA"
	#define MSG_PREHEAT_PLA0 " pre-aquecer PLA 1"
	#define MSG_PREHEAT_PLA1 " pre-aquecer PLA 2"
	#define MSG_PREHEAT_PLA2 " pre-aquecer PLA 3"
	#define MSG_PREHEAT_PLA012 " pre-aq. PLA Tudo"
	#define MSG_PREHEAT_PLA_BEDONLY  " pre-aq. PLA \002Base"
	#define MSG_PREHEAT_PLA_SETTINGS "PLA setting"
	#define MSG_PREHEAT_ABS "Pre-aquecer ABS"
	#define MSG_PREHEAT_ABS0 " pre-aquecer ABS 1"
	#define MSG_PREHEAT_ABS1 " pre-aquecer ABS 2"
	#define MSG_PREHEAT_ABS2 " pre-aquecer ABS 3"
	#define MSG_PREHEAT_ABS012 " pre-aq. ABS Tudo"
	#define MSG_PREHEAT_ABS_BEDONLY  " pre-aq. ABS \002Base"
	#define MSG_PREHEAT_ABS_SETTINGS "ABS setting"
	#define MSG_COOLDOWN "Esfriar"
	#define MSG_SWITCH_PS_ON "Switch Power On"
	#define MSG_SWITCH_PS_OFF "Switch Power Off"
	#define MSG_EXTRUDE "Extrudar"
	#define MSG_RETRACT "Retrair"
	#define MSG_PREHEAT_PLA "Pre-aquecer PLA"
	#define MSG_PREHEAT_ABS "Pre-aquecer ABS"
	#define MSG_MOVE_AXIS "Mover eixo      \x7E"
	#define MSG_MOVE_X "Move X"
	#define MSG_MOVE_Y "Move Y"
	#define MSG_MOVE_Z "Move Z"
	#define MSG_MOVE_E "Extruder"
	#define MSG_MOVE_E1 "Extruder2"
	#define MSG_MOVE_E2 "Extruder3"
	#define MSG_MOVE_01MM "Move 0.1mm"
	#define MSG_MOVE_1MM "Move 1mm"
	#define MSG_MOVE_10MM "Move 10mm"
	#define MSG_SPEED "Velocidade:"
	#define MSG_NOZZLE "\002Nozzle:"
	#define MSG_NOZZLE1 "\002Nozzle2:"
	#define MSG_NOZZLE2 "\002Nozzle3:"
	#define MSG_BED "\002Base:"
	#define MSG_FAN_SPEED "Velocidade vento."
	#define MSG_FLOW "Fluxo:"
	#define MSG_FLOW0 "Fluxo0:"
	#define MSG_FLOW1 "Fluxo1:"
	#define MSG_FLOW2 "Fluxo2:"
	#define MSG_CONTROL "Controle \003"
	#define MSG_MIN "\002 Min:"
	#define MSG_MAX "\002 Max:"
	#define MSG_FACTOR "\002 Fact:"
	#define MSG_AUTOTEMP "Autotemp:"
	#define MSG_ON "On "
	#define MSG_OFF "Off"
	#define MSG_PID_P "PID-P: "
	#define MSG_PID_I "PID-I: "
	#define MSG_PID_D "PID-D: "
	#define MSG_PID_C "PID-C: "
	#define MSG_ACC  "Acc:"
	#define MSG_VXY_JERK "Vxy-jerk: "
	#define MSG_VZ_JERK "Vz-jerk"
	#define MSG_VE_JERK "Ve-jerk"
	#define MSG_VMAX " Vmax "
	#define MSG_X "x:"
	#define MSG_Y "y:"
	#define MSG_Z "z:"
	#define MSG_E "e:"
	#define MSG_VMIN "Vmin:"
	#define MSG_VTRAV_MIN "VTrav min:"
	#define MSG_AMAX "Amax "
	#define MSG_A_RETRACT "A-retract:"
	#define MSG_XSTEPS "Xpasso/mm:"
	#define MSG_YSTEPS "Ypasso/mm:"
	#define MSG_ZSTEPS "Zpasso/mm:"
	#define MSG_ESTEPS "Epasso/mm:"
	#define MSG_MAIN_WIDE "Menu Principal  \003"
	#define MSG_RECTRACT "Retrair"
	#define MSG_TEMPERATURE "Temperatura"
	#define MSG_MOTION "Movimento"
	#define MSG_STORE_EPROM "Guardar memoria"
	#define MSG_LOAD_EPROM "Carregar memoria"
	#define MSG_RESTORE_FAILSAFE "Rest. de emergen."
	#define MSG_REFRESH "\004Recarregar"
	#define MSG_WATCH "Monitorar   \003"
	#define MSG_PREPARE "Preparar \x7E"
	#define MSG_PREPARE_ALT "Preparar \003"
	#define MSG_CONTROL_ARROW "Controle \x7E"
	#define MSG_RETRACT_ARROW "Retrair \x7E"
	#define MSG_TUNE "Tune    \x7E"
	#define MSG_PAUSE_PRINT "Pausar impressao"
	#define MSG_RESUME_PRINT "Resumir impressao"
	#define MSG_STOP_PRINT "Parar impressao"
	#define MSG_CARD_MENU "Menu cartao SD"
	#define MSG_NO_CARD "Sem cartao SD"
	#define MSG_DWELL "Repouso..."
	#define MSG_USERWAIT "Esperando ordem"
	#define MSG_RESUMING "Resuming print"
	#define MSG_NO_MOVE "Sem movimento"
	#define MSG_KILLED "PARADA DE EMERG."
	#define MSG_STOPPED "PARADA. "
	#define MSG_STEPPER_RELEASED "Lancado."
	#define MSG_CONTROL_RETRACT  " Retrair mm:"
	#define MSG_CONTROL_RETRACT_SWAP  "Troca Retrair mm:"
	#define MSG_CONTROL_RETRACTF " Retrair  V:"
	#define MSG_CONTROL_RETRACT_ZLIFT " Levantar mm:"
	#define MSG_CONTROL_RETRACT_RECOVER " DesRet +mm:"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Troca DesRet +mm:"
	#define MSG_CONTROL_RETRACT_RECOVERF " DesRet  V:"
	#define MSG_AUTORETRACT " AutoRetr.:"
	#define MSG_FILAMENTCHANGE "Change filament"
	#define MSG_INIT_SDCARD "Init. SD-Card"
	#define MSG_CNG_SDCARD "Change SD-Card"
	#define MSG_ZPROBE_OUT "Son. fora da mesa"
	#define MSG_POSITION_UNKNOWN "XY antes de Z"
	#define MSG_ZPROBE_ZOFFSET "Z Offset"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Endstop abort"
	#define MSG_CONTRAST "Contrast"

#endif



#if LANGUAGE_CHOICE == 9

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " valmis."
	#define MSG_SD_INSERTED "Kortti asetettu"
	#define MSG_SD_REMOVED "Kortti poistettu"
	#define MSG_MAIN "Palaa"
	#define MSG_AUTOSTART "Automaatti"
	#define MSG_DISABLE_STEPPERS "Vapauta moottorit"
	#define MSG_AUTO_HOME "Aja referenssiin"
	#define MSG_SET_HOME_OFFSETS "Set home offsets"
	#define MSG_SET_ORIGIN "Aseta origo"
	#define MSG_PREHEAT_PLA "Esilammita PLA"
	#define MSG_PREHEAT_PLA0 "Esilammita PLA 1"
	#define MSG_PREHEAT_PLA1 "Esilammita PLA 2"
	#define MSG_PREHEAT_PLA2 "Esilammita PLA 3"
	#define MSG_PREHEAT_PLA012 "Esila. PLA Kaikki"
	#define MSG_PREHEAT_PLA_BEDONLY  "Esila. PLA Alusta"
	#define MSG_PREHEAT_PLA_SETTINGS "Esilamm. PLA konf"
	#define MSG_PREHEAT_ABS "Esilammita ABS"
	#define MSG_PREHEAT_ABS0 "Esilammita ABS 1"
	#define MSG_PREHEAT_ABS1 "Esilammita ABS 2"
	#define MSG_PREHEAT_ABS2 "Esilammita ABS 3"
	#define MSG_PREHEAT_ABS012 "Esila. ABS Kaikki"
	#define MSG_PREHEAT_ABS_BEDONLY  "Esila. ABS Alusta"
	#define MSG_PREHEAT_ABS_SETTINGS "Esilamm. ABS konf"
	#define MSG_COOLDOWN "Jaahdyta"
	#define MSG_SWITCH_PS_ON "Virta paalle"
	#define MSG_SWITCH_PS_OFF "Virta pois"
	#define MSG_EXTRUDE "Pursota"
	#define MSG_RETRACT "Veda takaisin"
	#define MSG_MOVE_AXIS "Liikuta akseleita"
	#define MSG_MOVE_X "Move X"
	#define MSG_MOVE_Y "Move Y"
	#define MSG_MOVE_Z "Move Z"
	#define MSG_MOVE_E "Extruder"
	#define MSG_MOVE_E1 "Extruder2"
	#define MSG_MOVE_E2 "Extruder3"
	#define MSG_MOVE_01MM "Move 0.1mm"
	#define MSG_MOVE_1MM "Move 1mm"
	#define MSG_MOVE_10MM "Move 10mm"
	#define MSG_SPEED "Nopeus"
	#define MSG_NOZZLE "Suutin"
	#define MSG_NOZZLE1 "Suutin2"
	#define MSG_NOZZLE2 "Suutin3"
	#define MSG_BED "Alusta"
	#define MSG_FAN_SPEED "Tuul. nopeus"
	#define MSG_FLOW "Virtaus"
	#define MSG_FLOW0 "Virtaus 0"
	#define MSG_FLOW1 "Virtaus 1"
	#define MSG_FLOW2 "Virtaus 2"
	#define MSG_CONTROL "Kontrolli"
	#define MSG_MIN " \002 Min"
	#define MSG_MAX " \002 Max"
	#define MSG_FACTOR " \002 Kerr"
	#define MSG_AUTOTEMP "Autotemp"
	#define MSG_ON "On "
	#define MSG_OFF "Off"
	#define MSG_PID_P "PID-P"
	#define MSG_PID_I "PID-I"
	#define MSG_PID_D "PID-D"
	#define MSG_PID_C "PID-C"
	#define MSG_ACC  "Kiihtyv"
	#define MSG_VXY_JERK "Vxy-jerk"
	#define MSG_VZ_JERK "Vz-jerk"
	#define MSG_VE_JERK "Ve-jerk"
	#define MSG_VMAX "Vmax "
	#define MSG_X "x"
	#define MSG_Y "y"
	#define MSG_Z "z"
	#define MSG_E "e"
	#define MSG_VMIN "Vmin"
	#define MSG_VTRAV_MIN "VLiike min"
	#define MSG_AMAX "Amax "
	#define MSG_A_RETRACT "A-peruuta"
	#define MSG_XSTEPS "Xsteps/mm"
	#define MSG_YSTEPS "Ysteps/mm"
	#define MSG_ZSTEPS "Zsteps/mm"
	#define MSG_ESTEPS "Esteps/mm"
	#define MSG_RECTRACT "Veda takaisin"
	#define MSG_TEMPERATURE "Lampotila"
	#define MSG_MOTION "Liike"
	#define MSG_CONTRAST "LCD contrast"
	#define MSG_STORE_EPROM "Tallenna muistiin"
	#define MSG_LOAD_EPROM "Lataa muistista"
	#define MSG_RESTORE_FAILSAFE "Palauta oletus"
	#define MSG_REFRESH "Paivita"
	#define MSG_WATCH "Seuraa"
	#define MSG_PREPARE "Valmistele"
	#define MSG_TUNE "Saada"
	#define MSG_PAUSE_PRINT "Keskeyta tulostus"
	#define MSG_RESUME_PRINT "Jatka tulostusta"
	#define MSG_STOP_PRINT "Pysayta tulostus"
	#define MSG_CARD_MENU "Korttivalikko"
	#define MSG_NO_CARD "Ei korttia"
	#define MSG_DWELL "Nukkumassa..."
	#define MSG_USERWAIT "Odotet. valintaa"
	#define MSG_RESUMING "Jatke. tulostusta"
	#define MSG_NO_MOVE "Ei liiketta."
	#define MSG_KILLED "KILLED. "
	#define MSG_STOPPED "STOPPED. "
	#define MSG_CONTROL_RETRACT  "Veda mm"
	#define MSG_CONTROL_RETRACT_SWAP  "Va. Veda mm"
	#define MSG_CONTROL_RETRACTF "Veda V"
	#define MSG_CONTROL_RETRACT_ZLIFT "Z mm"
	#define MSG_CONTROL_RETRACT_RECOVER "UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Va. UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "UnRet  V"
	#define MSG_AUTORETRACT "AutoVeto."
	#define MSG_FILAMENTCHANGE "Change filament"
	#define MSG_INIT_SDCARD "Init. SD-Card"
	#define MSG_CNG_SDCARD "Change SD-Card"
	#define MSG_ZPROBE_OUT "Z probe out. bed"
	#define MSG_POSITION_UNKNOWN "Home X/Y before Z"
	#define MSG_ZPROBE_ZOFFSET "Z Offset"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Endstop abort"

#endif

#if LANGUAGE_CHOICE == 10

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " parada."
	#define MSG_SD_INSERTED "Tarcheta colocada"
	#define MSG_SD_REMOVED "Tarcheta retirada"
	#define MSG_MAIN "Menu prencipal"
	#define MSG_AUTOSTART " Autostart"
	#define MSG_DISABLE_STEPPERS "Amortar motors"
	#define MSG_AUTO_HOME "Levar a l'orichen"
	#define MSG_SET_HOME_OFFSETS "Set home offsets"
	#define MSG_SET_ORIGIN "Establir zero"
	#define MSG_PREHEAT_PLA "Precalentar PLA"
	#define MSG_PREHEAT_PLA0 "Precalentar PLA0"
	#define MSG_PREHEAT_PLA1 "Precalentar PLA1"
	#define MSG_PREHEAT_PLA2 "Precalentar PLA2"
	#define MSG_PREHEAT_PLA012 "Precalentar PLA a"
	#define MSG_PREHEAT_PLA_BEDONLY  "Prec. PLA Base"
	#define MSG_PREHEAT_PLA_SETTINGS "Achustar tem. PLA"
	#define MSG_PREHEAT_ABS "Precalentar ABS"
	#define MSG_PREHEAT_ABS0 "Precalentar ABS0"
	#define MSG_PREHEAT_ABS1 "Precalentar ABS1"
	#define MSG_PREHEAT_ABS2 "Precalentar ABS2"
	#define MSG_PREHEAT_ABS012 "Precalentar ABS a"
	#define MSG_PREHEAT_ABS_BEDONLY  "Prec. ABS Base"
	#define MSG_PREHEAT_ABS_SETTINGS "Achustar tem. ABS"
	#define MSG_COOLDOWN "Enfriar"
	#define MSG_SWITCH_PS_ON "Enchegar Fuent"
	#define MSG_SWITCH_PS_OFF "Desenchegar Fuent"
	#define MSG_EXTRUDE "Extruir"
	#define MSG_RETRACT "Retraer"
	#define MSG_MOVE_AXIS "Mover Eixes"
	#define MSG_MOVE_X "Move X"
	#define MSG_MOVE_Y "Move Y"
	#define MSG_MOVE_Z "Move Z"
	#define MSG_MOVE_E "Extruder"
	#define MSG_MOVE_E1 "Extruder2"
	#define MSG_MOVE_E2 "Extruder3"
	#define MSG_MOVE_01MM "Move 0.1mm"
	#define MSG_MOVE_1MM "Move 1mm"
	#define MSG_MOVE_10MM "Move 10mm"
	#define MSG_SPEED "Velocidat"
	#define MSG_NOZZLE "Nozzle"
	#define MSG_NOZZLE1 "Nozzle2"
	#define MSG_NOZZLE2 "Nozzle3"
	#define MSG_BED "Base"
	#define MSG_FAN_SPEED "Ixoriador"
	#define MSG_FLOW "Fluxo"
	#define MSG_FLOW0 "Fluxo 0"
	#define MSG_FLOW1 "Fluxo 1"
	#define MSG_FLOW2 "Fluxo 2"
	#define MSG_CONTROL "Control"
	#define MSG_MIN "\002 Min"
	#define MSG_MAX "\002 Max"
	#define MSG_FACTOR "\002 Fact"
	#define MSG_AUTOTEMP "Autotemp"
	#define MSG_ON "On"
	#define MSG_OFF "Off"
	#define MSG_PID_P "PID-P"
	#define MSG_PID_I "PID-I"
	#define MSG_PID_D "PID-D"
	#define MSG_PID_C "PID-C"
	#define MSG_ACC  "Acel"
	#define MSG_VXY_JERK "Vxy-jerk"
	#define MSG_VZ_JERK "Vz-jerk"
	#define MSG_VE_JERK "Ves-jerk"
	#define MSG_VMAX "Vmax"
	#define MSG_X "x"
	#define MSG_Y "y"
	#define MSG_Z "z"
	#define MSG_E "y"
	#define MSG_VMIN "Vmin"
	#define MSG_VTRAV_MIN "VTrav min"
	#define MSG_AMAX "Amax"
	#define MSG_A_RETRACT "A-retrac."
	#define MSG_XSTEPS "X trangos/mm"
	#define MSG_YSTEPS "Y trangos/mm"
	#define MSG_ZSTEPS "Z trangos/mm"
	#define MSG_ESTEPS "E trangos/mm"
	#define MSG_RECTRACT "Retraer"
	#define MSG_TEMPERATURE "Temperatura"
	#define MSG_MOTION "Movimiento"
	#define MSG_STORE_EPROM "Alzar Memoria"
	#define MSG_LOAD_EPROM "Cargar Memoria"
	#define MSG_RESTORE_FAILSAFE "Rest. d'emerchen."
	#define MSG_REFRESH "Tornar a cargar"
	#define MSG_WATCH "Monitorizar"
	#define MSG_PREPARE "Preparar"
	#define MSG_TUNE "Achustar"
	#define MSG_PAUSE_PRINT "Pausar impresion"
	#define MSG_RESUME_PRINT "Contin. impresion"
	#define MSG_STOP_PRINT "Detener Impresion"
	#define MSG_CARD_MENU "Menu de SD"
	#define MSG_NO_CARD "No i hai tarcheta"
	#define MSG_DWELL "Reposo..."
	#define MSG_USERWAIT "Asperan. ordines"
	#define MSG_RESUMING "Contin. impresion"
	#define MSG_NO_MOVE "Sin movimiento"
	#define MSG_KILLED "ATURADA D'EMERCH."
	#define MSG_STOPPED "ATURADA."
	#define MSG_CONTROL_RETRACT  "Retraer mm"
	#define MSG_CONTROL_RETRACT_SWAP  "Swap Retraer mm"
	#define MSG_CONTROL_RETRACTF "Retraer  F"
	#define MSG_CONTROL_RETRACT_ZLIFT "Devantar mm"
	#define MSG_CONTROL_RETRACT_RECOVER "DesRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Swap DesRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "DesRet F"
	#define MSG_AUTORETRACT "AutoRetr."
	#define MSG_FILAMENTCHANGE "Cambear"
	#define MSG_INIT_SDCARD "Encetan. tarcheta"
	#define MSG_CNG_SDCARD "Cambiar tarcheta"
	#define MSG_RECTRACT_WIDE "Retraer"
	#define MSG_TEMPERATURE_WIDE "Temperatura"
	#define MSG_TEMPERATURE_RTN  "Temperatura"
	#define MSG_MAIN_WIDE "Menu Prencipal"
	#define MSG_MOTION_WIDE "Movimiento"
	#define MSG_PREPARE_ALT "Preparar"
	#define MSG_CONTROL_ARROW "Control"
	#define MSG_RETRACT_ARROW "Retraer"
	#define MSG_STEPPER_RELEASED "Desacoplada."
	#define MSG_ZPROBE_OUT "Z probe out. bed"
	#define MSG_POSITION_UNKNOWN "Home X/Y before Z"
	#define MSG_ZPROBE_ZOFFSET "Z Offset"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Endstop abort"
	#define MSG_CONTRAST "Contrast"

#endif

#if LANGUAGE_CHOICE == 11 //Dutch

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " gereed."
	#define MSG_SD_INSERTED "Kaart ingestoken"
	#define MSG_SD_REMOVED "Kaart verwijderd"
	#define MSG_MAIN "Main"
	#define MSG_AUTOSTART "Autostart"
	#define MSG_DISABLE_STEPPERS "Motoren uit"
	#define MSG_AUTO_HOME "Auto home"
	#define MSG_SET_HOME_OFFSETS "Set home offsets"
	#define MSG_SET_ORIGIN "Nulpunt instellen"
	#define MSG_PREHEAT_PLA "PLA voorverwarmen"
	#define MSG_PREHEAT_PLA0 "PLA voorverw. 0"
	#define MSG_PREHEAT_PLA1 "PLA voorverw. 1"
	#define MSG_PREHEAT_PLA2 "PLA voorverw. 2"
	#define MSG_PREHEAT_PLA012 "PLA voorverw. aan"
	#define MSG_PREHEAT_PLA_BEDONLY  "PLA voorverw. Bed"
	#define MSG_PREHEAT_PLA_SETTINGS "PLA verw. conf"
	#define MSG_PREHEAT_ABS "ABS voorverwarmen"
	#define MSG_PREHEAT_ABS0 "ABS voorverw. 0"
	#define MSG_PREHEAT_ABS1 "ABS voorverw. 1"
	#define MSG_PREHEAT_ABS2 "ABS voorverw. 2"
	#define MSG_PREHEAT_ABS012 "ABS voorverw. aan"
	#define MSG_PREHEAT_ABS_BEDONLY  "ABS voorverw. Bed"
	#define MSG_PREHEAT_ABS_SETTINGS "ABS verw. conf"
	#define MSG_COOLDOWN "Afkoelen"
	#define MSG_SWITCH_PS_ON "Stroom aan"
	#define MSG_SWITCH_PS_OFF "Stroom uit"
	#define MSG_EXTRUDE "Extrude"
	#define MSG_RETRACT "Retract"
	#define MSG_MOVE_AXIS "As verplaatsen"
	#define MSG_MOVE_X "Verplaats X"
	#define MSG_MOVE_Y "Verplaats Y"
	#define MSG_MOVE_Z "Verplaats Z"
	#define MSG_MOVE_E "Extruder"
	#define MSG_MOVE_E1 "Extruder2"
	#define MSG_MOVE_E2 "Extruder3"
	#define MSG_MOVE_01MM "Verplaats 0.1mm"
	#define MSG_MOVE_1MM "Verplaats 1mm"
	#define MSG_MOVE_10MM "Verplaats 10mm"
	#define MSG_SPEED "Snelheid"
	#define MSG_NOZZLE "Nozzle"
	#define MSG_NOZZLE1 "Nozzle2"
	#define MSG_NOZZLE2 "Nozzle3"
	#define MSG_BED "Bed"
	#define MSG_FAN_SPEED "Fan snelheid"
	#define MSG_FLOW "Flow"
	#define MSG_FLOW0 "Flow 0"
	#define MSG_FLOW1 "Flow 1"
	#define MSG_FLOW2 "Flow 2"
	#define MSG_CONTROL "Control"
	#define MSG_MIN " \002 Min"
	#define MSG_MAX " \002 Max"
	#define MSG_FACTOR " \002 Fact"
	#define MSG_AUTOTEMP "Autotemp"
	#define MSG_ON "Aan "
	#define MSG_OFF "Uit"
	#define MSG_PID_P "PID-P"
	#define MSG_PID_I "PID-I"
	#define MSG_PID_D "PID-D"
	#define MSG_PID_C "PID-C"
	#define MSG_ACC  "Versn"
	#define MSG_VXY_JERK "Vxy-jerk"
	#define MSG_VZ_JERK "Vz-jerk"
	#define MSG_VE_JERK "Ve-jerk"
	#define MSG_VMAX "Vmax "
	#define MSG_X "x"
	#define MSG_Y "y"
	#define MSG_Z "z"
	#define MSG_E "e"
	#define MSG_VMIN "Vmin"
	#define MSG_VTRAV_MIN "VTrav min"
	#define MSG_AMAX "Amax "
	#define MSG_A_RETRACT "A-retract"
	#define MSG_XSTEPS "Xsteps/mm"
	#define MSG_YSTEPS "Ysteps/mm"
	#define MSG_ZSTEPS "Zsteps/mm"
	#define MSG_ESTEPS "Esteps/mm"
	#define MSG_RECTRACT "Terugtrekken"
	#define MSG_TEMPERATURE "Temperatuur"
	#define MSG_MOTION "Beweging"
	#define MSG_CONTRAST "LCD contrast"
	#define MSG_STORE_EPROM "Geheugen opslaan"
	#define MSG_LOAD_EPROM "Geheugen laden"
	#define MSG_RESTORE_FAILSAFE "Noodstop reset"
	#define MSG_REFRESH "Ververs"
	#define MSG_WATCH "Info scherm"
	#define MSG_PREPARE "Voorbereiden"
	#define MSG_TUNE "Afstellen"
	#define MSG_PAUSE_PRINT "Print pauzeren"
	#define MSG_RESUME_PRINT "Print hervatten"
	#define MSG_STOP_PRINT "Print stoppen"
	#define MSG_CARD_MENU "Print van SD"
	#define MSG_NO_CARD "Geen SD kaart"
	#define MSG_DWELL "Slapen..."
	#define MSG_USERWAIT "Wachten..."
	#define MSG_RESUMING "Print hervatten"
	#define MSG_NO_MOVE "Geen beweging."
	#define MSG_KILLED "AFGEBROKEN. "
	#define MSG_STOPPED "GESTOPT. "
	#define MSG_CONTROL_RETRACT  "Retract mm"
	#define MSG_CONTROL_RETRACT_SWAP "Ruil Retract mm"
	#define MSG_CONTROL_RETRACTF "Retract  F"
	#define MSG_CONTROL_RETRACT_ZLIFT "Hop mm"
	#define MSG_CONTROL_RETRACT_RECOVER "UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Ruil UnRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "UnRet  F"
	#define MSG_AUTORETRACT "AutoRetr."
	#define MSG_FILAMENTCHANGE "Verv. Filament"
	#define MSG_INIT_SDCARD "Init. SD kaart"
	#define MSG_CNG_SDCARD "Verv. SD card"
	#define MSG_ZPROBE_OUT "Z probe uit. bed"
	#define MSG_POSITION_UNKNOWN "Home X/Y voor Z"
	#define MSG_ZPROBE_ZOFFSET "Z Offset"
	#define MSG_BABYSTEP_X "Babystap X"
	#define MSG_BABYSTEP_Y "Babystap Y"
	#define MSG_BABYSTEP_Z "Babystap Z"
	#define MSG_ENDSTOP_ABORT "Endstop afbr."

#endif


#if LANGUAGE_CHOICE == 12

// LCD Menu Messages

// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " preparada."
	#define MSG_SD_INSERTED "SD detectada."
	#define MSG_SD_REMOVED "SD expulsada."
	#define MSG_MAIN "Menu principal"
	#define MSG_AUTOSTART "Inici automatic"
	#define MSG_DISABLE_STEPPERS "Apagar motors"
	#define MSG_AUTO_HOME "Home global"
	#define MSG_SET_ORIGIN "Establir origen"
	#define MSG_PREHEAT_PLA "Preescalfar PLA"
	#define MSG_PREHEAT_PLA0 "Preescalfar PLA 1"
	#define MSG_PREHEAT_PLA1 "Preescalfar PLA 2"
	#define MSG_PREHEAT_PLA2 "Preescalfar PLA 3"
	#define MSG_PREHEAT_PLA012 "Preesc. tot PLA"
	#define MSG_PREHEAT_PLA_BEDONLY "Preesc. llit PLA"
	#define MSG_PREHEAT_PLA_SETTINGS "Configuració PLA"
	#define MSG_PREHEAT_ABS "Preescalfar ABS"
	#define MSG_PREHEAT_ABS0 "Preescalfar ABS 1"
	#define MSG_PREHEAT_ABS1 "Preescalfar ABS 2"
	#define MSG_PREHEAT_ABS2 "Preescalfar ABS 3"
	#define MSG_PREHEAT_ABS012 "Preesc. tot ABS"
	#define MSG_PREHEAT_ABS_BEDONLY "Preesc. llit ABS"
	#define MSG_PREHEAT_ABS_SETTINGS "Configuració ABS"
	#define MSG_COOLDOWN "Refredar"
	#define MSG_SWITCH_PS_ON "Switch power on"
	#define MSG_SWITCH_PS_OFF "Switch power off"
	#define MSG_EXTRUDE "Extruir"
	#define MSG_RETRACT "Refredar"
	#define MSG_MOVE_AXIS "Moure eixos"
	#define MSG_MOVE_X "Moure X"
	#define MSG_MOVE_Y "Moure Y"
	#define MSG_MOVE_Z "Moure Z"
	#define MSG_MOVE_E "Extrusor"
	#define MSG_MOVE_E1 "Extruder2"
	#define MSG_MOVE_E2 "Extruder3"
	#define MSG_MOVE_01MM "Moure 0.1mm"
	#define MSG_MOVE_1MM "Moure 1mm"
	#define MSG_MOVE_10MM "Moure 10mm"
	#define MSG_SPEED "Velocitat"
	#define MSG_NOZZLE "Nozzle"
	#define MSG_NOZZLE1 "Nozzle2"
	#define MSG_NOZZLE2 "Nozzle3"
	#define MSG_BED "Llit"
	#define MSG_FAN_SPEED "Vel. Ventilador"
	#define MSG_FLOW "Fluxe"
	#define MSG_FLOW0 "Fluxe 0"
	#define MSG_FLOW1 "Fluxe 1"
	#define MSG_FLOW2 "Fluxe 2"
	#define MSG_CONTROL "Control"
	#define MSG_MIN " \002 Min"
	#define MSG_MAX " \002 Max"
	#define MSG_FACTOR " \002 Fact"
	#define MSG_AUTOTEMP "Autotemp"
	#define MSG_ON "On "
	#define MSG_OFF "Off"
	#define MSG_PID_P "PID-P"
	#define MSG_PID_I "PID-I"
	#define MSG_PID_D "PID-D"
	#define MSG_PID_C "PID-C"
	#define MSG_ACC  "Accel"
	#define MSG_VXY_JERK "Vxy-jerk"
	#define MSG_VZ_JERK "Vz-jerk"
	#define MSG_VE_JERK "Ve-jerk"
	#define MSG_VMAX "Vmax "
	#define MSG_X "x"
	#define MSG_Y "y"
	#define MSG_Z "z"
	#define MSG_E "e"
	#define MSG_VMIN "Vmin"
	#define MSG_VTRAV_MIN "VTrav min"
	#define MSG_AMAX "Amax "
	#define MSG_A_RETRACT "A-retract"
	#define MSG_XSTEPS "Xpassos/mm"
	#define MSG_YSTEPS "Ypassos/mm"
	#define MSG_ZSTEPS "Zpassos/mm"
	#define MSG_ESTEPS "Epassos/mm"
	#define MSG_RECTRACT "Retreure"
	#define MSG_TEMPERATURE "Temperatura"
	#define MSG_MOTION "Moviment"
	#define MSG_CONTRAST "Contrast de LCD"
	#define MSG_STORE_EPROM "Desar a memoria"
	#define MSG_LOAD_EPROM "Carregar de mem."
	#define MSG_RESTORE_FAILSAFE "Rest. emergencia"
	#define MSG_REFRESH "Refrescar"
	#define MSG_WATCH "Pantalla Info."
	#define MSG_PREPARE "Preparar"
	#define MSG_TUNE "Calibrar"
	#define MSG_PAUSE_PRINT "Pausa imp."
	#define MSG_RESUME_PRINT "Reprendre imp."
	#define MSG_STOP_PRINT "Parar inp."
	#define MSG_CARD_MENU "Imprimir de SD"
	#define MSG_NO_CARD "-Sense targeta SD"
	#define MSG_DWELL "Repos..."
	#define MSG_USERWAIT "Esperant usuari.."
	#define MSG_RESUMING "Reprenent imp."
	#define MSG_NO_MOVE "Sense moviment."
	#define MSG_KILLED "PARADA DE EMERG. "
	#define MSG_STOPPED "ATURAT. "
	#define MSG_CONTROL_RETRACT  "Retreure mm"
	#define MSG_CONTROL_RETRACT_SWAP  "Swap Retreure mm"
	#define MSG_CONTROL_RETRACTF "Retreure  F"
	#define MSG_CONTROL_RETRACT_ZLIFT "Aixecar mm"
	#define MSG_CONTROL_RETRACT_RECOVER "DesRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Swap DesRet +mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "DesRet  F"
	#define MSG_AUTORETRACT "AutoRetr."
	#define MSG_FILAMENTCHANGE "Canviar filament"
	#define MSG_INIT_SDCARD "Iniciant SD"
	#define MSG_CNG_SDCARD "Canviar SD"
	#define MSG_ZPROBE_OUT "Z probe out. bed"
	#define MSG_POSITION_UNKNOWN "Home X/Y abans Z"
	#define MSG_ZPROBE_ZOFFSET "Z Offset"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Endstop abort"

#endif

//Basque-Euskera
#if LANGUAGE_CHOICE == 13

// LCD Menu Messages
// Please note these are limited to 17 characters!

	#define WELCOME_MSG MACHINE_NAME " prest."
	#define MSG_SD_INSERTED "Txartela sartuta"
	#define MSG_SD_REMOVED "Txartela kenduta"
	#define MSG_MAIN "Menu nagusia"
	#define MSG_AUTOSTART "Auto hasiera"
	#define MSG_DISABLE_STEPPERS "Itzali motoreak"
	#define MSG_AUTO_HOME "Hasierara joan"
	#define MSG_SET_ORIGIN "Hasiera ipini"
	#define MSG_PREHEAT_PLA "Aurreberotu PLA"
	#define MSG_PREHEAT_PLA0 "Aurreberotu PLA1"
	#define MSG_PREHEAT_PLA1 "Aurreberotu PLA2"
	#define MSG_PREHEAT_PLA2 "Aurreberotu PLA3"
	#define MSG_PREHEAT_PLA012 "Berotu PLA Guztia"
	#define MSG_PREHEAT_PLA_BEDONLY "Berotu PLA Ohea"
	#define MSG_PREHEAT_PLA_SETTINGS "Berotu PLA Konfig"
	#define MSG_PREHEAT_ABS "Aurreberotu ABS"
	#define MSG_PREHEAT_ABS0 "Aurreberotu ABS 1"
	#define MSG_PREHEAT_ABS1 "Aurreberotu ABS 2"
	#define MSG_PREHEAT_ABS2 "Aurreberotu ABS 3"
	#define MSG_PREHEAT_ABS012 "Berotu ABS Guztia"
	#define MSG_PREHEAT_ABS_BEDONLY "Berotu ABS Ohea"
	#define MSG_PREHEAT_ABS_SETTINGS "Berotu ABS Konfig"
	#define MSG_COOLDOWN "Hoztu"
	#define MSG_SWITCH_PS_ON "Energia piztu"
	#define MSG_SWITCH_PS_OFF "Energia itzali"
	#define MSG_EXTRUDE "Estruitu"
	#define MSG_RETRACT "Atzera eragin"
	#define MSG_MOVE_AXIS "Ardatzak mugitu"
	#define MSG_MOVE_X "Mugitu X"
	#define MSG_MOVE_Y "Mugitu Y"
	#define MSG_MOVE_Z "Mugitu Z"
	#define MSG_MOVE_E "Estrusorea"
	#define MSG_MOVE_E1 "Estrusorea2"
	#define MSG_MOVE_E2 "Estrusorea3"
	#define MSG_MOVE_01MM "Mugitu 0.1mm"
	#define MSG_MOVE_1MM "Mugitu 1mm"
	#define MSG_MOVE_10MM "Mugitu 10mm"
	#define MSG_SPEED "Abiadura"
	#define MSG_NOZZLE "Pita"
	#define MSG_NOZZLE1 "Pita2"
	#define MSG_NOZZLE2 "Pita3"
	#define MSG_BED "Ohea"
	#define MSG_FAN_SPEED "Haizagailua"
	#define MSG_FLOW "Fluxua"
	#define MSG_FLOW0 "Fluxua 0"
	#define MSG_FLOW1 "Fluxua 1"
	#define MSG_FLOW2 "Fluxua 2"
	#define MSG_CONTROL "Kontrola"
	#define MSG_MIN " \002 Min"
	#define MSG_MAX " \002 Max"
	#define MSG_FACTOR " \002 Faktorea"
	#define MSG_AUTOTEMP "Auto tenperatura"
	#define MSG_ON "On "
	#define MSG_OFF "Off"
	#define MSG_PID_P "PID-P"
	#define MSG_PID_I "PID-I"
	#define MSG_PID_D "PID-D"
	#define MSG_PID_C "PID-C"
	#define MSG_ACC  "Azelerazioa"
	#define MSG_VXY_JERK "Vxy-astindua"
	#define MSG_VZ_JERK "Vz-astindua"
	#define MSG_VE_JERK "Ve-astindua"
	#define MSG_VMAX "Vmax "
	#define MSG_X "x"
	#define MSG_Y "y"
	#define MSG_Z "z"
	#define MSG_E "e"
	#define MSG_VMIN "Vmin"
	#define MSG_VTRAV_MIN "VTrav min"
	#define MSG_AMAX "Amax "
	#define MSG_A_RETRACT "A-retrakt"
	#define MSG_XSTEPS "X pausoak/mm"
	#define MSG_YSTEPS "Y pausoak/mm"
	#define MSG_ZSTEPS "Z pausoak/mm"
	#define MSG_ESTEPS "E pausoak/mm"
	#define MSG_RECTRACT "Atzera eragin"
	#define MSG_TEMPERATURE "Tenperatura"
	#define MSG_MOTION "Mugimendua"
	#define MSG_CONTRAST "LCD kontrastea"
	#define MSG_STORE_EPROM "Gorde memoria"
	#define MSG_LOAD_EPROM "Kargatu memoria"
	#define MSG_RESTORE_FAILSAFE "Larri. berriz."
	#define MSG_REFRESH "Berriz kargatu"
	#define MSG_WATCH "Pantaila info"
	#define MSG_PREPARE "Prestatu"
	#define MSG_TUNE "Doitu"
	#define MSG_PAUSE_PRINT "Pausatu inprimak."
	#define MSG_RESUME_PRINT "Jarraitu inprima."
	#define MSG_STOP_PRINT "Gelditu inprima."
	#define MSG_CARD_MENU "SD-tik inprimatu"
	#define MSG_NO_CARD "Ez dago txartelik"
	#define MSG_DWELL "Lo egin..."
	#define MSG_USERWAIT "Aginduak zain..."
	#define MSG_RESUMING "Jarraitzen inpri."
	#define MSG_NO_MOVE "Mugimendu gabe"
	#define MSG_KILLED "LARRIALDI GELDIA"
	#define MSG_STOPPED "GELDITUTA. "
	#define MSG_CONTROL_RETRACT  "Atzera egin mm"
	#define MSG_CONTROL_RETRACT_SWAP  "Swap Atzera egin mm"
	#define MSG_CONTROL_RETRACTF "Atzera egin V"
	#define MSG_CONTROL_RETRACT_ZLIFT "Igo mm"
	#define MSG_CONTROL_RETRACT_RECOVER "Atzera egin +mm"
	#define MSG_CONTROL_RETRACT_RECOVER_SWAP "Swap Atzera egin +mm"
	#define MSG_CONTROL_RETRACT_RECOVERF "Atzera egin V"
	#define MSG_AUTORETRACT "Atzera egin"
	#define MSG_FILAMENTCHANGE "Aldatu filament."
	#define MSG_INIT_SDCARD "Hasieratu txartela"
	#define MSG_CNG_SDCARD "Aldatu txartela"
	#define MSG_ZPROBE_OUT "Z ohe hasiera"
	#define MSG_POSITION_UNKNOWN "Posizio ezezaguna"
	#define MSG_ZPROBE_ZOFFSET "Z konpentsatu"
	#define MSG_BABYSTEP_X "Babystep X"
	#define MSG_BABYSTEP_Y "Babystep Y"
	#define MSG_BABYSTEP_Z "Babystep Z"
	#define MSG_ENDSTOP_ABORT "Endstop deuseztat"
#endif


#endif // COMMUNICATION_H
