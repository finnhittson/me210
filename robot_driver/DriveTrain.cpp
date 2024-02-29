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
	leftMotor.forwards();
	rightMotor.forwards();
}

void DriveTrain::backwards(void) {
	leftMotor.setSpeed(speed);
	rightMotor.setSpeed(speed);
	leftMotor.backwards();
	rightMotor.backwards();
}

void DriveTrain::rotateLeft(void) {
	leftMotor.setSpeed(speed);
	rightMotor.setSpeed(speed);
	leftMotor.backwards();
	rightMotor.forwards();
}

void DriveTrain::rotateRight(void) {
	leftMotor.setSpeed(speed);
	rightMotor.setSpeed(speed);
	leftMotor.forwards();
	rightMotor.backwards();
}

void DriveTrain::rotate90Right() {
	rotateRight();
	delay(2500);
	stop();
}

void DriveTrain::rotate90Left() {
	rotateLeft();
	delay(2500);
	stop();
}

void DriveTrain::rotate180() {
	rightMotorOn();
	delay(100000);
	stop();
}

void DriveTrain::stop() {
	leftMotor.stop();
	rightMotor.stop();
}

void DriveTrain::leftMotorOff(void) {
	leftMotor.stop();
}

void DriveTrain::leftMotorOn(void) {
	leftMotor.setSpeed(speed);
	leftMotor.forwards();
}

void DriveTrain::rightMotorOff(void) {
	rightMotor.stop();
}

void DriveTrain::rightMotorOn(void) {
	rightMotor.setSpeed(speed);
	rightMotor.forwards();
}
