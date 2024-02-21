#include "DriveTrain.h"
#include "Motor.h"
#include "Arduino.h"
using namespace std;

DriveTrain::DriveTrain() {
	// empty constructor
}

DriveTrain::DriveTrain(
	const Motor &leftMotor, 
	const Motor &rightMotor, 
	int motorSpeed
	) : leftMotor(leftMotor), rightMotor(rightMotor) {
	speed = motorSpeed;
}

int DriveTrain::getSpeed() const {
	return speed;
}

void DriveTrain::forwards(void) {
	Serial.println("Driving forwards");
	leftMotor.setSpeed(speed);
	rightMotor.setSpeed(speed);
	leftMotor.spinForwards();
	rightMotor.spinForwards();
}

void DriveTrain::backwards(void) {
	Serial.println("Driving backwards");
	leftMotor.setSpeed(speed);
	rightMotor.setSpeed(speed);
	leftMotor.spinBackwards();
	rightMotor.spinBackwards();
}

void DriveTrain::rotateLeft(void) {
	leftMotor.setSpeed(speed);
	rightMotor.setSpeed(speed);
	leftMotor.spinBackwards();
	rightMotor.spinForwards();
}

void DriveTrain::rotateRight(void) {
	leftMotor.setSpeed(speed);
	rightMotor.setSpeed(speed);
	leftMotor.spinForwards();
	rightMotor.spinBackwards();
}

void DriveTrain::leftMotorOff(void) {
	leftMotor.setSpeed(0);
}

void DriveTrain::leftMotorOn(void) {
	leftMotor.setSpeed(speed);
}

void DriveTrain::rightMotorOff(void) {
	rightMotor.setSpeed(0);
}

void DriveTrain::rightMotorOn(void) {
	rightMotor.setSpeed(speed);
}