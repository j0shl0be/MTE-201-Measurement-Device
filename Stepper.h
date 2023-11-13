#include "Constants.h"
#ifndef STEPPER_H
#define STEPPER_H

class Stepper {

private:

    float reductionRatio;
    int mSteps; // Microsteps, i.e. 1, 2, 4, 8, 16 etc.
    int stepsPerRev; // Microsteps per full revolution
    int timePerStep; // Delay per step (in microseconds)
    int steps; // Counter for the number of steps
    int dirPin;
    int stepPin;
    
public:

    // Default constructor
    Stepper(int _dirPin, int _stepPin, float _reductionRatio);

    // Boot sequences
    void initialize();
    void moveTest();
    void setHome(int limitSwitch, bool direction);

    // Running methods ------------------------------------------------------------------------------

    float readRevs(); // Returns the current number of turns since reset
    void setMicrosteps(int microsteps); // sets micrstepping resolution
    void setTimePerStep(int time); // in microseconds
    void resetSteps(); // Resets the step counter
    void spinSteps(int nbOfSteps, bool direction); // Spins by n steps
    void spinRevs(float nbOfTurns, bool direction); // Spins n revolutions (can be decimal)
    void moveDist(float dist_mm, bool direction); // Moves n mm 
    void moveUnitl(int limitSwitch, bool direction); // Moves until switch is hit

    // Data Return ------------------------------------------------------------------------------------
    
    int getSteps(); // Returns the number of steps
    float stepToLength(); // returns length of movement from step count.
};

#endif