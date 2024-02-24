#define USE_TIMER_1     true

#include <TimerInterrupt.h>
#include <ISR_Timer.h>
#include "Motor.h"
#include "DriveTrain.h"

const int inA = 8;
const int outA = 7;
const int enableA = 9;

const int inB = 13;
const int outB = 12;
const int enableB = 11;
int duty = 200; // 0 - 255

Motor leftMotor(inA, outA, enableA, duty);
Motor rightMotor(inB, outB, enableB, duty);
DriveTrain driveTrain(leftMotor, rightMotor, duty);

int freq = 1;

void setup() {
	Serial.begin(9600);

	// pinout for left motor
	pinMode(inA, OUTPUT);
	pinMode(outA, OUTPUT);
	pinMode(enableA, OUTPUT);

	// pinout for right motor
	pinMode(inB, OUTPUT);
	pinMode(outB, OUTPUT);
	pinMode(enableB, OUTPUT);

	ITimer1.init();
	if (ITimer1.attachInterrupt(freq, TimerHandler))
		Serial.println("Starting  ITimer1 OK, millis() = " + String(millis()));
	else
		Serial.println("Can't set ITimer1. Select another freq. or timer");
}

void loop() {
	//driveTrain.forwards();
}

void TimerHandler(void) {
	Serial.println("HERE");
}