#define USE_TIMER_1     true

#include <TimerInterrupt.h>
#include <ISR_Timer.h>
#include "Motor.h"
#include "DriveTrain.h"

const int inA = 8;
const int outA = 7;
const int enableA = 9;

const int inB = 13;
const int outB = 12;
const int enableB = 10;

int duty = 200; // 0 - 255
bool driveForwards = true;

Motor LeftMotor(inA, outA, enableA);
Motor RightMotor(inB, outB, enableB);
DriveTrain FullDriveTrain(LeftMotor, RightMotor, duty);

void setup() {
	Serial.begin(9600);

	// pinout for left motor
	pinMode(inA, OUTPUT);
	pinMode(outA, OUTPUT);
	pinMode(enableA, OUTPUT);

	// pinout for right motor
	pinMode(inB, OUTPUT);
	pinMode(outB, OUTPUT);
	pinMode(enableB, OUTPUT);
}

void loop() {
	analogWrite(enableB, duty);
	digitalWrite(inB, HIGH);
	digitalWrite(outB, LOW);
}

// int delayTime = 1000;
// FullDriveTrain.forwards();
// delay(delayTime);
// FullDriveTrain.backwards();
// delay(delayTime);
// FullDriveTrain.rotateLeft();
// delay(delayTime);
// FullDriveTrain.rotateRight();
// delay(delayTime);
// FullDriveTrain.rightMotorOn();
// FullDriveTrain.leftMotorOff();
// delay(delayTime);
// FullDriveTrain.rightMotorOff();
// FullDriveTrain.leftMotorOn();
// delay(delayTime);