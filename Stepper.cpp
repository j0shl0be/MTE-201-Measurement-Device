#include <Arduino.h>
#include "Stepper.h"
#include "Constants.h"

// Class constructor
Stepper::Stepper(int _dirPin, int _stepPin, float _reductionRatio) { 
    mSteps = 1; // Microsteps, i.e. 1, 2, 4, 8, 16 etc.
    stepsPerRev = 200;
    timePerStep = 2000; // Delay per step (in microseconds)
    steps = 0; // Counter for the number of steps
    dirPin = _dirPin;
    stepPin = _stepPin;
    reductionRatio = _reductionRatio;
}

void Stepper::initialize() {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    digitalWrite(dirPin, HIGH);
}

void Stepper::moveTest() {
    timePerStep = 2000;
    for (int i = 0; i < 3; i++) { // Perform tests at 3 diff speeds
        spinRevs(0.125, HIGH);
        spinRevs(0.125, LOW);
        timePerStep -= 200;
        delay(200);
    }
}

void Stepper::setHome(int limitSwitch, bool direction) {
    pinMode(limitSwitch, INPUT);
    timePerStep = 400;

    while ((digitalRead(limitSwitch) == LOW)) {
        spinSteps(1, direction);
    }

    delay(1000);
    spinSteps(32*mSteps, !direction);
    delay(1000);
    timePerStep = 2000;

    while ((digitalRead(limitSwitch) == LOW)) {
        spinSteps(1, direction);
    }
    steps = 0; //set the steps count to 0
}

float Stepper::readRevs() {
    return steps/(stepsPerRev*reductionRatio);
}

void Stepper::setMicrosteps(int microsteps) {
    mSteps = microsteps;
    stepsPerRev = mSteps*200;
}

void Stepper::setTimePerStep(int time) {
    timePerStep = time;
}

void Stepper::resetSteps() {
    steps = 0;
}

void Stepper::spinSteps(int nbOfSteps, bool direction) {
    digitalWrite(dirPin, direction);
    
    if (direction) {
        for (int i = 0; i < nbOfSteps; i++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(timePerStep);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(timePerStep);

            steps--; // Update counter
        }
    }
    else {
        for (int i = 0; i < nbOfSteps; i++) {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(timePerStep);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(timePerStep);

            steps++; // Update counter
        }    
    }
}

void Stepper::spinRevs(float nbOfTurns, bool direction) {
    spinSteps(stepsPerRev*nbOfTurns*reductionRatio, direction);
}

void Stepper::moveDist(float dist_mm, bool direction) {
    int tempSteps = (dist_mm/REVS_TO_DIST)*stepsPerRev;
    spinSteps(tempSteps, direction);
}

void Stepper::moveUnitl(int limitSwitch, bool direction) {
    digitalWrite(DIR_1_PIN,direction);
    timePerStep = 200;
    while(digitalRead(limitSwitch) == LOW){
        spinSteps(1, direction);}
}

int Stepper::getSteps() {
    return this->steps;
}

float Stepper::stepToLength(){
    float tempLength = this->steps*SLOPE + CONSTANT_ADD;
    return tempLength;
}