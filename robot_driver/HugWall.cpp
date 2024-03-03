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
	int goTime = 250;
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
				delay(goTime);
			}
			else if (d - dPrev < 0) {
				driveTrain.rightMotorOn();
				driveTrain.leftMotorOff();
				Serial.println("left");
				delay(goTime);
			}
			driveTrain.forwards();
			delay(goTime);
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
				delay(goTime);
			}
			else if (d - dPrev < 0) {
				driveTrain.leftMotorOn();
				driveTrain.rightMotorOff();
				Serial.println("right");
				delay(goTime);
			}
			driveTrain.forwards();
			delay(goTime);
			dPrev = d;
		}
	}
	Serial.println("stopped hug walling");
}

void HugWall::alternativeWallHugging(int mode) {
	float closeThreshold = 8.0;
	float farThreshold = 12.0;
	int goTime = 100;
	int rotateTime = 10;
	int stopTime = 1000;
	while (!lineFollower.AtFrontWall(uFront, 3.0)) {
		if (micros() - lineFollower.lastTime < lineFollower.cycleDur) {  
			// wait for recommended measurement cycle
		}
		else if (digitalRead(mode)) {  // LEFT FIELD // send trigger next
			Serial.println();
			lineFollower.lastTime = micros();
			float d = uRight.dist();
			Serial.println(d);
			//Serial.println(d);
			//  Serial.println(d);
			if (d <= closeThreshold) {
				driveTrain.rightMotorOn();
				driveTrain.leftMotorOff();
				Serial.println("left");
				delay(rotateTime);
				driveTrain.rightMotorOff();	
				delay(stopTime);
				driveTrain.forwards();
				delay(goTime);
				driveTrain.stop();
				delay(stopTime);
			}
			else if (d >= farThreshold) {
				driveTrain.leftMotorOn();
				driveTrain.rightMotorOff();
				Serial.println("right");
				delay(rotateTime);
				driveTrain.leftMotorOff();
				delay(stopTime);
				driveTrain.forwards();
				delay(goTime);
				driveTrain.stop();
				delay(stopTime);
			}
			else {
				driveTrain.forwards();
				delay(goTime);
				driveTrain.stop();
				delay(stopTime);
			}
		}
		else  { // send trigger next
			lineFollower.lastTime = micros();
			float d = uLeft.dist();
			//  Serial.println(d);
			if (d <= closeThreshold) {
				driveTrain.rightMotorOn();
				driveTrain.leftMotorOff();
				Serial.println("left");
				delay(goTime);
				driveTrain.forwards();
				delay(goTime);
				driveTrain.stop();
				delay(stopTime);
			}
			else if (d >= farThreshold) {
				driveTrain.leftMotorOn();
				driveTrain.rightMotorOff();
				Serial.println("right");
				delay(goTime);
				driveTrain.forwards();
				delay(goTime);
				driveTrain.stop();
				delay(stopTime);
			}
			else {
				driveTrain.forwards();
				delay(goTime);
				driveTrain.stop();
				delay(stopTime);
			}
		}
	}
	Serial.println("stopped hug walling");
}