#ifndef CONSTANTS_H
#define CONSTANTS_H

// Misc
const int DIST_MEASURE_MAX = 220;//safe distance from home to measure from, dont extend much more than this
const bool FORWARD = 0;
const bool BACKWARD = !FORWARD;

// Motor info
const int MOTION_MICROSTEPS = 16;

const float REVS_TO_DIST = 39.37; // distance per full revolution of the guide motor (mm)
const int MOTION_REDUCTION = 1; // Reduction ration for the spindle

// Board inputs
const int LIMIT_SWITCH_PIN = 27;
const int RESET_BUTTON_PIN = 16;
const int MEASURE_BUTTON_PIN = 19;
const int STOP_BUTTON_PIN = 32;
// button pins : 16, 17, 18, 19
// potentiomietr : 23
// right limit switch : 27
// Left Limit switch : 32

// Motor pins
const int DIR_1_PIN = 14;
const int STP_1_PIN = 26;
const int DIR_2_PIN = 33;
const int STP_2_PIN = 32;
// Motor Right - Dir 14 , Step 26
// Motor Left - Dir 
#endif
