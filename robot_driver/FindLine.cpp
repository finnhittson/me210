#include "FindLine.h"
#include "DriveTrain.h"
#include "LimitSwitch.h"
#include "LineSensor.h"
#include "Arduino.h"
using namespace std;

FindLine::FindLine(
	const DriveTrain &driveTrain,
	const LineSensor &leftSensor,
	const LineSensor &rightSensor,
	const LimitSwitch &topLeft,
	const LimitSwitch &front,
	const LimitSwitch &topRight
	) : driveTrain(driveTrain),
		leftSensor(leftSensor),
		rightSensor(rightSensor),
		topLeft(topLeft),
		front(front),
		topRight(topRight) {
	// empty
}

bool FindLine::detectedBarrier() {
	if (topLeft.status()) {
		sensor = 0;
		return true;
	} else if (front.status()) {
		sensor = 1;
		return true;
	} else if (topRight.status()) {
		sensor = 2;
		return true;
	}
	return false;
}

void FindLine::driveState() {
	driveTrain.forwards();
	if (detectedBarrier())
		state = ROTATE90;
	else if (leftSensor.status())
		state = ROTATELEFT;
	else if (rightSensor.status())
		state = ROTATERIGHT;
}

void FindLine::rotate90State() {
	if (sensor == 0)
		driveTrain.rotate90Right();
	else if (sensor == 1)
		driveTrain.rotate180();
	else if (sensor == 2)
		driveTrain.rotate90Right();
	state = DRIVE;
}

void FindLine::rotateLeftState() {
	while (leftSensor.status() || !rightSensor.status())
		driveTrain.rotateLeft();
	state = LINEFOLLOWING;
}

void FindLine::rotateRightState() {
	while (!leftSensor.status() || rightSensor.status())
		driveTrain.rotateRight();
	state = LINEFOLLOWING;
}

void FindLine::findLine() {
	while (state != LINEFOLLOWING) {
		if (state == DRIVE)
			driveState();
		else if (state == ROTATE90)
			rotate90State();
		else if (state == ROTATELEFT)
			rotateLeftState();
		else if (state == ROTATERIGHT)
			rotateRightState();
	}
	Serial.println("Entering line following mode.");
}