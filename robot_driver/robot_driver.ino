#include "Motor.h"
#include "DriveTrain.h"
#include "LineSensor.h"
#include "LineFollowing.h"
#include "LimitSwitch.h"
#include "FindLine.h"
#include <Servo.h>

// motor definitions
const int inLeft = 8;
const int outLeft = 7;
const int enable = 9;
const int inRight = 13;
const int outRight = 12;
int duty = 100;  // 0 - 255
Motor leftMotor(inLeft, outLeft, enable, duty);
Motor rightMotor(inRight, outRight, enable, duty);
DriveTrain driveTrain(leftMotor, rightMotor, duty);

// line sensor definitions
const int leftSensorPin = A0;
const int rightSensorPin = A1;
const int threshold = 80;
LineSensor leftSensor(threshold, leftSensorPin);
LineSensor rightSensor(threshold, rightSensorPin);

// line following definition
LineFollowing lineFollow(leftSensor, rightSensor, driveTrain);

// mode swtich
const int modePin = A5;
int success = 0;
int findLine = 0;
void setup() {
	Serial.begin(9600);

	// pin configuration for left motor
	pinMode(inLeft, OUTPUT);
	pinMode(outLeft, OUTPUT);
	pinMode(enable, OUTPUT);

	// pin configuration for right motor
	pinMode(inRight, OUTPUT);
	pinMode(outRight, OUTPUT);

	// pin configuration for line sensors
	pinMode(leftSensorPin, INPUT);
	pinMode(rightSensorPin, INPUT);

	pinMode(modePin, INPUT_PULLUP);
}

void loop() {
	
}

// Serial.println(digital(modePin));
	// if (findLine != 1) {
	// 	findLine = lineFollow.findLine(digitalRead(modePin));
	// 	Serial.println("run once");
	// 	driveTrain.stop();
	// }

	// if (success != 2) {
	// 	success += lineFollow.followLine();
	// 	Serial.println(success);
	// 	Serial.println("Tee detected.");
	// 	if (success == 1) {
	// 		Serial.print("first tee detected");
	// 		driveTrain.forwards();
	// 		delay(1000);
	// 	}
	// 	if (success == 2) {
	// 		Serial.println("second tee detected");
	// 		driveTrain.forwards();
	// 		delay(1000);
	// 		lineFollow.findLine(digitalRead(modePin));
	// 		lineFollow.followLine();
	// 	}
	// 	Serial.println();
	// }

	// driveTrain.rotateLeft();

	// Serial.print("Left sensor: ");
	// Serial.println(analogRead(leftSensorPin));
	// Serial.print("Right sensor: ");
	// Serial.println(analogRead(rightSensorPin));
	// Serial.println();
	// delay(1000);

	// if (!leftSensor.status() && !rightSensor.status()) {
	// 	driveTrain.forwards();
	// 	Serial.println("drive");
	// } else {
	// 	driveTrain.stop();
	// 	Serial.println("stop");
	// 	delay(1000);
	// }