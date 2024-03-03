#include "Motor.h"
#include "DriveTrain.h"
#include "LineSensor.h"
#include "LineFollowing.h"
#include "LimitSwitch.h"
#include <Servo.h>

// ultrasonic definitions
const int trigPin1 = 2;   // LEFT
const int echoPin1 = 3;
const int trigPin2 = 4;   // RIGHT
const int echoPin2 = 5;
const int trigPinF = 10;  // FRONT
const int echoPinF = 11;

HCSR04 uL(2, 3); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)
HCSR04 uR(4, 5);
HCSR04 uF(A3, A2);

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

// motor definitions
const int inLeft = 8;
const int outLeft = 7;
const int enableLeft = 6;
const int inRight = 13;
const int outRight = 12;
const int enableRight = 11;
int dutyLeft = 110;  // 0 - 255
int dutyRight = 80;
Motor leftMotor(inLeft, outLeft, enableLeft, dutyLeft);
Motor rightMotor(inRight, outRight, enableRight, dutyRight);
DriveTrain driveTrain(leftMotor, rightMotor, dutyLeft, dutyRight);

// line sensor definitions
const int leftSensorPin = A0;
const int rightSensorPin = A1;
const int threshold = 60;
LineSensor leftSensor(threshold, leftSensorPin);
LineSensor rightSensor(threshold, rightSensorPin);

// line following definition
LineFollowing lineFollow(leftSensor, rightSensor, driveTrain, uF);

// mode swtich
const int modePin = A5;

// servos 
const int dartServoPin = 9;
const int celebrationServoPin = 10;
Servo dartServo;
Servo celebrationServo;

int notOriented = 1;
int oriented = 0;
int findFirstTee = 0;
int firstTeeDetected = 0;
int secondTeeDetected = 0;
int findLine = 0;
int touchTheButt = 0;
int rotate90 = 0;
int findTeeBackwards = 0;
int driveToDropZone = 0;
int rotateToDropZone = 0;
int driveAtDropZone = 0;
int dispense = 0;
int celebrate = 0;

void setup() {
	Serial.begin(9600);

	// pin config for left motor
	pinMode(inLeft, OUTPUT);
	pinMode(outLeft, OUTPUT);
	pinMode(enableLeft, OUTPUT);
	pinMode(enableRight, OUTPUT);

	// pin config for right motor
	pinMode(inRight, OUTPUT);
	pinMode(outRight, OUTPUT);

	// pin config for line sensors
	pinMode(leftSensorPin, INPUT);
	pinMode(rightSensorPin, INPUT);

	// pin config for input mode
	pinMode(modePin, INPUT_PULLUP);

	// pin config for ultrasonics
	pinMode(trigPin1, OUTPUT);
	pinMode(trigPin2, OUTPUT);
	pinMode(trigPinF, OUTPUT);
	pinMode(echoPin1, INPUT);
	pinMode(echoPin2, INPUT);
	pinMode(echoPinF, INPUT);
	digitalWrite(trigPin1, LOW);  // no trigger signal
	digitalWrite(trigPin2, LOW);  // no trigger signal

	// pin config for servos
	dartServo.attach(dartServoPin);
	celebrationServo.attach(celebrationServoPin);
	celebrationServo.write(0);
	dartServo.write(0);
}

void loop() {
	// Serial.println("HERE");
	celebrationServo.write(0);
	dartServo.write(0);

	// driveTrain.rotate90Left();
	// delay(2000);
	// driveTrain.rotate90Right();
	// delay(2000);

	// orient outwards away from walls
	if (notOriented) {
		// Serial.println("\nBeginning!");
		notOriented = TestStartZone();
		// Serial.println("Oriented outwards.");
		delay(1000);
		oriented = 1;
	}

	// rotate towards line according to mode
	if (oriented) {
		if (digitalRead(modePin)) {
			driveTrain.rotateRight();
			delay(1000);
			driveTrain.stop();
		} else {
			driveTrain.rotateLeft();
			delay(1000);
			driveTrain.stop();
		}
		// Serial.println("Oriented towards line. Ready to find first tee.");
		oriented = 0;
		findFirstTee = 1;
	}

	// do line following to first tee
	if (findFirstTee) {
		findFirstTee = lineFollow.followLine();
		// Serial.println("First tee detected. Ready for line following");
		driveTrain.stop();
		firstTeeDetected = 1;
	}

	// do line following to second tee
	if (firstTeeDetected) {
		driveTrain.forwards();
		delay(1000);
		firstTeeDetected = lineFollow.followLine();
		// Serial.println("Second tee detected.");
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
		// Serial.println("Second tee crossed.");
		secondTeeDetected = 0;
		findLine = 1;
	}

	// find next line, do line following, and stop at wall.
	if (findLine) {
		findLine = lineFollow.findLine(digitalRead(modePin));
		// Serial.println("found next line.");
		delay(1000);
		lineFollow.followLine();
		driveTrain.stop();
		// Serial.println("stopped at wall");
		delay(1000);
		touchTheButt = 1;
	}

	// touch the contact zone
	if (touchTheButt) {
		celebrationServo.write(180);
		delay(1000);
		celebrationServo.write(0);
		delay(1000);
		celebrationServo.write(180);
		delay(1000);
		touchTheButt = 0;
		rotate90 = 1;
	}

	// backup, rotate ~90 degrees, and backup again
	if (rotate90) {
		driveTrain.backwards();
		delay(2000);
		if (digitalRead(modePin)) {
			driveTrain.rotate90Left();
			// Serial.println("rotated towards drop zone");
		} else {
			driveTrain.rotate90Right();
		}
		driveTrain.backwards();
		delay(2000);
		driveTrain.stop();
		rotate90 = 0;
		findTeeBackwards = 1;
	}

	// do line following to find tee and become "oriented"
	if (findTeeBackwards) {
		lineFollow.followLine();
		driveTrain.stop();
		delay(1000);
		driveTrain.forwards();
		delay(1000);
		driveTrain.stop();
		delay(1000);
		driveToDropZone = 1;
	}

	// drive straight along wall to drop zone
	if (driveToDropZone) {
		lineFollow.followLine();
		driveTrain.stop();
		// Serial.println("at drop zone");
		delay(1000);
		driveToDropZone = 0;
		rotateToDropZone = 1;
	}

	// rotate towards drop zone
	if (rotateToDropZone) {
		driveTrain.backwards();
		delay(200);
		if (digitalRead(modePin)) {
			driveTrain.rotateRight();
			delay(2100);
		}
		else {
			driveTrain.rotateLeft();
			delay(1900);
		}
		driveTrain.stop();
		rotateToDropZone = 0;
		driveAtDropZone = 1;
		delay(1000);
		// Serial.println("rotated towards drop zone");
	}

	if (driveAtDropZone) {
		driveTrain.forwards();
		delay(3000);
		// lineFollow.followLine();
		driveTrain.stop();
		driveAtDropZone = 0;
		dispense = 1;
	}
	
	if (dispense) {
		if (digitalRead(modePin)) {
			driveTrain.rotateLeft();
			delay(300);
			driveTrain.stop();
		}
		else {
			driveTrain.rotateRight();
			delay(300);
			driveTrain.stop();
		}
		dartServo.write(120);
		delay(1000);
		dispense = 0;
		celebrate = 1;
	}

	if (celebrate) {
		driveTrain.stop();
	}

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
			return 0;
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

