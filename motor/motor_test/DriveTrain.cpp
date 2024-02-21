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
	this->speed = motorSpeed;
}

void DriveTrain::setSpeed(int newSpeed) {
	this->speed = newSpeed;
}

int DriveTrain::getSpeed() const {
	return speed;
}

void DriveTrain::forwards(void) {
	leftMotor.setSpeed(speed);
	rightMotor.setSpeed(speed);
	leftMotor.spinForwards();
	rightMotor.spinForwards();
}

void DriveTrain::backwards(void) {
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
	leftMotor.stop();
}

void DriveTrain::leftMotorOn(void) {
	leftMotor.setSpeed(speed);
	leftMotor.spinForwards();
}

void DriveTrain::rightMotorOff(void) {
	rightMotor.stop();
}

void DriveTrain::rightMotorOn(void) {
	rightMotor.setSpeed(speed);
	rightMotor.spinForwards();
}