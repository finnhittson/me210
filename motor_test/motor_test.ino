#include "Motor.h"
#include "DriveTrain.h"
#include "LineSensor.h"
#include "LineFollowing.h"
#include "LimitSwitch.h"
#include "FindLine.h"
#include <Servo.h>

// motor definitions
const int inA = 8;
const int outA = 7;
const int enable = 9;
const int inB = 13;
const int outB = 12;
int duty = 200; // 0 - 255
Motor leftMotor(inA, outA, enable, duty);
Motor rightMotor(inB, outB, enable, duty);
DriveTrain driveTrain(leftMotor, rightMotor, duty);

// line sensor definitions
const int leftSensorPin = A0;
const int rightSensorPin = A1;
const int threshold = 30;
LineSensor leftSensor(threshold, leftSensorPin);
LineSensor rightSensor(threshold, rightSensorPin);

// line following definition
LineFollowing lineFollow(leftSensor, rightSensor, driveTrain);

// limit switch definitions
const int limitSwitch1Pin = 4;
const int limitSwitch2Pin = 5;
const int limitSwitch3Pin = 6;
LimitSwitch topLeft(limitSwitch1Pin);
LimitSwitch front(limitSwitch2Pin);
LimitSwitch topRight(limitSwitch3Pin);

// find the line definition
FindLine findLine(driveTrain, leftSensor, rightSensor, topLeft, front, topRight);

// servo definitions
const int celebrationServoPin = 10;
const int dartServoPin = 11;
Servo celebrationServo;
Servo dartServo;

void setup() {
	Serial.begin(9600);

	// pin configuration for left motor
	pinMode(inA, OUTPUT);
	pinMode(outA, OUTPUT);
	pinMode(enable, OUTPUT);

	// pin configuration for right motor
	pinMode(inB, OUTPUT);
	pinMode(outB, OUTPUT);
	pinMode(enable, OUTPUT);

	// pin configuration for line sensors
	pinMode(leftSensorPin, INPUT);
	pinMode(rightSensorPin, INPUT);

	// pin configuration for limit switches
	pinMode(limitSwitch1Pin, INPUT_PULLUP); 
	pinMode(limitSwitch2Pin, INPUT_PULLUP);
	pinMode(limitSwitch3Pin, INPUT_PULLUP);

	// pin configuration for servos
	celebrationServo.attach(celebrationServoPin);
	dartServo.attach(dartServoPin);
}

void loop() {
	leftMotor.forwards();
	rightMotor.forwards();
	driveTrain.forwards();
	bool status = leftSensor.status();
	status = rightSensor.status();
	lineFollow.followLine();
	status = topLeft.status();
	status = front.status();
	status = topRight.status();
	findLine.findLine();
}