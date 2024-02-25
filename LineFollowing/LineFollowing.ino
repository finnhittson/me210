#include "LineSensor.h"

const int leftSensorPin = A0;
const int threshold = 30;
LineSensor leftSensor(threshold, leftSensorPin);

void setup() {
	Serial.begin(9600);
	pinMode(leftSensorPin, INPUT);
}

void loop() {
	if (leftSensor.status())
		Serial.println("on line");
	else
		Serial.println("off line");
	delay(1000);
}
