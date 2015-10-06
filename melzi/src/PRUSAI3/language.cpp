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
#include "m_include.h"

const char *tDebug="Debug:";
const char *tOk="ok";
const char *tNewline="\r\n";
const char *tNAN="NAN";
const char *tINF="INF";
const char *tError="Error:";
const char *tInfo="Info:";
const char *tWarning="Warning:";
const char *tWait="wait";
const char *tResend="Resend:";
const char *tEcho="Echo:";
const char *tOkSpace="ok ";
const char *tWrongChecksum="Wrong checksum";
const char *tMissingChecksum="Missing checksum";
const char *tBuffOverFlow="BuffOverFlow";
const char *tFormatError="Format error";
const char *tDonePrinting="Done printing file";
const char *tX=" X";
const char *tY=" Y";
const char *tZ=" Z";
const char *tE=" E";
const char *tF=" F";
const char *tS=" S";
const char *tP=" P";
const char *tI=" I";
const char *tJ=" J";
const char *tR=" R";
const char *tSDReadError="SD read error";
const char *tExpectedLine="Error:expected line ";
const char *tGot=" got ";
const char *tSkip="skip ";
const char *tBLK="BLK ";
const char *tStart="start";
const char *tPowerUp="PowerUp";
const char *tExternalReset="External Reset";
const char *tBrownOut="Brown out Reset";
const char *tWatchdog="Watchdog Reset";
const char *tSoftwareReset="Software Reset";
const char *tUnknownCommand="Unknown command:";
const char *tFreeRAM="Free RAM:";
const char *tXColon="X:";
const char *tSpaceXColon=" X:";
const char *tSpaceYColon=" Y:";
const char *tSpaceZColon=" Z:";
const char *tSpaceEColon=" E:";
const char *tTColon="T:";
const char *tSpaceBColon=" B:";
const char *tSpaceAtColon=" @:";
const char *tSpaceT=" T";
const char *tSpaceAt=" @";
const char *tSpaceBAtColon=" B@:";
const char *tSpaceRaw=" RAW";
const char *tColon=":";
const char *tSlash="/";
const char *tSpeedMultiply="SpeedMultiply:";
const char *tFlowMultiply="FlowMultiply:";
const char *tFanspeed="Fanspeed:";
const char *tPrintedFilament="Printed filament:";
const char *tPrintingTime="Printing time:";
const char *tSpacem="m ";
const char *tSpaceDaysSpace=" days ";
const char *tSpaceHoursSpace=" hours ";
const char *tSpaceMin=" min";
const char *tInvalidArc="Invalid arc";
const char *tComma="=";
const char *tSpace=" ";
const char *tYColon="Y:";
const char *tZColon="Z:";
const char *tE0Colon="E0:";
const char *tE1Colon="E1:";
const char *tMS1MS2Pins="MS1,MS2 Pins";
const char *tSetOutputSpace="Set output ";
const char *tSpaceToSpace=" to ";
const char *tHSpace="H ";
const char *tLSpace="L ";
const char *tXMinColon="x_min:";
const char *tXMaxColon="x_max:";
const char *tYMinColon="y_min:";
const char *tYMaxColon="y_max:";
const char *tZMinColon="z_min:";
const char *tZMaxColon="z_max:";
const char *tJerkColon="Jerk:";
const char *tZJerkColon=" ZJerk:";
const char *tLinearStepsColon=" linear steps:";
const char *tQuadraticStepsColon=" quadratic steps:";
const char *tCommaSpeedEqual=", speed=";
const char *tEEPROMUpdated="EEPROM updated";

const char *tLinearLColon="linear L:";
const char *tQuadraticKColon=" quadratic K:";
#if DRIVE_SYSTEM==3
const char *tMeasurementReset="Measurement reset.";
const char *tMeasureDeltaSteps="Measure/delta (Steps; =";
const char *tMeasureDelta="Measure/delta =";
const char *tMeasureOriginReset="Measured origin set. Measurement reset.";
const char *tMeasurementAbortedOrigin="Origin measurement cannot be set.  Use only Z-Cartesian (straight up and down; movements and try again.";
const char *tInvalidDeltaCoordinate="Invalid delta coordinate - move ignored";
const char *tLevelingCalc="Leveling calc:";
const char *tTower1="Tower 1:";
const char *tTower2="Tower 2:";
const char *tTower3="Tower 3:";
const char *tDeltaAlphaA="Alpha A(210;:";
const char *tDeltaAlphaB="Alpha B(330;:";
const char *tDeltaAlphaC="Alpha C(90;:";
const char *tDeltaRadiusCorrectionA="Delta Radius A(0;:";
const char *tDeltaRadiusCorrectionB="Delta Radius B(0;:";
const char *tDeltaRadiusCorrectionC="Delta Radius C(0;:";
const char *tDBGDeltaNoMoveinDSegment="No move in delta segment with > 1 segment. This should never happen and may cause a problem!";
#endif // DRIVE_SYSTEM
#if DRIVE_SYSTEM==4
const char *tInvalidDeltaCoordinate="Invalid coordinate - move ignored";
const char *tDBGDeltaNoMoveinDSegment="No move in delta segment with > 1 segment. This should never happen and may cause a problem!";
const char *tEPRDiagonalRodLength="Long arm length [mm]";
#endif // DRIVE_SYSTEM
#ifdef DEBUG_GENERIC
const char *tGenTemp="GenTemp:";
#endif // DEBUG_GENERICconst char *="";
const char *tTargetExtr="TargetExtr";
const char *tTargetBedColon="TargetBed:";
const char *tPIDAutotuneStart="PID Autotune start";
const char *tAPIDBias=" bias: ";
const char *tAPIDD=" d: ";
const char *tAPIDMin=" min: ";
const char *tAPIDMax=" max: ";
const char *tAPIDKu=" Ku: ";
const char *tAPIDTu=" Tu: ";
const char *tAPIDClassic=" Classic PID";
const char *tAPIDKp=" Kp: ";
const char *tAPIDKi=" Ki: ";
const char *tAPIDKd=" Kd: ";
const char *tAPIDFailedHigh="PID Autotune failed! Temperature to high";
const char *tAPIDFailedTimeout="PID Autotune failed! timeout";
const char *tAPIDFinished="PID Autotune finished ! Place the Kp, Ki and Kd constants in the Configuration.h or EEPROM";
const char *tMTEMPColon="MTEMP:";
const char *tHeatedBed="heated bed";
const char *tExtruderSpace="extruder ";
const char *tTempSensorDefect=": temp sensor defect";
const char *tTempSensorWorking=": working";
const char *tDryModeUntilRestart="Printer set into dry run mode until restart!";
#ifdef DEBUG_QUEUE_MOVE
const char *tDBGId="ID:";
const char *tDBGVStartEnd="vStart/End:";
const char *tDBAccelSteps="accel/decel steps:";
const char *tDBGStartEndSpeed="st./end speed:";
const char *tDBGFlags="Flags:";
const char *tDBGJoinFlags="joinFlags:";
const char *tDBGDelta="Delta";
const char *tDBGDir="Dir:";
const char *tDBGFullSpeed="fullSpeed:";
const char *tDBGVMax="vMax:";
const char *tDBGAcceleration="Acceleration:";
const char *tDBGAccelerationPrim="Acceleration Prim:";
const char *tDBGRemainingSteps="Remaining steps:";
const char *tDBGAdvanceFull="advanceFull:";
const char *tDBGAdvanceRate="advanceRate:";
const char *tDBGLimitInterval="LimitInterval:";
const char *tDBGMoveDistance="Move distance on the XYZ space:";
const char *tDBGCommandedFeedrate="Commanded feedrate:";
const char *tDBGConstFullSpeedMoveTime="Constant full speed move time:";
#endif // DEBUG_QUEUE_MOVEconst char *="";
#ifdef DEBUG_DELTA_OVERFLOW
const char *tDBGDeltaOverflow="Delta overflow:";
#endif // DEBUG_DELTA_OVERFLOW
#ifdef DEBUG_SPLIT
const char *tDBGDeltaSeconds="Seconds:";
const char *tDBGDeltaZDelta="Z delta:";
const char *tDBGDeltaSegments="Segments:";
const char *tDBGDeltaNumLines="Num lines:";
const char *tDBGDeltaSegmentsPerLine="segments_per_line:";
const char *tDBGDeltaMaxDS="Max DS:";
const char *tDBGDeltaStepsPerSegment="Steps Per Segment:";
const char *tDBGDeltaVirtualAxisSteps="Virtual axis steps:";
#endif
#ifdef DEBUG_STEPCOUNT
const char *tDBGMissedSteps="Missed steps:";
#endif // DEBUG_STEPCOUNT
#if FEATURE_Z_PROBE
const char *tZProbe="Z-probe:";
const char *tZProbeAverage="Z-probe average height:";
const char *tZProbeZReset="Reset Z height";
const char *tZProbeState="Z-probe state:";
const char *tZProbeStartScript,Z_PROBE_START_SCRIPT;
const char *tZProbeEndScript,Z_PROBE_FINISHED_SCRIPT;
const char *tHitZProbe="Hit z-probe";
const char *tAutolevelReset="Autolevel matrix reset";
#endif
const char *tAutolevelEnabled="Autoleveling enabled";
const char *tAutolevelDisabled="Autoleveling disabled";
const char *tZProbeFailed="Z-probe failed";
const char *tZProbeMax="Z-probe max:";
const char *tZProbePrinterHeight="Printer height:";
//const char *="";
#if EEPROM_MODE==0
const char *tNoEEPROMSupport="No EEPROM support compiled.\r\n";
#else
#if FEATURE_Z_PROBE
const char *tZProbeHeight="Z-probe height";
const char *tZProbeOffsetX="Z-probe offset x";
const char *tZProbeOffsetY="Z-probe offset y";
const char *tZProbeSpeed="Z-probe speed";
const char *tZProbeSpeedXY="Z-probe x-y-speed";
const char *tZProbeX1="Z-probe X1";
const char *tZProbeY1="Z-probe Y1";
const char *tZProbeX2="Z-probe X2";
const char *tZProbeY2="Z-probe Y2";
const char *tZProbeX3="Z-probe X3";
const char *tZProbeY3="Z-probe Y3";
#endif
#if FEATURE_AUTOLEVEL
const char *tAutolevelActive="Autolevel active (1/0;";
#endif
const char *tConfigStoredEEPROM="Configuration stored to EEPROM.";
const char *tConfigLoadedEEPROM="Configuration loaded from EEPROM.";
const char *tEPRConfigResetDefaults="Configuration reset to defaults.";
const char *tEPRProtocolChanged="Protocol version changed, upgrading";
const char *tExtrDot="Extr.";
const char *tEPR0="EPR:0 ";
const char *tEPR1="EPR:1 ";
const char *tEPR2="EPR:2 ";
const char *tEPR3="EPR:3 ";
const char *tEPRBaudrate="Baudrate";
const char *tEPRFilamentPrinted="Filament printed [m]";
const char *tEPRPrinterActive="Printer active [s]";
const char *tEPRMaxInactiveTime="Max. inactive time [ms,0=off]";
const char *tEPRStopAfterInactivty="Stop stepper after inactivity [ms,0=off]";
const char *tEPRXHomePos="X home pos [mm]";
const char *tEPRYHomePos="Y home pos [mm]";
const char *tEPRZHomePos="Z home pos [mm]";
const char *tEPRXMaxLength="X max length [mm]";
const char *tEPRYMaxLength="Y max length [mm]";
const char *tEPRZMaxLength="Z max length [mm]";
const char *tEPRXBacklash="X backlash [mm]";
const char *tEPRYBacklash="Y backlash [mm]";
const char *tEPRZBacklash="Z backlash [mm]";
const char *tEPRMaxJerk="Max. jerk [mm/s]";
#if DRIVE_SYSTEM==3
const char *tEPRZAcceleration="Acceleration [mm/s^2]";
const char *tEPRZTravelAcceleration="Travel acceleration [mm/s^2]";
const char *tEPRZStepsPerMM="Steps per mm";
const char *tEPRZMaxFeedrate="Max. feedrate [mm/s]";
const char *tEPRZHomingFeedrate="Homing feedrate [mm/s]";

const char *tEPRDiagonalRodLength="Diagonal rod length [mm]";
const char *tEPRHorizontalRadius="Horizontal radius [mm]";
const char *tEPRSegmentsPerSecondPrint="Segments/s for printing";
const char *tEPRSegmentsPerSecondTravel="Segments/s for travel";

const char *tEPRTowerXOffset="Tower X endstop offset [steps]";
const char *tEPRTowerYOffset="Tower Y endstop offset [steps]";
const char *tEPRTowerZOffset="Tower Z endstop offset [steps]";

#else
const char *tEPRMaxZJerk="Max. Z-jerk [mm/s]";
const char *tEPRXStepsPerMM="X-axis steps per mm";
const char *tEPRYStepsPerMM="Y-axis steps per mm";
const char *tEPRZStepsPerMM="Z-axis steps per mm";
const char *tEPRXMaxFeedrate="X-axis max. feedrate [mm/s]";
const char *tEPRYMaxFeedrate="Y-axis max. feedrate [mm/s]";
const char *tEPRZMaxFeedrate="Z-axis max. feedrate [mm/s]";
const char *tEPRXHomingFeedrate="X-axis homing feedrate [mm/s]";
const char *tEPRYHomingFeedrate="Y-axis homing feedrate [mm/s]";
const char *tEPRZHomingFeedrate="Z-axis homing feedrate [mm/s]";
const char *tEPRXAcceleration="X-axis acceleration [mm/s^2]";
const char *tEPRYAcceleration="Y-axis acceleration [mm/s^2]";
const char *tEPRZAcceleration="Z-axis acceleration [mm/s^2]";
const char *tEPRXTravelAcceleration="X-axis travel acceleration [mm/s^2]";
const char *tEPRYTravelAcceleration="Y-axis travel acceleration [mm/s^2]";
const char *tEPRZTravelAcceleration="Z-axis travel acceleration [mm/s^2]";
#endif
const char *tEPROPSMode="OPS operation mode [0=Off,1=Classic,2=Fast]";
const char *tEPROPSMoveAfter="OPS move after x% retract [%]";
const char *tEPROPSMinDistance="OPS min. distance for fil. retraction [mm]";
const char *tEPROPSRetractionLength="OPS retraction length [mm]";
const char *tEPROPSRetractionBacklash="OPS retraction backlash [mm]";
const char *tEPRBedHeatManager="Bed Heat Manager [0-3]";
const char *tEPRBedPIDDriveMax="Bed PID drive max";
const char *tEPRBedPIDDriveMin="Bed PID drive min";
const char *tEPRBedPGain="Bed PID P-gain";
const char *tEPRBedIGain="Bed PID I-gain";
const char *tEPRBedDGain="Bed PID D-gain";
const char *tEPRBedPISMaxValue="Bed PID max value [0-255]";
const char *tEPRStepsPerMM="steps per mm";
const char *tEPRMaxFeedrate="max. feedrate [mm/s]";
const char *tEPRStartFeedrate="start feedrate [mm/s]";
const char *tEPRAcceleration="acceleration [mm/s^2]";
const char *tEPRHeatManager="heat manager [0-3]";
const char *tEPRDriveMax="PID drive max";
const char *tEPRDriveMin="PID drive min";
const char *tEPRPGain="PID P-gain/dead-time";
const char *tEPRIGain="PID I-gain";
const char *tEPRDGain="PID D-gain";
const char *tEPRPIDMaxValue="PID max value [0-255]";
const char *tEPRXOffset="X-offset [steps]";
const char *tEPRYOffset="Y-offset [steps]";
const char *tEPRStabilizeTime="temp. stabilize time [s]";
const char *tEPRRetractionWhenHeating="temp. for retraction when heating [C]";
const char *tEPRDistanceRetractHeating="distance to retract when heating [mm]";
const char *tEPRExtruderCoolerSpeed="extruder cooler speed [0-255]";
const char *tEPRAdvanceK="advance K [0=off]";
const char *tEPRAdvanceL="advance L [0=off]";

#endif
#if SDSUPPORT
// const char *tSDRemoved,UI_TEXT_SD_REMOVED;
// const char *tSDInserted,UI_TEXT_SD_INSERTED;
const char *tSDInitFail="SD init fail";
const char *tErrorWritingToFile="error writing to file";
const char *tBeginFileList="Begin file list";
const char *tEndFileList="End file list";
const char *tFileOpened="File opened:";
const char *tSpaceSizeColon=" Size:";
const char *tFileSelected="File selected";
const char *tFileOpenFailed="file.open failed";
const char *tSDPrintingByte="SD printing byte ";
const char *tNotSDPrinting="Not SD printing";
const char *tOpenFailedFile="open failed, File: ";
const char *tWritingToFile="Writing to file: ";
const char *tDoneSavingFile="Done saving file.";
const char *tFileDeleted="File deleted";
const char *tDeletionFailed="Deletion failed";
const char *tDirectoryCreated="Directory created";
const char *tCreationFailed="Creation failed";
const char *tSDErrorCode="SD errorCode:";
#endif

void Com::printWarningF(const char *(text)) {
    printF(tWarning);
    printF(text);
}
void Com::printWarningFLN(const char *(text)) {
    printF(tWarning);
    printFLN(text);
}
void Com::printInfoF(const char *(text)) {
    printF(tInfo);
    printF(text);
}
void Com::printInfoFLN(const char *(text)) {
    printF(tInfo);
    printFLN(text);
}

void Com::printErrorF(const char *(text)) {
    printF(tError);
    printF(text);
}
void Com::printErrorFLN(const char *(text)) {
    printF(tError);
    printFLN(text);
}
void Com::printFLN(const char *(text)) {
    printF(text);
    println();
}
void Com::printFLN(const char *(text),const char *msg) {
    printF(text);
    print(msg);
    println();
}

void Com::printF(const char *(ptr)) {
  char c;
  while ((c=*(ptr++)) != 0)
     serialRepetier.write(c);
}
void Com::printF(const char *(text),const char *msg) {
    printF(text);
    print(msg);
}

void Com::printF(const char *(text),int value) {
    printF(text);
    print(value);
}
void Com::printF(const char *(text),long value) {
    printF(text);
    print(value);
}
void Com::printF(const char *(text),unsigned long value) {
    printF(text);
    printNumber(value);
}
void Com::printFLN(const char *(text),int value) {
    printF(text);
    print(value);
    println();
}
void Com::printFLN(const char *(text),long value) {
    printF(text);
    print(value);
    println();
}
void Com::printFLN(const char *(text),unsigned long value) {
    printF(text);
    printNumber(value);
    println();
}
void Com::printFLN(const char *(text),float value,uint8_t digits) {
    printF(text);
    printFloat(value,digits);
    println();
}
void Com::printF(const char *(text),float value,uint8_t digits) {
    printF(text);
    printFloat(value,digits);
}

void Com::print(const char *text) {
  while(*text) {
    serialRepetier.write(*text++);
  }
}
void Com::print(long value) {
    if(value<0) {
        serialRepetier.write('-');
        value = -value;
    }
    printNumber(value);
}

void Com::printNumber(unsigned long n) {
  char buf[11]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[10];
  *str = '\0';
  do {
    unsigned long m = n;
    n /= 10;
    *--str = '0'+(m - 10 * n);
  } while(n);

  print(str);
}
void Com::printArrayFLN(const char *(text),float *arr,uint8_t n,uint8_t digits) {
    printF(text);
    for(uint8_t i=0; i<n; i++)
        printF(tSpace,arr[i],digits);
    println();
}
void Com::printArrayFLN(const char *(text),long *arr,uint8_t n) {
    printF(text);
    for(uint8_t i=0; i<n; i++)
        printF(tSpace,arr[i]);
    println();
}

void Com::printFloat(float number, uint8_t digits)
{
  if (isnan(number)) {
	printF(tNAN);
    return;
  }
  if (isinf(number)) {
	printF(tINF);
    return;
  }
  // Handle negative numbers
  if (number < 0.0)
  {
     print('-');
     number = -number;
  }
  // Round correctly so that print(1.999, 2) prints as "2.00"
  float rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  float remainder = number - (float)int_part;
  printNumber(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    print('.');

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print(toPrint);
    remainder -= toPrint;
  }
}

Com mCom;






