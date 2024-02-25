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

// UNTESTED: NEED NEW ROBOT CHASSIS FOR TESTING AND SENSOR MOUNTS
void LineFollowing::followLine(void) {
	while(!leftSensor.status() && !rightSensor.status()) {
		if (leftSensor.status())
			driveTrain.rotateLeft();
		else if (rightSensor.status())
			driveTrain.rotateRight();
		else
			driveTrain.forwards();
	}
	Serial.println("Both sensors triggered: stop.");
}
