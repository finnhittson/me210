#include "Motor.h"
#include "DriveTrain.h"
#include "LineSensor.h"
#include "LineFollowing.h"
#include "LimitSwitch.h"
#include "FindLine.h"
#include <HCSR04.h>

// ultrasonic definitions
const int trigPin1 = 2;   // LEFT
const int echoPin1 = 3;
const int trigPin2 = 4;   // RIGHT
const int echoPin2 = 5;
const int trigPinF = 10;  // FRONT
const int echoPinF = 11;

HCSR04 uL(2, 3); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)
HCSR04 uR(4, 5);
HCSR04 uF(10, 11);

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
const int threshold = 60;
LineSensor leftSensor(threshold, leftSensorPin);
LineSensor rightSensor(threshold, rightSensorPin);

// line following definition
LineFollowing lineFollow(leftSensor, rightSensor, driveTrain);

// mode swtich
const int modePin = A5;

int orientOnce = 1;
int oriented = 0;
int doLineFollowing = 0;
int firstTeeDetected = 0;
int secondTeeDetected = 0;
int findLine = 0;

// motor + ultrasonic vars
bool keepDriving = true;
bool findCorner = false;
float loThresh = 3.0;       // [cm]
float hiThresh = 800.0;     // [in] when <1" away from sensor
float farThresh = 40.0;     // [cm]
unsigned long lastTime;
float dist1;
float dist2;
float distF; 

bool AtFrontWall(HCSR04 uF, float thresh);

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

	pinMode(trigPin1, OUTPUT);
	pinMode(trigPin2, OUTPUT);
	pinMode(trigPinF, OUTPUT);
	pinMode(echoPin1, INPUT);
	pinMode(echoPin2, INPUT);
	pinMode(echoPinF, INPUT);

	digitalWrite(trigPin1, LOW);  // no trigger signal
	digitalWrite(trigPin2, LOW);  // no trigger signal
}

void loop() {

	// orient outwards away from walls
	if (!orientOnce) {
		orientOnce = TestStartZone();
		oriented = 1;
		Serial.println("\nOriented outwards.");
		delay(1000);
	}

	// rotate towards line according to mode
	if (oriented) {
		if (digitalRead(modePin)) {
			driveTrain.rotateRight();
			delay(700);
			driveTrain.stop();
		} else {
			driveTrain.rotateLeft();
			delay(700);
			driveTrain.stop();
		}
		oriented = 0;
		doLineFollowing = 1;
		Serial.println("Oriented towards line. Ready for line following.");
	}

	// do line following to first tee
	if (doLineFollowing) {
		doLineFollowing = lineFollow.followLine();
		Serial.println("First tee detected.");
		driveTrain.stop();
		firstTeeDetected = 1;
	}

	// do line following to second tee
	if (firstTeeDetected) {
		driveTrain.forwards();
		delay(1000);
		firstTeeDetected = lineFollow.followLine();
		Serial.println("Second tee detected.");
		driveTrain.stop();
		delay(1000);
		secondTeeDetected = 1;
	}

	// cross over tee
	if (secondTeeDetected) {
		driveTrain.forwards();
		delay(1000);
		driveTrain.stop();
		delay(1000);
		findLine = 1;
		Serial.println("second tee crossed.");
	}

	if (findLine) {
		findLine = lineFollow.findLine(digitalRead(modePin));
		Serial.println("found next line.");
		lineFollow.followLine();
	}
	Serial.println(AtFrontWall(uF, 3.0));
	if (!AtFrontWall(uF, 3.0))
		driveTrain.forwards();


	// // test line sensors
	// Serial.print("Left sensor: ");
	// Serial.println(analogRead(leftSensorPin));
	// Serial.print("Right sensor: ");
	// Serial.println(analogRead(rightSensorPin));
	// Serial.println();
	// delay(1000);
}

int TestStartZone() {
	lastTime = millis();
	bool run = true;
	while (run) {
		dist1 = uL.dist();
		dist2 = uR.dist();
		distF = uF.dist();
		// Serial.println(dist1);
		// Serial.println(dist2);
		// Serial.println(distF);

		if (!keepDriving) {
			driveTrain.stop();
			run = false;
			return 1;
		}
		else {
			if (distF > farThresh) {
				findCorner = true;
				// Serial.println("good");
			}
			else {
				findCorner = false;
			}
			if (!findCorner) {
				if (dist1 > farThresh) {
					driveTrain.rotateLeft();
					// Serial.println("left!");
				}
				if (dist2 > farThresh) {
					driveTrain.rotateRight();
					// Serial.println("right");
				}
				if (dist1 <= farThresh && dist2 <= farThresh && distF <= farThresh) {
					driveTrain.rotateLeft();
					// Serial.println("left");
				}
			}
			else {
				if (dist1 - dist2 > 5) {
					driveTrain.rotateLeft();
					// Serial.println("good left");
				}
				else if (dist2 - dist1 > 5) {
					driveTrain.rotateRight();
					// Serial.println("good right");
				}
				else {
					driveTrain.stop();
					// Serial.println("good stop");
					keepDriving = false;
				}
			}

			if (millis() - lastTime < 60) {
				delay(millis() - lastTime);
			}
		}
	}
}

bool AtFrontWall(HCSR04 uF, float thresh=3.0) {
	int d = uF.dist();
	if (d > thresh) return false;
	else return true;
}