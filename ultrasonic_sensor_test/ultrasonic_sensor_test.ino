#define USE_TIMER_1     true

#include <TimerInterrupt.h>
#include <ISR_Timer.h>
#include "Motor.h"

const int triggerPin = 9;
const int echoPin = 10;
const int freq = 1;

long duration;
int distance;
volatile byte state = LOW;

const int in = 7;
const int out = 8;
const int en = 9;
const int duty = 200;

Motor motor(in, out, en, duty);

void setup() {
	Serial.begin(9600);
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);

	pinMode(in, OUTPUT);
	pinMode(out, OUTPUT);
	pinMode(en, OUTPUT);

// 	ITimer1.init();
// 	if (ITimer1.attachInterrupt(freq, TimerHandler))
// 		Serial.println("Starting  ITimer1 OK, millis() = " + String(millis()));
// 	else
// 		Serial.println("Can't set ITimer1. Select another freq. or timer");
}

void loop() {
	Serial.println(motor.getSpeed());
	// digitalWrite(triggerPin, LOW);
	// delayMicroseconds(2);
	// digitalWrite(triggerPin, HIGH);
	// delayMicroseconds(10);
	// digitalWrite(triggerPin, LOW);
	// duration = pulseIn(echoPin, HIGH);
	// distance = duration * 0.034 / 2;
	// Serial.print("Distance: ");
	// Serial.print(distance);
	// Serial.println(" cm");
	// delay(1000);
}

void TimerHandler() {
  Serial.println("timer");
}
