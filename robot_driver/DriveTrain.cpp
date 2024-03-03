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
	int dutyLeft,
	int dutyRight
	) : leftMotor(leftMotor), rightMotor(rightMotor) {
	this->dutyLeft = dutyLeft;
	this->dutyRight = dutyRight;
}

void DriveTrain::setLeftDuty(int newLeftDuty) {
	this->dutyLeft = newLeftDuty;
}

void DriveTrain::setRightDuty(int newRightDuty) {
	this->dutyRight = newRightDuty;
}

void DriveTrain::forwards(void) {
	leftMotor.setSpeed(dutyLeft);
	rightMotor.setSpeed(dutyRight);
	leftMotor.forwards();
	rightMotor.forwards();
}

void DriveTrain::backwards(void) {
	leftMotor.setSpeed(dutyLeft);
	rightMotor.setSpeed(dutyRight);
	leftMotor.backwards();
	rightMotor.backwards();
}

void DriveTrain::rotateLeft(void) {
	leftMotor.setSpeed(dutyLeft);
	rightMotor.setSpeed(dutyRight);
	leftMotor.backwards();
	rightMotor.forwards();
}

void DriveTrain::rotateRight(void) {
	leftMotor.setSpeed(dutyLeft);
	rightMotor.setSpeed(dutyRight);
	leftMotor.forwards();
	rightMotor.backwards();
}

void DriveTrain::rotate90Right() {
	rotateRight();
	delay(2000);
	// delay(2200); for matching duty of 80
	stop();
}

void DriveTrain::rotate90Left() {
	rotateLeft();
	delay(1900);
	// delay(2200);
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
	leftMotor.setSpeed(dutyLeft);
	leftMotor.forwards();
}

void DriveTrain::rightMotorOff(void) {
	rightMotor.stop();
}

void DriveTrain::rightMotorOn(void) {
	rightMotor.setSpeed(dutyRight);
	rightMotor.forwards();
}
