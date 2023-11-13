#include <Arduino.h>
#include "Stepper.h"
#include "Constants.h"

// put function declarations here:
void waitButtonPress(int);
bool checkButtonPress(int);
void prepMeasure();
void measureSteps(int);
float stepToLength(int);


// Create stepper motor objects
//need to ask yifei what the reduction ratio is for this
Stepper motion(DIR_1_PIN, STP_1_PIN, MOTION_REDUCTION);

void setup() {
  // comunicate with computer
  Serial.begin(9600);
  
  //INitialize inputs
  pinMode(LIMIT_SWITCH_PIN, INPUT);
  pinMode(MEASURE_BUTTON_PIN, INPUT);
  pinMode(RESET_BUTTON_PIN, INPUT);
  
  //Initialize motor
  motion.initialize();
  motion.setMicrosteps(MOTION_MICROSTEPS);

  //wait for starting the system
  waitButtonPress(RESET_BUTTON_PIN);
  delay(500);
}

void loop() {
  //reset the motor to zero
  prepMeasure();

  // put your main code here, to run repeatedly:
  waitButtonPress(MEASURE_BUTTON_PIN);
  measureSteps(LIMIT_SWITCH_PIN);

  // wait for the reset button to be pressed to run again
  waitButtonPress(RESET_BUTTON_PIN);
  delay(500);
}

//useful funtions
void waitButtonPress(int button){
  //waits for the press and release of a button
  while(digitalRead(button) == LOW){
    delay(10);}
  while (digitalRead(button) == HIGH){
    delay(10);}
}

bool checkButtonPress(int button){
  //checks if a button is pressed
  return (digitalRead(button) == HIGH);
}

void prepMeasure(){
  //homes the cariage, resets steps then moves it back into place to measure. 
  motion.setHome(LIMIT_SWITCH_PIN, BACKWARD);
  delay(500);
  motion.setTimePerStep(200);
  motion.moveDist(DIST_MEASURE_MAX, FORWARD);
}

void measureSteps(int limitSwitch){
  //get initial steps reading, measure length then poll steps again
  motion.moveUnitl(limitSwitch, BACKWARD);

  Serial.print("Measured ");
  Serial.print(motion.getSteps());
  Serial.print(" steps measured");
  Serial.println("Length: ");
  Serial.print(motion.stepToLength(), 1);

  delay(500);
  
  // move off of block after getting measurement
  motion.moveDist(3,FORWARD);
}