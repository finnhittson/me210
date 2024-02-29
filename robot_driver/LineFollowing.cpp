#include "Arduino.h"
#include "LineFollowing.h"
#include "LineSensor.h"
#include "DriveTrain.h"
using namespace std;

LineFollowing::LineFollowing(
	const LineSensor &leftSensor, 
	const LineSensor &rightSensor, 
	const DriveTrain &driveTrain
) : leftSensor(leftSensor), rightSensor(rightSensor), driveTrain(driveTrain) {
	// empty constructor
}

bool LineFollowing::rapidSwitching() {
	int rapidSwitchTime = 100;
	if (millis() - prevSwitchTime < rapidSwitchTime && prevSensor != currentSensor) {
		rapidSwitchCount++;
	}
	if (rapidSwitchCount >= 10) {
		return false;
	}
	prevSensor = currentSensor;
	prevSwitchTime = millis();
	return true;
}

int LineFollowing::followLine(void) {
	bool run = true;
	while (run) {
		if (leftSensor.status()) {
			driveTrain.rotateLeft();
			currentSensor = 0;
			run = rapidSwitching();
		} else if (rightSensor.status()) {
			driveTrain.rotateRight();
			currentSensor = 1;
			run = rapidSwitching();
		} else if (leftSensor.status() && rightSensor.status()){
			run = false;
		} else {
			driveTrain.forwards();
			rapidSwitchCount = 0;
			prevSensor = -1;
			currentSensor = -1;
		}
	}
	driveTrain.stop();
	return 0;
}

int LineFollowing::findLine(int mode) {	
	// find a line
	bool run = true;
	while (run) {
		driveTrain.forwards();
		if (rightSensor.status() || leftSensor.status()) {
			driveTrain.stop();
			delay(1000);
			run = false;
		}
	}
	// rotate perpendicular to it
	if (rightSensor.status()) {
		// Serial.println("right sensor triggered");
		while (!leftSensor.status())
			driveTrain.leftMotorOn();
	} else if (leftSensor.status()) {
		// Serial.println("left sensor triggered");
		while (!rightSensor.status())
			driveTrain.rightMotorOn();
	}

	// rotate onto it depending on mode
	int driveTime = 100;
	int rotateTime = 1500;
	if (mode) {
		// driveTrain.forwards();
		// delay(driveTime);
		driveTrain.rotateRight();
		delay(rotateTime);
	}
	else {
		// driveTrain.forwards();
		// delay(driveTime);
		driveTrain.rotateLeft();
		delay(rotateTime);
	}
	driveTrain.stop();
	return 0;
}


