#include "Arduino.h"
#include "LineFollowing.h"
#include "LineSensor.h"
#include "C:\Users\hitts\Documents\ee118\final_project\me210\motor\motor_test\DriveTrain.h"
using namespace std;

LineFollowing::LineFollowing() {
	// empty constructor
}

LineFollowing::LineFollowing(
	const LineSensor &leftSensor, 
	const LineSensor &rightSensor, 
	const DriveTrain &driveTrain
) : driveTrain(driveTrain), leftSensor(leftSensor), rightSensor(rightSensor) {
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
