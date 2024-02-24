#include "Motor.h"
#include "Arduino.h"
using namespace std;

Motor::Motor() {
	// empty constructor
}

Motor::Motor(const int in, const int out, const int enable) {
	this->in = in;
	this->out = out;
	this->enable = enable;
}

Motor::Motor(const int in, const int out, const int enable, const int speed) {
	this->in = in;
	this->out = out;
	this->enable = enable;
	this->speed = speed;
}

void Motor::setSpeed(int speed) {
	this->speed = speed;
}

int Motor::getSpeed(void) const {
	return speed;
}

void Motor::stop(void) {
	analogWrite(in, 0);
	analogWrite(out, 0);
}

void Motor::spinForwards(void) {
	analogWrite(in, speed);
	analogWrite(out, 0);
}

void Motor::spinBackwards(void) {
	analogWrite(in, 0);
	analogWrite(out, speed);
}
