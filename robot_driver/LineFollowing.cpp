#include "Arduino.h"
#include "LineFollowing.h"
#include "LineSensor.h"
#include "DriveTrain.h"
#include <HCSR04.h>
using namespace std;

LineFollowing::LineFollowing(
	const LineSensor &leftSensor, 
	const LineSensor &rightSensor, 
	const DriveTrain &driveTrain,
  const HCSR04 &uF
) : leftSensor(leftSensor), rightSensor(rightSensor), driveTrain(driveTrain), uF(uF) {
	// empty constructor
}

bool LineFollowing::rapidSwitching() {
  Serial.println("rapid switching");
	int rapidSwitchTime = 100;
	if (millis() - prevSwitchTime < rapidSwitchTime && prevSensor != currentSensor) {
		rapidSwitchCount++;
	}
	if (rapidSwitchCount >= 10) {
		Serial.println("end for rapid switching");
		rapidSwitchCount = 0;
		prevSensor = -1;
		currentSensor = -1;
		return false;
	}
	prevSensor = currentSensor;
	prevSwitchTime = millis();
	return true;
}

int LineFollowing::followLine(void) {
	Serial.println("in line following");
	bool run = true;
	while (run) {
		if (leftSensor.status() && rightSensor.status()){
				Serial.println("Found tee.");
				run = false;
		}
		else if (leftSensor.status()) {
			driveTrain.rotateLeftPivot();
			currentSensor = 0;
			//run = rapidSwitching();
		} else if (rightSensor.status()) {
			driveTrain.rotateRightPivot();
			currentSensor = 1;
			//run = rapidSwitching();
		} else if (AtFrontWall(uF)){
      		Serial.println("Found wall.");
     		Serial.println(uF.dist());
		  	run = false;
		} else {
			driveTrain.forwards();
			rapidSwitchCount = 0;
			prevSensor = -1;
			currentSensor = -1;
		}
	}
	driveTrain.stop();
	Serial.println("Stop here");
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
	driveTrain.stop();
	// Serial.println("detected line");
	delay(1000);
	// rotate perpendicular to it
	if (rightSensor.status()) {
		while (!leftSensor.status())
			driveTrain.leftMotorOn();
	} else if (leftSensor.status()) {
		while (!rightSensor.status())
			driveTrain.rightMotorOn();
	}
	driveTrain.stop();
	// Serial.println("oriented to line");
	delay(1000);
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

bool LineFollowing::AtFrontWall(const HCSR04& uF, float thresh) {
  if (micros() - lastTime < cycleDur) {  // wait for recommended measurement cycle
    return false;
  }
  else {  // send trigger next
    lastTime = micros();
    float d = uF.dist();
    //  Serial.println(d);
    if (d > 3.0 && d != 0) 
      return false;
    else 
      return true;
  }
  
}
