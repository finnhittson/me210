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
		Serial.println(rapidSwitchCount);
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
	return 1;
}

int LineFollowing::findLine(int mode) {
	bool run = true;
	int rotateTime = 1500;
	while (run) {
		driveTrain.forwards();
		if (rightSensor.status()) {
			Serial.println("right sensor triggered");
			driveTrain.stop();
			run = false;
		}
		if (leftSensor.status()) {
			Serial.println("left sensor triggered");
			driveTrain.stop();
			run = false;
		}
	}
	if (rightSensor.status()) {
		Serial.println("right sensor triggered");
		while (!leftSensor.status())
			driveTrain.leftMotorOn();
		if (mode) {
			driveTrain.rotateRight();
			delay(rotateTime);
		}
		else {
			driveTrain.rotateLeft();
			delay(rotateTime);
		}
	} else if (leftSensor.status()) {
		Serial.println("left sensor triggered");
		while (!rightSensor.status())
			driveTrain.rightMotorOn();
		if (mode) {
			driveTrain.rotateRight();
			delay(rotateTime);
		}
		else {
			driveTrain.rotateLeft();
			delay(rotateTime);
		}
	}
	driveTrain.stop();
	return 1;
}


