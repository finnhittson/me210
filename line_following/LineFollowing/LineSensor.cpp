#include "LineSensor.h"
#include "Arduino.h"
using namespace std;

LineSensor::LineSensor() : threshold(0), sensorPin(0) {
	// empty
}

LineSensor::LineSensor(const int threshold, const int sensorPin) : threshold(threshold), sensorPin(sensorPin) {
	// empty
}

int LineSensor::getThreshold() {
	return threshold;
}

void LineSensor::setThreshold(const int threshold) {
	this->threshold = threshold;
}

int LineSensor::getSensorPin() {
	return sensorPin;
}

void LineSensor::setSensorPin(const int sensorPin) {
	this->sensorPin = sensorPin;
}

// true if on line, false if off line
bool LineSensor::status() const {
	int sensor = analogRead(sensorPin);
	if (sensor < threshold)
		return true;
	return false;
}