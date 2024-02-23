//max's test comment
#define USE_TIMER_1     true

#include <TimerInterrupt.h>
#include <ISR_Timer.h>
#include "Motor.h"
#include "DriveTrain.h"

const int leftMotorPin1 = 9;
const int leftMotorPin2 = 10;

const int rightMotorPin1 = 5;
const int rightMotorPin2 = 6;
const int potPin = A0;

int speed = 100;
bool driveForwards = true;

Motor LeftMotor(leftMotorPin1, leftMotorPin2);
Motor RightMotor(rightMotorPin1, rightMotorPin2);
DriveTrain FullDriveTrain(LeftMotor, RightMotor, speed);

void setup() {
	Serial.begin(9600);

	// pinout for left motor
	pinMode(leftMotorPin1, OUTPUT);
	pinMode(leftMotorPin2, OUTPUT);

	// pinout for right motor
	pinMode(rightMotorPin1, OUTPUT);
	pinMode(rightMotorPin2, OUTPUT);
}

void loop() {
	FullDriveTrain.forwards();
	delay(2000);
	FullDriveTrain.backwards();
	delay(2000);
	FullDriveTrain.rotateLeft();
	delay(2000);
	FullDriveTrain.rotateRight();
	delay(2000);
	FullDriveTrain.rightMotorOn();
	FullDriveTrain.leftMotorOff();
	delay(2000);
	FullDriveTrain.rightMotorOff();
	FullDriveTrain.leftMotorOn();
	delay(2000);
}