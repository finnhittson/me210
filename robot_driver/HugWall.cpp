#include "HugWall.h"
#include "DriveTrain.h"
#include "LineFollowing.h"
#include <HCSR04.h>
#include "Arduino.h"
using namespace std;

HugWall::HugWall(const DriveTrain& driveTrain, const HCSR04& uFront, const HCSR04& uLeft, const HCSR04& uRight, const LineFollowing& lineFollower) : driveTrain(driveTrain), uFront(uFront), uLeft(uLeft), uRight(uRight), lineFollower(lineFollower) {
	// empty
}

void HugWall::DoHugWalling(int mode) {
	float dPrev = 0.0;
	while (!lineFollower.AtFrontWall(uFront, 3.0))
	{
		if (micros() - lineFollower.lastTime < lineFollower.cycleDur) {  // wait for recommended measurement cycle
		}
		else if (digitalRead(mode)) {  // LEFT FIELD // send trigger next
			lineFollower.lastTime = micros();
			float d = uRight.dist();
			//  Serial.println(d);
			if (d - dPrev > 0) {
				driveTrain.leftMotorOn();
				driveTrain.rightMotorOff();
				Serial.println("right");
				delay(250);
			}
			else if (d - dPrev < 0) {
				driveTrain.rightMotorOn();
				driveTrain.leftMotorOff();
				Serial.println("left");
				delay(250);
			}
			driveTrain.forwards();
			delay(250);
			dPrev = d;
		}
		else  { // send trigger next
			lineFollower.lastTime = micros();
			float d = uLeft.dist();
			//  Serial.println(d);
			if (d - dPrev > 0) {
				driveTrain.rightMotorOn();
				driveTrain.leftMotorOff();
				Serial.println("left");
				delay(250);
			}
			else if (d - dPrev < 0) {
				driveTrain.leftMotorOn();
				driveTrain.rightMotorOff();
				Serial.println("right");
				delay(250);
			}
			driveTrain.forwards();
			delay(250);
			dPrev = d;
		}
	}
	Serial.println("stopped hug walling");
}