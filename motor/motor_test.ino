#define USE_TIMER_1     true

#include <TimerInterrupt.h>
#include <ISR_Timer.h>
#include "Motor.h"
#include "DriveTrain.h"

const int leftMotorPin1 = 8;
const int leftMotorPin2 = 9;
const int leftEnablePin = 10;

const int rightMotorPin1 = 12;
const int rightMotorPin2 = 13;
const int rightEnablePin = 11;

int speed = 100;
bool driveForwards = true;
int freq = 1;

Motor LeftMotor(leftMotorPin1, leftMotorPin2, leftEnablePin);
Motor RightMotor(rightMotorPin1, rightMotorPin2, rightEnablePin);
DriveTrain FullDriveTrain(LeftMotor, RightMotor, speed);

void setup() {  
	Serial.begin(9600);

	// pinout for left motor
	pinMode(leftMotorPin1, OUTPUT);
	pinMode(leftMotorPin2, OUTPUT);
	pinMode(leftEnablePin, OUTPUT);

	// pinout for right motor
	pinMode(rightMotorPin1, OUTPUT);
	pinMode(rightMotorPin2, OUTPUT);
	pinMode(rightEnablePin, OUTPUT);

	ITimer1.init();
	if (ITimer1.attachInterrupt(freq, TimerHandler))
		Serial.println("Starting  ITimer1 OK, millis() = " + String(millis()));
	else
		Serial.println("Can't set ITimer1. Select another freq. or timer");
}  

void loop() {
	// empty loop
}

void TimerHandler() {
	if (driveForwards)
		FullDriveTrain.forwards();
	else
		FullDriveTrain.backwards();
	driveForwards = !driveForwards;
}

