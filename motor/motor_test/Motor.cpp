#include "Motor.h"
#include "Arduino.h"
using namespace std;

Motor::Motor() {
	// empty constructor
}

Motor::Motor(const int mp1, const int mp2) {
	motorPin1 = mp1;
	motorPin2 = mp2;
}

Motor::Motor(const int mp1, const int mp2, const int speed) {
	motorPin1 = mp1;
	motorPin2 = mp2;
	this->speed = speed;
}

void Motor::setSpeed(int speed) {
	this->speed = speed;
}

int Motor::getSpeed(void) const {
	return speed;
}

void Motor::stop(void) {
	analogWrite(motorPin1, 0);
	analogWrite(motorPin2, 0);
}

void Motor::spinForwards(void) {
	analogWrite(motorPin1, speed);
	analogWrite(motorPin2, 0);
}

void Motor::spinBackwards(void) {
	analogWrite(motorPin1, 0);
	analogWrite(motorPin2, speed);
}
